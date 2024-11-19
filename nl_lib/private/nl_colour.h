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

#define COLOUR_RED  (colour){255,0,0,255}
#define COLOURF_RED (colourf){1.f,0.f,0.f,1.f}

#define COLOUR_GREEN  (colour){0,255,0,255}
#define COLOURF_GREEN (colourf){0.f,1.f,0.f,1.f}

#define COLOUR_BLUE  (colour){0,0,255,255}
#define COLOURF_BLUE (colourf){0.f,0.f,1.f,1.f}

#define COLOUR_WHITE  (colour){255,255,255,255}
#define COLOURF_WHITE (colourf){1.f,1.f,1.f,1.f}

#endif//__NL_COLOUR_H__