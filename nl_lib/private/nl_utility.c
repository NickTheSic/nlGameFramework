#include "../nl_utility.h"

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
