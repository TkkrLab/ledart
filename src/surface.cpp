#include "surface.h"

int ***Surface::surface;
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

void Surface::write_pixel(int x, int y, int *color)
{
    this->surface[x][y][0] = color[0];
    this->surface[x][y][1] = color[1];
    this->surface[x][y][2] = color[2];
}

void Surface::read_pixel(int x, int y, int *color)
{
    // return this->surface[x][y];
    color[0] = this->surface[x][y][0];
    color[1] = this->surface[x][y][1];
    color[2] = this->surface[x][y][2];
}

void Surface::create_surface()
{
    int x, y, width, height;
    x = this->rect.x;
    y = this->rect.y;
    width = this->rect.width;
    height = this->rect.height;

    this->surface = new int**[width];
    for(int x = 0; x < width; x++){
       this->surface[x] = new int*[height];
       
       for(int y = 0; y < height; y++){
           this->surface[x][y] = new int[3];
           
           for(int z = 0; z < 3; z++){
              this->surface[x][y][z] = 0;
           }
       }
    }
}

rect_t Surface::get_rect()
{
    return this->rect;
}

int ***Surface::get_surface()
{
    return this->surface;
}

Surface::~Surface(){};