#include "nl_graphics.h"

void draw_line(float startx, float starty, float endx, float endy)
{

}

void draw_line_v(v2f start, v2f end)
{
    draw_line(start.x, start.y, end.x, end.y);
}

void draw_sprite(float x, float y, float w, float h, float u, float v)
{

}

void draw_sprite_v(v2f pos, v2f size, v2f uv)
{
    draw_sprite(pos.x, pos.y, size.x, size.y, uv.x, uv.y);
}

