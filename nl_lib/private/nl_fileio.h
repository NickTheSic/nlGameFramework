#ifndef __NL_FILE_IO_H__
#define __NL_FILE_IO_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct file_contents file_contents;
struct file_contents
{
    size_t size;
    unsigned char* content;
};

// binary
void read_entire_file(const char* const filename, file_contents* const contents);
void clear_file_read(file_contents* const content);

// reads text file and sets the last char to a '\0'
void read_entire_text_file(const char* const filename, file_contents* const contents);

void save_to_binary_file(const char* const filename, unsigned int size, char* const content);
void load_from_binary_file(const char* const filename, unsigned int size, char* const dest);

// returns a pointer to the first '.' found 
const char* find_file_type_from_name(const char* const filename);

// helper for joining shader name to data/shaders to consolodate the string names I use
void load_shader_from_data(const char* filename, file_contents* const contents);
void load_sound_from_data(const char* filename, file_contents* const contents);

#ifdef __cplusplus
}
#endif

#endif //__NL_FILE_IO_H__