#include "tehconsole.hh"

command parancsok[] = {
    {"help", help, "Segitseg a parancsokhoz"},
    {"cls", cls, "A kepernyo torlese"},
    {"exit", exit, "A rendszer leallitasa"},
    {"tehlang", tehlang, "A TEHLANG nyelv futtatasa"}
};


void help() {
    for (command f : parancsok) {
        teh::print(f.call, szin::vilagos_zold);
        teh::print(" - ", szin::vilagos_zold);
        teh::print(f.help, szin::vilagos_zold);
        teh::endl();
    }
}

void cls() {
    teh::clear();
    teh::char_fill('=', szin::vilagos_cian);
    teh::print("                           TEHOS operacios rendszer                            \n", szin::vilagos_zold);
    teh::char_fill('=', szin::vilagos_cian);
    teh::endl();
    teh::endl();
}

void exit() {
    teh::clear();
    teh::setcolor(szin::vilagos_piros);
    teh::print("\nA rendszer leall, nyomja meg a gep gombjat!");
    while (1) {
        asm volatile("cli");
        asm volatile("hlt");
    }
}

void tehlang() {
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
}

void system(const char* parancs) {
    for (command f : parancsok) {
        if (strcmp(parancs, f.call)) {
            f.func();
            return;
        }
    }
}