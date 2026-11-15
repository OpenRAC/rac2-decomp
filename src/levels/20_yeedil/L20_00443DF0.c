#include "names.h"
/* func_L20_00443DF0 (1 place). -O2 -G0 -ffunction-sections -frac2-hazard-labels:
   without -frac2-hazard-labels the branch at +0xA4 targets one label to the
   right, so it cannot stay in L20_0043ECB0.c, whose other functions build
   without the flag. */
#include "common.h"

extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);
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
/* Throws a projectile at the hero. The throw angle is kept inside a fixed range and a little randomness is added. */
char *yeedil_boss_fire_lobbed_projectile(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    float launch_pos[4];
    float launch_velocity[4];
    float spread[4];
    float aim_angle;
    float heading;

    aim_angle = 0.78539825f;
    yeedil_boss_compute_shot_launch(moby, (char *)launch_pos, (char *)launch_velocity, &aim_angle);
    launch_pos[2] = launch_pos[2] + 1.0f;
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
    heading = FastAddRotations(aim_angle, *(float *)(moby + 0xF8));
    launch_velocity[0] = math_fast_sin_or_cos_a(heading) * 0.16666667f;
    launch_velocity[1] = math_fast_sin_or_cos_b(heading) * 0.16666667f;
    launch_velocity[2] = -0.033333335f;
    if (math_random_int_below(2) != 0) {
        FastVecScale(spread, launch_velocity, 90.0f);
    } else {
        FastVecScale(spread, launch_velocity, math_random_float_range(0.4f, 0.6f) * 180.0f);
    }
    FastVecAdd(spread, spread, launch_pos);
    FastVecSub(spread, g_hero_position, spread);
    spread[2] = 0.0f;
    vec_scale_to_length(spread, spread, 0.16666667f);
    return part_create_interpolated_emitter((int)moby, 0, launch_pos, launch_velocity, spread, 0xB4, 0x258, *(unsigned char *)(state + 0x36));
}
