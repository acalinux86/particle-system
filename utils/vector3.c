#include "./vector3.h"

// NOTE: Vector3 Implementation
Vector3 v3_init(float x, float y, float z)
{
    return (Vector3){x, y, z};
}

void v3_print(const Vector3 *self)
{
    printf("Vector3: [%.2f, %.2f, %.2f]\n", self->x, self->y, self->z);
}

Vector3 v3_add(Vector3 a, Vector3 b) {
    return v3_init(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Function that Subtracts Two Vector
Vector3 v3_sub(Vector3 a, Vector3 b) {
    return v3_init(a.x-b.x, a.y-b.y, a.z-b.z);
}

// Function that returns the Dot Product of two Vectors -> (a float)
float v3_dot(Vector3 a, Vector3 b) {
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

// Function that Returns A Cross Product of two Vectors
Vector3 v3_cross(Vector3 a, Vector3 b) {
    float cross_x = a.y * b.z - a.z * b.y;
    float cross_y = a.z * b.x - a.x * b.z;
    float cross_z = a.x * b.y - a.y * b.x;

    return v3_init(cross_x, cross_y, cross_z);
}

// Scale A 3D Vector by a value
Vector3 v3_scale(Vector3 a, float value) {
    return v3_init(a.x*value, a.y*value, a.z*value);
}

// Length of a vector
float v3_length(Vector3 a)
{
    return sqrtf(((a.x*a.x)+(a.y*a.y)+(a.z*a.z)));
}

// Function that Normalizes a 3D Vector
Vector3 v3_normalize(Vector3 a) {
    float mag = v3_length(a);
    if (mag == 0.0f) return v3_init(0.0f, 0.0f, 0.0f);
    else return v3_init(a.x/mag, a.y/mag, a.z/mag);
}
