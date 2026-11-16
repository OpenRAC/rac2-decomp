#include "names.h"
/* func_L18_003F6CA8 from L18_002C4000.c: dispatches on the object's byte at +0x42.
 * Its own unit: the velocity snapshot needs -frac2-qcopy -frac2-qcopy-barrier, and the
 * selector switch's jump table is this unit's only .rodata.
 */
#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

extern float moby_get_anim_value(char *);
extern int hero_set_control_motion_and_step(char *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(float *, float *, int, float, float, float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int moby_l01_turn_toward_target(char *, char *);
extern int moby_step_at_own_position_factor(unsigned char *, float);
extern int moby_step_at_own_position(char *);
extern int moby_turn_toward_target_and_step(char *, float *, float);
extern void moby_set_state(unsigned char *, int, int);
extern float func_L00_002EE290(void *);
extern void vec_fast_normalize(void *, void *, void *);
extern Vector128 g_normalize_scratch_vec;

/* Moves an enemy depending on its current move type, such as walking, turning or being knocked back. */
void enemy_update_move_by_type(char *object)
{
    Vector128 local[1];
    char *state = *(char **)(object + 0x68);
    int mode;
    float scale, heading;

    *(int *)(state + 0x138) &= ~2;
    mode = *(unsigned char *)(object + 0x42);
    if (mode == -1) mode = *(unsigned char *)(object + 0x43);
    switch (mode) {
    case 0: case 1: case 2: case 3: case 6: case 7: case 8: case 10:
        if (*(unsigned char *)(object + 0x20) == 16 && *(unsigned char *)(object + 0x42) == 2) {
            float phase = moby_get_anim_value(object);
            if (phase > 4.0f && phase < 22.0f) {
                hero_set_control_motion_and_step(object, state + 0x1a0);
                *(float *)(state + 0x1a8) -= *(float *)(state + 0x12c);
                return;
            }
            if (!(*(float *)(object + 0x48) == -1.0f && phase <= 4.0f)) return;
            moby_step_at_own_position(object);
            return;
        }
        if (*(unsigned char *)(object + 0x20) == 14) {
            float *rotation;
            if (*(unsigned char *)(object + 0xbc) == 0) return;
            FastVecSub(local, state + 0x230, object + 0x10);
            rotation = (float *)(object + 0xf8);
            vec_scale_to_length(local, local, *(float *)(state + 0x274) * 0.016666668f);
            heading = mat_fast_helper_a(*(float *)(state + 0x230) - *(float *)(object + 0x10),
                                    *(float *)(state + 0x234) - *(float *)(object + 0x14));
            math_approach_target_with_direction_mode(rotation, (float *)(state + 0x1b4), 0, heading, *(float *)(state + 0x114),
                          *(float *)(state + 0x118), *(float *)(state + 0x11c));
            hero_set_control_motion_and_step(object, local);
            return;
        }
        if (*(unsigned char *)(object + 0x20) == 9) return;
        if (*(short *)(state + 0x290) != 0) moby_step_at_own_position_factor((unsigned char *)object, *(float *)(state + 0x264));
        else moby_step_at_own_position(object);
        return;
    case 5: {
        float phase = moby_get_anim_value(object);
        if (phase > 10.0f && phase < 17.0f && (*(unsigned int *)(state + 0x194) & 15) == 0 &&
            *(int *)(state + 0x180) == 0 && *(short *)(state + 0x1c2) == 0) {
            FastVecScale(local, object + 0xc0, 10.0f);
            FastVecAdd(local, object + 0x10, local);
            moby_l01_turn_toward_target(object, (char *)local);
            if (!(*(float *)(state + 0x190) <= *(float *)(object + 0x18))) return;
            if (*(float *)(state + 0x1a8) > 0.003333333647f) *(float *)(state + 0x1a8) = 0.003333333647f;
            return;
        }
        if (*(short *)(state + 0x290) != 0) moby_step_at_own_position_factor((unsigned char *)object, *(float *)(state + 0x264));
        else moby_step_at_own_position(object);
        return;
    }
    case 4:
        moby_turn_toward_target_and_step(object, (float *)(state + 0x230), *(float *)(state + 0x24c));
        if (*(float *)(object + 0x18) >= *(float *)(state + 0x190) && *(float *)(state + 0x1a8) > 0.003333333647f)
            *(float *)(state + 0x1a8) = 0.003333333647f;
        if ((unsigned int)(*(unsigned char *)(object + 0x20) - 11) > 1) return;
        if (*(int *)(state + 0x180) < 16) return;
        if (*(float *)(state + 0x1a8) < 0.001f && *(int *)(state + 0x184) == 0)
            moby_set_state((unsigned char *)object, 16, -1);
        return;
    case 9: {
        char *velocity;
        char *position;
        if (*(unsigned char *)(object + 0x20) == 2) return;
        scale = *(float *)(state + 0x100);
        local[0] = *(Vector128 *)(state + 0x1a0);
        if (*(short *)(state + 0x2a6) == 0) {
            *(int *)(state + 0x138) |= 2;
            *(float *)(state + 0x100) = (scale * *(float *)(object + 0x2c)) / *(float *)(state + 0x268);
        } else {
            *(float *)(state + 0x100) = (scale * *(float *)(object + 0x2c)) / *(float *)(state + 0x268);
        }
        velocity = state + 0x1a0;
        hero_set_control_motion_and_step(object, velocity);
        *(float *)(state + 0x100) = scale;
        if (func_L00_002EE290(state + 0x170) > 0.0f && *(int *)(state + 0x184) == 0) {
            (*(short *)(state + 0x294))++;
            position = object + 0x10;
            FastVecAdd(position, position, state + 0x170);
            vec_fast_normalize(velocity, local, &g_normalize_scratch_vec);
            FastVecScale(velocity, velocity, 0.8f);
            FastVecAdd(position, position, velocity);
        }
        *(float *)(state + 0x1a8) -= *(float *)(state + 0x12c);
        return;
    }
    case 13:
        if (*(unsigned char *)(object + 0x20) != 15) return;
        *(float *)(state + 0x1a8) -= *(float *)(state + 0x12c);
        hero_set_control_motion_and_step(object, state + 0x1a0);
        return;
    }
}
