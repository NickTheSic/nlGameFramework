#include "nl_mesh.h"
#include "private/gl/nl_gl.h"


internal_function void parse_vertices_indices(const file_contents *const content, int*const vertices, int*const indices, int*const face_value_count)
{
    int vertice_count = 0;
    int indice_line_count = 0;
    int face_values = 0;

    char* buffer = (char*)memory_allocate(content->size * sizeof(char));
    memcpy(buffer, content->content, content->size * sizeof(char));

    char* next_token = 0;

    // creating a new buffer based of data since strtok will replace "\n" with a "\0" and return that buffer....
    char* line = strtok_s(buffer, "\n", &next_token);

    while (line)
    {
        if (line[0] == 'v')
        {
            // TODO: Handle vn, vt
            if (line[1] == ' ')
            {
                vertice_count++;
            }
        }

        else if (line[0] == 'f')
        {
            if (face_values == 0)
            {
                char* cline = line;
                while (*cline != '\0')
                {
                    if (*cline == '\0')
                    {
                        break;
                    }
                    else if (*cline == ' ')
                    {
                        face_values++;
                    }
                    else if (*cline == '/')
                    {
                        NL_LOG("Have not handled how to parse / yet but this model contains one");
                    }
                    cline++;
                }
                NL_LOG("Face Values = %d", face_values);
            }

            indice_line_count++;
        }

        line = strtok_s(0, "\n", &next_token);
    }

    // TODO: Probably should null check
    //Until I encounter a scenario where I want values to be null
    //I will wait to see if I ever encounter a crash here
    *vertices = vertice_count;
    *indices = indice_line_count;
    *face_value_count = face_values;

    memory_free(buffer);
}

void load_mesh_from_file(const char* const file, mesh* const mesh)
{
    NL_LOG("Loading Mesh %s", file);

    int vertice_count = 0;
    int indice_line_count = 0;
    int face_values = 0;

    file_contents loaded_mesh;

    read_entire_file(file, &loaded_mesh);

    parse_vertices_indices(&loaded_mesh, &vertice_count, &indice_line_count, &face_values);

    if (face_values != 3)
    {
        NL_LOG("There seems to be an error. Face Values is: %d.", face_values);
        NL_LOG("We currently only support face values of 3");
    }

    NL_LOG("Vertices: %d, Indices line count: %d, Face Values: %d", vertice_count, indice_line_count, face_values);
    
    const int indice_count = indice_line_count * 3;
    vertex_data* vd = (vertex_data*)memory_allocate(vertice_count * sizeof(vertex_data));
    unsigned int* indices =  (unsigned int*)memory_allocate(indice_count * 3 * sizeof(unsigned int));

    int position_in_vertex_data = 0;
    int position_in_indice_data = 0;

    char* buffer = (char*)memory_allocate(loaded_mesh.size * sizeof(char));
    memcpy(buffer, loaded_mesh.content, loaded_mesh.size * sizeof(char));

    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);

    while (line)
    {
        if (line[0] == 'v')
        {
            v3f pos;
            sscanf_s(line, "v %f %f %f", &pos.x, &pos.y, &pos.z);

            vertex_data* const vd0 = &vd[position_in_vertex_data];
            vd0->pos.x = pos.x;
            vd0->pos.y = pos.y;
            vd0->pos.z = pos.z;


#if 1
            DO_ONCE(NL_LOG("Without proper shading we have debug colouring")); 

            //so the mesh isn't completely white for now
            {
                local_persist float colour_shift;

                vd0->color.r = colour_shift;
                colour_shift += 0.1912354f;
                vd0->color.g = colour_shift;
                colour_shift += 0.11244212;
                vd0->color.b = colour_shift;
                if (colour_shift - 0.5f < 0)
                    colour_shift += 0.326;
                vd0->color.a = 1.0f;

                if (colour_shift > 1.0f) colour_shift -= 1.0f;
            }
#else
            vd0->color = (colourf){1.f,1.f,1.f,1.f};
#endif

            ++position_in_vertex_data;
        }

        else if (line[0] == 'f')
        {
            int i1, i2, i3;
            sscanf_s(line, "f %d %d %d", &i1, &i2, &i3);

            unsigned int* const ind = &indices[position_in_indice_data];
            ind[0] = i1-1;
            ind[1] = i2-1;
            ind[2] = i3-1;
            position_in_indice_data += 3;
        }

        line = strtok_s(0, "\n", &next_token);
    }

    generate_mesh_using_vertices_and_indices(mesh, vd, vertice_count, indices, indice_count);

    memory_free(buffer);
    memory_free(indices);
    memory_free(vd);
    clear_file_read(&loaded_mesh);
}

void generate_mesh_using_vertices_and_indices(mesh* const mesh, const vertex_data* const vertices, int vertice_count, const unsigned int* const indices, unsigned int indice_count)
{
    const size_t vertices_data_size = sizeof(vertex_data) * vertice_count;
    const size_t indice_data_size = indice_count * sizeof(unsigned int);

    mesh->vertices = (vertex_data*)memory_allocate(vertices_data_size);
    memcpy(mesh->vertices, vertices, vertices_data_size);

    mesh->indices = (unsigned int*)memory_allocate(indice_data_size);
    memcpy(mesh->indices, indices, indice_data_size);

    mesh->vertice_count = vertice_count;
    mesh->indice_count = indice_count;

    glGenVertexArrays(1, &mesh->VAO);
    glBindVertexArray(mesh->VAO);

    glGenBuffers(1, &mesh->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_data_size, vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &mesh->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, color));
    glEnableVertexAttribArray(1);  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_single_mesh(mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

    glDrawElements(GL_TRIANGLES, mesh->indice_count, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void free_mesh(mesh* const mesh)
{
    memory_free(mesh->vertices);
    memory_free(mesh->indices);

    // gl free buffers here
    glDeleteBuffers(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
}

void generate_rectangle_mesh(mesh* const mesh, float width, float height, colourf col)
{
    vertex_data square_vertices[] =
    {
        {{0.0f,  0.0f,   0.0f}, col},
        {{width, 0.0f,   0.0f}, col},
        {{width, height, 0.0f}, col},
        {{0.0f,  height, 0.0f}, col},
    };

    static const unsigned int indices[] = {0,1,2,0,2,3};

    generate_mesh_using_vertices_and_indices(mesh, square_vertices, 4, indices, 6);
}

void generate_square_mesh(mesh* const mesh, float width, colourf col)
{
    generate_rectangle_mesh(mesh, width, width, col);
}

void generate_circle_mesh(mesh* const mesh, float radius, int segments)
{
    colourf col = COLOURF_RED;
    unsigned int vertice_count = segments + 1;
    unsigned int indice_count = segments * 3 - 3;

    vertex_data* data = memory_allocate(sizeof(vertex_data) * vertice_count);
    unsigned int* indices = memory_allocate(sizeof(unsigned int) * indice_count);

    if (data == 0 || indices == 0)
    {
        NL_LOG("Unable to allocate memory for a circle mesh. Mesh not being created");
        return;
    }

    data[0].pos = (v3f){0.0f,0.0f,0.0f};
    data[0].color = col;
    float angle_diff = 2 * 3.1415f / (float)segments;
    for (unsigned int i = 0; i < vertice_count-1; ++i)
    {
        const float x = cosf( angle_diff * i ) * radius;
        const float y = sinf( angle_diff * i ) * radius;
        const int idx = i+1;
        data[idx].pos.x = x;
        data[idx].pos.y = y;
        data[idx].pos.z = 0.0f;
        data[idx].color = col;
    }
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    unsigned int start = 3;
    for (unsigned int i = 3; i < indice_count; i+=3)
    {
        indices[i] = 0;
        indices[i+1] = start-1;
        indices[i+2] = start;
        ++start;
    }
    indices[indice_count-1] = 1;

    generate_mesh_using_vertices_and_indices(mesh, data, segments, indices, indice_count);

    memory_free(indices);
    memory_free(data);
}

