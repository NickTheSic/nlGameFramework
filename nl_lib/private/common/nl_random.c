#include "../nl_random.h"
#include "stdlib.h"

void init_random_number_generator(int seed)
{
    srand(seed);
}

inline static float random_percent()
{
    return (float)rand()/(float)RAND_MAX;
}

int random_int_in_range(int low, int high)
{
    return (int)(random_percent() * (high - low) + low);
}

float random_float_in_range(float low, float high)
{
    return random_percent() * (high - low) + low;
}
