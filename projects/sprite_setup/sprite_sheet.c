#include "sprite_sheet.h"
#include "private/nl_gl.h"
#include "private/nl_shader.h"

static const char* spritesheet_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"layout (location = 2) in vec2 aTexCoord;              \n"
"uniform mat4 uViewMat;                                \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"out vec2 oCoord;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = vec4(aPos, 1.0);                   \n"
"   vec4 viewPos = uViewMat * worldPos;                \n"
"   gl_Position = uProjMat * viewPos;                  \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* spritesheet_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"uniform sampler2D uText;                              \n"
"in vec4 oColor;                                       \n"
"in vec2 oCoord;                                       \n"
"void main() {                                         \n"
"    FragColor = texture(uText, oCoord) * oColor;      \n"
"}                                                     \0";

void init_sprite_sheet(spritesheet* const sheet, unsigned int batch_count, unsigned int sprite_count, v2i atlas_size)
{
    sheet->atlas_size = atlas_size;
    sheet->max_vertices = batch_count*4;
    sheet->max_sprites = sprite_count;
    const unsigned int max_indices = batch_count*6;

    sheet->shader_program = create_shader_program(spritesheet_vert_shader_code, spritesheet_fragment_shader_code);
    use_shader_program(sheet->shader_program);

    const size_t vertice_data_size = sizeof(sprite_vertex_data) * sheet->max_vertices;
    const size_t indice_data_size = sizeof(unsigned int) * max_indices;

    sheet->vertices = (sprite_vertex_data*)memory_allocate(vertice_data_size);

    glGenVertexArrays(1, &sheet->vao);
    glBindVertexArray(sheet->vao);

    glGenBuffers(1, &sheet->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, sheet->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertice_data_size, (void*)0, GL_DYNAMIC_DRAW);

    unsigned int *indices = (unsigned int*)memory_allocate(indice_data_size)
    unsigned int offset = 0;
    for (unsigned int i = 0; i < max_indices; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &sheet->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sheet->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW);

    memory_free(indices);

    stbi_set_flip_vertically_on_load(1);
    sheet->sprites = (sprite*)memory_allocate(sizeof(sprite) * sprite_count);

    glActiveTexture(GL_TEXTURE0); // Could make global variable and struct variable to define different textures?
    glGenTextures(1, &sheet->texture_id);
    glBindTexture(GL_TEXTURE_2D, sheet->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             atlas_size.x, atlas_size.y,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             0
             );
}

void free_sprite_sheet(spritesheet* sheet)
{
    memory_free(sheet->sprites);
    memory_free(sheet->vertices);
}