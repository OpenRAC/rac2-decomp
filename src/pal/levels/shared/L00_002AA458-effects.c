#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char g_hero_state[];
extern float math_random_float_range(float, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecScale(void *, void *, float);
extern void func_PAL_L00_00337918(Vector *, void *, float);
extern unsigned char *func_PAL_002C0428(Vector *, Vector *, float, float);

/* Joint branches and velocity copy follow RAC1 emit_hero_randomized_motion_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Emit particles either around the player or alternately from selected joints. */
void func_PAL_L00_002AA820(int count, int sourceMode, int sparks) {
    Vector position;
    Vector velocity;
    unsigned char *player;
    Vector *inheritedVelocity;
    int index;
    float size;
    for (index = 0; index < count; ++index) {
        player = g_hero_state;
        inheritedVelocity = (Vector *)(player + 0x110);
        if (sourceMode == 0) {
            position.f[0] = *(float *)(player + 0x80) + math_random_float_range(-0.1f, 0.1f);
            position.f[1] = *(float *)(player + 0x84) + math_random_float_range(-0.1f, 0.1f);
            position.f[2] = *(float *)(player + 0x88) + math_random_float_range(-0.5f, 0.1f);
        } else if (sourceMode == 1) {
            if (!(index & 1))
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 0, (char *)&position);
            else
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 14, (char *)&position);
        } else if (sourceMode == 2) {
            if (!(index & 1))
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 23, (char *)&position);
            else
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 22, (char *)&position);
        }
        qcopy(&velocity, inheritedVelocity);
        if (*(int *)(player + 0x2294) == 0x33) FastVecScale(&velocity, &velocity, 1.15f);
        else FastVecScale(&velocity, &velocity, 0.7f);
        velocity.f[0] += math_random_float_range(-0.008f, 0.008f);
        velocity.f[1] += math_random_float_range(-0.008f, 0.008f);
        velocity.f[2] += math_random_float_range(-0.020000001f, 0.0f);
        if (sparks) {
            unsigned char *matrix = *(unsigned char **)(player + 0x2290) + 0xC0;
            size = math_random_float_range(0.7f, 1.1f);
            func_PAL_L00_00337918(&position, matrix, *(float *)(player + 0x170) * size);
        } else {
            size = math_random_float_range(4200.0f, 7350.0f);
            func_PAL_002C0428(&position, &velocity, size, -1.0f);
        }
    }
}

extern int FastDecTimer(short *);
extern float FastAddRotations(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern void func_PAL_002BEF58(Vector *, Vector *, int, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern unsigned char *part_spawn_scaling(Vector *, Vector *, unsigned int, unsigned int, int, int, int, int);

/* Timer-relative views and copy lifetimes follow RAC1 emit_hero_timed_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Update two timers that emit falling motes and a burst of colored particles. */
void func_PAL_L00_002AACE8(void) {
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
        speed = math_random_signed_float_range(0.004f, 0.014f);
        velocity.f[0] = math_fast_sin_or_cos_a(angle) * speed;
        velocity.f[1] = math_fast_sin_or_cos_b(angle) * speed;
        velocity.f[3] = -0.0032000002f;
        velocity.f[2] = 0.0f;
        func_PAL_002BEF58(&position, &velocity, 0, -1.0f);
        *(short *)(base + 0x51E) = math_random_int_range(2, 3);
    }
    if (FastDecTimer((short *)(timer - 2))) {
        fade = (float)(33 - *(int *)(timer - 0x366)) * 0.030303031f;
        if (fade > 1.0f) fade = 1.0f;
        if (fade < 0.0f) fade = 0.0f;
        alpha = FloatToInt(fade * 240.0f);
        if (alpha > 160) alpha = 160;
        if (alpha < 32) alpha = 32;
        color = ((unsigned int)alpha << 24) | 0xC0F0U;
        for (index = 56; index >= 0; --index) {
            firstLife = FloatToInt(math_random_float_range(4200.0f, 7350.0f) * 0.001f);
            secondLife = FloatToInt(math_random_float_range(21000.0f, 31500.001953125f) * 0.001f);
            speed = math_random_float_range(0.0030000003f, 0.011400001f);
            qcopy(&position, timer - 0x49E);
            firstAngle = math_random_angle();
            secondAngle = math_random_angle();
            vec_build_spherical_offset(velocity.f, speed, firstAngle, secondAngle);
            part_spawn_scaling(&position, &velocity, color, 0x70F0, 33, firstLife, secondLife, 1);
        }
        {
            unsigned char *finalBase = g_hero_state;
            *(short *)(finalBase + 0x51C) = math_random_int_range(2, 6);
        }
    }
}
