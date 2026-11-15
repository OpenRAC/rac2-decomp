#include "include_asm.h"
#include "common.h"

typedef float V4_2EE238[4] __attribute__((aligned(16)));

extern float D_001AC240 __attribute__((sda));
extern float D_001AC244 __attribute__((sda));
extern float D_001AC248 __attribute__((sda));

extern char *moby_get_motion_data(char *);
extern void follower_load_tuning_for_state(char *);
extern void vec_clear_128(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern float FastVecLength(void *);

/* One step of a follower: it is pulled towards its target and kept at its ride
   height, with the speed clamped, then moved. */
/* Moves a follower toward its target and keeps it at a good height, with a speed limit. */
void follower_move_toward_target(char *owner)
{
    char *vars = moby_get_motion_data(owner);
    char *vel;
    char *pull;
    char *pos;
    V4_2EE238 temp;
    float heightErr, scale, speed;

    if (vars == 0)
        return;
    follower_load_tuning_for_state(owner);
    vel = vars + 0xC0;
    pull = vars + 0x80;
    pos = vars + 0x90;
    vec_clear_128(vel);
    FastVecSub(pull, vars + 0x60, owner + 0x10);
    vec_scale_to_length(temp, pull, D_001AC240);
    FastVecAdd(vel, temp, vel);
    qcopy(temp, pos);
    heightErr = (*(float *)(vars + 0x124) - D_001AC248 * 0.5f) / D_001AC248;
    scale = math_fabs(heightErr);
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
