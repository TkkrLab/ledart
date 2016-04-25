#ifndef __BUILDER_H__
#define __BUILDER_H__

#include <mtools.h>
#include <surface.h>
#include <patterns.h>

// include network interfaces here.
// for lack of a better place.
#include <network.h>
#include <lmcp.h>

Surface *surface_builder(const char *, rect_t);
Network *protocol_builder(const char *, const char*, uint16_t);

#endif