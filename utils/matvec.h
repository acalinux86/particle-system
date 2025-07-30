#ifndef MATVEC_H_
#define MATVEC_H_

#include "./matrix.h"
#include "./vector4.h"
#include "./vector3.h"

Vector4 v4_from_v3(Vector3 vec3);
Vector3 v3_from_v4(Vector4 vec4);
Vector4 mv4_transform(Matrix4 mat_4, Vector4 vec_4);
Matrix4 mv4_translate(Vector4 vec_4);
Vector3 to_screen_coords(Vector3 vec3, float screen_width, float screen_height);

#endif // MATVEC_H_
