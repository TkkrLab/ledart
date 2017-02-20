#include "patterns/patterns.h"

void PatternJobs::register_pattern(pattern_ptr pattern)
{
    this->patterns.append(pattern);
}

void PatternJobs::process()
{
    for(int i = 0; i < this->patterns.length(); i++)
    {
        pattern_ptr pattern = this->patterns[i];
        if(pattern->surf)
        {
            pattern->surf->generate();
            if(pattern->net)
            {
                pattern->net->process(pattern->surf);
            }
            if(pattern->sim)
            {
                pattern->sim->process(pattern->surf);
            }
        }
    }
}
