#ifndef __NL_RANDOM_H__
#define __NL_RANDOM_H__

void init_random_number_generator(int seed);
int random_int_in_range(int low, int high);
float random_float_in_range(float low, float high);

#endif//__NL_RANDOM_H__