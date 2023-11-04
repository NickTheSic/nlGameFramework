#include "nl_lib.h"
#include "nl_gl.h"

int flip_flop = 0;
float r = 0.0f;

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v2f pos;
    colourf color;
};

typedef struct AtrributePtrData AtrributePtrData;
struct AtrributePtrData
{
    GLuint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* offset;
};

void app_specific_init()
{
    // gl stuff to init
    {
        #define ATTRIBUTE_COUNT 2
        AtrributePtrData attrib_data[ATTRIBUTE_COUNT];
        // vertex pos
        {
            AtrributePtrData* ad0 = &attrib_data[0];
            ad0->size = 2;
            ad0->type = GL_FLOAT;
            ad0->normalized = GL_FALSE;
            ad0->stride = sizeof(vertex_data);
            ad0->offset = (void*)0;

            AtrributePtrData* ad1 = &attrib_data[1];
            ad1->size = 4;
            ad1->type = GL_BYTE;
            ad1->normalized = GL_FALSE;
            ad1->stride = sizeof(vertex_data);
            ad1->offset = (void*)8;
        }

        for (int i = 0; i < ATTRIBUTE_COUNT; ++i)
        {

        }

        const char* vertex_shader_code = 
        ""
        ""
        "";
        (void)vertex_shader_code;

        const char* fragment_shader_code = 
        ""
        ""
        "";
        (void)fragment_shader_code;
    }
}

void app_specific_update()
{
    if (r <= 0.0f) flip_flop = 1;
    else if (r >= 1.0f) flip_flop = 0;

    if (flip_flop) r+=0.0003f;
    else r -= 0.003;

    set_background_colour_4f(r, 0.4f, 0.8f-r, 1.0f);
}
