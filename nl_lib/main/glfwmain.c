#include <GLFW/glfw3.h>

extern void app_specific_init(void);
extern void app_specific_update(double dt);
extern void app_specific_render(void);
extern void app_specific_cleanup(void);

int main(int count, char** args)
{
    NL_UNUSED(count);NL_UNUSED(args);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 800, "My Title", NULL, NULL);
    glfwMakeContextCurrent(window);

    app_specific_init();

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    

        app_specific_update(1.0);
        app_specific_render();
    }

    app_specific_cleanup();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
