#include <stdio.h>

extern "C"
{
    #include <SDL2/SDL.h>
}

#include <lmcp.h>
#include <BouncingDot.h>
#include <eventhandler.h>
#include <patterns.h>

#include <yamlcpp.h>

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

int main(int argc, char **argv)
{
    signal(SIGINT, ki_func);

    // rect_t matrix_dims = {0, 0, 96, 48};

    // Surface *testsurf = new BouncingDot(matrix_dims);
    // MatrixSimulator *sim = new MatrixSimulator(matrix_dims, 1);
    // Lmcp *net = new Lmcp((char *)"10.42.3.12");
    // Pattern_t pat = {NULL, NULL, NULL};
    // pat.surf = testsurf;
    // pat.sim = sim;
    // pat.net = NULL;//net;
    // patternjobs.register_pattern(&pat);

    // for(;;)
    // {
    //     global_event_handler.process();
    //     patternjobs.process();
    //     SDL_Delay(33.33);
    // }
    return 0;
}