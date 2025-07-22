#ifndef MATRIX4_H
#define MATRIX4_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    float row1[4];
    float row2[4];
    float row3[4];
    float row4[4];
} Matrix4;

Matrix4 mat4_init(float row1[], float row2[], float row3[], float row4[]);

#endif // MATRIX4_H
