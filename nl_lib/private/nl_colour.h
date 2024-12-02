#ifndef __NL_COLOUR_H__
#define __NL_COLOUR_H__

#define NL_COLOUR_STRUCT_LAYOUT_RGBA r,g,b,a
#define NL_COLOUR_STRUCT_LAYOUT_ARGB a,r,g,b
#define NL_COLOUR_STRUCT_LAYOUT_AGBR a,g,b,r

#if defined (PSP)
#define NL_COLOUR_STRUCT_LAYOUT a,g,b,r
#else 
#define NL_COLOUR_STRUCT_LAYOUT r,g,b,a
#endif

typedef struct colour colour;
struct colour
{
    union
    {
        struct
        {
            unsigned char NL_COLOUR_STRUCT_LAYOUT;
        };
        unsigned int unsigned_integer;
    };
};

typedef struct colourf colourf;
struct colourf
{
    float NL_COLOUR_STRUCT_LAYOUT;
};

#if defined (PSP)
#define COLOUR_RED (colour){255,0,0,255}
#define COLOURF_RED (colourf){1.f,0.f,0.f,1.f}

#define COLOUR_BLUE (colour){255,255,0,0}
#define COLOURF_BLUE (colourf){1.f,1.f,0.f,0.f}

#define COLOUR_GREEN (colour){255,0,255,0}
#define COLOURF_GREEN (colourf){1.f,0.f,1.f,0.f}

#define COLOUR_WHITE (colour){255,255,255,255}
#define COLOURF_WHITE (colourf){1.f,1.f,1.f,1.f}

#else 
#define COLOUR_RED (colour){255,0,0,255}
#define COLOURF_RED (colourf){1.f,0.f,0.f,1.f}

#define COLOUR_GREEN (colour){0,255,0,255}
#define COLOURF_GREEN (colourf){0.f,1.f,0.f,1.f}

#define COLOUR_BLUE (colour){0,0,255,255}
#define COLOURF_BLUE (colourf){0.f,0.f,1.f,1.f}

#define COLOUR_WHITE (colour){255,255,255,255}
#define COLOURF_WHITE (colourf){1.f,1.f,1.f,1.f}

#endif

#endif//__NL_COLOUR_H__