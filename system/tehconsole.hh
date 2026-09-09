#ifndef TEHCONSOLE_HPP
#define TEHCONSOLE_HPP

#include <tehos.hh>
#include <tehio.hh>
#include <tehlang.hh>

// ezek a parancsok
struct command {
    const char* call;
    void (*func)(char* parancs);
    const char* help;
};
void system(char* parancs);

void help(char* parancs);
void echo(char* parancs);
void cls(char* parancs);
void tehlang(char* parancs);
void exit(char* parancs);
#endif //TEHCONSOLE_HPP