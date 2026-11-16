#include "common.h"

extern int g_current_map_index MACRO_ADDR;
extern int g_museum_dust_start_a[] SDATA(D_L30_001B1820);
extern int g_museum_dust_end_a[] SDATA(D_L30_001B1824);
extern int g_museum_dust_start_b[] SDATA(D_L30_001B18B8);
extern int g_museum_dust_end_b[] SDATA(D_L30_001B18BC);
extern float g_museum_dust_range_divisor[] SDATA(D_L30_001B1858);
extern float g_museum_dust_rise_divisor[] SDATA(D_L30_001B185C);
extern float g_museum_dust_motion_z_scale[] SDATA(D_L30_001B18AC);
extern float g_museum_dust_offset_z[] SDATA(D_L30_001B18B0);
extern float g_museum_dust_range_a_min[] SDATA(D_L30_001B1828);
extern float g_museum_dust_range_a_max[] SDATA(D_L30_001B182C);
extern float g_museum_dust_range_b_min[] SDATA(D_L30_001B1830);
extern float g_museum_dust_range_b_max[] SDATA(D_L30_001B1834);
extern float g_museum_dust_range_c_min[] SDATA(D_L30_001B1838);
extern float g_museum_dust_range_c_max[] SDATA(D_L30_001B183C);
extern int GetCollHitMaterial(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* rac1-decomp's clobber-free quadword clear: cse forgets the vector addresses at it, so
   the spawn call builds its velocity and acceleration pointers again (addiu from $sp). */
static __inline__ void vzero(float *v) {
    qzero_nc(v);
}

/* func_PAL_L30_004106D0, the PAL copy of func_L30_0040B6B0: the same C, where 1/6 becomes
   0.02 in the speed and rise terms and the three particle timers get the 50 Hz scale. */
/* A museum dust burst in the style of func_L08_00424FF8: the moby's own vector at vars
   joins the velocity, scaled in z. Own unit for -g: its line label gives the pre-div.s
   nop pair. */
void func_PAL_L30_004106D0(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], motion[4];
    int start, end;
    int a, b, c;
    char *particle;
    char *vars = *(char **)(m + 0x68);

    if (g_current_map_index == 21 || g_current_map_index == 30) {
        start = 0x30301010;
        end = g_museum_dust_end_a[0];
    } else {
        start = g_museum_dust_start_a[0];
        end = g_museum_dust_end_a[0];
    }
    if (!GetCollHitMaterial()) {
        start = g_museum_dust_start_b[0];
        end = g_museum_dust_end_b[0];
    }
    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(minRadius, maxRadius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.020000001f) / maxRadius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range / g_museum_dust_range_divisor[0], range));
            }
            qcopy(motion, vars);
            motion[2] *= g_museum_dust_motion_z_scale[0];
            FastVecAdd(velocity, velocity, motion);
            velocity[2] += math_random_float_range(rise / g_museum_dust_rise_divisor[0], rise) * 0.020000001f;
            vzero(accel);
            FastVecAdd(offset, offset, position);
            offset[2] += g_museum_dust_offset_z[0];
            velocity[3] = size;
            accel[3] = endSize;
            a = FloatToInt((math_random_float_range(g_museum_dust_range_a_min[0], g_museum_dust_range_a_max[0]) * 5.0f + 2.0f) * 0.16666667f);
            b = FloatToInt((math_random_float_range(g_museum_dust_range_b_min[0], g_museum_dust_range_b_max[0]) * 5.0f + 2.0f) * 0.16666667f);
            c = FloatToInt((math_random_float_range(g_museum_dust_range_c_min[0], g_museum_dust_range_c_max[0]) * 5.0f + 2.0f) * 0.16666667f);
            particle = part_spawn_trail(offset, velocity, accel, start, end, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
