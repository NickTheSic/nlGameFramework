#include "nl_lib.h"
#include "private/nl_gl.h"

#include "grid.c"

typedef struct GameObject GameObject;
struct GameObject
{
    transform2d transform;
    mesh m;
};

typedef struct GameControls GameControls ;
struct GameControls 
{
    float MovementSpeed;
    nl_key Left;
    nl_key Right;
    nl_key Up;
    nl_key Down;
    nl_key Pause;
};

typedef struct GameData GameData;
struct GameData
{
    int IsPaused;
    unsigned int shader_program;
    GameControls Controls;
    GameObject Player;
    camera game_camera;
};
GameData *TheGame = {0}; 

internal_function v2f get_movement_input(const GameControls controls, const float dt)
{
    v2f speed = {0};

    speed.x = dt * ((controls.MovementSpeed * is_key_held(controls.Right)) - (controls.MovementSpeed * is_key_held(controls.Left)));
    speed.y = dt * ((controls.MovementSpeed * is_key_held(controls.Up)) - (controls.MovementSpeed * is_key_held(controls.Down)));

    const v2f normalized_speed = v2f_normalize(speed);
    return (normalized_speed);
}

internal_function void move_player(GameObject* player, v2f movement)
{
    player->transform.position.x += movement.x;
    player->transform.position.y += movement.y;
}

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&TheGame->game_camera.view_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(TheGame->shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &TheGame->game_camera.view_matrix.m11);
}

void app_specific_init(void)
{
    TheGame = (GameData*)memory_allocate(sizeof(GameData));

    TheGame->shader_program = create_shader_program(common_vert_shader_code , common_fragment_shader_code);
    use_shader_program(TheGame->shader_program);

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
    
    // Controls Setup
    {
        TheGame->Controls.MovementSpeed = 10.0f;
        TheGame->Controls.Left  = key_a;
        TheGame->Controls.Right = key_d;
        TheGame->Controls.Up    = key_w;
        TheGame->Controls.Down  = key_s;
        TheGame->Controls.Pause = key_escape;
    }

    // Player Mesh which I plan to change to a sprite
    {
        TheGame->Player.transform.size = (v2f){1.0f,1.0f};
        TheGame->Player.transform.position  = (v2f){100.0f,100.0f};

        const int SQUARE_HALF_SIZE = 30;
        vertex_data square_verts[] =
        {
            {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}},
            {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
            {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
        unsigned int indices[]={0,1,2,2,3,0};
        generate_mesh_using_vertices_and_indices(&TheGame->Player.m, square_verts, 4, indices,6);
    }
}

internal_function void game_update(double dt)
{
    const v2f movement_vector = get_movement_input(TheGame->Controls, dt);
    move_player(&TheGame->Player, movement_vector);
}

internal_function void game_draw()
{
    unsigned int worldMat = glGetUniformLocation(TheGame->shader_program, "uWorldMat");
    mat4x4f mat = {0};

    create_identity_matrix(&mat);
    create_srt_matrix_from_transform2d(&mat, TheGame->Player.transform);
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&TheGame->Player.m);
}

void app_specific_update(double dt)
{
    if (was_key_pressed(TheGame->Controls.Pause))
    {
        TheGame->IsPaused = !TheGame->IsPaused; 
    }

    if (TheGame->IsPaused == 0)
    {
        game_update(dt);
    }
    else
    {
        if (was_key_pressed(key_space))
        {
            NL_LOG("Space Pressed");
            window_request_close();
        }
    }

    game_draw();
}

void app_specific_cleanup()
{
    free_mesh(&TheGame->Player.m);
    memory_free(TheGame);
}