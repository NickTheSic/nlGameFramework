#include "../nl_math.h"
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
