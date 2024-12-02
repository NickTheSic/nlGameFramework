#include "../nl_math.h"
#include "string.h" // memset

#define PI 3.14159f


void create_identity_matrix(mat4x4f* const mat)
{
}

void create_fustrum(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
}

void create_orthographic_projection(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
}

void create_srt_matrix(mat4x4f* const mat, const v3f scale, const v3f rot, const v3f translation)
{
   
}

void matrix_to_matrix_multiplication(mat4x4f* const result, mat4x4f* const o)
{
    
}

float matrix_determinant(const mat4x4f* const matrix)
{
    return 0;
}

int invert_matrix_4x4(const mat4x4f* const original, mat4x4f* const inverse)
{
    return 0;
}

int invert_matrix_4x4_glm(const mat4x4f* const og, mat4x4f* const inverse)
{
    return 0;
}

void create_srt_matrix_from_transform2d(mat4x4f* const mat, transform2d transform)
{
    
}

float v3f_length_squared(const v3f vec)
{
    return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
}

float v3f_length(const v3f vec)
{
    return v3f_length_squared(vec);
}

float v3f_dot(const v3f ref, const v3f other)
{
    return (ref.x * other.x) + (ref.y * other.y) + (ref.z * other.z);
}

v3f v3f_subtract(const v3f lhs, const v3f rhs)
{
    v3f result = {0};
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

v3f v3f_add(const v3f lhs, const v3f rhs)
{
    v3f result = {0};
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;
    return result;
}

v3f v3f_normalize(const v3f vec)
{
    v3f result = {0};
    float len = v3f_length_squared(vec);

    if (len != 0)
    {
        result.x = vec.x/len;
        result.y = vec.y/len;
        result.z = vec.z/len;
    }

    return result;
}

v3f v3f_cross(const v3f lhs, const v3f rhs)
{
    NL_UNIMPLEMENTED_FUNC;
    (void)lhs; (void)rhs;
    return (v3f){0,0,0};
}   

float v2f_length_squared(const v2f vec)
{   
    return (vec.x*vec.x)+(vec.y*vec.y);
}

float v2f_length(const v2f vec)
{
    return v2f_length_squared(vec);
}

float v2f_dot(const v2f ref, const v2f other)
{
    return (ref.x * other.x) + (ref.y * other.y);
}

v2f v2f_subtract(const v2f lhs, const v2f rhs)
{
    v2f result = {0};
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    return result;
}

v2f v2f_add(const v2f lhs, const v2f rhs)
{
    v2f result = {0};
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}

v2f v2f_normalize(const v2f vec)
{
    v2f result = {0};
    const float length = v2f_length(vec);

    if (length != 0.0f)
    {
        result.x = vec.x/length;
        result.y = vec.y/length;
    }
        
    return result;
}

void v2i_mat4_transfrom(v2i* const lhs, const mat4x4f* const mat)
{

}

void v2f_mat4_transform(v2f* const lhs, const mat4x4f* const mat)
{

}

void initialize_transform2d(transform2d* const t)
{
    t->position = (v2f){0,0};
    t->size = (v2f){1,1};
    t->rotation = 0.0f;
}
