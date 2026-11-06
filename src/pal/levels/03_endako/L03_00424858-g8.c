/* func_PAL_L03_00424858, the PAL copy of func_L03_0041F410: the same C, where 0.016666668f becomes
 * 0.020000001f and the first random value is scaled to 50 Hz. The scale's extra insns keep loop.c from
 * hoisting 210000.0f on its own, so the loop's constants are locals, in retail's preheader order. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282D08(void *, void *, void *, float);
extern u8 *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern int func_002A77E0(int);
extern u8 *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int D_L03_001B1C40 __attribute__((sda));
extern int D_L03_001B1C44 __attribute__((sda));
extern int D_L03_001B1C48 __attribute__((sda));
extern int D_L03_001B1C58 __attribute__((sda));
/* Upper bounds are the second words of the measured min/max pairs.
 * Their unsized views keep the absolute accesses alongside GP lower bounds. */
extern int D_L03_001B1C58_1[] MACRO_ADDR;
extern float D_L03_001B1C68 __attribute__((sda));
extern float D_L03_001B1C68_1[] MACRO_ADDR;
extern float D_L03_001B1C50 __attribute__((sda));
extern float D_L03_001B1C50_1[] MACRO_ADDR;
extern float D_L03_001B1C70 __attribute__((sda));
extern int D_L03_001B1C60_1[] MACRO_ADDR;
extern int D_L03_001B1C60 __attribute__((sda));
extern float D_L03_001B1C70_1[] MACRO_ADDR;
/* Emits two particle families along the visible segment between from and to. */
void func_PAL_L03_00424858(u8 *entity, Vector *from, Vector *to, int enabled) {
    Vector test, velocity, point, aux;
    int i, count, color, rotation;
    float life, step;
    qcopy(&test, from);
    test.f[3] = func_00282E48(from, to);
    if (test.f[3] > 1.0f) return;
    if (func_00283DB8(&test, 32.0f) == -1) return;
    for (i=0; i<D_L03_001B1C40; i++) {
        float lo = 0.0f, dt = 0.020000001f, scale = 210000.0f;
        color = (func_002A7820(D_L03_001B1C58, D_L03_001B1C58_1[1]) * 5 + 2) / 6;
        rotation = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        life = func_002A7878(D_L03_001B1C68, D_L03_001B1C68_1[1]) * scale;
        func_002A7A00(&velocity, lo, dt);
        velocity.f[2] += func_002A7878(D_L03_001B1C50, D_L03_001B1C50_1[1]) * dt;
        func_00282D08(&point, from, to, func_002A7878(0, 1));
        func_002C16C0(&point, &velocity, color, D_L03_001B1C48 >> 24,
                     D_L03_001B1C48 & 0xFFFFFF, rotation, life, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (enabled) {
        int j;
        count = D_L03_001B1C44;
        if (entity[0x20] == 5) count = func_002A77E0(2);
        step = 1.0f / (float)D_L03_001B1C44;
        for (j=0; j<count; j++) {
            point.q = 0;
            aux.q = 0;
            point.f[3] = D_L03_001B1C70;
            aux.f[3] = D_L03_001B1C70_1[1];
            velocity.q = point.q;
            point.q = aux.q;
            life = func_002A7878(0, step);
            func_00282D08(&aux, from, to, life + (float)j * step);
            aux.f[2] += 0.02f;
            {
                u8 *p = func_002BAA28(&aux, &velocity, &point, 0x40000000, 0x10000000, 5,
                                    D_L03_001B1C60, D_L03_001B1C60_1[1], -1);
                if (p) p[1] = 1;
            }
        }
    }
}
