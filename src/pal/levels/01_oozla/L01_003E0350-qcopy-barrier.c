#include "include_asm.h"

#include "common.h"
typedef int V4 __attribute__((mode(TI)));
extern float coll_probe_ground_height_below(void *a0, int a1, float f12);
extern int GetCollHitMaterial(void);
extern void vec_add_random_offset(float *v, float f);
extern float func_PAL_L01_003BEB40(void);
extern float math_random_float_range(float a, float b);
extern int math_random_int_below(int a);
extern void *part_spawn_drifting(char *a0, int a1, int a2, float f12, float f13);
extern float FastVecLength(void *a0);
extern f32 D_L01_001AFE18[];

/* Same body as func_L01_003B4480, with this function's own callees. */
void func_PAL_L01_003E05D0(u8 *arg0)
{
    u8 *state = *(u8 **)(arg0 + 0x68);
    float v[4];
    float f;
    int i;

    coll_probe_ground_height_below(arg0 + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *p = arg0 + 0x10;
        u8 *q = state + 0x190;
        i = 0;
        while (i >= 0) {
            *(V4 *)v = *(V4 *)p;
            vec_add_random_offset(v, 0.1f);
            v[2] = func_PAL_L01_003BEB40();
            f = math_random_float_range(0.2f, 2.0f);
            part_spawn_drifting((char *)v, (int)D_L01_001AFE18,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), f, 1.2e+04f);
            i--;
        }
        if (0.040000003f < FastVecLength(q))
            func_PAL_L01_003E0350(arg0, 3, 10, 1);
    }
}
