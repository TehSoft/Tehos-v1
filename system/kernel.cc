#include <tehos.hh>
#include <tehio.hh>
#include <tehconsole.hh>
#include <tehdisk.hh>
#include <tehsound.hh>

extern "C" {
    void main(void);
    int __cxa_guard_acquire(long long* g) { return !*g; }
    void __cxa_guard_release(long long* g) { *g = 1; }
}

teh::sound play[8] = {
    { 330, 250 },
    { 294, 250 },
    { 392, 250 },
    { 349, 250 },
    { 494, 250 },
    { 440, 250 },
    { 523, 250 },
    { 494, 250 }
};

void loading_screen() {
    teh::clear();
    teh::setcolor(szin::voros);
    teh::set_cursor(35, 7);
    teh::print("\xb1\xb1      \xb1\xb1");
    teh::set_cursor(35, 8);
    teh::print("\xb1\xb1      \xb1\xb1");
    teh::set_cursor(35, 9);
    teh::print("\xb1\xb1      \xb1\xb1");
    teh::set_cursor(35, 10);
    teh::print("\xb1\xb1      \xb1\xb1");
    teh::set_cursor(35, 11);
    teh::print("\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1");
    teh::set_cursor(35, 12);
    teh::print("\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1\xb1");
    teh::set_cursor(35, 13);
    teh::print("  \xb1\xb1\xb1\xb1\xb1\xb1  ");
    teh::set_cursor(35, 14);
    teh::print("  \xb1\xb1\xb1\xb1\xb1\xb1  ");
    teh::set_cursor(35, 15);
    teh::print("    \xb1\xb1    ");
    teh::set_cursor(35, 16);
    teh::print("    \xb1\xb1    ");
        for (int i = 0; i < 8; i++) {
        teh::playsound(play[i]);
    }
    teh::clear();
    teh::setcolor(szin::feher);
    teh::set_cursor(46, 18);
    teh::print(']');
    teh::set_cursor(34, 18);
    teh::print('[');

    for(uint8 i = 0; i < 10; i++) {
        teh::print((char)0xDB);
        wait(100);
    }
}

void kernel_init() {
    timer_init();
    loading_screen();
    teh::screen_init();
    /*if(!disk::init()) {
        print("Disk initialization failed!", szin::voros);
        while(1);
    }*/
    teh::setcolor(szin::sarga);
}

void main(void) {
    kernel_init();
    char txt[128];
    while (1) {
        teh::print(">", szin::vilagos_szurke);
        teh::input(txt);
        teh::endl();
        system(txt);
    }
}
