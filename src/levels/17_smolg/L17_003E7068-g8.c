#include "common.h"

/* func_L17_003E7068 has a unit of its own for two flags (config/cflags.txt):
 * -frac2-gcse-unsplit-edges lets PRE put the &v30 copy before the state switch's
 * bounds check, as GCC 2.95 does, instead of in a split-off default block; and
 * -fmove-all-movables hoists the case 8 loop's D_L17_001C0020 address in loop.c's
 * first pass, ahead of st + 0x710, which decides the loop's s1/s5 allocation.
 * The pool reads use Moby member access (index scaled first), the address-of
 * uses plain pointer sums (base first), as retail's operand order shows. */
typedef union { u8 b[0x2000]; s8 c[0x2000]; s16 h[0x1000]; u16 uh[0x1000]; s32 i[0x800]; u32 u[0x800]; f32 f[0x800]; void *p[0x800]; } UView;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
typedef struct { float sn, cs, one, big; void *obj; int flags; u8 z, o; u16 id; float val; int k; } Hit;
extern void func_0026FEB8(const char *, ...);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00282948(void *);
extern int func_00282978(short *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern void func_0029F338(void *);
extern float func_0029F530(u8 *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(u8 *, int, int);
extern int func_002A77E0(int);
extern float func_002A89A8(void *, int, float);
extern int func_002A8D70(float, float, float, void *, int, int, int, int, int);
extern void func_002AA800(void *, int, float, float);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(u8 *);
extern int func_002B3890(u8 *);
extern int func_002B50E0(void *, void *, float);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L01_00321178(void *, void *);
extern void func_L01_003E9CF8(u8 *, int, void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, float, float);
extern void func_L02_0032EF10(void *, void *, void *, int, float);
extern void func_L17_0032C070(void *, void *, void *, int, float, float);
extern void func_L17_003C5AF8(u8 *);
extern int func_L17_003C5B68(u8 *);
extern void func_L17_003C7250(u8 *, u8 *);
extern int func_L17_003E6DE8(u8 *);
extern void func_L17_003E6F20(u8 *);
extern int func_L17_003E6F58(u8 *);
extern int func_L17_003E7010(u8 *);
extern void func_L17_003E8A58(void);
extern u8 D_00189E20[];
extern u8 *D_L17_001B2C1C[] __attribute__((sda));
extern int D_L17_001B3940[] __attribute__((sda));
extern u8 *D_L17_001FB720[];
extern u8 *D_L17_001FE880[];
extern Vec D_L17_001B9BC0;
extern Vec D_L17_001C0020;
extern char D_L17_001B0ED0[], D_L17_001B0EE8[], D_L17_001B0F10[], D_L17_001B0F20[];
extern float D_L17_001B0E3C __attribute__((sda));
extern float D_L17_001B0E58 __attribute__((sda));
extern int D_L17_001B0E68 __attribute__((sda));
extern int D_L17_001B0E6C __attribute__((sda));
extern float D_L17_001B0E70 __attribute__((sda));
extern float D_L17_001B0E74 __attribute__((sda));
extern float D_L17_001B0E7C __attribute__((sda));
extern float D_L17_001B0E80 __attribute__((sda));
extern float D_L17_001B0E88 __attribute__((sda));
extern int D_L17_001B0E8C __attribute__((sda));
extern float D_L17_001B0E90 __attribute__((sda));
extern int D_L17_001B0E94 __attribute__((sda));
extern int D_L17_001B0E9C __attribute__((sda));
extern float D_L17_001B0EA4 __attribute__((sda));
extern int D_L17_001B0EA8 __attribute__((sda));
extern float D_L17_001B0EAC __attribute__((sda));
extern float D_L17_001B0EB0 __attribute__((sda));
extern float D_L17_001B0EB4 __attribute__((sda));
extern float D_L17_001B0EB8 __attribute__((sda));
extern int D_L17_001B0EC0 __attribute__((sda));
extern int D_L17_001B0EC4 __attribute__((sda));
extern float D_L17_001B0EC8 __attribute__((sda));

/* Moby update: Two-headed Smolgian snapper (class 3019, PS3 name). */
void func_L17_003E7068(u8 *self) {
    Hit h;
    u8 *st = ((u8 *)((UView *)(self))->p[0x1A]);
    float dist, ang, f20, fa, fb, fc, fd, fe, ff, fg;
    Vec v30, v40, v50;
    float f60;
    int idx, a1, hit, n;
    int idx2, idx3;
    u8 *o2;
    int cnt, hit8, near, hit13;
    float fx;
    Moby *pool;

    func_L17_003E8A58();
    dist = vec_distance_xy(self + 0x10, st + 0x240);
    ang = func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]);
    idx = *(int *)(st + 0x6B8);
    if (idx != -1) {
        if (((Moby *)D_L17_001B2C1C[0])[idx].oclass != 0x929) {
            STUB_printf(D_L17_001B0ED0);
        } else {
            func_L17_003C7250((u8 *)&((Moby *)D_L17_001B2C1C[0])[idx], self);
        }
    }
    switch (self[0x95]) {
    case 5:
        func_002AD0E0(self, D_L17_001B2C1C[0] + (*(int *)(st + 0x6B8) << 8), self + 0x10, self + 0xF0, self + 0x10, self + 0xF0);
        idx2 = *(int *)(st + 0x6DC);
        if (idx2 == -1 || (o2 = D_L17_001B2C1C[0] + (idx2 << 8)) == self || o2 == 0 || o2[0x20] == 0xFE || o2[0x20] == 0xFD) {
            idx3 = *(int *)(st + 0x6B8);
            if (idx3 != -1) {
                if (*(s16 *)(st + 0x69E) == 1 && func_L17_003C5B68(D_L17_001B2C1C[0] + (idx3 << 8))) {
                    func_L17_003C5AF8(D_L17_001B2C1C[0] + (*(int *)(st + 0x6B8) << 8));
                    if (((Moby *)D_L17_001B2C1C[0])[*(int *)(st + 0x6B8)].oclass == 0x929) {
                        if (self[0x20] != 6) func_002A7750(self, 6, -1);
                        pool = (Moby *)D_L17_001B2C1C[0];
                        ((UView *)(self))->uh[0x1A] = ((UView *)(self))->uh[0x1A] & 0xFFBE;
                        ((UView *)(self))->i[0x26] = *(int *)(((u8 *)((UView *)(self))->p[0x9]) + 0x10);
                        ((UView *)(self))->f[0x3E] = pool[*(int *)(st + 0x6B8)].rotz;
                    } else if (self[0x20] != 6) {
                        func_002A7750(self, 6, -1);
                    }
                }
                break;
            }
            goto case0;
        }
        break;
    case 0:
    case0:
        if (*(s16 *)(st + 0x69E) == 1) {
            if (*(int *)(st + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || ClaimNearestObjectSlot(self) != 0) {
                func_002A7750(self, 0xF, 2);
            } else {
                func_002A7750(self, 7, 6);
                if (self[0x43] != 1) func_002A7470(self, 1, 0, D_L17_001B0E9C);
            }
            func_002B60B0(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(s16 *)(st + 0x69C) = 0xC8;
            *(int *)(st + 0x148) = *(int *)(st + 0x148) | 0x10;
        }
        break;
    case 2:
        if (*(s16 *)(st + 0x69E) == 1) *(s16 *)(st + 0x69C) = 0xC8;
        if (FastDecTimer((short *)(st + 0x69C)) != 0) {
            func_002A7750(self, 5, 4);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 3) func_002A7470(self, 3, 0, 0x14);
            *(s16 *)(st + 0x69C) = 0xDC;
        }
        break;
    case 4:
        if (*(s16 *)(st + 0x69E) == 1) goto alert;
        goto b62;
    case 6:
        if (ClaimNearestObjectSlot(self) != 0) {
            if ((self[0x42] != 1 && self[0x43] != 1) || (self[0x60] & 2)) {
alert:
                func_002A7750(self, 0xB, 2);
                func_002B60B0(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
                *(s16 *)(st + 0x69C) = 0xC8;
                *(int *)(st + 0x148) = *(int *)(st + 0x148) | 0x10;
            }
        } else {
            f20 = func_0029F530(self);
            if (*(s16 *)(st + 0x69E) == 1) *(s16 *)(st + 0x69C) = 0xC8;
            if ((self[0x60] & 2) && self[0x42] == 3 && self[0x43] != 0xE) func_002A7470(self, 0xE, 0, D_L17_001B0E9C);
            if (f20 >= 20.0f && self[0x42] == 0xE && self[0x43] != 3) func_002A7470(self, 3, 0, D_L17_001B0E9C);
            if (self[0x60] & 2) {
                if (self[0x42] == 1) {
                    if (self[0x43] != 0xE) func_002A7470(self, 0xE, 0, D_L17_001B0E9C);
                    goto b60;
                }
            } else {
b60:
                if (self[0x42] == 1) {
                    StepAngleTowardTarget(self + 0xF8, 0, func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
                }
            }
b62:
            if (FastDecTimer((short *)(st + 0x69C)) != 0) {
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 2) func_002A7470(self, 2, 0, 0x14);
                func_002A7750(self, 3, 0);
            }
        }
        break;
    case 3:
        if (func_002B3890(self) != 0) {
            fa = ((UView *)(self))->f[0x12];
            if (fa <= 0.0f || fa > 1.0f) ((UView *)(self))->f[0x12] = 1.0f;
            func_002B60B0(self, (float)(D_L17_001B0E68 * 8) * 0.00027777778f, D_L17_001B0E70 * 0.13333334f, 0.10471977f, 0.10471977f);
        }
        if (((UView *)(self))->f[0x6] < D_L17_001B0E3C) goto b262;
        if (*(float *)(st + 0xE8) > 0.016666668f) {
            *(float *)(st + 0xE8) = 0.016666668f;
            STUB_printf(D_L17_001B0F10);
        }
        hit = func_002B1C20(self, st + 0x60);
        if (hit & 1) {
            func_L01_003E9CF8(self, 0, 0);
            SetDeathBits(self, 0, 3);
        }
        fb = func_0029F530(self);
        if (fb >= 13.0f && fb <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, st + 0x240) < D_L17_001B0E58) {
            if (self[0x42] == 4) {
                if (func_L17_003E7010(self) != 0) {
                    h.obj = self;
                    h.flags = 0x10001;
                    h.val = *(float *)(st + 0x700);
                    h.sn = func_00283180(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
                    h.cs = func_00283198(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
                    h.one = 1.0f;
                    h.big = 5627.925f;
                    h.o = h.k = 1;
                    h.z = 0;
                    h.id = ((UView *)(self))->uh[0x55];
                    a1 = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
                    func_002A8D70(D_L17_001B0EC8, *(float *)(st + 0x700), 1.0f, self, a1, 0x10001, 0, 1, 0);
                }
            }
        }
        if ((self[0x42] == 4 || self[0x43] == 4) && !(fb > 13.0f)) {
            func_L01_00321178(self, st + 0x240);
        }
        if ((hit & 2) && D_L17_001B0EB0 <= fb) func_002A7750(self, 0xD, 2);
        if (self[0x42] == 0xD && D_L17_001B0EB4 <= fb) {
            if (self[0x43] != 4) func_002A7470(self, 4, 0, 8);
            *(s16 *)(D_00189E20 + 0x1DC) = 0;
        }
        break;
    }
    switch (self[0x20]) {
    case 3:
        if (func_002B3868(self) != 0) {
            if (func_002A77E0(2) == 0) {
                if (self[0x43] != 2) func_002A7470(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                func_002A7470(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        fg = func_0029F530(self);
        if ((self[0x42] == 2 && (self[0x60] & 2)) || (self[0x42] == 0xE && fg >= 20.0f)) {
            if (func_002A77E0(2) == 0) {
                if (self[0x43] != 2) func_002A7470(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                func_002A7470(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        break;
    case 8:
        if (func_002B3868(self) != 0) {
            cnt = 0;
            do {
                n = func_L17_003E6F58(self);
                qcopy(&v30, self + 0x10);
                qcopy(&v40, &((Vec *)D_L17_001FE880[*(int *)(st + 0x684)])[n + 1]);
                v30.f[2] = v30.f[2] + 1.0f;
                v40.f[2] = v30.f[2];
                if (CollLine(&v30, &v40, 0, self, 0) != 0) {
                    if (!(vec_distance_xy(self + 0x10, &D_L17_001C0020) < 2.0f)) {
                        qcopy(st + 0x710, &D_L17_001C0020);
                        break;
                    }
                } else {
                    qcopy(st + 0x710, &v40);
                    break;
                }
                cnt++;
            } while (cnt < 5);
            if (cnt != 5) {
                if (self[0x43] != 0xC) func_002A7470(self, 0xC, 0, D_L17_001B0E9C);
            } else {
                func_002A7750(self, 3, -1);
                break;
            }
        }
        hit8 = func_L01_00321178(self, st + 0x710);
        StepAngleTowardTarget(self + 0xF8, 0, func_00283248(*(float *)(st + 0x710) - ((UView *)(self))->f[0x4], *(float *)(st + 0x714) - ((UView *)(self))->f[0x5]), 0.043633237f);
        if (!(hit8 & 0x80) && *(int *)(st + 0x190) < 0xB && !(hit8 & 0x10F)) {
        } else {
            func_002A7750(self, 3, -1);
        }
        break;
    case 6:
        if (func_002B3868(self) != 0) {
            if (((Moby *)D_L17_001B2C1C[0])[*(int *)(st + 0x6B8)].oclass != 0x929) {
                if (self[0x43] != 1) func_002A7470(self, 1, 0, D_L17_001B0E9C);
                func_002B60B0(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            } else {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) func_002A7470(self, 0xA, 0, D_L17_001B0E9C);
                func_002B60B0(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            }
            ((UView *)(self))->f[0x6] = func_002A89A8(self + 0x10, 0, 3.0f);
            qcopy(st + 0x6C0, self + 0x10);
        }
        if (self[0x60] & 2) {
            if (self[0x42] == 1) {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) func_002A7470(self, 0xA, 0, 0x14);
                func_L01_00321178(self, self + 0x10);
                goto s6_157;
            }
            goto s6_159;
        }
s6_157:
        if (self[0x42] == 1) {
            ((UView *)(self))->f[0x6] = func_002A89A8(self + 0x10, 0, 3.0f);
            break;
        }
s6_159:
        if (self[0x42] == 0xA) {
            (&v30)->f[0] = func_00283180(((UView *)(self))->f[0x3E]) * 3.0f;
            (&v30)->f[1] = func_00283198(((UView *)(self))->f[0x3E]) * 3.0f;
            (&v30)->f[2] = 0.0f;
            FastVecAdd(&v40, self + 0x10, (&v30));
            ((UView *)(self))->f[0x6] = func_002A89A8(self + 0x10, 0, 0.5f);
            func_L01_00321178(self, &v40);
            if (!(vec_distance_xy(self + 0x10, st + 0x6C0) > 4.9f)) {
            } else if (*(int *)(st + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || (((UView *)(self))->f[0x12] = 1.0f, ClaimNearestObjectSlot(self) != 0)) {
                func_002A7750(self, 0xB, 2);
            } else {
                func_002A7750(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) func_002A7470(self, 3, 0, 0x14);
            }
        }
        break;
    case 11:
        if (func_002B3868(self) != 0) {
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) func_002A7470(self, 0xA, 0, D_L17_001B0E9C);
            fc = D_L17_001B0EB8;
            ((UView *)(self))->f[0x12] = -fc;
            func_002B60B0(self, (float)D_L17_001B0E68 * 0.00027777778f, fc * D_L17_001B0E70 * 0.016666668f, 0.05817765f, 0.05817765f);
        }
        if (self[0x42] == 0xA) {
            if (dist < D_L17_001B0E7C) {
                qcopy((&v30), &D_L17_001B9BC0);
                if (vec_distance_xy((&v30), self + 0x10) < D_L17_001B0EA4) {
                    if (*(int *)(st + 0x738) < D_L17_001B0EA8) {
                        (&v30)->f[2] = *(float *)(st + 0x248);
                        FastVecSub((&v30), st + 0x240, (&v30));
                        vec_scale_to_length((&v30), (&v30), 2.0f * D_L17_001B0EA4);
                        FastVecAdd((&v30), &D_L17_001B9BC0, (&v30));
                        v40.q = *(Quad *)(self + 0x10);
                        func_L02_0032EF10(&v40, (&v30), (&v30), *(int *)(st + 0x684), 3.0f);
                        fx = vec_distance_xy(self + 0x10, (&v30));
                        if (D_L17_001B0EA4 + 0.3f < fx) {
                            func_L01_00321178(self, (&v30));
                            *(int *)(st + 0x738) = *(int *)(st + 0x738) + 1;
                            break;
                        }
                    } else {
                        goto s11_184;
                    }
                }
                if (*(int *)(st + 0x738) >= D_L17_001B0EA8) {
s11_184:
                    STUB_printf(D_L17_001B0F20);
                }
                *(int *)(st + 0x738) = 0;
                func_002A7750(self, 0xC, -1);
                ((UView *)(self))->f[0x12] = 1.0f;
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != func_002A77E0(2) + 4) func_002A7470(self, func_002A77E0(2) + 4, 2, 0x14);
            } else {
                ComputeRegionRouteHeading(self + 0x10, st + 0x240, &f60, st + 0x280, *(int *)(st + 0x750), st + 0x758, st + 0x754, 0.0f, 0.5f);
                func_002B50E0(self, st + 0x240, f60);
                StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
                if (*(int *)(st + 0x190) >= 0x3D) {
                    *(int *)(st + 0x704) = D_L17_001B0E8C;
                    func_002A7750(self, 4, -1);
                    ((UView *)(self))->f[0x12] = 1.0f;
                    if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                    if (self[0x43] != 2) func_002A7470(self, 2, 0, 0x14);
                }
            }
        }
        break;
    case 15:
        if (func_002B3868(self) != 0 && self[0x43] != 1) func_002A7470(self, 1, 0, 0x14);
        StepAngleTowardTarget(self + 0xF8, 0, func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
        if (self[0x60] & 2) func_002A7750(self, 0xB, -1);
        break;
    case 12:
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        fd = func_0029F530(self);
        if (fd >= 13.0f && fd <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, st + 0x240) < D_L17_001B0E58
            && func_L17_003E7010(self) != 0) {
            h.obj = self;
            h.flags = 0x10001;
            h.val = *(float *)(st + 0x700);
            h.sn = func_00283180(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
            h.cs = func_00283198(func_00283248(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
            h.one = 1.0f;
            h.big = 5627.925f;
            h.o = h.k = 1;
            h.z = 0;
            h.id = ((UView *)(self))->uh[0x55];
            a1 = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
            func_002A8D70(D_L17_001B0EC8, *(float *)(st + 0x700), 1.0f, self, a1, 0x10001, 0, 1, 0);
        }
        if ((u32)(self[0x42] - 4) < 2U && D_L17_001B0EAC <= fd) func_002A7750(self, 0xD, -1);
        break;
    case 4:
        if (func_00282948(st + 0x704) != 0) {
            func_002A7750(self, 0xC, -1);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != func_002A77E0(2) + 4) func_002A7470(self, func_002A77E0(2) + 4, 0, 0x14);
        }
        break;
    case 13:
        if (func_002B3868(self) != 0) {
            fe = FastAddRotations(((UView *)(self))->f[0x3E], 3.141593f);
            (&v30)->f[0] = func_00283180(fe) * D_L17_001B0E88;
            (&v30)->f[1] = func_00283198(fe) * D_L17_001B0E88;
            (&v30)->f[2] = 0.0f;
            FastVecAdd((&v30), (&v30), self + 0x10);
            v40.q = *(Quad *)(self + 0x10);
            func_L02_0032EF10(&v40, (&v30), (&v30), *(int *)(st + 0x684), 3.0f);
            if (fast_vec_dist(self + 0x10, (&v30)) < D_L17_001B0E88 * 0.5f) {
                func_L17_0032C070(self + 0x10, st + 0x240, (&v30), *(int *)(st + 0x684), D_L17_001B0E90, 1.0f);
            }
            qcopy(&v40, self + 0x10);
            v40.f[2] += 0.5f;
            qcopy(&v50, (&v30));
            v50.f[2] += 0.5f;
            if (CollLine(&v40, &v50, 2, 0, 0) != 0) qcopy((&v30), &D_L17_001C0020);
            qcopy(st + 0x710, (&v30));
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) func_002A7470(self, 0xA, 0, D_L17_001B0E9C);
            func_002B60B0(self, (float)D_L17_001B0E6C * 0.00027777778f, D_L17_001B0E74 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(int *)(st + 0x708) = D_L17_001B0E94;
            func_L17_003E6F20(self);
            ((UView *)(self))->f[0x12] = D_L17_001B0EB8;
        }
        near = 0;
        hit13 = func_L01_00321178(self, st + 0x710);
        func_0029FCC0(self, 3, (&v30));
        if (func_002A89A8((&v30), 0, 0.5f) < 10.0f) near = 1;
        if (!(hit13 & 0x80) && *(int *)(st + 0x190) < 0xA && !(hit13 & 0xF) && near != 1) {
        } else {
            ((UView *)(self))->f[0x12] = 1.0f;
            if (dist < D_L17_001B0E7C + D_L17_001B0E80) {
                func_002A7750(self, 0xC, -1);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != func_002A77E0(2) + 4) func_002A7470(self, func_002A77E0(2) + 4, 0, 0x14);
            } else {
                func_002A7750(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) func_002A7470(self, 3, 0, 0x14);
            }
        }
        if (func_00282948(st + 0x708) != 0 && dist < D_L17_001B0E7C) {
            func_002A7750(self, 0xC, -1);
            ((UView *)(self))->f[0x12] = 1.0f;
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != func_002A77E0(2) + 4) func_002A7470(self, func_002A77E0(2) + 4, 0, 0x14);
        }
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        break;
    case 9:
        if (func_002B3868(self) != 0 && self[0x43] != 7) func_002A7470(self, 7, 0, 0x14);
        qcopy((&v30), self + 0x10);
        ff = ((UView *)(self))->f[0x6] - 0.050000004f;
        (&v30)->f[2] = 70.0f;
        ((UView *)(self))->f[0x6] = ff;
        if (ff < 70.0f) {
b262:
            SetDeathBits(self, 0, 3);
            func_0029F338(self);
            return;
        }
        break;
    }
    func_0029FCC0(self, D_L17_001B3940[0], (&v30));
    if (func_002A89A8((&v30), 0, 1.0f) < 20.0f && self[0x95] != 3 && self[0x20] != 9) {
        if (self[0x20] == 0xD || self[0x20] == 0xB) func_002A7750(self, 9, 7);
    }
}
