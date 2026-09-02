/*#ifndef TEHFS_HPP
#define TEHFS_HPP

#include <tehos.hh>
#include <tehdisk.hh>
#include <tehmbr.hh>

struct partition {
    uint32 start_lba;
    uint32 sector_count;
    superblock sb;
};

struct __attribute__((packed)) superblock {
    uint32 magic;
    uint32 version;
    uint32 firstfree;
    uint32 blocksize;
};

constexpr uint32 TEHFS_MAGIC = 0x54454846;
constexpr uint32 sbsize = sizeof(superblock);

enum class filetype : uint8 {
    unused,
    unknown,
    text,
    uint64num,
    int64num,
    commandscript,
    tehlang,            //todo olyan tehlang, amit lehet szerkeszteni
    runable_tehlang     //todo olyan tehlang, amit már nem lehet szerkeszteni, csak futtatni
};

struct __attribute__((packed)) fileheader {
    filetype type;
    uint32 size;
    char name[64];
};

constexpr uint32 header_size = sizeof(fileheader);

namespace teh::fs {
    //todo nincs még kész
    uint8 init();
    bool write();
    bool read();
}
#endif*/