#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <string.h>
#include <stdlib.h>

#include <graphics/surface.h>
#include <matrixsim.h>

// include network interfaces here.
#include <network/network.h>
#include <network/lmcp.h>

// include available patterns also here.
#include <patterns/BouncingDot.h>

typedef struct
{
    Surface *surf;
    Network *net;
    MatrixSimulator *sim;
} Pattern_t;

class PatternJobs
{
public:
    PatternJobs();
    ~PatternJobs();
    void register_pattern(Pattern_t *);
    void process();
private:
    Pattern_t *patterns = NULL;
    size_t num_patterns = 0;
};

#endif