#include "../nl_math.h"
#include "math.h"
#include "string.h" // memset

void create_identity_matrix(mat4x4f* const mat)
{
    memset(mat, 0, sizeof(mat4x4f));
    mat->m11 = 1;
    mat->m22 = 1;
    mat->m33 = 1;
    mat->m44 = 1;

    //mat->m12 = 0;
    //mat->m13 = 0;
    //mat->m14 = 0;
    //mat->m21 = 0;
    //mat->m23 = 0;
    //mat->m24 = 0;
    //mat->m31 = 0;
    //mat->m32 = 0;
    //mat->m34 = 0;
    //mat->m41 = 0;
    //mat->m42 = 0;
    //mat->m43 = 0;
}

void create_orthographic_projection(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
    memset(mat, 0, sizeof(mat4x4f));

    float delta_x = right-left;
    float delta_y = top-bottom;
    float delta_z = far_z-near_z;
    
    mat->m11 = 2.0f/delta_x;
    //mat.m12 = mat.m13 = mat.m14 = 0.0f;
    
    mat->m22 = 2.0f/delta_y;
    //mat.m21 = mat.m23 = mat.m24 = 0.0f;
    
    mat->m33 = -2.0f/delta_z;
    //mat.m31 = mat.m32 = mat.m34 = 0.0f;
    
    mat->m41 = -(right + left) / delta_x;
    mat->m42 = -(top + bottom) / delta_y;
    mat->m43 = -(near_z) / delta_z;
    mat->m44 = 1;
}

float v3f_length_squared(const v3f vec)
{
    return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
}

float v3f_length(const v3f vec)
{
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y) +(vec.z * vec.z));
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
    float len = vector_length_squared(vec);

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

}
