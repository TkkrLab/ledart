#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <new>
#include <memory>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <yaml-cpp/yaml.h>

#include <graphics/colors.h>

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} rect_t;

typedef RGBColor_t * source_ptr;

template<class T>
T get_arg(YAML::Node arg, T _default)
{
    if(arg)
    {
        return arg.as<T>();
    }
    return _default;
}

class Surface
{
public:
    Surface();
    Surface(rect_t);
    Surface(rect_t, YAML::Node);

    void create_surface();

    rect_t get_rect();
    YAML::Node get_args();
    source_ptr &get_surface();
    void set_surface(source_ptr &);

    void write_pixel(int, int, RGBColor_t &);
    void read_pixel(int, int, RGBColor_t &);
    void fill(RGBColor_t);
    size_t ctop(int, int);

    // virtual generate for derived classes that override.
    virtual void generate(){};

    ~Surface();
private:
    YAML::Node args;
    RGBColor_t *surface;
    rect_t rect;
};

typedef std::shared_ptr<Surface> surface_ptr;

#endif
