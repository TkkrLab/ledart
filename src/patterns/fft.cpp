#include "fft.h"

Fft::Fft(rect_t rect, YAML::Node args):
Graphics(rect, args)
{
    // this->fill(BLUE);
}

void Fft::generate()
{
    this->draw_pixel(0, 0, BLUE);
}
