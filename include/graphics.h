#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

/* 
*/

#include <surface.h>
#include <math.h>

class Graphics: public Surface
{
public:
    Graphics(int, int);
    Graphics(int, int, int, int);

    void xLine(int, int, int, int *);
    void yLine(int, int, int, int *);
    void draw_circle(int, int, int, int, int *);

    void draw_pixel(int, int, int *);
    void draw_line(int, int, int, int, int, int *);
    void draw_rect(int, int, int, int, int, int *);
private:
};

#endif