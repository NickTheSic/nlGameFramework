#include "nl_lib.h"
#include "private/nl_gl.h"
#include "stddef.h"

#include "sprite_batch.h"
#include "sprite_batch.c"


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

void app_specific_init(void)
{
    init_render_batch_2d(&sprite_renderer, 10);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);   
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{

}
