#include "nl_lib.h"
#include "nl_gl.h"

typedef struct mesh mesh;
struct mesh
{
    int unused;    
};
mesh the_thing = {0};

void generate_mesh(mesh* mesh, file_contents* content)
{
    
}

void app_specific_init()
{
    file_contents contents = {0};
    read_entire_file("BaseObj.obj", &contents);

    generate_mesh(&the_thing, &contents);
}

void app_specific_update()
{

}
