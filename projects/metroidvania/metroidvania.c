#include "nl_lib.h"
#include "private/nl_gl.h"

//
#include "metroidvania.h"
#include "player.h"
#include "physics.h"


global_variable player_controller controller = {key_a, key_d, key_space};
global_variable game_object player = {0};
global_variable game_object mouse_follow = {0};

global_variable float camera_pos = {0};

unsigned int shader_program = 0;
unsigned int u_model_loc = 0;
unsigned int u_view_mat = 0;
camera main_cam = {0};

// Bad to include here - but I will need to pass main_cam into player update to be sure
#include "player.c"

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

    generate_square_mesh(&mouse_follow.mesh, PLAYER_HALF_WIDTH, (colourf){0.5f,0.1f,1.0f,1.0f});

    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    u_model_loc = glGetUniformLocation(shader_program, "uModelMat");

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    //create_srt_matrix(mat4x4f* const mat, const v3f scale, const v3f rot, const v3f translation);
    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    u_view_mat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(u_view_mat, 1, GL_FALSE, &main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    player_update(dt, &player, &controller);
}

void app_specific_render(void)
{
    mat4x4f model = {0};
    create_identity_matrix(&model);
    {
        model.m41 = player.pos.x;
        model.m42 = player.pos.y;
        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&player.mesh);
    }

    create_identity_matrix(&model);
    {
        const v2i mouse_posi = get_mouse_position_from_system();
        v2f mouse_pos = {mouse_posi.x, mouse_posi.y};
        project_mouse_to_camera(&main_cam, &mouse_pos);

        model.m41 += (mouse_pos.x-PLAYER_QUARTER_WIDTH);
        model.m42 += (mouse_pos.y-PLAYER_QUARTER_WIDTH);

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&mouse_follow.mesh);
    }
}

void app_specific_cleanup(void)
{
    free_mesh(&player.mesh);
    free_mesh(&mouse_follow.mesh);
}