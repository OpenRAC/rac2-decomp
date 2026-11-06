/* func_PAL_00324378, the PAL copy of func_00322CC0: the same C at 50 Hz, where per-frame rates
 * grow by 6/5 (accelerations by 36/25) and frame counts x become (x * 5 + 2) / 6.
 * D_001A8BB0 is reached through the assembler's address macro (MACRO_ADDR), as in the template.
 * A unit of its own: the two switches' jump tables, and this template's prototypes differ from
 * those 00323D48.c declares for the same callees.
 */
#include "common.h"

typedef int Quad00324378 __attribute__((mode(TI)));

extern int D_001A8BB0 MACRO_ADDR;
extern char D_00189EA0[];
extern char *D_0018C2BC;
extern u8 D_00188660[];
extern u32 D_001F1700[];
extern char D_001B0020[];

extern int func_PAL_00326010(char *);
extern void func_0029F338(void *);
extern void func_PAL_002B5E30(char *object, float factor);
extern int func_002B3890(char *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_00282948(void *);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern void *func_002A9640(void *, u32, s32);
extern int func_PAL_002B27B8(char *, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00325D30(char *, char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_PAL_0032DF28(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
extern void func_PAL_002A7650(char *, int, int);
extern void func_002A8C28(char *, char *, int, int, int, int, float, float, float);
extern void func_PAL_002AD288(char *, char *, float, float, int);
extern int func_PAL_002B5E10(char *);
extern float func_002AA2E8(void *, float, float);
extern void func_PAL_002AF420(char *, char *, float, float);
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
extern int func_PAL_002B6CD8(char *, u32);
extern float func_00283C80(float, float);
extern int func_PAL_002B5BA8(char *, void *, float);
extern int func_PAL_002B5C98(char *, void *, float);
extern float func_0029F530(char *);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_0027CDC8(void (*)(char *), char *);
extern void func_00325A88(char *);
extern void func_00325B28(char *);
extern void func_PAL_003268C0(char *);

void func_PAL_00324378(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (func_PAL_00326010(self) != 0) {
        func_0029F338(self);
        return;
    }

    if (*(u8 *)(self + 0x20) != 0xC && *(u8 *)(self + 0x95) != 2)
        func_PAL_002B5E30(self, *(float *)(self + 0xF8));

    if (D_001A8BB0 == 2) {
        *(u16 *)(self + 0x34) |= 0x41;
        *(u16 *)(self + 0x34) &= ~0x1000;
        *(int *)(self + 0x98) = 0;
        if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A4) + 0x98) = 0;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x41;
            *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x1000;
            *(int *)(*(char **)(vars + 0x2A0) + 0x98) = 0;
        }
        return;
    }

    *(u16 *)(self + 0x34) &= ~0x41;
    *(u16 *)(self + 0x34) |= 0x1000;
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    if (*(char **)(vars + 0x2A0) != 0 && *(char **)(vars + 0x2A4) != 0) {
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A4) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A4) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A4) + 0x24) + 0x10);
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) &= ~0x41;
        *(u16 *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x1000;
        *(int *)(*(char **)(vars + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A0) + 0x24) + 0x10);
    }

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && D_001A8BB0 != 2) {
            if (func_00282948(vars + 0x2D0) != 0) {
                func_002A7750(self, 0xB, 4);
                if (*(u8 *)(self + 0x42) == 0) {
                    if (*(u8 *)(self + 0x43) != 1)
                        func_PAL_002A7E68(self, 1, 0, 3);
                } else if (*(u8 *)(self + 0x43) != 5) {
                    int a = func_002A77E0(2);
                    func_PAL_002A7E68(self, 5, a, (func_002A7820(10, 20) * 5 + 2) / 6);
                }
                if (*(int *)(vars + 0x288) != -1) {
                    func_002A7750(self, 0xA, 1);
                    if (*(u8 *)(self + 0x43) != 0x1A)
                        func_PAL_002A7E68(self, 0x1A, 0, 3);
                }
            }
        } else if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    func_PAL_002A7E68(self, 1, 0, 3);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = func_002A77E0(2);
                func_PAL_002A7E68(self, 5, a, (func_002A7820(10, 20) * 5 + 2) / 6);
            }
            *(int *)(vars + 0x294) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0) {
            func_002A7750(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 250)
                *(s16 *)(vars + 0x270) = (func_002A7820(480, 600) * 5 + 2) / 6;
        }
        break;
    case 2: {
        char *hit;
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        *(int *)(self + 0x98) = 0;
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            if (func_00282948(vars + 0x2D0) != 0) {
                func_002A7750(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    func_PAL_002A7E68(self, 0x19, 0, 3);
                *(int *)(vars + 0x2E4) = 1;
            }
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            func_002A7750(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                func_PAL_002A7E68(self, 0x19, 0, 3);
            *(int *)(vars + 0x2E4) = 1;
        }
        hit = func_002A9640(*(char **)(vars + 0x2E0), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2E0) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xC;
            if (*(int *)(vars + 0x2E4) == 0) {
                func_002A7750(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    func_PAL_002A7E68(self, 0x19, 0, 3);
                *(int *)(vars + 0x2E4) = 1;
            }
            if (*(float *)(vars + 0x20) <= 0.0f)
                func_002A7750(self, 0xF, 5);
        }
        qcopy(*(char **)(vars + 0x2E0) + 0x10, self + 0x10);
        break;
    }
    case 3:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0
            && ((float *)D_00189EA0)[2] - *(float *)(self + 0x18) < 3.25f) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    func_PAL_002A7E68(self, 1, 0, 3);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = func_002A77E0(2);
                func_PAL_002A7E68(self, 5, a, (func_002A7820(10, 20) * 5 + 2) / 6);
            }
        } else if (*(s16 *)(vars + 0x270) == 0) {
            func_002A7750(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 4)
                func_PAL_002A7E68(self, 4, 0, 0x8);
        }
        break;
    case 4:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        if ((*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1)
            || *(float *)(vars + 0x238) - *(float *)(self + 0x18) >= 3.25f) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7) {
                    int a = func_002A77E0(2);
                    func_PAL_002A7E68(self, 7, a, (func_002A7820(10, 20) * 5 + 2) / 6);
                }
                *(s16 *)(vars + 0x270) = (func_002A7820(580, 600) * 5 + 2) / 6;
            }
        }
        break;
    case 5: {
        int flags = func_PAL_002B27B8(self, vars + 0x60);
        if ((flags & 1) || (*(float *)(vars + 0x20) <= 0.0f && *(int *)(vars + 0x2EC) == 0)) {
            char *child;
            func_002E5CF8(0xD, 0, self);
            func_00325D30(self, vars + 0x2A0);
            child = *(char **)(vars + 0x2E0);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                func_0029F338(child);
            *(Quad00324378 *)v = 0;
            v[2] = 0.75f;
            func_00283098(v, v, self + 0xC0);
            func_00282CC0(v, v, self + 0x10);
            func_PAL_0032DF28(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);

            func_00282F20(w, vars + 0xE0, 0.060000002f);
            func_PAL_002B15D8(self, 0x3F8, w, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);

            func_PAL_002A7650(self, 0, 3);
            func_0029F338(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                func_002A7750(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_PAL_002A7E68(self, 0xB, 0, 0x8);
            } else {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7)
                    func_PAL_002A7E68(self, 7, 0, 0x8);
                *(s16 *)(vars + 0x270) = (func_002A7820(580, 600) * 5 + 2) / 6;
            }
            if (*(int *)(vars + 0x294) != 1)
                *(int *)(vars + 0x294) = 1;
        }
        if (*(int *)(vars + 0x2EC) != 0)
            func_002A8C28(self, self + 0x10, 0x10000, 0, 1, 0, 0.9f, 0.1f, 1.0f);
        break;
    }
    case 6:
        func_PAL_002B27B8(self, vars + 0x60);
        if ((*(u8 *)(self + 0x60) & 2) || *(float *)(self + 0x18) < 100.0f) {
            func_00325D30(self, vars + 0x2A0);
            func_PAL_002AD288(self, self + 0x10, 0.5f, 13.0f, -1);
            func_PAL_002A7650(self, 0, 3);
            func_0029F338(self);
            return;
        }
        v[0] = 0.0f;
        v[1] = -0.4f;
        v[2] = 0.0f;
        func_00282CC0(self + 0x10, self + 0x10, v);
        break;
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2F0) != 0)
            func_PAL_002B5E10(self);
        break;
    case 2: {
        int anim;
        func_00282948(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 8 && anim != 2 && anim != 4 && anim != 8)
            func_PAL_002A7E68(self, 8, 0, 0xC);
        if (*(int *)(vars + 0x2D8) > 17)
            func_002AA2E8(vars + 0x214, 0.060000002f, 0.0012f);
        else
            func_002AA2E8(vars + 0x214, 0.0f, 0.0012f);
        anim = *(u8 *)(self + 0x43);
        if (anim == 8) {
            if (*(int *)(vars + 0x2D8) == 0) {
                func_PAL_002A7E68(self, 4, 0, 0xA);
                if (func_002A77E0(3) == 1 && *(u8 *)(self + 0x43) != 2)
                    func_PAL_002A7E68(self, 2, 0, 0xA);
            }
            func_PAL_002AF420(self, vars + 0x200, 0.35f, 0.25f);
        } else if (anim == 2 || anim == 4) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = func_002A7820(100, 583);
                if (*(u8 *)(self + 0x43) != 8)
                    func_PAL_002A7E68(self, 8, 0, 0xA);
            }
        }
        break;
    }
    case 3:
        func_002AEF28(self, vars + 0x298, vars + 0x29C, 0.06981318f, 0.062831864f, 0.015707966f);
        break;
    case 5: {
        u8 *slot = D_00188660 + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = func_002E5CF8(0xB, 4, self);
        *(int *)(vars + 0x2BC) += 1;
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
            if (*(u8 *)(self + 0x43) != 0xF)
                func_PAL_002A7E68(self, 0xF, 0, 2);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                func_PAL_002A7E68(self, 0x1A, 0, 0xC);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2BC) += 1;
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        func_002AA3A8(self + 0xF0, 0.0f, vars + 0x290, 0.020000001f, 0.0f, 0.080000006f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            func_002AA548(self + 0x18, vars + 0x280, height, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            int index = *(int *)(vars + 0x2C0);
            char *child;
            if (index != -1) {
                u8 *slot = D_00188660 + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    func_002E59F8(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            func_0026FEB8(D_001B0020, *(int *)(vars + 0x2BC));
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                func_PAL_002A7E68(self, 0xF, 0, 2);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            child = *(char **)(vars + 0x2E0);
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
            if (*(u8 *)(self + 0x43) != 0xE)
                func_PAL_002A7E68(self, 0xE, 0, 0xC);
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
            if (*(u8 *)(self + 0x43) != 0xF)
                func_PAL_002A7E68(self, 0xF, 0, 2);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 8)
                func_PAL_002A7E68(self, 8, 0, 0xC);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            *(float *)(self + 0x18) = func_002A89A8(self + 0x10, 0, 0.5f);
        }
        break;
    case 9: {
        u8 anim;
        func_00282948(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 0xB && anim != 6 && anim != 7 && anim != 0xB)
            func_PAL_002A7E68(self, 0xB, 0, 0xC);
        if (*(int *)(vars + 0x2D8) > 17)
            func_002AA2E8(vars + 0x214, 0.120000005f, 0.0024f);
        else
            func_002AA2E8(vars + 0x214, 0.0f, 0.0024f);
        if (*(u8 *)(self + 0x43) == 0xB) {
            if (*(int *)(vars + 0x2D8) == 0) {
                func_PAL_002A7E68(self, 6, 0, 0xA);
                if (func_002A77E0(3) == 1 && *(u8 *)(self + 0x43) != 7)
                    func_PAL_002A7E68(self, 7, 0, 0xA);
            }
            func_PAL_002AF420(self, vars + 0x200, 0.35f, 0.25f);
        } else if (*(u8 *)(self + 0x43) == 6 || *(u8 *)(self + 0x43) == 7) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = func_002A7820(100, 167);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_PAL_002A7E68(self, 0xB, 0, 0xA);
            }
        }
        break;
    }
    case 10:
        qcopy(v, vars + 0x300);
        v[2] -= 3.0f;
        func_00282CF0(w, v, self + 0x10);
        *(float *)(self + 0xF8) = func_00283248(w[0], w[1]);
        *(float *)(self + 0xF4) = func_00283248(func_00282E20(w), w[2]);
        func_002833F0(self + 0xC0, self + 0xF0);
        func_002AA458(self + 0x10, v, vars + 0x280, 0.020000001f, 0.0f, 0.40000004f);
        if (func_00282E48(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xE)
                func_PAL_002A7E68(self, 0xE, 0, 0x8);
            func_002A7750(self, 7, -1);
        }
        break;
    case 11:
        func_PAL_002B5E10(self);
        if (*(u8 *)(self + 0x60) & 2) {
            func_002B60B0(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            func_002A7750(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0xB)
                func_PAL_002A7E68(self, 0xB, 0, 0xC);
        }
        break;
    case 12:
        if (*(int *)(vars + 0x2F8) != -1) {
            if (func_PAL_002B6CD8(self, D_001F1700[*(int *)(vars + 0x2F8)]) != 0
                || func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f)
                *(int *)(vars + 0x2F8) = -1;
        } else if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
                   && func_00283C80(*(float *)(self + 0xF8),
                                    func_00283248(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                                  *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.20943953f) {
            func_002A7750(self, 0xD, -1);
            if (*(u8 *)(self + 0x43) != 0x1B)
                func_PAL_002A7E68(self, 0x1B, 0, 5);
            if (func_002A77E0(2) == 1) {
                if (*(u8 *)(self + 0x43) != 0x10)
                    func_PAL_002A7E68(self, 0x10, 0, 5);
            }
            *(int *)(vars + 0x2B0) = 0;
        } else if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            func_PAL_002B5BA8(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            func_PAL_002B5C98(self, self + 0x10,
                          func_00283248(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 5.0f && *(u8 *)(self + 0x42) == 8) {
            if (*(u8 *)(self + 0x43) != 0xB)
                func_PAL_002A7E68(self, 0xB, 0, 3);
            func_002B60B0(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
        }
        break;
    case 13: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            *(float *)(vars + 0x2E8) = 8.0f;
            if (D_0018C2BC == self) {
                func_002A7750(self, 0xE, -1);
                if (*(u8 *)(self + 0x43) != 0x11)
                    func_PAL_002A7E68(self, 0x11, 0, 6);
            } else if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                func_002B60B0(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_PAL_002A7E68(self, 0xB, 0, 0x8);
            } else {
                func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    func_PAL_002A7E68(self, 8, 0, 0x8);
            }
        }
        func_PAL_002B5E10(self);
        frame = func_0029F530(self);
        if (*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) {
            if (frame >= 19.0f && frame <= 25.0f) {
                func_002A8D70(self, 0, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                func_002A8D70(self, 1, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                func_002A8D70(self, 2, 0.15f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
                func_002A8D70(self, 9, 0.35f, *(float *)(vars + 0x2CC), 1, 1.0f, 0, 1, 0);
            }
        }
        if ((*(u8 *)(self + 0x42) == 0x1B || *(u8 *)(self + 0x42) == 0x10) && frame >= 17.0f && frame <= 25.0f) {
            func_0027CDC8(func_00325B28, self);
            func_00325A88(self);
            *(float *)(vars + 0x2E8) = 25.0f;
        }
        break;
    }
    case 14: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            if (func_00282E80(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                func_002B60B0(self, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_PAL_002A7E68(self, 0xB, 0, 0x8);
            } else {
                func_002B60B0(self, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    func_PAL_002A7E68(self, 8, 0, 0x8);
            }
        }
        func_PAL_002B5E10(self);
        frame = func_0029F530(self);
        if (*(u8 *)(self + 0x42) == 0x11 && (frame <= 5.0f || (frame >= 12.0f && frame <= 15.0f)))
            *(int *)(vars + 0x2C4) = 1;
        else
            *(int *)(vars + 0x2C4) = 0;
        break;
    }
    }
    func_PAL_003268C0(self);
}
