#include "nl_lib.h"
#include "sprite_batch.h"
#include "sprite_sheet.h"

global_variable unsigned int sp    = {0};
global_variable sprite_batch batch = {0};
global_variable unsigned int img   = {0};

void app_specific_init(void)
{
    sp = create_shader_program(batch_vert_shader_code, common_fragment_shader_code);
    use_shader_program(sp);
    init_batch(&batch, 3);

    img = load_image("data/test_sprite.png");
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render()
{
    use_shader_program(sp);
    begin_render_batch(&batch);
    add_to_render_batch(&batch, (v2f){0.5f,0.3f});
    add_to_render_batch(&batch, (v2f){0.1f,-0.2f});

    const v2i mouse_posi = get_mouse_position_from_system();
    const v2f mouse_pos = (v2f){(float)(mouse_posi.x/800.f) - 0.5f, (float)(mouse_posi.y/600.f) - 0.5f};
    add_to_render_batch(&batch, mouse_pos);

    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_batch(&batch);
}

#include "sprite_batch.c"
#include "sprite_sheet.c"