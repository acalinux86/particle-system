#ifndef WINDOW_H_
#define WINDOW_H_

#include "../utils/array.h"
#include "../utils/vector2.h"
#include "../utils/vector3.h"
#include "../utils/vector4.h"
#include "../utils/matrix.h"
#include "../utils/matvec.h"
#include "../utils/log.h"

#include <stddef.h>
#include <errno.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    int window_width, window_height;
    GLFWwindow *window;
} Renderer;

bool InitOpenGl(void);
GLFWwindow *CreateWindowWithContext(int width, int height, const char *name);
bool WindowShouldClose(GLFWwindow *window);

bool log_shader_error(GLuint Id);
bool log_program_error(GLuint Id);

char *read_file(const char *file_path, uint8_t *size);

GLuint compile_vertex(char *vertex_code);
GLuint compile_fragment(char *fragment_code);
GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path);

Renderer *CreateRenderer(GLFWwindow *window);
void DestroyRenderer(Renderer *renderer);
void Flush(Renderer *renderer);
void DetectWindowSizeChange(Renderer *renderer);

void DrawTriangle(Renderer *renderer, Vector3 v1, Vector3 v2, Vector3 v3, Vector4 color);
void DrawLines(Renderer *renderer, Vector3 v1, Vector3 v2, Vector4 color);
void DrawRectangle(Renderer *renderer, Vector3 size, Vector3 position, Vector4 color);

#endif // WINDOW_H_
