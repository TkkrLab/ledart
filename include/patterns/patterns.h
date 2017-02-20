#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <string.h>
#include <stdlib.h>

#include <memory>

#include <linkedlist.h>

#include <graphics/surface.h>
#include <matrixsim.h>

// include network interfaces here.
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
    void register_pattern(std::shared_ptr<Pattern_t>);
    void process();
private:
    LinkedList<std::shared_ptr<Pattern_t>> patterns;
};

#endif
