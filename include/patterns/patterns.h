#ifndef __PATTERNS_H__
#define __PATTERNS_H__


#include <memory>
#include <string.h>
#include <stdlib.h>

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
    surface_ptr surf;
    network_ptr net;
    simulator_ptr sim;
} Pattern_t;

typedef std::shared_ptr<Pattern_t> pattern_ptr;

class PatternJobs
{
public:
    void register_pattern(pattern_ptr);
    void process();
private:
    LinkedList<pattern_ptr> patterns;
};

#endif
