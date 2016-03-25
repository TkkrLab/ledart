#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <stdint.h>
#include <stdlib.h>
#include <new>

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    size_t size;
} rect_t;

class Surface
{
public:
    Surface(int, int);
    Surface(int, int, int, int);
    void create_surface();
    rect_t get_rect();
    int *get_surface();
    void write_pixel(int, int, int *);
    void read_pixel(int, int, int *);
    size_t ctop(int, int, int );
    ~Surface();
private:
    // 3D array vector for x, y, color;
    static int *surface;
    static rect_t rect;
};

#endif