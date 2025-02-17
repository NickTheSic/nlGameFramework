#include "nl_lib.h"
#include "nl_sprite_renderer.h"
#include <private/nl_physics2d.h>

global_variable camera main_cam = {0};

#define LASER_BOTTOM_Y 80.f
#define LASER_DISTANCE 170.f
#define LASER_TOP_Y LASER_BOTTOM_Y + LASER_DISTANCE
#define LASER_START_X 120.f
#define MAX_LASER_BEAMS_IN_GAME 4

unsigned int difficulty = {1};

typedef struct laser laser;
struct laser
{
    v2f pos;
    float laser_pos_x;
    float delay;
    float current_time;
    unsigned char beam_active; // The beam
    unsigned char laser_active; // the entire system
};
laser lasers[MAX_LASER_BEAMS_IN_GAME];

nl_sprite laser_base = {0};
nl_sprite laser_beam = {0};
nl_sprite laser_top = {0};
nl_sprite man = {0};
nl_sprite money = {0};

v2f man_pos = {0};
v2f money_pos = {0};

v2f laser_beam_size = {0};

unsigned int coin_pickup_sfx = {0};
unsigned int laser_hit_sfx = {0};
unsigned int run_start_sfx = {0};
unsigned int sneak_bgm = {0};

unsigned char game_state = 0;

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix.m11);
}

internal_function void load_game_sfx(void)
{
    coin_pickup_sfx = load_sound_file("data/coinPickup.wav");
    laser_hit_sfx = load_sound_file("data/laserHit.wav");
    run_start_sfx = load_sound_file("data/run.wav");
    sneak_bgm = load_sound_file("data/SneakySong.wav");
}

internal_function void generate_game_sprites(void)
{
    generate_rectangle_simple_sprite(&laser_base, 32, 16);
    load_texture_for_sprite(&laser_base, "data/laser_stop.png");

    generate_rectangle_simple_sprite(&laser_top, 32, 16);
    load_texture_for_sprite(&laser_top, "data/laser_top.png");

    generate_rectangle_simple_sprite(&laser_beam, 16, LASER_DISTANCE);
    load_texture_for_sprite(&laser_beam, "data/single_red_pixel.png");

    generate_rectangle_simple_sprite(&man, 32, 64);
    load_texture_for_sprite(&man, "data/man.png");

    generate_rectangle_simple_sprite(&money, 32, 32);
    load_texture_for_sprite(&money, "data/money.png");
}

internal_function unsigned char get_laser_beam_showing(laser* const laser, const float dt)
{
    unsigned char active = laser->beam_active;
    laser->current_time += dt;

    if (laser->current_time >= laser->delay)
    {
        active = !laser->beam_active;
        laser->current_time -= laser->delay;
    }

    return active;
}

internal_function void set_man_start_position(void)
{
    man_pos.x = LASER_START_X - 40.f;
    man_pos.y = LASER_BOTTOM_Y + 32.f;
}

internal_function void set_money_end_position(int furthest_active_laser)
{
    money_pos.x = LASER_START_X + 64 + (50 * furthest_active_laser);
    money_pos.y = LASER_BOTTOM_Y + 32;
}

internal_function void generate_game_laser_beams(void)
{
    laser_beam_size.x = 16.f;
    laser_beam_size.y = LASER_DISTANCE;

    int furthest_active_laser = 0;
    for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
    {
        lasers[i].pos.x = (LASER_START_X) + (i*50);
        lasers[i].pos.y = LASER_BOTTOM_Y;

        lasers[i].laser_pos_x = lasers[i].pos.x + 8;

        lasers[i].delay = random_float_in_range(2,4);
        lasers[i].current_time = 0.0f;

        lasers[i].laser_active = (unsigned char)random_int_in_range(0,3);
        lasers[i].beam_active = get_laser_beam_showing(&lasers[i], 1.0f);

        NL_LOG("Laser %d active: %d", i, (int)lasers[i].laser_active);
        NL_LOG("Laser %d beam active: %d", i, (int)lasers[i].beam_active);

        if (lasers[i].laser_active)
        {furthest_active_laser = i;}
    }

    set_money_end_position(furthest_active_laser);
}

internal_function void reset_game(void)
{
    set_man_start_position();
    game_state = 0;
}   

internal_function void restart_game(void)
{
    reset_game();
    generate_game_laser_beams();
}

internal_function void collision_test(void)
{
    aabb man_box = {0};
    man_box.min = man_pos;
    man_box.max.x = man_pos.x + 32;
    man_box.max.y = man_pos.y + 64;

    aabb money_box = {0};
    money_box.min = money_pos;
    money_box.max.x = money_pos.x + 32;
    money_box.max.y = money_pos.y + 32;

    if (aabb_box_overlap(man_box, money_box))
    {
        game_state = 4;
        play_sound(coin_pickup_sfx);
    }

    for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
    {
        if (lasers[i].laser_active && lasers[i].beam_active)
        {
            aabb laser_box = {0};
            laser_box.min.x = lasers[i].laser_pos_x;
            laser_box.min.y = lasers[i].pos.y;
            laser_box.max.x = lasers[i].laser_pos_x + laser_beam_size.x;
            laser_box.max.y = lasers[i].pos.y + laser_beam_size.y;
            if (aabb_box_overlap(man_box, laser_box))
            {
                game_state = 3;
                play_sound(laser_hit_sfx);
                break;
            }
        }
    }
}

void app_specific_init(void)
{
    init_sprite_renderer();

    generate_game_sprites();
    load_game_sfx();

    set_sound_to_loop(sneak_bgm);
    play_sound(sneak_bgm);

    restart_game();

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix.m11);
}

void app_specific_update(double dt)
{
    for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
    {
        if (lasers[i].laser_active)
        {
            lasers[i].beam_active = get_laser_beam_showing(&lasers[i], dt);
        }
    }
    
    switch(game_state)
    {
        case 0:
        {
            if (key_was_pressed(key_space))
            {
                game_state = 1;
                play_sound(run_start_sfx);
            }
        } break;

        case 1:
        {
            man_pos.x += 100 * dt;

            if (key_was_pressed(key_space))
            {
                game_state = 0;
                play_sound(run_start_sfx);
            }

            collision_test();
        } break;

        case 3:
        {
            //Hit Laser
            reset_game();
        } break;

        case 4:
        {
            difficulty = (difficulty+1) % 5;
            // hit coins
            restart_game();
        } break;
    }
}

void app_specific_render(void)
{
    mat4x4f model = {0};
    //model.m41
    create_identity_matrix(&model);
    {
        for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
        {
            if (lasers[i].laser_active == 0)
            {
                continue;
            }

            model.m41 = lasers[i].laser_pos_x;
            model.m42 = lasers[i].pos.y;
            set_model_matrix(&model.m11);

            if (lasers[i].beam_active)
            {
                render_single_simple_sprite(&laser_beam);
            }

            model.m41 = lasers[i].pos.x;
            set_model_matrix(&model.m11);
            render_single_simple_sprite(&laser_base);

            model.m41 = lasers[i].pos.x;
            model.m42 = LASER_TOP_Y;
            set_model_matrix(&model.m11);
            render_single_simple_sprite(&laser_top);
        }
    }

    create_identity_matrix(&model);
    {
        model.m41 = money_pos.x;
        model.m42 = money_pos.y;
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&money);
    }

    create_identity_matrix(&model);
    {
        model.m41 = man_pos.x;
        model.m42 = man_pos.y;
        set_model_matrix(&model.m11);
        render_single_simple_sprite(&man);
    }

}

void app_specific_cleanup(void)
{
    free_simple_sprite(&laser_base);
    free_simple_sprite(&laser_beam);
    free_simple_sprite(&laser_top);
    free_simple_sprite(&man);
    free_simple_sprite(&money);
}

#include "nl_sprite_renderer_gl.c"
