#ifndef __NL_DEBUG_H__
#define __NL_DEBUG_H__

#include <stdio.h>

#define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");
#define NL_UNIMPLEMENTED_FUNC NL_LOG("Unimplemented Function %s in %s", __FUNCTION__, __FILE__);

#define internal_function static
#define global_variable static
#define local_persist static

#define NL_UNUSED(x) (void)(x)

#endif //__NL_DEBUG_H__