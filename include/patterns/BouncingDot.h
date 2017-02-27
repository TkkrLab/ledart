#ifndef __BOUNCINGDOT_H__
#define __BOUNCINGDOT_H__

#include <iostream>

#include <patterns/patterns.h>
#include <graphics/graphics.h>
#include <graphics/colors.h>

class BouncingDot: public Graphics
{
public:
    BouncingDot(rect_t, YAML::Node);
    void generate();
private:
    RGBColor_t dot_color = WHITE;
    RGBColor_t bg_color = BLACK;
    int posx=0, posy=0;
    int dirx=1, diry=1;
};

#endif
