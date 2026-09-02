#ifndef KEPERNYO_HPP
#define KEPERNYO_HPP

#include <tehos.hh>

namespace teh {
    namespace {
        // 64 bites környezetben a volatile char* mutató már 8 bájton tárolódik
        volatile char* video_memoria = (volatile char*)0xB8000;
        int x = 0;
        int y = 0;
        szin alap_szin = szin::feher;
    };

    //alap kezelés
    inline void kurzor_frissit() {
        for (int i = 0; i < 80 * 25 * 2; i += 2) {
            if (video_memoria[i] == '_')video_memoria[i] = ' ';
        }
        unsigned short pozicio = y * 80 + x;
        video_memoria[pozicio * 2] = '_';
        video_memoria[pozicio * 2 + 1] = char(alap_szin);
    }


    inline void clear() {
        for (int i = 0; i < 80 * 25 * 2; i += 2) {
            video_memoria[i] = ' ';
            video_memoria[i + 1] = char(alap_szin);
        }
        x = 0; y = 0;
        kurzor_frissit();
    }

    inline void scroll() {
        for (int i = 0; i < 24 * 80 * 2; i++) {
            video_memoria[i] = video_memoria[i + 80 * 2];
        }
        for (int i = 24 * 80 * 2; i < 25 * 80 * 2; i += 2) {
            video_memoria[i] = ' ';
            video_memoria[i + 1] = char(alap_szin);
        }
        y = 24;
    }

    inline void endl() {
        x = 0;
        y++;
        if (y >= 25) {
            scroll();
        }
        kurzor_frissit();
    }

    inline void setcolor(szin SZIN) {
        alap_szin = SZIN;
        kurzor_frissit();
    }

    inline void backspace(bool leptetes = true) {
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
        kurzor_frissit();
    }


    //valami kiírása a képernyőre
    inline void print(char betu, szin SZIN = szin::alap) { // az összes kiírás alapja
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

        int index = (y * 80 + x) * 2;
        video_memoria[index] = betu;
        video_memoria[index + 1] = char(SZIN);
        x++;
        if (x >= 80) { endl(); }
        kurzor_frissit();
    }

    inline void print(const char* szoveg, szin SZIN = szin::alap) {
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }

        for (int i = 0; szoveg[i] != '\0'; i++) {
            print(szoveg[i], SZIN);
        }
    }

    inline void char_fill(char betu, szin SZIN = szin::alap) {
        if (SZIN == szin::alap) {
            SZIN = alap_szin;
        }
        int nowy = y;
        while (nowy == y) {
            print(betu, SZIN);
        }
    }

    inline void print(int64 szam, szin SZIN = szin::alap) {
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
};

#endif
