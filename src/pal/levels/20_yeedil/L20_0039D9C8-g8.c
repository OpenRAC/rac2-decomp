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

/* Updates the glowing particle effect (moby class 4802). It fades the effect in while its owner is close, spawns drifting sparks every frame, and removes itself once it has faded out. (PAL: 50 Hz timings) */
void UpdateYeedilParticleEmitter_pal(void *moby)
{
    L20_0039BB18_V4 pos;
    L20_0039BB18_V4 vel;
    u32 vars;
    float drift;
    float angle;
    float radius;
    float size;
    float zero_arg;
    u32 timer;
    unsigned long long age;
    int count_scaled;
    int random_alpha;
    float fall_speed;
    float height;
    float alt_height;

    vars = *(u32 *)((u32)moby + 0x68);
    if (math_fast_float_d((int *)(vars + 4)) != 0)
        goto pathA;
    timer = *(u16 *)((u32)moby + 0x96);
    age = timer++;
    *(u16 *)((u32)moby + 0x96) = timer;
    if (age < 9)
        goto check;
    if (*(u16 *)(*(u32 *)((u32)moby + 0xB8) + 0x34) & 1)
        goto pathA;
check:
    if (vec_distance_xy((void *)((u32)moby + 0x10),
                      (void *)(*(u32 *)((u32)moby + 0xB8) + 0x10)) > 0.1f) {
pathA:
        zero_arg = 0.0f;
        ApproachValue((float *)vars, zero_arg, 0.020000001f);
        if (*(float *)vars == 0.0f) {
            moby_mark_spawned(moby);
            goto end;
        }
    } else {
        ApproachValue((float *)vars, 1.0f, 0.020000001f);
    }

    drift = g_glow_trail_drift;
    {
        float v = *(float *)(vars + 0xC) + drift * 0.020000001f;
        *(float *)(vars + 0xC) = v;
        if (v > 1.0f) {
            *(float *)(vars + 0xC) = v - 1.0f;
        } else if (v < -1.0f) {
            *(float *)(vars + 0xC) = v + 1.0f;
        } else {
            goto skip;
        }
    }
skip:
    size = math_random_float_range(0.1f, 0.3f);
    count_scaled = ((s32)(math_random_int_range(30, 60)) * 5 + 2) / 6;
    vel.q = 0;
    fall_speed = math_random_float_range(0.5f, 2.0f);
    vel.f[2] = -fall_speed * 0.020000001f;
    pos.q = vel.q;
    radius = math_random_float_range(0.0f, 1.0f);
    angle = math_random_angle();
    vel.f[0] = math_fast_sin_or_cos_a(angle) * radius;
    vel.f[1] = math_fast_sin_or_cos_b(angle) * radius;
    vel.f[2] = 0.0f;
    height = math_random_float_range(1.0f, 10.0f);
    vel.f[2] = height;
    alt_height = math_random_float_range(1.0f, 10.0f);
    if (!(vel.f[2] > alt_height)) {
        ;
    } else {
        vel.f[2] = alt_height;
    }
    FastVecAdd(&vel, &vel, moby + 0x10);
    {
        u8 particle_count = count_scaled;
        random_alpha = math_random_int_below(255);
        part_spawn_hero_relative(&vel, &pos, 0x60107080, particle_count, random_alpha & 0xFF, 0, size);
    }
    gfx_add_draw_callback_first(part_draw_glow_trail, moby);
end:
    return;
}
