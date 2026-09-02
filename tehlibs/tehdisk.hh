/*#ifndef TEHDISK_HPP
#define TEHDISK_HPP

#include <tehos.hh>

namespace disk {
    struct device_info {
        bool present;
        bool lba48;

        uint64 sector_count;
        char serial[21];
        char firmware[9];
        char model[41];
    };
    extern uint16 initdata[256];
    extern device_info device;
    constexpr uint32 blocksize = 512;
    struct block {
        uint8 data[blocksize];
    };
    void ata_string(uint16 data[256], char* buffer, uint32 size, uint32 point);
    bool init();
    bool read(uint64 offset, block& buffer);
    bool write(uint64 offset, const block& buffer);
}

#endif*/