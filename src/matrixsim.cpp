#include "matrixsim.h"

// access to the global event handler
extern EventHandler global_event_handler;

typedef struct 
{
    MatrixSimulator* instance;
} handler_params_t;

static handler_params_t handler_params;

MatrixSimulator::MatrixSimulator(rect_t dims, int pixelsize)
{
    // initialize some variables/
    this->pixelsize = pixelsize;
    this->dims = dims;

    // size of a pixel is pixelsize
    this->pixel.width = pixelsize;
    this->pixel.height = pixelsize;
    
    // screen is at 0,0 and it's width is number of pixelwidth * dim_width.
    this->screen_dims.x = 0;
    this->screen_dims.y = 0;
    this->screen_dims.width = dims.width * this->pixel.width;
    this->screen_dims.height = dims.height * this->pixel.height;

    // initialize sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    this->window = SDL_CreateWindow("MatrixSim",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    this->screen_dims.width, this->screen_dims.height,
                                    SDL_WINDOW_SHOWN);
    if(this->window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    this->window_id = SDL_GetWindowID(this->window);

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if(this->renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    // set a event handler callback.
    // global_event_handler.register_handler(this->handle_input, this);
    handler_params.instance = this;
    global_event_handler.register_handler(this->handle_input, (void *)&handler_params);

    this->num_instances++;
}

void MatrixSimulator::draw_rect(rect_t rect, RGBColor_t color, bool border)
{
    int bw;
    if(border) bw = 1;
    else bw = 0;

    SDL_Rect r = {rect.x + bw, rect.y + bw , rect.width - (2 * bw), rect.height - (2 * bw)};
    SDL_SetRenderDrawColor(this->renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderFillRect(this->renderer, &r);
}

// draws everything to the windows/screen.
void MatrixSimulator::draw(Surface *surf)
{
    static rect_t surf_rect = {0, 0, 0, 0};
    static RGBColor_t color = {0, 0, 0, 0};

    if(surf == NULL)
    {
        return;
    }

    surf_rect = surf->get_rect();

    // fill background.
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(this->renderer);

    // // draw pixels
    for(int y = 0; y < surf_rect.height; y++)
    {
        for(int x = 0; x < surf_rect.width; x++)
        {
            pixel.x = x * this->pixel.width;
            pixel.y = y * this->pixel.height;
            surf->read_pixel(x, y, &color);
            // draw border when pixelsize < 3
            this->draw_rect(pixel, color, (this->pixelsize < 5) ? false:true);
        }
    }

    // actually draw contents to window/screen
    // aka flip back buffer.
    SDL_RenderPresent(this->renderer);
}

// this just handles any process,
void MatrixSimulator::process(Surface *surf)
{
    if(!running)
        return;

    this->draw(surf);
}

void MatrixSimulator::handle_input(SDL_Event event, void *p)
{
    if(p == NULL)
    {
        fprintf(stderr, "got NULL parameters. exiting!\n");
    }
    handler_params_t *params = (handler_params_t*)p;
    if(params->instance == NULL)
    {
        fprintf(stderr, "received NULL instance.\n");
        exit(-1);
    }
    // thins == this instance
    // see what i did there?
    MatrixSimulator *thins = params->instance;

    if(thins->window_id != event.window.windowID)
    {
        return;
    }

    if(event.type == SDL_WINDOWEVENT)
    {
        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            thins->window_quit = true;
        }
        else if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            thins->in_focus = true;
        }
        else if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            thins->in_focus = false;
        }

    }
    if(thins->running && thins->in_focus)
    {
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_c:
                    thins->c_key_isdown = true;
                    break;
                case SDLK_LCTRL:
                    thins->ctrl_key_isdown = true;
                    break;
                case SDLK_ESCAPE:
                    thins->escape_key_isdown = true;
                    break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_c:
                    thins->c_key_isdown = false;
                    break;
                case SDLK_LCTRL:
                    thins->ctrl_key_isdown = false;
                    break;
                case SDLK_ESCAPE:
                    thins->escape_key_isdown = false;
                    break;
            }
        }
        // all reasons to quit.
        if(thins->window_quit || thins->escape_key_isdown)
        {
            thins->running = false;
            // hide window away.
            SDL_HideWindow(thins->window);
            thins->num_instances--;
            if(!thins->num_instances)
            {
                printf("exiting because no simulators running.\n");
                exit(1);
            }
        }
        else if(thins->c_key_isdown && thins->ctrl_key_isdown)
        {
            exit(0);
        }
    }
}

MatrixSimulator::~MatrixSimulator()
{
    if(this->renderer != NULL)
    {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = NULL;
    }
    if(this->window != NULL)
    {
        SDL_DestroyWindow(this->window);
        this->renderer = NULL;
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}