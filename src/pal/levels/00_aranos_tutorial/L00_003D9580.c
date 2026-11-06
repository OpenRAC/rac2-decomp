/* func_PAL_L00_003D9580, the PAL copy of func_L00_003D54B0 (4,496 bytes): the same C, with the 50 Hz values.
 * Timers and blend counts scale by 5/6 (4 to 3, 10 to 8, 15 to 12, and func_002A7820's result written out),
 * and speeds by 6/5. The equal blend counts are why more arm tails cross-jump here than in the USA body.
 */
#include "common.h"

typedef int Quad003D54B0 __attribute__((mode(TI)));

extern int D_L00_001A8F00 MACRO_ADDR;
extern u8 D_00188660[];
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_001B0318[];

extern int func_PAL_00322DA0(char *);
extern void func_0029F338(void *);
extern int func_002B3890(char *);
extern void func_002B60B0(void *, float, float, float, float);
extern float func_00282C48(float);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern void *func_002A9640(void *, u32, s32);
extern int func_002B1C20(char *, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_003240E8(void *);
extern void func_PAL_002A7650(char *, int, int);
extern int func_PAL_002B5E10(char *);
extern void func_002AEF28(char *, char *, char *, float, float, float);
extern float func_002A7E08(char *, char *, char *, float, float, float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern void func_002E59F8(s32);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_0026FEB8(const char *, ...);
extern void func_002833F0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00282E48(void *, void *);
extern float func_00283C80(float, float);
extern int func_PAL_002B5BA8(char *, void *, float);
extern int func_PAL_002B5C98(char *, void *, float);
extern void func_PAL_00323D48(float, char *, void *, int);
extern void func_0027CFD0(void (*)(char *), char *);
extern void func_003225C0(char *);
extern void func_PAL_00323538(char *);
extern void func_00321FE0(char *);

void func_PAL_L00_003D9580(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (func_PAL_00322DA0(self) != 0) {
        func_0029F338(self);
        return;
    }

    if (D_L00_001A8F00 == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0
            && func_00282C48(*(float *)(self + 0x18) - *(float *)(vars + 0x238)) < 2.0f && D_L00_001A8F00 != 2) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                func_PAL_002A7E68(self, 1, 0, 3);
            if (*(int *)(vars + 0x288) != -1) {
                func_002A7750(self, 0xA, 1);
                if (*(u8 *)(self + 0x43) != 0x1A)
                    func_PAL_002A7E68(self, 0x1A, 0, 3);
            }
        } else if (*(s16 *)(vars + 0x276) != 0) {
            func_002A7750(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 250)
                *(s16 *)(vars + 0x270) = (((int)(func_002A7820(480, 600)) * 5 + 2) / 6);
        }
        break;
    case 2: {
        char *hit;
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            func_002A7750(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                func_PAL_002A7E68(self, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2B0) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            func_002A7750(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                func_PAL_002A7E68(self, 0x19, 0, 3);
            *(int *)(vars + 0x2B0) = 1;
        }
        hit = func_002A9640(*(char **)(vars + 0x2AC), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2AC) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xc;
            if (*(int *)(vars + 0x2B0) == 0) {
                func_002A7750(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    func_PAL_002A7E68(self, 0x19, 0, 3);
                *(int *)(vars + 0x2B0) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                func_002A7750(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2AC) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x43) != 1)
                func_PAL_002A7E68(self, 1, 0, 3);
        } else if (*(s16 *)(vars + 0x270) == 0) {
            func_002A7750(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 3)
                func_PAL_002A7E68(self, 3, 0, 0x8);
        }
        break;
    case 4:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    func_PAL_002A7E68(self, 6, 0, 0x8);
                *(s16 *)(vars + 0x270) = (((int)(func_002A7820(580, 600)) * 5 + 2) / 6);
            }
        }
        break;
    case 5: {
        int flags = func_002B1C20(self, vars + 0x60);
        int index = *(int *)(vars + 0x2C0);
        if (index != -1) {
            u8 *slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                func_002E59F8(index);
        }
        *(int *)(vars + 0x2C0) = -1;
        if ((flags & 1) || *(float *)(vars + 0x20) <= 0.0f) {
            char *child;
            func_002E5CF8(0xC, 0, self);
            child = *(char **)(vars + 0x2AC);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                func_0029F338(child);
            *(Quad003D54B0 *)v = 0;
            v[2] = 0.75f;
            *(u16 *)(self + 0x34) |= 0x41;
            *(u16 *)(self + 0x34) &= ~0x1000;
            *(int *)(self + 0x98) = 0;
            func_00283098(v, v, self + 0xC0);
            func_00282CC0(v, v, self + 0x10);
            func_PAL_L00_003FB330(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);
            func_PAL_003240E8(self);
            func_PAL_002A7650(self, 0, 3);
            func_0029F338(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                func_002A7750(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    func_PAL_002A7E68(self, 0x1C, 0, 0x8);
            } else {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 6)
                    func_PAL_002A7E68(self, 6, 0, 0x8);
                *(s16 *)(vars + 0x270) = (((int)(func_002A7820(580, 600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2BC) == 0)
            func_PAL_002B5E10(self);
        break;
    case 3:
        func_002AEF28(self, vars + 0x2A4, vars + 0x2A8, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5: {
        u8 *slot = D_00188660 + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        *(int *)(vars + 0x2A0) += 1;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = func_002E5CF8(0xD, 4, self);
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        func_002AA3A8(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        y = *(float *)(self + 0x18);
        if (y - height > 0.05f) {
            *(float *)(self + 0x18) = y - height * 0.00025f;
        } else {
            int index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *other = D_00188660 + index * 0x70;
                if (*(char **)(other + 0x88) == self && other[0x74] != 0)
                    func_002E59F8(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                func_PAL_002A7E68(self, 0xE, 0, 2);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                func_PAL_002A7E68(self, 0x1A, 0, 0xc);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2A0) += 1;
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        func_002AA3A8(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            func_002AA548(self + 0x18, vars + 0x280, height, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            int index;
            char *child;
            func_0026FEB8(D_L00_001B0318, *(int *)(vars + 0x2A0));
            index = *(int *)(vars + 0x2C0);
            if (index != -1) {
                u8 *slot = D_00188660 + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    func_002E59F8(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                func_PAL_002A7E68(self, 0xE, 0, 2);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2AC);
            if (*(s16 *)(child + 0xAA) == 0xAB7)
                func_0029F338(child);
            *(float *)(vars + 0x30) = 0.5f;
            *(u16 *)(self + 0x34) |= 0x1000;
        }
        break;
    }
    case 6:
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 7, -1);
            if (*(u8 *)(self + 0x43) != 0xD)
                func_PAL_002A7E68(self, 0xD, 0, 0xc);
        }
        break;
    case 7: {
        float height;
        float above;
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        func_002833F0(self + 0xC0, self + 0xF0);
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            func_002AA548(self + 0x18, vars + 0x280, height, 0.030000001f, 0.19600002f, 0.3f);
        } else {
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xE)
                func_PAL_002A7E68(self, 0xE, 0, 2);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 0x1C)
                func_PAL_002A7E68(self, 0x1C, 0, 0xc);
            *(float *)(self + 0x18) = func_002A89A8(self + 0x10, 0, 0.5f);
        }
        break;
    case 10:
        qcopy(v, vars + 0x380);
        v[2] -= 3.0f;
        func_00282CF0(w, v, self + 0x10);
        *(float *)(self + 0xF8) = func_00283248(w[0], w[1]);
        *(float *)(self + 0xF4) = func_00283248(func_00282E20(w), w[2]);
        func_002833F0(self + 0xC0, self + 0xF0);
        func_002AA458(self + 0x10, v, vars + 0x280, 0.020000001f, 0.0f, 0.40000004f);
        if (func_00282E48(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xD)
                func_PAL_002A7E68(self, 0xD, 0, 0x8);
            func_002A7750(self, 7, -1);
        }
        break;
    case 11:
        func_PAL_002B5E10(self);
        if (*(u8 *)(self + 0x60) & 2) {
            func_002B60B0(self, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
            func_002A7750(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0x1C)
                func_PAL_002A7E68(self, 0x1C, 0, 0xc);
        }
        break;
    case 12:
        func_002B60B0(self, 0.0016000001f, 0.040000003f, 0.0016755164f, 0.12566373f);
        if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
            && func_00283C80(*(float *)(self + 0xF8),
                             func_00283248(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                           *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.38397247f) {
        } else if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            func_PAL_002B5BA8(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            func_PAL_002B5C98(self, self + 0x10,
                          func_00283248(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (*(u8 *)(self + 0x42) == 0x1C)
            func_PAL_00323D48(*(float *)(vars + 0x298), self, D_L00_001A8F20, 4);
        break;
    case 13: {
        char *target;
        if (*(u8 *)(self + 0x42) == 0xF)
            func_0027CFD0(func_003225C0, self);
        target = *(char **)(vars + 0x240);
        func_PAL_002B5C98(self, self + 0x10,
                      func_00283248(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                    *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        break;
    }
    case 14:
        if (*(u8 *)(self + 0x60) & 2) {
            if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0x1C)
                    func_PAL_002A7E68(self, 0x1C, 0, 0x8);
            } else {
                func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 7)
                    func_PAL_002A7E68(self, 7, 0, 0x8);
            }
        }
        break;
    }
    func_PAL_00323538(self);
    func_0027CFD0(func_00321FE0, self);
}
