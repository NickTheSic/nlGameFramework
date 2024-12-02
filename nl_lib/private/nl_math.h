#ifndef __NL_MATH_H__
#define __NL_MATH_H__
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __PSX__
// Terrible but there are no floats so this is a place to start
#define float int
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

typedef struct v4f v4f;
struct v4f
{
    float x,y,z,w;
};

typedef struct transform2d transform2d;
struct transform2d
{
    v2f position;
    v2f size;
    float rotation;
};
void initialize_transform2d(transform2d* const t);

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
void create_fustrum(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z);

void create_srt_matrix(mat4x4f* const mat, const v3f scale, const v3f rot, const v3f translation);
void create_srt_matrix_from_transform2d(mat4x4f* const mat, transform2d transform);

void matrix_to_matrix_multiplication(mat4x4f* const result, mat4x4f* const o);
int invert_matrix_4x4(const mat4x4f* const original, mat4x4f* const inverse);
int invert_matrix_4x4_glm(const mat4x4f * original, mat4x4f* const inverse);
float matrix_determinant(const mat4x4f* const matrix);


float v3f_length_squared(const v3f vec);
float v3f_length(const v3f vec);
float v3f_dot(const v3f ref, const v3f other);
v3f   v3f_subtract(const v3f lhs, const v3f rhs);
v3f   v3f_add(const v3f lhs, const v3f rhs);
v3f   v3f_normalize(const v3f vec);
v3f   v3f_cross(const v3f lhs, const v3f rhs);

float v2f_length_squared(const v2f vec);
float v2f_length(const v2f vec);
float v2f_dot(const v2f ref, const v2f other);
v2f   v2f_subtract(const v2f lhs, const v2f rhs);
v2f   v2f_add(const v2f lhs, const v2f rhs);
v2f   v2f_normalize(const v2f vec);
v2f   v2f_cross(const v2f lhs, const v2f rhs);


void  v2i_mat4_transfrom(v2i* const lhs, const mat4x4f* const mat);
void  v2f_mat4_transform(v2f* const lhs, const mat4x4f* const mat);


// #ifdef __PSX__
// #undef float
// #endif


#ifdef __cplusplus
}
#endif
#endif