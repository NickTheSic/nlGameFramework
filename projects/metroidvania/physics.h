#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "private/nl_math.h"

typedef struct aabb aabb;
struct aabb
{
    v2f min;
    v2f max;
};


static inline int box_in_box_with_size_pos(aabb left, aabb right)
{
    if (left.max.x < right.min.x || left.min.x > right.min.x) return 0;
    if (left.max.y < right.min.y || left.min.y > right.min.y) return 0;

    return 1;
}

#endif//__PHYSICS_H__