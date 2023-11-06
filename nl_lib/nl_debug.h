#ifndef __NL_DEBUG_H__
#define __NL_DEBUG_H__

#include <stdio.h>

#define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");

#define internal_function static
#define global_variable static;
#define local_persist static

#endif //__NL_DEBUG_H__