#include "nl_rr_sprite.h"
#include "private/gl/nl_gl.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


nl_rr_sprite create_simple_rr_sprite(const char* filename)
{
    nl_rr_sprite new_sprite = {0};

    glGenVertexArrays(1, &new_sprite.VAO);
    glBindVertexArray(new_sprite.VAO);

    glGenBuffers(1, &new_sprite.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, new_sprite.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &new_sprite.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_sprite.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenTextures(1, &new_sprite.TextureID);
    glBindTexture(GL_TEXTURE_2D, new_sprite.TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return (new_sprite);
}

void render_simple_rr_sprite(nl_rr_sprite spr)
{
    glBindVertexArray(spr.VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, spr.TextureID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spr.EBO);
   
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
