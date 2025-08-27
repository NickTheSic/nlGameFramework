#ifndef __NL_PLATFORM_H__
#define __NL_PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif

// Note: Not really needed if I have platform specific main files

int platform_init(void);
void platform_cleanup(void);


#ifdef __cplusplus
}
#endif

#endif//__NL_PLATFORM_H__