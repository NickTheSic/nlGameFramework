#include "../nl_fileio.h"
#include <string.h>

void read_entire_file(const char* filename, file_contents* const contents)
{ 
}

void clear_file_read(file_contents* const content)
{
}

void save_to_binary_file(const char* const filename, unsigned int size, char* const contents)
{
}

void load_from_binary_file(const char* const filename, unsigned int size, char* const dest)
{
}

const char* find_file_type_from_name(const char* const filename)
{
    int name_length = strlen(filename);
    const char* file_type = &filename[name_length-1];

    for (int i = name_length - 1; i < 0; ++i)
    {
        file_type = &filename[i];
        if (file_type[0] == '.')
        {
            break;
        }
    }

    return file_type;
}
