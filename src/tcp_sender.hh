#pragma once

#include "byte_stream.hh"
#include "tcp_receiver_message.hh"
#include "tcp_sender_message.hh"

#include <functional>
#include <queue>

class TCPSender
{
public:
  /* Construct TCP sender with given default Retransmission Timeout and possible ISN */
  TCPSender( ByteStream&& input, Wrap32 isn, uint64_t initial_RTO_ms )
    : input_( std::move( input ) ), isn_( isn ), initial_RTO_ms_( initial_RTO_ms )
  {}

  /* Generate an empty TCPSenderMessage */
  TCPSenderMessage make_empty_message() const;

  /* Receive and process a TCPReceiverMessage from the peer's receiver */
  void receive( const TCPReceiverMessage& msg );

  /* Type of the `transmit` function that the push and tick methods can use to send messages */
  using TransmitFunction = std::function<void( const TCPSenderMessage& )>;

  /* Push bytes from the outbound stream */
  void push( const TransmitFunction& transmit );

  /* Time has passed by the given # of milliseconds since the last time the tick() method was called */
  void tick( uint64_t ms_since_last_tick, const TransmitFunction& transmit );

  // Accessors
  uint64_t sequence_numbers_in_flight() const;  // For testing: how many sequence numbers are outstanding?
  uint64_t consecutive_retransmissions() const; // For testing: how many consecutive retransmissions have happened?
  const Writer& writer() const { return input_.writer(); }
  const Reader& reader() const { return input_.reader(); }
  Writer& writer() { return input_.writer(); }

private:
  Reader& reader() { return input_.reader(); }

  ByteStream input_;
  Wrap32 isn_;
  uint64_t initial_RTO_ms_;

  // 窗口和确认信息
  uint64_t ackno_ { 0 };       // 接收方确认的下一个序列号（绝对序列号）
  uint16_t window_size_ { 1 }; // 接收方的窗口大小

  // 发送状态
  uint64_t next_seqno_ { 0 }; // 下一个要发送的序列号（绝对序列号）
  bool syn_sent_ { false };   // 是否已发送 SYN
  bool fin_sent_ { false };   // 是否已发送 FIN

  // 未确认的段队列
  std::queue<TCPSenderMessage> outstanding_segments_ {}; // 已发送但未确认的段
  uint64_t outstanding_cnt_ { 0 };                       // 未确认的序列号数量

  // 重传计时器
  uint64_t timer_ms_ { 0 };         // 计时器已运行的时间
  uint64_t current_RTO_ms_ { 0 };   // 当前 RTO 值
  bool timer_is_running_ { false }; // 计时器是否运行
  uint64_t consecutive_retx_ { 0 }; // 连续重传次数
};
