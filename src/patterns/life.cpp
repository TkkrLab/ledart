#include "patterns/patterns.h"

Life::Life(rect_t rect, YAML::Node):
Graphics(rect)
{
    this->buffer = graphics_ptr(new Graphics(rect));
    this->fill(BLACK);
    this->buffer->fill(BLACK);

    // int x = 0;
    // int y = 0;
    // this->draw_pixel(x + 1, y + 0, this->color_alive);
    // this->draw_pixel(x + 2, y + 1, this->color_alive);
    // this->draw_pixel(x + 0, y + 2, this->color_alive);
    // this->draw_pixel(x + 1, y + 2, this->color_alive);
    // this->draw_pixel(x + 2, y + 2, this->color_alive);
    for(int x = 0; x < this->get_rect().width; x++)
    {
        for(int y = 0; y < this->get_rect().height; y++)
        {
            RGBColor_t color = rand()%2 ? this->color_alive : this->color_dead;
            this->draw_pixel(x, y, color);
        }
    }
}

void Life::swap_buffers()
{
    // get and set surface deal with references.
    // so we swap the references to the surfaces.
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
            this->read_pixel(x, y, color);

            around = this->cells_around(x, y);
            color = this->new_state(color, around);
            this->buffer->write_pixel(x, y, color);
        }
    }
    this->swap_buffers();
}

RGBColor_t Life::new_state(RGBColor_t current, int neighbors)
{
    if(current == this->color_alive && (neighbors < 2 || neighbors > 3))
    {
        return this->color_dead;
    }
    if(current == this->color_dead && neighbors == 3)
    {
        return this->color_alive;
    }
    return current;
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
