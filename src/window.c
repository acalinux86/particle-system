#include "./system.h"

bool InitOpenGl(void)
{
    Log(INFO, "Initializing OpenGL\n");
    glewExperimental = true;
    if (!glfwInit())
    {
        Logf(stderr, ERROR, "Failed to Initialize glfw.\n");
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // Anti-Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Log(INFO, "SuccessFully Initialized GLFW.\n");
    return true;
}

GLFWwindow *CreateWindowWithContext(int width, int height, const char *name)
{
    GLFWwindow *window;
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to Open GLFW Window.\n");
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to Initialize GLEW.\n");
        return NULL;
    }
    Log(INFO, "SuccessFully Initialized GLEW\n");
    const GLubyte *version = glGetString(GL_VERSION);
    Log(INFO, "OpenGL Version: %s\n", version);

    const GLubyte *renderer = glGetString(GL_RENDERER);
    Log(INFO, "Renderer Version: %s\n", renderer);

    const GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    Log(INFO, "GLSL Version: %s\n", glsl_version);

    const GLubyte *vendor = glGetString(GL_VENDOR);
    Log(INFO, "Vendor: %s\n", vendor);

    glDisable(GL_DEPTH_TEST);

    // Enable blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Log(INFO, "ALPHA Blend Enabled\n");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    Log(INFO, "Input Mode Enabled\n");
    return window;
}

bool WindowShouldClose(GLFWwindow *window)
{
    if (window == NULL) return true;
    return glfwWindowShouldClose(window) ||
           glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}
