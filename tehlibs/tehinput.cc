#include "tehio"

namespace teh {
    bool shift_aktiv = false;
    bool altgr_aktiv = false;
    char scancode_to_ascii(unsigned char scancode) {
        switch (scancode) {
            //nemlétező karakter = 0
        case 0x1E: return shift_aktiv ? 'A' : altgr_aktiv ? 0 : 'a';   case 0x30: return shift_aktiv ? 'B' : altgr_aktiv ? '{' : 'b';
        case 0x2E: return shift_aktiv ? 'C' : altgr_aktiv ? '&' : 'c'; case 0x20: return shift_aktiv ? 'D' : altgr_aktiv ? 0 : 'd';
        case 0x12: return shift_aktiv ? 'E' : altgr_aktiv ? 0 : 'e';   case 0x21: return shift_aktiv ? 'F' : altgr_aktiv ? '[' : 'f';
        case 0x22: return shift_aktiv ? 'G' : altgr_aktiv ? ']' : 'g'; case 0x23: return shift_aktiv ? 'H' : altgr_aktiv ? 0 : 'h';
        case 0x17: return shift_aktiv ? 'I' : altgr_aktiv ? 0 : 'i';   case 0x24: return shift_aktiv ? 'J' : altgr_aktiv ? 0 : 'j';
        case 0x25: return shift_aktiv ? 'K' : altgr_aktiv ? 0 : 'k';   case 0x26: return shift_aktiv ? 'L' : altgr_aktiv ? 0 : 'l';
        case 0x32: return shift_aktiv ? 'M' : altgr_aktiv ? 0 : 'm';   case 0x31: return shift_aktiv ? 'N' : altgr_aktiv ? '}' : 'n';
        case 0x18: return shift_aktiv ? 'O' : altgr_aktiv ? 0 : 'o';   case 0x19: return shift_aktiv ? 'P' : altgr_aktiv ? 0 : 'p';
        case 0x10: return shift_aktiv ? 'Q' : altgr_aktiv ? '\\' : 'q';case 0x13: return shift_aktiv ? 'R' : altgr_aktiv ? 0 : 'r';
        case 0x1F: return shift_aktiv ? 'S' : altgr_aktiv ? 0 : 's';   case 0x14: return shift_aktiv ? 'T' : altgr_aktiv ? 0 : 't';
        case 0x16: return shift_aktiv ? 'U' : altgr_aktiv ? 0 : 'u';   case 0x2F: return shift_aktiv ? 'V' : altgr_aktiv ? '@' : 'v';
        case 0x11: return shift_aktiv ? 'W' : altgr_aktiv ? 0 : 'w';   case 0x2D: return shift_aktiv ? 'X' : altgr_aktiv ? '#' : 'x';
        case 0x2C: return shift_aktiv ? 'Y' : altgr_aktiv ? '>' : 'y'; case 0x15: return shift_aktiv ? 'Z' : altgr_aktiv ? 0 : 'z';

        case 0x0B: return shift_aktiv ? 153 : altgr_aktiv ? 0 : 148;   case 0x0C: return shift_aktiv ? 154 : altgr_aktiv ? 0 : 129;
        case 0x0D: return shift_aktiv ? 0 : altgr_aktiv ? 0 : 162;     case 0x1A: return shift_aktiv ? 0 : altgr_aktiv ? '/' : 0;
        case 0x1B: return shift_aktiv ? 0 : altgr_aktiv ? 0 : 163;     case 0x27: return shift_aktiv ? 144 : altgr_aktiv ? '$' : 130;
        case 0x28: return shift_aktiv ? 0 : altgr_aktiv ? 0 : 160;     case 0x2B: return shift_aktiv ? 0 : altgr_aktiv ? '>' : 0;

        case 0x02: return shift_aktiv ? '\'' : altgr_aktiv ? '~' : '1';case 0x03: return shift_aktiv ? '"' : altgr_aktiv ? 0 : '2';
        case 0x04: return shift_aktiv ? '+' : altgr_aktiv ? 0 : '3';   case 0x05: return shift_aktiv ? '!' : altgr_aktiv ? 0 : '4';
        case 0x06: return shift_aktiv ? '%' : altgr_aktiv ? 0 : '5';   case 0x07: return shift_aktiv ? '/' : altgr_aktiv ? 0 : '6';
        case 0x08: return shift_aktiv ? '=' : altgr_aktiv ? '`' : '7'; case 0x09: return shift_aktiv ? '(' : altgr_aktiv ? 0 : '8';
        case 0x0A: return shift_aktiv ? ')' : altgr_aktiv ? 0 : '9';   case 0x29: return shift_aktiv ? 0 : altgr_aktiv ? 0 : '0';

        case 0x33: return shift_aktiv ? '?' : altgr_aktiv ? ';' : ',';
        case 0x34: return shift_aktiv ? ':' : '.'; 
        case 0x35: return shift_aktiv ? '_' : altgr_aktiv ? '*' : '-';
        case 0x39: return ' ';  // Szóköz
        case 0x1C: return '\n'; // Enter
        case 0x0E: return '\b'; // Backspace
        default: return 0;      // Ismeretlen gomb
        }
    }

    // Polling függvény: 0-t ad vissza, ha nincs gombnyomás, vagy az ASCII kódot, ha van
    char karakter_olvas() {
        // Ellenőrizzük a PS/2 kontroller állapotregiszterének (0x64) legalsó bitjét
        if (cpu::inb(0x64) & 1) {
            unsigned char scancode = cpu::inb(0x60); // Beolvassuk a leütött gombot

            if (scancode == 0x2A || scancode == 0x36) { // Shift lenyomva
                teh::shift_aktiv = true;
                return 0; // Nem adunk vissza karaktert
            }
            else if (scancode == 0xAA || scancode == 0xB6) { // Shift felengedve
                teh::shift_aktiv = false;
                return 0; // Nem adunk vissza karaktert
            }
            else if (scancode == 0xE0) { // AltGr változása
                teh::altgr_aktiv = !teh::altgr_aktiv;
                return 0; // Nem adunk vissza karaktert
            }
            return teh::scancode_to_ascii(scancode);
        }
        return 0; // Nincs új adat
    }


    void input(char(&txt)[128]) {
        int index = 0;
        while (1) {
            char c = karakter_olvas();
            if (c != 0) {
                teh::cursor_refresh();
                if (c == '\n') {
                    txt[index] = '\0'; // Null terminálás a végén
                    break;
                }
                else if (c == '\b') {
                    if (index > 0) {
                        index--;
                        txt[index] = '\0';
                        teh::backspace();
                    }
                    else teh::backspace(false);
                }
                else if (index < 127) { // Biztonságos határ
                    teh::print(c);
                    txt[index] = c;
                    index++;
                }
            }
        }
    }
}