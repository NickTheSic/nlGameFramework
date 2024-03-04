#include "nl_lib.h"
#include "private/nl_gl.h"

#include "a_game.h"

global_variable object_controller player_controller = {0};
global_variable object player = {0};

internal_function void update_player_controller(object_controller* const pc, double dt)
{
    object* const player = pc->object;

    if (is_key_held(pc->controls.move_up))
    {
        player->transform.position.y += pc->speed*dt;
    }
    if (is_key_held(pc->controls.move_down))
    {
        player->transform.position.y -= pc->speed*dt;
    }
    
    if (was_key_pressed(pc->controls.move_left))
    {
        player->transform.position.x -= pc->speed*dt;
    }

    if (is_key_held(pc->controls.move_right))
    {
        player->transform.position.x += pc->speed*dt;
    }
}

void app_specific_init(void)
{
    NL_LOG("Startup!");

    player_controller.object = &player;   
    player_controller.controls.move_up = key_w;
    player_controller.controls.move_down = key_s;
    player_controller.controls.move_left = key_a;
    player_controller.controls.move_right = key_d;
    player_controller.speed = 5.f;

}

void app_specific_update(double dt)
{
    update_player_controller(&player_controller, dt);

    
}
