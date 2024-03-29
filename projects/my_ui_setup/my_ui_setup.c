#include "nl_lib.h"
#include "private/nl_gl.h"


#include "my_ui_types.h"


unsigned int shader_program;


global_variable camera my_camera = {0};
#define UI_ELEMENT_COUNT 10
global_variable ui_element_data MAX_ELEMENTS[UI_ELEMENT_COUNT] = {1.f};
global_variable vertex_data vertices[UI_ELEMENT_COUNT*4];

global_variable v2i mouse_click_pos;
global_variable v2i last_mouse_pos;
global_variable int active_element;
global_variable int editing;
global_variable int change;

global_variable unsigned int VAO;
global_variable unsigned int VBO;
global_variable unsigned int EBO;

mesh mouse_square = {0};

internal_function void window_size_callback(int width, int height)
{
    create_screen_aspect(&my_camera, width, height);
    
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &my_camera.proj_matrix.m11);
}

void app_specific_init(void)
{
    pfn_window_size_callback = &window_size_callback;
    
    v2i retrieved_screen_size = get_screen_size();
    v2f screen_size;
    screen_size.x = retrieved_screen_size.x;
    screen_size.y = retrieved_screen_size.y;
    initialize_camera(&my_camera, (v3f){0.0f,0.0f,0.0f}, (v2f){(float)screen_size.x, (float)screen_size.y});
    window_size_callback(screen_size.x, screen_size.y);

    shader_program = create_shader_program(common_vert_shader_code, common_fragment_shader_code);
    glUseProgram(shader_program);
    unsigned int transformLoc = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &my_camera.view_matrix.m11);

    {
        vertex_data mouse_verts[4] = {
            {100.f,1.f,1.f,1.f,1.f,1.f,1.f},
            {100.f,10.f,1.f,1.f,1.f,1.f,1.f},
            {1.f,10.f,1.f,1.f,1.f,1.f,1.f},
            {1.f,100.f,1.f,1.f,1.f,1.f,1.f}
        };

        const unsigned int mouse_pos_indices[6] = {0,1,2,2,3,0};
        generate_mesh_using_vertices_and_indices(&mouse_square, mouse_verts, 4, mouse_pos_indices, 6);
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data) * (UI_ELEMENT_COUNT) * 4, 0, GL_DYNAMIC_DRAW);
    
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
    update_camera(&my_camera, dt);
    glUseProgram(shader_program);
    unsigned int transformLoc = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &my_camera.view_matrix.m11);

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


    render_single_mesh(&mouse_square);
}
