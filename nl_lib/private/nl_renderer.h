#ifndef __NL_RENDERER_H__
#define __NL_RENDERER_H__

/////////////////////////////////////////////////////////////////
//                     Renderer System                         //
/////////////////////////////////////////////////////////////////
int initialize_renderer_subsystem();
void cleanup_renderer_subsystem(void);

void begin_render_frame();
void end_render_frame();
void renderer_swap_buffers();

/////////////////////////////////////////////////////////////////
//              Wrappers around GL specific calls              //
/////////////////////////////////////////////////////////////////
void set_background_colour_4f(float r, float g, float b, float a);
void set_viewport_size(int width, int height);
void set_wireframe_rendering(void);
void set_fill_rendering(void);
void set_depth_test_enabled(int enabled);

void set_cull_face_enabled(int enabled); 
void set_cull_face_side(int front);
void set_cull_front_face(int clockwise);

#endif