#ifndef __COLORS_H__
#define __COLORS_H__

#include <memory>
#include <stdint.h>

typedef struct RGBColor_t
{
    RGBColor_t():
    red(0), green(0), blue(0), alpha(0){}
    
    RGBColor_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    red(r), green(g), blue(b), alpha(a){}
    
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

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} RGBColor_t;

typedef std::shared_ptr<RGBColor_t> RGBColor_ptr;

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

#endif
