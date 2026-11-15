/* func_002BC508: a drifting particle.  It moves by its velocity, slows down, rises,
 * grows between one of two tuning ranges as its timer runs, fades over its last 15
 * frames and dies when it leaves the 2..1021 box or its timer ends.
 *
 * The tuning floats are small data reached through $gp, hence the -G8 unit; -g keeps
 * the two nops in front of each div.s.  The two size ranges are two LERP statements:
 * cross-jumping merges their common tail, leaving only the loads of the range in the
 * two arms, and the fraction stays in $f12 for the colour call. */
#include "common.h"

extern void func_00282CC0(char *out, char *a, char *b);
extern float func_00282DF0(char *v);
extern void func_002AA548(char *out, float *res, float a, float b, float c, float d);
extern void func_00282F20(char *out, char *v, float scale);
extern float func_00283CE0(int n);
extern int func_00283D38(int from, int to, float t);
extern int func_00282978(void *timer);
extern void func_002B9180(char *particle);
extern float D_001AA348 __attribute__((sda));
extern float D_001AA34C __attribute__((sda));
extern float D_001AA33C __attribute__((sda));
extern float D_001AA338 __attribute__((sda));
extern float D_001AA31C __attribute__((sda));
extern float D_001AA318 __attribute__((sda));

#define LERP(lo, hi, t) (((hi) - (lo)) * (t) + (lo))

void func_002BC508(char *particle)
{
    char *motion = particle + 0x20;
    float speed, lifeLeft, maxLife, lifeFraction;

    particle[8] = (unsigned char)particle[8] + (unsigned char)motion[0x1E];
    FastVecAdd(particle + 0x10, particle + 0x10, motion);
    speed = -FastVecLength(motion);
    StepValueTowardTarget(particle + 0x30, &speed, 0.0f, 0.0f, D_001AA348 * 0.00027777778f, speed);
    vec_scale_to_length(motion, motion, -speed);
    *(float *)(particle + 0x18) += D_001AA34C * 0.016666667f;
    lifeLeft = IntToFloat(*(short *)(particle + 0xA));
    maxLife = IntToFloat((unsigned char)motion[0x1D]);
    lifeFraction = lifeLeft / maxLife;
    if (motion[0x1F] & 1)
        *(float *)(particle + 0xC) = LERP(D_001AA33C, D_001AA338, lifeFraction) * 210000.0f;
    else
        *(float *)(particle + 0xC) = LERP(D_001AA31C, D_001AA318, lifeFraction) * 210000.0f;
    *(int *)(particle + 4) = FastTweenColor(*(int *)(motion + 0x18), *(int *)(motion + 0x14), lifeFraction);
    if (*(short *)(particle + 0xA) < 15) {
        lifeLeft = IntToFloat(*(short *)(particle + 0xA));
        maxLife = IntToFloat(10);
        *(int *)(particle + 4) = FastTweenColor(*(int *)(particle + 4) & 0xFFFFFF, *(int *)(particle + 4), lifeLeft / maxLife);
    }
    if (*(float *)(particle + 0x10) < 2.0f || *(float *)(particle + 0x10) > 1021.0f ||
        *(float *)(particle + 0x14) < 2.0f || *(float *)(particle + 0x14) > 1021.0f ||
        *(float *)(particle + 0x18) < 2.0f || *(float *)(particle + 0x18) > 1021.0f ||
        FastDecTimer(particle + 0xA)) {
        KillParticle(particle);
        return;
    }
    if (*(float *)(motion + 0x10) < 0.01f)
        --*(short *)(particle + 0xA);
}
