#ifndef __NL_MY_UI_TYPES_H__
#define __NL_MY_UI_TYPES_H__


/* Assumes 0,0 ----------- 1,0
            |               |
            |               |
            |               |
           0,1 ----------- 1,1
*/
typedef struct ui_camera ui_camera;
struct ui_camera
{
    mat4x4f matrix;
};
void ui_camera_initialize_screen_size(ui_camera *const camera, v2i screen_size);



typedef unsigned int ui_sprite_handle;

typedef struct ui_element_data ui_element_data;
struct ui_element_data
{
    v2i anchor;
    v2f position;
    v2f size;
    ui_sprite_handle sprite;
};



#endif //__NL_MY_UI_TYPES_H__