#ifndef __NL_PHYSICS_2D_H__
#define __NL_PHYSICS_2D_H__

#include "private/nl_math.h"

typedef struct aabb aabb;
struct aabb
{
    v2f min;
    v2f max;
};

typedef struct circle_collider circle_collider;
struct circle_collider
{
    v2f position;
    float radius;
};

static inline int aabb_box_overlap(aabb left, aabb right)
{
    if (left.max.x < right.min.x || left.min.x > right.max.x) return 0;
    if (left.max.y < right.min.y || left.min.y > right.max.y) return 0;

    return 1;
}

static inline int circle_collider_overlap(circle_collider left, circle_collider right)
{
    const float distx = left.position.x - right.position.x;
    const float disty = left.position.y - right.position.y;
    const float distance = (distx*distx) + (disty*disty);
    const float radii = (left.radius*left.radius) + (right.radius*right.radius);

    return distance <= radii;
}

#endif//__NL_PHYSICS_2D_H__