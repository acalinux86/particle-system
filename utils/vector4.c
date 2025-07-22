#include "./vector4.h"

// NOTE: Vector4 Implementation

// Pseudo Constructor for Vector4
Vector4 v4_init(float x, float y, float z, float w)
{
    return (Vector4){x, y, z, w};
}

// Constructor for Vector4 Point 
Vector4 v4_point(float x, float y, float z)
{
    return v4_init(x, y, z, 1.0f);
}

// Constructor for Vector4 Direction
Vector4 v4_direction(float x, float y, float z)
{
    return v4_init(x, y, z, 0.0f);
}

void v4_print(const Vector4 *self, const char *name)
{
    if (self->w != 0) {
        printf("Point (%s): [%.2f, %.2f, %.2f, %.2f]\n", name, self->x, self->y, self->z, self->w);
    } else {
        printf("Direction (%s): [%.2f, %.2f, %.2f, %.2f]\n", name, self->x, self->y, self->z, self->w);
    }
}

Vector4 v4_add(Vector4 a, Vector4 b) {
    return v4_init(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); // Operates on all components
}

// Function that Subtracts Two Vector
Vector4 v4_sub(Vector4 a, Vector4 b) {
    return v4_init(a.x-b.x, a.y-b.y, a.z-b.z, a.w - b.w); // Operates on all components
}

// Function that returns the Dot Product of two Vectors -> (a float)
float v4_dot(Vector4 a, Vector4 b) {
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

// Function that Returns A Cross Product of two Vectors
Vector4 v4_cross(Vector4 a, Vector4 b) {
    float cross_x = a.y * b.z - a.z * b.y;
    float cross_y = a.z * b.x - a.x * b.z;
    float cross_z = a.x * b.y - a.y * b.x;

    return v4_init(cross_x, cross_y, cross_z, 0); // cross product always returns direction
}

// Scale A 4D Vector by a value
Vector4 v4_scale(Vector4 a, float value) {
    // Preserve w (0 for directions) (1 for points)
    return v4_init(a.x*value, a.y*value, a.z*value, a.w);
}

// Length of a vector
float v4_length(Vector4 a)
{
    // Only Compute Length for 3d Products (Homogenous coordinates)
    return sqrtf(((a.x*a.x)+(a.y*a.y)+(a.z*a.z)));
}

// Function that Normalizes a 4D Vector
Vector4 v4_normalize(Vector4 a)
{
    float mag = v4_length(a);
    if (mag == 0.0f) return v4_init(0.0f, 0.0f, 0.0f, a.w); // Preserve Original w
    else return v4_init(a.x/mag, a.y/mag, a.z/mag, a.w); // Preserve Original w
}

Vector4 v4_perspective_divide(Vector4 a)
{
    if (a.w == 0) return a;
    else return v4_point(a.x/a.w, a.y/a.w, a.z/a.w);
}

bool v4_equals(Vector4 a, Vector4 b)
{
    if (a.w != b.w) return false;
    if (a.w == 0) {
        return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
    } else {
        Vector4 norm_a = v4_perspective_divide(a);
        Vector4 norm_b = v4_perspective_divide(b);

        return  (norm_a.x == norm_b.x) &&
                (norm_a.y == norm_b.y) &&
                (norm_a.z == norm_b.z);
    }
}
