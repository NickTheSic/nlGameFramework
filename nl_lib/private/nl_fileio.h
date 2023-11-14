#ifndef __NL_FILE_IO_H__
#define __NL_FILE_IO_H__

typedef struct file_contents file_contents;
struct file_contents
{
    unsigned int size;
    char* content;
};

void read_entire_file(const char* const filename, file_contents* const contents);
void clear_file_read(file_contents* const content);

#endif //__NL_FILE_IO_H__