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

void create_fustrum(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
    (void)mat;
    (void)left;
    (void)right;
    (void)bottom;
    (void)top;
    (void)near_z;
    (void)far_z;
}

void create_orthographic_projection(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
    memset(mat, 1, sizeof(mat4x4f));

    float delta_x = right-left;
    float delta_y = top-bottom;
    float delta_z = far_z-near_z;
    
    mat->m11 = 2.0f/delta_x;
    //mat.m12 = mat.m13 = mat.m14 = 0.0f;
    
    mat->m22 = 2.0f/delta_y;
    //mat.m21 = mat.m23 = mat.m24 = 0.0f;
    
    //mat->m33 = -2.0f/delta_z; //Right Handed
    mat->m33 = 2.0f/delta_z; //Left Handed
    //mat.m31 = mat.m32 = mat.m34 = 0.0f;
    
    mat->m41 = -(right + left) / delta_x;
    mat->m42 = -(top + bottom) / delta_y;
    mat->m43 = -(near_z) / delta_z;
    mat->m44 = 1;
}

internal_function void scale_matrix_3f(mat4x4f* const mat, v3f scale)
{
    mat->m11 *= scale.x; mat->m21 *= scale.x; mat->m31 *= scale.x; mat->m41 *= scale.x;
    mat->m12 *= scale.y; mat->m22 *= scale.y; mat->m32 *= scale.y; mat->m42 *= scale.y;
    mat->m13 *= scale.z; mat->m23 *= scale.z; mat->m33 *= scale.z; mat->m43 *= scale.z;
}

internal_function void scale_matrix_2f(mat4x4f* const mat, v2f scale)
{
    mat->m11 *= scale.x; mat->m21 *= scale.x; mat->m31 *= scale.x; mat->m41 *= scale.x;
    mat->m12 *= scale.y; mat->m22 *= scale.y; mat->m32 *= scale.y; mat->m42 *= scale.y;
    mat->m13 *= 1.0f;    mat->m23 *= 1.0f;    mat->m33 *= 1.0f;    mat->m43 *= 1.0f;
}

internal_function void scale_matrix_1f(mat4x4f* const mat, float scale)
{
    mat->m11 *= scale; mat->m21 *= scale; mat->m31 *= scale; mat->m41 *= scale;
    mat->m12 *= scale; mat->m22 *= scale; mat->m32 *= scale; mat->m42 *= scale;
    mat->m13 *= scale; mat->m23 *= scale; mat->m33 *= scale; mat->m43 *= scale;
}

internal_function void rotate_matrix(mat4x4f* const mat, float angle, float x, float y, float z)
{
    (void)mat;(void)angle;(void)x;(void)y;(void)z;
    NL_UNIMPLEMENTED_FUNC
}

internal_function void translate_matrix(mat4x4f* const mat, v3f pos)
{
    mat->m41 += pos.x;
    mat->m42 += pos.y;
    mat->m43 += pos.z;
}

void create_srt_matrix(mat4x4f* const mat, const v3f scale, const v3f rot, const v3f translation)
{
    scale_matrix_3f(mat, scale);
    rotate_matrix(mat, rot.z, 0,0,1);//roll
    rotate_matrix(mat, rot.x, 1,0,0);//pitch
    rotate_matrix(mat, rot.y, 0,1,0);//yaw
    translate_matrix(mat, translation);
}

void create_srt_matrix_from_transform2d(mat4x4f* const mat, transform2d transform)
{
    scale_matrix_2f(mat, transform.size);
    rotate_matrix(mat, transform.rotation, 0,0,1); //roll
    translate_matrix(mat, transform.position);
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
    v3f result = {0};
    return (result);
}   

float v2f_length_squared(const v2f vec)
{   
    return (vec.x*vec.x)+(vec.y*vec.y);
}

float v2f_length(const v2f vec)
{
    return sqrtf((vec.x*vec.x)+(vec.y*vec.y));
}

float v2f_dot(const v2f ref, const v2f other)
{
    return (ref.x * other.x) + (ref.y * other.y);
}

v2f v2f_subtract(const v2f lhs, const v2f rhs)
{
    (void)lhs; (void)rhs;
    v2f result = {0};
    NL_UNIMPLEMENTED_FUNC
    return result;
}

v2f v2f_add(const v2f lhs, const v2f rhs)
{
    (void)lhs; (void)rhs;
    v2f result = {0};
    NL_UNIMPLEMENTED_FUNC
    return result;
}

v2f v2f_normalize(const v2f vec)
{
    (void)vec;
    v2f result = {0};
    NL_UNIMPLEMENTED_FUNC
    return result;
}

void initialize_transform2d(transform2d* const t)
{
    t->position = (v3f){0,0,0};
    t->size = (v2f){1,1};
    t->rotation = 0.0f;
}
