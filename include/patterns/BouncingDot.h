#ifndef __BOUNCINGDOT_H__
#define __BOUNCINGDOT_H__

#include <string.h>
#include <patterns.h>
#include <graphics.h>
#include <colors.h>

class BouncingDot: public Graphics
{
public:
    BouncingDot(rect_t);
    void generate();
private:
    static int posx, posy;
    static int dirx, diry;
    static RGBColor_t pixel_color;
    static RGBColor_t background_color;
};

#endif