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
    x = std::max(std::min(this->rect.width, x), 0);
    y = std::max(std::min(this->rect.height, y), 0);
    return (y * this->rect.width + x);
}

void Surface::write_pixel(int x, int y, const RGBColor_t &color)
{
    // get index for color.
    const int index = this->ctop(x, y);
    this->surface.get()[index] = color;
}

void Surface::read_pixel(int x, int y, RGBColor_t &color)
{
    // get base index
    const int index = this->ctop(x, y);
    // fill in the colors
    color = this->surface.get()[index];
}

template<typename T> std::shared_ptr<T> make_shared_array(size_t size)
{
   return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

void Surface::create_surface()
{
    const size_t size = this->rect.width * this->rect.height;
    this->surface = make_shared_array<RGBColor_t>(size);
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
    this->surface = surf;
}
