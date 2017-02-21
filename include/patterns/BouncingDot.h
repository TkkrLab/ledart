#ifndef __BOUNCINGDOT_H__
#define __BOUNCINGDOT_H__

#include <patterns/patterns.h>
#include <graphics/graphics.h>
#include <graphics/colors.h>

class BouncingDot: public Graphics
{
public:
    BouncingDot(rect_t);
    void generate();
private:
    int posx=0, posy=0;
    int dirx=1, diry=1;
};

#endif
