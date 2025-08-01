#include "./system.h"

void Renderer_Init(GLFWwindow *window, Renderer *renderer)
{
    if (!renderer || !window) exit(1);
    memset(renderer, 0, sizeof(Renderer));
    renderer->window = window;
    uint32_t w, h;
    glfwGetWindowSize(renderer->window, (int*)&w, (int*)&h);
    renderer->window_width = w;
    renderer->window_height = h;
    Log(DEBUG, "Renderer Window Sizes: %d, %d\n", renderer->window_width, renderer->window_height);
    renderer->ProgramID = LoadShader("./shader/vertex_shader.vert", "./shader/fragment_shader.frag");
    if (renderer->ProgramID == 0)
    {
        fprintf(stderr, "Shader Loading Failed.\n");
        exit(1);
    }
}

void Destroy_Renderer(Renderer *renderer)
{
    if (renderer)
    {
        Log(INFO, "Destroying Renderer...\n");
        glDeleteProgram(renderer->ProgramID);
        Log(INFO, "SuccessFully Destroyed Renderer\n");
    }
}

bool Detect_Window_Size_Change(Renderer *renderer)
{
    uint32_t w, h;
    glfwGetWindowSize(renderer->window, (int*)&w, (int*)&h);
    if (renderer->window_width != w ||
        renderer->window_height != h) {
        Log(INFO, "Window Size Change Detected: Width: %d, Height: %d\n", w, h);
        renderer->window_width = w;
        renderer->window_height = h;
        glViewport(0, 0, renderer->window_width, renderer->window_height);
        return true;
    }
    return false;
}
