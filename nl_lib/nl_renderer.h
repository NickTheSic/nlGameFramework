#ifndef __NL_RENDERER_H__
#define __NL_RENDERER_H__

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

int initialize_renderer_subsystem();

void begin_render_frame();
void end_render_frame();
void renderer_swap_buffers();

void set_background_colour_4f(float r, float g, float b, float a);
void set_viewport_size(int width, int height);

unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code);
void use_shader_program(unsigned int shader_program);

#endif