#include "patterns/patterns.h"

void GraphicsTest::generate()
{
    this->fill(BLACK);
    this->draw_circle(10, 10, 0, 10, BLUE);
    this->draw_circle(30, 30, 10, 10, BLUE);
    this->draw_ellipse(40, 40, 20, 15, BLUE);
    this->draw_line(this->get_rect().x, this->get_rect().y, this->get_rect().width, this->get_rect().height, 0, BLUE);
    this->draw_rect(this->get_rect().x, this->get_rect().y, this->get_rect().width, this->get_rect().height, 1, BLUE);
    this->draw_bezier(0, 0, 10, this->get_rect().height - 10, this->get_rect().width, this->get_rect().height, GREEN); 
}
