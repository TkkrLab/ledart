#include "graphics/surface.h"

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

Surface::Surface(rect_t dims, YAML::Node args):
Surface(dims)
{
    this->args = args;
}

// fill a surface to a certain color.
void Surface::fill(RGBColor_t color)
{
    static RGBColor_t pre_color;
    for(int px = 0; px < this->rect.width; px++)
    {
        for(int py = 0; py < this->rect.height; py++)
        {
            this->read_pixel(px, py, pre_color);
            if(pre_color != color)
            {
                this->write_pixel(px, py, color);
            }
        }
    }
}

// cordinate (x, y) to 1D pos
size_t Surface::ctop(int x, int y)
{
    x = std::max(std::min(this->rect.width, x), 0);
    y = std::max(std::min(this->rect.height, y), 0);

    size_t index = (y * this->rect.width + x);
    return index;
}

void Surface::write_pixel(int x, int y, RGBColor_t &color)
{
    // x = std::max(std::min(this->rect.width, x), 0);
    // y = std::max(std::min(this->rect.height, y), 0);
    static RGBColor_t pre_color;
    this->read_pixel(x, y, pre_color);
    if(pre_color != color)
    {
        // get index for color.
        const size_t index = this->ctop(x, y);
        this->surface[index] = color;
    }
}

void Surface::read_pixel(int x, int y, RGBColor_t &color)
{
    // x = std::max(std::min(this->rect.width, x), 0);
    // y = std::max(std::min(this->rect.height, y), 0);
    // get base index
    const size_t index = this->ctop(x, y);
    // fill in the colors
    color = this->surface[index];
}

void Surface::create_surface()
{
    const size_t size = this->rect.width * this->rect.height;
    this->surface = new RGBColor_t[size];
    if(this->surface == NULL)
    {
        printf("couldn't create Surface::surface. \n");
        exit(-1);
    }
}

YAML::Node Surface::get_args()
{
    return this->args;
}

rect_t Surface::get_rect()
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

Surface::~Surface()
{
    if(this->surface != NULL)
    {
        delete [] this->surface;
        this->surface = NULL;
    }
}
