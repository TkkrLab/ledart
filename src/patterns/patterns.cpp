#include "patterns/patterns.h"

PatternJobs::PatternJobs()
{
    this->patterns.reserve(100);
}

void PatternJobs::register_pattern(pattern_ptr &pattern)
{
    this->patterns.push_back(std::move(pattern));
}

void PatternJobs::process()
{
    // for(std::vector::size_type i = 0; i < this->patterns.size(); i++)
    for(auto &pattern: this->patterns)
    {
        // pattern_ptr pattern = this->patterns[i];
        if(pattern->surf)
        {
            pattern->surf->generate();
            if(pattern->out)
            {
                pattern->out->process(pattern->surf);
            }
            if(pattern->sim)
            {
                pattern->sim->process(pattern->surf);
            }
        }
    }
}
