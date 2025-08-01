#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

// Vector2
// NOTE: VECTOR2 PROTOTYPES
typedef struct {
    float x;
    float y;
} Vector2;

Vector2 v2_init(float x, float y);
void v2_print(const Vector2 *self);

Vector2 v2_add(Vector2 a, Vector2 b);
Vector2 v2_sub(Vector2 a, Vector2 b);

// NOTE: If value is negative, direction reverses else unchanged
Vector2 v2_scale(Vector2 a, float value);
float v2_perp_dot(Vector2 a, Vector2 b);
float v2_dot(Vector2 a, Vector2 b);

// NOTE: returns the Magnitude of a Vector
float v2_length(Vector2 a);
Vector2 v2_normalize(Vector2 a);

// Vector3

// NOTE: VECTOR3 STRUCTURE
typedef struct {
    float x;
    float y;
    float z;
} Vector3;


// NOTE: VECTOR3 PROTOTYPES
Vector3 v3_init(float x, float y, float z);
void v3_print(const Vector3 *self);

Vector3 v3_add(Vector3 a, Vector3 b);
Vector3 v3_sub(Vector3 a, Vector3 b);

Vector3 v3_scale(Vector3 a, float value);
Vector3 v3_cross(Vector3 a, Vector3 b);
float v3_dot(Vector3 a, Vector3 b);

float v3_length(Vector3 a);
Vector3 v3_normalize(Vector3 a);


// Vector4

// NOTE: VECTOR4 STRUCTURE
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4;


// NOTE: VECTOR4 PROTOTYPES
Vector4 v4_init(float x, float y, float z, float w);
Vector4 v4_point(float x, float y, float z);
Vector4 v4_direction(float x, float y, float z);

void v4_print(const Vector4 *self, const char *name);
#define V4_PRINT(self) v4_print(&self, #self)

Vector4 v4_add(Vector4 a, Vector4 b);
Vector4 v4_sub(Vector4 a, Vector4 b);

Vector4 v4_scale(Vector4 a, float value);
Vector4 v4_cross(Vector4 a, Vector4 b);
float v4_dot(Vector4 a, Vector4 b);

float v4_length(Vector4 a);
Vector4 v4_normalize(Vector4 a);
Vector4 v4_perspective_divide(Vector4 a);
bool v4_equals(Vector4 a, Vector4 b);

// Matrix4
#define MAT4_ROWS 4
#define MAT4_COLS 4
#define PI 3.14593f
#define EPSILON 1e-3f

typedef struct {
    float rows[MAT4_ROWS][MAT4_COLS];
} Matrix4;

void mat4_print(const Matrix4 *self, const char *name);
#define MAT4_PRINT(self) mat4_print(&self, #self);

Matrix4 mat4_add(Matrix4 a, Matrix4 b);
Matrix4 mat4_sub(Matrix4 a, Matrix4 b);
Matrix4 mat4_mult(Matrix4 a, Matrix4 b);

Matrix4 mat4_value(float value);
Matrix4 mat4_identity();

Matrix4 mat4_transpose(Matrix4 mat4);

Matrix4 mat4_copy(Matrix4 mat4);

Matrix4 mat4_rotate_x(float degrees);
Matrix4 mat4_rotate_y(float degrees);
Matrix4 mat4_rotate_z(float degrees);

// Matvec (Matrix and Vector related Operations)

Vector4 v4_from_v3(Vector3 vec3);
Vector3 v3_from_v4(Vector4 vec4);
Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4);
Matrix4 mv4_translate(Vector4 vec_4);
Vector3 to_screen_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height);
Vector3 to_world_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height);

#endif // MATH_UTIL_H
