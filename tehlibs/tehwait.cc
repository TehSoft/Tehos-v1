#include "tehos.hh"

// Globális inicializáló: a kernel_init()-ben EGYSZER meg kell hívni a dallam előtt!
void timer_init() {
    // 0-s csatorna, LSB/MSB, Mode 2 (Rate Generator)
    // Beállítjuk a maximális 65535-ös periódusra, így folyamatosan pörög körbe
    cpu::outb(0x43, 0x34); 
    cpu::outb(0x40, 0xFF);
    cpu::outb(0x40, 0xFF);
}

// Biztonságos, hardveres szintű Latch-olvasás
uint16 pit_read() {
    cpu::outb(0x43, 0x00); // Latch parancs a 0-s csatornára
    uint8 low = cpu::inb(0x40);
    uint8 high = cpu::inb(0x40);
    return (high << 8) | low;
}

// Ez a függvény megvárja, amíg a PIT számlálója pontosan 1-et fordul (65535 tick)
void wait_one_overflow() {
    uint16 start = pit_read();
    while (true) {
        uint16 current = pit_read();
        // Mivel a PIT CSÖKKENŐEN számol, ha a jelenlegi érték NAGYOBB, 
        // mint ahol kezdtük, az azt jelenti, hogy átfordult (0 -> 65535)
        if (current > start) {
            break;
        }
        start = current;
    }
}

// A valódi wait függvény, ami milliszekundumot (ms) vár
void wait(uint32 ms) {
    if (ms == 0) return;

    // A PIT maximális periódusa (65535) az alapórajelből adódóan 
    // pontosan ~55 milliszekundumonként fordul át (65535 / 1193180 = 0.0549s)
    // Kiszámoljuk, hányszor kell a PIT-nek teljesen körbeérnie:
    uint32 loops = ms / 55;

    for (uint32 i = 0; i < loops; i++) {
        wait_one_overflow();
    }

    // A maradék időre (ami < 55ms) egy nagyon rövid, kalibrált busy-wait-et használunk,
    // így nem akad el a hardveres regiszterekben a kód
    uint32 remainder_ms = ms % 55;
    for (volatile uint64 i = 0; i < remainder_ms * 400000; i++) {
        __asm__ volatile("nop");
    }
}
