#include "nl_lib.h"

#include "sprite_sheet.h"

global_variable spritesheet sheet = {0};

void app_specific_init(void)
{
    init_sprite_sheet(&sheet, 4, 4, (v2i){32,32});
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    begin_sprite_batch(&sheet);

    add_sprite_to_batch(0, (v2f){100.f,100.f}, (colourf){1.0f,1.0f,1.0f,1.0f});

    end_sprite_batch(&sheet);
}

void app_specific_cleanup(void)
{
    free_sprite_sheet(&sheet);
}

#include "sprite_sheet.c"