#include "builder.h"

surface_ptr Builder::surface_builder(std::string name, rect_t dims, YAML::Node args)
{
    surface_ptr surf;
    // there has to be a beter way then checking hardcoded names.
    if(name == GETNAME(BouncingDot))
    {
        surf = surface_ptr(new BouncingDot(dims, args));
        return surf;
    }
    if(name == GETNAME(GraphicsTest))
    {
        surf = surface_ptr(new GraphicsTest(dims, args));
        return surf;
    }
    if(name == GETNAME(Life))
    {
        surf = surface_ptr(new Life(dims, args));
        return surf;
    }
    if(name == GETNAME(Fft))
    {
        surf = surface_ptr(new Fft(dims, args));
        return surf;
    }
    if(name == GETNAME(Fire))
    {
        surf = surface_ptr(new Fire(dims, args));
        return surf;
    }
    return surf;
}

output_ptr Builder::protocol_builder(std::string name, YAML::Node args)
{
    output_ptr net;
    if(name == GETNAME(Lmcp))
    {
        net = output_ptr(new Lmcp(args));
        return net;
    }
    return net;
}
