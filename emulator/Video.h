#ifndef VIDEO_H_
#define VIDEO_H_



#include <SDL.h>


class Video {
    public:
        
        float frame_width, frame_height;
        float frame_left, frame_right, frame_top, frame_bottom;

        Video(const unsigned int, const unsigned int);
        ~Video();

        void setFullscreen(bool);
        void onResize(const unsigned int, const unsigned int);

        void startFrame();
        void drawFrame(const pixel_t *, const unsigned int, const unsigned int);
        void endFrame(void);

    private:
        unsigned int video_width, video_height;
        unsigned int win_width, win_height;
        
        SDL_Window    *window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        SDL_Texture* _gs_screen = nullptr;
        
        //current resolution; hires, super-hires, etc.
        SDL_Rect _gs_screen_size = {0,0,0,0}; 
        
        //area that we will draw the finished screen. ie., window size - space for gui elements
        //the screen texture will be stretched/shrunk as needed.
        const SDL_Rect _viewport = {0,0,720,262*2}; 
        
        void initResources();
};

#endif // VIDEO_H_
