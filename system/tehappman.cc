#include "tehappman.hh"


#define APP_DEF(name, desc) namespace name { bool run(char* args); }
namespace teh::apps {
    #include "apps/app_list.inc"
}
#undef APP_DEF

namespace teh::apps {
    app apps[] = {
        #define APP_DEF(name, desc) { #name, teh::apps::name::run, desc },
        #include "apps/app_list.inc"
        #undef APP_DEF
    };

    bool useapp(char* name) {
        name = trim_string(name);
        for (const auto& f : apps) {
            if (strcmp(name, f.call, false)) {
                f.func(name + strlen(f.call));
                return true;
            }
        }
        return false;
    }
}