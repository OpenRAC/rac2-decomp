/* func_L20_0043ECB0 needs -G8 for its $gp globals but not -mno-split-addresses, which
   L20_0043ECB0-g8.c is built with: with it the timer branch fills its delay slot through a
   beql instead of retail's split lui. So it has a file of its own at the default -G8 flags. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vector;

/* State block of the orbiting projectile, pointed to by moby + 0x68 (filled by func_L20_0043F318). */
typedef struct {
    Vector vel;          /* 0x00 */
    Vector history[3];   /* 0x10 */
    float radius;        /* 0x40 */
    float angle;         /* 0x44 */
    float targetRadius;  /* 0x48 */
    float targetHeight;  /* 0x4C */
    float radiusSpeed;   /* 0x50 */
    float angleSpeed;    /* 0x54 */
    float heightSpeed;   /* 0x58 */
    float baseHeight;    /* 0x5C */
    int unk60;           /* 0x60 */
    int timer;           /* 0x64 */
    int clockwise;       /* 0x68 */
    int *clock;          /* 0x6C */
    float damage;        /* 0x70 */
} OrbitState;

extern int D_L20_001A8F00[] __attribute__((sda));
extern float D_L20_001B1F9C __attribute__((sda));
extern float D_L20_001B1FA0 __attribute__((sda));
extern float D_L20_001B1FA4 __attribute__((sda));
extern float D_L20_001B1FA8 __attribute__((sda));
extern float D_L20_001B1FAC __attribute__((sda));
extern float D_L20_001B1FB0 __attribute__((sda));
extern float D_L20_001B1FB4 __attribute__((sda));
extern float D_L20_001B1FB8 __attribute__((sda));
extern int D_L20_001B2AC8[] __attribute__((sda));
extern int D_L20_001C0418 __attribute__((nosda));
extern char D_L20_001B9FC0[] __attribute__((nosda));
extern char D_00189E20[] __attribute__((nosda));

extern void func_0029F338(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern int func_00282948(void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_00282CF0(void *, void *, void *);
extern int func_00282C30(int);
extern void func_002A7750(void *, int, int);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E20(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_0032DA58(void *, void *, void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int,
                          float, float, int, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L20_0043F460(char *);
extern void func_L20_0043F510(char *);
extern void func_L00_002E6EF8(void (*)(char *), char *);

void func_L20_0043ECB0(char *arg0) {
    OrbitState *state = *(OrbitState **)(arg0 + 0x68);
    Vector oldPos;
    Vector delta;
    Vector v0;
    float f;
    float spin;
    float speed;
    int i;

    if (D_L20_001A8F00[0] == 2) {
        func_0029F338(arg0);
        return;
    }
    qcopy(&oldPos, arg0 + 0x10);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        func_002AA548(&state->radius, &state->radiusSpeed, state->targetRadius,
                      D_L20_001B1F9C * 0.000277777785f,
                      D_L20_001B1F9C * 0.000277777785f,
                      D_L20_001B1FA0 * 0.0166666675f);
        *(float *)(arg0 + 0x10) = func_00283180(state->angle) * state->radius;
        *(float *)(arg0 + 0x14) = func_00283198(state->angle) * state->radius;
        *(float *)(arg0 + 0x18) = 0.0f;
        func_00282CC0(arg0 + 0x10, arg0 + 0x10, *(char **)(arg0 + 0xB8) + 0x10);
        *(float *)(arg0 + 0x18) = oldPos.f[2];
        if (func_00282C48(state->radius - state->targetRadius) < 0.5f) {
            float turn = D_L20_001B1FA4 * 0.000290888245f;
            if (state->clockwise == 0) {
                turn = -turn;
            }
            func_002AA2E8(&state->angleSpeed, turn, D_L20_001B1FA8 * 4.84813745e-06f);
            state->angle = func_00283B98(state->angle, state->angleSpeed);
            func_002AA548((float *)(arg0 + 0x18), &state->heightSpeed, state->targetHeight,
                          D_L20_001B1FAC * 0.000277777785f,
                          D_L20_001B1FAC * 0.000277777785f,
                          D_L20_001B1FB0 * 0.0166666675f);
            if (func_00282C48(*(float *)(arg0 + 0x18) - state->targetHeight) < 0.1f) {
                state->targetHeight = state->baseHeight + func_002A7878(3.0f, 8.0f);
            }
        }
        if (func_00282948(&state->timer) == 0) {
            goto afterTimer;
        }
        {
            char *hero = D_00189E20;
            f = func_00283248(*(float *)(hero + 0x80) - *(float *)(arg0 + 0x10),
                              *(float *)(hero + 0x84) - *(float *)(arg0 + 0x14));
            if (func_00283C80(*(float *)(arg0 + 0xF8), f) < 0.6283185482f) {
                func_00282CF0(&state->vel, arg0 + 0x10, &oldPos);
                state->vel.f[2] = 0.0f;
                func_002A7750(arg0, 1, -1);
                break;
            }
        }
afterTimer:
        if (func_00282C30(*state->clock - D_L20_001B2AC8[0]) >= 6) {
            func_00282CF0(&state->vel, arg0 + 0x10, &oldPos);
            state->vel.f[2] = 0.0f;
            func_002A7750(arg0, 2, -1);
        }
        break;
    case 1: {
        char *hero;
        float step;
        float accel = D_L20_001B1FAC * 0.000277777785f;
        float maxSpeed = D_L20_001B1FB0 * 0.0166666675f;

        func_002AA548((float *)(arg0 + 0x18), &state->heightSpeed, state->baseHeight + 1.0f,
                      accel, accel, maxSpeed);
        step = D_L20_001B1FB8 * 0.0166666675f;
        func_00282CF0(&v0, D_00189E20 + 0xD0, arg0 + 0x10);
        v0.f[2] = 0.0f;
        func_00282F20(&v0, &v0, step);
        func_00282CF0(&delta, &v0, &state->vel);
        func_00282F20(&delta, &delta, D_L20_001B1FB4 * 0.000277777785f);
        func_00282CC0(&state->vel, &state->vel, &delta);
        func_00282F20(&state->vel, &state->vel, step);
        func_00282CC0(arg0 + 0x10, arg0 + 0x10, &state->vel);
        hero = D_00189E20;
        f = func_00283248(*(float *)(hero + 0x80) - *(float *)(arg0 + 0x10),
                          *(float *)(hero + 0x84) - *(float *)(arg0 + 0x14));
        if (func_00283C80(*(float *)(arg0 + 0xF8), f) > 1.5707964f) {
            func_002A7750(arg0, 2, -1);
        }
        break;
    }
    case 2:
        speed = func_00282DF0(&state->vel);
        func_002AA2E8(&speed, D_L20_001B1FB8 * 0.0166666675f, 0.002777777845f);
        func_00282F20(&state->vel, &state->vel, speed);
        func_00282CC0(arg0 + 0x10, arg0 + 0x10, &state->vel);
        if (*(unsigned char *)(arg0 + 0x31) == 0) {
            goto remove;
        }
        break;
    }
    func_00282CF0(&delta, arg0 + 0x10, &oldPos);
    *(float *)(arg0 + 0xF8) = func_00283248(delta.f[0], delta.f[1]);
    *(float *)(arg0 + 0xF4) = -func_00283248(func_00282E20(&delta), delta.f[2]);
    spin = func_00283B98(*(float *)(arg0 + 0xF0), 0.05235988647f);
    {
        int historyPhase = D_L20_001B2AC8[0] & 3;
        *(float *)(arg0 + 0xF0) = spin;
        if (historyPhase == (((int)arg0 >> 8) & 3)) {
            Vector *history;
            Vector *src;
            Vector *dst;
            i = 2;
            history = state->history;
            src = history + 1;
            dst = history + 2;
            for (; i > 0; i--) {
                qcopy(dst, src);
                src--;
                dst--;
            }
            qcopy(history, arg0 + 0x10);
        }
    }
    if (func_002761F8(&oldPos, arg0 + 0x10, 0, *(char **)(arg0 + 0xB8), 0) == 0) {
        goto noHit;
    }
    if (D_L20_001C0418 != 0) {
        func_00282CF0(&v0, D_L20_001B9FC0, arg0 + 0x10);
        func_00282F20(&v0, &v0, 1.0f);
        func_002A8C28(*(char **)(arg0 + 0xB8), arg0 + 0x10, 0x10001, 0, 1, 0,
                      2.0f, state->damage, 1.0f);
        func_0032DA58(arg0, arg0 + 0x10, &v0, 0.0f);
    } else {
        func_0032C700(arg0 + 0x10, 0, 10, 20, 20, 20, 45, 0,
                      0.75f, 20.0f, 1, 0, 0, 0);
    }
    func_002E5CF8(0, 0, arg0);
remove:
    func_0029F338(arg0);
    return;
noHit:
    if (*(unsigned char *)(arg0 + 0x31) != 0) {
        func_L20_0043F460(arg0);
    }
    func_L00_002E6EF8(func_L20_0043F510, arg0);
}
