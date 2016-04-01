#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <surface.h>
#include <graphics.h>
#include <network.h>
#include <lmcp.h>

#define MATRIX_WIDTH 96
#define MATRIX_HEIGHT 48

char target[] = "127.0.0.1";

class Pattern
{
public:
    static Surface *pattern;
    static Network *network;

    Pattern(Surface &, Network &);
    void generate();
    void sendout();
private:
};

Surface *Pattern::pattern = NULL;
Network *Pattern::network = NULL;

Pattern::Pattern(Surface &pat, Network &net)
{
    this->pattern = &pat;
    this->network = &net;
}

void Pattern::generate()
{
    this->pattern->generate();
}

void Pattern::sendout()
{
    this->network->send(*this->pattern, target);
}

class BouncingDot: public Graphics
{
public:
    BouncingDot();
    void generate();
private:
    static int posx, posy;
    static int dirx, diry;
    static RGBColor_t pixel_color;
    static RGBColor_t background_color;
};

int BouncingDot::posx = 0;
int BouncingDot::posy = 0;
int BouncingDot::dirx = 0;
int BouncingDot::diry = 0;
RGBColor_t BouncingDot::pixel_color = {0xff, 0xff, 0xff};
RGBColor_t BouncingDot::background_color = {0x00, 0x00, 0x00};

BouncingDot::BouncingDot():
Graphics(MATRIX_WIDTH, MATRIX_HEIGHT)
{
};

void BouncingDot::generate()
{
    rect_t grect = Graphics::get_rect();
    if(posx > (grect.width - 1) or posx <= 0)
    {
        dirx *= -1;
    }
    if(posy > (grect.height - 1) or posy <= 0)
    {
        diry *= -1;
    }

    this->draw_pixel(0, 0, this->pixel_color);
}

void process(Pattern pattern)
{
    // generate a new frame
    pattern.generate();
    // send it out on the coupled network.
    pattern.sendout();
};

int main(int argc, char **argv)
{
    BouncingDot testdot = BouncingDot();
    Lmcp network = Lmcp();
    Pattern testpattern = Pattern(testdot, network);
    
    process(testpattern);

    return 0;
}