#ifndef __LIFE_H__
#define __LIFE_H__

#include <graphics/colors.h>
#include <graphics/surface.h>
#include <graphics/graphics.h>

class Life: public Graphics
{
public:
    Life(rect_t);
    void init(int, int);
    int cells_around(int, int);
    void process();
    void swap_buffers();
    void clear();
    void generate();
private:
    graphics_ptr buffer;

    RGBColor_t color_alive = BLUE;
    RGBColor_t color_dead = BLACK;

    const int surviveAbility = 2;
    const int reproductiveNumber = 3;
};

#endif
