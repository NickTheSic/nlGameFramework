#ifndef __NL_RENDERER_H__
#define __NL_RENDERER_H__

#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////
//                     Renderer System                         //
/////////////////////////////////////////////////////////////////
int initialize_renderer_subsystem(void);
void cleanup_renderer_subsystem(void);

void begin_render_frame(void);
void end_render_frame(void);
void renderer_swap_buffers(void);

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


#ifdef __cplusplus
}
#endif

#endif