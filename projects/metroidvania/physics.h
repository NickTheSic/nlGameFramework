#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "private/nl_math.h"

typedef struct aabb aabb;
struct aabb
{
    v2f min;
    v2f max;
};

static inline int aabb_box_overlap(aabb left, aabb right)
{
    if (left.max.x < right.min.x || left.min.x > right.max.x) return 0;
    if (left.max.y < right.min.y || left.min.y > right.max.y) return 0;

    return 1;
}

#endif//__PHYSICS_H__