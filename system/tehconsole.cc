#include "tehconsole.hh"

namespace teh {
    command parancsok[] = {
        { "help", teh::console::help, "Segitseg a parancsokhoz" },
        { "testchars", teh::console::testchars, "Temp!" },
        { "openapp", teh::console::openapp, "Alk. megnyitasa" },
        { "echo", teh::console::echo, "Szoveg kiirasa" },
        { "cls", teh::console::cls, "A kepernyo torlese" },
        //{ "tehlang", teh::console::tehlang, "A TEHLANG nyelv futtatasa" },
        { "exit", teh::console::exit, "A rendszer leallitasa" }
    };

    namespace console {
        void cmd(char* parancs) {
            parancs = trim_string(parancs);
            if (*parancs == '\0') {
                return;
            }
            for (command f : teh::parancsok) {
                if (strcmp(parancs, f.call, false)) {
                    f.func(trim_string(parancs + strlen(f.call)));
                    return;
                }
            }
            teh::print("Ismeretlen parancs:", szin::vilagos_piros);
            teh::print(parancs, szin::voros);
            teh::endl();
            return;
        }
        void help(char* parancs) {
            if (*parancs == '\0') {
                for (command f : parancsok) {
                    teh::print(f.call, szin::vilagos_zold);
                    teh::print(" - ", szin::vilagos_zold);
                    teh::print(f.help, szin::vilagos_zold);
                    teh::endl();
                }
            }
            else {
                bool found = false;
                for (command f : parancsok) {
                    if (strcmp(parancs, f.call)) {
                        teh::print(f.help, szin::vilagos_zold);
                        teh::endl();
                        found = true;
                    }
                }
            }
        }

        void testchars(char* parancs) {
            for (int i = 0; i < 256; i++) {
                teh::print((int64)i);
                teh::print(": ");
                teh::print((char)i);
            }
        }

        void openapp(char* parancs) {
            if (*parancs == '\0') {
                return;
            }
            if (teh::apps::useapp(parancs)) {
                teh::print("Alkalmazas sikeresen lefutott.\n", szin::vilagos_zold);
            }
            else {
                teh::print("Alkalmazas futtatasa sikertelen.\n", szin::vilagos_piros);
            }
        }

        void echo(char* parancs) {
            if (*parancs == '\0') {
                return;
            }
            teh::print(parancs, szin::vilagos_zold);
            teh::endl();
        }

        void cls(char* parancs) {
            if (*parancs != '\0') return;
            teh::clear();
            teh::print('\xC9', szin::vilagos_cian);
            teh::char_fill('\xCD', szin::vilagos_cian);
            teh::print("\b\xBB\xBA", szin::vilagos_cian);
            teh::print("\x01                         TEHOS operacios rendszer                           \x01", szin::vilagos_zold);
            teh::print("\xBA\xC8", szin::vilagos_cian);
            teh::char_fill('\xCD', szin::vilagos_cian);
            teh::print("\b\xBC", szin::vilagos_cian);
            teh::endl();
            teh::endl();
        }

        /*void tehlang(char* parancs) {
            if (*parancs != '\0') return;
            teh::print("A TEHLANG nyelv futtatasa, exit a kilepeshez.\n", szin::vilagos_zold);
            char buffer[128];
            while (1) {
                teh::print(">>> ", szin::vilagos_zold);
                teh::input(buffer);
                if (strcmp(buffer, "exit")) {
                    teh::endl();
                    break;
                }
                teh::endl();
                buffer[127] = '\0';
                teh::lang::inline_tehlang(buffer);
                teh::endl();
            }
        }*/

        void exit(char* parancs) {
            if (*parancs != '\0') return;
            teh::clear();
            teh::setcolor(szin::vilagos_piros);
            teh::print("\nA rendszer leall, nyomja meg a gep gombjat!");
            while (1) {
                asm volatile("cli");
                asm volatile("hlt");
            }
        }
    };
};
void system(char* parancs) {
    parancs = trim_string(parancs);
    char* line_start = parancs;
    for (int i = 0; parancs[i] != '\0'; i++) {
        if (parancs[i] == '\n' || parancs[i] == ';') {
            parancs[i] = '\0';
            teh::console::cmd(line_start);
            line_start = parancs + i + 1;
        }
    }
    if (*line_start != '\0') {
        teh::console::cmd(line_start);
    }
}