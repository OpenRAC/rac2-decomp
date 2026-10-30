/* Complete C reconstruction; not linked and no matching credit.
 * 2026-10-30, game -O2 -G0 -ffunction-sections -frac2-qcopy:
 * 1524/1520 bytes, USA v1.01 0/1 and USA v2.00 0/1. PAL identity absent.
 * Explicit damping/maximum lifetimes restore the retail 0x50 frame and f20-f22;
 * the literal-only alternative is 1516 bytes with a 0x40 frame. The initializer's
 * scalar/store order, saved pointer roles, animation result and switch layout
 * still differ. The five jump-table entries were read independently: event 1
 * falls through, 2/3 select animation 8, and 4/5 select animation 9 and reset.
 * Full 16-byte position transfers and canonical per-program symbols are kept.
 * Four meaningful transfer/lifetime trials; reopen with independent state-field
 * grouping and initializer scheduling evidence, not register pins or fake uses.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern float func_002A89A8(void *, int, float);
extern int func_00283CF0(float);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern void func_L04_003E22B0(void *, int, int, int, int);
extern float func_002A7878(float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_L04_003E5250(void *);
extern char *func_002A9640(void *, int, int);
extern void func_L04_00412AF8(void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_00291450(int);
extern void func_002A7470(void *, int, int, int);
extern void func_L04_003E5298(void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern char *D_L04_001B25CC;
extern char D_L04_001B9680[];

int func_L04_003E4C00(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    int event;
    char *hit;

    if (actor[0x20] == 0) {
        float damping = 0.4f;
        float maximum = 1.25f;
        *(float *)(actor + 0x18) = func_002A89A8(actor + 0x10, 0, 0.5f);
        *(void **)(state + 0x18) = state + 0x140;
        *(int *)(state + 0x2D0) = 0;
        state[0x48] = func_00283CF0(20.0f);
        state[0x4A] = func_00283CF0(11.2f);
        *(int *)(state + 0xA8) = 3;
        *(float *)(state + 0x90) = 0.5f;
        *(float *)(state + 0x94) = 0.5f;
        *(float *)(state + 0x9C) = damping;
        state[0xD7] = 1;
        *(float *)(state + 0x148) = 0.5f;
        *(float *)(state + 0x14C) = 0.5f;
        state[0xD3] = 0xFF;
        state[0xCC] = 0xFF;
        state[0xCD] = 0xFF;
        state[0xCE] = 0xFF;
        state[0xCF] = 0xFF;
        state[0xD2] = 0xFF;
        state[0x70] = 22;
        state[0x72] = 11;
        state[0x76] = 13;
        state[0x77] = 14;
        *(float *)(state + 0x7C) = 0.100000009f;
        *(float *)(state + 0x88) = 0.008333333768f;
        *(float *)(state + 0x8C) = 0.004166666884f;
        *(float *)(state + 0x140) = 1.0f;
        *(float *)(state + 0x144) = 0.25f;
        *(float *)(state + 0x150) = 1.483530045f;
        *(float *)(state + 0x170) = 0.5235988498f;
        *(float *)(state + 0x16C) = 0.00555555569f;
        state[0x71] = 11;
        *(float *)(state + 0x80) = 0.06666667014f;
        *(float *)(state + 0x84) = 0.004166666884f;
        func_002B60B0(actor, 0.002222222276f, 0.06666667014f,
                     0.001163552981f, 0.1047197729f);
        *(TI128 *)(state + 0x110) = *(TI128 *)(actor + 0x10);
        *(float *)(state + 0x120) = maximum;
        *(float *)(state + 0x12C) = *(float *)(state + 0x2C0);
        *(float *)(state + 0x130) = 10.0f;
        *(int *)(state + 0x2BC) = func_002A7820(120, 700);
        state[0x28] = 3;
        state[0x2E] = 1;
        state[0x29] = 1;
        *(float *)(state + 0x2E4) = (float)state[0x34];
        *(float *)(state + 0x2E8) = (float)state[0x34];
        *(float *)(state + 0x30) = 0.75f;
        func_002A7750(actor, 1, 0);
        if (*(int *)(state + 0x2F0) != -1) {
            *(float *)(actor + 0x2C) = *(float *)(*(char **)(actor + 0x24) + 0x24) * damping;
            state[0x306] = 0;
            *(TI128 *)(actor + 0x10) =
                *(TI128 *)(D_L04_001B25CC + (*(int *)(state + 0x2F0) << 7) + 0x30);
            *(TI128 *)(state + 0x280) = *(TI128 *)(actor + 0x10);
            func_L04_003E22B0(actor, 1, 1,
                func_002A77E0(*(u8 *)(*(char **)(*(char **)(actor + 0x24) + 0x4C) + 0x10)), 10);
            *(short *)(state + 0x300) = func_002A7820(1200, 3000);
            func_002A7750(actor, 5, 0);
            *(float *)(state + 0x140) *= damping;
            state[0x307] = 0;
            *(float *)(state + 0x144) = *(float *)(state + 0x140) + 0.01f;
        } else {
            func_L04_003E22B0(actor, 4, 1,
                func_002A77E0(*(u8 *)(*(char **)(*(char **)(actor + 0x24) + 0x58) + 0x10)), 0);
        }
        *(float *)(actor + 0x48) = func_002A7878(0.5f, maximum);
    }
    if (actor[0x31] != 0 && func_00282E48(actor + 0x10, D_L04_001B9680) < 24.0f) {
        func_002A93B0(actor);
        actor[0x6F] = 22;
    }
    if (state[0x2E] == 2) {
        func_L04_003E5250(actor);
        return 1;
    }
    if (*(int *)(state + 0x2F0) != -1) {
        hit = func_002A9640(actor, 0x10000, 1);
        if (actor[0x20] == 22 || state[0x307] != 0)
            actor[0xA8] = 0xFF;
        else if (hit != 0) {
            func_L04_00412AF8(actor, state + 0x280);
            *(float *)(hit + 0x2C) = (float)*(short *)(state + 0x24) * 0.3f;
        }
    }
    if (state[0x307] != 0)
        state[0x307]--;
    event = func_002B0ED8(actor, state + 0x60, 0);
    if (event != 0) {
        *(int *)(state + 0x2D0) = 0;
        if (*(int *)(state + 0x2E0) >= 0) {
            func_00291450(*(int *)(state + 0x2E0));
            *(int *)(state + 0x2E0) = -1;
        }
        if (event == 5) {
            *(int *)(state + 0xF0) = 0;
            *(float *)(state + 0xF4) = 0.8377581835f;
        }
        if (*(void **)(state + 0x2AC) != 0) {
            switch (event) {
            case 2:
            case 3:
                func_002A7470(*(void **)(state + 0x2AC), 8, 0, 3);
                break;
            case 4:
            case 5:
                func_002A7470(*(void **)(state + 0x2AC), 9, 0, 3);
                *(int *)(*(char **)(*(char **)(state + 0x2AC) + 0x68) + 0x27C) = 0;
                break;
            }
        }
        func_L04_003E5298(actor);
        if (actor[0x95] == 0) {
            if (*(int *)(state + 0x2CC) != -1) {
                func_002A7750(actor, 9, 1);
                func_L04_003E22B0(actor, 4, 3, 0, 12);
            } else {
                func_002A7750(actor, 8, 1);
                *(short *)(state + 0x2A0) = func_002A7820(580, 600);
                func_L04_003E22B0(actor, 6, 5, 0, 10);
            }
        }
    }
    if (*(int *)(state + 0x2F0) != -1)
        *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(int *)(state + 0x258) = func_002B3BA8(actor, *(int *)(state + 0x250), 0, 0,
                                         *(float *)(state + 0x298), 10.0f);
    *(int *)(state + 0x25C) = func_002B3BA8(actor, *(int *)(state + 0x254), 0, 0,
                                         *(float *)(state + 0x29C), 10.0f);
    return 0;
}
