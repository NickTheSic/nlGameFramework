#include "nl_rr_sprite.h"
#include "private/gl/nl_gl.h"
#include "third_party/stb/stb_image.h"
#include <string.h>

global_variable nl_rr_vertex_data vertices[] = {
    {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-1.0f,  1.0f, 0.0f}, {0.8f, 0.2f, 0.8f}, {0.0f, 1.0f}},
};

global_variable unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


void create_simple_rr_sprite(const char* filename, nl_rr_sprite* const rr_sprite)
{
    glGenVertexArrays(1, &rr_sprite->VAO);
    glGenBuffers(1, &rr_sprite->VBO);
    glGenBuffers(1, &rr_sprite->EBO);
    
    glBindVertexArray(rr_sprite->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, rr_sprite->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rr_sprite->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Need to bind this items here.  each attribute takes is managed by a VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nl_rr_vertex_data), (void*)offsetof(nl_rr_vertex_data, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nl_rr_vertex_data), (void*)offsetof(nl_rr_vertex_data, colour));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(nl_rr_vertex_data), (void*)offsetof(nl_rr_vertex_data, uv));
    glEnableVertexAttribArray(2);


    glGenTextures(1, &rr_sprite->TextureID);
    glBindTexture(GL_TEXTURE_2D, rr_sprite->TextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    
    char path[64] = "data/images/";
    strcat(path, filename);

    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

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
    else
    {
        NL_LOG("Failed to load image with STBI");
    }

    stbi_image_free(data);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    create_identity_matrix(&rr_sprite->transform);
    scale_matrix_2f(&rr_sprite->transform, (v2f){width,height});
}

void render_simple_rr_sprite(nl_rr_sprite* const spr)
{
    glBindVertexArray(spr->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, spr->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spr->EBO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, spr->TextureID);
   
    unsigned int model_loc = get_uniform_loc(rr_shader_program, "uModelTransform");
    set_uniform_mat4x4f(model_loc, &spr->transform.m11);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void free_simple_rr_sprite(nl_rr_sprite* const sprite)
{
    glDeleteBuffers(1, &sprite->EBO);
    glDeleteBuffers(1, &sprite->VBO);
    glDeleteVertexArrays(1, &sprite->VAO);
    glDeleteTextures(1, &sprite->TextureID);

    sprite->EBO = sprite->VBO = sprite->VAO = sprite->TextureID = 0;
}
