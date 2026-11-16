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
extern void part_spawn_water_splash_effects_pal(void *a0, int a1, int a2, int a3);
extern f32 g_water_l01_height[];

void swamp_beast_spawn_bubbles_pal(u8 *arg0)
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
        u8 *q = state + 0xE0;
        i = 0;
        while (i >= 0) {
            *(V4 *)v = *(V4 *)p;
            vec_add_random_offset(v, 0.15f);
            v[2] = func_PAL_L01_003BEB40();
            f = math_random_float_range(0.3f, 2.5f);
            part_spawn_drifting((char *)v, (int)g_water_l01_height,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), f, 13200.001f);
            i--;
        }
        f = 0.040000003f;
        if (f < FastVecLength(q) || f < FastVecLength(state + 0x2F0))
            part_spawn_water_splash_effects_pal(arg0, 3, 10, 1);
    }
}
