#include "libs/main"
#include <tehsound.hh>

namespace teh::apps::test {
    bool run(char* args) {
        teh::clear();
        teh::print_no_scroll(startpage, szin::barna);
        teh::print_no_scroll(emptyline, szin::barna);
        teh::print_no_scroll(fulline, szin::barna);
        for (int _ = 0; _ < 21; _++) {
            teh::print_no_scroll(emptyline, szin::barna);

        }
        teh::print_no_scroll(endpage, szin::barna);
        teh::set_cursor(38, 1);
        teh::cout << "TEST";
        teh::set_cursor(1, 3);
        teh::cout << "Ez egy tesztapp.";
        wait(10000);
        return true;
    }
}
namespace teh::apps::otherapp {
    bool run(char* args) {
        teh::print("Vegzetes hiba!\nAllitsa le a gepet!", szin::voros);
        wait(1000);
        teh::clear();
        while(true) {
            wait(10);
            teh::playsound(1000, 10);
            teh::playsound(250, 10);
            teh::playsound(1500, 10);
            teh::playsound(2000, 10);
            for(int _ = 0; _ < 25 * 80; _++) {
                teh::print_no_scroll("\xDB", szin::voros);
            }
            wait(10);
            teh::playsound(1000, 10);
            teh::playsound(250, 10);
            teh::playsound(1500, 10);
            teh::playsound(2000, 10);
            teh::setcolor(szin::fekete);
            teh::clear();
        }
    }
}