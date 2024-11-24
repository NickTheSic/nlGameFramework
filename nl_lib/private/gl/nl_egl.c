#include "nl_egl.h"

EGLRenderer g_EGLRenderer;

//TODO: Seems like different platforms may have different requirements

int initialize_gles(NativeWindowType platform_window)
{
    EGLint const attribute_list[] = 
	{ 
		EGL_RED_SIZE, 8, 
		EGL_GREEN_SIZE, 8, 
		EGL_BLUE_SIZE, 8, 
		EGL_ALPHA_SIZE, 8, 
		EGL_NONE 
	};

	EGLint const context_config[] = 
	{ 
		EGL_CONTEXT_CLIENT_VERSION , 2, 
		EGL_NONE 
	};

	EGLint num_config = {};
	EGLConfig config = {};

	g_EGLRenderer.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!g_EGLRenderer.display)
	{
		NL_LOG("Could not get egl Display: %d", eglGetError());
		goto _fail0;
	}

	if (eglBindAPI(NL_EGL_API) == EGL_FALSE)
    {
        NL_LOG("Could not set API! error: %d", eglGetError());
        goto _fail1;
    }

	eglInitialize(g_EGLRenderer.display, NULL, NULL);
	eglChooseConfig(g_EGLRenderer.display, attribute_list, &config, 1, &num_config);
	if (num_config == 0)
	{
		NL_LOG("Unable to Choose EGL Config: %d", eglGetError());
		goto _fail1;
	}
		
	/* create an EGL rendering context */
	g_EGLRenderer.surface = eglCreateWindowSurface(g_EGLRenderer.display, config, platform_window, NULL);
	if (!g_EGLRenderer.surface)
	{
		NL_LOG("Could not create EGL surface: %d", eglGetError());
		goto _fail2;
	}

	g_EGLRenderer.context = eglCreateContext(g_EGLRenderer.display, config, EGL_NO_CONTEXT, context_config);
		
	eglMakeCurrent(g_EGLRenderer.display, g_EGLRenderer.surface, g_EGLRenderer.surface, g_EGLRenderer.context);
	return 1;

	// from devkit pro graphics example. I like this idea to de init and then return
_fail2:
    eglDestroySurface(g_EGLRenderer.display, g_EGLRenderer.surface);
    g_EGLRenderer.surface = 0;
_fail1:
    eglTerminate(g_EGLRenderer.display);
    g_EGLRenderer.display = 0;
_fail0:
    return 0;
}
