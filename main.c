#include "./utils/array.h"
#include "./utils/vector2.h"
#include "./utils/vector3.h"
#include "./utils/vector4.h"
#include "./utils/matrix.h"
#include "./utils/matvec.h"
#include "./utils/file.h"
#include "./utils/log.h"

#include <stddef.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool log_shader_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetShaderiv(Id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length];
        glGetShaderInfoLog(Id, info_log_length, NULL, ErrorMessage);
        Log(ERROR, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

bool log_program_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetProgramiv(Id, GL_LINK_STATUS, &result);
    glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length + 1];
        glGetProgramInfoLog(Id, info_log_length, NULL, ErrorMessage);
        Log(ERROR, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

GLuint compile_vertex(char *vertex_code)
{
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (vertex_code == NULL)
    {
        Logf(stderr, ERROR, "Vertex Shader Source is NULL");
        return 0;
    }

    Log(INFO, "Compiling Vertex Shader Program...\n");
    glShaderSource(VertexShaderId, 1, (const GLchar* const*)&vertex_code, NULL);
    glCompileShader(VertexShaderId);
    
    // Check Vertex Shader
    if (!log_shader_error(VertexShaderId))
    {
        glDeleteShader(VertexShaderId);
        return 0;
    }
    Log(INFO, "SuccessFully Compiled Vertex Shader.\n");
    return VertexShaderId;
}

GLuint compile_fragment(char *fragment_code)
{
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragment_code == NULL)
    {
        Logf(stderr, ERROR, "Fragment Shader Source is NULL.\n");
        return 0;
    }

    Log(INFO, "Compiling Fragment Shader Program...\n");
    glShaderSource(FragmentShaderId, 1, (const GLchar* const*)&fragment_code, NULL);
    glCompileShader(FragmentShaderId);

    // Check fragment Shader
    if (!log_shader_error(FragmentShaderId))
    {
        glDeleteShader(FragmentShaderId);
        return 0;
    }
    Log(INFO, "SuccessFully Compiled Fragment Shader.\n");
    return FragmentShaderId;
}

GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
    uint8_t v_len, f_len = 0;
    char *vertex_code = read_file(vertex_file_path, &v_len);
    char *fragment_code = read_file(fragment_file_path, &f_len);

    // Debug print the shader sources
    Log(INFO, "Vertex shader source (%u bytes)\n", v_len);
    Log(INFO, "Fragment shader source (%u bytes)\n", f_len);
    
    GLuint FragmentShaderId = compile_fragment(fragment_code);
    GLuint VertexShaderId = compile_vertex(vertex_code);

    if (FragmentShaderId == 0 || VertexShaderId == 0)
    {
        if (VertexShaderId) glDeleteShader(VertexShaderId);
        if (FragmentShaderId) glDeleteShader(FragmentShaderId);
        free(vertex_code);
        free(fragment_code);
        return 0;
    }

    // Link the Program
    Log(INFO, "Linking Programs...\n");
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    // Check the Program
    if (!log_program_error(ProgramId))
    {
        Logf(stderr, ERROR, "Program Linking Failed.\n");
        glDeleteProgram(ProgramId);
        ProgramId = 0;
        return 0;
    }
    Log(INFO, "SuccessFully Linked Program.\n");

    Log(INFO, "Detaching and Deleting Shaders...\n");
    // Detach Shaders
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    // Delete Shader Id
    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);
    
    Log(INFO, "SuccessFully Detached and Deleted the Shaders.\n");
    // Free the shader buffers
    free(vertex_code);
    free(fragment_code);
    Log(INFO, "SuccessFully Freed the Shader Buffers\n");
    return ProgramId; // return program id
}

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

typedef struct {
    Vector3 position;
    Vector4 color;
} Vertex;

typedef ARRAY(Vertex) Vertices;

typedef ARRAY(uint32_t) Indices;

typedef struct {
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint ProgramID;
    Vertices va;
    Indices indices;
    GLenum current_mode;
} Renderer;

Renderer *CreateRenderer()
{
    Renderer *renderer = calloc(1, sizeof(Renderer));
    if (renderer == NULL)
    {
        fprintf(stderr, "calloc() failed: Failed to Allocate Memory for Renderer.\n");
        return NULL;
    }

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

void DrawTriangle(Renderer *renderer, Vector3 v1, Vector3 v2, Vector3 v3, Vector4 color)
{
    if (renderer->va.count + 3 > renderer->va.capacity ||
        renderer->current_mode != GL_TRIANGLES) {
        Flush(renderer);
        renderer->current_mode = GL_TRIANGLES;
    }
    uint32_t base = renderer->va.count;
    array_append(&renderer->va, ((Vertex){v1, color}));
    array_append(&renderer->va, ((Vertex){v2, color}));
    array_append(&renderer->va, ((Vertex){v3, color}));

    uint32_t tri_indices[3] = {base, base+1, base+2};
    for (uint32_t i = 0; i < 3; ++i)
    {
        array_append(&renderer->indices, tri_indices[i]);
    }
}

void DrawLines(Renderer *renderer, Vector3 v1, Vector3 v2, Vector4 color)
{
    if (renderer->va.count + 2 > renderer->va.capacity ||
        renderer->current_mode != GL_LINES) {
        Flush(renderer);
        renderer->current_mode = GL_LINES;
    }

    uint32_t base_index = renderer->va.count;
    array_append(&renderer->va, ((Vertex){v1, color}));
    array_append(&renderer->va, ((Vertex){v2, color}));
    
    uint32_t line_indices[2] = {base_index, base_index+1};
    for (uint32_t i = 0; i < 2; ++i)
    {
        array_append(&renderer->indices, line_indices[i]);
    }
}

void DrawRectangle(Renderer *renderer, Vector3 size, Vector3 position, Vector4 color)
{
    if (renderer->indices.count + 6 > renderer->indices.capacity ||
        renderer->va.count + 4 > renderer->va.capacity ||
        renderer->current_mode != GL_TRIANGLES) {
        Flush(renderer);
        renderer->current_mode = GL_TRIANGLES;
    }

    // Calculate corner positions
    Vector3 half_size = v3_scale(size, 0.5);
    Vector3 corners[4] = {
        v3_add(position, v3_init(-half_size.x, -half_size.y, 0.0f)), // botom-left
        v3_add(position, v3_init(-half_size.x,  half_size.y, 0.0f)), // top-left
        v3_add(position, v3_init(half_size.x,   half_size.y, 0.0f)), // top-right
        v3_add(position, v3_init(half_size.x,  -half_size.y, 0.0f)), // bottom-right
    };

    uint32_t base_index = renderer->indices.count;
    for (uint32_t i = 0; i < 4; ++i)
    {
        array_append(&renderer->va, ((Vertex){corners[i], color}));
    }

    uint32_t quad_indices[6] = {
        base_index, base_index+1, base_index+2,
        base_index, base_index+2, base_index+3
    };
    for (uint32_t i = 0; i < 6; ++i)
    {
        array_append(&renderer->indices, quad_indices[i]);
    }
}

bool WindowShouldClose(GLFWwindow *window)
{
    if (window == NULL) return true;
    return glfwWindowShouldClose(window) ||
           glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

int main(void)
{
    if (!InitOpenGl()) return 1;

    GLFWwindow *window = CreateWindowWithContext(800, 600, "PARTICLE SYSTEM");
    if (window == NULL)
    {
        return 1;
    }
    Log(INFO, "Window Opened SuccessFully.\n");

    Renderer *renderer = CreateRenderer();
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
