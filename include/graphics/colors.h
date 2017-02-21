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

#define WHITE  {0xff, 0xff, 0xff, 0x00}
#define BLACK  {0x00, 0x00, 0x00, 0x00}
#define GRAY  {0x80, 0x80, 0x80, 0x00}
#define SILVER  {0xc0, 0xc0, 0xc0, 0x00}
#define MAROON  {0x80, 0x00, 0x00, 0x00}
#define RED  {0xff, 0x00, 0x00, 0x00}
#define OLIVE  {0x80, 0x80, 0x00, 0x00}
#define YELLOW  {0xff, 0xff, 0x00, 0x00}
#define GREEN  {0x00, 0x80, 0x00, 0x00}
#define LIME  {0x00, 0xff, 0x00, 0x00}
#define TEAL  {0x00, 0x80, 0x80, 0x00}
#define AQUA  {0x00, 0xff, 0xff, 0x00}
#define NAVY  {0x00, 0x00, 0x80, 0x00}
#define BLUE  {0x00, 0x00, 0xff, 0x00}
#define PURPLE  {0x80, 0x00, 0x80, 0x00}
#define FUCHSIA  {0xff, 0x00, 0xff, 0x00}

#endif
