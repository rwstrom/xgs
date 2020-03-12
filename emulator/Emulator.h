#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "emulator/common.h"

#include <stdexcept>
#if __has_include(<filesystem>)
    #include <filesystem>
#else
    #include <experimental/filesystem>
#endif

#include <SDL.h>



class Config;
class Video;

class System;
class ADB;
class DOC;
class IWM;
class Mega2;
class Smartport;
class VGC;

namespace M65816 {
    class Processor;
}

constexpr unsigned int kRom01Bytes = 128 * 1024; //131072
constexpr unsigned int kRom03Bytes = 256 * 1024; //262144

const unsigned int kFont40Bytes = 28672;
const unsigned int kFont80Bytes = 14336;

class Emulator {
    public:
        Emulator();
        ~Emulator();

        bool setup(const int, const char **);
        void run();
        void tick();

        Video* getVideo() { return video; }

        M65816::Processor* getCpu() { return cpu; }
        System* getSys() { return sys; }
        ADB* getAdb() { return adb; }
        DOC* getDoc() { return doc; }
        IWM* getIwm() { return iwm; }
        Smartport* getSmartport() { return smpt; }

        float getSpeed() { return actual_speed; }
        float getMaxSpeed() { return maximum_speed; }
        void setMaxSpeed(float speed) { maximum_speed = speed; }

    private:
#if __has_include(<filesystem>)
        std::filesystem::path data_dir;
        std::filesystem::path config_file;
#else
        std::experimental::filesystem::path data_dir;
        std::experimental::filesystem::path config_file;
#endif
        

        System* sys             = nullptr;
        M65816::Processor* cpu  = nullptr;
        Video *video            = nullptr;
        ADB*   adb              = nullptr;
        DOC*   doc              = nullptr;
        IWM*   iwm              = nullptr;
        Mega2* mega2            = nullptr;
        Smartport* smpt         = nullptr;
        VGC*   vgc              = nullptr;

        uint8_t *rom        = nullptr;
        uint8_t *fast_ram   = nullptr;
        uint8_t *slow_ram   = nullptr;

        unsigned int rom_start_page = 0;
        unsigned int rom_pages = 0;
        unsigned int fast_ram_pages = 0;

        bool rom03 = false;
        bool use_debugger = false;
        bool pal = false;

        uint8_t font_40col[kFont40Bytes * 2] = {0};
        uint8_t font_80col[kFont80Bytes * 2] = {0};

        std::string s5d1;
        std::string s5d2;
        std::string s6d1;
        std::string s6d2;
        std::string hd[kSmartportUnits];

        struct {
            bool trace = false;
        } debugger;

        bool running        = false;
        bool fullscreen     = false;
        bool show_status_bar = true;
        bool show_menu      = false;

        float maximum_speed = 0.0f;
        float actual_speed = 0.0f;
        float target_speed = 0.0f;

        unsigned int timer_interval = 0;

        // The number of frames to produce every second
        unsigned int framerate = 0;

        unsigned int current_frame = 0;

        /**
         * To maintain sync we need 32 DOC cycles (38us) 
         * for every 19 microticks (63.7u). Each integer
         * in this area is how many DOC ticks to run
         * during that microtick.
         */
        unsigned int doc_ticks[19] = {
            2, 1, 2, 1, 3, 1,
            2, 1, 2, 1, 3, 1,
            2, 1, 2, 1, 3, 1,
            2
        };

        long times[60] = {0};
        long last_time = 0;
        long this_time = 0;
        long total_time = 0;

        cycles_t cycles[60] = {0};
        cycles_t last_cycles = 0;
        cycles_t total_cycles = 0;

        void pollForEvents();

        unsigned int loadFile(const std::string&, const unsigned int, uint8_t *);
        bool loadConfig(const int, const char **);
};

class EmulatorTimerException : public std::runtime_error {};

#endif // EMULATOR_H_
