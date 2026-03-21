#include <private/nl_fileio.h>
#include <private/nl_memory.h>
#include <private/nl_debug.h>

#include <stdio.h>
#include <string.h>

void read_entire_file(const char* filename, file_contents* const contents, nl_bump_allocator* const allocator)
{
    FILE* fp = fopen(filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (unsigned char*)bump_alloc(allocator, sizeof(char) * file_size + 1);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
            contents->content[file_size] = 0;
        }
        else 
        {
            NL_LOG("NL_FILEIO: Could not allocate memory for Contents");
        }
        fclose(fp);
    }
    else
    {
        NL_LOG("NL_FILEIO: Failed to open file %s", filename);
    }
}

void clear_file_read(file_contents* const content)
{
    //memory_free(content->content);
    
    content->size = 0;
    content->content = 0;
}

void save_to_binary_file(const char* const filename, unsigned int size, char* const contents)
{
    FILE* fp = fopen(filename, "wb");

    if (fp)
    {
        fwrite(contents, size, 1, fp);
        fclose(fp);
    }
}

void load_from_binary_file(const char* const filename, unsigned int size, char* const dest)
{
    FILE* fp = fopen(filename, "rb");
    
    if (fp)
    {
        fread(dest, size, 1, fp);
        fclose(fp);
    }
}

const char* find_file_type_from_name(const char* const filename)
{
    size_t name_length = strlen(filename);
    const char* file_type = &filename[name_length-1];

    for (size_t i = name_length - 1; i > 0; --i)
    {
        file_type = &filename[i];
        if (file_type[0] == '.')
        {
            break;
        }
    }

    return file_type;
}



// NOTE: The following functions provide a unique use case for
// Finding the file extension and then loading as "data/EXT/filename"
// Would require a named data dir for each.  (March 14/2026)

// NOTE: the path size is:
// 1. the length of the starting string
// 2. Estimated max size for my own asset
// 3. possible file ext length

// Entirely overcomplicated! I still need to add the file ext 

//NOTE: March 2026: Debug verify string length may crash the program but at least I have it show in the log before hand!

#if NL_DEBUG_ENABLED
#define NL_DEBUG_STR_JOIN_LOG(); NL_LOG("NL_FILEIO: Joining string path as: %s", path);
#define NL_DEBUG_VERIFY_STR_LENGTH(str1, str2, max); {if (strlen(str1)+strlen(str2)>max){NL_LOG("NL_FILEIO: String size of joined string is greater than the max!: %s", str1); return;}}
#else
#define NL_DEBUG_STR_JOIN_LOG(path);
#define NL_DEBUG_VERIFY_STR_LENGTH(str1, str2, max);
#endif

#define NL_PATH_JOIN_BUFFER_SIZE 64

void load_sound_from_data(const char* filename, file_contents* const contents, nl_bump_allocator* const allocator)
{
    char path[NL_PATH_JOIN_BUFFER_SIZE] = "data/sfx/";

    NL_DEBUG_VERIFY_STR_LENGTH(filename, path, NL_PATH_JOIN_BUFFER_SIZE);
    
    strcat(path, filename);
    NL_DEBUG_STR_JOIN_LOG();

    read_entire_file(path, contents, allocator);
}

void load_shader_from_data(const char* filename, file_contents* const contents, nl_bump_allocator* const allocator)
{
    char path[NL_PATH_JOIN_BUFFER_SIZE] = "data/shaders/";

    NL_DEBUG_VERIFY_STR_LENGTH(filename, path, NL_PATH_JOIN_BUFFER_SIZE);

    strcat(path, filename);
    NL_DEBUG_STR_JOIN_LOG();

    read_entire_file(path, contents, allocator);
}

// I doubt I would use this elsewhere but this seems like a good practice to undef it

#undef NL_DEBUG_STR_JOIN_LOG
#undef NL_DEBUG_VERIFY_STR_LENGTH
#undef NL_PATH_JOIN_BUFFER_SIZE
