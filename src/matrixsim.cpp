#include "matrixsim.h"

// access to the global event handler
extern EventHandler global_event_handler;

int MatrixSimulator::pixelsize;
rect_t MatrixSimulator::dims;
rect_t MatrixSimulator::pixel;
rect_t MatrixSimulator::screen_dims;
SDL_Window *MatrixSimulator::window = NULL;
SDL_Surface *MatrixSimulator::screen_surf = NULL;
SDL_Renderer *MatrixSimulator::renderer = NULL;

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
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
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

    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED);
    if(this->renderer == NULL)
    {
        printf("Renderer coudl not be created! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    this->screen_surf = SDL_GetWindowSurface(this->window);
    if(this->screen_surf == NULL)
    {
        printf("couldn't create surface. %s\n", SDL_GetError());
        exit(-1);
    }

    // set a event handler callback.
    global_event_handler.register_handler(this->handle_input, this);
}

void MatrixSimulator::draw_rect(rect_t rect, RGBColor_t color, bool border)
{
    SDL_Rect r = {rect.x, rect.y, rect.width, rect.height};
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

    // draw pixels
    for(int y = 0; y < surf_rect.height; y++)
    {
        for(int x = 0; x < surf_rect.width; x++)
        {
            pixel.x = x * this->pixel.width;
            pixel.y = y * this->pixel.height;
            surf->read_pixel(x, y, &color);
            this->draw_rect(pixel, color, false);
        }
    }

    // actually draw contents to window/screen
    // aka flip back buffer.
    SDL_RenderPresent(this->renderer);
}

// this just handles any process,
void MatrixSimulator::process(Surface *surf)
{
    static uint64_t frame = 0;

    frame++;
    if(!(frame % 10000))
    {
        this->draw(surf);
    }
}

void MatrixSimulator::handle_input(SDL_Event event, void *this_instance)
{
    static bool c_key_isdown;
    static bool ctrl_key_isdown;
    static bool escape_key_isdown;
    static bool window_quit = false;

    if(event.type == SDL_QUIT)
    {
        window_quit = true;
    }
    else if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_c:
                c_key_isdown = true;
            break;
            case SDLK_LCTRL:
                ctrl_key_isdown = true;
            break;
            case SDLK_ESCAPE:
                escape_key_isdown = true;
            break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_c:
                c_key_isdown = false;
            break;
            case SDLK_LCTRL:
                ctrl_key_isdown = false;
            break;
            case SDLK_ESCAPE:
                escape_key_isdown = false;
            break;
        }
    }

    // all reasons to quit.
    if(window_quit || (c_key_isdown && ctrl_key_isdown) || escape_key_isdown)
    {
        exit(0);
    }
}

MatrixSimulator::~MatrixSimulator()
{
    if(this->screen_surf != NULL)
    {
        SDL_FreeSurface(this->screen_surf);
        this->screen_surf = NULL;
    }
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
    SDL_Quit();
}