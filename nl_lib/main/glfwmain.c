#include <GLFW/glfw3.h>

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

int main(int count, char** args)
{
    NL_UNUSED(count);NL_UNUSED(args);

    //Platform Init!

    app_specific_init();

    {
        app_specific_update(1.0);
        app_specific_render();
    }

    app_specific_cleanup();

    return 0;
}
