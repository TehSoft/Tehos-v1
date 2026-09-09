#ifndef TEHSOUND_HH
#define TEHSOUND_HH
#include <tehos.hh>

namespace teh{
    struct sound {
        uint32 freq_hz;
        uint32 duration_ms;
    };
    void playsound(uint32 freq_hz, uint32 duration_ms);
    void playsound(sound s);
    void startsound(uint32 freq_hz);
    void startsound();
    void endsound();
    void setsound(uint32 freq_hz);
}
#endif //TEHSOUND_HH