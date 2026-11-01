#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern unsigned char *func_00312D58(Vector *, float);
extern unsigned char *func_002C19D8(Vector *, float *, int, float, float);
extern unsigned char *func_PAL_002C0838(Vector *, Vector *, int, int);

/* Emit ground dust and scattered debris around the resident player's position. */
void func_PAL_L00_002AAAC8(int dust, int debris, int model) {
    Vector velocity;
    Vector position;
    float angle, radius, size;
    int kind, life;
    if (model) {
        unsigned char *origin = D_00189E20 + 0x80;
        velocity.q = *(Quadword *)origin;
        velocity.f[2] = *(float *)(origin + 0x2B0);
        func_00312D58(&velocity, 2.25f);
    }
    if (dust > 0) {
        unsigned char *player = D_00189E20;
        do {
            --dust;
            velocity.f[0] = *(float *)(player + 0x80) + func_002A7878(-0.3f, 0.3f);
            velocity.f[1] = *(float *)(player + 0x84) + func_002A7878(-0.3f, 0.3f);
            velocity.f[2] = *(float *)(player + 0x330);
            size = func_002A7878(0.3f, 0.6f);
            func_002C19D8(&velocity, (float *)(player + 0x330), -1, size, 5250.0f);
        } while (dust);
    }
    if (debris > 0) {
        int remaining = debris;
        unsigned char *player = D_00189E20;
        do {
            --remaining;
            angle = func_002A7940();
            radius = func_002A7878(0.0f, 0.060000002f);
            velocity.f[0] = func_00283180(angle) * radius;
            velocity.f[1] = func_00283198(angle) * radius;
            velocity.f[2] = func_002A7878(0.060000002f, 0.16000001f);
            position.f[0] = *(float *)(player + 0x80) + velocity.f[0] * 8.0f;
            position.f[1] = *(float *)(player + 0x84) + velocity.f[0] * 8.0f;
            position.f[2] = *(float *)(player + 0x330) - func_002A7878(0.0f, 0.2f);
            kind = func_002A77E0(2);
            life = func_002A7820(90, 120);
            func_PAL_002C0838(&position, &velocity, kind, life);
        } while (remaining);
    }
}
