#include "patterns/BouncingDot.h"

BouncingDot::BouncingDot(rect_t dims, YAML::Node args):
Graphics(dims, args)
{
    // can we get our own name?
    std::string name = get_arg<std::string>(args["job"], "nope didn't get");
    std::cout << "our name is: " << name << std::endl;

    std::string bgcolorstr = get_arg<std::string>(args["bgcolor"], "BLACK");
    parse_color(bgcolorstr, this->bg_color);
    this->fill(this->bg_color);

    std::string dotcolorstr = get_arg<std::string>(args["dotcolor"], "WHITE");
    parse_color(dotcolorstr, this->dot_color);
}

void BouncingDot::generate()
{
    this->fill(this->bg_color);
    rect_t grect = this->get_rect();

    this->draw_pixel(this->posx, this->posy, this->dot_color);

    this->posx += this->dirx;
    this->posy += this->diry;

    if(this->posx >= (grect.width - 1) || this->posx <= 0)
    {
        this->dirx *= -1;
    }
    if(this->posy >= (grect.height - 1) || this->posy <= 0)
    {
        this->diry *= -1;
    }
}
