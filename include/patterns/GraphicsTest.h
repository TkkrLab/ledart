#ifndef __GRAPHICSTEST_H__
#define __GRAPHICSTEST_H__

#include <stdlib.h>
#include <time.h>

#include <patterns/patterns.h>
#include <graphics/graphics.h>
#include <graphics/colors.h>
#include <timer.h>


class GraphicsTest: public Graphics
{
public:
    GraphicsTest(rect_t rect, YAML::Node args): Graphics(rect, args){};
    void generate();
private:
};

#endif
