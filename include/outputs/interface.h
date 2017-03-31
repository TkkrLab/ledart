#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <yaml-cpp/yaml.h>

#include <graphics/surface.h>

class Interface
{
public:
    Interface(){};
    Interface(YAML::Node argnode):
    args(argnode){};
    virtual ~Interface(){};
    
    virtual void open(){};
    virtual void close(){};
    virtual void transmit(uint8_t *, size_t){};
    virtual void process(const surface_ptr &){};
private:
    YAML::Node args;
};

typedef std::unique_ptr<Interface> output_ptr;

#endif
