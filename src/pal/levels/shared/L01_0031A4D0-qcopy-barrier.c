#include "include_asm.h"
#include "names.h"

typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern int func_PAL_L01_00323068(char *, float *);
extern float coll_probe_ground_height_below(char *, int, float);
extern float math_move_angle_toward_target(float, float, float);
extern void StepAngleTowardTarget(float *, int, float, float);
extern int FastDecTimer(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(char *, char *);
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;
extern GameState_189E20 g_hero_state;

/* Hand-adapted from func_002AE8C0. */
void func_PAL_L01_0031A4D0(char *obj, char *st, char *ctx)
{
    char *pos;
    float v[4];
    float f;

    int r;

    if (*(short *)(st + 0x28) == 0) {
        *(float *)(st + 0x24) = *(float *)(st + 0x24) + math_random_signed_float_range(0.78539824f, 2.6179941f);
        *(short *)(st + 0x2A) = math_random_int_range(*(short *)(st + 0x2C), *(short *)(st + 0x2E));
        *(short *)(st + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(obj + 0xF8), 0, *(float *)(st + 0x24), *(float *)(st + 0x18));
        if (FastDecTimer(st + 0x2A) != 0)
            *(short *)(st + 0x28) = 0;
    }
    pos = obj + 0x10;
    *(V4_002AE8C0 *)v = *(V4_002AE8C0 *)pos;
    f = *(float *)(ctx + 0x28);
    *(float *)(ctx + 0x28) = *(float *)(st + 0x14);
    v[0] = v[0] + math_fast_sin_or_cos_a(*(float *)(obj + 0xF8)) * 2.0f;
    v[1] = v[1] + math_fast_sin_or_cos_b(*(float *)(obj + 0xF8)) * 2.0f;
    *(float *)(ctx + 0x28) = f;
    r = func_PAL_L01_00323068(obj, v);
    *(float *)(obj + 0x18) = coll_probe_ground_height_below(pos, 0, 0.5f);
    f = vec_distance_xy(pos, st);
    if (r != 0 || *(float *)(st + 0x1C) < f) {
        *(float *)(st + 0x24) = mat_fast_helper_a(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = math_random_int_range(25, 75);
        *(short *)(st + 0x28) = 1;
    } else {
        float limit;

        f = vec_distance_xy(pos, g_hero_state.pos);
        limit = *(float *)(st + 0x20);
        if (f < limit) {
            f = f / limit;
            *(float *)(st + 0x24) = math_move_angle_toward_target(*(float *)(st + 0x24),
                    mat_fast_helper_a(*(float *)(obj + 0x10) - g_hero_state.pos[0],
                                  *(float *)(obj + 0x14) - g_hero_state.pos[1]), f);
        }
    }
}
