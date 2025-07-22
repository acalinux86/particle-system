#include "./matrix.h"

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
