#pragma once

#include "address.hh"
#include "ethernet_frame.hh"
#include "ipv4_datagram.hh"

#include <memory>
#include <queue>
#include <unordered_map>

// A "network interface" that connects IP (the internet layer, or network layer)
// with Ethernet (the network access layer, or link layer).

// This module is the lowest layer of a TCP/IP stack
// (connecting IP with the lower-layer network protocol,
// e.g. Ethernet). But the same module is also used repeatedly
// as part of a router: a router generally has many network
// interfaces, and the router's job is to route Internet datagrams
// between the different interfaces.

// The network interface translates datagrams (coming from the
// "customer," e.g. a TCP/IP stack or router) into Ethernet
// frames. To fill in the Ethernet destination address, it looks up
// the Ethernet address of the next IP hop of each datagram, making
// requests with the [Address Resolution Protocol](\ref rfc::rfc826).
// In the opposite direction, the network interface accepts Ethernet
// frames, checks if they are intended for it, and if so, processes
// the the payload depending on its type. If it's an IPv4 datagram,
// the network interface passes it up the stack. If it's an ARP
// request or reply, the network interface processes the frame
// and learns or replies as necessary.
class NetworkInterface
{
public:
  // An abstraction for the physical output port where the NetworkInterface sends Ethernet frames
  class OutputPort
  {
  public:
    virtual void transmit( const NetworkInterface& sender, const EthernetFrame& frame ) = 0;
    virtual ~OutputPort() = default;
  };

  // Construct a network interface with given Ethernet (network-access-layer) and IP (internet-layer)
  // addresses
  NetworkInterface( std::string_view name,
                    std::shared_ptr<OutputPort> port,
                    const EthernetAddress& ethernet_address,
                    const Address& ip_address );

  // Sends an Internet datagram, encapsulated in an Ethernet frame (if it knows the Ethernet destination
  // address). Will need to use [ARP](\ref rfc::rfc826) to look up the Ethernet destination address for the next
  // hop. Sending is accomplished by calling `transmit()` (a member variable) on the frame.
  void send_datagram( const InternetDatagram& dgram, const Address& next_hop );

  // Receives an Ethernet frame and responds appropriately.
  // If type is IPv4, pushes the datagram to the datagrams_in queue.
  // If type is ARP request, learn a mapping from the "sender" fields, and send an ARP reply.
  // If type is ARP reply, learn a mapping from the "sender" fields.
  void recv_frame( EthernetFrame frame );

  // Called periodically when time elapses
  void tick( size_t ms_since_last_tick );

  // Accessors
  const std::string& name() const { return name_; }
  const OutputPort& output() const { return *port_; }
  OutputPort& output() { return *port_; }
  std::queue<InternetDatagram>& datagrams_received() { return datagrams_received_; }

private:
  // Human-readable name of the interface
  std::string name_;

  // The physical output port (+ a helper function `transmit` that uses it to send an Ethernet frame)
  std::shared_ptr<OutputPort> port_;
  void transmit( const EthernetFrame& frame ) const { port_->transmit( *this, frame ); }

  // Ethernet (known as hardware, network-access-layer, or link-layer) address of the interface
  EthernetAddress ethernet_address_;

  // IP (known as internet-layer or network-layer) address of the interface
  Address ip_address_;

  // Datagrams that have been received
  std::queue<InternetDatagram> datagrams_received_ {};

  // ARP 缓存：IP 地址到以太网地址的映射及其过期时间
  struct ARPEntry
  {
    EthernetAddress eth_addr;
    size_t ttl_ms; // 剩余生存时间（毫秒）
  };
  std::unordered_map<uint32_t, ARPEntry> arp_cache_ {}; // IP -> (以太网地址, TTL)

  // 等待 ARP 解析的数据报队列
  std::unordered_map<uint32_t, std::queue<InternetDatagram>> pending_datagrams_ {}; // IP -> 待发送的数据报队列

  // 最近发送 ARP 请求的记录（用于防止重复请求）
  std::unordered_map<uint32_t, size_t> arp_request_sent_ {}; // IP -> 发送后经过的时间（毫秒）

  // ARP 缓存的 TTL（30秒）
  static constexpr size_t ARP_CACHE_TTL_MS = 30000;
  // ARP 请求重发间隔（5秒）
  static constexpr size_t ARP_REQUEST_TIMEOUT_MS = 5000;
};
