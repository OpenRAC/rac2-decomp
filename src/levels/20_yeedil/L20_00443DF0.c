/* func_L20_00443DF0 (1 place). -O2 -G0 -ffunction-sections -frac2-hazard-labels:
   without -frac2-hazard-labels the branch at +0xA4 targets one label to the
   right, so it cannot stay in L20_0043ECB0.c, whose other functions build
   without the flag. */
#include "common.h"

extern void func_L20_00443B60(char *, char *, char *, float *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_L03_003D09D0(int, int, void *, void *, void *, int, int, int);
extern char D_00189EA0[];

/* Clamps the aim angle's magnitude into [pi/6, pi/4], keeping its sign, then
   launches a projectile along the rotated, flattened offset.  Retail's
   constants are 0x3F490FDC and 0x3F060A93, one ulp above the nearest floats
   to pi/4 and pi/6, so they are written 0.78539825f and 0.52359885f. */
/* Throws a projectile at the hero. The throw angle is kept inside a fixed range and a little randomness is added. */
char *func_L20_00443DF0(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    float launchPos[4];
    float launchVelocity[4];
    float spread[4];
    float aimAngle;
    float heading;

    aimAngle = 0.78539825f;
    ComputeShotLaunch(moby, (char *)launchPos, (char *)launchVelocity, &aimAngle);
    launchPos[2] = launchPos[2] + 1.0f;
    if (aimAngle < 0.0f) {
        if (aimAngle > -0.52359885f)
            aimAngle = -0.52359885f;
        else if (aimAngle < -0.78539825f)
            aimAngle = -0.78539825f;
    } else {
        if (aimAngle > 0.78539825f)
            aimAngle = 0.78539825f;
        else if (aimAngle < 0.52359885f)
            aimAngle = 0.52359885f;
    }
    heading = FastAddRotations(aimAngle, *(float *)(moby + 0xF8));
    launchVelocity[0] = FastSinOrCosA(heading) * 0.16666667f;
    launchVelocity[1] = FastSinOrCosB(heading) * 0.16666667f;
    launchVelocity[2] = -0.033333335f;
    if (RandomIntBelow(2) != 0) {
        FastVecScale(spread, launchVelocity, 90.0f);
    } else {
        FastVecScale(spread, launchVelocity, RandomFloatRange(0.4f, 0.6f) * 180.0f);
    }
    FastVecAdd(spread, spread, launchPos);
    FastVecSub(spread, gHeroPosition, spread);
    spread[2] = 0.0f;
    vec_scale_to_length(spread, spread, 0.16666667f);
    return CreateInterpolatedParticleEmitter((int)moby, 0, launchPos, launchVelocity, spread, 0xB4, 0x258, *(unsigned char *)(state + 0x36));
}
