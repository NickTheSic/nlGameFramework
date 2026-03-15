#include "nl_lib.h"
#include "private/gl/nl_gl.h"

#include "rr_shader.c"


float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.8f,
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int VAO = 0;
unsigned int VBO = 0;
unsigned int EBO = 0;
unsigned int rr_shader_program = 0;

void app_specific_init(void)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    rr_shader_program = rr_create_shader_program();
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(rr_shader_program);

    glClearColor(0.2f,0.3f,0.8f,1.0f);
}

void app_specific_update(double dt)
{
    local_persist int triggered;
    local_persist float timer;
    timer += dt;

    if (timer > 2.0f)
    {
        timer -= 2.0f;
        if (!triggered){
            triggered = 1;
            set_wireframe_rendering();
        }
        else
        {
            triggered = 0;
            set_fill_rendering();
        }
    }
}

void app_specific_render(void)
{
    glUseProgram(rr_shader_program);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void app_specific_cleanup(void)
{

}