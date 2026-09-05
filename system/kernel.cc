#include <tehos.hh>
#include <tehscreen.hh>
#include <tehkeyboard.hh>
#include <tehconsole.hh>
#include <tehdisk.hh>

using namespace teh;

extern "C" void main(void);
extern "C" int __cxa_guard_acquire(long long *g) { return !*g; }
extern "C" void __cxa_guard_release(long long *g) { *g = 1; }


void main(void) {
    teh::clear();
    teh::char_fill('=', szin::vilagos_cian);
    teh::print("                           TEHOS operacios rendszer                            \n", szin::vilagos_zold);
    teh::char_fill('=', szin::vilagos_cian);
    teh::endl();
    teh::endl();
    /*if(!disk::init()) {
        print("Disk initialization failed!", szin::voros);
        while(1);
    }*/

    char txt[128];
    while (1) {
        print("TEHOS>", szin::vilagos_szurke);
        setcolor(szin::sarga);
        input(txt);
        endl();
        system(txt);
    }
}
