#include "nl_lib.h"

 int png_first_eight_bytes[] =  {137, 80, 78, 71, 13, 10, 26, 10};

 typedef struct ihrd_chunk ihrd_chunk;
 struct ihrd_chunk
 {
    int width;
    int height;
    char bit_depth;
    char color_type;
    char compression_method;
    char filter_method;
    char interlace_method;
 };

extern void app_specific_init(void)
{

}

extern void app_specific_update(double dt)
{
    
}
