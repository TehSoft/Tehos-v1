#ifndef TEHCONSOLE_HH
#define TEHCONSOLE_HH

#include <tehmain>
#include <tehio>
#include <tehlang.hh>
#include <tehappman.hh>

// ezek a parancsok
struct command {
    const char* call;
    void (*func)(char* parancs);
    const char* help;
};
void system(char* parancs);
namespace teh::console {
    void cmd(char* parancs);
    void help(char* parancs);
    void testchars(char* parancs);
    void openapp(char* parancs);
    void echo(char* parancs);
    void cls(char* parancs);
    //void tehlang(char* parancs);
    void exit(char* parancs);
};
#endif //TEHCONSOLE_HH