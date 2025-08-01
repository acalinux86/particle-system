#include "./src/system.h"

#define RED    (Color){255, 0, 0, 255}
#define GREEN  (Color){0, 255, 0, 255}
#define YELLOW (Color){255, 255, 0, 255}
#define GREY   (Color){128, 128, 128, 255}
#define PURPLE (Color){160, 32, 240, 255}

void calculate_fps(double *last_time, double *frame_count)
{
    double current_time = glfwGetTime();
    (*frame_count)++;
    if (current_time - *last_time > 1.0f) {
        double fps = *frame_count / (current_time - *last_time);
        Log(INFO, "FPS: %.2lf\n", fps);
        *frame_count = 0.0;
        *last_time = current_time;
    }
}

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
    glfwSwapInterval(0);  // 0 to disable VSync, 1 to enable

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

    double last_time = glfwGetTime();
    double frame_count = 0.0;
    // TODO: Render Many quads on the screen then access each of it
    while (!WindowShouldClose(window))
    {
        set_background(GREY);

        float cell_size = renderer->window_width/10.0f;

        float x = renderer->window_width/2.0f;
        float y = renderer->window_height/2.0f;

        float gap = cell_size / 2.0f;

        Vector3 size = v3_init(cell_size, cell_size, 0.0f);
        Vector3 position = v3_init(x - (cell_size + gap)/2.0f, y, 0.0f);

        DrawRectangle(renderer, position, size, PURPLE);
        DrawRectangle(renderer, v3_add(v3_init(cell_size + gap, 0.0f, 0.0f), position), size, PURPLE);

        DetectWindowSizeChange(renderer);
        calculate_fps(&last_time, &frame_count);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    DestroyRenderer(renderer);
    glfwTerminate();
    return 0;
}
