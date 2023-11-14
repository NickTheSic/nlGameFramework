#include "nl_lib.h"
#include "private/nl_gl.h"

typedef int sprite_handle;

typedef struct sprite_vertex_data sprite_vertex_data;
struct sprite_vertex_data
{
    v3f game_pos;
    v2f texture_coords;
    colourf colour;
};

typedef struct sprite sprite;
struct sprite
{
    v2f loaded_size;
    v2f uv_coords;
};

typedef struct sprite_sheet sprite_sheet;
struct sprite_sheet
{
    v2i atlas_size;
    v2i atlas_used;
    int atlas_height_loc;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int max_vertices;
    unsigned int current_vertices;

    unsigned int max_sprites;
    unsigned int sprite_count;

    sprite* sprites;
    sprite_vertex_data* vertex_data;
};

extern void app_specific_init(void)
{

}

extern void app_specific_update(double dt)
{
    
}
