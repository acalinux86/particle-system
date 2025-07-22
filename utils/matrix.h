#ifndef MATRIX4_H
#define MATRIX4_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

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

#endif // MATRIX4_H
