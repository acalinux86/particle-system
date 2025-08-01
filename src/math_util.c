#include "./math_util.h"
#include "./system.h"
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


// Matrix4 Implementation
static inline void safe_memcpy(Matrix4 *dest, Matrix4 *src)
{
    if (src && dest) memcpy(dest, src, sizeof(Matrix4));
}

void mat4_print(const Matrix4 *self, const char *name)
{
    printf("Matrix4 (%s): {\n", name);
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        printf("    [ ");
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            printf("%3.2f ", self->rows[i][j]);
        }
        printf("]\n");
    }
    printf("}\n");
}

Matrix4 mat4_add(Matrix4 a, Matrix4 b)
{
    Matrix4 result = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = a.rows[i][j] + b.rows[i][j];
        }
    }
    return result;
}

Matrix4 mat4_sub(Matrix4 a, Matrix4 b)
{
    Matrix4 result = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = a.rows[i][j] - b.rows[i][j];
        }
    }
    return result;
}

Matrix4 mat4_mult(Matrix4 a, Matrix4 b)
{
    // a b    e f   ae + bg   af + bh
    //      X
    // c d    g h   ce + dg   cf + dh
    //

    Matrix4 result = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            float c = 0.0f;
            for (uint32_t k = 0; k < MAT4_COLS; ++k) {
                c += a.rows[i][k] * b.rows[k][j];
            }
            result.rows[i][j] = c;
        }
    }
    return result;
}

Matrix4 mat4_value(float value)
{
    /*Matrix4 result = {
        .rows = {
                {value, 0.0f,  0.0f,  0.0f},
                {0.0f,  value, 0.0f,  0.0f},
                {0.0f,  0.0f,  value, 0.0f},
                {0.0f,  0.0f,  0.0f,  1.0f}
        }
    };*/

    Matrix4 result = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = (i == j) ? value : 0.0f;
        }
    }

    result.rows[MAT4_ROWS - 1][MAT4_COLS - 1] = 1.0f;
    return result;
}

Matrix4 mat4_identity()
{
    return mat4_value(1.0f);
}

Matrix4 mat4_transpose(Matrix4 mat4)
{
    /* Matrix4 result =  {
        .rows = {
                {mat4.rows[0][0], mat4.rows[1][0], mat4.rows[2][0], mat4.rows[3][0]},
                {mat4.rows[0][1], mat4.rows[1][1], mat4.rows[2][1], mat4.rows[3][1]},
                {mat4.rows[0][2], mat4.rows[1][2], mat4.rows[2][2], mat4.rows[3][2]},
                {mat4.rows[0][3], mat4.rows[1][3], mat4.rows[2][3], mat4.rows[3][3]}
        }
    }; */

    Matrix4 result = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        for (uint32_t j = 0; j < MAT4_COLS; ++j) {
            result.rows[i][j] = mat4.rows[j][i];
        }
    }
    return result;
}

Matrix4 mat4_copy(Matrix4 mat4)
{
    Matrix4 result = {0};
    safe_memcpy(&result, &mat4);
    return result;
}

static inline float degrees_to_radians(float degrees)
{
    return degrees * (PI / 180.0f);
}

Matrix4 mat4_rotate_x(float degrees)
{
    float c = cosf(degrees_to_radians(degrees));
    float s = sinf(degrees_to_radians(degrees));

    if (fabsf(c) < EPSILON) c = 0.0f;
    if (fabsf(s) < EPSILON) s = 0.0f;
    Matrix4 result =  {
        .rows = {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f,    c,   -s, 0.0f},
                {0.0f,    s,    c, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    return result;
}

Matrix4 mat4_rotate_y(float degrees)
{
    float c = cosf(degrees_to_radians(degrees));
    float s = sinf(degrees_to_radians(degrees));

    if (fabsf(c) < EPSILON) c = 0.0f;
    if (fabsf(s) < EPSILON) s = 0.0f;
    Matrix4 result =  {
        .rows = {
                {   c, 0.0f,    s, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {  -s, 0.0f,    c, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    return result;
}

Matrix4 mat4_rotate_z(float degrees)
{
    float c = cosf(degrees_to_radians(degrees));
    float s = sinf(degrees_to_radians(degrees));

    if (fabsf(c) < EPSILON) c = 0.0f;
    if (fabsf(s) < EPSILON) s = 0.0f;
    Matrix4 result =  {
        .rows = {
                {   c,   -s, 0.0f, 0.0f},
                {   s,    c, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    return result;
}


Vector4 v4_from_v3(Vector3 vec3)
{
    return v4_init(vec3.x, vec3.y, vec3.z, 1.0f);
}

Vector3 v3_from_v4(Vector4 vec4)
{
    return v3_init(vec4.x, vec4.y, vec4.z);
}

Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4)
{
    /* return v4_init(
        ((mat_4.row1[0] * vec_4.x) + (mat_4.row1[1] * vec_4.y) + (mat_4.row1[2] * vec_4.z) + (mat_4.row1[3] * vec_4.w)),
        ((mat_4.row2[0] * vec_4.x) + (mat_4.row2[1] * vec_4.y) + (mat_4.row2[2] * vec_4.z) + (mat_4.row2[3] * vec_4.w)),
        ((mat_4.row3[0] * vec_4.x) + (mat_4.row3[1] * vec_4.y) + (mat_4.row3[2] * vec_4.z) + (mat_4.row3[3] * vec_4.w)),
        ((mat_4.row4[0] * vec_4.x) + (mat_4.row4[1] * vec_4.y) + (mat_4.row4[2] * vec_4.z) + (mat_4.row4[3] * vec_4.w))
    );*/

    float v4[MAT4_ROWS] = {0};
    for (uint32_t i = 0; i < MAT4_ROWS; ++i) {
        v4[i] = ((mat_4.rows[i][0] * vec_4.x) +
                 (mat_4.rows[i][1] * vec_4.y) +
                 (mat_4.rows[i][2] * vec_4.z) +
                 (mat_4.rows[i][3] * vec_4.w));
    }

    return v4_init(v4[0], v4[1], v4[2], v4[3]);
}

Matrix4 mv4_translate(Vector4 vec_4)
{
    // NOTE: We Only Translate points
    Matrix4 result = {
        .rows = {
                {1.0f, 0.0f, 0.0f, vec_4.x},
                {0.0f, 1.0f, 0.0f, vec_4.y},
                {0.0f, 0.0f, 1.0f, vec_4.z},
                {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    return result;
}

Vector3 to_screen_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height)
{
    Vector4 vec4 = v4_from_v3(vec3);
    float x = screen_width / 2.0f;
    float y = screen_height / 2.0f;

    Matrix4 ModelMatrix = {
        .rows = {
            {x,    0.0f, 0.0f,    x},
            {0.0f,   -y, 0.0f,    y},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    Vector4 TransformedVec4 = mv4_transform(ModelMatrix, vec4);
    return v3_from_v4(TransformedVec4);
}

Vector3 to_world_coords(Vector3 vec3, uint32_t screen_width, uint32_t screen_height)
{
    Vector4 vec4 = v4_from_v3(vec3);
    float x = 2.0f / screen_width;
    float y = 2.0f / screen_height;

    Matrix4 ModelMatrix = {
        .rows = {
            {x,    0.0f, 0.0f,    -1},
            {0.0f,    y, 0.0f,    -1},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };

    Vector4 TransformedVec4 = mv4_transform(ModelMatrix, vec4);
    return v3_from_v4(TransformedVec4);
}
