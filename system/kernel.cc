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
    teh::set_cursor(46, 18);
    teh::print(']');
    teh::set_cursor(34, 18);
    teh::print('[');

    for(uint8 i = 0; i < 10; i++) {
        teh::print('#');
        wait(100);
    }

    /*teh::setcolor(szin::vilagos_piros);
    teh::set_cursor(35, 7);
    teh::print("██      ██");
    teh::set_cursor(36, 7);
    teh::print("██      ██");
    teh::set_cursor(37, 7);
    teh::print("██      ██");
    teh::set_cursor(38, 7);
    teh::print("██      ██");
    teh::set_cursor(39, 7);
    teh::print("██████████");
    teh::set_cursor(40, 7);
    teh::print("██████████");
    teh::set_cursor(41, 7);
    teh::print("  ██████  ");
    teh::set_cursor(42, 7);
    teh::print("  ██████  ");
    teh::set_cursor(43, 7);
    teh::print("    ██    ");
    teh::set_cursor(44, 7);
    teh::print("    ██    ");
    wait(1000);*/
}

void kernel_init() {
    timer_init();
    loading_screen();
    teh::screen_init();
    for (int i = 0; i < 8; i++) {
        teh::playsound(play[i]);
    }
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
