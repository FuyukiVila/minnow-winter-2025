#include "wrapping_integers.hh"
#include "debug.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  return zero_point + static_cast<uint32_t>( n );
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  auto checkpoint_wrapped = wrap( checkpoint, zero_point );
  uint32_t diff = raw_value_ - checkpoint_wrapped.raw_value_;
  if ( diff <= ( 1ull << 31 ) || checkpoint + diff < ( 1ull << 32 ) ) {
    return checkpoint + diff;
  } else {
    return checkpoint + diff - ( 1ull << 32 );
  }
}
