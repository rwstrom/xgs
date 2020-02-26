#ifndef VIDEO_H_
#define VIDEO_H_

#ifdef RPI
    #include "GLES2/gl2.h"
    #include "EGL/egl.h"
    #include "EGL/eglext.h"
#else
    #include "gl_33.h"
#endif

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct TriangleVertex {
    GLfloat coord[2];
    GLfloat tex[2];
};

class Video {
    public:
        SDL_Window    *window;
        SDL_GLContext context;

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

        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        GLuint texture;
        GLuint vbo;

        GLint attribute_coord;
        GLint attribute_tex_coord;
        GLint uniform_transform;
        GLint uniform_sampler;

        glm::mat4 projection;

        void initResources();
};

#endif // VIDEO_H_
