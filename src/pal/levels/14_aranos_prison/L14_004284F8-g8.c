#include "include_asm.h"
#include "common.h"

extern float D_L14_001B16B0 __attribute__((sda));
extern int func_002A9640(char *a0, int a1, int a2);
extern void func_002B0ED8(char *a0, char *a1, int a2);
extern void func_002AC728(char *a0, char *a1, float f12, float f13, int a2);
extern void func_002A6C58(char *a0, int a1, int a2);
extern void func_0029F338(char *a0);

/* Resets the moby's scale when its model says so, then lets it fall or die. */
void func_PAL_L14_00428798(char *a0)
{
    char *s0 = a0;
    char *s1;
    char *m;
    char *v;

    s1 = *(char **)(s0 + 0x68);
    v = (char *)func_002A9640(a0, 0x10000, 1);
    if (v != 0) {
        m = *(char **)(v + 0x20);
        if (m != 0 && *(short *)(m + 0xAA) == 0xB69) {
            if (*(unsigned char *)(s0 + 0x31) == 0)
                *(float *)(v + 0x2C) = 0.0f;
            else
                *(float *)(v + 0x2C) = 1.0f;
        }
    }
    func_002B0ED8(s0, s1 + 0x60, 0);
    if (*(float *)(s1 + 0x20) <= 0.0f) {
        func_002AC728(s0, s0 + 0x10, 1.0f, 13.0f, -1);
        func_002A6C58(s0, 0, 3);
        func_0029F338(s0);
    } else if (*(float *)(s0 + 0x18) < D_L14_001B16B0) {
        func_002A6C58(s0, 0, 3);
        func_0029F338(s0);
    }
}

extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L14_00423CD0(void *, void *, int, void *, int, float);
extern void func_L14_00423DC0(void *, void *);
extern int func_L14_00423E50(void *);
extern int func_L09_0033E690(void *, int, float);
extern float func_00282E80(void *, void *);
extern int func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, float, float);
extern unsigned long func_002B1C20(void *, void *);

extern char *D_L14_001B259C;
extern char *D_L14_001B268C;
extern int D_L14_001B16B4 __attribute__((sda));
extern int D_L14_001B16B8 __attribute__((sda));
extern int D_L14_001B16BC __attribute__((sda));
extern char D_00189EA0[];

/*
 * Updates the actor's animation, movement phases and hit response.
 * func_PAL_L14_004288B0, the PAL copy of func_L14_00423358: the same C, where the animation blend
 * of 10 frames becomes 8, the four rates passed to func_002B60B0 are rescaled for 50 Hz, and the
 * idle timer's limit D_L14_001B16B4 is scaled by 5/6.
 */
void func_PAL_L14_004288B0(char *self)
{
    char *state = *(char **)(self + 0x68);
    float target[4];
    unsigned long flags;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        break;
    case 1:
        if (func_002B3868(self)) {
            if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 1)
                func_002A7470(self, func_002A77E0(2) + 1, 0, 8);
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            float a = *(float *)(state + 0x720);
            float b = *(float *)(state + 0x724);
            func_002B60B0(self, (a + a) * 0.00040000002f,
                a * 0.020000001f, (b + b) * 6.981318e-06f,
                b * 0.0003490659f);
            if (*(unsigned char *)(self + 0x43) != func_002A77E0(4) + 6)
                func_002A7470(self, func_002A77E0(4) + 6, 0, 8);
            *(short *)(state + 0x770) = 0;
        } else if (func_L14_00423CD0(self, state + 0x700, *(int *)(state + 0x730), state + 0x770, 0, 2.0f)) {
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(self)) {
            if (*(unsigned char *)(self + 0x43) != 1)
                func_002A7470(self, 1, 0, 8);
            *(unsigned char *)(self + 0xBC) = 0;
            *(unsigned short *)(self + 0x96) = func_002A77E0(D_L14_001B16B4 >> 1);
        } else {
            qcopy_nc(target, (void *)((*(int *)(state + 0x748) << 8) + (unsigned int)D_L14_001B259C + 0x10));
            target[2] += 0.3f;
            func_L14_00423DC0(self, D_L14_001B259C + (*(int *)(state + 0x748) << 8) + 0x10);
            if (*(unsigned char *)(self + 0xBC) == 0 && *(unsigned short *)(self + 0x96) > ((s32)(D_L14_001B16B4) * 5 + 2) / 6) {
                *(unsigned short *)(self + 0x96) = func_002A77E0(D_L14_001B16B4 >> 1);
                if (func_002A77E0(5) != 0 && *(unsigned char *)(self + 0x43) != 5)
                    func_002A7470(self, 5, 0, 8);
            }
            if (*(unsigned char *)(self + 0xBC) == 1 && (*(unsigned char *)(self + 0x60) & 2))
                func_002A7750(self, 2, -1);
        }
        break;
    case 4:
        if (func_002B3868(self)) {
            switch (*(unsigned char *)(self + 0xBC) = func_002A77E0(2)) {
            case 0:
                if (*(unsigned char *)(self + 0x43) != 4)
                    func_002A7470(self, 4, 0, 8);
                break;
            case 1:
                if (*(unsigned char *)(self + 0x43) != 3)
                    func_002A7470(self, 3, 0, 8);
                break;
            }
        }
        if (*(int *)(state + 0x764) != -1)
            func_L14_00423DC0(self, D_L14_001B268C + (*(int *)(state + 0x764) << 7) + 0x30);
        if (*(unsigned char *)(self + 0x60) & 2)
            func_002A7750(self, 5, 2);
        break;
    case 5:
        if (func_002B3868(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 10)
                func_002A7470(self, func_002A77E0(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (*(int *)(state + 0x734) != -1) {
                    float a, b;
                    *(unsigned char *)(self + 0xBC) = 1;
                    a = *(float *)(state + 0x728);
                    b = *(float *)(state + 0x72C);
                    func_002B60B0(self, (a + a) * 0.00040000002f,
                        a * 0.020000001f, (b + b) * 6.981318e-06f,
                        b * 0.0003490659f);
                    if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 14)
                        func_002A7470(self, func_002A77E0(2) + 14, 0, 8);
                    *(short *)(state + 0x770) = func_L09_0033E690(self + 0x10, *(int *)(state + 0x734), 0.0f);
                } else {
                    *(unsigned char *)(self + 0xBC) = 2;
                }
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                func_L14_00423CD0(self, state + 0x700, *(int *)(state + 0x734), state + 0x770, *(short *)(state + 0x77C), 1.0f);
                if (*(unsigned short *)(self + 0x96) % D_L14_001B16B8 == 0 && func_002A77E0(D_L14_001B16BC) == 0) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 12)
                        func_002A7470(self, func_002A77E0(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (func_L14_00423E50(self))
                    func_002A7750(self, 5, -1);
                else
                    func_002A7750(self, 1, -1);
            }
        }
        break;
    case 6:
        if (func_002B3868(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 10)
                func_002A7470(self, func_002A77E0(2) + 10, 0, 8);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                float a, b;
                *(unsigned char *)(self + 0xBC) = 1;
                a = *(float *)(state + 0x728);
                b = *(float *)(state + 0x72C);
                func_002B60B0(self, (a + a) * 0.00040000002f,
                    a * 0.020000001f, (b + b) * 6.981318e-06f,
                    b * 0.0003490659f);
                if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 14)
                    func_002A7470(self, func_002A77E0(2) + 14, 0, 8);
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                qcopy(state + 0x700, D_00189EA0);
                if (func_00282E80(self + 0x10, state + 0x700) < *(float *)(state + 0x74C) && *(unsigned char *)(self + 0x31)) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 12)
                        func_002A7470(self, func_002A77E0(2) + 12, 0, 8);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                func_002A7750(self, 6, -1);
            }
        }
        break;
    case 7:
        if (func_002B3868(self)) {
            if (*(unsigned char *)(self + 0x43) != func_002A77E0(2) + 14)
                func_002A7470(self, func_002A77E0(2) + 14, 0, 8);
        }
        func_L02_0032E998(self + 0x10, state + 0x710, state + 0x768, state + 0x200,
            *(int *)(state + 0x750), state + 0x75C, state + 0x760, 0.0f, 0.4f);
        qcopy(state + 0x700, state + 0x710);
        *(short *)(state + 0x77A) = 1;
        if (func_00282E80(self + 0x10, state + 0x710) < 0.2f)
            func_002A7750(self, 1, 1);
        break;
    case 8:
        flags = func_002B1C20(self, state + 0x60);
        if ((*(unsigned char *)(self + 0x42) == 0x12 && func_002A77E0(30) == 0) || ((flags & 1UL) == 1UL)) {
            func_002A6C58(self, 0, 3);
            func_0029F338(self);
        } else if ((flags & 2UL) == 2UL) {
            func_002A7750(self, *(unsigned char *)(self + 0x94), 2);
        }
        break;
    }
}
