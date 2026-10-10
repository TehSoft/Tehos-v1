#include "tehappman.hh"

#include "appcollector.ii"

namespace teh::apps {
    app apps[] = {
        #define APP_DEF(name, desc) { #name, teh::apps::name::run, desc },
        #include "apps/app_list.inc"
        #undef APP_DEF
    };

    bool useapp(char* name) {
        name = trim_string(name);
        for (app f : apps) {
            if (strcmp(name, f.call, false)) {
                f.func(name + strlen(f.call));
                return true;
            }
        }
        return false;
    }
}