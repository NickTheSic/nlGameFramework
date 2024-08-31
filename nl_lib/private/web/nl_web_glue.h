
// The following two functions do not exist with emscripten
// this is so code can be compiled between the 2

#ifdef __EMSCRIPTEN__

#include "stdarg.h" //__va_list__
#include "string.h" // strtok

// static char* strtok_s(char* buffer, char* delim, char** ptr)
// {
//     (void)(ptr);
//     return strtok(buffer, delim);
// }
#define sscanf_s(line, str, ...) sscanf(line, str, __VA_ARGS__);

#endif