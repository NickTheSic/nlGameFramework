#include "../nl_renderer.h"
#include <vulkan/vulkan.h>

struct vk_render_system
{
    VkIntsance instance;
};
global_variable struct vk_render_system vk_renderer;

internal_function void vk_create_instance(void)
{
    VkApplicationInfo app_info = {0};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "nl_lib";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "nl_lib";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}

int initialize_renderer_subsystem(void)
{
    vk_create_instance();
}

void cleanup_renderer_subsystem(void)
{

}


void begin_render_frame(void)
{

}

void end_render_frame(void)
{

}

void renderer_swap_buffers(void)
{

}


/////////////////////////////////////////////////////////////////
//              Wrappers around GL specific calls              //
/////////////////////////////////////////////////////////////////

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
