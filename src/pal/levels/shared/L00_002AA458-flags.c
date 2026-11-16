#include "include_asm.h"
#include "names.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char g_hero_state[];
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern unsigned char *moby_spawn_scaled_effect(Vector *, float);
extern unsigned char *part_spawn_drifting(Vector *, float *, int, float, float);
extern unsigned char *func_PAL_002C0838(Vector *, Vector *, int, int);

/* Emit ground dust and scattered debris around the resident player's position. */
void part_emit_hero_dust_and_debris_pal(int dust, int debris, int model) {
    Vector velocity;
    Vector position;
    float angle, radius, size;
    int kind, life;
    if (model) {
        unsigned char *origin = g_hero_state + 0x80;
        velocity.q = *(Quadword *)origin;
        velocity.f[2] = *(float *)(origin + 0x2B0);
        moby_spawn_scaled_effect(&velocity, 2.25f);
    }
    if (dust > 0) {
        unsigned char *player = g_hero_state;
        do {
            --dust;
            velocity.f[0] = *(float *)(player + 0x80) + math_random_float_range(-0.3f, 0.3f);
            velocity.f[1] = *(float *)(player + 0x84) + math_random_float_range(-0.3f, 0.3f);
            velocity.f[2] = *(float *)(player + 0x330);
            size = math_random_float_range(0.3f, 0.6f);
            part_spawn_drifting(&velocity, (float *)(player + 0x330), -1, size, 5250.0f);
        } while (dust);
    }
    if (debris > 0) {
        int remaining = debris;
        unsigned char *player = g_hero_state;
        do {
            --remaining;
            angle = math_random_angle();
            radius = math_random_float_range(0.0f, 0.060000002f);
            velocity.f[0] = math_fast_sin_or_cos_a(angle) * radius;
            velocity.f[1] = math_fast_sin_or_cos_b(angle) * radius;
            velocity.f[2] = math_random_float_range(0.060000002f, 0.16000001f);
            position.f[0] = *(float *)(player + 0x80) + velocity.f[0] * 8.0f;
            position.f[1] = *(float *)(player + 0x84) + velocity.f[0] * 8.0f;
            position.f[2] = *(float *)(player + 0x330) - math_random_float_range(0.0f, 0.2f);
            kind = math_random_int_below(2);
            life = math_random_int_range(90, 120);
            func_PAL_002C0838(&position, &velocity, kind, life);
        } while (remaining);
    }
}
