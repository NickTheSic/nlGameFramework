#include "../nl_window.h"
#include "../nl_input.h"
#include "../nl_renderer.h"
#include "../nl_debug.h"
#include "nl_win32_include.h"

typedef struct win32_window win32_window;
struct win32_window
{
    HWND  window;
    HDC   device;
    HGLRC context;

    int running;
};
global_variable win32_window g_window;

PFNWINDOWSIZECALLBACK pfn_window_size_callback = {0};

internal_function LRESULT CALLBACK 
window_proc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = {0};

    switch (msg)
    {
		case WM_CLOSE:
		{
			NL_LOG("Close Message");
			g_window.running = 0;
			DestroyWindow(window);
		}break;

        case WM_DESTROY:
		{
			NL_LOG("Destroy Message");
            PostQuitMessage(0);
		}break;

		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			NL_LOG("New Width: %i Height: %i", width, height);
			set_viewport_size(width, height);
			
			if (pfn_window_size_callback != 0)
			{
				pfn_window_size_callback(width, height);
			}
		} break;

		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		{
			nl_key k = (nl_key)wParam;
			set_key_state_down(k);
		} break;

		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			nl_key k = (nl_key)wParam;
			set_key_state_up(k);
		} break;

		case WM_LBUTTONDOWN:
		{
			set_mouse_button_down(NL_MOUSE_BUTTON_LEFT);
		} break;
	
		case WM_LBUTTONUP:
		{
			set_mouse_button_up(NL_MOUSE_BUTTON_LEFT);
		} break;
	
		case WM_RBUTTONDOWN:
		{
			set_mouse_button_down(NL_MOUSE_BUTTON_RIGHT);
		} break;
	
		case WM_RBUTTONUP:
		{
			set_mouse_button_up(NL_MOUSE_BUTTON_RIGHT);
		} break;

		case WM_MOUSEWHEEL:
		{
			short mouse_delta = GET_WHEEL_DELTA_WPARAM(wParam);
			short modifier = GET_KEYSTATE_WPARAM(wParam);
			
			add_mouse_scroll(mouse_delta);
		} break;

		case WM_MOUSEMOVE:
		{
			set_mouse_position_from_system(GET_X_LPARAM(lParam), get_screen_size().y - GET_Y_LPARAM(lParam));
		} break;

        default:
        {
            result = DefWindowProcW(window,msg, wParam, lParam);
        } break;
    }

    return (result);
}

void poll_events()
{
    MSG msg = {0};
    //while (PeekMessage(&msg, g_window.window, 0, 0, PM_REMOVE) != 0)
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int window_active()
{
    return g_window.running;
}

int initialize_window(int width, int height, const char* title)
{
    DWORD dw_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD dw_style = WS_OVERLAPPEDWINDOW;

    wchar_t wide_title[50] = {0};
    {
        // todo Assert old_length <= 50
        size_t old_length = strlen(title) + 1;
        size_t converted = 0;
        mbstowcs_s(&converted, wide_title, old_length, title, _TRUNCATE);
    }

    RECT window_rect = {0};
    window_rect.left = (long)0;
    window_rect.right = (long)width;
    window_rect.top = (long)0;
    window_rect.bottom = (long)height;

    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = window_proc;
	wc.hInstance = GetModuleHandle(0);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpszClassName = wide_title;
	wc.cbClsExtra = 0;                              // No extra window data.
	wc.cbWndExtra = 0;                              // No extra window data.
	wc.hIcon = LoadIcon(0, IDI_WINLOGO);            // Load the default icon.
	wc.hCursor = LoadCursor(0, IDC_ARROW);          // Load the arrow pointer.
	wc.hbrBackground = 0;                     // No background required for GL.
	wc.lpszMenuName = 0; 

    if (!RegisterClassExW(&wc))
    {
        return 0;
    }

    AdjustWindowRectEx(&window_rect, dw_style, 0, dw_ex_style);

    g_window.window = CreateWindowExW(
        dw_ex_style,
		wc.lpszClassName,
		wide_title,
		dw_style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(window_rect.right - window_rect.left),
		(window_rect.bottom - window_rect.top),
		NULL, NULL, GetModuleHandle(0),
		0
    );

    if (g_window.window == 0)
    {
        return 0;
    }

    g_window.device = GetDC(g_window.window);
    if (g_window.device == 0)
    {
        return 0;
    }

    //@todo: Learn more about zbits and stencil bits
	BYTE colorbits = 32;
	BYTE zbits = 31;
	BYTE stencilbits = 1;
	PIXELFORMATDESCRIPTOR pfd =  // pfd tells Windows how we want things to be.
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // Size of this pixel format descriptor.
		1,                              // Version number.
		PFD_DRAW_TO_WINDOW |            // Format must support window.
		PFD_SUPPORT_OPENGL |            // Format must support opengl.
		PFD_DOUBLEBUFFER,               // Must support double buffering.
		PFD_TYPE_RGBA,                  // Request an rgba format.
		(BYTE)colorbits,                // Select our color depth.
		0, 0, 0, 0, 0, 0,               // Color bits ignored.
		0,                              // No alpha buffer.
		0,                              // Shift bit ignored.
		0,                              // No accumulation buffer.
		0, 0, 0, 0,                     // Accumulation bits ignored.
		(BYTE)zbits,                    // Bits for z-buffer (depth buffer).
		(BYTE)stencilbits,              // Stencil bits.
		0,                              // No auxiliary buffer.
		PFD_MAIN_PLANE,                 // Main drawing layer.
		0,                              // Reserved.
		0, 0, 0                         // Layer masks ignored.
	};

    unsigned int pixel_format = ChoosePixelFormat((HDC)g_window.device, &pfd);

	if (!pixel_format)
	{
		return 0;
	}

	if (!SetPixelFormat(g_window.device, pixel_format, &pfd))
	{
        return 0;
	}

	g_window.context = wglCreateContext(g_window.device);
	if (g_window.context == 0)
	{
		return 0;
	}

	if (!wglMakeCurrent(g_window.device, g_window.context))
	{
		return 0;
	}

	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwap = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwap != 0)
	{
		wglSwap(0);
	}

	// Displays the graphics card used
	{
		char* rendererString;
		rendererString = (char*)glGetString(GL_RENDERER);
		if (rendererString) fprintf(stderr, "%s\n", rendererString);
	}

	// calculate DPI for scaling
	{
		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

		const UINT dpi = GetDpiForWindow(g_window.window);
		AdjustWindowRectExForDpi(&window_rect, dw_style, 0, dw_ex_style, dpi);
		SetWindowPos(
			g_window.window,
			0,
			window_rect.left,
			window_rect.top,
			window_rect.right - window_rect.left,
			window_rect.bottom - window_rect.top,
			SWP_NOMOVE);
	}

	ShowWindow(g_window.window, SW_SHOW);
	SetForegroundWindow(g_window.window);
	SetFocus(g_window.window);

    g_window.running = 1;

    return 1;
}

void window_swap_buffers()
{
	SwapBuffers(g_window.device);
}

void window_request_close()
{
	NL_LOG("Requesting window Close");
	//PostQuitMessage(WM_QUIT);
	SendMessage(g_window.window, WM_CLOSE, 0, 0);
}

v2i get_screen_size()
{	
	RECT rect = {0};
	GetClientRect(g_window.window, &rect);

	return (v2i){rect.right - rect.left, rect.bottom - rect.top};
}

void set_window_title(const char* title)
{
	SetWindowTextA(g_window.window, title);
}

void set_window_size_callback(PFNWINDOWSIZECALLBACK callback)
{
	pfn_window_size_callback = callback;
}
