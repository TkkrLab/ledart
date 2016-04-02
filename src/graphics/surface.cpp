#include "surface.h"
#include <stdio.h>

RGBColor_t *Surface::surface = NULL;
rect_t Surface::rect;

Surface::Surface()
{
    this->rect.width = 1;
    this->rect.height = 1;
    this->rect.x = 0;
    this->rect.y = 0;
    this->rect.size = (this->rect.width * this->rect.height);
}

Surface::Surface(rect_t dims)
{
    // this->rect.width = width;
    // this->rect.height = height;
    // this->rect.size = (this->rect.width * this->rect.height);
    memcpy(&this->rect, &dims, sizeof(dims));
    this->create_surface();
}

// cordinate (x, y, z) to 1D pos
// z == color.
size_t Surface::ctop(int x, int y)
{
    return (y * (this->rect.width)) + x;
}

void Surface::write_pixel(int x, int y, RGBColor_t color)
{
    if(x > (this->rect.width - 1) || x < 0)
    {
        return;
    }
    if(y > (this->rect.height - 1) || y < 0)
    {
        return;
    }
    // get index for color.
    int index = this->ctop(x, y);
    this->surface[index] = color;
}

void Surface::read_pixel(int x, int y, RGBColor_t *color)
{
    if(x > (this->rect.width - 1) || x < 0)
    {
        return;
    }
    if(y > (this->rect.height - 1) || y < 0)
    {
        return;
    }
    // get base index
    int index = this->ctop(x, y);
    color->red = this->surface[index].red;
    color->green = this->surface[index].green;
    color->blue = this->surface[index].blue;
    color->alpha = this->surface[index].alpha;
}

void Surface::generate()
{

}

void Surface::create_surface()
{
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
    if(this->surface != NULL)
    {
        delete [] this->surface;
    }
}