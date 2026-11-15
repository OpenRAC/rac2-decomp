#include "common.h"
/* EE argument-bank order: owner/index/point/force in a0..a3, range/height in f12/f13. */
extern int weapon_select_aim_target(void *, int, float, float, void *, int);
extern void FastVecSub(void *, const void *, const void *);
extern float math_random_float_range(float, float), vec_fast_helper_c(const void *, const void *);
extern void vec_add_random_offset(float *, float), vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void *arena_get_center_point(void *);
extern unsigned char g_hero_position[] NOT_SDA;
extern float D_L11_001B0590[] SDATA(D_L11_001B0590);
extern float D_L11_001B0558[] SDATA(D_L11_001B0558);

/* Picks a new beam target point near the given point and pulls it toward the arena centre. Returns 1 when the point was already close enough. */
int joba_beam_pick_target_point(char *object, float *from, float *to)
{
    char *state = *(char **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float radial[4] __attribute__((aligned(16)));
    float radius, factor, height;
    int result;
    *(int *)(state + 0x258) = weapon_select_aim_target(object, *(int *)(state + 0x25c), 200.0f, 200.0f, from, 0);
    if (*(int *)(state + 0x258) == 1) qcopy(to, state + 0x80);
    else qcopy(to, g_hero_position);
    factor = 0.2f;
    /* The subtraction writes all 16 bytes, preserving the initialized input W. */
    FastVecSub(delta, to, from);
    result = 0;
    radius = D_L11_001B0590[0] + math_random_float_range(-D_L11_001B0590[1], D_L11_001B0590[1]);
    if (radius * radius < vec_fast_helper_c(from, to)) {
        vec_add_random_offset(delta, D_L11_001B0590[2]);
        vec_scale_to_length(delta, delta, radius);
        FastVecAdd(to, from, delta);
    } else {
        result = 1;
        factor = 0.5f;
    }
    height = to[2];
    FastVecSub(radial, to, arena_get_center_point(*(void **)(object + 0xb8)));
    radial[2] = 0.0f;
    vec_scale_to_length(radial, radial, D_L11_001B0558[0] - factor);
    FastVecAdd(to, arena_get_center_point(*(void **)(object + 0xb8)), radial);
    to[2] = height;
    return result;
}
