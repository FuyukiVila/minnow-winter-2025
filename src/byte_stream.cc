#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( string data )
{
  uint64_t bytes_to_write = min( static_cast<uint64_t>( data.size() ), available_capacity() );
  for ( uint64_t i = 0; i < bytes_to_write; ++i ) {
    buffer_.push_back( data[i] );
  }
  push_count_ += bytes_to_write;
}

void Writer::close()
{
  is_closed_ = true;
}

bool Writer::is_closed() const
{
  return is_closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return push_count_;
}

string_view Reader::peek() const
{
  if ( buffer_.empty() ) {
    return {};
  }
  return string_view( &buffer_.front(), 1 );
}

void Reader::pop( uint64_t len )
{
  uint64_t bytes_to_pop = min( len, static_cast<uint64_t>( buffer_.size() ) );
  for ( uint64_t i = 0; i < bytes_to_pop; ++i ) {
    buffer_.pop_front();
  }
  pop_count_ += bytes_to_pop;
}

bool Reader::is_finished() const
{
  return is_closed_ && buffer_.empty();
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}

uint64_t Reader::bytes_popped() const
{
  return pop_count_;
}
