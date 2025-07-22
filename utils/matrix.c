#include "./matrix.h"

static inline void safe_memcpy(float dest[4], float src[4])
{
    if (src && dest) memcpy(dest, src, sizeof(float) * 4);
}

Matrix4 mat4_init(float row1[], float row2[], float row3[], float row4[])
{
    Matrix4 result;
    safe_memcpy(result.row1, row1);
    safe_memcpy(result.row2, row2);
    safe_memcpy(result.row3, row3);
    safe_memcpy(result.row4, row4);
    return result;
}
