#include "common.h"
extern float coll_probe_ground_height_below(void *, float, int);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern void TransitionTaboraSlot(void *, void *, void *);
extern struct { char pad[0x1830]; char *object; char pad1834[0xA60]; int state; } g_hero_state;
extern char *D_L08_001BFF58;
extern volatile float D_L08_001B1D24[] __attribute__((sda));

/* Aims the Desert Dune Monster's sweeping attack at its target and hurts whatever it hits on the way. */
void dune_monster_sweep_attack(char *actor) {
    float target[4], origin[4], desired[4], matrix[16];
    char hit[48];
    float start[4], end[4];
    char *vars = *(char **)(actor + 0x68);
    float speed = *(float *)(vars + 0x21C) * 20.0f;
    float distance;
    qcopy(origin, vars + 0x120);
    origin[2] = coll_probe_ground_height_below(origin, 6.0f, 0) + 0.6f;
    desired[0] = math_fast_sin_or_cos_a(FastAddRotations(*(float *)(vars + 0x208), *(float *)(vars + 0x1F4))) * 8.0f;
    desired[1] = math_fast_sin_or_cos_b(FastAddRotations(*(float *)(vars + 0x208), *(float *)(vars + 0x1F4))) * 8.0f;
    desired[2] = 0.0f;
    FastVecAdd(desired, desired, actor + 0x10);
    desired[2] = coll_probe_ground_height_below(desired, 0.5f, 0) + 0.6f;
    if (*(s16 *)(vars + 0x1B8)) *(float *)(vars + 0x1CC) += 0.05f;
    else *(float *)(vars + 0x1CC) -= 0.05f;
    if (*(float *)(vars + 0x1CC) > 1.0f) *(float *)(vars + 0x1CC) = 1.0f;
    else if (*(float *)(vars + 0x1CC) < 0.0f) *(float *)(vars + 0x1CC) = 0.0f;
    FastVecScale(desired, desired, 1.0f - *(float *)(vars + 0x1CC));
    FastVecScale(origin, origin, *(float *)(vars + 0x1CC));
    FastVecAdd(target, desired, origin);
    moby_transform_joint_point(actor, 4, matrix);
    vec_scale_to_length(origin, matrix, 0.7f);
    FastVecAdd(matrix + 12, matrix + 12, origin);
    target[2] = *(float *)(vars + 0x148);
    FastVecSub(origin, target, matrix + 12);
    origin[2] = 0.0f;
    vec_scale_to_length(origin, origin, speed);
    FastVecAdd(desired, origin, matrix + 12);
    desired[2] = *(float *)(vars + 0x148);
    FastVecSub(desired, desired, matrix + 12);
    vec_scale_to_length(desired, desired, speed);
    FastVecAdd(desired, desired, matrix + 12);
    distance = vec_distance_xy(vars + 0x120, matrix + 12);
    if (distance < speed) {
        *(char **)(hit + 16) = actor;
        *(int *)(hit + 20) = 1;
        *(float *)(hit + 28) = (float)*(u8 *)(vars + 0x34);
        *(int *)(hit + 32) = 1;
        *(float *)(hit + 0) = math_fast_sin_or_cos_a(*(float *)(actor + 0xF8));
        *(float *)(hit + 4) = math_fast_sin_or_cos_b(*(float *)(actor + 0xF8));
        *(u8 *)(hit + 25) = 1;
        *(u16 *)(hit + 26) = *(u16 *)(actor + 0xAA);
        *(float *)(hit + 12) = 5627.9248046875f;
        *(float *)(hit + 8) = 1.0f;
        *(u8 *)(hit + 24) = 0;
        vec_scale_to_length(start, origin, distance - 1.0f);
        FastVecAdd(start, start, matrix + 12);
        vec_scale_to_length(end, origin, distance + 1.0f);
        FastVecAdd(end, end, matrix + 12);
        if (g_hero_state.state != 0x31)
            end[2] = start[2] = coll_probe_ground_height_below(vars + 0x140, 0.5f, 0) + D_L08_001B1D24[0];
        else
            end[2] = start[2] = coll_probe_ground_height_below(g_hero_state.object + 0x10, 0.5f, 0) + D_L08_001B1D24[0];
        if (g_hero_state.object && D_L08_001BFF58 == g_hero_state.object)
            end[2] = start[2] = *(float *)(D_L08_001BFF58 + 0x18) + D_L08_001B1D24[0];
        if (!CollLine(start, end, 0, actor, hit)) {
            start[2] -= 0.5f;
            end[2] -= 0.5f;
            CollLine(start, end, 0, actor, hit);
        }
    }
    TransitionTaboraSlot(actor, matrix, desired);
}
