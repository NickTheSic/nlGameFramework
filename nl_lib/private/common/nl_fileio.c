#include <private/nl_fileio.h>
#include <private/nl_memory.h>
#include <private/nl_debug.h>
#include <private/nl_vertex_data.h>

#include <stdio.h>
#include <string.h>

void read_entire_file(const char* filename, file_contents* const contents)
{
    FILE* fp = fopen(filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (unsigned char*)memory_allocate(sizeof(char) * file_size);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
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

void read_entire_text_file(const char* const filename, file_contents* const contents)
{
    FILE* fp = fopen(filename, "r");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        // add 1 for the null terminated end of file
        file_size += 1;

        contents->size = file_size;
        contents->content = (unsigned char*)memory_allocate(sizeof(char) * file_size);
        if (contents->content)
        {
            // Don't actually read the file size since that may be out of scope
            fread(contents->content, file_size-1, 1, fp);
            contents->content[file_size-1] = '\0';
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
    memory_free(content->content);
    
    content->size = 0;
    content->content = 0;
}

void save_to_binary_file(const char* const filename, unsigned int size, char* const contents)
{
    FILE* fp = fopen(filename, "wb");

    if (fp)
    {
        fwrite(contents, 1, size, fp);
        fclose(fp);
    }
}

void load_from_binary_file(const char* const filename, unsigned int size, char* const dest)
{
    FILE* fp = fopen(filename, "rb");
    
    if (fp)
    {
        fread(dest, 1, size, fp);
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

#if 1
#define DBUG_STR_JOIN_LOG NL_LOG("NL_FILEIO: Joining string path as: %s", path);
#else
#define DBUG_STR_JOIN_LOG(path)
#endif

// NOTE: The following functions provide a unique use case for
// Finding the file extension and then loading as "data/EXT/filename"
// Would require a named data dir for each.  (March 14/2026)

// NOTE: the path size is:
// 1. the length of the starting string
// 2. Estimated max size for my own asset
// 3. possible file ext length

// Entirely overcomplicated! I still need to add the file ext 

void load_sound_from_data(const char* filename, file_contents* const contents)
{
    char path[9+23+4] = "data/sfx/";
    strcat(path, filename);

    DBUG_STR_JOIN_LOG

    read_entire_file(path, contents);
}

void load_shader_from_data(const char* filename, file_contents* const contents)
{
    char path[13+22+3] = "data/shaders/";
    strcat(path, filename);

    DBUG_STR_JOIN_LOG

    read_entire_text_file(path, contents);
}

