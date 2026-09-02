/*#ifndef MBR_HPP
#define MBR_HPP

#include <tehdisk.hh>

namespace mbr {
    struct partition {
        uint8 boot;
        uint8 start_chs[3];
        uint8 type;
        uint8 end_chs[3];
        uint32 start_lba;
        uint32 sector_count;
    };

    struct table {
        partition partitions[4];
    };

    bool read(table& result);
}

#endif*/