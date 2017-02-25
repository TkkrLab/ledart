#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <mtools.h>
#include <graphics/surface.h>
#include <patterns/patterns.h>

typedef void(*build_handler)(const std::string, rect_t);

class Builder
{
public:
    surface_ptr surface_builder(std::string, rect_t, YAML::Node);
    network_ptr protocol_builder(std::string, std::string, uint16_t);
    void register_builder(build_handler);
private:

};

#endif
