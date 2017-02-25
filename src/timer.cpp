#include "timer.h"

extern "C"
{
    #include <SDL2/SDL.h>
}

Timer::Timer()
{}

Timer::Timer(int ms_interval):
interval(ms_interval)
{}

bool Timer::valid(void)
{
    this->current = SDL_GetTicks();
    if((this->current - this->previous) >= this->interval)
    {
        this->previous = this->current;
        return 1;
    }
    return 0;
}
