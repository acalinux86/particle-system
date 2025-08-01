#include "./system.h"

Renderer *CreateRenderer(GLFWwindow *window)
{
    Renderer *renderer = calloc(1, sizeof(Renderer));
    if (renderer == NULL)
    {
        fprintf(stderr, "calloc() failed: Failed to Allocate Memory for Renderer.\n");
        return NULL;
    }

    renderer->window = window;
    int w, h;
    glfwGetWindowSize(renderer->window, &w, &h);
    renderer->window_width = w;
    renderer->window_height = h;

    array_new(&renderer->va, 1024);
    array_new(&renderer->indices, 2048);

    glGenVertexArrays(1, &renderer->VAO);
    glBindVertexArray(renderer->VAO);

    glGenBuffers(1, &renderer->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, renderer->va.capacity*sizeof(renderer->va.items[0]), NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &renderer->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer->indices.capacity*sizeof(renderer->indices.items[0]), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(renderer->va.items[0]),
                          (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(renderer->va.items[0]), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    renderer->ProgramID = LoadShader("./shader/vertex_shader.vert", "./shader/fragment_shader.frag");
    if (renderer->ProgramID == 0)
    {
        fprintf(stderr, "Shader Loading Failed.\n");
        glDeleteBuffers(1, &renderer->VBO);
        glDeleteVertexArrays(1, &renderer->VAO);
        array_delete(&renderer->va);
        free(renderer);
        return NULL;
    }
    return renderer;
}

void DestroyRenderer(Renderer *renderer)
{
    if (renderer)
    {
        Log(INFO, "Destroying Renderer...\n");
        glDeleteProgram(renderer->ProgramID);
        glDeleteBuffers(1, &renderer->VBO);
        glDeleteVertexArrays(1, &renderer->VAO);
        array_delete(&renderer->va);
        free(renderer);
        Log(INFO, "SuccessFully Destroyed Renderer\n");
    }
}

void Flush(Renderer *renderer)
{
    if (renderer->va.count == 0) {
        Log(WARN, "Nothing to flush\n");
        return;
    }

    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(renderer->va.items[0]) * renderer->va.count, renderer->va.items);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(renderer->indices.items[0]) * renderer->indices.count, renderer->indices.items);

    glUseProgram(renderer->ProgramID);
    // glUniform4f(glGetUniformLocation(renderer->ProgramID, "fragColor"),
    //             renderer->va.items[0].color.x,
    //             renderer->va.items[0].color.y,
    //             renderer->va.items[0].color.z,
    //             renderer->va.items[0].color.w);

    glDrawElements(renderer->current_mode, renderer->indices.count, GL_UNSIGNED_INT, (void*)0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        Log(ERROR, "OpenGL error during draw call: %d\n", err);
    }
    renderer->indices.count = 0;
    renderer->va.count = 0;
}

bool DetectWindowSizeChange(Renderer *renderer)
{
    int w, h;
    glfwGetWindowSize(renderer->window, &w, &h);
    if (renderer->window_width != w ||
        renderer->window_height != h) {
        Log(INFO, "Window Size Change Detected: Width: %d, Height: %d\n", w, h);
        renderer->window_width = w;
        renderer->window_height = h;
        glViewport(0, 0, w, h);
        return true;
    }
    return false;
}
