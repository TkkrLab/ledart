#include "patterns/patterns.h"

PatternJobs::PatternJobs()
{
    this->num_patterns = 0;
    this->patterns = NULL;
}

PatternJobs::~PatternJobs()
{
    if(this->patterns != NULL)
    {
        free(this->patterns);
        this->patterns = NULL;
    }
}

void PatternJobs::register_pattern(Pattern_t *pattern)
{
    this->num_patterns += 1;
    Pattern_t *new_p = (Pattern_t *)realloc(this->patterns, sizeof(Pattern_t)*this->num_patterns);
    if(new_p == NULL)
    {
        free(this->patterns);
        this->patterns = NULL;
        fprintf(stderr, "couldn't create/reallocate space for more patterns exiting.\n");
        exit(-1);
    }
    memcpy(&new_p[this->num_patterns-1], pattern, sizeof(Pattern_t));
    this->patterns = new_p;
}

void PatternJobs::process()
{
    Pattern_t *pattern = NULL;
    for(size_t p = 0; p < num_patterns; p++)
    {
        pattern = &patterns[p];
        if(pattern->surf != NULL && pattern != NULL)
        {
            pattern->surf->generate();
            if(pattern->net != NULL)
            {
                pattern->net->process(pattern->surf);
            }
            if(pattern->sim != NULL)
            {
                pattern->sim->process(pattern->surf);
            }
        }
    }
}
