#ifndef BILLENTYUZET_HPP
#define BILLENTYUZET_HPP

#include <tehos.hh>

namespace {
    bool shift_aktiv = false;
    bool altgr_aktiv = false;
    // Scancode (Set 1) átalakítása kisbetűs ASCII karakterré
    inline char scancode_to_ascii(unsigned char scancode) {
        switch (scancode) {
        case 0x1E: return 'a'; case 0x30: return 'b';
        case 0x2E: return 'c'; case 0x20: return 'd';
        case 0x12: return 'e'; case 0x21: return 'f';
        case 0x22: return 'g'; case 0x23: return 'h';
        case 0x17: return 'i'; case 0x24: return 'j';
        case 0x25: return 'k'; case 0x26: return 'l';
        case 0x32: return 'm'; case 0x31: return 'n';
        case 0x18: return 'o'; case 0x19: return 'p';
        case 0x10: return 'q'; case 0x13: return 'r';
        case 0x1F: return 's'; case 0x14: return 't';
        case 0x16: return 'u'; case 0x2F: return 'v';
        case 0x11: return 'w'; case 0x2D: return 'x';
        case 0x2C: return 'y'; case 0x15: return 'z';
        case 0x02: return shift_aktiv ? '\'' : altgr_aktiv ? '~' : '1'; case 0x03: return shift_aktiv ? '"' : altgr_aktiv ? 'ˇ' :'2';
        case 0x04: return '3'; case 0x05: return '4';
        case 0x06: return '5'; case 0x07: return '6';
        case 0x08: return shift_aktiv ? '=' : altgr_aktiv ? '`' : '7'; case 0x09: return '8';
        case 0x0A: return '9'; case 0x29: return '0';
        case 0x33: return shift_aktiv ? '?' : altgr_aktiv ? ';' : ',';
        case 0x34: return shift_aktiv ? ':' : '.';
        case 0x35: return shift_aktiv ? '_' : altgr_aktiv ? '*' : '-';
        case 0x39: return ' ';  // Szóköz
        case 0x1C: return '\n'; // Enter
        case 0x0E: return '\b'; // Backspace
        default: return 0;      // Ismeretlen gomb
        }
    }
}
// Polling függvény: 0-t ad vissza, ha nincs gombnyomás, vagy az ASCII kódot, ha van
inline char karakter_olvas() {
    // Ellenőrizzük a PS/2 kontroller állapotregiszterének (0x64) legalsó bitjét
    if (cpu::inb(0x64) & 1) {
        unsigned char scancode = cpu::inb(0x60); // Beolvassuk a leütött gombot

        if(scancode == 0x2A || scancode == 0x36) { // Shift lenyomva
            shift_aktiv = true;
            return 0; // Nem adunk vissza karaktert
        }
        elif(scancode == 0xAA || scancode == 0xB6) { // Shift felengedve
            shift_aktiv = false;
            return 0; // Nem adunk vissza karaktert
        }
        elif(scancode == 0xE0) { // AltGr változása
            altgr_aktiv = !altgr_aktiv;
            return 0; // Nem adunk vissza karaktert
        }
        return scancode_to_ascii(scancode);
    }
    return 0; // Nincs új adat
}


namespace teh {
    inline void input(char(&txt)[128]) {
        int index = 0;
        while (1) {
            char c = karakter_olvas();
            if (c != 0) {
                teh::kurzor_frissit();
                if (c == '\n') {
                    txt[index] = '\0'; // Null terminálás a végén
                    break;
                }
                elif(c == '\b') {
                    if (index > 0) {
                        index--;
                        txt[index] = '\0';
                        teh::backspace();
                    }
                    else teh::backspace(false);
                }
                elif(index < 127) { // Biztonságos határ
                    teh::print(c);
                    txt[index] = c;
                    index++;
                }
            }
        }
    }
}

#endif