#include <tehos.hh>
#include <tehscreen.hh>
#include <tehkeyboard.hh>
#include <tehconsole.hh>
#include <tehdisk.hh>

using namespace teh;

extern "C" void main(void);
extern "C" int __cxa_guard_acquire(long long *g) { return !*g; }
extern "C" void __cxa_guard_release(long long *g) { *g = 1; }

void kernel_init() {
    // 1. Hardveres kurzor engedélyezése
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
    teh::endl();
}

void main(void) {
    kernel_init();
    /*if(!disk::init()) {
        print("Disk initialization failed!", szin::voros);
        while(1);
    }*/

    char txt[128];
    while (1) {
        print(">", szin::vilagos_szurke);
        setcolor(szin::sarga);
        input(txt);
        endl();
        system(txt);
    }
}
