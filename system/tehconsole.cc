#include "tehconsole.hh"

command parancsok[] = {
    {"help", help, "Segitseg a parancsokhoz"},
    {"echo", echo, "Szoveg kiirasa"},
    {"cls", cls, "A kepernyo torlese"},
    {"tehlang", tehlang, "A TEHLANG nyelv futtatasa"},
    {"exit", exit, "A rendszer leallitasa"}
};


void help(char* parancs) {
    parancs += 4;
    parancs = trim_string(parancs);
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

void echo(char* parancs) {
    parancs += 4;
    trim_string(parancs);
    if (*parancs == '\0') {
        return;
    }
    teh::print(parancs, szin::vilagos_zold);
    teh::endl();
}

void cls(char* parancs) {
    parancs += 3;
    if (*parancs != '\0') return;
    teh::clear();
    teh::char_fill('=', szin::vilagos_cian);
    teh::print("                           TEHOS operacios rendszer                            \n", szin::vilagos_zold);
    teh::char_fill('=', szin::vilagos_cian);
    teh::endl();
    teh::endl();
}

void tehlang(char* parancs) {
    parancs += 7;
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
}

void exit(char* parancs) {
    parancs += 4;
    if (*parancs != '\0') return;
    teh::clear();
    teh::setcolor(szin::vilagos_piros);
    teh::print("\nA rendszer leall, nyomja meg a gep gombjat!");
    while (1) {
        asm volatile("cli");
        asm volatile("hlt");
    }
}



void system(char* parancs) {
    for (command f : parancsok) {
        if (strcmp(parancs, f.call, false)) {
            f.func(parancs);
            return;
        }
    }
    return;
}