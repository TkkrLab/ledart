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

void Pattern::generate()
{
    this->pattern->generate();
}

void Pattern::sendout()
{
    this->network->send(*this->pattern);
}

char *Pattern::get_name()
{
    return this->name;
}