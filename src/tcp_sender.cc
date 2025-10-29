#include "tcp_sender.hh"
#include "debug.hh"
#include "tcp_config.hh"

using namespace std;

// 返回未确认的序列号总数
uint64_t TCPSender::sequence_numbers_in_flight() const
{
  return outstanding_cnt_;
}

// 返回连续重传次数
uint64_t TCPSender::consecutive_retransmissions() const
{
  return consecutive_retx_;
}

void TCPSender::push( const TransmitFunction& transmit )
{
  // 计算可用窗口大小
  // 特殊情况：如果接收方窗口为0，仍然尝试发送1字节（窗口探测）
  uint64_t window_size = window_size_ == 0 ? 1 : window_size_;
  uint64_t bytes_in_flight = next_seqno_ - ackno_;

  // 如果窗口已满，无法发送
  if ( bytes_in_flight >= window_size ) {
    return;
  }

  uint64_t available_window = window_size - bytes_in_flight;

  // 持续发送直到窗口满或没有数据
  while ( available_window > 0 ) {
    TCPSenderMessage msg;
    msg.seqno = Wrap32::wrap( next_seqno_, isn_ );

    // 如果 ByteStream 有错误，设置 RST 标志
    if ( reader().has_error() ) {
      msg.RST = true;
    }

    // 1. 如果还没发送 SYN，发送它
    if ( !syn_sent_ ) {
      msg.SYN = true;
      syn_sent_ = true;
      available_window--;
    }

    // 2. 读取数据（不超过窗口大小和最大负载大小）
    uint64_t payload_size = min( available_window, static_cast<uint64_t>( TCPConfig::MAX_PAYLOAD_SIZE ) );

    // 从 ByteStream 读取数据
    string payload;
    while ( payload.size() < payload_size && reader().bytes_buffered() > 0 ) {
      string_view view = reader().peek();
      uint64_t to_read = min( static_cast<uint64_t>( view.size() ), payload_size - payload.size() );
      payload += view.substr( 0, to_read );
      reader().pop( to_read );
    }

    msg.payload = payload;
    available_window -= payload.size();

    // 3. 如果流结束且有空间，发送 FIN
    if ( !fin_sent_ && reader().is_finished() && available_window > 0 ) {
      msg.FIN = true;
      fin_sent_ = true;
      available_window--;
    }

    // 4. 如果这个段没有占用任何序列号，停止发送
    uint64_t seq_length = msg.sequence_length();
    if ( seq_length == 0 ) {
      break;
    }

    // 5. 发送段并加入未确认队列
    transmit( msg );
    outstanding_segments_.push( msg );
    outstanding_cnt_ += seq_length;
    next_seqno_ += seq_length;

    // 6. 如果计时器未运行，启动它
    if ( !timer_is_running_ ) {
      timer_is_running_ = true;
      timer_ms_ = 0;
      current_RTO_ms_ = initial_RTO_ms_;
    }

    // 如果已经发送了 FIN，停止发送
    if ( msg.FIN ) {
      break;
    }
  }
}

TCPSenderMessage TCPSender::make_empty_message() const
{
  TCPSenderMessage msg;
  msg.seqno = Wrap32::wrap( next_seqno_, isn_ );
  // 如果 ByteStream 有错误，设置 RST 标志
  if ( reader().has_error() ) {
    msg.RST = true;
  }
  return msg;
}

void TCPSender::receive( const TCPReceiverMessage& msg )
{
  // 如果收到 RST 标志，设置流的错误状态
  if ( msg.RST ) {
    writer().set_error();
  }

  // 更新窗口大小
  window_size_ = msg.window_size;

  // 如果没有 ackno，直接返回
  if ( !msg.ackno.has_value() ) {
    return;
  }

  // 将 ackno 转换为绝对序列号
  uint64_t abs_ackno = msg.ackno.value().unwrap( isn_, next_seqno_ );

  // 如果 ackno 无效（超出已发送的范围），忽略
  if ( abs_ackno > next_seqno_ ) {
    return;
  }

  // 如果这是一个新的确认（确认了新数据）
  if ( abs_ackno > ackno_ ) {
    // 更新 ackno
    ackno_ = abs_ackno;

    // 移除已完全确认的段
    while ( !outstanding_segments_.empty() ) {
      const auto& segment = outstanding_segments_.front();
      uint64_t seg_start = segment.seqno.unwrap( isn_, next_seqno_ );
      uint64_t seg_end = seg_start + segment.sequence_length();

      // 如果这个段已被完全确认
      if ( seg_end <= abs_ackno ) {
        outstanding_cnt_ -= segment.sequence_length();
        outstanding_segments_.pop();
      } else {
        break;
      }
    }

    // 重置 RTO 为初始值
    current_RTO_ms_ = initial_RTO_ms_;

    // 重置连续重传次数
    consecutive_retx_ = 0;

    // 如果还有未确认的数据，重启计时器
    if ( !outstanding_segments_.empty() ) {
      timer_is_running_ = true;
      timer_ms_ = 0;
    } else {
      // 否则停止计时器
      timer_is_running_ = false;
    }
  }
}

void TCPSender::tick( uint64_t ms_since_last_tick, const TransmitFunction& transmit )
{
  // 更新计时器
  timer_ms_ += ms_since_last_tick;

  // 如果计时器未运行，直接返回
  if ( !timer_is_running_ ) {
    return;
  }

  // 检查是否超时
  if ( timer_ms_ >= current_RTO_ms_ ) {
    // 重传最早的未确认段
    if ( !outstanding_segments_.empty() ) {
      transmit( outstanding_segments_.front() );

      // 如果窗口大小非零
      if ( window_size_ > 0 ) {
        // 增加连续重传次数
        consecutive_retx_++;

        // RTO 翻倍（指数退避）
        current_RTO_ms_ *= 2;
      }

      // 重置并重启计时器
      timer_ms_ = 0;
      timer_is_running_ = true;
    }
  }
}
