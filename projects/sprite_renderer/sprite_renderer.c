#include "nl_lib.h"
#include "private/nl_gl.h"

#define STBI_ONLY_PNG
#include "stb_image.h"

#include "stddef.h"

typedef int sprite_handle;

typedef struct sprite_vertex_data sprite_vertex_data;
struct sprite_vertex_data
{
    v3f game_pos;
    v2f uv_coords;
    colourf colour;
};

internal_function void setup_sprite_vertex_data_attribs()
{    
    vertex_atrribute_info sprite_vertex_data_info[3] = {0};
    // game_pos
    {
        vertex_atrribute_info* const svd = &sprite_vertex_data_info[0];
        svd->value_count = 3;
        svd->type = GL_FLOAT;
        svd->normalized = GL_FALSE;
        svd->offset = offsetof(sprite_vertex_data, game_pos);
    }
    // uv_coords
    {
        vertex_atrribute_info* const svd = &sprite_vertex_data_info[1];
        svd->value_count = 2;
        svd->type = GL_FLOAT;
        svd->normalized = GL_FALSE;
        svd->offset = offsetof(sprite_vertex_data, uv_coords);
    }
    // colour
    {
        vertex_atrribute_info* const svd = &sprite_vertex_data_info[2];
        svd->value_count = 4;
        svd->type = GL_FLOAT;
        svd->normalized = GL_FALSE;
        svd->offset = offsetof(sprite_vertex_data, colour);
    }

    setup_vertex_atrributes(sizeof(sprite_vertex_data), sprite_vertex_data_info, 3);
}

typedef struct sprite sprite;
struct sprite
{
    v2f loaded_size;
    v2f uv_coords;
};

/* The texture data on the GPU - Separate from the Batch Renderer */
typedef struct sprite_sheet sprite_sheet;
struct sprite_sheet
{
    v2i atlas_size;
    v2i atlas_used;
    int atlas_height_loc;

    unsigned int sprite_count;

    sprite* sprites;
};

typedef struct render_batch_2d render_batch_2d;
struct render_batch_2d
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int max_count;
    unsigned int draw_count;

    sprite_vertex_data* sprite_data; // render_data? Alternate name.  Names not important.  Not sure how to keep generic
};


void init_render_batch_2d(render_batch_2d* const batch, const unsigned int batch_count)
{
    batch->max_count = batch_count;
    const unsigned int max_vertice_count = batch_count*4;
    const unsigned int max_indice_count = batch_count*6;

    const size_t vertex_data_size = max_vertice_count * sizeof(sprite_vertex_data);
    const size_t indice_data_size = max_indice_count  * sizeof(unsigned int);

    batch->sprite_data = (sprite_vertex_data*)memory_allocate(vertex_data_size);

    glGenVertexArrays(1, &batch->VAO);
    glBindVertexArray(batch->VAO);

    glGenBuffers(1, &batch->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data_size, 0, GL_DYNAMIC_DRAW);
    
    unsigned int* indices = (unsigned int*)memory_allocate(indice_data_size);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < max_indice_count; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &batch->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    memory_free(indices);

    setup_sprite_vertex_data_attribs();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void start_render_batch(render_batch_2d* const batch)
{
    glBindVertexArray(batch->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->EBO);
}

void end_render_batch(render_batch_2d* const batch)
{
    glBindVertexArray(batch->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, batch->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sprite_vertex_data) * batch->draw_count, batch->sprite_data);

    glDrawElements(GL_TRIANGLES, batch->draw_count * 6, GL_UNSIGNED_INT, 0);

    batch->draw_count = 0;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// void add_mesh_to_batch(batch_render* const batch, const mesh* const mesh)
// {
//     unsigned int current_verts = batch->current_vertices;
//     unsigned int current_index = batch->current_indices;

//     if ((current_verts + mesh->vertice_count > batch->max_vertices) || (current_index + mesh->indice_count > batch->max_indices))
//     {
//         end_render_batch(batch);
//     }

//     vertex_data* vertex_buffer = &batch->vertex_batch[current_verts];
//     memcpy(vertex_buffer, mesh->vertices, sizeof(vertex_data) * mesh->vertice_count);

//     unsigned int* index_buffer = &batch->indice_batch[current_index];
//     for (unsigned int i = 0; i < mesh->indice_count; i++)
//     {
//         index_buffer[i] = current_index + mesh->indices[i];
//     }

//     batch->current_indices += mesh->indice_count;
//     batch->current_vertices += mesh->vertice_count;    
// }

render_batch_2d sprite_renderer = {0};

extern void app_specific_init(void)
{
    init_render_batch_2d(&sprite_renderer, 10);
}

extern void app_specific_update(double dt)
{
    
}
