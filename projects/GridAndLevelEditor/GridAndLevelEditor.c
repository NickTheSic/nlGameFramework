#include "nl_lib.h"
#include "private/nl_gl.h"

#include "GridAndLevelEditor.h"

v2i convert_index_to_grid_coords(world_grid *const grid, unsigned int index)
{
    v2i result = {0};

    if (index > grid->width*grid->height)
    {
        NL_LOG("Index is bigger than grid height and width");
        return result;
    }

    result.x = (index%grid->width);
    result.y = (index/grid->width);

    return (result);
}

int get_value_at_coords(world_grid* grid, unsigned int x, unsigned int y)
{
    if (x > grid->width || y > grid->height)
    {
        NL_LOG("Invalid values were passed into %s %i, %i for grid %i, %i", __FUNCTION__, x, y, grid->width, grid->height);
        return 0;
    }

    return (grid->tiles[y*grid->width+x]);
}

void init_world_grid(world_grid* grid, int width, int height, int tile_size)
{
    grid->tiles = memory_allocate(sizeof(int) * (width*height));

    if (grid->tiles != 0)
    {
        grid->width = width;
        grid->height = height;

        grid->tile_size = tile_size;
    }
    else
    {
        NL_LOG("Unable to allocate space for the grid");
    }
}

void free_world_grid(world_grid* const grid)
{
    if (grid->tiles != 0)
    {
        memory_free(grid->tiles);
    }

    grid->width = 0;
    grid->height = 0;
    grid->tile_size = 0;
}

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    init_world_grid(&grid, 10, 10, 32);

    generate_square_mesh(&tile_0, grid.tile_size, (colourf){1.0f,0.0f,0.0f,1.0f});

    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = glGetUniformLocation(shader_program, "uModelMat");

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    u_view_mat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(u_view_mat, 1, GL_FALSE, &main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    use_shader_program(shader_program);

    mat4x4f model = {0};
    
    for (int i = 0; i < grid.width*grid.height; ++i)
    {
        v2i coords = convert_index_to_grid_coords(&grid, i);
        int tile_type = get_value_at_coords(&grid, coords.x, coords.y);

        create_identity_matrix(&model);
    
        model.m41 = coords.x * grid.tile_size;
        model.m42 = coords.y * grid.tile_size;
        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);

        render_single_mesh(&tile_0);
    }
}

void app_specific_cleanup(void)
{
    free_mesh(&tile_0);
    free_world_grid(&grid);
}