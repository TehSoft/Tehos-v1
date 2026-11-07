#include "libs/main"

#include <tehconsole.hh>
#include <tehlang.hh>
//#include <tehfs.hh>

namespace teh::apps::tote {
    bool run(char* args) {
        teh::print("Hello, world!\n");
        return true;
    }
}