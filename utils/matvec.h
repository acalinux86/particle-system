#ifndef MATVEC_H_
#define MATVEC_H_

#include "./matrix.h"
#include "./vector4.h"

Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4);
Matrix4 mv4_translate(Vector4 vec_4);
#endif // MATVEC_H_
