#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <math.h>
#include <stdio.h>

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

#endif // VECTOR3_H_
