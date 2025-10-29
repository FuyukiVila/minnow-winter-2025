#include "tcp_receiver.hh"
#include "debug.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  // 如果收到 RST 标志，设置流的错误状态并立即返回
  if ( message.RST ) {
    reader().set_error();
    return;
  }

  // 如果消息包含 SYN 标志，设置初始序列号
  if ( message.SYN ) {
    isn_ = message.seqno;
  }

  // 如果还没收到 SYN，无法处理消息（因为不知道序列号的零点）
  if ( !isn_.has_value() ) {
    return;
  }

  // 将序列号转换为绝对序列号
  uint64_t abs_seqno = message.seqno.unwrap( isn_.value(), writer().bytes_pushed() );

  // 计算流索引（stream index）：
  // - 绝对序列号 0 对应 SYN（不是数据）
  // - 数据从绝对序列号 1 开始
  // - 如果当前消息也包含 SYN，数据从 abs_seqno + 1 开始
  // - 流索引 = 绝对序列号 - 1（减去 SYN 占用的位置）
  uint64_t stream_index = message.SYN ? 0 : abs_seqno - 1;

  // 将数据推送到重组器
  reassembler_.insert( stream_index, message.payload, message.FIN );
}

TCPReceiverMessage TCPReceiver::send() const
{
  TCPReceiverMessage msg {};

  // 只有在收到 SYN 后才能发送确认号
  if ( isn_.has_value() ) {
    // 计算下一个需要的绝对序列号：
    // - bytes_pushed() 是已推送的数据字节数（不包括 SYN）
    // - +1 是因为 SYN 占用一个序列号
    uint64_t abs_ackno = writer().bytes_pushed() + 1;

    // 如果流已经关闭（收到并处理了 FIN），FIN 也占用一个序列号
    if ( writer().is_closed() ) {
      abs_ackno += 1;
    }

    // 将绝对序列号转换回序列号
    msg.ackno = Wrap32::wrap( abs_ackno, isn_.value() );
  }

  // 计算窗口大小（接收器的可用容量）
  uint64_t capacity = writer().available_capacity();
  // 窗口大小字段只有 16 位，最大值为 65535
  msg.window_size
    = static_cast<uint16_t>( min( capacity, static_cast<uint64_t>( numeric_limits<uint16_t>::max() ) ) );

  // 如果写入器遇到错误，设置 RST 标志
  msg.RST = writer().has_error();

  return msg;
}
