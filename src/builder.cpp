#include "builder.h"

surface_ptr Builder::surface_builder(std::string name, rect_t dims)
{
    surface_ptr surf;
    // there has to be a beter way then checking hardcoded names.
    if(name == GETNAME(BouncingDot))
    {
        surf = surface_ptr(new BouncingDot(dims));
        return surf;
    }
    if(name == GETNAME(GraphicsTest))
    {
        surf = surface_ptr(new GraphicsTest(dims));
        return surf;
    }
    return surf;
}

network_ptr Builder::protocol_builder(std::string name, std::string target, uint16_t port)
{
    network_ptr net;
    if(name == GETNAME(Lmcp))
    {
        net = network_ptr(new Lmcp(target.c_str(), port));
        return net;
    }
    return net;
}
