#ifndef __FFT_H__
#define __FFT_H__

#include <colors.h>
#include <graphics/graphics.h>

class Fft: public Graphics
{
public:
    Fft(rect_t, YAML::Node);
    void generate();
};

#endif
