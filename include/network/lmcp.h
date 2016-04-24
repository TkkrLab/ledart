#ifndef __LMCP_H__
#define __LMCP_H__

#include <surface.h>
#include <network.h>

class Lmcp: public Network
{
public:
    Lmcp(const char *target=NULL, uint16_t port=1337);
    void process(Surface *);
    void send_command(uint8_t);
private:
    static const uint8_t WRITE_BUFF = 0x01;
    static const uint8_t CLEAR = 0x02;
    static const uint8_t DRAW_ROWS = 0x10;
    static const uint8_t DRAW_IMG_RECT = 0x11;
    static const uint8_t WRITE_TEXT_LN_BASED = 0x20;
    static const uint8_t WRITE_TEXT_ABSOLUTE = 0x21;
};

#endif