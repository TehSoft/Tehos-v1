/*#include <tehfs.hh>

namespace teh::fs {
    partition partitions[4];
    uint8 partition_count = 0;

    uint8 init() {
        if (!disk::init()) {
            return 0;
        }

        mbr::table mbr_table;

        if (!mbr::read(mbr_table)) {
            return 0;
        }

        for (uint8 i = 0; i < 4; i++) {
            if (mbr_table.partitions[i].type == 0) {
                continue;
            }

            disk::block block;

            if (!disk::read(mbr_table.partitions[i].start_lba, block)) {
                continue;
            }

            superblock* sb =
                reinterpret_cast<superblock*>(block.data);

            if (sb->magic != TEHFS_MAGIC) {
                continue;
            }

            partitions[partition_count].start_lba =
                mbr_table.partitions[i].start_lba;

            partitions[partition_count].sector_count =
                mbr_table.partitions[i].sector_count;

            partitions[partition_count].sb = *sb;

            partition_count++;
        }

        return partition_count;
    }
}*/