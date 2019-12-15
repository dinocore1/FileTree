#pragma once

#include <stdint.h>

namespace fs {

typedef uint32_t blockid_t;

typedef int (*read_block)(void* data, blockid_t, void* buf);
typedef int (*erase_block)(void* data, blockid_t);
typedef int (*write_block)(void* data, blockid_t, void* buf);



} // namespace fs