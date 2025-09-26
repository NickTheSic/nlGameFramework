#ifndef __NL_WINDOWS_INCLUDE_H__
#define __NL_WINDOWS_INCLUDE_H__

// So I can include the windows header under the same circumstances always
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS

#include <windows.h>
#include <windowsx.h>

#if 1
#include <xaudio2.h>
#endif

#undef far
#undef near

#endif