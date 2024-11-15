#include "nl_lib.h"
#include "private/nl_gl.h"

//
#include "metroidvania.h"
#include "player.h"
#include "physics.h"


#include "player.c"


global_variable player_controller controller = {key_a, key_d, key_space};
global_variable game_object player = {0};

global_variable game_object mouse_follow = {0};

global_variable mesh debug_points[4] = {0};

global_variable float camera_pos_x = {0};
global_variable float camera_pos_y = {0};


unsigned int shader_program = 0;
unsigned int u_model_loc = 0;
unsigned int u_view_mat = 0;
camera main_cam = {0};


internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &main_cam.proj_matrix.m11);
}

void camera_controls(float dt)
{
    char bIsDirty = 0;

    if (key_is_held(key_right))
    {
        camera_pos_x -= GRAVITY_FALL * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_left))
    {
        camera_pos_x += GRAVITY_FALL * dt;
        bIsDirty = 1;
    }

    if (key_is_held(key_up))
    {
        camera_pos_y -= GRAVITY_FALL * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_down))
    {
        camera_pos_y += GRAVITY_FALL * dt;
        bIsDirty = 1;
    }

    if (bIsDirty > 0)
    {
        create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,1.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){camera_pos_x,camera_pos_y,0.0f});
        u_view_mat = glGetUniformLocation(shader_program, "uViewMat");
        glUniformMatrix4fv(u_view_mat, 1, GL_FALSE, &main_cam.view_matrix.m11);
    }
}

void app_specific_init(void)
{
    player_init(&player);

    generate_square_mesh(&mouse_follow.mesh, PLAYER_HALF_WIDTH, (colourf){0.5f,0.1f,1.0f,1.0f});
    
    generate_square_mesh(&debug_points[0], PLAYER_QUARTER_WIDTH, (colourf){1.f,1.f,1.0f,1.0f});
    generate_square_mesh(&debug_points[1], PLAYER_QUARTER_WIDTH, (colourf){1.f,0.f,0.0f,1.0f});
    generate_square_mesh(&debug_points[2], PLAYER_QUARTER_WIDTH, (colourf){0.f,1.f,0.0f,1.0f});
    generate_square_mesh(&debug_points[3], PLAYER_QUARTER_WIDTH, (colourf){0.f,0.f,1.0f,1.0f});

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

    camera_controls(dt);

    const v2i mouse_posi = get_mouse_position_from_system();
    mouse_follow.pos = (v2f){(float)mouse_posi.x, (float)mouse_posi.y};
    project_mouse_to_camera(&main_cam, &mouse_follow.pos);

    // Overlap Code
    {
        aabb player_box = {0};
        player_box.min.x = player.pos.x;
        player_box.min.y = player.pos.y;
        player_box.max.x = player.pos.x + player.width;
        player_box.max.y = player.pos.y + player.width;

        aabb mouse_box  = {0};
        mouse_box.min.x = mouse_follow.pos.x - PLAYER_QUARTER_WIDTH;
        mouse_box.min.y = mouse_follow.pos.y - PLAYER_QUARTER_WIDTH;
        mouse_box.max.x = mouse_follow.pos.x + PLAYER_QUARTER_WIDTH;
        mouse_box.max.y = mouse_follow.pos.y + PLAYER_QUARTER_WIDTH;

        if (aabb_box_overlap(player_box, mouse_box))
        {
            local_persist int count;
            NL_LOG("Overlap! %d", ++count);
        }
    }
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

    {
        model.m41 = player.pos.x;
        model.m42 = player.pos.y;

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&debug_points[0]);
    }
    {
        model.m41 = player.pos.x + player.width - PLAYER_QUARTER_WIDTH;
        model.m42 = player.pos.y;

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&debug_points[1]);
    }
    {
        model.m41 = player.pos.x + player.width - PLAYER_QUARTER_WIDTH;
        model.m42 = player.pos.y + player.width - PLAYER_QUARTER_WIDTH;

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&debug_points[2]);
    }
    {
        model.m41 = player.pos.x;
        model.m42 = player.pos.y + player.width - PLAYER_QUARTER_WIDTH;

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&debug_points[3]);
    }

    {
        model.m41 = (mouse_follow.pos.x-PLAYER_QUARTER_WIDTH);
        model.m42 = (mouse_follow.pos.y-PLAYER_QUARTER_WIDTH);

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&mouse_follow.mesh);
    }
}

void app_specific_cleanup(void)
{
    free_mesh(&player.mesh);
    free_mesh(&mouse_follow.mesh);

    for (int i = 0; i < 4; ++i)
    {
        free_mesh(&debug_points[i]);
    }
}