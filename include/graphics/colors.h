#ifndef __COLORS_H__
#define __COLORS_H__

#include <map>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include <stdint.h>

#include <mtools.h>

#define color_str color_map()

/*
    basic color structure that supports == and != comparisons.
    and instantiation by ({r, g, b, a})
*/
typedef struct RGBColor_t
{
    RGBColor_t():
    red(0), green(0), blue(0), alpha(0){}

    RGBColor_t(const RGBColor_t &&o):
    red(o.red), green(o.green), blue(o.blue), alpha(o.alpha){}
    RGBColor_t(const RGBColor_t &o):
    red(o.red), green(o.green), blue(o.blue), alpha(o.alpha){}
    
    RGBColor_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    red(r), green(g), blue(b), alpha(a){}

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    /*Function to find minimum of x and y*/
    inline int min(int x, int y)
    {
      return y ^ ((x ^ y) & -(x < y));
    }
     
    /*Function to find maximum of x and y*/
    inline int max(int x, int y)
    {
      return x ^ ((x ^ y) & -(x < y)); 
    }

    inline void constrain(int min, int max, RGBColor_t &color)
    {
        // color.red = this->min(max, this->max(min, color.red));
        // color.green = this->min(max, this->max(min, color.red));
        // color.blue = this->min(max, this->max(min, color.red));
        for(int i = 0; i < 3; i++)
        {
            color[i] = (uint8_t)this->min(max, this->max(min, color[i]));
        }

    }
    uint8_t& operator[] (const uint8_t index)
    {
        switch(index)
        {
            case(0):
                return this->red;
                break;
            case(1):
                return this->green;
                break;
            case(2):
                return this->blue;
                break;
            case(3):
                return this->alpha;
                break;
            default:
                throw std::out_of_range ("unknown color.");
                break;
        }
    }

    RGBColor_t &operator=(const RGBColor_t &o)
    {
        if(this != &o)
        {
            this->red = o.red;
            this->green = o.green;
            this->blue = o.blue;
            this->alpha = o.alpha;
        }

        return *this;
    }

    RGBColor_t &operator=(const RGBColor_t &&o)
    {
        if(this != &o)
        {
            this->red = o.red;
            this->green = o.green;
            this->blue = o.blue;
            this->alpha = o.alpha;
        }

        return *this;
    }

    RGBColor_t &operator+=(const int &o)
    {
        this->red += o;
        this->green += o;
        this->blue += o;
        this->constrain(1, 0xfe, *this);
        
        return *this;
    }

    RGBColor_t &operator-=(const int &o)
    {
        this->red -= o;
        this->green -= o;
        this->blue -= o;
        this->constrain(1, 0xfe, *this);
        
        return *this;
    }

    bool operator==(const RGBColor_t &other) const
    {
        bool condition = ((this->red == other.red) &&
                          (this->green == other.green) &&
                          (this->blue == other.blue) &&
                          (this->alpha == other.alpha));
        return condition;
    }

    bool operator!=(const RGBColor_t &other) const
    {
        return !(*this == other);
    }
} RGBColor_t;

std::ostream& operator<<(std::ostream&, const RGBColor_t&);

/* some generic color values. */
#define WHITE       RGBColor_t({0xff, 0xff, 0xff, 0x00})
#define BLACK       RGBColor_t({0x00, 0x00, 0x00, 0x00})
#define GRAY        RGBColor_t({0x80, 0x80, 0x80, 0x00})
#define SILVER      RGBColor_t({0xc0, 0xc0, 0xc0, 0x00})
#define MAROON      RGBColor_t({0x80, 0x00, 0x00, 0x00})
#define RED         RGBColor_t({0xff, 0x00, 0x00, 0x00})
#define OLIVE       RGBColor_t({0x80, 0x80, 0x00, 0x00})
#define YELLOW      RGBColor_t({0xff, 0xff, 0x00, 0x00})
#define GREEN       RGBColor_t({0x00, 0x80, 0x00, 0x00})
#define LIME        RGBColor_t({0x00, 0xff, 0x00, 0x00})
#define TEAL        RGBColor_t({0x00, 0x80, 0x80, 0x00})
#define AQUA        RGBColor_t({0x00, 0xff, 0xff, 0x00})
#define NAVY        RGBColor_t({0x00, 0x00, 0x80, 0x00})
#define BLUE        RGBColor_t({0x00, 0x00, 0xff, 0x00})
#define PURPLE      RGBColor_t({0x80, 0x00, 0x80, 0x00})
#define FUCHSIA     RGBColor_t({0xff, 0x00, 0xff, 0x00})

/* parses input(string) to valid RGBColor_t data */
int parse_color(std::string, RGBColor_t &);
std::map<std::string, RGBColor_t> color_map();

#endif
