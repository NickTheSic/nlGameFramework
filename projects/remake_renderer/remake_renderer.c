#include "nl_lib.h"
#include "private/gl/nl_gl.h"
#include "third_party/stb/stb_image.h"

float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 0.0f, 1.0f 
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int VAO = 0;
unsigned int VBO = 0;
unsigned int EBO = 0;
unsigned int TextureID = 0;

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

    
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    unsigned char* data = stbi_load("data/images/fish.png", &width, &height, &channels, 0);

    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0, 
            GL_RGBA, 
            width, height, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            data
        );
    }

    stbi_image_free(data);


    rr_shader_program = load_shader_from_files("rr_shader.vs", "rr_shader.fs");
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

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
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureID);
   
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void app_specific_cleanup(void)
{

}