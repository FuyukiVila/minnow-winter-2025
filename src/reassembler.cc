#include "reassembler.hh"
#include "debug.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // 如果数据为空，只需要处理 EOF 标志
  if ( data.empty() ) {
    if ( is_last_substring ) {
      eof_received_ = true;
      if ( buffer_.empty() ) {
        output_.writer().close();
      }
    }
    return;
  }

  // 获取 Writer 的引用
  auto& writer = output_.writer();

  // 计算可接受的最大索引
  uint64_t max_acceptable_index = next_index_ + writer.available_capacity();

  // 如果数据完全在已写入的范围之前，直接忽略
  if ( first_index + data.size() <= next_index_ ) {
    if ( is_last_substring ) {
      eof_received_ = true;
      if ( buffer_.empty() ) {
        writer.close();
      }
    }
    return;
  }

  // 裁剪数据：移除已经写入的部分
  if ( first_index < next_index_ ) {
    data = data.substr( next_index_ - first_index );
    first_index = next_index_;
  }

  // 裁剪数据：移除超出容量的部分
  if ( first_index >= max_acceptable_index ) {
    return; // 完全超出容量，不设置 EOF（因为最后的字节被丢弃了）
  }

  if ( first_index + data.size() > max_acceptable_index ) {
    data = data.substr( 0, max_acceptable_index - first_index );
    is_last_substring = false;
  }

  if ( is_last_substring ) {
    eof_received_ = true;
  }

  // 统一处理：先将数据插入/合并到缓冲区（如果有间隙）或直接准备写入
  // 检查是否与现有缓存重叠或相邻
  auto it = buffer_.lower_bound( first_index );

  // 向前检查，看是否有重叠或相邻
  if ( it != buffer_.begin() ) {
    auto prev_it = prev( it );
    uint64_t prev_end = prev_it->first + prev_it->second.size();

    // 如果新数据与前一个片段重叠或相邻
    if ( prev_end >= first_index ) {
      // 合并数据
      if ( first_index + data.size() > prev_end ) {
        // 新数据有扩展部分
        uint64_t overlap = prev_end - first_index;
        prev_it->second += data.substr( overlap );
      }
      first_index = prev_it->first;
      data = prev_it->second;
      buffer_.erase( prev_it );
      it = buffer_.lower_bound( first_index );
    }
  }

  // 向后检查，合并所有被新数据覆盖或相邻的片段
  while ( it != buffer_.end() && it->first <= first_index + data.size() ) {
    uint64_t it_end = it->first + it->second.size();
    uint64_t data_end = first_index + data.size();

    if ( it_end > data_end ) {
      // 后续片段有扩展部分
      data += it->second.substr( data_end - it->first );
    }

    it = buffer_.erase( it );
  }

  // 如果数据可以立即写入（从 next_index_ 开始），则写入；否则缓存
  if ( first_index == next_index_ ) {
    // 可以立即写入
    writer.push( data );
    next_index_ += data.size();

    // 尝试从缓冲区写入后续的连续数据
    while ( !buffer_.empty() && buffer_.begin()->first == next_index_ ) {
      auto buf_it = buffer_.begin();
      writer.push( buf_it->second );
      next_index_ += buf_it->second.size();
      buffer_.erase( buf_it );
    }

    // 检查是否需要关闭流
    if ( eof_received_ && buffer_.empty() ) {
      writer.close();
    }
  } else {
    // 还有间隙，需要缓存
    buffer_[first_index] = data;
  }
}

// How many bytes are stored in the Reassembler itself?
// This function is for testing only; don't add extra state to support it.
uint64_t Reassembler::count_bytes_pending() const
{
  uint64_t count = 0;
  for ( const auto& segment : buffer_ ) {
    count += segment.second.size();
  }
  return count;
}
