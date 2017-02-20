/*
    author: Duality4y (Robert)

    this software serves as fun software to controle ledboards.
    normaly they all have different interfaces.
    some have a serial interface some have wifi, and yet some other boards
    are networked (utp udp/tcp)

    these files implement classes that can be used to send data to different
    ledboards.

    mainly it is in 3 parts. plus some extra support classes.
    anything that can be drawn to inherits from surface.
    if you want any graphical draw function you inherit from Graphics,
    which inherits from surface.

    the main processing loop calls the surface's that are load by the config file.
    thier overridden function generate() makes sure that everything for you pattern
    is updated and done. all of this is done in the PatternJob object. it has a list of surfaces.
    calls each surface its generate function. then passes that surface to the associated network
    object. surfaces are paired with network objects so that each pattern can be send to a different
    ledboard if needed.

    and third part is the network interface.
    any class/object that wants to connect to a networked ledboard inherits from
    Network class. it mainly implements some low level socket things.
    your interface class overrides it's send function.
    that is where you implement protocol details.
    Network::transmit() is called to send the actual data.

    TODO write more on support functions:
    * matrixsimulator.
    * global_event_handler
    * more on surface object construction?
*/

#include <iostream>
#include <stdio.h>
extern "C"
{
    #include <SDL2/SDL.h>
}
#include <yaml-parse.h>

// project includes
#include <eventhandler.h>
#include <patterns/patterns.h>

#include <gflags/gflags.h>

// gflags name space
using namespace google;

DEFINE_double(fps, 0, "Set Fps for program.");
DEFINE_bool(showFps, false, "enable fps printing.");
DEFINE_bool(n, false, "run program once.");
DEFINE_string(config_file, "test.yml", "run with selected config_file.");

typedef struct {
    double fps = 0;
    bool showFps = false;
    bool run_once = false;
    bool list = false;
    bool debug = false;
    // serves as prefix.
    char config_file[40] = "configs/";
} options_t;

options_t options;

// search for it with extern if you want to register a event handler.
EventHandler global_event_handler = EventHandler();
// pattern handler
PatternJobs patternjobs = PatternJobs();
// this build objects that are known from name.
Builder builder = Builder();

void cleanup()
{
    printf("\ncleanup needed\n");
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
    options.fps = 1 / (FLAGS_fps / 1000);
    options.run_once = FLAGS_n;
    options.showFps = FLAGS_showFps;

    // options.config_file = FLAGS_config_file.c_str();
    size_t prefix_offset = strlen(options.config_file);
    
    strncpy((options.config_file + prefix_offset),
            FLAGS_config_file.c_str(),
            strlen(FLAGS_config_file.c_str()));
}

int main(int argc, char **argv)
{
    uint32_t current_ticks = 0;
    uint32_t previous_ticks = 0;
    uint32_t interval = 1000;

    uint64_t previous_frames = 0;
    uint64_t frames = 0;

    atexit(cleanup);
    signal(SIGINT, ki_func);
    general_info();
    arg_parse(argc, argv);

    // parse yaml config_file.
    // if return less then 0 things went wrong.
    printf("using config_file: %s\n", options.config_file);
    if(yaml_parse(options.config_file) < 0)
    {
        return -1;
    }

    for(;;)
    {
        // handle user input and any other event.s
        global_event_handler.process();
        // process all the patterns.
        patternjobs.process();

        // print fps information.
        if(options.showFps)
        {
            current_ticks = SDL_GetTicks();
            if((current_ticks - previous_ticks) >= interval)
            {
                previous_ticks = SDL_GetTicks();
                // the values for (frames - previous_frames) won't get ridiculously high
                printf("Fps: %d          \r", (int)(frames - previous_frames));
                fflush(stdout);
                previous_frames = frames;
            }
        }
        
        // if fps > 0 then it's applied. else we go for it as fast as possible.
        if(options.fps > 0)
            SDL_Delay(options.fps);
        
        // single run we break early or right after the first itteration.
        if(options.run_once)
            break;

        // keep track of how many frames we have ran.
        frames += 1;
    }
    return 0;
}
