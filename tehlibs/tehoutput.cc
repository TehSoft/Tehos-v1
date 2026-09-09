#include "tehio.hh"

namespace teh {
    volatile char* video_memoria = (volatile char*)0xB8000;
    int x = 0;
    int y = 0;
    szin alap_szin = szin::feher;

    //alap kezelés
    void cursor_refresh() {
        uint16 pozicio = y * 80 + x;
        cpu::outb(0x3D4, 0x0F);
        cpu::outb(0x3D5, (uint8)(pozicio & 0xFF));
        cpu::outb(0x3D4, 0x0E);
        cpu::outb(0x3D5, (uint8)((pozicio >> 8) & 0xFF));
    }

    void set_cursor(int nx, int ny) {
        x = nx;
        y = ny;
        cursor_refresh();
    }

    void clear() {
        for (int i = 0; i < 80 * 25 * 2; i += 2) {
            video_memoria[i] = ' ';
            video_memoria[i + 1] = char(alap_szin);
        }
        x = 0; y = 0;
        cursor_refresh();
    }

    void scroll() {
        for (int i = 0; i < 24 * 80 * 2; i++) {
            video_memoria[i] = video_memoria[i + 80 * 2];
        }
        for (int i = 24 * 80 * 2; i < 25 * 80 * 2; i += 2) {
            video_memoria[i] = ' ';
            video_memoria[i + 1] = char(alap_szin);
        }
        y = 24;
    }

    void endl() {
        x = 0;
        y++;
        if (y >= 25) {
            scroll();
        }
        cursor_refresh();
    }

    void setcolor(szin SZIN) {
        alap_szin = SZIN;
        cursor_refresh();
    }

    void backspace(bool leptetes) {
        if (leptetes) {
            if (x > 0) {
                x--;
            }
            elif(y > 0) {
                y--;
                x = 79;
            }
            else {
                return;
            }
        }
        unsigned short pozicio = y * 80 + x;
        video_memoria[pozicio * 2] = ' ';
        video_memoria[pozicio * 2 + 1] = char(alap_szin);
        cursor_refresh();
    }


    //valami kiírása a képernyőre
    void print(char betu, szin SZIN) { // az összes kiírás alapja
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }
        if (betu == '\n') {
            endl();
            return;
        }
        elif(betu == '\b') {
            backspace();
            return;
        }
        elif(betu == '\t') {
            for (int i = 0; i < 4; i++) {
                print(' ', SZIN);
            }
            return;
        }
        int index = (y * 80 + x) * 2;
        video_memoria[index] = betu;
        video_memoria[index + 1] = char(SZIN);
        x++;
        if (x >= 80) { endl(); }
        cursor_refresh();
    }

    void print(const char* szoveg, szin SZIN ) {
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }

        for (int i = 0; szoveg[i] != '\0'; i++) {
            print(szoveg[i], SZIN);
        }
    }

    void char_fill(char betu, szin SZIN) {
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }
        int nowy = y;
        while (nowy == y) {
            print(betu, SZIN);
        }
    }

    void print(int64 szam, szin SZIN) {
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }

        if (szam < 0) {
            szam = -szam;
            print('-', SZIN);
        }
        int hossz = 0;
        if (szam == 0) {
            hossz = 1;
        }
        else {
            int ideiglenes = szam;
            while (ideiglenes > 0) {
                ideiglenes /= 10;
                hossz++;
            }
        }

        int szamjegyek[hossz];
        for (int i = 0; i < hossz; i++) {
            szamjegyek[i] = szam % 10;
            szam /= 10;
        }
        for (int i = hossz - 1; i >= 0; i--) {
            print((char)('0' + szamjegyek[i]), SZIN);
        }
    }

    void screen_init() {
        cpu::outb(0x3D4, 0x0A);
        uint8 val_0A = cpu::inb(0x3D5);
        cpu::outb(0x3D5, (val_0A & 0xC0) | 13);

        cpu::outb(0x3D4, 0x0B);
        uint8 val_0B = cpu::inb(0x3D5);
        cpu::outb(0x3D5, (val_0B & 0xE0) | 15);

        teh::clear();
        teh::char_fill('=', szin::vilagos_cian);
        teh::print("                           TEHOS operacios rendszer                            \n", szin::vilagos_zold);
        teh::char_fill('=', szin::vilagos_cian);
        teh::endl();
    }

};
