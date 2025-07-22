#include "./vector2.h"

// NOTE: VECTOR2 Implementation
Vector2 v2_init(float x, float y)
{
    return (Vector2) {x , y};
}

void v2_print(const Vector2 *self)
{
    printf("Vector2: [%.2f, %.2f]\n", self->x, self->y);
}

Vector2 v2_add(Vector2 a, Vector2 b)
{
    return v2_init(a.x + b.x, a.y + b.y);
}

Vector2 v2_sub(Vector2 a, Vector2 b)
{
    return v2_init(a.x - b.x, a.y - b.y);
}

// NOTE: If value is negative, direction reverses else unchanged
Vector2 v2_scale(Vector2 a, float value)
{
    return v2_init(a.x*value, a.y*value);
}

float v2_perp_dot(Vector2 a, Vector2 b)
{
    return (a.x*b.y - a.y*b.x);
}

float v2_dot(Vector2 a, Vector2 b)
{
    return (a.x*b.x) + (a.y*b.y);
}

// NOTE: returns the Magnitude of a Vector
float v2_length(Vector2 a)
{
    return sqrtf((a.x*a.x) + (a.y*a.y));
}

Vector2 v2_normalize(Vector2 a) {
    float mag = v2_length(a);
    if (mag == 0.0f) return v2_init(0.0f, 0.0f);
    else return v2_init(a.x/mag, a.y/mag);
}
