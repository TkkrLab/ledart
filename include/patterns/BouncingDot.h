#ifndef __BOUNCINGDOT_H__
#define __BOUNCINGDOT_H__

#include <string.h>
#include <patterns.h>
#include <graphics.h>
#include <colors.h>

Surface *build_BouncingDot();

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