#include <iostream>
#include <stdio.h>

using namespace std;

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <lmcp.h>
#include <BouncingDot.h>
#include <eventhandler.h>
#include <patterns.h>

#include <yaml-cpp/yaml.h>

// these are global so that other patterns could use them if they want.
// via the extern keyword.
EventHandler global_event_handler = EventHandler();
PatternJobs patternjobs = PatternJobs();

// called when keyboard intterup comes
void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

Surface *surface_builder(char *name, rect_t dims)
{
    if(strcmp(GETNAME(BouncingDot), name))
    {
        Surface *surf = new BouncingDot(dims);
    }
}

int main(int argc, char **argv)
{

    rect_t matrix_dims = {0, 0, 0, 0};
    // allocate the new sim just once and assign if needed.
    MatrixSimulator *sim = NULL;
    Surface *surf = NULL;
    Network *net = NULL;

    signal(SIGINT, ki_func);

    YAML::Node config = YAML::LoadFile("configs/test.yml");
    if(config.size() == 0 || !(config))
    {
        fprintf(stderr,
                "config file incomplete or empyt!. exiting\n");
        return -1;
    }
    for(YAML::const_iterator j = config.begin();j != config.end(); ++j) {
        YAML::Node pattern_job = config[j->first.as<std::string>()];
        YAML::Node matrix = pattern_job["matrix"].as<YAML::Node>();
        YAML::Node matrixsim = pattern_job["matrixsim"].as<YAML::Node>();
        YAML::Node protocol = pattern_job["protocol"].as<YAML::Node>();
        YAML::Node pattern = pattern_job["pattern"].as<YAML::Node>();
        
        const char *pname = pattern["job"].as<std::string>().c_str();

        if(matrix)
        {}
        else
        {
            fprintf(stderr,
                    "%s: no valid dimensions found. exiting.\n",
                    pname);
            return -1;
        }

        if(matrixsim)
        {}
        else
        {
            fprintf(stderr,
                    "%s: running pattern without simulator.\n",
                    pname);
        }

        if(protocol)
        {}
        else
        {
            fprintf(stderr,
                    "%s: no protocol found. not sending.\n",
                    pname);
        }
        if(pattern)
        {}
        else
        {
            fprintf(stderr,
                    "%s: no pattern found. exiting.\n",
                    pname);
            return -1;
        }
    }
    return 0;

    Pattern_t pat = {NULL, NULL, NULL};
    pat.surf = surf;
    pat.sim = sim;
    pat.net = net;
    patternjobs.register_pattern(&pat);

    for(;;)
    {
        global_event_handler.process();
        patternjobs.process();
        // SDL_Delay(20.00);
    }
    return 0;
}