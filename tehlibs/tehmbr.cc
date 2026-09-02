/*#include <tehmbr.hh>

namespace mbr {

    bool read(table& result) {
        disk::block block;

        if (!disk::read(0, block)) {
            return false;
        }

        // MBR partíciós tábla: offset 446
        for (int i = 0; i < 4; i++) {
            uint8* p = &block.data[446 + i * 16];

            result.partitions[i].boot = p[0];

            result.partitions[i].start_chs[0] = p[1];
            result.partitions[i].start_chs[1] = p[2];
            result.partitions[i].start_chs[2] = p[3];

            result.partitions[i].type = p[4];

            result.partitions[i].end_chs[0] = p[5];
            result.partitions[i].end_chs[1] = p[6];
            result.partitions[i].end_chs[2] = p[7];

            result.partitions[i].start_lba =
                (uint32)p[8] |
                ((uint32)p[9] << 8) |
                ((uint32)p[10] << 16) |
                ((uint32)p[11] << 24);

            result.partitions[i].sector_count =
                (uint32)p[12] |
                ((uint32)p[13] << 8) |
                ((uint32)p[14] << 16) |
                ((uint32)p[15] << 24);
        }

        // MBR signature: 0x55AA
        if (block.data[510] != 0x55 ||
            block.data[511] != 0xAA) {
            return false;
        }

        return true;
    }

}*/