#ifndef VIDEOMODE_H_
#define VIDEOMODE_H_


#include "emulator/common.h"

class VideoMode {
    public:
        VideoMode() = default;
        ~VideoMode() = default;

        virtual unsigned int getWidth() { return 560; }
        virtual unsigned int getHeight() { return 192; }

        virtual void renderLine(const unsigned int, pixel_t *, bool mono = false) = 0;
};

#endif // VIDEOMODE_H_
