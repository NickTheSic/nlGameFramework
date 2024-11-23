#ifndef __NL_GRAPHICS_H__
#define __NL_GRAPHICS_H__

void draw_line(float startx, float starty, float endx, float endy);
void draw_line_v(v2f start, v2f end);
void draw_sprite(float x, float y, float w, float h, float u, float v);
void draw_sprite_v(v2f pos, v2f size, v2f uv);

#endif//__NL_GRAPHICS_H__