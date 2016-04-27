#include "eventhandler.h"

EventHandler::EventHandler()
{}

// don't know why but in hindsight maybe didn't need to include the void *
// for passing extra stuff, but maybe nice for future applications.
void EventHandler::register_handler(ev_callback callback, void *param)
{
    if(this->num_handlers == this->MAX_HANDLERS)
    {
        printf("to many event handlers.\n");
        exit(0);
    }

    this->handlers[this->num_handlers] = callback;
    this->params[this->num_handlers] = param;
    this->num_handlers++;
}

void EventHandler::unregister_handler(ev_callback callback)
{
    for(size_t i = 0; i < this->num_handlers; i++)
    {
        if(this->handlers[i] == callback)
        {
            this->handlers[i] = NULL;
            return;
        }
    }
}

void EventHandler::process()
{
    static SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        for(unsigned int h = 0; h < this->num_handlers; h++)
        {
            ev_callback handler = this->handlers[h];
            if(handler != NULL)
            {
                void *param = this->params[h];
                handler(event, param);
            }
        }
    }
}
