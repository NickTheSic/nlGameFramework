#include "nl_lib.h"
#include "private/gl/nl_gl.h"
#include "third_party/stb/stb_image.h"

#include "nl_rr_sprite.h"

nl_rr_sprite SPRITE;
nl_rr_sprite TWO;

unsigned int rr_shader_program = 0;

void app_specific_init(void)
{
    SPRITE = create_simple_rr_sprite("data/images/fish.png");
    TWO = create_simple_rr_sprite("data/images/thing.png");

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
    
    render_simple_rr_sprite(SPRITE);
    render_simple_rr_sprite(TWO);
}

void app_specific_cleanup(void)
{

}


#include "nl_rr_sprite.c"
