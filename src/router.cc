#include "router.hh"
#include "debug.hh"

#include <iostream>

using namespace std;

// route_prefix: The "up-to-32-bit" IPv4 address prefix to match the datagram's destination address against
// prefix_length: For this route to be applicable, how many high-order (most-significant) bits of
//    the route_prefix will need to match the corresponding bits of the datagram's destination address?
// next_hop: The IP address of the next hop. Will be empty if the network is directly attached to the router (in
//    which case, the next hop address should be the datagram's final destination).
// interface_num: The index of the interface to send the datagram out on.
void Router::add_route( const uint32_t route_prefix,
                        const uint8_t prefix_length,
                        const optional<Address> next_hop,
                        const size_t interface_num )
{
  cerr << "DEBUG: adding route " << Address::from_ipv4_numeric( route_prefix ).ip() << "/"
       << static_cast<int>( prefix_length ) << " => " << ( next_hop.has_value() ? next_hop->ip() : "(direct)" )
       << " on interface " << interface_num << "\n";

  // 将路由添加到路由表
  routing_table_.push_back( { route_prefix, prefix_length, next_hop, interface_num } );
}

// Go through all the interfaces, and route every incoming datagram to its proper outgoing interface.
void Router::route()
{
  // 遍历所有接口，处理每个接口接收到的数据报
  for ( auto& iface : interfaces_ ) {
    auto& datagrams_received = iface->datagrams_received();

    while ( !datagrams_received.empty() ) {
      InternetDatagram dgram = datagrams_received.front();
      datagrams_received.pop();

      // 检查 TTL
      if ( dgram.header.ttl <= 1 ) {
        // TTL 已经为 0 或递减后为 0，丢弃数据报
        continue;
      }

      // 递减 TTL
      dgram.header.ttl--;
      // 重新计算校验和（因为 TTL 改变了）
      dgram.header.compute_checksum();

      // 查找最长前缀匹配的路由
      const uint32_t dst_ip = dgram.header.dst;
      optional<RouteEntry> best_match;
      uint8_t best_prefix_length = 0;

      for ( const auto& route : routing_table_ ) {
        // 检查是否匹配
        if ( route.prefix_length == 0 ) {
          // 默认路由（0.0.0.0/0）总是匹配
          if ( !best_match.has_value() || route.prefix_length > best_prefix_length ) {
            best_match = route;
            best_prefix_length = route.prefix_length;
          }
        } else {
          // 计算掩码
          uint32_t mask
            = ( route.prefix_length == 32 ) ? 0xFFFFFFFF : ( 0xFFFFFFFF << ( 32 - route.prefix_length ) );

          // 比较前缀
          if ( ( dst_ip & mask ) == ( route.route_prefix & mask ) ) {
            // 匹配，检查是否是更长的前缀
            if ( !best_match.has_value() || route.prefix_length > best_prefix_length ) {
              best_match = route;
              best_prefix_length = route.prefix_length;
            }
          }
        }
      }

      // 如果找到匹配的路由，转发数据报
      if ( best_match.has_value() ) {
        const auto& route = best_match.value();

        // 确定下一跳地址
        Address next_hop_addr = route.next_hop.value_or( Address::from_ipv4_numeric( dst_ip ) );

        // 通过对应的接口发送数据报
        interface( route.interface_num )->send_datagram( dgram, next_hop_addr );
      }
      // 如果没有匹配的路由，丢弃数据报（不做任何处理）
    }
  }
}
