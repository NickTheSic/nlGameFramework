#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#ifdef PSP 
#include <stb_image.h> //PSP Sdk contains it's own version unlike the one I have included
#else
#include "main_stb_image.h"
#endif