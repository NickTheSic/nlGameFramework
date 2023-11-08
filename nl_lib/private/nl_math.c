#include "nl_math.h"

void create_identity_matrix(mat4x4f* const mat)
{
    mat->m11 = 1;
    mat->m22 = 1;
    mat->m33 = 1;
    mat->m44 = 1;

    mat->m12 = 0;
    mat->m13 = 0;
    mat->m14 = 0;

    mat->m21 = 0;
    mat->m23 = 0;
    mat->m24 = 0;
    
    mat->m31 = 0;
    mat->m32 = 0;
    mat->m34 = 0;

    mat->m41 = 0;
    mat->m42 = 0;
    mat->m43 = 0;
}
