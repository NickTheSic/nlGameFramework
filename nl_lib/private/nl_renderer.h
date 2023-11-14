#ifndef __NL_RENDERER_H__
#define __NL_RENDERER_H__

/////////////////////////////////////////////////////////////////
//                      Data Types                             //
/////////////////////////////////////////////////////////////////

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

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v3f pos;
    colourf color;
};

// not batch able?
// creates own VAO, VBO, EBO which could be avoided in some cases
typedef struct mesh mesh;
struct mesh
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int indice_count;
    unsigned int vertice_count;

    unsigned int* indices;
    vertex_data* vertices;
};


/////////////////////////////////////////////////////////////////
//                     Renderer System                         //
/////////////////////////////////////////////////////////////////
int initialize_renderer_subsystem();

void begin_render_frame();
void end_render_frame();
void renderer_swap_buffers();

/////////////////////////////////////////////////////////////////
//                        Mesh Functions                       //
/////////////////////////////////////////////////////////////////
// Does not yet take into account batching
void generate_mesh_using_vertices_and_indices(mesh* const mesh, const vertex_data* const vertice, int vertice_count, const unsigned int* const indices, unsigned int indice_count);
void render_single_mesh(mesh* mesh);


/////////////////////////////////////////////////////////////////
//              Wrappers around GL specific calls              //
/////////////////////////////////////////////////////////////////
void set_background_colour_4f(float r, float g, float b, float a);
void set_viewport_size(int width, int height);
void set_wireframe_rendering(void);
void set_fill_rendering(void);
void set_depth_test_enabled(int enabled);

#endif