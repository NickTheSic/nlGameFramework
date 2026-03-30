#include "nl_lib.h"
#include "endless_grid_2d.h"
#include "nl_rr_linerenderer.h"
#include "sprite_renderer.h"

#include "private/gl/nl_gl.h"

typedef struct global_renderer global_renderer;
struct global_renderer
{

    mat4x4f ortho_view;
    endless_grid_2d grid;
    nl_rr_linerenderer line_renderer;
    sprite_renderer sprite_renderer;
    float camera_size;

};

global_renderer gRenderer = {0};

void winsizeclbk(int width, int height)
{
    if (width >= height)
    {
        float aspect = (float)width / (float)height;
        float sx = gRenderer.camera_size * aspect;
        float sy = gRenderer.camera_size;
        create_orthographic_projection(&gRenderer.ortho_view, -sx, sx, -sy, sy, 0.0f, 1.0f);
    }
    else
    {
        float aspect = (float)height / (float)width;
        float sx = gRenderer.camera_size;
        float sy = gRenderer.camera_size*aspect;
        create_orthographic_projection(&gRenderer.ortho_view, -sx, sx, -sy, sy, 0.0f, 1.0f);
    }

    set_endless_grid_screen_sizei(&gRenderer.grid, width, height);
    set_endless_grid_view_matrix(&gRenderer.grid, &gRenderer.ortho_view);

    // A reason to encapWsulate the call!  So I can use the shader
    glUseProgram(gRenderer.line_renderer.shader);
    glUniformMatrix4fv(gRenderer.line_renderer.view_matrix_loc, 1, GL_FALSE, &gRenderer.ortho_view.m11);
}

void app_specific_init(void)
{
    set_window_size_callback(winsizeclbk);
    v2i screen = get_screen_size();
    gRenderer.camera_size = 25.0f;

    init_endless_grid(&gRenderer.grid);
    init_line_renderer(&gRenderer.line_renderer);
    init_sprite_renderer(&gRenderer.sprite_renderer);

    winsizeclbk(screen.x, screen.y);

    /// this is initialization stuff that could be good to pass into the init?
    /// I created a render_as function that takes this information in aswell...
    {
        set_endless_grid_screen_sizei(&gRenderer.grid, screen.x, screen.y);
        set_endless_grid_camera_position(&gRenderer.grid, (v3f){0.0f,0.0f,0.0f});
        set_endless_grid_view_matrix(&gRenderer.grid, &gRenderer.ortho_view);
    }

    {
        // Again, init stuff here. and I don't have the call wrapped
        // A reason to encasulate the call!  So I can use the shader
        glUseProgram(gRenderer.line_renderer.shader);
        glUniformMatrix4fv(gRenderer.line_renderer.view_matrix_loc, 1, GL_FALSE, &gRenderer.ortho_view.m11);
    }

    {
        // TODO: Set sprite uniform variables
    }
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    // NOTE: This is fine.  Calling things in order would be better anyway
    // endless_grid(); draw_line(x); draw_sprite(y); draw_line(x)
    // Would be nice to auto switch and I can do so in the future if I feel it is required

    render_endless_grid(&gRenderer.grid);

    begin_sprite_batch(&gRenderer.sprite_renderer);
    {
        sprite_data spr_d = {0};
        spr_d.texture_uv_tr.x = 1.0f;
        spr_d.texture_uv_tr.y = 1.0f;

        add_sprite_to_batch(&gRenderer.sprite_renderer, &spr_d);
    }
    end_sprite_batch(&gRenderer.sprite_renderer);


    begin_linerender_draw(&gRenderer.line_renderer);
    {
        //v2i screen = get_screen_size();
        float sx = gRenderer.camera_size;//loat)screen.x/4;
        float sy = gRenderer.camera_size;//loat)screen.y/4;

        v3f points_1[] = {
            {-sx, -sy, 0.0f},
            { sx,  sy, 0.0f},
        };
        add_linerender_points(&gRenderer.line_renderer, points_1, 2);

        v3f points_2[] = {
            { sx, -sy, 0.0f},
            {-sx,  sy, 0.0f},
        };
        add_linerender_points_coloured(&gRenderer.line_renderer, points_2, 2, COLOUR_GREEN);

        v3f points_3[] = {
            {0.0f,-sy, 0.0f},
            {0.0f, sy, 0.0f},
        };
        add_linerender_points_coloured(&gRenderer.line_renderer, points_3, 2, COLOUR_BLUE);
    }
    end_linerender_draw(&gRenderer.line_renderer);

}

void app_specific_cleanup(void)
{
    free_line_renderer(&gRenderer.line_renderer);
    free_sprite_renderer(&gRenderer.sprite_renderer);
}

#include "endless_grid_2d.c"
#include "nl_rr_linerenderer.c"
#include "sprite_renderer.c"
