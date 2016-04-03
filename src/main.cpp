#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <patterns.h>
#include <BouncingDot.h>
#include <lmcp.h>

char target[] = "10.42.3.12";

// 20 jobs max for now.
size_t num_patternjobs = 0;
const size_t max_patternjobs = 20;
Pattern patternjobs[max_patternjobs];

void process_patternjobs()
{
    // // generate a new frame
    // pattern.generate();
    // // send it out on the coupled network.
    // pattern.sendout();
    for(int job = 0; job < num_patternjobs; job++)
    {
        Pattern pat = patternjobs[job];
        pat.generate();
        pat.sendout();

        // wait some time
        usleep(30e3);
    }
}

void create_pattern_test()
{
    // size 96x48 at pos (0, 0) and size (96 * 48)
    const int width = 96 / 2;
    const int height = 48 / 2;
    rect_t ledboard_dims = {0, 0, width, height, (width * height)};

    BouncingDot testdot = BouncingDot(ledboard_dims);
    Lmcp network = Lmcp(target);
    // creates a pattern and gives it a name (GETNAME(pattern)) and associate a
    // network com protocol with it.
    Pattern testpattern = Pattern(testdot, network, GETNAME(BouncingDot));
    // run it for a bit but still exit.
    for(int i = 0; i < (width * height) / 2; i++)
    {
        testpattern.generate();
        testpattern.sendout();
        usleep(30e3);
    }

}

void add_pattern(Surface &pat, Network &net, const char *name)
{
    // check if we are at our limit.
    if(num_patternjobs >= max_patternjobs)
        return;

    patternjobs[num_patternjobs] = Pattern(pat, net, name);
    num_patternjobs++;
}

void some_general_info()
{
    printf("Build with gcc version: %s.\n", __VERSION__);
    printf("Compiled at: %s.\n", __TIMESTAMP__);
    printf("\n");
}

int main(int argc, char **argv)
{
    some_general_info();
    // create_pattern_test();

    //create a job

    rect_t dims = {0, 0, 96, 48, (96 * 48)};
    // this works as opposed to just letting the compiler make the object.
    // if the compiler makes the object then it doesnt called the derived class
    // it's base constructors.
    Surface *pattern = new BouncingDot(dims);
    Network *lmcp = new Lmcp(target);
    
    add_pattern(*pattern, *lmcp, GETNAME(BouncingDot));

    // run a few times
    for(int i = 0; i < 2000; i++)
    {
        process_patternjobs();
    }
    return 0;
}