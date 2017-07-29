#ifndef __FFT_H__
#define __FFT_H__

#include <colors.h>
#include <graphics/graphics.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <fftw3.h>
#include <math.h>

class Fft: public Graphics
{
public:
    Fft(rect_t rect, YAML::Node args):
    Graphics(rect, args){}

    void generate(){};
};

#endif
