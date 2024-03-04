#include "nl_lib.h"
#include "private/nl_gl.h"
#include "string.h" //memcpy

const char* vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 objectSpacePos = vec4( aPos, 1 );             \n"
"   vec4 worldSpacePos  = uWorldMat * objectSpacePos;  \n"
"   vec4 viewSpacePos   = uViewMat * worldSpacePos;    \n"
"   vec4 clipSpacePos   = uProjMat * viewSpacePos;     \n"
"   gl_Position = clipSpacePos;                        \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";
unsigned int shader_program;
mesh untitled = {0};

global_variable camera cam = {0};

internal_function void window_size_callback(int width, int height)
{
    create_screen_aspect(&cam, width, height);
    
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &cam.proj_matrix.m11);
}

void load_mesh_from_file();
void app_specific_init(void)
{
    pfn_window_size_callback = &window_size_callback;
    load_mesh_from_file();

    initialize_camera(&cam, (v3f){0.0f,0.0f,0.0f}, (v2f){2.f, 2.f});

    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    glUseProgram(shader_program);

    set_depth_test_enabled(1);
}

void app_specific_update(double dt)
{
    if (was_key_pressed(key_c))
    {
        static int enabled;
        enabled = enabled ^ 0b1;
        set_cull_face_enabled(enabled);
    }
    if (was_key_pressed(key_z))
    {
        static int side;
        side = side ^ 0b1;
        set_cull_face_side(side);
    }
    if (was_key_pressed(key_x))
    {
        static int clockwise;
        clockwise = clockwise ^ 0b1; 
        set_cull_front_face(clockwise);
    }

    update_camera(&cam, dt);

    glUseProgram(shader_program);
    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &cam.view_matrix.m11);

    v3f scale = {1,1,1};
    v3f rot = {0};
    v3f trans = {0};
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt(&mat, scale, rot, trans);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&untitled);
    set_wireframe_rendering(); 
    glClear(GL_DEPTH_BUFFER_BIT);
    render_single_mesh(&untitled);
    set_fill_rendering();
}

#ifdef __EMSCRIPTEN__
char* strtok_s(char* buffer, char* delim, char** ptr)
{
    (void)(ptr);
    return strtok(buffer, delim);
}
 
void sscanf_s(char* line, const char* str, __va_list__ args)
{
    // TODO: Implement proper?
    NL_UNIMPLEMENTED_FUNC;
}

#endif

void parse_vertices_indices(const file_contents *const content, int*const vertices, int*const indices, int*const face_value_count)
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
    *vertices = vertice_count;
    *indices = indice_line_count;
    *face_value_count = face_values;

    memory_free(buffer);
}

void load_mesh_from_file()
{
    NL_LOG("Loading Mesh From File");

    int vertice_count = 0;
    int indice_line_count = 0;
    int face_values = 0;

    file_contents loaded_mesh;
    read_entire_file("data/untitled.obj", &loaded_mesh);

    parse_vertices_indices(&loaded_mesh, &vertice_count, &indice_line_count, &face_values);

    if (face_values != 3)
    {
        NL_LOG("There seems to be an error. Face Values is: %d", face_values);
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

            // so the mesh isn't completely white for now
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

    generate_mesh_using_vertices_and_indices(&untitled, vd, vertice_count, indices, indice_count);

    memory_free(buffer);
    memory_free(indices);
    memory_free(vd);
    clear_file_read(&loaded_mesh);
}

