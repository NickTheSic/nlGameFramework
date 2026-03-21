
//// Audio ////
int init_audio_system()
{
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void cleanup_audio_system()
{
    NL_UNIMPLEMENTED_FUNC
}

unsigned int load_sound_file(const char* const filename)
{
    NL_UNUSED(filename);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

void play_sound(unsigned int sound)
{
    NL_UNUSED(sound);
    NL_UNIMPLEMENTED_FUNC
}

void set_sound_to_loop(unsigned int sound)
{
    NL_UNUSED(sound);
    NL_UNIMPLEMENTED_FUNC
}


//// Delta Time ////
void init_delta_time()
{
    NL_UNIMPLEMENTED_FUNC;
}

double get_frame_delta_time()
{
    NL_UNIMPLEMENTED_FUNC;
    return 0.0;
}


//// Gamepad ////

int init_gamepad_system(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void udpate_gamepad(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

int get_pressed_buttons(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

unsigned char button_is_held(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

unsigned char button_was_pressed(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

unsigned char button_was_released(button_value_type button)
{
    NL_UNUSED(button);
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

void debug_test_controller(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

float get_right_trigger(void)
{
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

float get_left_trigger(void)
{
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

v2f get_left_stick(void)
{
    NL_UNIMPLEMENTED_FUNC
    return (v2f){0,0};
}

v2f get_right_stick(void)
{
    NL_UNIMPLEMENTED_FUNC
    return (v2f){0,0};
}


//// Platform ////
int platform_init(void)
{
    // We can compile with 0 and run but it shouldn't do much
    return 0;
}

void platform_cleanup(void)
{
    NL_UNIMPLEMENTED_FUNC
}

//// Renderer ////
int initialize_renderer_subsystem()
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

void begin_render_frame()
{
    NL_UNIMPLEMENTED_FUNC;
}

void end_render_frame()
{
    NL_UNIMPLEMENTED_FUNC;
}

void renderer_swap_buffers()
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_background_colour_4f(float r, float g, float b, float a)
{
    NL_UNUSED(r);NL_UNUSED(g);NL_UNUSED(b);NL_UNUSED(a);
    NL_UNIMPLEMENTED_FUNC;
}

void set_viewport_size(int width, int height)
{
    NL_UNUSED(width);NL_UNUSED(height);
    NL_UNIMPLEMENTED_FUNC;
}

void set_wireframe_rendering()
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_fill_rendering()
{
    NL_UNIMPLEMENTED_FUNC;
}

void set_depth_test_enabled(int enabled)
{
    NL_UNUSED(enabled);
    NL_UNIMPLEMENTED_FUNC;
}

void set_cull_face_enabled(int enabled)
{
    NL_UNUSED(enabled);
    NL_UNIMPLEMENTED_FUNC;
}
void set_cull_face_side(int front)
{
    NL_UNUSED(front);
    NL_UNIMPLEMENTED_FUNC;
}

void set_cull_front_face(int clockwise)
{    
    NL_UNUSED(clockwise);
    NL_UNIMPLEMENTED_FUNC;
}

//// Shader ////
unsigned int create_shader_program(const char* vertex_shader_code, const char* fragment_shader_code)
{
    NL_UNUSED(vertex_shader_code);
    NL_UNUSED(fragment_shader_code);
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

void use_shader_program(unsigned int shader_program)
{
    NL_UNUSED(shader_program);
    NL_UNIMPLEMENTED_FUNC;
}

void free_shader_program(unsigned int shader_program)
{
    NL_UNUSED(shader_program);
    NL_UNIMPLEMENTED_FUNC;
}

unsigned int create_common_shader_program()
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

unsigned int get_uniform_loc(unsigned int program, const char* name)
{
    NL_UNUSED(program); NL_UNUSED(name);
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

void set_uniform_mat4x4f(unsigned int loc, const float* mat)
{
    NL_UNUSED(loc); NL_UNUSED(mat);
    NL_UNIMPLEMENTED_FUNC;
}


//// Window ////
// Avoid link errors for null platforms
PFNWINDOWSIZECALLBACK pfn_window_size_callback;

int initialize_window(int width, int height, const char* title)
{
    NL_UNUSED(width); NL_UNUSED(height); NL_UNUSED(title);
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void poll_events(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

int window_active(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return 1;
}

void window_request_close(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

void window_swap_buffers(void)
{
    NL_UNIMPLEMENTED_FUNC;
}

v2i get_screen_size(void)
{
    NL_UNIMPLEMENTED_FUNC;
    return (v2i){0,0};
}

void set_window_title(const char* title)
{
    NL_UNUSED(title);
    NL_UNIMPLEMENTED_FUNC;
}


//// Scoped Timer ////
#if NL_DEBUG_ENABLED

double debug_get_system_time()
{
    NL_UNIMPLEMENTED_FUNC
    return 0;
}

void debug_end_scope_timer(debug_scope_timer* const st)
{
    NL_UNUSED(st);
    NL_UNIMPLEMENTED_FUNC;
}

#endif