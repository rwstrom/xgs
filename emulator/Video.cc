/**
 * XGS: The Linux GS Emulator
 * Written and Copyright (C) 1996 - 2016 by Joshua M. Thompson
 *
 * You are free to distribute this code for non-commercial purposes
 * I ask only that you notify me of any changes you make to the code
 * Commercial use is prohibited without my written permission
 */

/*
 * This class handles low-level video functions such as OpenGL
 * initialization and pushing video frames out to the hardware.
 */

#include <SDL.h>

#ifdef RPI
#include <bcm_host.h>
#endif

#include "emulator/common.h"

#include "Emulator.h"
#include "Video.h"



Video::Video(const unsigned int width, const unsigned int height)
{
    video_width  = width;
    video_height = height;

    window = SDL_CreateWindow("XGS-rws",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,0 );
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    _renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    initResources();
#ifdef RPI
    onResize(disp_width, disp_height);
#else
    onResize(width, height);
#endif
}

Video::~Video()
{
    SDL_DestroyTexture(_gs_screen);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(window);
}

/**
 * Prepare the window for a new video frame
 */
void Video::startFrame()
{
    SDL_RenderClear(_renderer);
  
}

/**
 * This method actually draws the current frame from the VGC on the screen.
 * It just converts the frame buffer into a texture.
 */
void Video::drawFrame(const pixel_t *frame, const unsigned int width, const unsigned int height)
{
    uint8_t* pixels;
    int pitch;
    _gs_screen_size.w = width;
    _gs_screen_size.h = height;
    SDL_LockTexture(_gs_screen, nullptr, (void **)&pixels, &pitch);

    for(unsigned int h = 0; h < height; ++h)
    {
        memmove(pixels+(pitch*h), frame+(h*width), width*sizeof(uint32_t));
    }
    SDL_UnlockTexture(_gs_screen);
    
    

}

void Video::endFrame()
{
    SDL_RenderCopy(_renderer, _gs_screen, &_gs_screen_size, &_viewport);
    SDL_RenderPresent(_renderer);
}

void Video::setFullscreen(bool enabled)
{
#ifndef RPI
    SDL_SetWindowFullscreen(window, enabled? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
#endif
}

void Video::onResize(const unsigned int width, const unsigned int height)
{
    win_width  = width;
    win_height = height;

    float hscale = static_cast<float>(win_width / video_width);
    float vscale = static_cast<float>(win_height / video_height);

    if (hscale < vscale) {
        frame_height = video_height * hscale;
        frame_width  = video_width * hscale;
    }
    else {
        frame_height = video_height * vscale;
        frame_width  = video_width * vscale;
    }

    frame_left   = (win_width - frame_width) / 2;
    frame_right  = frame_left + frame_width - 1;
    frame_top    = (win_height - frame_height) / 2;
    frame_bottom = frame_top + frame_height - 1;

}

void Video::initResources()
{
    _gs_screen = SDL_CreateTexture(_renderer,SDL_PIXELFORMAT_BGR888,SDL_TEXTUREACCESS_STREAMING,720,262);

}
