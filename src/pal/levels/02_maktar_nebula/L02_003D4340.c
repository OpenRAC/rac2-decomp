#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L02_003D4458);

#include "common.h"
extern char D_L02_001BA500;
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_002A93B0(char *);
extern void *func_002A9640(char *, int, int);
extern void func_PAL_002B1A50(char *, char *, int);
extern void func_L02_003D1998(char *);
extern int func_L02_003D1880(char *, void *);
extern void func_PAL_L02_003D5FF0(char *, int);
extern void func_L02_003D2390(char *);
extern void func_PAL_L02_003D64F8(char *, int, int);

/* State 0 of the actor: fills its state record (a random heading of 10 to 30 degrees, either
   sign, then about twenty constants), queues func_L02_003D2390; then, while it is drawn, the
   per-frame part (the pulse test against D_L02_001BA500, the 0x15/0x10 animation switch,
   func_PAL_L02_003D64F8 and func_L02_003D1998).
   Spelling: the signed heading is a variable of its own, set after the coin flip and stored
   first. Its pseudo then crosses no call, so sched1 ties its store to that call by an
   anti-dependence (priority 3) and the zero store at 0x2F4 goes first, as in retail; stored
   from `ang` itself, the two stores tie at priority 4 and the dying `ang` wins. The constant
   stores come out in an order of the scheduler's own (the statement order below is the
   measured one), and 0.017453294f, 1.5707965f and 0.52359885f are retail's bits. */
void func_PAL_L02_003D5140(char *self) {
    char *s = *(char **)(self + 0x68);
    float ang;
    float dir;
    char *p;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(char **)(s + 0x18) = s + 0x100;
        *(unsigned char *)(s + 0x48) = func_00283CF0(15.0f);
        *(unsigned char *)(s + 0x4A) = func_00283CF0(16.0f);
        ang = func_002A7878(10.0f, 30.0f) * 0.017453294f;
        if (func_002A77E0(2) != 0)
            dir = -ang;
        else
            dir = ang;
        *(float *)(s + 0x2E8) = dir;
        *(unsigned char *)(s + 0x60) = 0x14;
        *(int *)(s + 0x98) = 7;
        *(float *)(s + 0x80) = 1.3f;
        *(float *)(s + 0x84) = 1.3f;
        *(unsigned char *)(s + 0x69) = 2;
        *(unsigned char *)(s + 0x1E9) = 3;
        *(float *)(s + 0x8C) = 0.4f;
        *(unsigned char *)(s + 0x1E6) = 5;
        *(float *)(s + 0x108) = 0.3f;
        *(unsigned char *)(s + 0x1E8) = 2;
        *(float *)(s + 0x1D4) = 0.5f;
        *(float *)(s + 0x100) = 1.0f;
        *(float *)(s + 0x104) = 0.2f;
        *(float *)(s + 0x10C) = 0.3f;
        *(float *)(s + 0x110) = 1.5707965f;
        *(float *)(s + 0x130) = 0.52359885f;
        *(short *)(s + 0x2F4) = 0;
        *(float *)(s + 0x134) = 0.01f;
        *(float *)(s + 0x12C) = 0.008f;
        *(unsigned char *)(s + 0x28) = 3;
        *(unsigned char *)(s + 0x29) = 1;
        *(float *)(s + 0x30) = 0.75f;
        if (func_002A77E0(2) == 0)
            *(unsigned short *)(self + 0x34) |= 0x8000;
        *(int *)(s + 0x2E4) = 0;
        func_L02_003D2390(self);
    }
    if (*(unsigned char *)(self + 0x31) != 0) {
        if (func_00282E48(self + 0x10, &D_L02_001BA500) < 24.0f) {
            func_002A93B0(self);
            *(unsigned char *)(self + 0x6F) = 0x16;
        }
        if (*(unsigned char *)(self + 0x31) != 0 && *(unsigned char *)(self + 0x20) >= 3) {
            *(float *)(s + 0xFC) = 1.0f;
            p = func_002A9640(self, 0x10000, 1);
            if (p != 0) {
                *(float *)(s + 0xFC) = 1.0f;
                if (func_L02_003D1880(self, p) != 0) {
                    *(unsigned char *)(s + 0x60) = 0x13;
                    func_PAL_002B1A50(self, s + 0x50, 1);
                    *(unsigned char *)(s + 0x60) = 0x14;
                    if (*(int *)(s + 0x2E4) != 0 && *(short *)(s + 0x2F4) == 0 &&
                        *(unsigned char *)(self + 0x31) != 0) {
                        func_PAL_L02_003D5FF0(*(char **)(s + 0x2E4) + 0x10, 2);
                        *(short *)(s + 0x2F4) = 0x32;
                    }
                } else {
                    func_PAL_002B1A50(self, s + 0x50, 0);
                }
            } else {
                func_PAL_002B1A50(self, s + 0x50, 0);
            }
            if (*(float *)(s + 0x20) <= 0.0f && *(unsigned char *)(self + 0x20) != 0x15) {
                func_002A7750(self, 0x15, 7);
                if (*(unsigned char *)(self + 0x43) != 0x10)
                    func_PAL_002A7E68(self, 0x10, 0, 0);
            }
            if (*(unsigned char *)(self + 0x20) >= 2 && *(unsigned char *)(s + 0x2E) == 2)
                func_PAL_L02_003D64F8(self, 1, 1);
            func_L02_003D1998(self);
        }
    }
}

