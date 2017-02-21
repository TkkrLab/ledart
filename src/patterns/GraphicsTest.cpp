#include "patterns/patterns.h"


GraphicsTest::GraphicsTest(rect_t rect):
Graphics(rect)
{

}


void GraphicsTest::generate()
{
    this->fill(BLACK);
    this->draw_circle(10, 10, 0, 10, BLUE);
    this->draw_line(this->get_rect().x, this->get_rect().y, this->get_rect().width, this->get_rect().height, 0, BLUE);
    this->draw_rect(this->get_rect().x, this->get_rect().y, this->get_rect().width, this->get_rect().height, 1, BLUE);
}
