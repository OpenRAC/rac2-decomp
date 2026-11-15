#include "names.h"
/* func_L02_003D9728: state handler of a Maktar walker: ten-state switch, footstep and
 * impact camera shakes (D_L02_001BA3C0), beam pursuit. */
extern int g_moby_l02_pool;
extern int D_L02_001B03F0 __attribute__((sda));
typedef struct { char pad[0x160]; float amount; int pad2; int time; int phase; } Shake;
extern Shake D_L02_001BA3C0;
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float moby_get_anim_value(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void moby_step_at_own_position_factor(char *, float);
extern float vec_step_toward_target_limited(void *, void *, float);
extern void *arena_get_state_word(void *);
extern float *arena_get_camera_point(void *);
extern int coll_point_inside_record_volume(void *, void *);
extern void moby_l01_turn_toward_target(char *, void *);
extern void *moby_transform_joint_to_world(char *, int, void *);
extern void euler_rotation_basis(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void moby_start_effect_from_entry(char *, float);
extern float math_fast_float_g(float);
extern void turret_spawn_beam_hits(char *);
extern float ApproachValue(float *, float, float);

/* Makes the walker move and shake the camera with its footsteps and impacts, based on its current walking mode. */
void walker_boss_update_movement_shake(char *moby) {
    float jointBefore[4];
    float jointAfter[4];
    float moveDelta[4];
    char *vars = *(char **)(moby + 0x68);
    float *targetPos = (float *)(vars + 0x230);
    float distance = vec_distance_xy(moby + 0x10, targetPos);
    float heading = mat_fast_helper_a(targetPos[0] - *(float *)(moby + 0x10), targetPos[1] - *(float *)(moby + 0x14));
    float animFrame = moby_get_anim_value(moby);
    char *legsMoby = (char *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + g_moby_l02_pool);
    int savedValue = *(int *)(legsMoby + 0x98);
    unsigned int walkMode;
    float pursuitSpeed;
    *(int *)(legsMoby + 0x98) = 0;
    moby_set_controller_speed_limits(moby, 0.0016666667f, 0.05166667f, 0.003490659f, 0.10471977f);
    walkMode = *(unsigned char *)(moby + 0x42);
    switch (walkMode) {
    case 0:
    if (*(unsigned char *)(moby + 0x20) != 4)
        moby_step_at_own_position_factor(moby, *(float *)(moby + 0xF8));
    else
        vec_step_toward_target_limited(moby + 0x10, &D_L02_001B03F0, 0.16666667f);
    break;
    case 1:
    if (coll_point_inside_record_volume(moby + 0x10, arena_get_state_word(*(void **)(moby + 0xB8))))
        moby_l01_turn_toward_target(moby, targetPos);
    else
        moby_l01_turn_toward_target(moby, arena_get_camera_point(*(void **)(moby + 0xB8)));
    if ((animFrame > 0.0f && animFrame < 2.0f) || (animFrame > 15.0f && animFrame < 17.0f) ||
        (animFrame > 30.0f && animFrame < 32.0f) || (animFrame > 45.0f && animFrame < 47.0f)) {
        D_L02_001BA3C0.amount = 0.05f;
        D_L02_001BA3C0.time = 15;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 2:
    if (animFrame > 12.0f && animFrame < 25.0f) {
        moby_transform_joint_to_world(moby, 4, jointBefore);
        moby_step_at_own_position_factor(moby, heading);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        moby_transform_joint_to_world(moby, 4, jointAfter);
        FastVecSub(moveDelta, jointBefore, jointAfter);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
    } else if (animFrame > 42.0f && animFrame < 55.0f) {
        moby_transform_joint_to_world(moby, 8, jointBefore);
        moby_step_at_own_position_factor(moby, heading);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        moby_transform_joint_to_world(moby, 8, jointAfter);
        FastVecSub(moveDelta, jointBefore, jointAfter);
        FastVecAdd(moby + 0x10, moby + 0x10, moveDelta);
    }
    if ((animFrame > 0.0f && animFrame < 2.0f) || (animFrame > 29.0f && animFrame < 31.0f)) {
        D_L02_001BA3C0.amount = 0.1f;
        D_L02_001BA3C0.time = 15;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 3:
        if (animFrame < 23.0f)
            break;
    case 4:
    moby_start_effect_from_entry(moby, mat_fast_helper_a(*(float *)(vars + 0xF0), *(float *)(vars + 0xF4)));
    *(float *)(vars + 0xF8) -= *(float *)(vars + 0x7C);
    FastVecAdd(moby + 0x10, moby + 0x10, vars + 0xF0);
    break;
    case 5:
    if (animFrame > 3.0f && animFrame < 5.0f) {
        D_L02_001BA3C0.amount = 0.4f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 6:
    if (animFrame > 20.0f && animFrame < 22.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    break;
    case 7:
    if ((unsigned int)(*(unsigned char *)(moby + 0x20) - 10) >= 2) {
        *(float *)(moby + 0xF8) += ((*(float *)(vars + 0x20) / (float)*(short *)(vars + 0x24)) * -90.0f + 160.0f) * 0.00029088825f;
        *(float *)(moby + 0xF8) = math_fast_float_g(*(float *)(moby + 0xF8));
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        turret_spawn_beam_hits(moby);
        if (distance > 12.0f && *(unsigned char *)(moby + 0x20) != 10) {
            if (coll_point_inside_record_volume(moby + 0x10, arena_get_state_word(*(void **)(moby + 0xB8)))) {
                pursuitSpeed = ((*(float *)(vars + 0x20) / (float)*(short *)(vars + 0x24)) * -2.2f + 3.0f) * 0.016666668f;
                ApproachValue((float *)(moby + 0x10), targetPos[0], pursuitSpeed);
                ApproachValue((float *)(moby + 0x14), targetPos[1], pursuitSpeed);
            } else {
                ApproachValue((float *)(moby + 0x10), arena_get_camera_point(*(void **)(moby + 0xB8))[0], 0.33333334f);
                ApproachValue((float *)(moby + 0x14), arena_get_camera_point(*(void **)(moby + 0xB8))[1], 0.33333334f);
            }
        }
    }
    break;
    case 8:
    if (animFrame > 30.0f && animFrame < 32.0f) {
        D_L02_001BA3C0.amount = 0.2f;
        D_L02_001BA3C0.time = 25;
        D_L02_001BA3C0.phase = 0;
    }
    case 9:
        break;
    }
    if (*(float *)(moby + 0x18) < arena_get_camera_point(*(void **)(moby + 0xB8))[2])
        *(float *)(moby + 0x18) = arena_get_camera_point(*(void **)(moby + 0xB8))[2];
    *(int *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + g_moby_l02_pool + 0x98) = savedValue;
}
