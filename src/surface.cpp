#include "surface.h"

int *Surface::surface;
rect_t Surface::rect;

Surface::Surface(int width, int height)
{
    this->rect.width = width;
    this->rect.height = height;
    this->create_surface();
}

Surface::Surface(int width, int height, int x, int y)
{
    this->rect.width = width;
    this->rect.height = height;
    this->rect.x = x;
    this->rect.y = y;
    this->create_surface();
};

// cordinate (x, y, z) to 1D pos
// z == color.
size_t Surface::ctop(int x, int y, int z)
{
    return (x*this->rect.width*this->rect.height+y*this->rect.width+z);
}

void Surface::write_pixel(int x, int y, int *color)
{
    // get index for color.
    int index = this->ctop(x, y, 0);

    this->surface[index] = color[0];
    this->surface[index + 1] = color[1];
    this->surface[index + 2] = color[2];
}

void Surface::read_pixel(int x, int y, int *color)
{
    // get base index.
    int index = this->ctop(x, y, 0);

    color[0] = this->surface[index];
    color[1] = this->surface[index + 1];
    color[2] = this->surface[index + 2];
}

void Surface::create_surface()
{
    this->rect.size = (this->rect.width * this->rect.height);
    // 3 colors. depth is 3.
    this->surface = new int[this->rect.size * 3];
}

rect_t Surface::get_rect()
{
    return this->rect;
}

int *Surface::get_surface()
{
    return this->surface;
}

Surface::~Surface()
{
    delete[] this->surface;
};