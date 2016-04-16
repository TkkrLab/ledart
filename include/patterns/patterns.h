#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <string.h>

#include <surface.h>
#include <network.h>

#define GETNAME(X) #X

class Pattern
{
public:
    Pattern();
    Pattern(Surface &, Network &, const char *);
    char *get_name();
    void generate();
    void process();
private:
    static Surface *pattern;
    static Network *network;
    static char name[100];
};

#endif