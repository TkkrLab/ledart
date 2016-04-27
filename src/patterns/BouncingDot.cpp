#include "BouncingDot.h"

BouncingDot::BouncingDot(rect_t dims):
Graphics(dims)
{
    this->fill(background_color);
}

void BouncingDot::generate()
{
    rect_t grect = this->get_rect();

    this->draw_pixel(this->posx, this->posy, this->pixel_color);

    this->posx += this->dirx;
    this->posy += this->diry;

    if(this->posx >= (grect.width - 1) || this->posx <= 0)
    {
        this->dirx *= -1;
    }
    if(this->posy >= (grect.height - 1) || this->posy <= 0)
    {
        this->diry *= -1;
    }
}
