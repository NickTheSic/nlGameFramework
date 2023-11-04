#include "nl_lib.h"
#include "nl_gl.h"

#if defined __EMSCRIPTEN__
#define SHADER_VERSION_HEADER "#version 300 es\n precision mediump float;\n"

#elif defined(_WIN32)
#define SHADER_VERSION_HEADER  "#version 330 core\n"

#elif 
#error Check for gl version header

#endif

int flip_flop = 0;
float r = 0.0f;

int frag_shader_program = -1;
int vert_shader_program = -1;

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

int CompileShaderCode(const char* shader_code, unsigned int type)
{
    int shader_program = glCreateShader(type);

    glShaderSource(shader_program, 1, &shader_code, 0);
    glCompileShader(shader_program);
    
    int success = 0;
    glGetShaderiv(shader_program, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader_program, 512, NULL, info_log);
        NL_LOG("Error Compiling shader: %d\n\t%s\n", type, info_log);

        shader_program = -1;
    }

    return (shader_program);
}

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
        SHADER_VERSION_HEADER
        "void main() { \n"
        ""
        "}\0";
        vert_shader_program = CompileShaderCode(vertex_shader_code, GL_VERTEX_SHADER);

        const char* fragment_shader_code = 
        SHADER_VERSION_HEADER
        "void main() { \n"
        ""
        "}\0";
        frag_shader_program = CompileShaderCode(fragment_shader_code, GL_FRAGMENT_SHADER);

    }
}

void app_specific_update()
{
    if (r <= 0.0f) flip_flop = 1;
    else if (r >= 1.0f) flip_flop = 0;

    if (flip_flop) r+=0.0003f;
    else r -= 0.0003;

    set_background_colour_4f(r, 0.4f, 0.8f-r, 1.0f);
}
