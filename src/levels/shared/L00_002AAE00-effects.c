#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
extern int func_00282978(short *);
extern float func_00283B98(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern void func_002BE278(Vector *, Vector *, int, float);
extern void func_002AF000(float *, float, float, float);
extern unsigned char *func_002BAE50(Vector *, Vector *, unsigned int, unsigned int, int, int, int, int);

/* Timer-relative views and copy lifetimes follow RAC1 emit_hero_timed_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Update two timers that emit falling motes and a burst of colored particles. */
void func_L00_002AAE00(void) {
    Vector position, velocity;
    unsigned int color;
    int alpha, index, firstLife, secondLife;
    float angle, speed, fade, firstAngle, secondAngle;
    unsigned char *timer = D_00189E20 + 0x51E;
    if (FastDecTimer((short *)timer)) {
        unsigned char *base;
        qcopy(&position, timer - 0x49E);
        base = timer - 0x51E;
        angle = FastAddRotations(*(float *)(base + 0x98), 1.5707964897155762f);
        speed = func_002A78D8(0.0033333336468786f, 0.011666666716337204f);
        velocity.f[0] = func_00283180(angle) * speed;
        velocity.f[1] = func_00283198(angle) * speed;
        velocity.f[3] = -0.002222222276031971f;
        velocity.f[2] = 0.0f;
        func_002BE278(&position, &velocity, 0, -1.0f);
        *(short *)(base + 0x51E) = func_002A7820(2, 3);
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
            firstLife = FloatToInt(func_002A7878(4200.0f, 7350.0f) * 0.001f);
            secondLife = FloatToInt(func_002A7878(21000.0f, 31500.001953125f) * 0.001f);
            speed = func_002A7878(0.002500000176951289f, 0.00950000062584877f);
            qcopy(&position, timer - 0x49E);
            firstAngle = func_002A7940();
            secondAngle = func_002A7940();
            func_002AF000(velocity.f, speed, firstAngle, secondAngle);
            func_002BAE50(&position, &velocity, color, 0x70F0, 40, firstLife, secondLife, 1);
        }
        {
            unsigned char *finalBase = D_00189E20;
            *(short *)(finalBase + 0x51C) = func_002A7820(3, 7);
        }
    }
}
