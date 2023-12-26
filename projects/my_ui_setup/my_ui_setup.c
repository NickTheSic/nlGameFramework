#include "nl_lib.h"
#include "private/nl_gl.h"


#include "my_ui_types.h"


const char* vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 transform;                               \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = transform * vec4(aPos, 1.0);         \n"
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


global_variable ui_camera camera = {0};
#define UI_ELEMENT_COUNT 10
global_variable ui_element_data MAX_ELEMENTS[UI_ELEMENT_COUNT];
global_variable vertex_data vertices[UI_ELEMENT_COUNT*4];

global_variable v2i mouse_click_pos;
global_variable v2i last_mouse_pos;
global_variable int active_element;
global_variable int editing;
global_variable int change;


global_variable unsigned int VAO;
global_variable unsigned int VBO;
global_variable unsigned int EBO;


void app_specific_init(void)
{
    ui_camera_initialize_screen_size(&camera, get_screen_size());

    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    glUseProgram(shader_program);
    unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &camera.matrix.m11);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data) * UI_ELEMENT_COUNT * 4, 0, GL_DYNAMIC_DRAW);
    
    size_t indice_data_size = sizeof(unsigned int) * UI_ELEMENT_COUNT * 6;
    unsigned int* indices = (unsigned int*)memory_allocate(indice_data_size);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < UI_ELEMENT_COUNT*6; i+=6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice_data_size, indices, GL_DYNAMIC_DRAW); 

    memory_free(indices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0);
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)12);
    glEnableVertexAttribArray(1);  

    for (int i = 0; i < UI_ELEMENT_COUNT; ++i)
    {
        vertices[i].color = (colourf){1.f,1.f,1.f,1.f};
    }

    NL_LOG("App Init Success");
}

void app_specific_update(double dt)
{
    if (was_mouse_button_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        editing = 1;
        mouse_click_pos = get_mouse_position_from_system();
        last_mouse_pos = mouse_click_pos;
        NL_LOG("Clicked %d %d", mouse_click_pos.x,  mouse_click_pos.y);
    }

    if (editing == 1)
    {
        v2i current_mouse_pos = get_mouse_position_from_system();
        if (current_mouse_pos.x != last_mouse_pos.x || current_mouse_pos.y != last_mouse_pos.y)
        {
            NL_LOG("Currently %d %d", current_mouse_pos.x,  current_mouse_pos.y);
            last_mouse_pos = current_mouse_pos;
        }

        if (was_mouse_button_released(NL_MOUSE_BUTTON_LEFT))
        {
            ui_element_data* const curr_elem = &MAX_ELEMENTS[active_element++];
            curr_elem->position.x = mouse_click_pos.x;
            curr_elem->position.y = mouse_click_pos.y;
            curr_elem->size.x = current_mouse_pos.x - mouse_click_pos.x;
            curr_elem->size.y = current_mouse_pos.y - mouse_click_pos.y;
            editing = 0;
            change = 1;
        }
    }


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    if (change)
    {
        change = 0;

        for (int i = 0; i < UI_ELEMENT_COUNT; ++i)
        {
            NL_LOG("Elem %d, x:%f y%f sx: %f sy: %f", i, 
            MAX_ELEMENTS[i].position.x,  MAX_ELEMENTS[i].position.y,  MAX_ELEMENTS[i].size.x,  MAX_ELEMENTS[i].size.y);
        }

        const int vertex = active_element * 4;

        vertices[vertex].pos = (v3f){MAX_ELEMENTS[active_element].position.x,  MAX_ELEMENTS[active_element].position.y, 0};
        vertices[vertex+1].pos = (v3f){MAX_ELEMENTS[active_element].position.x + MAX_ELEMENTS[active_element].size.x,  MAX_ELEMENTS[active_element].position.y, 0};
        vertices[vertex+2].pos = (v3f){MAX_ELEMENTS[active_element].position.x + MAX_ELEMENTS[active_element].size.x,  MAX_ELEMENTS[active_element].position.y + MAX_ELEMENTS[active_element].size.y, 0};
        vertices[vertex+3].pos = (v3f){MAX_ELEMENTS[active_element].position.x,  MAX_ELEMENTS[active_element].position.y + MAX_ELEMENTS[active_element].size.y, 0};
        
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_data) * UI_ELEMENT_COUNT * 4, vertices);
    }

    glDrawElements(GL_TRIANGLES, active_element*6, GL_UNSIGNED_INT, 0);
}

void ui_camera_initialize_screen_size(ui_camera *const camera, v2i screen_size)
{
    create_orthographic_projection(
        &camera->matrix, 
        0, 
        screen_size.x,
        0, 
        -screen_size.y,
        -0.1, 100
    );
}
