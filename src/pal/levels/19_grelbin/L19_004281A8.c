#include "names.h"
/* func_PAL_L19_004289C0, the PAL copy of func_L19_00423270: the same C, where 0.016666668f becomes
   0.020000001f and the fade 255 - x over 255 becomes 212 - (x * 5 + 2) / 6 over 212. The scale makes
   the loop too long for loop.c to hoist its constants, so the floats stay literals in the loop and
   the 20 is a local set before it, which lets i * spacing still reduce to a counter. */
#include "include_asm.h"
#include "common.h"

extern char g_hero_origin_vec[];
extern float g_group_release_speed_min_a[] SDATA(D_L19_001B1ECC);
extern float g_group_release_speed_max_a[] SDATA(D_L19_001B1ED0);
extern float g_group_release_speed_min_b[] SDATA(D_L19_001B1ED4);
extern float g_group_release_speed_max_b[] SDATA(D_L19_001B1ED8);
extern u8 g_group_release_glow_alpha[] SDATA(D_L19_001B1EDC);
extern int g_group_release_particle_type_a[] SDATA(D_L19_001B1EE0);
extern int g_group_release_particle_type_b[] SDATA(D_L19_001B1EE4);
extern float g_group_release_particle_scale_a[] SDATA(D_L19_001B1EE8);
extern float g_group_release_particle_scale_b[] SDATA(D_L19_001B1EEC);
extern u32 g_group_release_color_start[] SDATA(D_L19_001B1EF0);
extern u32 g_group_release_color_end[] SDATA(D_L19_001B1EF4);
extern int g_group_release_fade_param_a[] SDATA(D_L19_001B1EFC);
extern int g_group_release_fade_param_b[] SDATA(D_L19_001B1F00);
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
        vec_random_direction(velocity, g_group_release_speed_min_a[0] * 0.020000001f, g_group_release_speed_max_a[0] * 0.020000001f);
        {
            int glowAlpha = g_group_release_glow_alpha[0];
            part_spawn_hero_relative(origin, velocity, g_group_release_particle_type_a[0], glowAlpha, math_random_int_below(255), 0,
                          g_group_release_particle_scale_a[0]);
        }
        for (i = 2; i >= 0; i--) {
            vec_random_direction(jitter, g_group_release_speed_min_b[0] * 0.020000001f, g_group_release_speed_max_b[0] * 0.020000001f);
            FastVecAdd(velocity, velocity, jitter);
            {
                int glowAlpha = g_group_release_glow_alpha[0];
                part_spawn_hero_relative(origin, velocity, g_group_release_particle_type_b[0], glowAlpha, math_random_int_below(255), 0,
                              g_group_release_particle_scale_b[0]);
            }
        }
    }
    FastVecSub(point, g_hero_origin_vec, origin);
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(step, point, 0.1f);
    FastVecAdd(point, point, origin);
    spacing = 20;
    for (i = 0; i < 4; i++) {
        color = FastTweenColor(g_group_release_color_start[0], g_group_release_color_end[0],
                              math_fabs(0.5f - IntToFloat(212 - (((g_frame_l19_counter[0] + i * spacing) & 255) * 5 + 2) / 6) * (1.0f / 212.0f)));
        alpha = *(u8 *)g_frame_l19_counter;
        if (i & 2)
            alpha *= 2;
        if (i & 1)
            alpha = 255 - alpha;
        part_spawn_fading(point, color, alpha, g_group_release_fade_param_b[0], g_group_release_fade_param_a[0], 2, 0,
                      (IntToFloat(i) + 3.0f) * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(point, point, step);
    }
}
