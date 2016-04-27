#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

extern "C"
{
    #include <SDL2/SDL.h>
}

typedef void(*ev_callback)(SDL_Event, void *);

class EventHandler
{
    public:
        EventHandler();
        void register_handler(ev_callback, void *);
        void unregister_handler(ev_callback);
        void process();
    private:
        static const size_t MAX_HANDLERS = 100;
        size_t num_handlers = 0;
        void *params[MAX_HANDLERS] = {NULL};
        ev_callback handlers[MAX_HANDLERS] = {NULL};
};

#endif