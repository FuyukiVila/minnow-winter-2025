#include <iostream>

#include "arp_message.hh"
#include "debug.hh"
#include "ethernet_frame.hh"
#include "exception.hh"
#include "helpers.hh"
#include "network_interface.hh"

using namespace std;

//! \param[in] ethernet_address Ethernet (what ARP calls "hardware") address of the interface
//! \param[in] ip_address IP (what ARP calls "protocol") address of the interface
NetworkInterface::NetworkInterface( string_view name,
                                    shared_ptr<OutputPort> port,
                                    const EthernetAddress& ethernet_address,
                                    const Address& ip_address )
  : name_( name )
  , port_( notnull( "OutputPort", move( port ) ) )
  , ethernet_address_( ethernet_address )
  , ip_address_( ip_address )
{
  cerr << "DEBUG: Network interface has Ethernet address " << to_string( ethernet_address_ ) << " and IP address "
       << ip_address.ip() << "\n";
}

//! \param[in] dgram the IPv4 datagram to be sent
//! \param[in] next_hop the IP address of the interface to send it to (typically a router or default gateway, but
//! may also be another host if directly connected to the same network as the destination) Note: the Address type
//! can be converted to a uint32_t (raw 32-bit IP address) by using the Address::ipv4_numeric() method.
void NetworkInterface::send_datagram( const InternetDatagram& dgram, const Address& next_hop )
{
  const uint32_t next_hop_ip = next_hop.ipv4_numeric();

  // 查找 ARP 缓存
  auto arp_it = arp_cache_.find( next_hop_ip );
  if ( arp_it != arp_cache_.end() ) {
    // 找到了 ARP 缓存，直接发送以太网帧
    EthernetFrame frame;
    frame.header.dst = arp_it->second.eth_addr;
    frame.header.src = ethernet_address_;
    frame.header.type = EthernetHeader::TYPE_IPv4;
    frame.payload = serialize( dgram );
    transmit( frame );
  } else {
    // 检查是否最近已发送过 ARP 请求
    auto arp_req_it = arp_request_sent_.find( next_hop_ip );
    if ( arp_req_it == arp_request_sent_.end() || arp_req_it->second >= ARP_REQUEST_TIMEOUT_MS ) {
      // 如果之前的请求已超时，清空待发送队列
      if ( arp_req_it != arp_request_sent_.end() ) {
        pending_datagrams_.erase( next_hop_ip );
      }

      // 发送 ARP 请求
      ARPMessage arp_request;
      arp_request.opcode = ARPMessage::OPCODE_REQUEST;
      arp_request.sender_ethernet_address = ethernet_address_;
      arp_request.sender_ip_address = ip_address_.ipv4_numeric();
      arp_request.target_ethernet_address = {}; // 未知
      arp_request.target_ip_address = next_hop_ip;

      EthernetFrame frame;
      frame.header.dst = ETHERNET_BROADCAST;
      frame.header.src = ethernet_address_;
      frame.header.type = EthernetHeader::TYPE_ARP;
      frame.payload = serialize( arp_request );
      transmit( frame );

      // 记录 ARP 请求发送时间
      arp_request_sent_[next_hop_ip] = 0;
    }

    // 将数据报加入等待队列
    pending_datagrams_[next_hop_ip].push( dgram );
  }
}

//! \param[in] frame the incoming Ethernet frame
void NetworkInterface::recv_frame( EthernetFrame frame )
{
  // 忽略不是发给我的帧（除非是广播）
  if ( frame.header.dst != ethernet_address_ && frame.header.dst != ETHERNET_BROADCAST ) {
    return;
  }

  if ( frame.header.type == EthernetHeader::TYPE_IPv4 ) {
    // IPv4 数据报
    InternetDatagram dgram;
    if ( parse( dgram, frame.payload ) ) {
      datagrams_received_.push( dgram );
    }
  } else if ( frame.header.type == EthernetHeader::TYPE_ARP ) {
    // ARP 消息
    ARPMessage arp_msg;
    if ( !parse( arp_msg, frame.payload ) ) {
      return;
    }

    // 学习发送者的映射（无论是请求还是响应）
    arp_cache_[arp_msg.sender_ip_address] = { arp_msg.sender_ethernet_address, ARP_CACHE_TTL_MS };

    // 如果有等待该 IP 的数据报，现在可以发送了
    auto pending_it = pending_datagrams_.find( arp_msg.sender_ip_address );
    if ( pending_it != pending_datagrams_.end() ) {
      while ( !pending_it->second.empty() ) {
        const InternetDatagram& pending_dgram = pending_it->second.front();

        EthernetFrame eth_frame;
        eth_frame.header.dst = arp_msg.sender_ethernet_address;
        eth_frame.header.src = ethernet_address_;
        eth_frame.header.type = EthernetHeader::TYPE_IPv4;
        eth_frame.payload = serialize( pending_dgram );
        transmit( eth_frame );

        pending_it->second.pop();
      }
      pending_datagrams_.erase( pending_it );
    }

    // 删除 ARP 请求发送记录
    arp_request_sent_.erase( arp_msg.sender_ip_address );

    // 如果是发给我的 ARP 请求，发送响应
    if ( arp_msg.opcode == ARPMessage::OPCODE_REQUEST && arp_msg.target_ip_address == ip_address_.ipv4_numeric() ) {
      ARPMessage arp_reply;
      arp_reply.opcode = ARPMessage::OPCODE_REPLY;
      arp_reply.sender_ethernet_address = ethernet_address_;
      arp_reply.sender_ip_address = ip_address_.ipv4_numeric();
      arp_reply.target_ethernet_address = arp_msg.sender_ethernet_address;
      arp_reply.target_ip_address = arp_msg.sender_ip_address;

      EthernetFrame reply_frame;
      reply_frame.header.dst = arp_msg.sender_ethernet_address;
      reply_frame.header.src = ethernet_address_;
      reply_frame.header.type = EthernetHeader::TYPE_ARP;
      reply_frame.payload = serialize( arp_reply );
      transmit( reply_frame );
    }
  }
}

//! \param[in] ms_since_last_tick the number of milliseconds since the last call to this method
void NetworkInterface::tick( const size_t ms_since_last_tick )
{
  // 更新 ARP 缓存的 TTL
  for ( auto it = arp_cache_.begin(); it != arp_cache_.end(); ) {
    if ( it->second.ttl_ms <= ms_since_last_tick ) {
      it = arp_cache_.erase( it );
    } else {
      it->second.ttl_ms -= ms_since_last_tick;
      ++it;
    }
  }

  // 更新 ARP 请求发送时间
  for ( auto& entry : arp_request_sent_ ) {
    entry.second += ms_since_last_tick;
  }
}
