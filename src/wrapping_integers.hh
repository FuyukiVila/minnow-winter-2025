#pragma once

#include <cstdint>

/*
 * The Wrap32 type represents a 32-bit unsigned integer that:
 *    - starts at an arbitrary "zero point" (initial value), and
 *    - wraps back to zero when it reaches 2^32 - 1.
 */

class Wrap32
{
public:
  explicit Wrap32( uint32_t raw_value ) : raw_value_( raw_value ) {}

  /* Construct a Wrap32 given an absolute sequence number n and the zero point. */
  static Wrap32 wrap( uint64_t n, Wrap32 zero_point );

  /*
   * unwrap 方法返回一个绝对序列号：在给定零点（zero point）时，该绝对序列号会映射到此 Wrap32，
   * 并使用一个“检查点”（checkpoint）：另一个接近期望结果的绝对序列号。
   *
   * 可能存在多个绝对序列号映射到同一个 Wrap32。
   * unwrap 方法应返回与检查点最接近的那个绝对序列号。
   */
  uint64_t unwrap( Wrap32 zero_point, uint64_t checkpoint ) const;

  Wrap32 operator+( uint32_t n ) const { return Wrap32 { raw_value_ + n }; }
  bool operator==( const Wrap32& other ) const { return raw_value_ == other.raw_value_; }

protected:
  uint32_t raw_value_ {};
};
