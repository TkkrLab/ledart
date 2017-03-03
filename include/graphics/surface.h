#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <new>
#include <memory>
#include <vector>
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

typedef std::shared_ptr<RGBColor_t> source_ptr;

/*
    use like: variable = get_arg(YAML::Node["field"], "default value")
    where:
        variable is of the same type as the default value.
*/
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

    const rect_t &get_rect();
    const YAML::Node get_args();
    source_ptr &get_surface();
    void set_surface(source_ptr &);

    void write_pixel(int, int, const RGBColor_t &);
    void read_pixel(int, int, RGBColor_t &);
    void fill(const RGBColor_t &);
    int ctop(int, int);

    // virtual generate for derived classes that override.
    virtual void generate(){};

    virtual ~Surface() = default;

private:
    YAML::Node args;
    source_ptr surface;
    rect_t rect;
};

typedef std::unique_ptr<Surface> surface_ptr;

#endif
