#include "nl_lib.h"
#include "private/gl/nl_gl.h"

#include "grid.c"

typedef struct GameObject GameObject;
struct GameObject
{
    transform2d transform;
    mesh m;
    float movement_speed;
};

typedef struct GameControls GameControls ;
struct GameControls 
{
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
    Grid grid;
    camera game_camera;
};
GameData *TheGame = {0}; 

internal_function v2f get_movement_input(const GameControls controls)
{
    v2f speed = {0};

    speed.x = key_is_held(controls.Right) - key_is_held(controls.Left);
    speed.y = key_is_held(controls.Up) - key_is_held(controls.Down);

    const v2f normalized_speed = v2f_normalize(speed);

    return (normalized_speed);
}

internal_function void move_player(GameObject* player, v2f movement, double dt)
{
    v2f world_pos = TheGame->Player.transform.position;
    v2f x_check = world_pos;
    v2f y_check = world_pos;
    x_check.x += 16*movement.x;
    y_check.y += 16*movement.y;

    v2i x_coords = world_to_grid_coords(&TheGame->grid, x_check);
    v2i y_coords = world_to_grid_coords(&TheGame->grid, y_check);

    if (get_value_at_coords(&TheGame->grid, x_coords.x, x_coords.y) != 0)
        player->transform.position.x += player->movement_speed * movement.x * dt;
    
    if (get_value_at_coords(&TheGame->grid, y_coords.x, y_coords.y) != 0)
        player->transform.position.y += player->movement_speed * movement.y * dt;
}

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&TheGame->game_camera.proj_matrix, 0.f, width, 0.f, height, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(TheGame->shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &TheGame->game_camera.proj_matrix.m11);
}

void app_specific_init(void)
{
    TheGame = (GameData*)memory_allocate(sizeof(GameData));
    
    initialize_camera_to_identity(&TheGame->game_camera);

    TheGame->shader_program = create_common_shader_program();
    use_shader_program(TheGame->shader_program);

    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&TheGame->game_camera.view_matrix, (v3f){1.0f,1.f,1.f},  (v3f){0.0f,0.f,0.f}, (v3f){0.0f,0.f,0.f});
    unsigned int viewMat = glGetUniformLocation(TheGame->shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &TheGame->game_camera.view_matrix.m11);
    
    // Controls Setup
    {
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
        TheGame->Player.transform.rotation = 0.0f;

        const float SQUARE_HALF_SIZE = 16.f;
        vertex_data square_verts[] =
        {
            {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}},
            {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
            {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
        unsigned int indices[]={0,1,2,2,3,0};
        generate_mesh_using_vertices_and_indices(&TheGame->Player.m, square_verts, 4, indices,6);
        
        TheGame->Player.movement_speed = 300.0f;
    }

    {
        int g[] = {
            0,0,0,0,0,0,
            0,2,1,1,1,0,
            0,1,0,1,1,0,
            0,1,1,1,1,0,
            0,1,1,1,1,0
        };
        init_grid(&TheGame->grid, 6,5, g);
        //save_to_binary_file("TEST_GRID", sizeof(Grid), (char*)&TheGame->grid);
        //load_from_binary_file("TEST_GRID", sizeof(Grid), (char*)&TheGame->grid);
        //make_grid_meshes(&TheGame->grid);
    }
}

internal_function void game_update(double dt)
{
    const v2f movement_vector = get_movement_input(TheGame->Controls);
    move_player(&TheGame->Player, movement_vector, dt);
}

internal_function void game_draw()
{
    unsigned int worldMat = glGetUniformLocation(TheGame->shader_program, "uWorldMat");
    mat4x4f mat = {0};

    transform2d transform = {0};
    transform.size = (v2f){1.0f,1.0f};
    transform.rotation = 0.f;
    for (unsigned int i = 0; i < TheGame->grid.Width *TheGame->grid.Height; ++i)
    {
        create_identity_matrix(&mat);
        transform.position  = grid_to_world_position(&TheGame->grid, i);
        create_srt_matrix_from_transform2d(&mat, transform);
        glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);
        render_single_mesh(&grid_meshes[TheGame->grid.Data[i]]);
    }

    create_identity_matrix(&mat);
    create_srt_matrix_from_transform2d(&mat, TheGame->Player.transform);
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&TheGame->Player.m);
}

void app_specific_update(double dt)
{
    if (key_was_pressed(TheGame->Controls.Pause))
    {
        TheGame->IsPaused = !TheGame->IsPaused; 
    }

    if (TheGame->IsPaused == 0)
    {
        game_update(dt);
    }
    else
    {
        if (key_was_pressed(key_space))
        {
            NL_LOG("Space Pressed");
            window_request_close();
        }
    }
}

void app_specific_render()
{
    game_draw();
}

void app_specific_cleanup()
{
    free_grid(&TheGame->grid);
    free_mesh(&TheGame->Player.m);
    memory_free(TheGame);
}

#include "nl_mesh_gl.c"
