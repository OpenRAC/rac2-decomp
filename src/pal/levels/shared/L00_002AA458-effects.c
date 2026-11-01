#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
extern float func_002A7878(float, float);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282D30(void *, void *, float);
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
        player = D_00189E20;
        inheritedVelocity = (Vector *)(player + 0x110);
        if (sourceMode == 0) {
            position.f[0] = *(float *)(player + 0x80) + func_002A7878(-0.1f, 0.1f);
            position.f[1] = *(float *)(player + 0x84) + func_002A7878(-0.1f, 0.1f);
            position.f[2] = *(float *)(player + 0x88) + func_002A7878(-0.5f, 0.1f);
        } else if (sourceMode == 1) {
            if (!(index & 1))
                func_0029FCC0(*(char **)(player + 0x2290), 0, (char *)&position);
            else
                func_0029FCC0(*(char **)(player + 0x2290), 14, (char *)&position);
        } else if (sourceMode == 2) {
            if (!(index & 1))
                func_0029FCC0(*(char **)(player + 0x2290), 23, (char *)&position);
            else
                func_0029FCC0(*(char **)(player + 0x2290), 22, (char *)&position);
        }
        qcopy(&velocity, inheritedVelocity);
        if (*(int *)(player + 0x2294) == 0x33) func_00282D30(&velocity, &velocity, 1.15f);
        else func_00282D30(&velocity, &velocity, 0.7f);
        velocity.f[0] += func_002A7878(-0.008f, 0.008f);
        velocity.f[1] += func_002A7878(-0.008f, 0.008f);
        velocity.f[2] += func_002A7878(-0.020000001f, 0.0f);
        if (sparks) {
            unsigned char *matrix = *(unsigned char **)(player + 0x2290) + 0xC0;
            size = func_002A7878(0.7f, 1.1f);
            func_PAL_L00_00337918(&position, matrix, *(float *)(player + 0x170) * size);
        } else {
            size = func_002A7878(4200.0f, 7350.0f);
            func_PAL_002C0428(&position, &velocity, size, -1.0f);
        }
    }
}

extern int func_00282978(short *);
extern float func_00283B98(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern void func_PAL_002BEF58(Vector *, Vector *, int, float);
extern void func_002AF000(float *, float, float, float);
extern unsigned char *func_002BAE50(Vector *, Vector *, unsigned int, unsigned int, int, int, int, int);

/* Timer-relative views and copy lifetimes follow RAC1 emit_hero_timed_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Update two timers that emit falling motes and a burst of colored particles. */
void func_PAL_L00_002AACE8(void) {
    Vector position, velocity;
    unsigned int color;
    int alpha, index, firstLife, secondLife;
    float angle, speed, fade, firstAngle, secondAngle;
    unsigned char *timer = D_00189E20 + 0x51E;
    if (func_00282978((short *)timer)) {
        unsigned char *base;
        qcopy(&position, timer - 0x49E);
        base = timer - 0x51E;
        angle = func_00283B98(*(float *)(base + 0x98), 1.5707964897155762f);
        speed = func_002A78D8(0.004f, 0.014f);
        velocity.f[0] = func_00283180(angle) * speed;
        velocity.f[1] = func_00283198(angle) * speed;
        velocity.f[3] = -0.0032000002f;
        velocity.f[2] = 0.0f;
        func_PAL_002BEF58(&position, &velocity, 0, -1.0f);
        *(short *)(base + 0x51E) = func_002A7820(2, 3);
    }
    if (func_00282978((short *)(timer - 2))) {
        fade = (float)(33 - *(int *)(timer - 0x366)) * 0.030303031f;
        if (fade > 1.0f) fade = 1.0f;
        if (fade < 0.0f) fade = 0.0f;
        alpha = func_00283CF0(fade * 240.0f);
        if (alpha > 160) alpha = 160;
        if (alpha < 32) alpha = 32;
        color = ((unsigned int)alpha << 24) | 0xC0F0U;
        for (index = 56; index >= 0; --index) {
            firstLife = func_00283CF0(func_002A7878(4200.0f, 7350.0f) * 0.001f);
            secondLife = func_00283CF0(func_002A7878(21000.0f, 31500.001953125f) * 0.001f);
            speed = func_002A7878(0.0030000003f, 0.011400001f);
            qcopy(&position, timer - 0x49E);
            firstAngle = func_002A7940();
            secondAngle = func_002A7940();
            func_002AF000(velocity.f, speed, firstAngle, secondAngle);
            func_002BAE50(&position, &velocity, color, 0x70F0, 33, firstLife, secondLife, 1);
        }
        {
            unsigned char *finalBase = D_00189E20;
            *(short *)(finalBase + 0x51C) = func_002A7820(2, 6);
        }
    }
}
