#ifndef __NL_FILE_IO_H__
#define __NL_FILE_IO_H__
#ifdef __cplusplus
extern "C" {
#endif

struct mesh;

typedef struct file_contents file_contents;
struct file_contents
{
    unsigned int size;
    char* content;
};


void read_entire_file(const char* const filename, file_contents* const contents);
void clear_file_read(file_contents* const content);


void save_to_binary_file(const char* const filename, unsigned int size, char* const content);
void load_from_binary_file(const char* const filename, unsigned int size, char* const dest);

void load_mesh_from_file(const char* const file, struct mesh* const mesh);

// returns a pointer to the first '.' found 
const char* find_file_type_from_name(const char* const filename);


#ifdef __cplusplus
}
#endif
#endif //__NL_FILE_IO_H__