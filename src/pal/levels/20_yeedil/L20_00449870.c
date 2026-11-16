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
char *yeedil_boss_fire_lobbed_projectile_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    float pos[4];
    float vel[4];
    float target_dir[4];
    float aim_angle;
    float angle;

    aim_angle = 0.78539825f;
    yeedil_boss_compute_shot_launch_pal(moby, (char *)pos, (char *)vel, &aim_angle);
    pos[2] = pos[2] + 1.0f;
    if (aim_angle < 0.0f) {
        if (aim_angle > -0.52359885f)
            aim_angle = -0.52359885f;
        else if (aim_angle < -0.78539825f)
            aim_angle = -0.78539825f;
    } else {
        if (aim_angle > 0.78539825f)
            aim_angle = 0.78539825f;
        else if (aim_angle < 0.52359885f)
            aim_angle = 0.52359885f;
    }
    angle = FastAddRotations(aim_angle, *(float *)(moby + 0xF8));
    vel[0] = math_fast_sin_or_cos_a(angle) * 0.20000002f;
    vel[1] = math_fast_sin_or_cos_b(angle) * 0.20000002f;
    vel[2] = -0.04f;
    if (math_random_int_below(2) != 0) {
        FastVecScale(target_dir, vel, 75.0f);
    } else {
        FastVecScale(target_dir, vel, math_random_float_range(0.4f, 0.6f) * 150.0f);
    }
    FastVecAdd(target_dir, target_dir, pos);
    FastVecSub(target_dir, g_hero_position, target_dir);
    target_dir[2] = 0.0f;
    vec_scale_to_length(target_dir, target_dir, 0.20000002f);
    return part_create_interpolated_emitter((int)moby, 0, pos, vel, target_dir, 0x96, 0x1F4, *(unsigned char *)(state + 0x36));
}
