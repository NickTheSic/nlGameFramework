#ifndef __NL_FILE_IO_H__
#define __NL_FILE_IO_H__

typedef struct file_contents file_contents;
struct file_contents
{
    unsigned int size;
    unsigned char* content;
};

void read_entire_file(const char* filename, file_contents* contents);
void clear_file_read(file_contents* content);

#endif //__NL_FILE_IO_H__