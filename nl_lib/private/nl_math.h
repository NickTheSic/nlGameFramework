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

#ifdef __cplusplus
}
#endif
#endif