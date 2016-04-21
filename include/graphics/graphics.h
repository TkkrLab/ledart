#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

/* 
*/

#include <surface.h>
#include <colors.h>
#include <math.h>

class Graphics: public Surface
{
public:
    Graphics();
    Graphics(rect_t);

    void fill(RGBColor_t);

    void xLine(int, int, int, RGBColor_t);
    void yLine(int, int, int, RGBColor_t);
    void draw_circle(int, int, int, int, RGBColor_t);

    void draw_pixel(int, int, RGBColor_t);
    void draw_line(int, int, int, int, int, RGBColor_t);
    void draw_rect(int, int, int, int, int, RGBColor_t);
private:
};

#endif