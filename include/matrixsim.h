#ifndef __MATRIXSIM_H__
#define __MATRIXSIM_H__

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <stdio.h>
#include <signal.h>
#include <time.h>

#include <mtools.h>
#include <eventhandler.h>
#include <graphics/surface.h>

class MatrixSimulator
{
    public:
        MatrixSimulator(rect_t, int pixelsize=10, bool go_fullscreen=false);
        ~MatrixSimulator();
        void process(surface_ptr);
        void draw(surface_ptr);
        static void handle_input(SDL_Event, void *);
        void draw_rect(rect_t, RGBColor_t, bool);
    private:
        bool c_key_isdown = false;
        bool ctrl_key_isdown = false;
        bool escape_key_isdown = false;
        bool window_quit = false;
        bool in_focus = false;
        bool running = true;
        
        int pixelsize;
        rect_t dims;
        rect_t screen_dims;
        rect_t pixel;

        uint32_t num_instances;
        // sdl
        Uint32 window_id;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

typedef std::shared_ptr<MatrixSimulator> simulator_ptr;

#endif
