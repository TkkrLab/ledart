#include "graphics/graphics.h"

#include <stdio.h>

static RGBColor_t bg = BLACK;

Graphics::Graphics()
:Surface()
{
    this->fill(bg);
}

Graphics::Graphics(rect_t dims)
:Surface(dims)
{
    this->fill(bg);
}

void Graphics::draw_pixel(int x, int y, RGBColor_t color)
{
    Surface::write_pixel(x, y, color);
}

void Graphics::xLine(int x1, int x2, int y, RGBColor_t color)
{
    while (x1 <= x2)
    {
        this->draw_pixel(x1, y, color);
        x1++;
    }
}

void Graphics::yLine(int x, int y1, int y2, RGBColor_t color)
{
    while (y1 <= y2)
    {
        this->draw_pixel(x, y1, color);
        y1++;
    }
}

// making inner 0 and outer radius you can fill the whole circle.
void Graphics::draw_circle(int xc, int yc, int inner, int outer, RGBColor_t color)
{
    int xo = outer;
    int xi = inner;
    int y = 0;
    int erro = 1 - xo;
    int erri = 1 - xi;

    while(xo >= y) {
        this->xLine(xc + xi, xc + xo, yc + y,  color);
        this->yLine(xc + y,  yc + xi, yc + xo, color);
        this->xLine(xc - xo, xc - xi, yc + y,  color);
        this->yLine(xc - y,  yc + xi, yc + xo, color);
        this->xLine(xc - xo, xc - xi, yc - y,  color);
        this->yLine(xc - y,  yc - xo, yc - xi, color);
        this->xLine(xc + xi, xc + xo, yc - y,  color);
        this->yLine(xc + y,  yc - xo, yc - xi, color);

        y++;

        if (erro < 0) {
            erro += 2 * y + 1;
        } else {
            xo--;
            erro += 2 * (y - xo + 1);
        }

        if (y > inner) {
            xi = y;
        } else {
            if (erri < 0) {
                erri += 2 * y + 1;
            } else {
                xi--;
                erri += 2 * (y - xi + 1);
            }
        }
    }
}

void Graphics::draw_line(int x0, int y0, int x1, int y1, int wd, RGBColor_t color)
{                                    /* plot an anti-aliased line of width wd */
   int dx = abs(x1-x0), sx = x0 < x1 ? 1 : -1; 
   int dy = abs(y1-y0), sy = y0 < y1 ? 1 : -1; 
   int err = dx-dy, e2, x2, y2;                           /* error value e_xy */
   float ed = dx+dy == 0 ? 1 : sqrt((float)dx*dx+(float)dy*dy);
                                                       
   for (wd = (wd+1)/2; ; ) {                                    /* pixel loop */
      this->draw_pixel(x0, y0, color);
      e2 = err; x2 = x0;
      if (2*e2 >= -dx) {                                            /* x step */
         for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx)
            this->draw_pixel(x0, y2 += sy, color);
         if (x0 == x1) break;
         e2 = err; err -= dy; x0 += sx; 
      } 
      if (2*e2 <= dy) {                                             /* y step */
         for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy)
            this->draw_pixel(x2 += sx, y0, color);
         if (y0 == y1) break;
         err += dx; y0 += sy; 
      }
   }
}

// setting thickness to 0 fills the rect.
void Graphics::draw_rect(int x, int y, int width, int height, int thickness, RGBColor_t color)
{
    if(thickness <= 0)
    {
        for(int yo = 0; yo < height; yo++)
        {
            this->draw_line(x, y + yo, x + width - 1, y + yo, 0, color);
        }
    }
    else
    {
        for(int xo = 0; xo < thickness; xo++)
        {
            for(int yo = 0; yo < thickness; yo++)
            {
                // upper line
                this->draw_line(x, y + yo, x + width - 1, y + yo, 0, color);

                // lower line
                this->draw_line(x, y + height - 1 - yo, x + width - 1, y + height - 1 - yo, 0, color);

                // left line
                this->draw_line(x + xo, y, x + xo, y + height - 1, 0, color);

                // right line
                this->draw_line(x + width - 1 - xo, y, x + width - 1 - xo, y + height - 1, 0, color);
            }
        }
    }
}


void Graphics::draw_ellipse(int xc, int yc, int width, int height, RGBColor_t color)
{
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    /* first half */
    for (x = 0, y = height, sigma = 2 * b2 + a2 * (1 - 2 * height); b2 * x <= a2 * y; x++)
    {
        this->draw_pixel(xc + x, yc + y, color);
        this->draw_pixel(xc - x, yc + y, color);
        this->draw_pixel(xc + x, yc - y, color);
        this->draw_pixel(xc - x, yc - y, color);
        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    /* second half */
    for (x = width, y = 0, sigma = 2 * a2 + b2 * (1 - 2 * width); a2 * y <= b2 * x; y++)
    {
        this->draw_pixel(xc + x, yc + y, color);
        this->draw_pixel(xc - x, yc + y, color);
        this->draw_pixel(xc + x, yc - y, color);
        this->draw_pixel(xc - x, yc - y, color);
        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
}

void Graphics::draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2, RGBColor_t color)
{                            
    int sx = x2-x1, sy = y2-y1;
    long xx = x0-x1, yy = y0-y1, xy;         /* relative values for checks */
    double dx, dy, err, cur = xx*sy-yy*sx;                    /* curvature */

    if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) { /* begin with longer part */ 
        x2 = x0; x0 = sx+x1; y2 = y0; y0 = sy+y1; cur = -cur;  /* swap P0 P2 */
    }  
    if (cur != 0) {                                    /* no straight line */
        xx += sx; xx *= sx = x0 < x2 ? 1 : -1;           /* x step direction */
        yy += sy; yy *= sy = y0 < y2 ? 1 : -1;           /* y step direction */
        xy = 2*xx*yy; xx *= xx; yy *= yy;          /* differences 2nd degree */
        if (cur*sx*sy < 0) {                           /* negated curvature? */
            xx = -xx; yy = -yy; xy = -xy; cur = -cur;
        }
        dx = 4.0*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
        dy = 4.0*sx*cur*(y0-y1)+yy-xy;
        xx += xx; yy += yy; err = dx+dy+xy;                /* error 1st step */    
        do {                              
            this->write_pixel(x0,y0, color);                                     /* plot curve */
            if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
            y1 = 2*err < dx;                  /* save value for test of y step */
            if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
            if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
        } while (dy < 0 && dx > 0);   /* gradient negates -> algorithm fails */
    }
    this->draw_line(x0, y0, x2, y2, 1, color);                  /* plot remaining part to end */
}  
