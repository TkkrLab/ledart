#include "graphics/colors.h"

// ostream& operator<< (ostream& os, const RGBColor_t& obj) {
//     os << "obj.getXYZ() << obj.getABC()" << '\n';
//     return os;
// }

std::map<std::string, RGBColor_t> color_map()
{
    static std::map<std::string, RGBColor_t> colors = {{"WHITE", WHITE},
                                                       {"BLACK", BLACK},
                                                       {"GRAY", GRAY},
                                                       {"SILVER", SILVER},
                                                       {"MAROON", MAROON},
                                                       {"RED", RED},
                                                       {"OLIVE", OLIVE},
                                                       {"YELLOW", YELLOW},
                                                       {"GREEN", GREEN},
                                                       {"LIME", LIME},
                                                       {"TEAL", TEAL},
                                                       {"AQUA", AQUA},
                                                       {"NAVY", NAVY},
                                                       {"BLUE", BLUE},
                                                       {"PURPLE", PURPLE},
                                                       {"FUCHSIA", FUCHSIA}};
    return colors;
}

bool alpha_str(const std::string &str)
{
    for(size_t i = 0; i < str.size(); i++)
    {
        if( !isalpha(str[i]) || !isspace(str[i]))
        {
            return true;
        }
    }
    return false;
}

/* returns 0 on succes and !0 on error. */
int parse_color(std::string colorstr, RGBColor_t &color)
{
    UNUSED(color);
    std::string::iterator end_pos = std::remove(colorstr.begin(), colorstr.end(), ' ');
    colorstr.erase(end_pos, colorstr.end());

    /* colors in () or in [] */
    if((colorstr[0] == '(' && colorstr[colorstr.size() - 1] == ')') || (colorstr[0] == '[' && colorstr[colorstr.size() - 1] == ']'))
    {
        int numcommas = 0;
        for(size_t i = 0; i < colorstr.size(); i++)
        {
            if(colorstr[i] == ',')
                numcommas++;
        }
        /* either with 3 or 4 values. like (r, g, b) or (r, g, b, a) */
        if(numcommas == 2 || numcommas == 3)
        {
            std::cout << "this is a valid color: " << colorstr << std::endl;
            return 0;
        }

        std::cout << "this is not a valid color: " << colorstr << std::endl;
        return 1;
    }
    /* or when it's a know string value in colors. */
    else if(alpha_str(colorstr) && (color_map().count(colorstr) > 0))
    {
        RGBColor_t new_color = color_map()[colorstr];
        // new_color = ;
        return 0;
    }
    return 1;
}
