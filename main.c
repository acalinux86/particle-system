#include "./src/system.h"

#define RED (Color){255, 0, 0, 255}
#define YELLOW (Color){255, 255, 0, 255}
#define GREY (Color){128, 128, 128, 255}
#define PURPLE (Color){160, 32, 240, 255}

int main(void)
{
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

    Vector4 green = v4_init(0, 0.8, 0, 1.0);
    Vector3 size = v3_init(0.2f, 0.2f, 0.0f);
    Vector3 position = v3_init(0.0f, 0.0f, 0.0f);

    double last_time = glfwGetTime();
    double frame_count = 0.0;
    COLOR_PRINT(GREY);
    Color grey = color_to_gl(GREY);
    COLOR_PRINT(grey);
    // Render Many quads on the screen then access each of it
    while (!WindowShouldClose(window))
    {
        set_background(PURPLE);
        DrawRectangle(renderer, size, position, green);
        DetectWindowSizeChange(renderer);

        double current_time = glfwGetTime();
        frame_count++;
        if (current_time - last_time > 1.0f) {
            double fps = frame_count / (current_time - last_time);
            Log(INFO, "FPS: %.2lf\n", fps);
            frame_count = 0.0;
            last_time = current_time;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DestroyRenderer(renderer);
    glfwTerminate();
    return 0;
}
