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

class MatrixSimulator;
typedef struct 
{
    // i'll allow this pointer and not wrap it in a smart pointer.
    // since it's just a reference nothing more.
    MatrixSimulator* instance;
} handler_params_t;

class MatrixSimulator
{
    public:
        MatrixSimulator(rect_t, int pixelsize=10, bool go_fullscreen=false);
        ~MatrixSimulator();
        void process(const surface_ptr &);
        void draw(const surface_ptr &);
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

        uint32_t interval = 1000 / 25;
        uint32_t pre_tick = 0;

        static uint32_t num_instances;
        handler_params_t handler_params;

        // sdl
        Uint32 window_id;
        SDL_Window *window;
        SDL_Renderer *renderer;

        surface_ptr last_surf;
};


typedef std::unique_ptr<MatrixSimulator> simulator_ptr;

#endif
