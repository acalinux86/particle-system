#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <stdio.h>
#include <math.h>

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

#endif // VECTOR2_H_
