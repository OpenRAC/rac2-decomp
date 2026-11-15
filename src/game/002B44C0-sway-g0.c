/* func_002B44C0 (1,248 bytes, 28 places): the camera sway update. The offset copy uses qcopy_nc
 * although work[2] is read right after it (the generated code still reloads it from memory);
 * allowed by owner ruling, 13 November 2026.
 * Own unit: -O2 -G0 -ffunction-sections -frac2-gcse-hash-111 -frac2-gcse-hash-pseudo-spread -frac2-reorg-reverse-filled-branch
 * (config/cflags.txt; docs/build/compiler-notes.md). Owner standard of 12 November 2026 for
 * the switches.
 */
#include "common.h"

typedef int Vec128_2B44C0 __attribute__((mode(TI)));

typedef struct {
    Vec128_2B44C0 anchor;
    Vec128_2B44C0 offset;
    Vec128_2B44C0 rotation;
    float position[3];
    float velocity[3];
    float spring[3];
    float damping[3];
    float limit[3];
    float scale[3];
    float kick[3];
    float phase[3];
    float speed[3];
    float amplitude[3];
    int unused;
    int timer;
} Sway_2B44C0;

typedef struct {
    char pad0[0x80];
    Vec128_2B44C0 position;
    char pad1[0x33C - 0x90];
    char *target;
    int state;
} Player_2B44C0;

extern Player_2B44C0 g_hero_state;
extern void memset(void *, int, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_transform_by_object_or_given(char *, void *, void *, void *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void gravity_offset_object_position(char *, void *, void *, float);
extern char *moby_get_private_value_2(char *);
extern void mat_combine_and_store(char *, void *, void *, void *);

/* Makes an object sway like a spring: it is pushed toward a target or the player, wobbles and settles, and its position and tilt follow. */
void moby_update_sway(char *self, Sway_2B44C0 *sway, float *target)
{
    float old_position[4];
    float old_rotation[4];
    float push[4];
    float delta[4];
    float angles[4];
    float work[4];
    float matrix[12];
    float moved[4];
    float shift[4];
    float step[4];
    char *body;
    float roll;
    int i;
    int kick_axis;

    qcopy_nc(old_position, self + 0x10);
    qcopy(old_rotation, self + 0xF0);
    memset(push, 0, 16);
    if (target != 0)
        goto target_delta;
    if (g_hero_state.target == self && g_hero_state.state >= 2)
        goto player_delta;
    goto decay;
target_delta:
    FastVecSub(delta, target, self + 0x10);
    goto active;
player_delta:
    FastVecSub(delta, &g_hero_state.position, self + 0x10);
active:
    vec_transform_by_object_or_given(self, delta, delta, 0);
    FastVecSub(delta, delta, &sway->offset);
    push[0] = -delta[1] * sway->scale[0];
    push[1] = delta[0] * sway->scale[1];
    push[2] = -sway->scale[2];
    if (sway->timer == 0) {
        for (kick_axis = 0; kick_axis < 3; kick_axis++)
            sway->velocity[kick_axis] += push[kick_axis] * sway->kick[kick_axis];
        sway->timer = 10;
    }
    goto update;
decay:
    math_fast_float_d(&sway->timer);
update:
    for (i = 0; i < 3; i++) {
        sway->velocity[i] += sway->spring[i] * (push[i] - sway->position[i]);
        sway->velocity[i] -= sway->damping[i] * sway->velocity[i];
        sway->position[i] += sway->velocity[i];
        sway->phase[i] = FastAddRotations(sway->phase[i], sway->speed[i]);
        delta[i] = sway->amplitude[i] * math_fast_sin_or_cos_b(sway->phase[i]);
    }
    *(Vec128_2B44C0 *)work = 0;
    work[0] = sway->position[0] + delta[0];
    work[1] = sway->position[1] + delta[1];
    *(Vec128_2B44C0 *)angles = *(Vec128_2B44C0 *)work;
    if (sway->limit[0] < angles[0])
        angles[0] = sway->limit[0];
    else if (angles[0] < -sway->limit[0])
        angles[0] = -sway->limit[0];
    if (angles[1] > sway->limit[1])
        angles[1] = sway->limit[1];
    else if (angles[1] < -sway->limit[1])
        angles[1] = -sway->limit[1];
    euler_rotation_basis(matrix, angles);
    euler_rotation_basis(self + 0xC0, &sway->rotation);
    multiply_matrix3x3(self + 0xC0, self + 0xC0, matrix);
    qcopy_nc(work, &sway->offset);
    work[2] += delta[2];
    matrix_mul_vec3(moved, work, self + 0xC0);
    FastVecAdd(moved, moved, self + 0x10);
    FastVecSub(shift, &sway->anchor, moved);
    FastVecAdd(self + 0x10, self + 0x10, shift);
    roll = -sway->position[2];
    if (sway->limit[2] < roll)
        roll = sway->limit[2];
    else if (roll < -sway->limit[2])
        roll = -sway->limit[2];
    gravity_offset_object_position(self, self + 0x10, self + 0x10, roll);
    body = moby_get_private_value_2(self);
    if (body != 0) {
        FastVecSub(step, self + 0x10, old_position);
        mat_combine_and_store(body, step, old_rotation, self + 0xF0);
    }
}
