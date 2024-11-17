#ifndef __NL_COLOUR_H__
#define __NL_COLOUR_H__

typedef struct colour colour;
struct colour
{
    unsigned char r,g,b,a;
};

typedef struct colourf colourf;
struct colourf
{
    float r,g,b,a;
};

#endif//__NL_COLOUR_H__