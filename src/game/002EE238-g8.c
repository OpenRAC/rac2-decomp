#include "include_asm.h"
#include "common.h"

typedef float V4_2EE238[4] __attribute__((aligned(16)));

extern float g_follower_pull_speed __attribute__((sda));
extern float g_follower_max_scale __attribute__((sda));
extern float g_follower_height_scale __attribute__((sda));

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
    float height_err, scale, speed;

    if (vars == 0)
        return;
    follower_load_tuning_for_state(owner);
    vel = vars + 0xC0;
    pull = vars + 0x80;
    pos = vars + 0x90;
    vec_clear_128(vel);
    FastVecSub(pull, vars + 0x60, owner + 0x10);
    vec_scale_to_length(temp, pull, g_follower_pull_speed);
    FastVecAdd(vel, temp, vel);
    qcopy(temp, pos);
    height_err = (*(float *)(vars + 0x124) - g_follower_height_scale * 0.5f) / g_follower_height_scale;
    scale = math_fabs(height_err);
    if (scale < g_follower_pull_speed)
        scale = g_follower_pull_speed;
    if (g_follower_max_scale < scale)
        scale = g_follower_max_scale;
    if (0.0f < height_err)
        scale = -scale;
    vec_scale_to_length(temp, temp, scale);
    FastVecAdd(vel, temp, vel);
    speed = FastVecLength(vel);
    scale = g_follower_pull_speed * g_follower_height_scale;
    if (scale < speed)
        vec_scale_to_length(vel, vel, scale);
    qcopy(vars + 0xA0, pos);
    FastVecAdd(pos, vel, pos);
}
