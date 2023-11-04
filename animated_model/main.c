#include "nl_lib.h"
#include "nl_gl.h"

#include <stdio.h>

typedef struct file_contents file_contents;
struct file_contents
{
    unsigned int size;
    unsigned char* content;
};

void ReadEntireFile(const char* filename, file_contents* contents)
{
    FILE* fp = {0};
    fopen_s(&fp, filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (char*)malloc(sizeof(char) * file_size);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
        }
        fclose(fp);
    }
}

typedef struct mesh mesh;
struct mesh
{
    int unused;    
};
mesh the_thing = {0};

void generate_mesh(file_contents* content)
{

}

void run()
{
    poll_events();
    begin_render_frame();
    
    end_render_frame();
}

int main(int count, char** args)
{
    if (!initialize_window(800,800, "Sandbox Mode"))
    {
        return -1;
    }

    if (!initialize_renderer_subsystem())
    {
        return -1;
    }
    set_background_colour_4f(0.4f,0.6f,0.8f,1.0f);

    file_contents contents = {0};
    ReadEntireFile("BaseObj.obj", &contents);

    generate_mesh(&contents);

#ifdef _WIN32
    while (window_active())
    {
        run();
    }
#elif defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(run, 0, 1);
#endif

    free (contents.content);

    return 0;
}
