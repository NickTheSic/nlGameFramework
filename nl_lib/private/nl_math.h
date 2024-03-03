#ifndef __NL_MATH_H__
#define __NL_MATH_H__
#ifdef __cplusplus
extern "C" {
#endif


typedef struct v2i v2i;
struct v2i
{
    int x;
    int y;
};

typedef struct v2f v2f;
struct v2f 
{
    float x;
    float y;
};

typedef struct v3f v3f;
struct v3f
{
    float x, y, z;
};

typedef struct mat4x4f mat4x4f;
struct mat4x4f
{
    float m11,m12,m13,m14,
          m21,m22,m23,m24,
          m31,m32,m33,m34,
          m41,m42,m43,m44;
};

void create_identity_matrix(mat4x4f* const mat);

void create_orthographic_projection(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z);

float vector_length_squared(const v3f vec);
float vector_length(const v3f vec);

v3f vector_subtract(const v3f lhs, const v3f rhs);
v3f vector_add(const v3f lhs, const v3f rhs);

v3f vector_normalize(const v3f vec);
v3f vector_cross(const v3f lhs, const v3f rhs);

#ifdef __cplusplus
}
#endif
#endif