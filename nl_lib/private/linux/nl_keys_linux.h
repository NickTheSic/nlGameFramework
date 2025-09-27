#ifndef __NL_KEYS_LINUX_H__
#define __NL_KEYS_LINUX_H__

typedef enum nl_key nl_key;

enum nl_key
{
    key_a = 30,
    key_b,
    key_c,
    key_d,
    key_e,
    key_f,
    key_g,
    key_h,
    key_i,
    key_j,
    key_k,
    key_l,
    key_m,
    key_n,
    key_o,
    key_p,
    key_q,
    key_r,
    key_s,
    nl_key_t, // sys types alread has a key_t so I can't have this
    key_u,
    key_v,
    key_w,
    key_x,
    key_y,
    key_z,

    key_control, // UNKNOWN AT THE MOMENT - Will have to discover it in the future

    NL_KEY_COUNT
};


#endif//__NL_KEYS_LINUX_H__