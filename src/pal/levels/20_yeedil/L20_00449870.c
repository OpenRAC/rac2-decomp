#include "names.h"
/* func_PAL_L20_00449870 (1 place), the PAL copy of func_L20_00443DF0 with 50 Hz values: the
   per-frame scale 1/6 becomes 1/5 (0x3E4CCCCE, one ulp above 0.2f, written 0.20000002f), the
   drop -1/30 becomes -1/25, the spread 90/180 becomes 75/150 and the projectile's 180 and 600
   frames become 150 and 500. -O2 -G0 -ffunction-sections -frac2-hazard-labels, as v1.01's. */
#include "common.h"

extern void yeedil_boss_compute_shot_launch_pal(char *, char *, char *, float *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char *part_create_interpolated_emitter(int, int, void *, void *, void *, int, int, int);
extern char g_hero_position[];

/* Clamps the aim angle's magnitude into [pi/6, pi/4], keeping its sign, then
   launches a projectile along the rotated, flattened offset.  Retail's
   constants are 0x3F490FDC and 0x3F060A93, one ulp above the nearest floats
   to pi/4 and pi/6, so they are written 0.78539825f and 0.52359885f. */
char *func_PAL_L20_00449870(char *arg0)
{
    char *state = *(char **)(arg0 + 0x68);
    float ang[4];
    float v[4];
    float w[4];
    float t;
    float f;

    t = 0.78539825f;
    yeedil_boss_compute_shot_launch_pal(arg0, (char *)ang, (char *)v, &t);
    ang[2] = ang[2] + 1.0f;
    if (t < 0.0f) {
        if (t > -0.52359885f)
            t = -0.52359885f;
        else if (t < -0.78539825f)
            t = -0.78539825f;
    } else {
        if (t > 0.78539825f)
            t = 0.78539825f;
        else if (t < 0.52359885f)
            t = 0.52359885f;
    }
    f = FastAddRotations(t, *(float *)(arg0 + 0xF8));
    v[0] = math_fast_sin_or_cos_a(f) * 0.20000002f;
    v[1] = math_fast_sin_or_cos_b(f) * 0.20000002f;
    v[2] = -0.04f;
    if (math_random_int_below(2) != 0) {
        FastVecScale(w, v, 75.0f);
    } else {
        FastVecScale(w, v, math_random_float_range(0.4f, 0.6f) * 150.0f);
    }
    FastVecAdd(w, w, ang);
    FastVecSub(w, g_hero_position, w);
    w[2] = 0.0f;
    vec_scale_to_length(w, w, 0.20000002f);
    return part_create_interpolated_emitter((int)arg0, 0, ang, v, w, 0x96, 0x1F4, *(unsigned char *)(state + 0x36));
}
