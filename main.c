#include "./src/system.h"

int main(void)
{
    if (!InitOpenGl()) return 1;

    GLFWwindow *window = CreateWindowWithContext(800, 600, "PARTICLE SYSTEM");
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
    Vector4 green = v4_init(0, 1, 0, 0.1);

    while (!WindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawTriangle(renderer,
                     v3_init(-0.5f, 0.5f, 0.0f),
                     v3_init(-0.5f, -0.5f, 0.0f),
                     v3_init(0.25f, -0.5f, 0.0f), red);

        DrawLines(renderer,
                  v3_init(-0.8f, 0.8f, 0.0f),
                  v3_init(0.8f, 0.8f, 0.0f),
                  red);

        DrawRectangle(renderer,
                      v3_init(0.4f, 0.4f, 0.0f),
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

/*int main(void)
{
    Vector4 vec4 = v4_init(10.0f, 10.0f, 10.0f, 1.0f);;
    V4_PRINT(vec4);

    Matrix4 translate = mv4_translate(v4_init(10.0f, 10.0f, 10.0f, 1.0f));
    MAT4_PRINT(translate);

    Matrix4 ModelMatrix = mat4_mult(translate, mat4_mult(mat4_rotate_x(10.0f), mat4_value(1.0f)));
    MAT4_PRINT(ModelMatrix);

    Vector4 TransformedVec4 = mv4_transform(ModelMatrix, vec4);
    V4_PRINT(TransformedVec4);
    return 0;
}*/
