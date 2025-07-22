#include "./matvec.h"

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
