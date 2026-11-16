#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} L20_0039BB18_V4;
extern float g_glow_trail_drift __attribute__((sda));
extern int math_fast_float_d(int *);
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, u8, u8, int, float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void part_draw_glow_trail(void *);

void func_PAL_L20_0039EA48(void *arg0)
{
    L20_0039BB18_V4 pos;
    L20_0039BB18_V4 vel;
    u32 s0;
    float g;
    float angle;
    float rnd01;
    float rnd;
    float zero_arg;
    u32 old;
    unsigned long long c64;
    int m;
    int r;
    float r2;
    float rr;
    float rr2;

    s0 = *(u32 *)((u32)arg0 + 0x68);
    if (math_fast_float_d((int *)(s0 + 4)) != 0)
        goto pathA;
    old = *(u16 *)((u32)arg0 + 0x96);
    c64 = old++;
    *(u16 *)((u32)arg0 + 0x96) = old;
    if (c64 < 9)
        goto check;
    if (*(u16 *)(*(u32 *)((u32)arg0 + 0xB8) + 0x34) & 1)
        goto pathA;
check:
    if (vec_distance_xy((void *)((u32)arg0 + 0x10),
                      (void *)(*(u32 *)((u32)arg0 + 0xB8) + 0x10)) > 0.1f) {
pathA:
        zero_arg = 0.0f;
        ApproachValue((float *)s0, zero_arg, 0.020000001f);
        if (*(float *)s0 == 0.0f) {
            moby_mark_spawned(arg0);
            goto end;
        }
    } else {
        ApproachValue((float *)s0, 1.0f, 0.020000001f);
    }

    g = g_glow_trail_drift;
    {
        float v = *(float *)(s0 + 0xC) + g * 0.020000001f;
        *(float *)(s0 + 0xC) = v;
        if (v > 1.0f) {
            *(float *)(s0 + 0xC) = v - 1.0f;
        } else if (v < -1.0f) {
            *(float *)(s0 + 0xC) = v + 1.0f;
        } else {
            goto skip;
        }
    }
skip:
    rnd = math_random_float_range(0.1f, 0.3f);
    m = ((s32)(math_random_int_range(30, 60)) * 5 + 2) / 6;
    vel.q = 0;
    r2 = math_random_float_range(0.5f, 2.0f);
    vel.f[2] = -r2 * 0.020000001f;
    pos.q = vel.q;
    rnd01 = math_random_float_range(0.0f, 1.0f);
    angle = math_random_angle();
    vel.f[0] = math_fast_sin_or_cos_a(angle) * rnd01;
    vel.f[1] = math_fast_sin_or_cos_b(angle) * rnd01;
    vel.f[2] = 0.0f;
    rr = math_random_float_range(1.0f, 10.0f);
    vel.f[2] = rr;
    rr2 = math_random_float_range(1.0f, 10.0f);
    if (!(vel.f[2] > rr2)) {
        ;
    } else {
        vel.f[2] = rr2;
    }
    FastVecAdd(&vel, &vel, arg0 + 0x10);
    {
        u8 particle_count = m;
        r = math_random_int_below(255);
        part_spawn_hero_relative(&vel, &pos, 0x60107080, particle_count, r & 0xFF, 0, rnd);
    }
    gfx_add_draw_callback_first(part_draw_glow_trail, arg0);
end:
    return;
}
