#include "graphics/surface.h"

Surface::Surface()
{
    this->rect.width = 0;
    this->rect.height = 0;
    this->rect.x = 0;
    this->rect.y = 0;
}

Surface::Surface(rect_t dims):
rect(dims)
{
    this->create_surface();

    // clear surface.
    RGBColor_t color = {0, 0, 0, 0};
    this->fill(color);
}

Surface::Surface(rect_t dims, YAML::Node args):
Surface(dims)
{
    this->args = args;
}

// fill a surface to a certain color.
void Surface::fill(const RGBColor_t &color)
{
    for(int px = 0; px < this->rect.width; px++)
    {
        for(int py = 0; py < this->rect.height; py++)
        {
            this->write_pixel(px, py, color);
        }
    }
}

// coordinate (x, y) to 1D pos
int Surface::ctop(int x, int y)
{
    if(x < 0 || x > this->rect.width || y < 0 || y > this->rect.height)
        return -1;
    const int index = (y * this->rect.width + x);
    return index;
}

void Surface::write_pixel(int x, int y, const RGBColor_t &color)
{
    // get index for color.
    const int index = this->ctop(x, y);
    if(index != -1)
        this->surface.get()[index] = color;
}

void Surface::read_pixel(int x, int y, RGBColor_t &color)
{
    // get base index
    const int index = this->ctop(x, y);
    if(index != -1)
        color = this->surface.get()[index];
}

void Surface::create_surface()
{
    const int size = this->rect.width * this->rect.height;
    this->surface = source_ptr(new surface_t[size], std::default_delete<surface_t[]>());
}

const YAML::Node Surface::get_args()
{
    return this->args;
}

const rect_t &Surface::get_rect()
{
    return this->rect;
}

source_ptr &Surface::get_surface()
{
    return this->surface;
}

void Surface::set_surface(source_ptr &surf)
{
    this->surface = std::move(surf);
}
