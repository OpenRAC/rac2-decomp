#include "names.h"
/* func_PAL_L03_003E61B0, the PAL copy of func_L03_003E1C88: the same C, where rename func_L01_002E1680 becomes func_PAL_L01_002E2968; rename func_L00_0032A258 becomes func_PAL_L00_0032C328; rename func_002ABBB8 becomes func_PAL_002AC718; expr 0.16666667f becomes 0.20000002f; expr 0.06666667f becomes 0.080000006f; scale func_002A7820(20, 30); lit 0xf4 becomes 0xcb. */

#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern float vec_distance_squared_xy(void *, void *);
extern void moby_set_state(char *, int, int);
extern void euler_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_find_owned_effect_slot(char *, int, int);
extern void math_approach_target_with_direction_mode(void *, void *, int, float, float, float, float);
extern void update_moby_animation_state(char *);
extern int flag_set_first_pending(char *);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *, void *, float);
extern void func_PAL_L01_002E2968(void *, void *, int, int, int, float, float, float);
extern int PlayMobySound(int, int, char *);
extern char *moby_l00_spawn_child(char *, int, int);
extern void func_PAL_L00_0032C328(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void moby_mark_spawned(char *);
extern void vec_local_offset_to_world(char *, void *, float, float, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float,
                          float, float, int, float, int, int, int, int, int);

extern char g_hero_position[];
/* Paired absolute views of the same small-data floats. */
extern float D_L03_001B0AE0_1[] MACRO_ADDR;
extern float D_L03_001B0AE8_1[] MACRO_ADDR;
extern float D_L03_001B0B30_1[] MACRO_ADDR;
extern float D_L03_001B0AE0 __attribute__((sda));
extern float D_L03_001B0AE8 __attribute__((sda));
extern float D_L03_001B0AF0 __attribute__((sda));
extern float D_L03_001B0AF4 __attribute__((sda));
extern float D_L03_001B0AF8 __attribute__((sda));
extern float D_L03_001B0B30 __attribute__((sda));
extern char D_L03_001B0B10_GP[] SDATA(D_L03_001B0B10);
extern char D_L03_001B0B08_GP[] SDATA(D_L03_001B0B08);
extern char D_L03_001B0B00_GP[] SDATA(D_L03_001B0B00);
extern char D_L03_001A8F20[] __attribute__((sda));
extern int D_L03_001B0B40 __attribute__((sda));

void func_PAL_L03_003E61B0(char *obj)
{
    float v[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    float a;
    int n;

    n = *(u8 *)(obj + 0x20);
    switch (n) {
    case 0:
        qcopy(vars, obj + 0x10);
        *(int *)(obj + 0x48) = 0;
        obj[0x42] = 0;
        *(int *)(obj + 0x44) = 0;
        obj[0x43] = 1;
        *(float *)(vars + 0x10) = math_random_angle();
        *(float *)(vars + 0x14) = math_random_angle();
        *(float *)(vars + 0x18) =
            math_random_signed_float_range(D_L03_001B0AE0, D_L03_001B0AE0_1[1]) * 0.0003490659f;
        *(float *)(vars + 0x1C) =
            math_random_signed_float_range(D_L03_001B0AE8, D_L03_001B0AE8_1[1]) * 0.0003490659f;
        *(float *)(vars + 0x3C) = 0.12566373f;
        *(float *)(vars + 0x38) = 0.0025132746f;
        moby_set_state(obj, 1, -1);
        break;

    case 1:
        if (!*(u8 *)(obj + 0x31))
            break;
        *(float *)(vars + 0x10) = FastAddRotations(*(float *)(vars + 0x10), *(float *)(vars + 0x18));
        *(float *)(vars + 0x14) = FastAddRotations(*(float *)(vars + 0x14), *(float *)(vars + 0x1C));
        *(float *)(obj + 0xF0) = D_L03_001B0AF0 * math_fast_sin_or_cos_b(*(float *)(vars + 0x10));
        *(float *)(obj + 0xF4) = D_L03_001B0AF4 * math_fast_sin_or_cos_b(*(float *)(vars + 0x14));
        *(Quad *)angles = 0;
        angles[0] = *(float *)(vars + 0x10);
        angles[2] = *(float *)(vars + 0x14);
        *(Quad *)v = *(Quad *)angles;
        euler_rotation_basis(mat, v);
        FastVecScale(obj + 0x10, mat + 0x10, D_L03_001B0AF8);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        if (!*(int *)(vars + 0x30)) {
            char *p = part_find_owned_effect_slot(obj, 0x4010000, 0);
            if (p) {
                qcopy(vars + 0x20, p + 0x10);
                moby_set_state(obj, 2, -1);
            }
        }
        if (vec_distance_squared_xy(obj + 0x10, g_hero_position) < 200.0f) {
            char *hero = g_hero_position - 0x80;
            a = FastAddRotations(mat_fast_helper_a(*(float *)(hero + 0x80) - *(float *)(obj + 0x10),
                                            *(float *)(hero + 0x84) - *(float *)(obj + 0x14)),
                              1.5707964f);
            math_approach_target_with_direction_mode(obj + 0xF8, vars + 0x34, 0, a, *(float *)(vars + 0x38),
                          *(float *)(vars + 0x38), *(float *)(vars + 0x3C));
            a = mat_fast_helper_a(vec_distance_xy(g_hero_position, obj + 0x10),
                              *(float *)(obj + 0x18) - *(float *)(hero + 0x88)) * 0.63661975f;
            if (a > 1.0f)
                a = 1.0f;
            else if (a < 0.0f)
                a = 0.0f;
            *(float *)(obj + 0x44) = 1.0f - a;
            update_moby_animation_state(obj);
        }
        break;

    case 2:
        if (flag_set_first_pending(obj)) {
            *(unsigned short *)(obj + 0x96) = (((int)(math_random_int_range(20, 30)) * 5 + 2) / 6);
            *(float *)(obj + 0xf0) *= 4.0f;
            *(float *)(obj + 0xF4) *= 4.0f;
            vec_scale_to_length(vars + 0x20, vars + 0x20, 0.20000002f);
        }
        *(Quad *)v = 0;
        v[2] = 0.080000006f;
        if (!math_random_int_below(2))
            func_PAL_L01_002E2968(obj + 0x10, v, 1, 0x40202020, 1, 0.008f, 0.9f, 1.02f);
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), 0.25132746f);
        FastVecAdd(obj + 0x10, obj + 0x10, vars + 0x20);
        {
            int timer = *(unsigned short *)(obj + 0x96);

            n = timer - 1;
            *(unsigned short *)(obj + 0x96) = n;
            if (!timer)
                moby_set_state(obj, 3, -1);
        }
        break;

    case 3: {
        char *p;

        PlayMobySound(0, 0, obj);
        p = moby_l00_spawn_child(obj, 0x113D, *(u8 *)(obj + 0x30));
        if (p) {
            func_PAL_L00_0032C328(p, D_L03_001B0B10_GP, D_L03_001B0B08_GP, D_L03_001B0B00_GP, 65535, 1,
                              D_L03_001B0B40, 6, 65535, 255, 0);
            moby_mark_spawned(p);
        }
        vec_local_offset_to_world(obj, v, D_L03_001B0B30, D_L03_001B0B30_1[1], D_L03_001B0B30_1[2]);
        func_PAL_002AC718(obj, D_L03_001A8F20, v, 0.0f, 0.0f, 10, 5, 15, 0.0f, 0.0f, 9.0f,
                      *(float *)(obj + 0x2C) * 30.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        moby_mark_spawned(obj);
        break;
    }
    }
}
