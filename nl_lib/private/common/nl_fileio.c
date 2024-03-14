#include "../nl_fileio.h"
#include "../nl_memory.h"

#include <stdio.h>

#ifdef __EMSCRIPTEN__
void fopen_s(FILE** file, const char* filename, const char* descript)
{
    *file = fopen(filename, descript);
}
#endif

void read_entire_file(const char* filename, file_contents* const contents)
{
    FILE* fp = {0};
    fopen_s(&fp, filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (char*)memory_allocate(sizeof(char) * file_size);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
        }
        else 
        {
            NL_LOG("Could not allocate memory for Contents");
        }
        fclose(fp);
    }
    else
    {
        NL_LOG("Failed to open file %s", filename);
    }
}

void clear_file_read(file_contents* const content)
{
    memory_free(content->content);
    
    content->size = 0;
    content->content = 0;
}

void save_to_binary_file(const char* const filename, unsigned int size, char* const contents)
{
    // Create file and write char* bytes of size to it
}
