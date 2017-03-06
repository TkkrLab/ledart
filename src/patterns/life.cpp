#include "patterns/patterns.h"

Life::Life(rect_t rect, YAML::Node args):
Graphics(rect, args)
{
    this->field.resize(rect.width);
    this->buffer.resize(rect.width);
    for(fieldcol_t &row: this->field)
    {
        row.resize(rect.height);
    }
    for(fieldcol_t &row: this->buffer)
    {
        row.resize(rect.height);
    }

    // int x = 0;
    // int y = 0;
    // this->draw_pixel(x + 1, y + 0, this->color_alive);
    // this->draw_pixel(x + 2, y + 1, this->color_alive);
    // this->draw_pixel(x + 0, y + 2, this->color_alive);
    // this->draw_pixel(x + 1, y + 2, this->color_alive);
    // this->draw_pixel(x + 2, y + 2, this->color_alive);

    RGBColor_t color = BLACK;
    parse_color(get_arg<std::string>(args["acolor"], "BLUE"), color);
    this->color_alive = color;

    parse_color(get_arg<std::string>(args["dcolor"], "BLACK"), color);
    this->color_dead = color;

    this->color_step = get_arg<int>(args["cstep"], 1);

    this->mode = get_arg<int>(args["mode"], 0);

    for(int x = 0; x < rect.width; x++)
    {
        for(int y = 0; y < rect.height; y++)
        {
            bool state = (rand() % 2) ? ALIVE : DEAD;
            this->field[x][y] = state;
            if(state)
                this->draw_pixel(x, y, this->color_alive);
            else
                this->draw_pixel(x, y, this->color_dead);
        }
    }
}

void Life::swap_buffers()
{
    this->field.swap(this->buffer);
}

bool Life::new_state(bool current, int neighbors)
{
    if((current == this->ALIVE) && (neighbors < this->snum || neighbors > this->rnum))
    {
        return this->DEAD;
    }
    if((current == this->DEAD) && neighbors == this->rnum)
    {
        return this->ALIVE;
    }
    return current;
}

int Life::cells_around(int x, int y)
{
    static rect_t rect = this->get_rect();
    static int nx = 0;
    static int ny = 0;
    int n = 0;

    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            nx = (x + i + rect.width) % rect.width;
            ny = (y + j + rect.height) % rect.height;
            n += (this->field[nx][ny] == this->ALIVE) ? 1 : 0;
        }
    }
    if(this->field[x][y] == this->ALIVE)
        n--;

    return n;
}

void Life::process_normal()
{
    static rect_t rect = this->get_rect();
    static bool state;
    static int around;

    for(int x = 0; x < rect.width; x++)
    {
        for(int y = 0; y < rect.height; y++)
        {
            around = this->cells_around(x, y);
            state = this->new_state(this->field[x][y], around);
            if(state)
                this->draw_pixel(x, y, this->color_alive);
            else
                this->draw_pixel(x, y, this->color_dead);
            this->buffer[x][y] = state;
        }
    }
    this->swap_buffers();
}

void Life::process_progressed()
{
    static rect_t rect = this->get_rect();
    static bool state;
    static int around;
    static RGBColor_t color;

    for(int x = 0; x < rect.width; x++)
    {
        for(int y = 0; y < rect.height; y++)
        {
            around = this->cells_around(x, y);
            state = this->new_state(this->field[x][y], around);

            this->read_pixel(x, y, color);
            if(state)
            {
                color += this->color_step;
            }
            else
            {
                color -= this->color_step;
            }
            this->draw_pixel(x, y, color);
            
            this->buffer[x][y] = state;
        }
    }
    this->swap_buffers();
}

void Life::generate()
{
    switch(mode)
    {
        case 0:
            this->process_normal();
            break;
        case 1:
            this->process_progressed();
            break;
    };
}
