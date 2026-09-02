/*#include <tehdisk.hh>
#include <tehos.hh>

namespace disk {
    void ata_string(uint16 data[256], char* buffer, uint32 size, uint32 point) {
        uint32 outi = 0;
        for(uint32 i = point; i < point + size; i++) {
            buffer[outi + 1] = data[i] & 0xFF;
            buffer[outi] = data[i] >> 8;
            outi += 2;
        }
        buffer[outi] = '\0';
    }

    constexpr uint16 ATA_PRIMARY = 0x1F0;
    constexpr uint16 ATA_PRIMARY_CTRL = 0x3F6;
    /*base + 0 → DATA
    base + 1 → ERROR / FEATURES
    base + 2 → SECTOR COUNT
    base + 3 → LBA LOW
    base + 4 → LBA MID
    base + 5 → LBA HIGH
    base + 6 → DRIVE / LBA
    base + 7 → STATUS / COMMAND
    *//*
    bool initialized = false;
    device_info device;
    uint16 initdata[256];
    bool init() {
        cpu::outb(ATA_PRIMARY + 6, 0xA0);
        cpu::outb(ATA_PRIMARY + 2, 0);
        cpu::outb(ATA_PRIMARY + 3, 0);
        cpu::outb(ATA_PRIMARY + 4, 0);
        cpu::outb(ATA_PRIMARY + 5, 0);
        cpu::outb(ATA_PRIMARY + 7, 0xEC);
        uint8 status;
        do {status = cpu::inb(ATA_PRIMARY + 7);
        }
        while(status & 0b10000000);
        if (status & 0b00000001) {
            return false;
        }

        if (!(status & 0b00001000)) {
            return false;
        }
        for(int i = 0; i < 256; i++) {
            initdata[i] = cpu::inw(ATA_PRIMARY);
        }
        if (!(initdata[49] & 0b0000001000000000)) {
            return false;
        }
        if (!(initdata[83] & 0b0000010000000000)) {
            device.lba48 = false;
            return false;
        }
        else device.lba48 = true;
        ata_string(initdata, device.model, 20, 27);
        ata_string(initdata, device.serial, 10, 10);
        ata_string(initdata, device.firmware, 4, 23);
        device.sector_count = ((uint64)initdata[103] << 48) | ((uint64)initdata[102] << 32) | ((uint64)initdata[101] << 16) | ((uint64)initdata[100]);
        initialized = true;
        device.present = true;
        return true;
    }
    #pragma region unsafe
    bool read(uint64 offset, block& buffer) {
        if(offset >= device.sector_count) {
            return false;
        }
        if (!initialized) {
            return false;
        }

        cpu::outb(ATA_PRIMARY + 6, 0xE0);

        cpu::outb(ATA_PRIMARY + 2, 0);
        cpu::outb(ATA_PRIMARY + 3, offset >> 24);
        cpu::outb(ATA_PRIMARY + 4, offset >> 32);
        cpu::outb(ATA_PRIMARY + 5, offset >> 40);

        cpu::outb(ATA_PRIMARY + 2, 1);
        cpu::outb(ATA_PRIMARY + 3, offset);
        cpu::outb(ATA_PRIMARY + 4, offset >> 8);
        cpu::outb(ATA_PRIMARY + 5, offset >> 16);

        cpu::outb(ATA_PRIMARY + 7, 0x24);

        uint8 status;
        do{
            status = cpu::inb(ATA_PRIMARY + 7);
        }
        while (status & 0b10000000);

        if(status & 0b00000001) {
            return false;
        }

        if(!(status & 0b00001000)) {
            return false;
        }

        for(int i = 0; i < blocksize; i += 2) {
            uint16 tempdata = cpu::inw(ATA_PRIMARY);
            buffer.data[i] = tempdata & 0xFF;
            buffer.data[i+1] = tempdata >> 8;
        }
        return true;
    }

    bool write(uint64 offset, const block& buffer) {
        if(offset >= device.sector_count) {
            return false;
        }
        if (!initialized) {
            return false;
        }

        cpu::outb(ATA_PRIMARY + 6, 0xE0);

        cpu::outb(ATA_PRIMARY + 2, 0);
        cpu::outb(ATA_PRIMARY + 3, offset >> 24);
        cpu::outb(ATA_PRIMARY + 4, offset >> 32);
        cpu::outb(ATA_PRIMARY + 5, offset >> 40);

        cpu::outb(ATA_PRIMARY + 2, 1);
        cpu::outb(ATA_PRIMARY + 3, offset);
        cpu::outb(ATA_PRIMARY + 4, offset >> 8);
        cpu::outb(ATA_PRIMARY + 5, offset >> 16);

        cpu::outb(ATA_PRIMARY + 7, 0x34);

        uint8 status;
        do{
            status = cpu::inb(ATA_PRIMARY + 7);
        }
        while (status & 0b10000000);

        if(status & 0b00000001) {
            return false;
        }

        if(!(status & 0b00001000)) {
            return false;
        }

        for(int i = 0; i < blocksize; i += 2) {
            cpu::outw(ATA_PRIMARY, buffer.data[i] | ((uint16)buffer.data[i+1] << 8));
        }

        do{
            status = cpu::inb(ATA_PRIMARY + 7);
        }
        while (status & 0b10000000);

        if(status & 0b00000001) {
            return false;
        }

        return true;
    }
    #pragma endregion
}*/