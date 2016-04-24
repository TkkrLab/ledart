#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <string.h>
#include <stdlib.h>

#include <surface.h>
#include <network.h>
#include <matrixsim.h>

// include available patterns
#include <BouncingDot.h>

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
    static Pattern_t *patterns;
    static int num_patterns;
};

#endif