#include "../nl_math.h"
#include "math.h"
#include "string.h" // memset

#define PI 3.14159f

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
    NL_UNUSED(mat);
    NL_UNUSED(left);
    NL_UNUSED(right);
    NL_UNUSED(bottom);
    NL_UNUSED(top);
    NL_UNUSED(near_z);
    NL_UNUSED(far_z);
}

void create_orthographic_projection(mat4x4f* const mat, float left, float right, float bottom, float top, float near_z, float far_z)
{
    //memset(mat, 0, sizeof(mat4x4f));

    float delta_x = right-left;
    float delta_y = top-bottom;
    float delta_z = far_z-near_z;
    
    mat->m11 = 2.0f/delta_x;
    mat->m12 = mat->m13 = mat->m14 = 0.0f;
    
    mat->m22 = 2.0f/delta_y;
    mat->m21 = mat->m23 = mat->m24 = 0.0f;
    
    //mat->m33 = -2.0f/delta_z; //Right Handed
    mat->m33 = 2.0f/delta_z; //Left Handed
    mat->m31 = mat->m32 = mat->m34 = 0.0f;
    
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
    float magnitude = sqrtf((x*x)+(y*y)+(z*z));

    if (magnitude > 0.0f)
    {
        x/=magnitude;
        y/=magnitude;
        z/=magnitude;

        float xx = x*x;
        float yy = y*y;
        float zz = z*z;
        float xy = x*y;
        float yz = y*z;
        float zx = z*x;
        float sin_angle = sinf(angle * PI/180.0f);
        float xs = x * sin_angle;
        float ys = y * sin_angle;
        float zs = z * sin_angle;
        float cos_angle = cosf(angle * PI/180.0f);
        float one_sub_cos = 1.0f - cos_angle;

        mat4x4f rot = {0};
        create_identity_matrix(&rot);
        rot.m11 = (one_sub_cos * xx) + cos_angle;
        rot.m12 = (one_sub_cos * xy) - zs;
        rot.m13 = (one_sub_cos * zx) + ys;
        rot.m21 = (one_sub_cos * xy) + zs;
        rot.m22 = (one_sub_cos * yy) + cos_angle;
        rot.m23 = (one_sub_cos * yz) - xs;
        rot.m31 = (one_sub_cos * zx) - ys;
        rot.m32 = (one_sub_cos * yz) + xs;
        rot.m33 = (one_sub_cos * zz) + cos_angle;

        matrix_to_matrix_multiplication(mat, &rot);
    }
}

internal_function void translate_matrix(mat4x4f* const mat, v3f pos)
{
    mat->m41 += pos.x;
    mat->m42 += pos.y;
    mat->m43 += pos.z;
}

internal_function void translate_matrix2f(mat4x4f* const mat, v2f pos)
{
    mat->m41 += pos.x;
    mat->m42 += pos.y;
}

void create_srt_matrix(mat4x4f* const mat, const v3f scale, const v3f rot, const v3f translation)
{
    create_identity_matrix(mat);

    scale_matrix_3f(mat, scale);
    rotate_matrix(mat, rot.z, 0.0f,0.0f,1.0f);//roll
    rotate_matrix(mat, rot.x, 1.0f,0.0f,0.0f);//pitch
    rotate_matrix(mat, rot.y, 0.0f,1.0f,0.0f);//yaw
    translate_matrix(mat, translation);
}

void matrix_to_matrix_multiplication(mat4x4f* const result, mat4x4f* const o)
{
    mat4x4f temp = {0};

    temp.m11 = result->m11 * o->m11 + result->m21 * o->m12 + result->m31 * o->m13 + result->m41 * o->m14;
    temp.m12 = result->m12 * o->m11 + result->m22 * o->m12 + result->m32 * o->m13 + result->m42 * o->m14;
    temp.m13 = result->m13 * o->m11 + result->m23 * o->m12 + result->m33 * o->m13 + result->m43 * o->m14;
    temp.m14 = result->m14 * o->m11 + result->m24 * o->m12 + result->m34 * o->m13 + result->m44 * o->m14;
    temp.m21 = result->m11 * o->m21 + result->m21 * o->m22 + result->m31 * o->m23 + result->m41 * o->m24;
    temp.m22 = result->m12 * o->m21 + result->m22 * o->m22 + result->m32 * o->m23 + result->m42 * o->m24;
    temp.m23 = result->m13 * o->m21 + result->m23 * o->m22 + result->m33 * o->m23 + result->m43 * o->m24;
    temp.m24 = result->m14 * o->m21 + result->m24 * o->m22 + result->m34 * o->m23 + result->m44 * o->m24;
    temp.m31 = result->m11 * o->m31 + result->m21 * o->m32 + result->m31 * o->m33 + result->m41 * o->m34;
    temp.m32 = result->m12 * o->m31 + result->m22 * o->m32 + result->m32 * o->m33 + result->m42 * o->m34;
    temp.m33 = result->m13 * o->m31 + result->m23 * o->m32 + result->m33 * o->m33 + result->m43 * o->m34;
    temp.m34 = result->m14 * o->m31 + result->m24 * o->m32 + result->m34 * o->m33 + result->m44 * o->m34;
    temp.m41 = result->m11 * o->m41 + result->m21 * o->m42 + result->m31 * o->m43 + result->m41 * o->m44;
    temp.m42 = result->m12 * o->m41 + result->m22 * o->m42 + result->m32 * o->m43 + result->m42 * o->m44;
    temp.m43 = result->m13 * o->m41 + result->m23 * o->m42 + result->m33 * o->m43 + result->m43 * o->m44;
    temp.m44 = result->m14 * o->m41 + result->m24 * o->m42 + result->m34 * o->m43 + result->m44 * o->m44;

    *result = temp;
}

float matrix_determinant(const mat4x4f* const matrix)
{
    mat4x4f m = *matrix;

    const float factor1 = m.m33 * m.m44 - m.m43 * m.m34;
    const float factor2 = m.m32 * m.m44 - m.m42 * m.m34;
    const float factor3 = m.m32 * m.m43 - m.m42 * m.m33;
    const float factor4 = m.m31 * m.m44 - m.m41 * m.m34;
	const float factor5 = m.m31 * m.m43 - m.m41 * m.m33;
    const float factor6 = m.m31 * m.m42 - m.m41 * m.m32;

    v4f determinant_coefficient = {0};
    determinant_coefficient.x =  (m.m22 * factor1 - m.m23 * factor2 + m.m24 * factor3);
    determinant_coefficient.y = -(m.m21 * factor1 - m.m23 * factor4 + m.m24 * factor5);
    determinant_coefficient.z =  (m.m21 * factor2 - m.m22 * factor4 + m.m24 * factor6);
    determinant_coefficient.w = -(m.m21 * factor3 - m.m22 * factor5 + m.m23 * factor6);

	return 
        m.m11 * determinant_coefficient.x + 
        m.m12 * determinant_coefficient.y + 
        m.m13 * determinant_coefficient.z + 
        m.m41 * determinant_coefficient.w ;
}

int invert_matrix_4x4(const mat4x4f* const original, mat4x4f* const inverse)
{
    int determinant = matrix_determinant(original);

    if (determinant == 0) return 0;

    mat4x4f temp = *original;

    const float inverse_det = 1.0f / (float)determinant;
    for (int i = 0; i < 16; i += 4)
    {
        (&temp.m11)[i+0] *= inverse_det;
        (&temp.m11)[i+1] *= inverse_det;
        (&temp.m11)[i+2] *= inverse_det;
        (&temp.m11)[i+3] *= inverse_det;
    }

    *inverse = temp;
    return 1;
}

int invert_matrix_4x4_glm(const mat4x4f* const og, mat4x4f* const inverse)
{
    mat4x4f temp = {0};
    mat4x4f original = *og;

    const float factor1  = (original.m33 * original.m44) - (original.m43 * original.m34);
    const float factor2  = (original.m32 * original.m44) - (original.m42 * original.m34);
    const float factor3  = (original.m32 * original.m43) - (original.m42 * original.m33);
    const float factor4  = (original.m31 * original.m44) - (original.m41 * original.m34);
    const float factor5  = (original.m31 * original.m43) - (original.m41 * original.m33);
	const float factor6  = (original.m31 * original.m42) - (original.m41 * original.m32);
	const float factor7  = (original.m23 * original.m44) - (original.m43 * original.m24);
	const float factor8  = (original.m22 * original.m44) - (original.m42 * original.m24);
	const float factor9  = (original.m22 * original.m43) - (original.m42 * original.m23);
	const float factor10 = (original.m21 * original.m44) - (original.m41 * original.m24);
	const float factor11 = (original.m21 * original.m43) - (original.m41 * original.m23);
	const float factor12 = (original.m21 * original.m42) - (original.m41 * original.m22);
	const float factor13 = (original.m23 * original.m34) - (original.m33 * original.m24);
	const float factor14 = (original.m22 * original.m34) - (original.m32 * original.m24);
	const float factor15 = (original.m22 * original.m33) - (original.m32 * original.m23);
	const float factor16 = (original.m21 * original.m34) - (original.m31 * original.m24);
	const float factor17 = (original.m21 * original.m33) - (original.m31 * original.m23);
	const float factor18 = (original.m21 * original.m32) - (original.m31 * original.m22);

    temp.m11 =  (original.m22 * factor1 - original.m23 * factor1 + original.m24 * factor3);
    temp.m12 = -(original.m21 * factor1 - original.m23 * factor3 + original.m24 * factor5);
    temp.m13 =  (original.m21 * factor2 - original.m22 * factor3 + original.m24 * factor6);
    temp.m14 = -(original.m21 * factor3 - original.m22 * factor5 + original.m23 * factor6);

    temp.m21 = -(original.m12 * factor1 - original.m13 * factor2 + original.m14 * factor3);
    temp.m22 =  (original.m11 * factor1 - original.m13 * factor4 + original.m14 * factor5);
    temp.m23 = -(original.m11 * factor2 - original.m12 * factor4 + original.m14 * factor6);
    temp.m24 =  (original.m11 * factor3 - original.m12 * factor5 + original.m13 * factor6);

    temp.m31 =  (original.m12 * factor7 - original.m13 * factor8 + original.m14 * factor9);
    temp.m32 = -(original.m11 * factor7 - original.m13 * factor10 + original.m14 * factor11);
    temp.m33 =  (original.m11 * factor8 - original.m12 * factor10 + original.m14 * factor12);
    temp.m34 = -(original.m11 * factor9 - original.m12 * factor11 + original.m13 * factor12);

    temp.m41 = -(original.m12 * factor13 - original.m13 * factor14 + original.m14 * factor15);
    temp.m42 =  (original.m11 * factor13 - original.m13 * factor16 + original.m14 * factor17);
    temp.m43 = -(original.m11 * factor14 - original.m12 * factor16 + original.m14 * factor18);
    temp.m44 =  (original.m11 * factor15 - original.m12 * factor17 + original.m13 * factor18);

    const float det = original.m11 * temp.m11 + original.m12 * temp.m12	+ original.m13 * temp.m13 + original.m14 * temp.m14;
    if (det == 0.0f) return 0;

    const float inverse_det = 1.0f / det;
    for (int i = 0; i < 16; i += 4)
    {
        (&temp.m11)[i+0] *= inverse_det;
        (&temp.m11)[i+1] *= inverse_det;
        (&temp.m11)[i+2] *= inverse_det;
        (&temp.m11)[i+3] *= inverse_det;
    }

    *inverse = temp;
    return 1;
}

internal_function void rotate2d_roll(mat4x4f* const mat, float angle)
{
    float sin_angle = sinf(angle * PI/180.0f);
    float cos_angle = cosf(angle * PI/180.0f);
    mat4x4f rot = {0};
    rot.m11 = cos_angle;
    rot.m12 = -sin_angle;
    rot.m21 = sin_angle;
    rot.m22 = cos_angle;
    rot.m33 = 1.0;
    rot.m44 = 1.0;
    matrix_to_matrix_multiplication(mat, &rot);
}


void create_srt_matrix_from_transform2d(mat4x4f* const mat, transform2d transform)
{
    scale_matrix_2f(mat, transform.size);
    rotate2d_roll(mat, transform.rotation);
    //rotate_matrix(mat, transform.rotation, 0,0,1); //roll
    translate_matrix2f(mat, transform.position);
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
    v2i temp = {0};

    const float w = 1.0f / (mat->m41 * lhs->x + mat->m42 * lhs->y + mat->m44);

    temp.x = ((mat->m11 * lhs->x) + (mat->m12 * lhs->y) + mat->m14) * w;
    temp.y = ((mat->m21 * lhs->x) + (mat->m22 * lhs->y) + mat->m24) * w;

    *lhs = temp;
}

void v2f_mat4_transform(v2f* const lhs, const mat4x4f* const mat)
{
    v2f temp = {0};

    const float w = 1.0f / (mat->m41 * lhs->x + mat->m42 * lhs->y + mat->m44);

    temp.x = ((mat->m11 * lhs->x) + (mat->m12 * lhs->y) + mat->m14) * w;
    temp.y = ((mat->m21 * lhs->x) + (mat->m22 * lhs->y) + mat->m24) * w;

    *lhs = temp;
}

void initialize_transform2d(transform2d* const t)
{
    t->position = (v2f){0,0};
    t->size = (v2f){1,1};
    t->rotation = 0.0f;
}
