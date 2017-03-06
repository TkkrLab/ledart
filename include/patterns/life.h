#ifndef __LIFE_H__
#define __LIFE_H__

#include <utility>

#include <graphics/colors.h>
#include <graphics/graphics.h>

typedef std::vector<bool> fieldcol_t;
typedef std::vector<fieldcol_t> field_t;

class Life: public Graphics
{
public:
    Life(rect_t, YAML::Node);
    void process_normal();
    void process_progressed();
    void generate();
    void swap_buffers();
    bool new_state(bool, int);
    int cells_around(int, int);
private:
    field_t field;
    field_t buffer;

    int mode = 0;
    int color_step = 1;

    const bool ALIVE = 1;
    const bool DEAD = 0;
    // number needed to survive.
    const int snum = 2;
    // number needed for creation.
    const int rnum = 3;

    RGBColor_t color_alive = BLUE;
    RGBColor_t color_dead = BLACK;
    RGBColor_t cell_color = BLACK;
};

#endif
