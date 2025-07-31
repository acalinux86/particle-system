#include "./src/system.h"

int main(void)
{
    Vector3 vec3 = v3_init(400, 100, 0.0f);
    Vector3 vec3_w = to_world_coords(vec3, 800, 600);

    vec3 = v3_init(1.0f, 0.5f, 0.0f);
    Vector3 vec3_s = to_screen_coords(vec3, 800, 600);
    return 0;
    if (!InitOpenGl()) return 1;

    int width = 640;
    int height = 480;
    const char *title = "PARTICLE SYSTEM";
    GLFWwindow *window = CreateWindowWithContext(width, height, title);
    if (window == NULL)
    {
        return 1;
    }
    Log(INFO, "Window Opened SuccessFully.\n");

    int w , h;
    glfwGetWindowSize(window, &w, &h);
    Log(DEBUG, "Window Width: %d Window Height: %d\n", w, h);

    Renderer *renderer = CreateRenderer(window);
    if (renderer == NULL)
    {
        glfwTerminate();
        return 1;
    }
    Log(INFO, "Renderer Created SuccessFully.\n");

    Vector4 red = v4_init(1, 0, 0, 1.0);
    Vector4 green = v4_init(0, 0.8, 0, 1.0);

    // Render Many quads on the screen then access each of it
    while (!WindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.1f, 0.4f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawRectangle(renderer, v3_init(0.2f, 0.2f, 0.0f),
                      v3_init(0.0f, 0.0f, 0.0f),
                      green);
        DetectWindowSizeChange(renderer);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DestroyRenderer(renderer);
    glfwTerminate();
    return 0;
}
