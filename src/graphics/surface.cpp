#include "surface.h"

RGBColor_t *Surface::surface;
rect_t Surface::rect;

Surface::Surface(int width, int height)
{
    this->rect.width = width;
    this->rect.height = height;
    this->rect.size = (this->rect.width * this->rect.height);
    this->create_surface();
}

Surface::Surface(int width, int height, int x, int y)
{
    this->rect.width = width;
    this->rect.height = height;
    this->rect.x = x;
    this->rect.y = y;
    this->rect.size = (this->rect.width * this->rect.height);
    this->create_surface();
};

// cordinate (x, y, z) to 1D pos
// z == color.
size_t Surface::ctop(int x, int y)
{
    return (y * (this->rect.width)) + x;
}

void Surface::write_pixel(int x, int y, RGBColor_t color)
{
    // get index for color.
    int index = this->ctop(x, y);
    this->surface[index] = color;
}

void Surface::read_pixel(int x, int y, RGBColor_t *color)
{
    // get base index.
    int index = this->ctop(x, y);
    color->red = this->surface[index].red;
    color->green = this->surface[index].green;
    color->blue = this->surface[index].blue;
    color->alpha = this->surface[index].alpha;
}

void Surface::create_surface()
{
    // 3 colors. depth is 3.
    this->surface = new RGBColor_t[this->rect.size];
}

rect_t Surface::get_rect()
{
    return this->rect;
}

RGBColor_t *Surface::get_surface()
{
    return this->surface;
}

Surface::~Surface()
{
    if(this->surface)
    {
        delete[] this->surface;
    }
};