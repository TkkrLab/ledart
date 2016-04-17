#include <stdio.h>
#include <matrixsim.h>
#include <eventhandler.h>

EventHandler global_event_handler = EventHandler();

// called when keyboard intterup comes
void ki_func(int sig)
{
    printf("\nCaught keyboard interrupt.! signal: %d\n", sig);
    exit(1);
}

int main(int argc, char **argv)
{
    signal(SIGINT, ki_func);

    rect_t matrix_dims = {0, 0, 800, 600};
    Surface *testsurf = new BouncingDot(matrix_dims);
    MatrixSimulator *sim = new MatrixSimulator(matrix_dims, 1);

    for(;;)
    {
        global_event_handler.process();
        testsurf->generate();
        sim->process(testsurf);
    }
    return 0;
}