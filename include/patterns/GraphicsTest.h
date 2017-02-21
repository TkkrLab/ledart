#ifndef __GRAPHICSTEST_H__
#define __GRAPHICSTEST_H__

#include <patterns/patterns.h>
#include <graphics/graphics.h>
#include <graphics/colors.h>

class GraphicsTest: public Graphics
{
public:
    GraphicsTest(rect_t);
    void generate();
private:
};

#endif
