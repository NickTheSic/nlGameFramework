#ifndef __RENDERER_SETUP_H__
#define __RENDERER_SETUP_H__


#if defined __EMSCRIPTEN__
#define SHADER_VERSION_HEADER "#version 300 es \n precision mediump float; \n"
#else
#define SHADER_VERSION_HEADER  "#version 330 core\n"
#endif

typedef struct vertex_data vertex_data;
struct vertex_data
{
    v3f pos;
    colourf color;
};

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

#endif