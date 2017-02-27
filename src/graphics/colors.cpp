#include "graphics/colors.h"

std::ostream& operator<< (std::ostream& os, const RGBColor_t& color) {
    os << "RGBColor_t(" << int(color.red) << ", " <<
                           int(color.green) << ", " <<
                           int(color.blue) << ", " <<
                           int(color.alpha) <<
                           ")" << std::endl;
    return os;
}

inline std::map<std::string, RGBColor_t> color_map()
{
    static std::map<std::string, RGBColor_t> _colors = {{"WHITE", WHITE},
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
    return _colors;
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

#define COLOR_PARSE_OK 0
#define COLOR_PARSE_FAIL 1

/* returns 0 on succes and !0 on error. */
int parse_color(std::string colorstr, RGBColor_t &color)
{
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

        std::string red_str = "";
        std::string green_str = "";
        std::string blue_str = "";
        std::string alpha_str = "";
        /* either with 3 or 4 values. like (r, g, b) or (r, g, b, a) */
        if(numcommas == 2)
        {
            std::cout << "this is a valid color: " << colorstr << std::endl;
            return COLOR_PARSE_OK;
        }
        else if(numcommas == 3)
        {
            return COLOR_PARSE_OK;
        }

        std::cout << "this is not a valid color: " << colorstr << std::endl;
        return COLOR_PARSE_FAIL;
    }
    /* or when it's a know string value in colors. */
    else if(alpha_str(colorstr) && (color_map().count(colorstr) > 0))
    {
        color = color_map()[colorstr];
        return COLOR_PARSE_OK;
    }

    return COLOR_PARSE_FAIL;
}
