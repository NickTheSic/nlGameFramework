#ifndef __NL_RANDOM_H__
#define __NL_RANDOM_H__

#ifdef __cplusplus
extern "C" {
#endif


void init_random_number_generator(int seed);
int random_int_in_range(int low, int high);
float random_float_in_range(float low, float high);


#ifdef __cplusplus
}
#endif

#endif//__NL_RANDOM_H__