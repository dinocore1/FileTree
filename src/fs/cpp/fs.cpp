#include <fs.h>

namespace fs {



struct inode_t {
    uint32_t mtime; // modified time
    uint32_t size;
    uint16_t pointers[10];
};

struct superblock_t {
    uint32_t version;
    uint32_t block_size;
    uint32_t block_count;
};

int mount(fs_t* fs, config_t* config)
{
    fs->config = config;
}

} // namespace fs