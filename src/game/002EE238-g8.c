#include "include_asm.h"
#include "common.h"

typedef float V4_2EE238[4] __attribute__((aligned(16)));

extern float D_001AC240 __attribute__((sda));
extern float D_001AC244 __attribute__((sda));
extern float D_001AC248 __attribute__((sda));

extern char *func_002ED688(char *);
extern void func_002EE3B0(char *);
extern void func_00282C88(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_00282DF0(void *);

/* One step of a follower: it is pulled towards its target and kept at its ride
   height, with the speed clamped, then moved. */
/* Moves a follower toward its target and keeps it at a good height, with a speed limit. */
void func_002EE238(char *owner)
{
    char *vars = GetMobyMotionData(owner);
    char *vel;
    char *pull;
    char *pos;
    V4_2EE238 temp;
    float heightErr, scale, speed;

    if (vars == 0)
        return;
    LoadFollowerTuningForState(owner);
    vel = vars + 0xC0;
    pull = vars + 0x80;
    pos = vars + 0x90;
    ClearVector128(vel);
    FastVecSub(pull, vars + 0x60, owner + 0x10);
    vec_scale_to_length(temp, pull, D_001AC240);
    FastVecAdd(vel, temp, vel);
    qcopy(temp, pos);
    heightErr = (*(float *)(vars + 0x124) - D_001AC248 * 0.5f) / D_001AC248;
    scale = FloatAbs(heightErr);
    if (scale < D_001AC240)
        scale = D_001AC240;
    if (D_001AC244 < scale)
        scale = D_001AC244;
    if (0.0f < heightErr)
        scale = -scale;
    vec_scale_to_length(temp, temp, scale);
    FastVecAdd(vel, temp, vel);
    speed = FastVecLength(vel);
    scale = D_001AC240 * D_001AC248;
    if (scale < speed)
        vec_scale_to_length(vel, vel, scale);
    qcopy(vars + 0xA0, pos);
    FastVecAdd(pos, vel, pos);
}
