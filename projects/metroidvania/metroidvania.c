#include "nl_lib.h"
#include "private/nl_gl.h"

//
#include "metroidvania.h"
#include "physics.h"

typedef struct player_controller player_controller; 
struct player_controller
{
    nl_key left;
    nl_key right;
    nl_key jump;
};

global_variable player_controller controller = {key_a, key_d, key_space};
global_variable game_object player = {0};
global_variable game_object mouse_follow = {0};

global_variable float camera_pos = {0};

unsigned int shader_program = 0;
unsigned int u_model_loc = 0;
camera main_cam = {0};

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0 + camera_pos, width + camera_pos, 0 + camera_pos, height + camera_pos, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    {
        mat4x4f test = {
            1.f, 0.f, 1.f, 0.f, 
            2.f, 3.f, 0.f, 1.f, 
            5.f, 1.f, 2.f, 1.f, 
            0.f, 0.f, 1.f, 1.f
            };

        NL_LOG("%f", matrix_determinant(&test));

        mat4x4f res = {0};
        if (invert_matrix_4x4(&test, &res) == 0)
        {
            NL_LOG("Unable to invert");
        }
    }

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
}

void player_update(double dt)
{
    if (player.is_grounded == 0)
    {
        if (player.vertical_speed <= 0.0f)
        {
            player.vertical_speed -= (GRAVITY_FALL + 150) * dt;
        }
        else
        {
            player.vertical_speed -= GRAVITY_RAISE * dt;
        }
    }

    if (player.is_grounded == 1)
    {
        if (key_was_pressed(controller.jump))
        {
            player.vertical_speed = GRAVITY_RAISE;
            player.is_grounded = 0;
        }
    }

    if (player.pos.y < 0.0f)
    {
        player.pos.y = 0.0f;
        player.vertical_speed = 0;
        player.is_grounded = 1;
    }
    player.pos.y += player.vertical_speed * dt;

    float horizontal_speed = {0};
    if (key_is_held(controller.right))
    {
        horizontal_speed += GRAVITY_FALL;
    }
    if (key_is_held(controller.left))
    {
        horizontal_speed -= GRAVITY_FALL;
    }

    if (key_is_held(key_right))
    {
        camera_pos += GRAVITY_FALL * dt;
        v2i screen_size = get_screen_size();
        winsizecbk(screen_size.x, screen_size.y);
    }

    player.pos.x += horizontal_speed * dt;
}

void app_specific_update(double dt)
{
    player_update(dt);
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
        v2i pos = get_mouse_position_from_system();

        mat4x4f inverse = model;
        invert_matrix_4x4(&main_cam.proj_matrix, &inverse);
        
        model.m41 = (pos.x-PLAYER_QUARTER_WIDTH) + camera_pos;
        model.m42 = (pos.y-PLAYER_QUARTER_WIDTH) + camera_pos;

        matrix_to_matrix_multiplication(&model, &inverse);

        glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, &model.m11);
        render_single_mesh(&mouse_follow.mesh);
    }
}

void app_specific_cleanup(void)
{
    free_mesh(&player.mesh);
    free_mesh(&mouse_follow.mesh);
}