#include <stdio.h>
#include <signal.h>
extern "C"
{
    #include <SDL2/SDL.h>
}
#include <surface.h>
#include <BouncingDot.h>

class MatrixSimulator
{
    public:
        MatrixSimulator(rect_t);
        ~MatrixSimulator();
        void process(Surface *);
        void handle_input();
        void draw_rect(rect_t, RGBColor_t);
    private:
        static rect_t dims;
        static rect_t pixel;
        static SDL_Window *window;
        static SDL_Surface *screen_surf;
        static SDL_Renderer *renderer;
};

rect_t MatrixSimulator::dims;
rect_t MatrixSimulator::pixel;
SDL_Window *MatrixSimulator::window = NULL;
SDL_Surface *MatrixSimulator::screen_surf = NULL;
SDL_Renderer *MatrixSimulator::renderer = NULL;

MatrixSimulator::MatrixSimulator(rect_t dims)
{
    this->dims = dims;
    // initialize sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    this->window = SDL_CreateWindow("MatrixSim",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    this->dims.width, this->dims.height,
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
}

void MatrixSimulator::draw_rect(rect_t rect, RGBColor_t color)
{
    SDL_Rect r = {rect.x, rect.y, rect.width, rect.height};
    SDL_SetRenderDrawColor(this->renderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderFillRect(this->renderer, &r);
}

void MatrixSimulator::process(Surface *surf)
{
    static rect_t surf_rect = {0, 0, 0, 0};
    static rect_t pixel = {0, 0, 0, 0};
    static RGBColor_t color = {0, 0, 0, 0};

    surf_rect = surf->get_rect();

    // fill background.
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(this->renderer);

    // draw pixels
    for(int y = 0; y < surf_rect.height; y++)
    {
        for(int x = 0; x < surf_rect.width; x++)
        {
            pixel.x = x;
            pixel.y = y;
            pixel.width = 1;
            pixel.height = 1;
            surf->read_pixel(x, y, &color);
            this->draw_rect(pixel, color);
        }
    }

    // actually draw contents to window/screen
    // aka flip back buffer.
    SDL_RenderPresent(this->renderer);
}

void MatrixSimulator::handle_input()
{

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

volatile sig_atomic_t ki_flag = 0;

void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

int main(int argc, char **argv)
{
    signal(SIGINT, ki_func);

    rect_t matrix_dims = {0, 0, 10, 11};
    Surface *testsurf = new BouncingDot(matrix_dims);
    MatrixSimulator sim = MatrixSimulator(matrix_dims);
    for(;;)
    {
        testsurf->generate();
        sim.process(testsurf);
        SDL_Delay(100);
    }
    return 0;
}