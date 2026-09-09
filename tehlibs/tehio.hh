#ifndef TEHIO_HH
#define TEHIO_HH
#include <tehos.hh>

namespace teh {
    void cursor_refresh();
    void set_cursor(int nx, int ny);
    void clear();
    void scroll();
    void endl();
    void setcolor(szin SZIN);
    void backspace(bool leptetes = true);
    void print(char betu, szin SZIN = szin::alap);
    void print(const char* szoveg, szin SZIN = szin::alap);
    void char_fill(char betu, szin SZIN = szin::alap);
    void print(int64 szam, szin SZIN = szin::alap);
    void screen_init();
    char scancode_to_ascii(unsigned char scancode);
    char karakter_olvas();
    void input(char(&txt)[128]);
}

#endif //TEHIO_HH