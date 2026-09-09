#include "tehsound.hh"

namespace teh{
    void setsound(uint32 freq_hz) {
        uint32 divisor = 1193180 / freq_hz;
        if (divisor > 65535) divisor = 65535;
        if (divisor < 1) divisor = 1;
        cpu::outb(0x43, 0xB6);
        cpu::outb(0x42, (uint8)(divisor & 0xFF));
        cpu::outb(0x42, (uint8)((divisor >> 8) & 0xFF));
    }
    void startsound() {
        uint8 speaker = cpu::inb(0x61);
        speaker |= 0x03;
        cpu::outb(0x61, speaker);
    }
    void startsound(uint32 freq_hz) {
        setsound(freq_hz);
        startsound();
    }
    void endsound() {
        uint8 speaker = cpu::inb(0x61);
        speaker &= ~0x03;
        cpu::outb(0x61, speaker);
    }

    #pragma region playsound
    void playsound(uint32 freq_hz, uint32 duration_ms) {
        if (freq_hz == 0 || duration_ms == 0) return;

        // 1. Hang beállítása és elindítása
        setsound(freq_hz);
        startsound();

        // 2. Közvetlenül átadjuk a milliszekundumot a wait-nek!
        // Nem kell osztani, nem kell darabolni, a wait(ms) elintézi.
        wait(duration_ms);

        // 3. Hang leállítása
        endsound();
        
        // 4. Egy pici (pl. 20 ms) szünet a hangok között, 
        // hogy ne folyjanak össze az egymást követő azonos frekvenciák
        wait(20); 
    }

    void playsound(sound s) {
        playsound(s.freq_hz, s.duration_ms);
    }
    #pragma endregion // playsound
}