#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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

#endif // VECTOR4_H_
