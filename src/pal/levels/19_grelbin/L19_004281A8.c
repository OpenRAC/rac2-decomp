/* func_PAL_L19_004289C0, the PAL copy of func_L19_00423270: the same C, where 0.016666668f becomes
   0.020000001f and the fade 255 - x over 255 becomes 212 - (x * 5 + 2) / 6 over 212. The scale makes
   the loop too long for loop.c to hoist its constants, so the floats stay literals in the loop and
   the 20 is a local set before it, which lets i * spacing still reduce to a counter. */
#include "include_asm.h"
#include "common.h"

extern char D_L19_001B9A40[];
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);
extern int g_frame_l19_counter[] __attribute__((sda));
extern int math_random_int_below(int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(float *, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_L19_004289C0(char *obj)
{
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float jitter[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int i, color, alpha, spacing;

    if (*(short *)(obj + 0xAA) == 0x11C7) {
        vec_scale_to_length(point, obj + 0xE0, 1.5f);
        FastVecAdd(origin, obj + 0x10, point);
    } else {
        moby_transform_joint_to_world(obj, 0, origin);
    }
    if (!math_random_int_below(4)) {
        vec_random_direction(velocity, D_L19_001B1ECC[0] * 0.020000001f, D_L19_001B1ED0[0] * 0.020000001f);
        {
            int glowAlpha = D_L19_001B1EDC[0];
            part_spawn_hero_relative(origin, velocity, D_L19_001B1EE0[0], glowAlpha, math_random_int_below(255), 0,
                          D_L19_001B1EE8[0]);
        }
        for (i = 2; i >= 0; i--) {
            vec_random_direction(jitter, D_L19_001B1ED4[0] * 0.020000001f, D_L19_001B1ED8[0] * 0.020000001f);
            FastVecAdd(velocity, velocity, jitter);
            {
                int glowAlpha = D_L19_001B1EDC[0];
                part_spawn_hero_relative(origin, velocity, D_L19_001B1EE4[0], glowAlpha, math_random_int_below(255), 0,
                              D_L19_001B1EEC[0]);
            }
        }
    }
    FastVecSub(point, D_L19_001B9A40, origin);
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(step, point, 0.1f);
    FastVecAdd(point, point, origin);
    spacing = 20;
    for (i = 0; i < 4; i++) {
        color = FastTweenColor(D_L19_001B1EF0[0], D_L19_001B1EF4[0],
                              math_fabs(0.5f - IntToFloat(212 - (((g_frame_l19_counter[0] + i * spacing) & 255) * 5 + 2) / 6) * (1.0f / 212.0f)));
        alpha = *(u8 *)g_frame_l19_counter;
        if (i & 2)
            alpha *= 2;
        if (i & 1)
            alpha = 255 - alpha;
        part_spawn_fading(point, color, alpha, D_L19_001B1F00[0], D_L19_001B1EFC[0], 2, 0,
                      (IntToFloat(i) + 3.0f) * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(point, point, step);
    }
}
