#include "common.h"
typedef int EffectQuadword __attribute__((mode(TI)));
extern void cam_compute_view_direction(char *, char *, int);
extern void vec_transform_or_copy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern int math_random_int_below(int);
extern void *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void ref_L00_003FC228_00(void (*)(void *), void *);
extern char g_default_vector[] MACRO_ADDR;
extern unsigned char *g_effect_param_pointer_b;
extern void spark_trail_draw_ribbon(char *);
extern void large_spark_trail_draw_ribbon(char *);

/* Advance the emitter, spawn its paired particles, and discard out-of-bounds owners. */

void spark_trail_update(char *object) {
    float before[4] __attribute__((aligned(16)));
    float scratch[4] __attribute__((aligned(16)));
    float after[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    unsigned char *particle;
    int phase;
    qcopy(before, position);
    cam_compute_view_direction(position, (char *)scratch, 1);
    qcopy(after, position);
    vec_transform_or_copy(position, position);
    vec_transform_or_copy(state + 0x50, state + 0x50);
    if (*(unsigned char *)(object + 0x20) == 0) {
        FastVecAdd(state + 0x50, state + 0x50, state + 0x20);
        if (math_fast_float_d((int *)(state + 0x38))) {
            moby_mark_spawned(object);
            return;
        }
        phase = math_random_int_below(255);
        particle = part_spawn_gravity_fade(position, g_default_vector, 2, 0x00202080,
                               phase, 64, 16, 420000.0f, 420000.0f, 0.0f, 0);
        if (particle != 0) particle[2] = *g_effect_param_pointer_b;
        particle = part_spawn_gravity_fade(position, g_default_vector, 2, 0x00202080,
                               (phase + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 0);
        if (particle != 0) particle[2] = *g_effect_param_pointer_b;
        ref_L00_003FC228_00((void (*)(void *))spark_trail_draw_ribbon, object);
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        moby_mark_spawned(object);
}
