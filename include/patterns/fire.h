#ifndef __FIRE_H__
#define __FIRE_H__

#include <utility>

#include <graphics/colors.h>
#include <graphics/graphics.h>

class Fire: public Graphics
{
public:
    typedef std::vector<RGBColor_t> fieldcol_t;
    typedef std::vector<fieldcol_t> field_t;
    Fire(rect_t, YAML::Node);
    void generate();
private:
};


#endif
