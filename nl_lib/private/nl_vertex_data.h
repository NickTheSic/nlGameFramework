#ifndef __NL_VERTEX_DATA_H__
#define __NL_VERTEX_DATA_H__

#include "nl_math.h"
#include "nl_colour.h"

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v3f pos;
    colourf color;
};

#endif//__NL_VERTEX_DATA_H__