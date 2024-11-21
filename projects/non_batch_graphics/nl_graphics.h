#ifndef __NL_GRAPHICS_H__
#define __NL_GRAPHICS_H__

#include <private/nl_colour.h>

// Just so we can call this during the app specific stuff while I test things out
void game_init_graphics(void);
void game_free_graphics(void);
void game_begin_render(void);
void game_end_render(void);

void draw_rectangle(v2f pos, colour col, v2f size);
void draw_square(v2f pos, colour col, float size);

unsigned int load_texture(const char *filepath);
void draw_sprite(v2f pos, colour col, v2f size, unsigned int texture_id);

void set_batch_view_matrix(float* m11);
void set_batch_proj_matrix(float* m11);

#endif//__NL_GRAPHICS_H__