#include "include_asm.h"

#include "common.h"
extern int D_L20_001A8F00;
extern int D_L20_001C0418 NOT_SDA;
extern float D_L20_001B2468 __attribute__((sda));
extern int D_L20_001B2460 __attribute__((sda));
extern void moby_mark_spawned(void *object);
extern float FastAddRotations(float, float);
extern void lerp_vector(float *out, char *a, char *b, float k);
extern float ApproachValue(float *p, float v, float w);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void moby_set_state(char *object, int a1, int a2);
extern void FastVecScale(void *dst, void *src, float value);
extern void vec_clear_128(void *target);
extern float math_random_float_range(float lo, float hi);
extern void *part_spawn_gravity_fade(void *, void *, float, float, float, int, int, int, int, int,
                           int);
extern int coll_sweep_from_object(char *, char *, int, int, float, float, float, int, int);
extern void func_PAL_L00_003FB330(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_two_glow_effects(void *);

void func_PAL_L20_00450AD0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float buf20[4] __attribute__((aligned(16)));
    float buf30[4] __attribute__((aligned(16)));
    float buf40[4] __attribute__((aligned(16)));
    float buf50[4] __attribute__((aligned(16)));
    u8 mode;

    if (D_L20_001A8F00 == 2) {
        moby_mark_spawned(arg0);
        return;
    }
    mode = *(u8 *)(arg0 + 0x20);
    switch (mode) {
    case 0: {
        char *base;
        float v = *(float *)(state + 0x28);
        float a;
        float b;

        base = arg0 + 0x10;
        *(float *)(arg0 + 0xF0) =
            FastAddRotations(*(float *)(arg0 + 0xF0), v * 0.7f);
        *(float *)(arg0 + 0xF4) = FastAddRotations(
            *(float *)(arg0 + 0xF4), *(float *)(state + 0x28) * 0.5f);
        *(float *)(arg0 + 0xF8) = FastAddRotations(
            *(float *)(arg0 + 0xF8), *(float *)(state + 0x28));
        lerp_vector(buf30, state, state + 0x10,
                      *(float *)(state + 0x30));
        ApproachValue((float *)(state + 0x30), 1.0f, *(float *)(state + 0x34));
        FastVecAdd(buf20, base, buf30);
        if (coll_test_point(buf20, 0, arg0, D_L20_001B2468) != 0) {
            int id = D_L20_001C0418;

            if (id != 0 && id != *(int *)(arg0 + 0xB8)) {
                moby_set_state(arg0, 1, -1);
                break;
            }
        }
        qcopy(arg0 + 0x10, buf20);
        FastVecScale(buf40, state, -0.5f);
        vec_clear_128(buf50);
        a = math_random_float_range(2.5f, 3.0f) * 210000.0f;
        b = math_random_float_range(0.2f, 0.4f) * 210000.0f;
        part_spawn_gravity_fade(arg0 + 0x10, buf40, a, b, 0.0f, 0xF,
                      D_L20_001B2460, 3, 0x50, 0, 0);
    } break;
    case 1: {
        char *base;
        base = arg0 + 0x10;
        coll_sweep_from_object(arg0, base, 0x10001, 0, 3.0f, *(float *)(state + 0x20),
                      1.0f, 1, 0);
        func_PAL_L00_003FB330(base, 1, 0xA, 0xA, 0xA, 0xA, 0xA, 0, 2.0f, 20.0f, mode,
                      mode, 0, 0);
        moby_mark_spawned(arg0);
        return;
    }
    }
    gfx_add_draw_callback_third(&part_spawn_two_glow_effects, arg0);
}
