#pragma once

#include <stdint.h>

namespace fs {

typedef uint32_t blockid_t;

enum error {
    ERR_OK          = 0,    // No error
    ERR_IO          = -5,   // Error during device operation
    ERR_CORRUPT     = -84,  // Corrupted
    ERR_NOENT       = -2,   // No directory entry
    ERR_EXIST       = -17,  // Entry already exists
    ERR_NOTDIR      = -20,  // Entry is not a dir
    ERR_ISDIR       = -21,  // Entry is a dir
    ERR_NOTEMPTY    = -39,  // Dir is not empty
    ERR_BADF        = -9,   // Bad file number
    ERR_FBIG        = -27,  // File too large
    ERR_INVAL       = -22,  // Invalid parameter
    ERR_NOSPC       = -28,  // No space left on device
    ERR_NOMEM       = -12,  // No more memory available
    ERR_NOATTR      = -61,  // No data/attr available
    ERR_NAMETOOLONG = -36,  // File name too long
};

// File types
enum type {
    // file types
    TYPE_REG            = 0x001,
    TYPE_DIR            = 0x002,

    // internally used types
    LFS_TYPE_SPLICE         = 0x400,
    LFS_TYPE_NAME           = 0x000,
    LFS_TYPE_STRUCT         = 0x200,
    LFS_TYPE_USERATTR       = 0x300,
    LFS_TYPE_FROM           = 0x100,
    LFS_TYPE_TAIL           = 0x600,
    LFS_TYPE_GLOBALS        = 0x700,
    LFS_TYPE_CRC            = 0x500,

    // internally used type specializations
    LFS_TYPE_CREATE         = 0x401,
    LFS_TYPE_DELETE         = 0x4ff,
    LFS_TYPE_SUPERBLOCK     = 0x0ff,
    LFS_TYPE_DIRSTRUCT      = 0x200,
    LFS_TYPE_CTZSTRUCT      = 0x202,
    LFS_TYPE_INLINESTRUCT   = 0x201,
    LFS_TYPE_SOFTTAIL       = 0x600,
    LFS_TYPE_HARDTAIL       = 0x601,
    LFS_TYPE_MOVESTATE      = 0x7ff,

    // internal chip sources
    LFS_FROM_NOOP           = 0x000,
    LFS_FROM_MOVE           = 0x101,
    LFS_FROM_USERATTRS      = 0x102,
};

// File open flags
enum open_flags {
    // open flags
    O_RDONLY = 1,         // Open a file as read only
    O_WRONLY = 2,         // Open a file as write only
    O_RDWR   = 3,         // Open a file as read and write
    O_CREAT  = 0x0100,    // Create a file if it does not exist
    O_EXCL   = 0x0200,    // Fail if a file already exists
    O_TRUNC  = 0x0400,    // Truncate the existing file to zero size
    O_APPEND = 0x0800,    // Move to end of file on every write

    // internally used flags
    LFS_F_DIRTY   = 0x010000, // File does not match storage
    LFS_F_WRITING = 0x020000, // File has been written since last flush
    LFS_F_READING = 0x040000, // File has been read since last flush
    LFS_F_ERRED   = 0x080000, // An error occured during write
    LFS_F_INLINE  = 0x100000, // Currently inlined in directory entry
    LFS_F_OPENED  = 0x200000, // File has been opened
};

// File seek flags
enum whence_flags {
    SEEK_SET = 0,   // Seek relative to an absolute position
    SEEK_CUR = 1,   // Seek relative to the current file position
    SEEK_END = 2,   // Seek relative to the end of the file
};

typedef int (*read_block)(void* data, blockid_t, void* buf);
typedef int (*erase_block)(void* data, blockid_t);
typedef int (*write_block)(void* data, blockid_t, void* buf);

struct config_t {
    uint32_t block_size;
    uint32_t block_count;
    void* low_level_data; // passed to the low-level read/erase/write block functions
    read_block read;
    erase_block erase;
    write_block write;
};

struct fs_t {
    config_t* config;
};

struct file_t {

};

int mount(fs_t*, config_t*);
int umount(fs_t*);
int format(fs_t*, config_t*);
int fopen(fs_t*, file_t*, const char* filename, int flags);
int fread(file_t*, void* buf, uint32_t len);
int fclose(file_t*);
int rewind(file_t*);
int fwrite(file_t*, void* buf, uint32_t len);




} // namespace fs