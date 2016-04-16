#include "patterns.h"

Surface *Pattern::pattern = NULL;
Network *Pattern::network = NULL;
char Pattern::name[100] = {0};

Pattern::Pattern()
{
}

Pattern::Pattern(Surface &pat, Network &net, const char *name)
{
    this->pattern = &pat;
    this->network = &net;
    strcpy(this->name, name);
}

// generate's new surface data.
void Pattern::generate()
{
    this->pattern->generate();
}

// sends data to network connector.
void Pattern::process()
{
    this->network->process(*this->pattern);
}

char *Pattern::get_name()
{
    return this->name;
}