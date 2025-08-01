#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "./math_util.h"
#include "./array.h"

#include <stddef.h>
#include <errno.h>
#include <stdarg.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct {
    Vector3 position;
    Color color;
} Vertex;

typedef ARRAY(Vertex) Vertices;
typedef ARRAY(uint32_t) Indices;

typedef struct {
    GLuint ProgramID;
    uint32_t window_width, window_height;
    GLFWwindow *window;
} Renderer;

typedef struct {
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    uint32_t indices_count;
    GLenum draw_mode;
} Static_Mesh;

typedef struct {
    uint32_t rows;
    uint32_t cols;
    uint32_t cell_size;
    Color color; // default color
} Grid;

typedef struct {
    Vertices va;
    Indices indices;
} Mesh_Data;

bool InitOpenGl(void);
GLFWwindow *CreateWindowWithContext(uint32_t width, uint32_t height, const char *name);
bool WindowShouldClose(GLFWwindow *window);
void set_background(Color color);
void destroy_window(GLFWwindow *window);

bool log_shader_error(GLuint Id);
bool log_program_error(GLuint Id);

char *read_file(const char *file_path, uint8_t *size);

GLuint compile_vertex(char *vertex_code);
GLuint compile_fragment(char *fragment_code);
GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path);

void Renderer_Init(GLFWwindow *window, Renderer *renderer);
void Destroy_Renderer(Renderer *renderer);
bool Detect_Window_Size_Change(Renderer *renderer);

void Mesh_Create(Static_Mesh *mesh, Vertices *va, Indices *indices, GLenum draw_hint);
void Mesh_Draw(const Static_Mesh *mesh);
void Render_Draw_Mesh(Renderer *renderer, Static_Mesh *mesh);
void Mesh_Destroy(Static_Mesh *mesh);
void Mesh_Update(Static_Mesh *mesh, Mesh_Data *mesh_data);
void GenerateGrid(Mesh_Data *data, Grid *grid);

void DrawTriangle(Mesh_Data *mesh_data, Vector3 v1, Vector3 v2, Vector3 v3, Color color);
void DrawLines(Mesh_Data *mesh_data, Vector3 v1, Vector3 v2, Color color);
void DrawRectangle(Mesh_Data *mesh_data, Vector3 position, Vector3 size, Color color);

typedef enum {
    INFO,
    ERROR,
    DEBUG,
    WARN,
    USAGE,
    COUNT_LEVELS,
} Log_Levels;

void Logging(FILE *stream, Log_Levels level, const char *fmt, ...);

#define Log(level, fmt, ...) Logging(stdout, level, fmt, ##__VA_ARGS__)
#define Logf(stream, level, fmt, ...) Logging(stream, level, fmt, ##__VA_ARGS__)

Color gl_to_color(Color color);
Color color_to_gl(Color color);
void color_print(Color color, const char *name);
#define COLOR_PRINT(color) color_print(color, #color)

#endif // SYSTEM_H_
