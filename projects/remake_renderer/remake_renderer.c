#include "nl_lib.h"
#include "private/gl/nl_gl.h"


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

unsigned int VBO = 0;

const char* rr_vertex_shader = 
"#version 330 core\n" 
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


void app_specific_init(void)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{
    glClearColor(0.2f,0.3f,0.8f,1.0f);
}

void app_specific_cleanup(void)
{

}