#include "../nl_fileio.h"
#include "../nl_memory.h"

#include <stdio.h>

#ifdef __EMSCRIPTEN__
void fopen_s(FILE** file, const char* filename, const char* descript)
{
    *file = fopen(filename, descript);
}
#endif

void read_entire_file(const char* filename, file_contents* contents)
{
    FILE* fp = {0};
    fopen_s(&fp, filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (unsigned char*)memory_allocate(sizeof(unsigned char) * file_size);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
        }
        fclose(fp);
    }
}
