#ifndef TEHFS_HH
#define TEHFS_HH

#include <tehmain>
#include <tehdisk.hh>
#include <tehmbr.hh>

namespace teh::fs {

    constexpr uint32 BLOCK_SIZE = 4096;

    constexpr uint32 SECTORS_PER_BLOCK =
        BLOCK_SIZE / disk::blocksize;

    constexpr uint32 TEHFS_MAGIC = 0x54454846;
    constexpr uint32 TEHFS_VERSION = 1;

    struct __attribute__((packed)) superblock {
        uint32 magic;
        uint32 version;
        uint32 block_size;
        uint32 block_count;

        uint32 bitmap_start;
        uint32 bitmap_blocks;

        uint32 inode_bitmap_start;
        uint32 inode_bitmap_blocks;

        uint32 inode_start;
        uint32 inode_count;

        uint32 data_start;

        uint32 root_inode;
    };

    struct __attribute__((packed)) partition {
        uint32 start_lba;
        uint32 sector_count;
        superblock sb;
    };

    constexpr uint32 MAX_PARTITIONS = 4;

    extern partition partitions[MAX_PARTITIONS];
    extern uint8 partition_count;

    bool init();

}

#endif // TEHFS_HH