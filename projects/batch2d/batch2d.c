#include "nl_lib.h"
#include "sprite_batch.h"

global_variable unsigned int sp = {0};
global_variable sprite_batch batch = {0};

void app_specific_init(void)
{
    sp = create_shader_program(batch_vert_shader_code, common_fragment_shader_code);
    use_shader_program(sp);
    init_batch(&batch, 3);
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
    end_render_batch(&batch);
}

void app_specific_cleanup()
{
    free_batch(&batch);
}

#include "sprite_batch.c"