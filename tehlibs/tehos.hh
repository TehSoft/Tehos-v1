#ifndef TEHOS_HPP
#define TEHOS_HPP

#define elif else if

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

using int8 = signed char;
using int16 = signed short;
using int32 = signed int;
using int64 = signed long long;


enum class boolean : uint8 {
    false_val,
    true_val
};

enum class szin : char {
    fekete = 0x00,
    kek = 0x01,
    zold = 0x02,
    cian = 0x03,
    voros = 0x04,
    lila = 0x05,
    barna = 0x06,
    vilagos_szurke = 0x07,
    sotet_szurke = 0x08,
    vilagos_kek = 0x09,
    vilagos_zold = 0x0A,
    vilagos_cian = 0x0B,
    vilagos_piros = 0x0C,
    vilagos_lila = 0x0D,
    sarga = 0x0E,
    feher = 0x0F,
    alap = 0x10
};

namespace cpu {
    inline void outb(uint16 port, uint8 adat) {
        asm volatile("outb %0, %1" : : "a"(adat), "Nd"(port) : "memory");
    }
    inline uint8 inb(uint16 port) {
        uint8 adat;
        asm volatile("inb %1, %0" : "=a"(adat) : "Nd"(port) : "memory");
        return adat;
    }

    inline void outw(uint16 port, uint16 adat) {
        asm volatile("outw %0, %1" : : "a"(adat), "Nd"(port) : "memory");
    }
    inline uint16 inw(uint16 port) {
        uint16 adat;
        asm volatile("inw %1, %0" : "=a"(adat) : "Nd"(port) : "memory");
        return adat;
    }

    inline void outd(uint16 port, uint32 adat) {
        asm volatile("outl %0, %1" : : "a"(adat), "Nd"(port) : "memory");
    }
    inline uint32 ind(uint16 port) {
        uint32 adat;
        asm volatile("inl %1, %0" : "=a"(adat) : "Nd"(port) : "memory");
        return adat;
    }
}

void wait(uint32 ms);
void timer_init();

char* trim_string(char* str);
bool strcmp(const char* a, const char* b, bool size_eq = true);

#endif