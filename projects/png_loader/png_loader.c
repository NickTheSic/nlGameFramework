#include "nl_lib.h"

#define FOUR_CC(str) (str[0] << 24  | str[1] << 16 | str[2] << 8 | str[3])

typedef struct first_eight_png_bytes first_eight_png_bytes;
struct first_eight_png_bytes
{
   unsigned char arr[8];
};

typedef struct png_chunk_layout png_chunk_layout;
struct png_chunk_layout
{
   int length;
   int type;
   // data
   //crc
};

typedef struct ihdr_chunk ihdr_chunk;
struct ihdr_chunk
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
   file_contents pic = {0};
   read_entire_file("data/test_sprite.png", &pic);

   first_eight_png_bytes* eight_bytes = (first_eight_png_bytes*)pic.content;

   int increment = sizeof(first_eight_png_bytes);


   while (increment < pic.size)
   {
      png_chunk_layout* const current_header = (png_chunk_layout*)(pic.content + increment);
      increment += sizeof(png_chunk_layout);

      if (current_header->type == (int)FOUR_CC("IHDR"))
      {
         ihdr_chunk *hrd = (ihdr_chunk*)(pic.content + increment);

         increment += sizeof(ihdr_chunk);
      }

      else if (current_header->type == (int)(FOUR_CC("IEND")))
      {
         break;
      }
   }

}

extern void app_specific_update(double dt)
{
    
}
