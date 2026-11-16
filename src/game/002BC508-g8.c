#include "names.h"
/* func_002BC508: a drifting particle.  It moves by its velocity, slows down, rises,
 * grows between one of two tuning ranges as its timer runs, fades over its last 15
 * frames and dies when it leaves the 2..1021 box or its timer ends.
 *
 * The tuning floats are small data reached through $gp, hence the -G8 unit; -g keeps
 * the two nops in front of each div.s.  The two size ranges are two LERP statements:
 * cross-jumping merges their common tail, leaving only the loads of the range in the
 * two arms, and the fraction stays in $f12 for the colour call. */
#include "common.h"

extern void FastVecAdd(char *out, char *a, char *b);
extern float FastVecLength(char *v);
extern float math_step_value_toward_target(char *out, float *res, float a, float b, float c, float d);
extern void vec_scale_to_length(char *out, char *v, float scale);
extern float IntToFloat(int n);
extern int FastTweenColor(int from, int to, float t);
extern int FastDecTimer(void *timer);
extern void part_kill(char *particle);
extern float g_drift_decel_param __attribute__((sda));
extern float g_drift_rise_param __attribute__((sda));
extern float g_drift_scale_start_b __attribute__((sda));
extern float g_drift_scale_end_b __attribute__((sda));
extern float g_drift_scale_start_a __attribute__((sda));
extern float g_drift_scale_end_a __attribute__((sda));

#define LERP(lo, hi, t) (((hi) - (lo)) * (t) + (lo))

void part_update_drifting(char *particle)
{
    char *motion = particle + 0x20;
    float speed, life_left, max_life, life_fraction;

    particle[8] = (unsigned char)particle[8] + (unsigned char)motion[0x1E];
    FastVecAdd(particle + 0x10, particle + 0x10, motion);
    speed = -FastVecLength(motion);
    math_step_value_toward_target(particle + 0x30, &speed, 0.0f, 0.0f, g_drift_decel_param * 0.00027777778f, speed);
    vec_scale_to_length(motion, motion, -speed);
    *(float *)(particle + 0x18) += g_drift_rise_param * 0.016666667f;
    life_left = IntToFloat(*(short *)(particle + 0xA));
    max_life = IntToFloat((unsigned char)motion[0x1D]);
    life_fraction = life_left / max_life;
    if (motion[0x1F] & 1)
        *(float *)(particle + 0xC) = LERP(g_drift_scale_start_b, g_drift_scale_end_b, life_fraction) * 210000.0f;
    else
        *(float *)(particle + 0xC) = LERP(g_drift_scale_start_a, g_drift_scale_end_a, life_fraction) * 210000.0f;
    *(int *)(particle + 4) = FastTweenColor(*(int *)(motion + 0x18), *(int *)(motion + 0x14), life_fraction);
    if (*(short *)(particle + 0xA) < 15) {
        life_left = IntToFloat(*(short *)(particle + 0xA));
        max_life = IntToFloat(10);
        *(int *)(particle + 4) = FastTweenColor(*(int *)(particle + 4) & 0xFFFFFF, *(int *)(particle + 4), life_left / max_life);
    }
    if (*(float *)(particle + 0x10) < 2.0f || *(float *)(particle + 0x10) > 1021.0f ||
        *(float *)(particle + 0x14) < 2.0f || *(float *)(particle + 0x14) > 1021.0f ||
        *(float *)(particle + 0x18) < 2.0f || *(float *)(particle + 0x18) > 1021.0f ||
        FastDecTimer(particle + 0xA)) {
        part_kill(particle);
        return;
    }
    if (*(float *)(motion + 0x10) < 0.01f)
        --*(short *)(particle + 0xA);
}
