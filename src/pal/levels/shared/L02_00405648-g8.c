#include "include_asm.h"

#include "common.h"
extern float g_puff_random_min __attribute__((sda));
extern float g_puff_random_max;
extern int g_growing_puff_param_a __attribute__((sda));
extern int g_growing_puff_param_b __attribute__((nosda));
extern int g_puff_local_word0 __attribute__((nosda));
extern int g_puff_local_word1 __attribute__((nosda));
extern char g_zero_l02_vector[];
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void func_PAL_002BE880(void *, void *, float, u32, s32, s32);

void func_PAL_L02_00405D00(void *a0)
{
    void *s1 = a0;
    void *s0;
    int local[2];
    float f20;
    float r;
    int t0;

    s0 = *(void **)(s1 + 0x68);
    r = math_random_float_range(g_puff_random_min, g_puff_random_max);
    f20 = r * 210000.0f;
    t0 = ((s32)(math_random_int_range(*(unsigned char *)(s0 + 0x75), *(unsigned char *)(s0 + 0x76))) * 5 + 2) / 6;
    if (*(short *)(s1 + 0xAA) == 0xB5A) {
        local[0] = g_growing_puff_param_a;
        local[1] = g_growing_puff_param_b;
    } else {
        local[0] = g_puff_local_word0;
        local[1] = g_puff_local_word1;
    }
    func_PAL_002BE880(s1 + 0x10, g_zero_l02_vector, f20, g_growing_puff_param_a, g_growing_puff_param_b, t0);
}
