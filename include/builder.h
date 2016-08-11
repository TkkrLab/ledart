#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <mtools.h>
#include <graphics/surface.h>
#include <patterns/patterns.h>

typedef void(*build_handler)(const char *, rect_t);

class Builder
{
public:
    Surface *surface_builder(const char *, rect_t);
    Network *protocol_builder(const char *, const char *, uint16_t);
    void register_builder(build_handler);
private:

};

#endif