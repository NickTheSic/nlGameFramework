#ifndef __NL_WINDOWS_INCLUDE_H__
#define __NL_WINDOWS_INCLUDE_H__

// So I can include the windows header under the same circumstances always
#define NOMINMAX

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#undef far
#undef near

#endif