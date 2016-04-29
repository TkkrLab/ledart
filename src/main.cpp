/* copyright gpl*/

#include <iostream>
#include <stdio.h>
extern "C"
{
    #include <SDL2/SDL.h>
}
#include <yaml-parse.h>
// my includes. <made with the project>
#include <eventhandler.h>
#include <patterns.h>

#include <gflags/gflags.h>

// gflags name space
using namespace google;

DEFINE_double(fps, 20.0, "Set Fps for program");

typedef struct {
    double fps = 0;
} options_t;

options_t options;

// search for it with extern if you want to register a event handler.
EventHandler global_event_handler = EventHandler();

PatternJobs patternjobs = PatternJobs();

Builder builder = Builder();

void cleanup()
{
    printf("cleanup needed\n");
}

// called when keyboard intterup comes
void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

void general_info()
{
    printf("Build with gcc version: %s.\n", __VERSION__);
    printf("Compiled at: %s.\n", __TIMESTAMP__);
    printf("\n");
}

void arg_parse(int argc, char **argv)
{
    ParseCommandLineFlags(&argc, &argv, true);
    options.fps = 1000 / FLAGS_fps;
}

int main(int argc, char **argv)
{
    atexit(cleanup);
    signal(SIGINT, ki_func);
    general_info();
    arg_parse(argc, argv);

    // parse yaml config.
    // if return less then 0 things went wrong.
    if(yaml_parse() < 0)
    {
        return -1;
    }

    uint64_t frame = 0;
    UNUSED(frame);
    printf("fps: %lf \n", options.fps);
    for(;;)
    {
        global_event_handler.process();
        patternjobs.process();
        SDL_Delay(options.fps);
    }
    return 0;
}