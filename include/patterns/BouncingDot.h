#ifndef __BOUNCINGDOT_H__
#define __BOUNCINGDOT_H__

#include <string.h>
#include <patterns/patterns.h>
#include <graphics/graphics.h>
#include <graphics/colors.h>

surface_ptr build_BouncingDot();

class BouncingDot: public Graphics
{
public:
    BouncingDot(rect_t);
    void generate();
private:
    int posx=0, posy=0;
    int dirx=1, diry=1;
    RGBColor_t pixel_color = WHITE;
    RGBColor_t background_color = BLACK;
};

#endif
