/* 
    Copyright

    This file is part of Foobar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/
    
/*
    author: Duality4y (Robert)

    this software serves as fun software to controle ledboards.
    normaly they all have different interfaces.
    some have a serial interface some have wifi, and yet some other boards
    are networked (utp udp/tcp)

    these files implement classes that can be used to send data to different
    ledboards.

    mainly it is in 3 parts. plus some extra support classes.
    anything that can be drawn to inherets from surface.
    if you want any graphical draw function you inheret from Grahics,
    which inherits from surface.

    the main processing loop calls the surface's that are load by config file.
    thier overridden function generate() makes sure that everything for you pattern
    is update and done. all of this is done in the PatterJob object. it has a list of surfaces.
    calls each surface its generate function. then passes that surface to the associated network
    object. surfaces are pared with network objects so that each pattern can be send to a different
    ledboard if needed.

    and third part is the network interface.
    any class/object that wants to connect to a networked ledboard inherits from
    Network class. in mainly implements some low level socket things.
    your inetrface class overrides it's send function.
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
// my includes. <made with the project>
#include <eventhandler.h>
#include <patterns.h>

#include <gflags/gflags.h>

// gflags name space
using namespace google;

DEFINE_double(fps, 20.0, "Set Fps for program.");
DEFINE_bool(n, false, "run program once.");
DEFINE_string(config_file, "test.yml", "run with selected config_file.");

typedef struct {
    double fps = 0;
    bool run_once = false;
    // serves as prefix.
    char config_file[40] = "configs/";
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
    options.run_once = FLAGS_n;
    // options.config_file = FLAGS_config_file.c_str();
    size_t prefix_offset = strlen(options.config_file);
    
    strncpy((options.config_file + prefix_offset),
            FLAGS_config_file.c_str(),
            strlen(FLAGS_config_file.c_str()));
}

int main(int argc, char **argv)
{
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

    uint64_t frame = 0;
    UNUSED(frame);

    if(options.run_once)
    {
        global_event_handler.process();
        patternjobs.process();
        SDL_Delay(options.fps);
    }

    for(;;)
    {
        global_event_handler.process();
        patternjobs.process();
        SDL_Delay(options.fps);
    }
    return 0;
}