#include "nl_lib.h"
#include "private/nl_gl.h"

#include "grid.c"

typedef struct GameObject GameObject;
struct GameObject
{
    transform2d transform;
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
    GameControls Controls;
    GameObject Player;
};
GameData *TheGame = {0}; 

internal_function v2f get_movement_input(const GameControls controls, const float dt)
{
    v2f speed = {0};

    speed.x = dt * (controls.MovementSpeed * is_key_held(controls.Right)) - (controls.MovementSpeed * is_key_held(controls.Left));
    speed.y = dt * (controls.MovementSpeed * is_key_held(controls.Up)) - (controls.MovementSpeed * is_key_held(controls.Down));

    const v2f normalized_speed = v2f_normalize(speed);
    return (normalized_speed);
}

internal_function void move_player(GameObject* player, v2f movement)
{
    player->transform.position.x += movement.x;

    player->transform.position.y += movement.y;

    if (movement.x != 0.0f)
    {
        NL_LOG("%f", player->transform.position.x)
    }
    if (movement.y != 0.0f)
    {
        NL_LOG("%f", player->transform.position.y)
    }
}

void app_specific_init(void)
{
    TheGame = (GameData*)memory_allocate(sizeof(GameData));
    
    // Controls Setup
    {
        TheGame->Controls.MovementSpeed = 10.0f;
        TheGame->Controls.Left = key_a;
        TheGame->Controls.Right = key_d;
        TheGame->Controls.Up = key_w;
        TheGame->Controls.Down = key_s;
        TheGame->Controls.Pause = key_escape;
    }
}

internal_function game_update(double dt)
{
    const v2f movement_vector = get_movement_input(TheGame->Controls, dt);
    move_player(&TheGame->Player, movement_vector);
}

internal_function game_draw()
{

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
            window_request_close();
        }
    }

    game_draw();
}

void app_specific_cleanup()
{
    memory_free(TheGame);
}