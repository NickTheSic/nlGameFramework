#include "../nl_fileio.h"
#include "../nl_memory.h"

#include "../nl_renderer.h"

#include <stdio.h>
#include <string.h>

#if !defined (_WIN32) 
void fopen_s(FILE** file, const char* filename, const char* descript)
{
    *file = fopen(filename, descript);
}

#define strtok_s strtok_r
#endif

#if defined (GEKKO)
// The following fails and suggests_sscanf_r which I cannot seem to find online
#define sscanf_s(...); 
#endif

void read_entire_file(const char* filename, file_contents* const contents)
{
    FILE* fp = {0};
    fopen_s(&fp, filename, "rb");

    if (fp)
    {
        fseek(fp, 0, SEEK_END); // seek to end of file
        size_t file_size = ftell(fp); // get current file pointer
        fseek(fp, 0, SEEK_SET);

        contents->size = file_size;
        contents->content = (char*)memory_allocate(sizeof(char) * file_size);
        if (contents->content)
        {
            fread(contents->content, file_size, 1, fp);
        }
        else 
        {
            NL_LOG("Could not allocate memory for Contents");
        }
        fclose(fp);
    }
    else
    {
        NL_LOG("Failed to open file %s", filename);
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
    FILE* fp = {0};
    fopen_s(&fp, filename, "wb");

    if (fp)
    {
        fwrite(contents, 1, size, fp);
        fclose(fp);
    }
}

void load_from_binary_file(const char* const filename, unsigned int size, char* const dest)
{
    FILE* fp = {0};
    fopen_s(&fp, filename, "rb");
    
    if (fp)
    {
        fread(dest, 1, size, fp);
        fclose(fp);
    }
}

const char* find_file_type_from_name(const char* const filename)
{
    int name_length = strlen(filename);
    const char* file_type = &filename[name_length-1];

    for (int i = name_length - 1; i < 0; ++i)
    {
        file_type = &filename[i];
        if (file_type[0] == '.')
        {
            break;
        }
    }

    return file_type;
}

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
#ifdef GEKKO
    NL_UNUSED(file); NL_UNUSED(mesh);
    NL_UNIMPLEMENTED_FUNC;
#endif

#if !defined GEKKO
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

#endif
}
