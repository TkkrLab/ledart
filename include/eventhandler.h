#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

extern "C"
{
    #include <SDL2/SDL.h>
}

typedef void *(*ev_callback)(SDL_Event, void *);

class EventHandler
{
    public:
        EventHandler();
        void register_handler(ev_callback, void *);
        void process();
    private:
        static const int MAX_HANDLERS = 100;
        static size_t num_handlers;
        static void *params[MAX_HANDLERS];
        static ev_callback handlers[MAX_HANDLERS];
};

#endif