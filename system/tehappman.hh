#ifndef TEHAPPMAN_HH
#define TEHAPPMAN_HH

#include <tehmain>
#include <tehio>

struct app {
    const char* call;
    bool (*func)(char* args);
    const char* help;
};

namespace teh::apps {
    bool useapp(char* name);
}
#endif // TEHAPPMAN_HH