#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char g_hero_state[];
extern int FastDecTimer(short *);
extern float FastAddRotations(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern void part_spawn_white_flash(Vector *, Vector *, int, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern unsigned char *part_spawn_scaling(Vector *, Vector *, unsigned int, unsigned int, int, int, int, int);

/* Timer-relative views and copy lifetimes follow RAC1 emit_hero_timed_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Update two timers that emit falling motes and a burst of colored particles. */
void EmitHeroTimedEffects(void) {
    Vector position, velocity;
    unsigned int color;
    int alpha, index, firstLife, secondLife;
    float angle, speed, fade, firstAngle, secondAngle;
    unsigned char *timer = g_hero_state + 0x51E;
    if (FastDecTimer((short *)timer)) {
        unsigned char *base;
        qcopy(&position, timer - 0x49E);
        base = timer - 0x51E;
        angle = FastAddRotations(*(float *)(base + 0x98), 1.5707964897155762f);
        speed = math_random_signed_float_range(0.0033333336468786f, 0.011666666716337204f);
        velocity.f[0] = math_fast_sin_or_cos_a(angle) * speed;
        velocity.f[1] = math_fast_sin_or_cos_b(angle) * speed;
        velocity.f[3] = -0.002222222276031971f;
        velocity.f[2] = 0.0f;
        part_spawn_white_flash(&position, &velocity, 0, -1.0f);
        *(short *)(base + 0x51E) = math_random_int_range(2, 3);
    }
    if (FastDecTimer((short *)(timer - 2))) {
        fade = (float)(40 - *(int *)(timer - 0x366)) * 0.025f;
        if (fade > 1.0f) fade = 1.0f;
        if (fade < 0.0f) fade = 0.0f;
        alpha = FloatToInt(fade * 240.0f);
        if (alpha > 160) alpha = 160;
        if (alpha < 32) alpha = 32;
        color = ((unsigned int)alpha << 24) | 0xC0F0U;
        for (index = 56; index >= 0; --index) {
            firstLife = FloatToInt(math_random_float_range(4200.0f, 7350.0f) * 0.001f);
            secondLife = FloatToInt(math_random_float_range(21000.0f, 31500.001953125f) * 0.001f);
            speed = math_random_float_range(0.002500000176951289f, 0.00950000062584877f);
            qcopy(&position, timer - 0x49E);
            firstAngle = math_random_angle();
            secondAngle = math_random_angle();
            vec_build_spherical_offset(velocity.f, speed, firstAngle, secondAngle);
            part_spawn_scaling(&position, &velocity, color, 0x70F0, 40, firstLife, secondLife, 1);
        }
        {
            unsigned char *finalBase = g_hero_state;
            *(short *)(finalBase + 0x51C) = math_random_int_range(3, 7);
        }
    }
}
