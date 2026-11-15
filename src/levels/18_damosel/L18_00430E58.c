/* func_L18_00430E58: own unit for -frac2-keep-block-order (the class-switch default stays last)
 * and -frac2-hazard-labels (case 9 branches to the hazard nop of a shared c.lt.s).
 * D_L18_001B290C is a MACRO_ADDR scalar (tied lui/lw); arms that end in a call repeat the
 * following store so the tails cross-jump as in retail. */
#include "common.h"

extern u8 *D_L18_001B290C MACRO_ADDR;

extern int func_00282948(void *);
extern int func_00282978(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern int func_002A8D70(void *, float, float, int, int, float, int, int, int);
extern float func_002AA2E8(void *, float, float);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L02_003329C8(void *, void *, float, float);
extern int func_L07_00323038(void *, float, float, float);
extern void func_L18_00432548(void *, void *, int);
extern int func_L18_00432598(void *, void *);
extern float func_L18_004325D8(void *, void *);
extern float func_L18_00432630(void *, void *);
extern int func_L18_00432698(void *, void *);
extern int func_L18_004326E8(void *);
extern int func_L18_00432718(void *, void *);
extern int func_L18_004327B0(void *);
extern void func_L18_00432910(void *);
extern void func_L18_00432960(void *);
extern void func_L18_004329B0(void *);
extern void func_L18_00432E78(void *, int, int, int);
extern void func_L18_004331D0(void *);
extern void func_L18_00433430(void *);
extern void func_L18_00433450(void *);

void func_L18_00430E58(u8 *self)
{
    float v[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(self + 0x68);

    switch (self[0x20]) {
    case 0:
    case 1:
        break;
    case 2:
        if (func_002B3868(self) != 0)
            func_L18_00432E78(self, 1, 0, 0xA);
        break;
    case 3:
        if (func_002B3868(self) != 0) {
            self[0xBC] = 0;
            *(s16 *)(vars + 0x80C) = func_002A77E0(30);
        } else {
            if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(vars + 0x80C)) {
                *(int *)(vars + 0x188) = 0;
                func_L18_00432E78(self, 2, 0, 3);
                self[0xBC] = 1;
                vec_scale_to_length(v, self + 0xC0, 2.0f);
                FastVecAdd(v, v, self + 0x10);
                v[2] -= 6.0f;
                func_L02_003329C8(self, v, 0.033333335f, 0.0055555557f);
            }
            if (self[0xBC] == 1) {
                ApproachValue(self + 0xF0, 0.0f, 0.052359886f);
                ApproachValue(self + 0xF4, 0.0f, 0.052359886f);
                *(int *)(vars + 0x138) |= 2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = 0;
                if (func_L07_00323038(self, 11.0f, 18.0f, 27.0f) != 0) {
                    func_L18_00432960(self);
                    func_L18_00432E78(self, 9, 0, 0xA);
                    *(float *)(vars + 0x134) = 0.2f;
                    if (*(int *)(vars + 0x7D0) != -1) {
                        self[0xBC] = 2;
                        qcopy(vars + 0x750, (u8 *)((*(int *)(vars + 0x7D0) << 7) + (s32)D_L18_001B290C) + 0x30);
                    } else {
                        func_002A7750(self, 4, 1);
                    }
                }
                *(int *)(vars + 0x138) &= ~2;
                if (*(u8 **)(vars + 0x7EC) != 0)
                    *(int *)(*(u8 **)(vars + 0x7EC) + 0x98) = *(int *)(*(u8 **)(*(u8 **)(vars + 0x7EC) + 0x24) + 0x10);
            } else if (self[0xBC] == 2) {
                if (vec_distance_xy(self + 0x10, D_L18_001B290C + (*(int *)(vars + 0x7D0) << 7) + 0x30) < 0.5f)
                    func_002A7750(self, 4, 1);
            }
        }
        break;
    case 4:
        if (func_002B3868(self) != 0) {
            func_L18_00432E78(self, func_002A77E0(2) + 3, 0, 0xA);
            if (self[0x94] != 4)
                *(int *)(vars + 0x7AC) = func_002A7820(0, 30);
        } else if (self[0x60] & 2) {
            func_002A7750(self, 4, -1);
        } else if (*(s16 *)(vars + 0x7FA) == 0 && *(int *)(vars + 0x79C) == 1 && func_00282948(vars + 0x7AC) != 0) {
            func_002A7750(self, 6, -1);
            func_002A7750(self, 5, -1);
        }
        break;
    case 5:
        if (func_002B3868(self) != 0)
            func_L18_00432E78(self, 5, 0, 0xA);
        else if (self[0x60] & 2)
            func_002A7750(self, self[0x94], -1);
        break;
    case 6:
        if (func_002B3868(self) != 0) {
            func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
            *(int *)(vars + 0x7A8) = func_002A7820(480, 600);
        } else if (*(int *)(vars + 0x79C) == 1) {
            if (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))
                func_002A7750(self, 8, -1);
            else if (func_L18_004327B0(self) != 0)
                func_002A7750(self, 7, 1);
        } else if (*(int *)(vars + 0x7A8) <= 0) {
            func_002A7750(self, 4, -1);
        }
        func_00282948(vars + 0x7A8);
        break;
    case 9: {
        float fr;
        if (func_002B3868(self) != 0) {
            *(float *)(vars + 0x134) = 2.0f;
            switch (self[0x42]) {
            case 8:
                func_L18_00432910(self);
                self[0xBC] = 1;
                break;
            case 9:
                func_L18_00432960(self);
                self[0xBC] = 2;
                break;
            default:
                func_L18_00432910(self);
                self[0xBC] = 1;
                func_L18_00432E78(self, 8, 0, 0xA);
                break;
            }
        }
        if (*(u8 **)(vars + 0x7BC) != 0) {
            u8 *t = *(u8 **)(vars + 0x7BC);
            if (t[0x20] != 0xFE && (*(u8 **)(vars + 0x7BC))[0x20] != 0xFD && ((*(u16 *)(t + 0x34) ^ 1) & 1))
                qcopy(vars + 0x750, t + 0x10);
            else
                func_002A7750(self, self[0x94], -1);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
        }
        func_L18_00432548(self, vars + 0x750, 0);
        fr = func_0029F530(self);
        if (self[0xBC] == 2) {
            if (func_L18_004325D8(self, vars + 0x750) < 4.0f && (self[0x60] & 2)) {
                func_L18_00432910(self);
                self[0xBC] = 1;
                func_L18_00432E78(self, 8, 0, 0xA);
            }
        } else if (self[0xBC] == 1) {
            if (func_L18_004325D8(self, vars + 0x750) > 7.0f && fr > 4.0f && fr < 9.0f) {
                func_L18_00432960(self);
                self[0xBC] = 2;
                func_L18_00432E78(self, 9, 6, 0xA);
            }
            if (((fr > 4.0f && fr < 9.0f) || (fr > 21.0f && fr < 26.0f))
                && func_L18_004325D8(self, vars + 0x750) < 0.0f && func_L18_00432630(self, vars + 0x750) < 0.0f
                && func_L18_00432698(self, vars + 0x750) != 0) {
                func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
                func_002A7750(self, self[0x94], -1);
            }
        } else {
            if ((self[0x60] & 2) && *(u16 *)(self + 0x96) >= 0x79) {
                func_L18_00432910(self);
                self[0xBC] = 1;
                func_L18_00432E78(self, 8, 0, 0xA);
            }
            if (func_L18_004325D8(self, vars + 0x750) < 0.0f && func_L18_00432630(self, vars + 0x750) < 0.0f
                && func_L18_00432698(self, vars + 0x750) != 0) {
                func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
                func_002A7750(self, self[0x94], -1);
            }
        }
        if ((self[0xBC] == 1 || self[0xBC] == 2)
            && (*(int *)(vars + 0x180) >= 2 || (*(int *)(vars + 0x194) & 0xF))) {
            self[0xBC] = 0;
            func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0x94] == 7 && *(int *)(vars + 0x79C) == 1
            && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 8, -1);
        }
        break;
    }
    case 7:
        if (func_002B3868(self) != 0 && func_L18_004327B0(self) == 0) {
            func_002A7750(self, 6, -1);
        } else if (func_L18_004325D8(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || func_L18_00432630(self, *(u8 **)(vars + 0x7B8) + 0x10) >= 0.0f
                   || func_L18_00432698(self, *(u8 **)(vars + 0x7B8) + 0x10) == 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            func_002A7750(self, 9, -1);
        } else if (*(int *)(vars + 0x79C) == 1
                   && (*(s16 *)(vars + 0x7F4) == -1 || *(s16 *)(vars + 0x7F6) < *(s16 *)(vars + 0x7F4))) {
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 6, -1);
        } else if (func_L18_00432598(self, *(u8 **)(vars + 0x7B8) + 0x10) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            func_002A7750(self, 0xB, -1);
        } else if (func_L18_004326E8(self) != 0) {
            *(u8 **)(vars + 0x7BC) = *(u8 **)(vars + 0x7B8);
            func_002A7750(self, 0xA, -1);
        }
        break;
    case 8: {
        u8 *p;
        if (func_002B3868(self) != 0)
            func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
        if (*(int *)(vars + 0x79C) != 1) {
            func_002A7750(self, 6, -1);
            break;
        }
        p = vars + 0x1F0;
        if (func_L18_00432598(self, p) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 0xB, -1);
        } else if (func_L18_004325D8(self, p) >= 0.0f || func_L18_00432630(self, p) >= 0.0f
                   || func_L18_00432698(self, p) == 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 9, -1);
        } else if (func_L18_004326E8(self) != 0) {
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 0xA, -1);
        }
        break;
    }
    case 10:
        if (func_002B3868(self) != 0) {
            func_L18_00432E78(self, 0xA, 0, 0xA);
            self[0xBC] = 0;
            *(float *)(self + 0x48) = 2.0f;
            if (*(s16 *)(vars + 0x7FC) != 0)
                *(s16 *)(vars + 0x806) = 0;
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            qcopy(v, *(u8 **)(vars + 0x7BC) + 0x10);
        else
            qcopy(v, vars + 0x1F0);
        func_L18_00432548(self, v, 0);
        if (self[0xBC] == 0) {
            if (func_L18_00432598(self, v) != 0) {
                u8 s = self[0x94];
                func_002A7750(self, 0xB, -1);
                self[0x94] = s;
                break;
            }
            if (self[0x60] & 2) {
                if (func_L18_00432718(self, v) != 0) {
                    self[0xBC] = 2;
                    if (*(s16 *)(vars + 0x7FC) != 0) {
                        func_L18_00432E78(self, 0xC, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    } else {
                        func_L18_00432E78(self, 0xD, 0, 0xA);
                        *(float *)(self + 0x48) = 1.0f;
                    }
                } else {
                    self[0xBC] = 1;
                    func_L18_00432E78(self, 0xB, 0, 0xA);
                    *(float *)(self + 0x48) = 1.0f;
                }
            }
        }
        if (self[0xBC] == 1) {
            if (func_L18_00432598(self, v) != 0) {
                u8 s = self[0x94];
                func_002A7750(self, 0xB, -1);
                self[0x94] = s;
                break;
            }
            if (func_L18_00432718(self, v) != 0) {
                self[0xBC] = 2;
                if (*(s16 *)(vars + 0x7FC) != 0)
                    func_L18_00432E78(self, 0xC, 0, 0xA);
                else
                    func_L18_00432E78(self, 0xD, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 2) {
            float fr = func_0029F530(self);
            if (*(s16 *)(vars + 0x7FC) != 0) {
                if (fr < 2.0f && *(s16 *)(vars + 0x806) == 0) {
                    qcopy(vars + 0x760, v);
                    func_L18_004331D0(self);
                    *(s16 *)(vars + 0x806) = 1;
                }
            } else if (fr < 5.0f && *(s16 *)(vars + 0x806) == 0) {
                func_L18_00433430(self);
            }
            if (self[0x60] & 2) {
                if (*(u8 **)(vars + 0x7BC) == 0) {
                    if (func_L18_00432598(self, v) != 0) {
                        u8 s = self[0x94];
                        func_002A7750(self, 0xB, -1);
                        self[0x94] = s;
                        break;
                    }
                    if (func_L18_004326E8(self) != 0 && func_L18_004325D8(self, v) < 0.0f
                        && func_L18_00432718(self, v) != 0) {
                        self[0xBC] = 2;
                        if (*(s16 *)(vars + 0x7FC) != 0) {
                            func_L18_00432E78(self, 0xC, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        } else {
                            func_L18_00432E78(self, 0xD, 0, 0xA);
                            *(float *)(self + 0x48) = 1.0f;
                        }
                    }
                }
                self[0xBC] = 3;
                func_L18_00432E78(self, 0xE, 0, 0xA);
                *(float *)(self + 0x48) = 1.0f;
            }
        } else if (self[0xBC] == 3) {
            if (self[0x60] & 2) {
                func_L18_00432E78(self, 8, 0, 0xA);
                func_002A7750(self, self[0x94], -1);
                *(float *)(self + 0x48) = 1.0f;
            }
        }
        break;
    case 11: {
        float fr;
        if (func_002B3868(self) != 0) {
            func_L18_00432E78(self, 0xF, 0, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            func_L18_00432548(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            func_L18_00432548(self, vars + 0x1F0, 1);
        fr = func_0029F530(self);
        if (fr > 11.0f && fr < 17.0f)
            func_002A8D70(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            func_002A7750(self, self[0x94], -1);
        break;
    }
    case 12: {
        float fr;
        if (func_002B3868(self) != 0) {
            func_L18_00432E78(self, 0xF, 2, 0xA);
            break;
        }
        if (*(u8 **)(vars + 0x7BC) != 0)
            func_L18_00432548(self, *(u8 **)(vars + 0x7BC) + 0x10, 1);
        else
            func_L18_00432548(self, vars + 0x1F0, 1);
        fr = func_0029F530(self);
        if (fr > 11.0f && fr < 17.0f)
            func_002A8D70(self, 0.8f, (float)vars[0x36], 2, 0x10001, 4.0f, 0, 1, 0);
        if (self[0x60] & 2)
            func_002A7750(self, self[0x94], -1);
        break;
    }
    case 13: {
        int flags;
        float fr;
        if (func_002B3868(self) != 0) {
            func_L18_00433450(self);
            *(s16 *)(vars + 0x804) = 0;
            *(s16 *)(vars + 0x80E) = 1;
        }
        flags = func_002B1C20(self, vars + 0x50);
        fr = func_0029F530(self);
        if (*(u16 *)(self + 0x96) >= 0xB5 || (flags & 1)) {
            SetDeathBits(self, 0, 3);
            func_L18_004329B0(self);
        } else if ((self[0x42] == 0x10 && fr > 27.0f) || (self[0x42] == 0x11 && fr > 47.0f) || (flags & 2)) {
            if (*(u8 **)(vars + 0x7C0) != 0) {
                if (func_L18_00432598(self, vars + 0x1F0) != 0) {
                    *(float *)(self + 0x48) = 0.0f;
                    *(u8 **)(vars + 0x7BC) = 0;
                    func_002A7750(self, 8, 1);
                    func_002A7750(self, 0xB, -1);
                } else {
                    func_L18_00432E78(self, func_002A77E0(2) + 6, 0, 0xA);
                    func_002A7750(self, 8, 1);
                }
                break;
            }
            func_002A7750(self, 0xE, 1);
        }
        if (*(s16 *)(vars + 0x80E) != 0 && *(u8 **)(vars + 0x38) != 0
            && *(s16 *)(*(u8 **)(vars + 0x38) + 0xAA) == 0x47 && *(u8 **)(vars + 0x7C0) != 0
            && self[0x42] == 0x10 && fr > 13.0f) {
            *(float *)(self + 0x48) = 0.0f;
            *(u8 **)(vars + 0x7BC) = 0;
            func_002A7750(self, 8, 1);
            func_002A7750(self, 0xC, -1);
        }
        break;
    }
    case 14:
        if (func_002B3868(self) != 0) {
            if (*(s16 *)(vars + 0x80A) == 0)
                *(s16 *)(vars + 0x80A) = 600;
            if (*(u8 **)(vars + 0x7C0) != 0) {
                func_0029FCC0(self, 0, v);
                SpawnExplosion(v, 1, 10, 30, 0, 10, 45, 1, 0.5f, 20.0f, 0, 0, 0, 0);
                func_0029F338(*(u8 **)(vars + 0x7C0));
                *(u8 **)(vars + 0x7C0) = 0;
            }
            if (*(u8 **)(vars + 0x7C4) != 0) {
                func_0029F338(*(u8 **)(vars + 0x7C4));
                *(u8 **)(vars + 0x7C4) = 0;
            }
            if (*(u8 **)(vars + 0x7C8) != 0) {
                func_0029F338(*(u8 **)(vars + 0x7C8));
                *(u8 **)(vars + 0x7C8) = 0;
            }
            if (self[0x43] != 8)
                func_002A7470(self, 8, 0, 0xA);
        } else {
            qcopy(vars + 0x750, vars + 0x1F0);
            if (func_L18_00432598(self, vars + 0x1F0) != 0) {
                func_002A7750(self, 0xB, -1);
            } else if (FastDecTimer(vars + 0x80A) != 0) {
                SetDeathBits(self, 0, 3);
                func_L18_004329B0(self);
            }
        }
        break;
    }
}
