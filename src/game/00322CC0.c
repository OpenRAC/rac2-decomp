/* func_00322CC0: boot + 6 levels (00, 02, 07, 11, 14, 26).
 * D_001A8BB0 is reached through the assembler's address macro (MACRO_ADDR): the entry read
 * at the join expands to lui/lw in flow, and reorg's copy of it in the state-2 branch's delay
 * slot is the $gp form.  SpawnExplosion returns a pointer (void *).
 */
#include "common.h"

typedef int Quad00322CC0 __attribute__((mode(TI)));

extern int D_001A8BB0 MACRO_ADDR;
extern char D_00189EA0[];
extern char *D_0018C2BC;
extern u8 D_00188660[];
extern u32 D_001F1700[];
extern char D_001B0020[];

extern int func_003248A8(char *);
extern void func_0029F338(void *);
extern void func_002B5278(char *object, float factor);
extern int func_002B3890(char *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_00282948(void *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_00282E80(void *, void *);
extern void *func_002A9640(void *, u32, s32);
extern int func_002B1C20(char *, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00325D30(char *, char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern void func_002A6C58(char *, int, int);
extern void func_002A8C28(char *, char *, int, int, int, int, float, float, float);
extern void func_002AC728(char *, char *, float, float, int);
extern int func_002B5258(char *);
extern float func_002AA2E8(void *, float, float);
extern void func_002AE8C0(char *, char *, float, float);
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
extern int func_002B6120(char *, u32);
extern float func_00283C80(float, float);
extern int func_002B4FF0(char *, void *, float);
extern int func_002B50E0(char *, void *, float);
extern float func_0029F530(char *);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_0027CDC8(void (*)(char *), char *);
extern void func_00325A88(char *);
extern void func_00325B28(char *);
extern void func_00325158(char *);

void func_00322CC0(char *self)
{
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);

    if (func_003248A8(self) != 0) {
        func_0029F338(self);
        return;
    }

    if (*(u8 *)(self + 0x20) != 0xC && *(u8 *)(self + 0x95) != 2)
        func_002B5278(self, *(float *)(self + 0xF8));

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
            func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && D_001A8BB0 != 2) {
            if (func_00282948(vars + 0x2D0) != 0) {
                func_002A7750(self, 0xB, 4);
                if (*(u8 *)(self + 0x42) == 0) {
                    if (*(u8 *)(self + 0x43) != 1)
                        func_002A7470(self, 1, 0, 4);
                } else if (*(u8 *)(self + 0x43) != 5) {
                    int a = func_002A77E0(2);
                    func_002A7470(self, 5, a, func_002A7820(10, 20));
                }
                if (*(int *)(vars + 0x288) != -1) {
                    func_002A7750(self, 0xA, 1);
                    if (*(u8 *)(self + 0x43) != 0x1A)
                        func_002A7470(self, 0x1A, 0, 4);
                }
            }
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    func_002A7470(self, 1, 0, 4);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = func_002A77E0(2);
                func_002A7470(self, 5, a, func_002A7820(10, 20));
            }
            *(int *)(vars + 0x294) = 1;
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0) {
            func_002A7750(self, 9, 3);
            *(s16 *)(vars + 0x276) = 0;
            if (*(s16 *)(vars + 0x270) < 300)
                *(s16 *)(vars + 0x270) = func_002A7820(480, 600);
        }
        break;
    case 2: {
        char *hit;
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        *(int *)(self + 0x98) = 0;
        if (*(int *)(vars + 0x258) == 1 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            if (func_00282948(vars + 0x2D0) != 0) {
                func_002A7750(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    func_002A7470(self, 0x19, 0, 4);
                *(int *)(vars + 0x2E4) = 1;
            }
        } else if (*(s16 *)(vars + 0x276) != 0 && *(int *)(vars + 0x294) != 0 && *(int *)(vars + 0x2E4) == 0) {
            *(s16 *)(vars + 0x276) = 0;
            func_002A7750(self, 5, -1);
            if (*(u8 *)(self + 0x43) != 0x19)
                func_002A7470(self, 0x19, 0, 4);
            *(int *)(vars + 0x2E4) = 1;
        }
        hit = func_002A9640(*(char **)(vars + 0x2E0), 0x10000, 0);
        if (hit != 0 && *(s16 *)(vars + 0x26) <= 0) {
            *(float *)(vars + 0x20) -= *(float *)(hit + 0x2C);
            *(u8 *)(*(char **)(vars + 0x2E0) + 0xA8) = 0xFF;
            *(s16 *)(vars + 0x26) = 0xF;
            if (*(int *)(vars + 0x2E4) == 0) {
                func_002A7750(self, 5, -1);
                if (*(u8 *)(self + 0x43) != 0x19)
                    func_002A7470(self, 0x19, 0, 4);
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
            func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if ((*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) && *(int *)(vars + 0x294) != 0
            && ((float *)D_00189EA0)[2] - *(float *)(self + 0x18) < 3.25f) {
            func_002A7750(self, 0xB, 4);
            if (*(u8 *)(self + 0x42) == 0) {
                if (*(u8 *)(self + 0x43) != 1)
                    func_002A7470(self, 1, 0, 4);
            } else if (*(u8 *)(self + 0x43) != 5) {
                int a = func_002A77E0(2);
                func_002A7470(self, 5, a, func_002A7820(10, 20));
            }
        } else if (*(s16 *)(vars + 0x270) == 0) {
            func_002A7750(self, 2, 0);
            if (*(u8 *)(self + 0x43) != 4)
                func_002A7470(self, 4, 0, 0xA);
        }
        break;
    case 4:
        if (func_002B3890(self) != 0)
            func_002B60B0(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if ((*(int *)(vars + 0x258) != 1 && *(int *)(vars + 0x25C) != 1)
            || *(float *)(vars + 0x238) - *(float *)(self + 0x18) >= 3.25f) {
            if (*(u8 *)(self + 0x20) != 5) if (*(u8 *)(self + 0x20) != 4) {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7) {
                    int a = func_002A77E0(2);
                    func_002A7470(self, 7, a, func_002A7820(10, 20));
                }
                *(s16 *)(vars + 0x270) = func_002A7820(580, 600);
            }
        }
        break;
    case 5: {
        int flags = func_002B1C20(self, vars + 0x60);
        if ((flags & 1) || (*(float *)(vars + 0x20) <= 0.0f && *(int *)(vars + 0x2EC) == 0)) {
            char *child;
            PlayMobySound(0xD, 0, self);
            func_00325D30(self, vars + 0x2A0);
            child = *(char **)(vars + 0x2E0);
            if (child != 0 && *(s16 *)(child + 0xAA) == 0xAB7)
                func_0029F338(child);
            *(Quad00322CC0 *)v = 0;
            v[2] = 0.75f;
            matrix_mul_vec3(v, v, self + 0xC0);
            FastVecAdd(v, v, self + 0x10);
            SpawnExplosion(v, 0, 5, 5, 5, 0, 0, 0, 0.5f, 20.0f, 1, 0, 0, 0);




            vec_scale_to_length(w, vars + 0xE0, 0.050000004f);
            func_002B0A68(self, 0x3F8, w, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);

            SetDeathBits(self, 0, 3);
            func_0029F338(self);
            return;
        }
        if (flags & 2) {
            if (*(int *)(vars + 0x258) == 1 || *(int *)(vars + 0x25C) == 1) {
                func_002A7750(self, 0xC, 4);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_002A7470(self, 0xB, 0, 0xA);
            } else {
                func_002A7750(self, 9, 3);
                if (*(u8 *)(self + 0x43) != 7)
                    func_002A7470(self, 7, 0, 0xA);
                *(s16 *)(vars + 0x270) = func_002A7820(580, 600);
            }
            if (*(int *)(vars + 0x294) != 1)
                *(int *)(vars + 0x294) = 1;
        }
        if (*(int *)(vars + 0x2EC) != 0)
            func_002A8C28(self, self + 0x10, 0x10000, 0, 1, 0, 0.9f, 0.1f, 1.0f);
        break;
    }
    case 6:
        func_002B1C20(self, vars + 0x60);
        if ((*(u8 *)(self + 0x60) & 2) || *(float *)(self + 0x18) < 100.0f) {
            func_00325D30(self, vars + 0x2A0);
            func_002AC728(self, self + 0x10, 0.5f, 13.0f, -1);
            SetDeathBits(self, 0, 3);
            func_0029F338(self);
            return;
        }
        v[0] = 0.0f;
        v[1] = -0.4f;
        v[2] = 0.0f;
        FastVecAdd(self + 0x10, self + 0x10, v);
        break;
    }

    switch (*(u8 *)(self + 0x20)) {
    case 1:
        if (*(int *)(vars + 0x2F0) != 0)
            func_002B5258(self);
        break;
    case 2: {
        int anim;
        func_00282948(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 8 && anim != 2 && anim != 4 && anim != 8)
            func_002A7470(self, 8, 0, 0xE);
        if (*(int *)(vars + 0x2D8) > 20)
            ApproachValue(vars + 0x214, 0.050000004f, 0.00083333335f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.00083333335f);
        anim = *(u8 *)(self + 0x43);
        if (anim == 8) {
            if (*(int *)(vars + 0x2D8) == 0) {
                func_002A7470(self, 4, 0, 0xC);
                if (func_002A77E0(3) == 1 && *(u8 *)(self + 0x43) != 2)
                    func_002A7470(self, 2, 0, 0xC);
            }
            func_002AE8C0(self, vars + 0x200, 0.35f, 0.25f);
        } else if (anim == 2 || anim == 4) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = func_002A7820(120, 700);
                if (*(u8 *)(self + 0x43) != 8)
                    func_002A7470(self, 8, 0, 0xC);
            }
        }
        break;
    }
    case 3:
        func_002AEF28(self, vars + 0x298, vars + 0x29C, 0.06981318f, 0.052359886f, 0.013089972f);
        break;
    case 5: {
        u8 *slot = D_00188660 + *(int *)(vars + 0x2C0) * 0x70;
        float height;
        float y;
        if (*(char **)(slot + 0x88) != self || slot[0x74] == 0)
            *(int *)(vars + 0x2C0) = PlayMobySound(0xB, 4, self);
        *(int *)(vars + 0x2BC) += 1;
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        func_002AA3A8(self + 0xF0, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
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
                func_002A7470(self, 0xF, 0, 3);
        }
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 4, -1);
            if (*(u8 *)(self + 0x43) != 0x1A)
                func_002A7470(self, 0x1A, 0, 0xF);
        }
        break;
    }
    case 4: {
        float height;
        float above;
        *(int *)(vars + 0x2BC) += 1;
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        func_002AA3A8(self + 0xF0, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            func_002AA548(self + 0x18, vars + 0x280, height, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            int index = *(int *)(vars + 0x2C0);
            char *child;
            if (index != -1) {
                u8 *slot = D_00188660 + index * 0x70;
                if (*(char **)(slot + 0x88) == self && slot[0x74] != 0)
                    func_002E59F8(index);
            }
            *(int *)(vars + 0x2C0) = -1;
            STUB_printf(D_001B0020, *(int *)(vars + 0x2BC));
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                func_002A7470(self, 0xF, 0, 3);
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
                func_002A7470(self, 0xE, 0, 0xF);
        }
        break;
    case 7: {
        float height;
        float above;
        func_002AA3A8(self + 0xF4, 0.0f, vars + 0x290, 0.016666668f, 0.0f, 0.06666667f);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        func_002A7E08(self, *(char **)(vars + 0x240), vars + 0x28C, 0.001f, 0.01f, 0.1f);
        height = func_002A89A8(self + 0x10, 0, 0.5f);
        above = *(float *)(self + 0x18) - height;
        height -= 3.0f;
        if (above > 0.05f) {
            func_002AA548(self + 0x18, vars + 0x280, height, 0.025000002f, 0.16333334f, 0.25f);
        } else {
            func_002A7750(self, 8, -1);
            if (*(u8 *)(self + 0x43) != 0xF)
                func_002A7470(self, 0xF, 0, 3);
        }
        break;
    }
    case 8:
        if (*(u8 *)(self + 0x60) & 2) {
            func_002A7750(self, 0xC, 4);
            if (*(u8 *)(self + 0x43) != 8)
                func_002A7470(self, 8, 0, 0xF);
            *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
            *(float *)(self + 0x18) = func_002A89A8(self + 0x10, 0, 0.5f);
        }
        break;
    case 9: {
        u8 anim;
        func_00282948(vars + 0x2D8);
        anim = *(u8 *)(self + 0x43);
        if (anim != 0xB && anim != 6 && anim != 7 && anim != 0xB)
            func_002A7470(self, 0xB, 0, 0xE);
        if (*(int *)(vars + 0x2D8) > 20)
            ApproachValue(vars + 0x214, 0.10000001f, 0.0016666667f);
        else
            ApproachValue(vars + 0x214, 0.0f, 0.0016666667f);
        if (*(u8 *)(self + 0x43) == 0xB) {
            if (*(int *)(vars + 0x2D8) == 0) {
                func_002A7470(self, 6, 0, 0xC);
                if (func_002A77E0(3) == 1 && *(u8 *)(self + 0x43) != 7)
                    func_002A7470(self, 7, 0, 0xC);
            }
            func_002AE8C0(self, vars + 0x200, 0.35f, 0.25f);
        } else if (*(u8 *)(self + 0x43) == 6 || *(u8 *)(self + 0x43) == 7) {
            if (*(u8 *)(self + 0x60) & 2) {
                *(int *)(vars + 0x2D8) = func_002A7820(120, 200);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_002A7470(self, 0xB, 0, 0xC);
            }
        }
        break;
    }
    case 10:
        qcopy(v, vars + 0x300);
        v[2] -= 3.0f;
        FastVecSub(w, v, self + 0x10);
        *(float *)(self + 0xF8) = func_00283248(w[0], w[1]);
        *(float *)(self + 0xF4) = func_00283248(vec_length_xy(w), w[2]);
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        func_002AA458(self + 0x10, v, vars + 0x280, 0.016666668f, 0.0f, 0.33333334f);
        if (fast_vec_dist(self + 0x10, v) < 0.4f) {
            if (*(u8 *)(self + 0x43) != 0xE)
                func_002A7470(self, 0xE, 0, 0xA);
            func_002A7750(self, 7, -1);
        }
        break;
    case 11:
        func_002B5258(self);
        if (*(u8 *)(self + 0x60) & 2) {
            func_002B60B0(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            func_002A7750(self, 0xC, -1);
            if (*(u8 *)(self + 0x43) != 0xB)
                func_002A7470(self, 0xB, 0, 0xF);
        }
        break;
    case 12:
        if (*(int *)(vars + 0x2F8) != -1) {
            if (func_002B6120(self, D_001F1700[*(int *)(vars + 0x2F8)]) != 0
                || vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) <= 3.4f)
                *(int *)(vars + 0x2F8) = -1;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) < 2.8f
                   && FastDiffRots(*(float *)(self + 0xF8),
                                    func_00283248(*(float *)(vars + 0x230) - *(float *)(self + 0x10),
                                                  *(float *)(vars + 0x234) - *(float *)(self + 0x14))) < 0.20943953f) {
            func_002A7750(self, 0xD, -1);
            if (*(u8 *)(self + 0x43) != 0x1B)
                func_002A7470(self, 0x1B, 0, 6);
            if (func_002A77E0(2) == 1) {
                if (*(u8 *)(self + 0x43) != 0x10)
                    func_002A7470(self, 0x10, 0, 6);
            }
            *(int *)(vars + 0x2B0) = 0;
        } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 2.8f) {
            func_002B4FF0(self, vars + 0x230, *(float *)(vars + 0x284));
        } else {
            char *target = *(char **)(vars + 0x240);
            func_002B50E0(self, self + 0x10,
                          func_00283248(*(float *)(target + 0x10) - *(float *)(self + 0x10),
                                        *(float *)(target + 0x14) - *(float *)(self + 0x14)));
        }
        if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 5.0f && *(u8 *)(self + 0x42) == 8) {
            if (*(u8 *)(self + 0x43) != 0xB)
                func_002A7470(self, 0xB, 0, 4);
            func_002B60B0(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        }
        break;
    case 13: {
        float frame;
        if (*(u8 *)(self + 0x60) & 2) {
            *(float *)(vars + 0x2E8) = 8.0f;
            if (D_0018C2BC == self) {
                func_002A7750(self, 0xE, -1);
                if (*(u8 *)(self + 0x43) != 0x11)
                    func_002A7470(self, 0x11, 0, 7);
            } else if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                func_002B60B0(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_002A7470(self, 0xB, 0, 0xA);
            } else {
                func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    func_002A7470(self, 8, 0, 0xA);
            }
        }
        func_002B5258(self);
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
            if (vec_distance_xy(self + 0x10, *(char **)(vars + 0x240) + 0x10) > 4.0f) {
                func_002B60B0(self, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 0xB)
                    func_002A7470(self, 0xB, 0, 0xA);
            } else {
                func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                func_002A7750(self, 0xC, -1);
                if (*(u8 *)(self + 0x43) != 8)
                    func_002A7470(self, 8, 0, 0xA);
            }
        }
        func_002B5258(self);
        frame = func_0029F530(self);
        if (*(u8 *)(self + 0x42) == 0x11 && (frame <= 5.0f || (frame >= 12.0f && frame <= 15.0f)))
            *(int *)(vars + 0x2C4) = 1;
        else
            *(int *)(vars + 0x2C4) = 0;
        break;
    }
    }
    func_00325158(self);
}
