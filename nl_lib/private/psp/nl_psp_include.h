#ifndef __NL_PSP_INCLUDE_H__
#define __NL_PSP_INCLUDE_H__

// Just a helper file for now while I figure things out
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

// TODO: Placing this here for testing purposes as this is PSP specific
// in the future will consider moving this somewhere else to be changed per project
//     name,user_or_kernel,version_major,version_minor
PSP_MODULE_INFO("NL LIB", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);

#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 272
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT BUFFER_HEIGHT

#endif//__NL_PSP_INCLUDE_H__