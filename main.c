#include "./utils/array.h"
#include "./utils/vector2.h"
#include "./utils/vector3.h"
#include "./utils/vector4.h"
#include "./utils/matrix.h"
#include "./utils/matvec.h"
#include "./file.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef ARRAY(Vector2) Vector2_Array;
void print_array(const Vector2_Array *va)
{
    array_analysis(va);
    for (uint32_t i = 0; i < va->count; ++i)
    {
        printf("index %u: ", i); v2_print(&va->items[i]);
    }
    printf("\n");
}

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
        printf("%s\n", &ErrorMessage[0]);
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
        printf("%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

GLuint compile_vertex(char *vertex_code)
{
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (vertex_code == NULL)
    {
        fprintf(stderr, "Vertex Shader Source is NULL");
        return 0;
    }

    printf("Compiling Shader Program...\n");
    glShaderSource(VertexShaderId, 1, (const GLchar* const*)&vertex_code, NULL);
    glCompileShader(VertexShaderId);
    
    // Check Vertex Shader
    if (!log_shader_error(VertexShaderId))
    {
        glDeleteShader(VertexShaderId);
        return 0;
    }

    return VertexShaderId;
}

GLuint compile_fragment(char *fragment_code)
{
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragment_code == NULL)
    {
        fprintf(stderr, "Fragment Shader Source is NULL.\n");
        return 0;
    }

    printf("Compiling Shader Program...\n");
    glShaderSource(FragmentShaderId, 1, (const GLchar* const*)&fragment_code, NULL);
    glCompileShader(FragmentShaderId);

    // Check fragment Shader
    if (!log_shader_error(FragmentShaderId))
    {
        glDeleteShader(FragmentShaderId);
        return 0;
    }
    return FragmentShaderId;
}

GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
    uint8_t v_len, f_len = 0;
    char *vertex_code = read_file(vertex_file_path, &v_len);
    char *fragment_code = read_file(fragment_file_path, &f_len);

    // Debug print the shader sources
    printf("Vertex shader source (%u bytes):\n%.*s\n", v_len, v_len, vertex_code);
    printf("Fragment shader source (%u bytes):\n%.*s\n", f_len, f_len, fragment_code);
    
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
    printf("Linking Programs...\n");
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    // Check the Program
    if (!log_program_error(ProgramId))
    {
        fprintf(stderr, "Program Linking Failed.\n");
        glDeleteProgram(ProgramId);
        ProgramId = 0;
        return 0;
    }
    
    // Detach Shaders
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    // Delete Shader Id
    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);

    // Free the shader buffers
    free(vertex_code);
    free(fragment_code);

    return ProgramId; // return program id
}

bool InitOpenGl(void)
{
    glewExperimental = true;
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to Initialize glfw.\n");
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // Anti-Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
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
    // Enable blend
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return window;
}

typedef struct {
    GLuint VBO;
    GLuint VAO;
    GLuint ProgramID;
} Renderer;

Renderer *CreateRenderer()
{
    Renderer *renderer = calloc(1, sizeof(Renderer));
    if (renderer == NULL)
    {
        fprintf(stderr, "calloc() failed: Failed to Allocate Memory for Renderer.\n");
        return NULL;
    }

    glGenVertexArrays(1, &renderer->VAO);
    glBindVertexArray(renderer->VAO);

    glGenBuffers(1, &renderer->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint)*9, NULL, GL_DYNAMIC_DRAW);

    renderer->ProgramID = LoadShader("./shader/vertex_shader.vert", "./shader/fragment_shader.frag");
    if (renderer->ProgramID == 0)
    {
        return NULL;
    }
    return renderer;
}

void DrawTriangle(Renderer *renderer, Vector2 v1, Vector2 v2, Vector2 v3, Vector4 color)
{
    GLfloat vertices[] = {
        v1.x, v1.y, 0.0f,
        v2.x, v2.y, 0.0f,
        v3.x, v3.y, 0.0f,
    };

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glUseProgram(renderer->ProgramID);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    glUniform4f(glGetUniformLocation(renderer->ProgramID, "our_color"), color.x, color.y, color.z, color.w); // Red
}

int main(void)
{
    if (!InitOpenGl()) return 1;

    GLFWwindow *window = CreateWindowWithContext(800, 600, "PARTICLE SYSTEM");
    if (window == NULL)
    {
        return 1;
    }

    Renderer *renderer = CreateRenderer();
    if (renderer == NULL)
    {
        return 1;
    }

    Vector4 red = v4_init(1.0, 0.0, 0.0, 0.2);
    Vector4 blue = v4_init(0.0, 0.0, 1.0, 1.0);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawTriangle(renderer,
                     v2_init(0.0f, 0.5f),
                     v2_init(0.0f, 0.0f),
                     v2_init(1.0f, 0.0f), red);

        DrawTriangle(renderer,
                     v2_init(1.0f, 0.0f),
                     v2_init(1.0f, 0.5f),
                     v2_init(0.0f, 0.5f), blue);
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
             glfwWindowShouldClose(window) == 0);
    
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
