#ifndef __PATTERNS_H__
#define __PATTERNS_H__


#include <memory>
#include <vector>
#include <string.h>
#include <stdlib.h>

#include <graphics/surface.h>
#include <matrixsim.h>

// include network interfaces here.
#include <outputs/interface.h>

// include available patterns here.
#include <patterns/BouncingDot.h>
#include <patterns/GraphicsTest.h>
#include <patterns/life.h>
#include <patterns/fft.h>

typedef struct
{
    surface_ptr surf;
    output_ptr out;
    simulator_ptr sim;
} Pattern_t;

typedef std::shared_ptr<Pattern_t> pattern_ptr;

class PatternJobs
{
public:
    PatternJobs();
    void register_pattern(pattern_ptr);
    void process();
private:
    std::vector<pattern_ptr> patterns;
};

#endif
