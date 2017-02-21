#ifndef __PATTERNS_H__
#define __PATTERNS_H__


#include <memory>
#include <vector>
#include <string.h>
#include <stdlib.h>

#include <graphics/surface.h>
#include <matrixsim.h>

// include network interfaces here.
#include <network/network.h>
#include <network/lmcp.h>

// include available patterns here.
#include <patterns/BouncingDot.h>
#include <patterns/GraphicsTest.h>

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
    std::vector<pattern_ptr> patterns;
};

#endif
