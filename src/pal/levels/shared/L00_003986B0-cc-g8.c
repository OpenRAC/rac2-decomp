/* func_PAL_L00_003986B0, the PAL copy of func_L00_00395428: the same C, where scale D_L00_001AF278; scale D_L00_001AF27C; scale D_L00_001AF278; scale D_L00_001AF27C; scale D_L00_001AF278; scale D_L00_001AF27C; rename func_002A7470 becomes func_PAL_002A7E68. */
/* Side-arc emitter: times the arcs' regrowth, then regrows or jitters each of the ten arcs.
 * Built with -G8 (the timers and lengths are read through $gp).
 */

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { char pad[0x2290]; char *object; int mode; } WorldState;
extern WorldState D_00189E20;
extern float D_L00_0025C64C NOT_SDA;
extern short D_L00_001B2778[] MACRO_ADDR, D_L00_001B2790[] MACRO_ADDR, D_L00_001B27A8[] MACRO_ADDR, D_L00_001B27C0[] MACRO_ADDR;
extern int D_L00_001AF278 __attribute__((sda));
extern int D_L00_001AF27C __attribute__((sda));
extern float D_L00_001AF274 __attribute__((sda));
extern float D_L00_001B27DC __attribute__((sda));
extern int D_L00_001B27D4, D_L00_001B27D8;
extern Vector D_L00_00239EF0[][5];
/* The same arcs seen from 16 bytes before them, as in RAC1 (electric_bolt_branch_points_base). */
typedef struct { Vector hdr; Vector p[4]; } ArcBase;
extern ArcBase D_L00_00239EE0[];
extern Vector D_L00_001B8DC0;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_0029F530(void *);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7988(void *, float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_003959C0(void);
/* func_L00_002E6EF8 in most levels; its address differs per level. */
extern void ref_L00_00395428_00(void *, void *);

void func_PAL_L00_003986B0(char *object)
{
    Vector origin, random, difference, offsets[5];
    int emitting = 0;
    int i, j, k, active;
    float distance;
    if (*(unsigned char *)(D_00189E20.object + 0x43) != 0x7B)
        D_L00_0025C64C = 0.1f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 2;
        {
            int n;
            for (n = 0; n < 10; n++) {
                D_L00_001B2778[n] = 0;
                D_L00_001B27A8[n] = 2;
                D_L00_001B27C0[n] = 1;
            }
        }
        D_L00_001B27D4 = (((int)(D_L00_001AF278) * 5 + 2) / 6);
        D_L00_001B27D8 = (((int)(D_L00_001AF27C) * 5 + 2) / 6);
        break;
    case 2:
        if (D_00189E20.mode == 31) {
            distance = func_0029F530(object);
            if (distance >= 6.0f) {
                emitting = 1;
                if (!func_00282948(&D_L00_001B27D4)) {
                    float elapsed = func_00283CE0(D_L00_001B27D4);
                    elapsed /= func_00283CE0((((int)(D_L00_001AF278) * 5 + 2) / 6));
                    D_L00_001B27DC = 1.0f - elapsed;
                } else if (distance >= 12.0f) {
                    if (!func_00282948(&D_L00_001B27D8)) {
                        float elapsed = func_00283CE0(D_L00_001B27D8);
                        elapsed /= func_00283CE0((((int)(D_L00_001AF27C) * 5 + 2) / 6));
                        D_L00_001B27DC = elapsed;
                    } else {
                        D_L00_001B27DC = 0.0f;
                    }
                } else {
                    D_L00_001B27DC = 1.0f;
                }
            }
        } else {
            D_L00_001B27D4 = (((int)(D_L00_001AF278) * 5 + 2) / 6);
            D_L00_001B27D8 = (((int)(D_L00_001AF27C) * 5 + 2) / 6);
            func_PAL_002A7E68(object, 1, 0, 10);
        }
        break;
    }
    func_00282D30(&origin, object + 0xD0, -0.5f);
    func_00282CC0(&origin, &origin, object + 0x10);
    active = 0;
    for (k = 0; k < 10; k++) {
        if (D_L00_001B2778[k]) {
            active = 1;
            break;
        }
    }
    if (!emitting && !active)
        return;
    for (i = 0; i < 10; i++) {
        if (--D_L00_001B2778[i] < 0)
            D_L00_001B2778[i] = 0;
        if (!D_L00_001B2778[i]) {
            if (emitting) {
                D_L00_001B2778[i] = 2;
                D_L00_001B2790[i] = 64;
                func_002A7988(&random, D_L00_001AF274, D_L00_001AF274);
                qcopy(&D_L00_00239EF0[i][0], &origin);
                {
                    float sign = 1.0f;
                    for (j = 1; j < 5; j++) {
                        func_00282CF0(&difference, &D_L00_00239EE0[i].p[j - 1], &D_L00_001B8DC0);
                        func_002ACEC0(&random, &random, &difference,
                                     func_002A7878(0.174532949924469f, 0.7853982448577881f) * sign);
                        sign = -sign;
                        func_00282CC0(&D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1], &random);
                    }
                }
            } else {
                /* Emits nothing, but gives this path a block of its own, so gcse puts the
                   next i there (the `b; addiu` after the regrow arm) and not before the test. */
                active = 0;
            }
        } else {
            for (j = 1; j < 5; j++) {
                func_00282CF0(&offsets[j], &D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1]);
                offsets[j].f[0] += func_002A78D8(0.0f, 0.1f);
                offsets[j].f[1] += func_002A78D8(0.0f, 0.1f);
                offsets[j].f[2] += func_002A78D8(0.0f, 0.1f);
            }
            qcopy(&D_L00_00239EF0[i][0], &origin);
            for (j = 1; j < 5; j++)
                func_00282CC0(&D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1], &offsets[j]);
            if (D_L00_001B2778[i] > 0)
                D_L00_001B2790[i] = 32;
            else
                D_L00_001B2790[i] = 0;
        }
    }
    ref_L00_00395428_00(func_L00_003959C0, object);
}
