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
#include <surface.h>

class MatrixSimulator
{
    public:
        MatrixSimulator(rect_t, int pixelsize=10);
        ~MatrixSimulator();
        void process(Surface *);
        void draw(Surface *);
        static void handle_input(SDL_Event, void *);
        void draw_rect(rect_t, RGBColor_t, bool);
    private:
        int pixelsize;
        rect_t dims;
        rect_t screen_dims;
        rect_t pixel;
        Uint32 window_id;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif