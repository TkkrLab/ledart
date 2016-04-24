#ifndef __MATRIXSIM_H__
#define __MATRIXSIM_H__

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <stdio.h>
#include <signal.h>
#include <time.h>

#include <eventhandler.h>
#include <surface.h>

class MatrixSimulator
{
    public:
        MatrixSimulator(rect_t, int pixelsize=10);
        ~MatrixSimulator();
        void process(Surface *);
        void draw(Surface *);
        static void *handle_input(SDL_Event, void *);
        void draw_rect(rect_t, RGBColor_t, bool);
    private:
        static int pixelsize;
        static rect_t dims;
        static rect_t screen_dims;
        static rect_t pixel;
        static SDL_Window *window;
        static SDL_Surface *screen_surf;
        static SDL_Renderer *renderer;
};

#endif