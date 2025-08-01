 #include "./src/system.h"

#define RED    (Color){255, 0, 0, 255}
#define GREEN  (Color){0, 255, 0, 255}
#define YELLOW (Color){255, 255, 0, 255}
#define GREY   (Color){128, 128, 128, 255}
#define PURPLE (Color){160, 32, 240, 255}
#define BLACK  (Color){0, 0, 0, 255}

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

    uint32_t SCREEN_WIDTH = 1920 / 2;
    uint32_t SCREEN_HEIGHT = 1080 / 2;
    const char *title = "PARTICLE SYSTEM";
    GLFWwindow *window = CreateWindowWithContext(SCREEN_WIDTH, SCREEN_HEIGHT, title);
    if (window == NULL)
    {
        return 1;
    }
    glDisable(GL_DEPTH_TEST);
    Log(INFO, "Window Opened SuccessFully.\n");
    glfwSwapInterval(0);  // 0 to disable VSync, 1 to enable

    uint32_t w , h;
    glfwGetWindowSize(window, (int*)&w, (int*)&h);
    Log(DEBUG, "Window Width: %d Window Height: %d\n", w, h);

    Renderer renderer = {0};
    Renderer_Init(window, &renderer);
    Log(INFO, "Renderer Created SuccessFully.\n");

    float factor = 100.0f;
    float cell_size = 5;
    uint32_t grid_cols = SCREEN_WIDTH / cell_size;
    uint32_t grid_rows = SCREEN_HEIGHT / cell_size;
    Log(DEBUG, "Cols: %d, Rows: %d, Cell Size: %f Factor: %f\n", grid_cols, grid_rows, cell_size, factor);
    Static_Mesh mesh = {0};
    Mesh_Data mesh_data = {0};
    array_new(&mesh_data.indices);
    array_new(&mesh_data.va);

    // Draw a red rectangle in the center of the screen
    // float rect_w = 100.0f;
    // float rect_h = 100.0f;
    // Vector3 center = v3_init(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
    // Vector3 size = v3_init(rect_w, rect_h, 0.0f);
    // DrawRectangle(&mesh_data, center, size, RED);

    Grid grid = {grid_rows, grid_cols, cell_size, PURPLE};
    GenerateGrid(&mesh_data, &grid);
    Mesh_Update(&mesh, &mesh_data);
    Mesh_Create(&mesh, &mesh_data.va, &mesh_data.indices, GL_TRIANGLES);
    Log(DEBUG, "Mesh has %d vertices and %d indices\n", mesh_data.va.count, mesh_data.indices.count);
    double last_time = glfwGetTime();
    double frame_count = 0.0;
    // TODO: Render Many quads on the screen then access each of it
    while (!WindowShouldClose(window))
    {
        set_background(BLACK);
        Render_Draw_Mesh(&renderer, &mesh);
        Detect_Window_Size_Change(&renderer);
        calculate_fps(&last_time, &frame_count);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    array_delete(&mesh_data.va);
    array_delete(&mesh_data.indices);
    Mesh_Destroy(&mesh);
    Destroy_Renderer(&renderer);
    destroy_window(window);
    return 0;
}
