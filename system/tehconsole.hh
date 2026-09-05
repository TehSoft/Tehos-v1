#ifndef TEHCONSOLE_HPP
#define TEHCONSOLE_HPP

#include <tehos.hh>
#include <tehlang.hh>
#include <tehkeyboard.hh>

// ezek a parancsok
struct command {
    const char* call;
    void (*func)();
    const char* help;
};

void tehlang();
void help();
void cls();
void exit();
#endif //TEHCONSOLE_HPP