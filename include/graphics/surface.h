#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <new>

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    size_t size;
} rect_t;

typedef struct 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} RGBColor_t;

class Surface
{
public:
    Surface(int, int);
    Surface(int, int, int, int);
    void create_surface();
    rect_t get_rect();
    RGBColor_t *get_surface();
    void write_pixel(int, int, RGBColor_t);
    void read_pixel(int, int, RGBColor_t *);
    size_t ctop(int, int);
    ~Surface();
private:
    static RGBColor_t *surface;
    static rect_t rect;
};

#endif