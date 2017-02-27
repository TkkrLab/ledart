#include "patterns/BouncingDot.h"

BouncingDot::BouncingDot(rect_t dims, YAML::Node args):
Graphics(dims, args)
{
    // for(YAML::const_iterator it=this->get_args().begin(); it != this->get_args().end(); ++it)
    // {
    //     std::cout << "Key: " << it->first.as<std::string>() << " Value: " << it->second.as<std::string>() << std::endl;
    // }

    // can we get our own name?
    std::string name = get_arg<std::string>(args["job"], "nope didn't get");
    std::cout << "our name is: " << name << std::endl;

    std::string str_color = get_arg<std::string>(args["color"], "BLUE");
    std::cout << "std color is: " << str_color << std::endl;

    RGBColor_t color = BLACK;
    parse_color("BLUE", color);
    parse_color("(11, 2, 3)", color);
    parse_color("[111, 2, 23]", color);
    parse_color("(11, 2, 45, 4)", color);
    parse_color("(1)", color);
    parse_color("(1, 2, 3, 4, 5)", color);

    this->fill(BLACK);
}

void BouncingDot::generate()
{
    // this->fill(BLACK);
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
