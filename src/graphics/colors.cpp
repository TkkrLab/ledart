#include "graphics/colors.h"

std::ostream& operator<< (std::ostream& os, const RGBColor_t& color) {
    os << "RGBColor_t(" << int(color.red) << ", " <<
                           int(color.green) << ", " <<
                           int(color.blue) << ", " <<
                           int(color.alpha) <<
                           ")";
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

// modifies original string beware.
std::string &strip_tokens(std::string &str, std::string delims)
{
    for(char &delim: delims)
    {
        std::string::iterator end_pos = std::remove(str.begin(), str.end(), delim);
        str.erase(end_pos, str.end());
    }
    return str;
}

std::vector<std::string> split_str(std::string &str, std::string delims)
{
    std::string buffer;
    std::istringstream ss(str);
    std::vector<std::string> tokens;

    for(char &delim: delims)
    {
        while(std::getline(ss, buffer, delim))
        {
            tokens.push_back(buffer);
        }
    }

    return tokens;
}

#define COLOR_PARSE_OK 0
#define COLOR_PARSE_FAIL 1


/*
    RGBColor_t color = BLACK;
    parse_color("BLUE", color);
    std::cout << "color now: " << color << std::endl;
    parse_color("(11, 2, 3)", color);
    std::cout << "color now: " << color << std::endl;
    parse_color("[111, 2, 23]", color);
    std::cout << "color now: " << color << std::endl;
    parse_color("(11, 2, 45, 4)", color);
    std::cout << "color now: " << color << std::endl;
    parse_color("(1)", color);
    std::cout << "color now: " << color << std::endl;
    parse_color("(1, 2, 3, 4, 5)", color);
    std::cout << "color now: " << color << std::endl;
    // also hexadecimal ? 
    parse_color("(0x10, 0x20, 0x30, 0x40)", color);
    std::cout << "color now: " << color << std::endl;
*/

/* returns 0 on succes and !0 on error. */
int parse_color(std::string colorstr, RGBColor_t &color)
{
    strip_tokens(colorstr, " ");
    /* colors in () or in [] */
    if((colorstr[0] == '(' && colorstr[colorstr.size() - 1] == ')') || (colorstr[0] == '[' && colorstr[colorstr.size() - 1] == ']'))
    {
        size_t numcommas = std::count(colorstr.begin(), colorstr.end(), ',');
        /* either with 3 or 4 values. like (r, g, b) or (r, g, b, a) */
        if(numcommas == 2 || numcommas == 3)
        {
            strip_tokens(colorstr, "()[]");
            std::vector<std::string> color_strs = split_str(colorstr, ",");

            color.red = std::stoi(color_strs[0], nullptr, 0);
            color.green = std::stoi(color_strs[1], nullptr, 0);
            color.blue = std::stoi(color_strs[2], nullptr, 0);
            if(numcommas == 3)
                color.alpha = std::stoi(color_strs[3], nullptr, 0);

            return COLOR_PARSE_OK;
        }

        return COLOR_PARSE_FAIL;
    }
    /* or when it's a know string value in colors. */
    else if(alpha_str(colorstr))
    {
        std::transform(colorstr.begin(), colorstr.end(),colorstr.begin(), ::toupper);
        if(color_map().count(colorstr) > 0)
        {
            color = color_map()[colorstr];
            return COLOR_PARSE_OK;
        }
        return COLOR_PARSE_FAIL;
    }

    return COLOR_PARSE_FAIL;
}
