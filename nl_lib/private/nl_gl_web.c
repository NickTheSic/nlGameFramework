#include "../nl_gl.h"

global_variable EGLRenderer g_EGLRenderer;

int initialize_gl()
{
    EmscriptenWebGLContextAttributes attr = {};
    emscripten_webgl_init_context_attributes(&attr);

    EGLint const attribute_list[] = { EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_NONE };
	EGLint const context_config[] = { EGL_CONTEXT_CLIENT_VERSION , 2, EGL_NONE };
	EGLint num_config = {};
	EGLConfig config = {};

	g_EGLRenderer.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(g_EGLRenderer.display, NULL, NULL);
	eglChooseConfig(g_EGLRenderer.display, attribute_list, &config, 1, &num_config);
		
	/* create an EGL rendering context */
	g_EGLRenderer.surface = eglCreateWindowSurface(g_EGLRenderer.display, config, 0, NULL);
	g_EGLRenderer.context = eglCreateContext(g_EGLRenderer.display, config, EGL_NO_CONTEXT, context_config);
		
	eglMakeCurrent(g_EGLRenderer.display, g_EGLRenderer.surface, g_EGLRenderer.surface, g_EGLRenderer.context);

    return 1;
}
