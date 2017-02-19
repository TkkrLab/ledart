#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <string.h>
#include <stdlib.h>

#include <linkedlist.h>

#include <graphics/surface.h>
#include <matrixsim.h>
#include <network/network.h>
#include <network/lmcp.h>

// include available patterns here.
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
    Pattern_t *patterns;
    size_t num_patterns;
};

#endif
