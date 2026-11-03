/* functional: high. The near-miss draft (1360/1428 bytes; address arithmetic, allocation and scheduling differ) read against all 357 retail instructions of level 00's copy: the float compares written in retail's sense and operand order (c.le.s 6 <= d, c.le.s 12 <= d), level 00's callees mapped through functions.tsv, data by retail's lui/$gp addresses (0x1B2778/0x1B2790/0x1B27A8/0x1B27C0 short tables, 0x1B27D4/0x1B27D8 timers, 0x1B27DC fade, 0x1AF274/0x1AF278/0x1AF27C tunables, 0x239EF0 the 10x5 point table, 0x25C64C, 0x1B8DC0 the camera). Retail's 0x72821800 words are R5900 three-operand madd (the 80-byte row address), ordinary arithmetic. */
/* func_L00_00395428 (shared, 27 places): electric arcs between an object and the hero. Unless the hero's
 * object (hero+0x2290) has class byte +0x43 == 0x7B it stores 0.1 at 0x25C64C. State 0: state 2 and resets
 * the ten arcs' tables and both timers. State 2: in hero mode 31, at distance >= 6 it emits, and sets the fade
 * (0x1B27DC) from the two timers (1 - t1/T1 while the first runs; past 12: t2/T2 while the second runs, else
 * 0; under 12: 1); in other modes it resets the timers and plays sound 12. Then from the object's centre
 * (pos - 0.5*size) each arc counts its life down: a dead arc restarts while emitting (life 2, alpha 64, a
 * random kink direction, four segments of random +-10..45 degree turns about the camera axis), a live one
 * jitters its four segment vectors by 0..0.1, re-roots at the centre and sets alpha 32 (0 at its last frame).
 * When anything is live it queues the draw func_L00_003959C0 through func_L00_002E6EF8.
 * From the near-miss draft nonmatching/levels/func_L00_00395428.c. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { char pad[0x2290]; char *object; int mode; } WorldState;

extern WorldState D_00189E20;
extern float D_L00_0025C64C;
extern short D_L00_001B2778[10], D_L00_001B2790[10], D_L00_001B27A8[10], D_L00_001B27C0[10];
extern float D_L00_001AF274 __attribute__((sda));
extern int D_L00_001AF278 __attribute__((sda));
extern int D_L00_001AF27C __attribute__((sda));
extern int D_L00_001B27D4;
extern int D_L00_001B27D8 __attribute__((sda));
extern float D_L00_001B27DC __attribute__((sda));
extern Vector D_L00_00239EF0[10][5];
extern Vector D_L00_001B8DC0;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_0029F530(void *);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7988(void *, float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_003959C0(char *);
extern void func_L00_002E6EF8(void *, void *);

void func_L00_00395428(char *object)
{
    Vector origin, random, difference, offsets[5];
    int emitting = 0;
    int i, j, active;
    float distance, elapsed, sign;

    if (*(unsigned char *)(D_00189E20.object + 0x43) != 0x7B)
        D_L00_0025C64C = 0.1f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 2;
        for (i = 0; i < 10; i++) {
            D_L00_001B2778[i] = 0;
            D_L00_001B27A8[i] = 2;
            D_L00_001B27C0[i] = 1;
        }
        D_L00_001B27D4 = D_L00_001AF278;
        D_L00_001B27D8 = D_L00_001AF27C;
        break;
    case 2:
        if (D_00189E20.mode == 31) {
            distance = func_0029F530(object);
            if (6.0f <= distance) {
                emitting = 1;
                if (func_00282948(&D_L00_001B27D4) == 0) {
                    elapsed = func_00283CE0(D_L00_001B27D4);
                    elapsed = elapsed / func_00283CE0(D_L00_001AF278);
                    D_L00_001B27DC = 1.0f - elapsed;
                } else if (12.0f <= distance) {
                    if (func_00282948(&D_L00_001B27D8) != 0) {
                        D_L00_001B27DC = 0.0f;
                    } else {
                        elapsed = func_00283CE0(D_L00_001B27D8);
                        elapsed = elapsed / func_00283CE0(D_L00_001AF27C);
                        D_L00_001B27DC = elapsed;
                    }
                } else {
                    D_L00_001B27DC = 1.0f;
                }
            }
        } else {
            D_L00_001B27D4 = D_L00_001AF278;
            D_L00_001B27D8 = D_L00_001AF27C;
            func_002A7470(object, 1, 0, 12);
        }
        break;
    }
    func_00282D30(&origin, object + 0xD0, -0.5f);
    func_00282CC0(&origin, &origin, object + 0x10);
    active = 0;
    for (i = 0; i < 10; i++) {
        if (D_L00_001B2778[i] != 0) {
            active = 1;
            break;
        }
    }
    if (emitting == 0 && active == 0)
        return;
    for (i = 0; i < 10; i++) {
        D_L00_001B2778[i] = D_L00_001B2778[i] - 1;
        if (D_L00_001B2778[i] < 0)
            D_L00_001B2778[i] = 0;
        if (D_L00_001B2778[i] == 0) {
            if (emitting == 0)
                continue;
            D_L00_001B2778[i] = 2;
            D_L00_001B2790[i] = 64;
            func_002A7988(&random, D_L00_001AF274, D_L00_001AF274);
            D_L00_00239EF0[i][0].q = origin.q;
            sign = 1.0f;
            for (j = 0; j < 4; j++) {
                func_00282CF0(&difference, &D_L00_00239EF0[i][j], &D_L00_001B8DC0);
                func_002ACEC0(&random, &random, &difference,
                              func_002A7878(0.17453295f, 0.785398245f) * sign);
                sign = -sign;
                func_00282CC0(&D_L00_00239EF0[i][j + 1], &D_L00_00239EF0[i][j], &random);
            }
        } else {
            for (j = 0; j < 4; j++) {
                func_00282CF0(&offsets[j + 1], &D_L00_00239EF0[i][j + 1], &D_L00_00239EF0[i][j]);
                offsets[j + 1].f[0] = offsets[j + 1].f[0] + func_002A78D8(0.0f, 0.1f);
                offsets[j + 1].f[1] = offsets[j + 1].f[1] + func_002A78D8(0.0f, 0.1f);
                offsets[j + 1].f[2] = offsets[j + 1].f[2] + func_002A78D8(0.0f, 0.1f);
            }
            D_L00_00239EF0[i][0].q = origin.q;
            for (j = 0; j < 4; j++)
                func_00282CC0(&D_L00_00239EF0[i][j + 1], &D_L00_00239EF0[i][j], &offsets[j + 1]);
            if (D_L00_001B2778[i] > 0)
                D_L00_001B2790[i] = 32;
            else
                D_L00_001B2790[i] = 0;
        }
    }
    func_L00_002E6EF8(func_L00_003959C0, object);
}
