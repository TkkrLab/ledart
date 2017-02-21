#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

/* 
    implementation of various shapes a graphics.
*/

#include <math.h>
#include <mtools.h>
#include <graphics/surface.h>
#include <graphics/colors.h>

class Graphics: public Surface
{
public:
    Graphics();
    Graphics(rect_t);

    void draw_pixel(int, int, RGBColor_t);
    void xLine(int, int, int, RGBColor_t);
    void yLine(int, int, int, RGBColor_t);
    void draw_circle(int, int, int, int, RGBColor_t);
    void draw_elipse(int, int, int, int, RGBColor_t);
    void draw_line(int, int, int, int, int, RGBColor_t);
    void draw_rect(int, int, int, int, int, RGBColor_t);
private:
};

#endif
