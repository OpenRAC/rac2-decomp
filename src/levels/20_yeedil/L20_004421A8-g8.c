#include "common.h"

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Vec;

typedef struct {
    char pad[0x80];
    float pos[4];
    char pad2[0x2200];
    char *hero;
    int mode;
} Globals;

extern Globals g_hero_state;
extern char D_L20_001A8F20[] __attribute__((sda));
extern float D_L20_001B2124 SDATA(D_L20_001B2124);

extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_start_effect_from_entry(void *, float);
extern int moby_move_to_target_temp_limits(void *, void *, int, float, float, float);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void coll_sweep_from_object(void *, void *, int, float, float, float, int, int,
                          int);
extern void moby_raise_state_to_eight(void *);
extern void moby_raise_state_to_eight_copy(void *);
extern void path_push_point_away(void *, void *, void *, float);

/* Runs one step of the enemy grab move. It turns toward the hero, keeps the hero held close, throws effects around, and wakes up a nearby turret. */
void yeedil_boss_update_grab(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *basis;
    char *hero;
    char *other;
    Vec pos;
    float angle;
    float rate;

    angle = mat_fast_helper_a(g_hero_state.pos[0] - *(float *)(obj + 0x10),
                          g_hero_state.pos[1] - *(float *)(obj + 0x14));
    if (FastDiffRots(*(float *)(obj + 0xF8), angle) < 1.57079637f) {
        angle = mat_fast_helper_a(g_hero_state.pos[0] - *(float *)(obj + 0x10),
                              g_hero_state.pos[1] - *(float *)(obj + 0x14));
        moby_start_effect_from_entry(obj, angle);
    }
    *(int *)(g_hero_state.hero + 0x98) = 0;
    basis = state + 0xF0;
    moby_move_to_target_temp_limits(obj, D_L20_001A8F20, 0x10, *(float *)(obj + 0xF8), -1.0f, -1.0f);
    hero = g_hero_state.hero;
    *(int *)(hero + 0x98) = *(int *)(*(char **)(hero + 0x24) + 0x10);
    vec_transform_by_object_or_given(obj, basis, basis, 0);
    *(int *)(state + 0xF4) = 0;
    matrix_mul_vec3(basis, basis, obj + 0xC0);
    rate = (*(float *)(state + 0x100) + *(float *)(state + 0x100)) / *(float *)(state + 0x78);
    if (rate < 0.5f) {
        rate = 0.5f;
    }
    *(float *)(state + 0x1804) =
        FastAddRotations(*(float *)(state + 0x1804), D_L20_001B2124 * (rate * 0.000290888245f));
    FastVecAdd(&pos, obj + 0xC0, obj + 0x10);
    coll_sweep_from_object(obj, &pos, 0x10008, 3.0f, (float)*(u8 *)(state + 0x34), 2.0f, 0, 1, 0);
    qcopy(&pos, obj + 0x10);
    pos.f[2] += 5.0f;
    coll_sweep_from_object(obj, &pos, 0x10000, 5.5f, 50.0f, 2.0f, 0, 1, 0);
    other = *(char **)(state + 0xD4);
    if (other) {
        if (*(short *)(other + 0xAA) == MOBY_CLASS_MINITURRET) {
            moby_raise_state_to_eight(other);
        } else if (*(short *)(other + 0xAA) == MOBY_CLASS_MEGATURRET) {
            moby_raise_state_to_eight_copy(other);
        }
    }
    if (g_hero_state.mode == 0x8C) {
        if (vec_distance_xy(g_hero_state.pos, obj + 0x10) <= 4.0f) {
            g_hero_state.pos[2] += 5.0f;
            g_hero_state.pos[2] = coll_probe_ground_height_below(g_hero_state.pos, 0, 0.5f);
            *(short *)((char *)&g_hero_state + 0x1E0) = 5;
            *(short *)((char *)&g_hero_state + 0x1F0) = 5;
        }
    }
    path_push_point_away(*(void **)(state + 0x210), obj + 0x10, obj + 0x10, *(float *)(state + 0x50));
}
