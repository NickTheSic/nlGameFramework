#include "nl_lib.h"
#include "nl_rr_sprite.h"

nl_rr_sprite SPRITE = {0};
nl_rr_sprite TWO = {0};

mat4x4f ModelSprite = {0};
mat4x4f ModelTwo = {0};

unsigned int rr_shader_program = 0;
unsigned int model_loc = 0;

void app_specific_init(void)
{
    create_simple_rr_sprite("fish.png", &SPRITE);
    create_simple_rr_sprite("thing.png", &TWO);

    rr_shader_program = load_shader_from_files("rr_shader_matrices.vs", "rr_shader.fs");
    model_loc = get_uniform_loc(rr_shader_program, "uModelTransform");

    create_identity_matrix(&ModelSprite);
    create_identity_matrix(&ModelTwo);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
    
    rotate_matrix(&ModelTwo, 75.f * dt, 0.f, 0.f, 1.f);
}

void app_specific_render(void)
{
    use_shader_program(rr_shader_program);
    
    set_uniform_mat4x4f(model_loc, &ModelSprite.m11);
    render_simple_rr_sprite(&SPRITE);

    set_uniform_mat4x4f(model_loc, &ModelTwo.m11);
    render_simple_rr_sprite(&TWO);
}

void app_specific_cleanup(void)
{
    free_simple_rr_sprite(&SPRITE);
    free_simple_rr_sprite(&TWO);

    free_shader_program(rr_shader_program);
}


#include "nl_rr_sprite.c"
