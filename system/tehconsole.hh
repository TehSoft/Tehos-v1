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

void help();
void echo();
void cls();
void tehlang();
void exit();
#endif //TEHCONSOLE_HPP