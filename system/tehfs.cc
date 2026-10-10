#include "tehfs.hh"
#pragma region temp
#include <tehio>
#pragma endregion /temp

namespace teh::fs {

    partition partitions[MAX_PARTITIONS];
    uint8 partition_count = 0;


    bool init() {

        partition_count = 0;

        print("FS init indul!\n", szin::vilagos_zold);
        wait(1000);

        print("Disk init elott!\n", szin::vilagos_zold);
        wait(1000);

        if (!disk::init()) {
            print("Disk init sikertelen!\n", szin::voros);
            wait(1000);
            return false;
        }

        print("Disk inicializalva!\n", szin::vilagos_zold);
        wait(1000);

        // 2. MBR beolvasása
        mbr::table mbr_table;

        if (!mbr::read(mbr_table)) {
            return false;
        }
        teh::print("Mbr inicializálva!\n", szin::vilagos_zold);
        wait(1000);

        // 3. MBR partíciók végignézése
        for (uint8 i = 0; i < 4; i++) {

            // Üres partíció
            if (mbr_table.partitions[i].type == 0) {
                continue;
            }

            // Egy TEHFS blokk sem fér bele
            if (mbr_table.partitions[i].sector_count <
                SECTORS_PER_BLOCK) {
                continue;
            }

            // Egyelőre nincs több helyünk
            if (partition_count >= MAX_PARTITIONS) {
                break;
            }

            /*
             * Egy TEHFS blokk 4096 bájt,
             * egy disk blokk 512 bájt.
             *
             * 4096 / 512 = 8
             */

            uint8 buffer[BLOCK_SIZE];

            bool success = true;

            for (uint32 sector = 0;
                sector < SECTORS_PER_BLOCK;
                sector++) {

                disk::block block;

                uint64 lba =
                    (uint64)mbr_table.partitions[i].start_lba
                    + sector;

                if (!disk::read(lba, block)) {
                    success = false;
                    break;
                }

                for (uint32 j = 0;
                    j < disk::blocksize;
                    j++) {

                    buffer[
                        sector * disk::blocksize + j
                    ] = block.data[j];
                }
            }

            if (!success) {
                continue;
            }

            // 4. Superblock értelmezése
            superblock* sb =
                reinterpret_cast<superblock*>(buffer);

            // 5. Magic ellenőrzése
            if (sb->magic != TEHFS_MAGIC) {
                continue;
            }

            // 6. Verzió ellenőrzése
            if (sb->version != TEHFS_VERSION) {
                continue;
            }

            // 7. Blokkméret ellenőrzése
            if (sb->block_size != BLOCK_SIZE) {
                continue;
            }

            // 8. Partíció eltárolása
            partitions[partition_count].start_lba =
                mbr_table.partitions[i].start_lba;

            partitions[partition_count].sector_count =
                mbr_table.partitions[i].sector_count;

            partitions[partition_count].sb = *sb;

            partition_count++;
        }

        return true;
    }

}