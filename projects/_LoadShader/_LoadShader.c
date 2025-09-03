#include "nl_lib.h"
#include "nl_sprite_renderer.h"
#include <private/nl_physics2d.h>

#if PLATFORM_CONSOLE
#include <private/nl_keys_to_controller.h>
#endif

global_variable camera main_cam = {0};

#define LASER_BOTTOM_Y 80.f
#define LASER_DISTANCE 170.f
#define LASER_TOP_Y LASER_BOTTOM_Y + LASER_DISTANCE
#define LASER_START_X 120.f
#define MAX_LASER_BEAMS_IN_GAME 4
#define BEAM_CHECK_TIME 3.0f

unsigned int difficulty = {1};
int current_volume = 50;

typedef struct laser laser;
struct laser
{
    v2f pos;
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

float current_beam_reset_time = 0.0f;

unsigned char game_state = 0;

internal_function void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, (float)width, 0, (float)height, -0.1f, 100.f);
    set_projection_matrix(&main_cam.proj_matrix);
}

internal_function void generate_game_sprites(void)
{
    load_texture_for_sprite(&laser_base, "data/laser_stop.png");
    generate_rectangle_simple_sprite(&laser_base, 32, 16);

    load_texture_for_sprite(&laser_top, "data/laser_top.png");
    generate_rectangle_simple_sprite(&laser_top, 32, 16);

    load_texture_for_sprite(&laser_beam, "data/ground.png");
    generate_rectangle_simple_sprite(&laser_beam, 32, LASER_DISTANCE);

    load_texture_for_sprite(&man, "data/man.png");
    generate_rectangle_simple_sprite(&man, 32, 64);

    load_texture_for_sprite(&money, "data/money.png");
    generate_rectangle_simple_sprite(&money, 32, 32);
}

internal_function unsigned char get_laser_beam_showing(laser* const laser)
{
    return (laser->laser_active > 0 ? (unsigned char)random_int_in_range(0,difficulty) : 0);
}

void app_specific_init(void)
{
    init_sprite_renderer();

    generate_game_sprites();

    set_screen_size(200, 240);

    set_window_size_callback(&winsizecbk);
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);

    create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,0.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){0.0f,0.0f,0.0f});
    set_view_matrix(&main_cam.view_matrix);
}

void app_specific_update(double dt)
{
    current_beam_reset_time += (float)dt;
    if (current_beam_reset_time >= BEAM_CHECK_TIME)
    {
        current_beam_reset_time -= BEAM_CHECK_TIME;
        for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
        {
            if (lasers[i].laser_active)
            {
                lasers[i].beam_active = get_laser_beam_showing(&lasers[i]);
            }
        }
    }
}

void app_specific_render(void)
{
    mat4x4f model = {0};
    create_identity_matrix(&model);
    {
        for (int i = 0; i < MAX_LASER_BEAMS_IN_GAME; ++i)
        {
            if (lasers[i].laser_active == 0)
            {
                continue;
            }

            model.m41 = lasers[i].pos.x;
            model.m42 = lasers[i].pos.y;
            set_model_matrix(&model);

            if (lasers[i].beam_active)
            {
                render_single_simple_sprite(&laser_beam);
            }

            render_single_simple_sprite(&laser_base);

            model.m42 = LASER_TOP_Y;
            set_model_matrix(&model);
            render_single_simple_sprite(&laser_top);
        }
    }

    create_identity_matrix(&model);
    {
        model.m41 = money_pos.x;
        model.m42 = money_pos.y;
        set_model_matrix(&model);
        render_single_simple_sprite(&money);
    }

    create_identity_matrix(&model);
    {
        model.m41 = man_pos.x;
        model.m42 = man_pos.y;
        set_model_matrix(&model);
        render_single_sprite_colour(&man, COLOUR_GREEN);
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

#if defined (PSP)
#include "nl_sprite_renderer_psp.c"

#else
#include "nl_sprite_renderer_gl.c"

#endif