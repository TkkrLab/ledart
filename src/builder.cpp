#include "builder.h"

Surface *surface_builder(const char *name, rect_t dims)
{
    static Surface *surf;
    surf = NULL;
    if(strcmp(GETNAME(BouncingDot), name) == 0)
    {
        surf = new BouncingDot(dims);
        return surf;
    }
    return surf;
}

Network *protocol_builder(const char *name, const char *target, uint16_t port)
{
    static Network *net;
    net = NULL;
    if(strcmp(GETNAME(Lmcp), name) == 0)
    {
        net = new Lmcp(target, port);
        return net;
    }
    return net;
}