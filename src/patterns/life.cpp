#include "patterns/patterns.h"

Life::Life(rect_t rect):
Graphics(rect)
{
    this->buffer = graphics_ptr(new Graphics(rect));
    this->fill(BLACK);
    this->buffer->fill(BLACK);

    int x = 0;
    int y = 0;
    this->draw_pixel(x + 1, y + 0, this->color_alive);
    this->draw_pixel(x + 2, y + 1, this->color_alive);
    this->draw_pixel(x + 0, y + 2, this->color_alive);
    this->draw_pixel(x + 1, y + 2, this->color_alive);
    this->draw_pixel(x + 2, y + 2, this->color_alive);
}

void Life::swap_buffers()
{
    source_ptr temp = this->get_surface();
    this->set_surface(this->buffer->get_surface());
    this->buffer->set_surface(temp);
}

void Life::process()
{
    static int around;
    static RGBColor_t color;

    for(int x = 0; x < this->get_rect().width; x++)
    {
        for(int y = 0; y < this->get_rect().height; y++)
        {
            around = this->cells_around(x, y);
            this->read_pixel(x, y, color);
            if(color == this->color_alive)
            {
                if(around == this->surviveAbility)
                {
                    this->buffer->write_pixel(x, y, this->color_alive);
                }
                else if(around == this->surviveAbility + 1)
                {
                    this->buffer->write_pixel(x, y, this->color_alive);
                }
                else
                {
                    this->buffer->write_pixel(x, y, this->color_dead);
                }
            }
            else
            {
                if(around == this->reproductiveNumber)
                {
                    this->buffer->write_pixel(x, y, this->color_alive);
                }
                else
                {
                    this->buffer->write_pixel(x, y, this->color_dead);
                }
            }
        }
    }
    this->swap_buffers();
}

int Life::cells_around(int x, int y)
{
    int n = 0;
    int nx = 0;
    int ny = 0;
    RGBColor_t color;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            nx = (x + i + this->get_rect().width) % this->get_rect().width;
            ny = (y + j + this->get_rect().height) % this->get_rect().height;
            this->read_pixel(nx, ny, color);
            if(color == this->color_alive)
                n++;
        }
    }
    this->read_pixel(x, y, color);
    if(color == this->color_alive)
        n--;

    return n;
}

void Life::generate()
{
    this->process();
}
