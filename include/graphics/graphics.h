#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

/* 
    implementation of various shapes and graphics.
*/

#include <memory>
#include <math.h>

#include <mtools.h>
#include <graphics/surface.h>
#include <graphics/colors.h>

class Graphics: public Surface
{
public:
    Graphics();
    Graphics(rect_t);
    Graphics(rect_t, YAML::Node);

    void draw_pixel(int, int, RGBColor_t);
    void xLine(int, int, int, RGBColor_t);
    void yLine(int, int, int, RGBColor_t);
    void draw_circle(int, int, int, int, RGBColor_t);
    void draw_ellipse(int, int, int, int, RGBColor_t);
    void draw_line(int, int, int, int, int, RGBColor_t);
    void draw_rect(int, int, int, int, int, RGBColor_t);
    void draw_bezier(int, int, int, int, int, int, RGBColor_t);
private:
};

typedef std::unique_ptr<Graphics> graphics_ptr;

#endif
