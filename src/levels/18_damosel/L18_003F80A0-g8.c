#include "include_asm.h"
#include "common.h"

extern int D_L18_001B05D4 __attribute__((sda));
extern float D_L18_001B05C8 __attribute__((sda));
extern float D_L18_001B05CC __attribute__((sda));
extern float D_L18_001B05D0 __attribute__((sda));
extern float D_L18_001B05B0[2] __attribute__((sda));
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void func_002ACB48(void *, float);
extern void func_00282F20(void *, void *, float);
extern void *func_L02_003449D8(void *, void *, void *, int, int);

/* Spawns a random number of particles (one more than a draw bounded by D_L18_001B05D4)
   around the object's position (+0x10): each from the position jittered by
   D_L18_001B05C8 and a direction from the vector at +0xC0, scaled by minus a random
   value between D_L18_001B05CC and D_L18_001B05D0 divided by 60, with two more draws. */
void func_L18_003FB620(u8 *object)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    int count;
    int i;

    count = func_002A77E0(D_L18_001B05D4) + 1;
    for (i = 0; i < count; i++) {
        qcopy(position, object + 0x10);
        func_002ACB48(position, D_L18_001B05C8);
        func_00282F20(direction, object + 0xC0,
                      -(func_002A7878(D_L18_001B05CC, D_L18_001B05D0) * 0.016666668f));
        func_L02_003449D8(position, direction, D_L18_001B05B0, func_002A77E0(2),
                          func_002A7820(-2, 2));
    }
}

extern int D_L18_001B15C0 __attribute__((sda));
extern int D_L18_001B15B0 __attribute__((sda));
extern float D_L18_001B15B8 __attribute__((sda));
extern float D_L18_001B15B4 __attribute__((sda));

extern int D_L18_001B15E0 __attribute__((sda));
extern int D_L18_001B15D0 __attribute__((sda));
extern float D_L18_001B15D8 __attribute__((sda));
extern float D_L18_001B15D4 __attribute__((sda));

extern int D_L18_001B1620 __attribute__((sda));
extern int D_L18_001B1614 __attribute__((sda));
extern float D_L18_001B161C __attribute__((sda));
extern float D_L18_001B1618 __attribute__((sda));
extern void func_0029FC20(s32 arg0, s32 arg1, void *arg2);
extern void func_002830C0(void *arg0, void *arg1, void *arg2);
extern void func_00282CC0(void *arg0, void *arg1, void *arg2);
extern void func_L00_00325AE8(void *arg0, s32 arg1, float arg2, float arg3);

void func_L18_00432FB8(u8 *a0) {
    u8 buf[0x50];
    u8 *s0 = buf + 0x10;
    func_0029FC20(*(s32 *)(*(u8 **)(a0 + 0x68) + 0x7C0), 1, s0);
    func_002830C0(buf, &D_L18_001B15C0, s0);
    func_00282CC0(buf, buf, buf + 0x40);
    func_L00_00325AE8(buf, D_L18_001B15B0, D_L18_001B15B8, D_L18_001B15B4);
}
void func_L18_00433020(u8 *a0) {
    u8 buf[0x50];
    u8 *s0 = buf + 0x10;
    func_0029FC20(*(s32 *)(*(u8 **)(a0 + 0x68) + 0x7C0), 1, s0);
    func_002830C0(buf, &D_L18_001B15E0, s0);
    func_00282CC0(buf, buf, buf + 0x40);
    func_L00_00325AE8(buf, D_L18_001B15D0, D_L18_001B15D8, D_L18_001B15D4);
}
void func_L18_00433168(u8 *a0, s32 a1) {
    u8 buf[0x50];
    u8 *s0 = buf + 0x10;
    func_0029FC20(*(s32 *)(*(u8 **)(a0 + 0x68) + 0x7C4), a1, s0);
    func_002830C0(buf, &D_L18_001B1620, s0);
    func_00282CC0(buf, buf, buf + 0x40);
    func_L00_00325AE8(buf, D_L18_001B1614, D_L18_001B161C, D_L18_001B1618);
}

typedef int TI128 __attribute__((mode(TI)));

extern void func_00308DE0(void *arg0, void *arg1, void *arg2);
extern void func_003088F0(void *arg0, void *arg1, void *arg2);
extern void func_00308920(void *arg0, void *arg1, void *arg2);
extern void func_00308BD8(void *arg0, void *arg1, float arg2);
extern float func_003089E0(void *arg0, void *arg1);
extern s32 func_00337AD8(s32 arg0, s32 arg1, float arg2);
extern void func_00340828(void *arg0, s32 arg1, float arg2, float arg3);
extern int D_L18_001B15F0 __attribute__((sda));
extern float D_L18_001B15F4 __attribute__((sda));
extern float D_L18_001B15F8 __attribute__((sda));
extern u8 D_L18_001B1600[] __attribute__((sda));
extern float D_L18_001B1610 __attribute__((sda));
extern u8 D_001C97C0[];
extern float D_L18_001B1520 __attribute__((sda));
extern float D_L18_001B1524 __attribute__((sda));
extern int D_L18_001B1528 __attribute__((sda));
extern float D_L18_001B152C __attribute__((sda));

extern char D_L18_001B1480[1] __attribute__((sda));
extern char D_L18_001B1490[] __attribute__((sda));

/* Runs the effect twice: once against the shared table at 0x1B1480 and once
   against the level's own copy at 0x1B1490. */
void func_L18_0042FAA8(u8 *a0)
{
    u8 *s0 = a0;

    func_L18_0042FAE0(a0, D_L18_001B1480);
    func_L18_0042FAE0(s0, D_L18_001B1490);
}

INCLUDE_ASM("asm/levels", func_L18_00433088);

void func_L18_0042FAE0(u8 *a0, void *a1) {
    u8 buf[0x30];
    u8 *s0;
    u8 *s2 = a0 + 0xC0;
    float t;
    func_00283098(buf, a1, s2);
    func_003088F0(buf, a0 + 0x10, buf);
    s0 = buf + 0x10;
    func_00308920(s0, D_001C97C0, buf);
    func_00308BD8(s0, s0, 1.0f);
    func_00308BD8(buf + 0x20, s2, -1.0f);
    t = func_003089E0(s0, buf + 0x20);
    if (D_L18_001B152C < t) {
        func_00340828(buf, func_00337AD8(D_L18_001B1528 & 0xFFFFFF,
                                         D_L18_001B1528, t * t),
                      D_L18_001B1524, D_L18_001B1520);
    }
}
