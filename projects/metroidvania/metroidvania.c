#include "nl_lib.h"
#include "private/nl_gl.h"

//
#include "metroidvania.h"
#include "physics.h"


global_variable game_object player = {0};

unsigned int shader_program = 0;
unsigned int u_model_loc = 0;
camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    player.width = PLAYER_WIDTH;
    player.pos = (v2f){100.0f,100.0f};
    generate_square_mesh(&player.mesh, player.width, (colourf){1.0f,0.5f,0.2f,1.0f});

    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = glGetUniformLocation(shader_program, "uModelMat");

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    (void)dt;
    
    if (player.is_grounded == 0)
    {
        if (player.movement_speed.y >= 0.0f)
            player.movement_speed.y -= GRAVITY_RAISE * dt;
        else
            player.movement_speed.y -= GRAVITY_FALL * dt;
    }

    if (player.is_grounded == 1)
    {
        if (key_was_pressed(key_space))
        {
            player.movement_speed.y = GRAVITY_RAISE;
            player.is_grounded = 0;
        }
    }

    if (player.pos.y < 0.0f && player.movement_speed.y < 0.0f)
    {
        player.pos.y = 0.0f;
        player.movement_speed.y = 0;
        player.is_grounded = 1;
    }

    player.pos.x += player.movement_speed.x * dt;
    player.pos.y += player.movement_speed.y * dt;
}

void app_specific_render(void)
{
    {
        mat4x4f model = {0};
        create_identity_matrix(&model);
        model.m41 += player.pos.x;
        model.m42 += player.pos.y;
        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&player.mesh);
    }
}

void app_specific_cleanup(void)
{
    free_mesh(&player.mesh);
}