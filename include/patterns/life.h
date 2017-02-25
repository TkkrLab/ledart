#ifndef __LIFE_H__
#define __LIFE_H__

#include <utility>

#include <graphics/colors.h>
#include <graphics/surface.h>
#include <graphics/graphics.h>

class Life: public Graphics
{
public:
    Life(rect_t);
    void process();
    void generate();
    void init(int, int);
    void swap_buffers();
    RGBColor_t new_state(RGBColor_t, int);
    int cells_around(int, int);
private:
    graphics_ptr buffer;

    RGBColor_t color_alive = BLUE;
    RGBColor_t color_dead = BLACK;

    const int surviveAbility = 2;
    const int reproductiveNumber = 3;
};

#endif
