#include "fire.h"

Fire::Fire(rect_t rect, YAML::Node args):
Graphics(rect, args)
{
    Fire::field_t field;
}

void Fire::generate()
{
    static rect_t rect = this->get_rect();
    for(int x = 0; x < rect.width; x++)
    {
        for(int y = 0; y < rect.height; y++)
        {
            this->write_pixel(x, y, BLUE);
        }
    }
}
