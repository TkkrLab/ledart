#ifndef __FIRE_H__
#define __FIRE_H__

#include <graphics/colors.h>
#include <graphics/graphics.h>

typedef std::vector<RGBColor_t> fieldcol_t;
typedef std::vector<fieldcol_t> field_t;

class Fire: public Graphics
{
public:
    Fire(rect_t, YAML::Node);
    void generate();
private:
};


#endif
