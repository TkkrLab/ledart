#include "surface.h"

Surface::Surface()
{
    this->rect.width = 1;
    this->rect.height = 1;
    this->rect.x = 0;
    this->rect.y = 0;
}

Surface::Surface(rect_t dims)
{
    memcpy(&this->rect, &dims, sizeof(dims));
    this->create_surface();
    // clear surface.
    RGBColor_t color = {0, 0, 0, 0};
    this->fill(color);
}

// fill a surface to a certain color.
void Surface::fill(RGBColor_t color)
{
    for(int px = 0; px < this->rect.width; px++)
    {
        for(int py = 0; py < this->rect.height; py++)
        {
            this->write_pixel(px, py, color);
        }
    }
}

// cordinate (x, y) to 1D pos
size_t Surface::ctop(int x, int y)
{
    return y * this->rect.width + x;
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
    size_t index = this->ctop(x, y);
    // fill in the colors
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
    size_t size = this->rect.width * this->rect.height;
    this->surface = new RGBColor_t[size];
    if(this->surface == NULL)
    {
        printf("couldn't create Surface::surface. \n");
        exit(-1);
    }
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
    printf("calling deconstructor: \n");
    if(this->surface != NULL)
    {
        delete [] this->surface;
        this->surface = NULL;
    }
}