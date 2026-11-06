/* func_PAL_L09_003FEAF0 (levels 09 and 20), the PAL copy of func_L09_003FA080: the same C, with
 * the frame timers scaled 5/6 for 50 Hz and the turn rate scaled 6/5.  D_L09_001B0F40 is read as
 * a word here, and the timer tests of case 11 are written with the frame count first. */
#include "common.h"

extern int D_L09_001B10F4 __attribute__((sda));
extern int D_L09_001B0F54 __attribute__((sda));
extern int D_L09_001B0F58 __attribute__((sda));
extern float D_L09_001B0F60 __attribute__((sda));
extern int D_L09_001B2388 __attribute__((sda));
extern float D_L09_001B0F2C __attribute__((sda));
extern int D_L09_001B0F34 __attribute__((sda));
extern int D_L09_001B0F38 __attribute__((sda));
extern int D_L09_001B0F3C __attribute__((sda));
extern int D_L09_001B0F40 __attribute__((sda));
extern int D_L09_001B0F44 __attribute__((sda));
extern int D_L09_001B0F48 __attribute__((sda));
extern s32 D_L09_001B285C MACRO_ADDR;
extern char *D_L09_001FE6C0[];
extern char D_L09_001B10F8[];
extern char D_L09_001B1128[];

extern void func_0026FEB8(const char *, ...);
extern int func_00282978(void *);
extern float func_00282E80(void *, void *);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_00283CE0(int);
extern void func_0029F338(void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002ABB18(float);
extern int func_002ACD38(void *);
extern int func_002B1C20(void *, void *);
extern void func_002B3380(void *, void *, void *);
extern int func_002B3868(void *);
extern void func_002B5278(void *, float);
extern int func_002E5CF8(int, int, void *);
extern int func_001163B0(void);
extern void func_PAL_L09_003FBC48(void *, float);
extern void func_L09_003F73E8(void *);
extern void func_L09_003F7430(void *);
extern void func_L09_003F7468(void *);
extern void func_L09_003F74A8(void *);
extern void func_PAL_L09_003FBDF0(void *, int, int, int);
extern void func_L09_003F77D0(void *);
extern int func_L09_003F7B28(void *, int);
extern void func_L09_003F7C50(void *, int, int);
extern void func_PAL_L09_003FCF28(void *);
extern void func_PAL_L09_003FD248(void *);
extern void func_PAL_L09_003FD4F0(void *);
extern void func_PAL_L09_003FDB18(void *);
extern void func_L09_003F9468(void *);
extern int func_L09_003F9568(void *, int, int, int);
extern void func_PAL_L09_003FE118(void *);
extern void func_L09_003F9970(void *);
extern void func_PAL_L09_003FE4C0(void *);
extern int func_L09_003F9D08(void *);

void func_PAL_L09_003FEAF0(char *self)
{
    char *vars;
    int state;

    if (D_L09_001B10F4 != 0)
        return;
    if (func_002ACD38(self + 0x10) == 0)
        return;
    vars = *(char **)(self + 0x68);
    if (func_L09_003F9D08(self) != 0)
        return;
    func_L09_003F7468(self);
    state = *(u8 *)(self + 0x95);
    func_PAL_L09_003FD4F0(self);
    if (self == 0 || *(u8 *)(self + 0x20) == 0xFE || *(u8 *)(self + 0x20) == 0xFD || state == 0)
        return;

    switch (*(u8 *)(self + 0x95)) {
    case 0:
        func_0026FEB8(D_L09_001B10F8, *(s16 *)(self + 0xB2), *(s16 *)(self + 0xAA));
        break;
    case 1: {
        int k;
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        k = *(int *)(vars + 0x4B0);
        if (k == -1 || ((u8 *)((k << 8) + D_L09_001B285C))[0x20] == 0xFE
            || ((u8 *)((k << 8) + D_L09_001B285C))[0x20] == 0xFD) {
            if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
                *(int *)(vars + 0x2D8) = *(int *)(vars + 0x2D4);
                if ((*(u8 *)(vars + 0x302) ^ 1) & 1) {
                    *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
                    func_002A7750(self, *(u8 *)(self + 0x20), 2);
                } else {
                    func_PAL_L09_003FBDF0(self, 0xC, 0, func_002A7820(7, 0xC));
                    func_002A7750(self, 8, 5);
                }
            }
        }
        break;
    }
    case 2:
        if (func_00282978(vars + 0x300) != 0) {
            *(int *)(vars + 0x2D8) = *(int *)(vars + 0x2D4);
            if (*(int *)(vars + 0x2B0) != -1) {
                func_L09_003F7C50(self, *(int *)(vars + 0x2B0), -1);
                if (*(u8 *)(self + 0x42) != 2)
                    func_PAL_L09_003FBDF0(self, 2, 0, 0);
                func_002A7750(self, 2, 3);
            } else {
                func_L09_003F7C50(self, *(int *)(vars + 0x2B8), -1);
                func_PAL_L09_003FBDF0(self, 2, 0, 0xA);
                *(float *)(self + 0x48) = D_L09_001B0F60;
                func_002A7750(self, 4, 3);
            }
            if (*(u8 *)(vars + 0x302) & 2) {
                func_L09_003F7C50(self, *(int *)(vars + 0x2C0), -1);
                *(u8 *)(vars + 0x302) = 0;
            }
        }
    case 3:
        *(float *)(vars + 0x2EC) = func_00283248(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        if (*(int *)(vars + 0x204) == 1)
            *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
        break;
    case 4:
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
            func_L09_003F7C50(self, *(int *)(vars + 0x2B8), -1);
            *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
            func_PAL_L09_003FBDF0(self, 2, 0, 0xA);
            *(float *)(self + 0x48) = D_L09_001B0F60;
            func_002A7750(self, 4, 3);
        }
        break;
    case 5:
        *(float *)(vars + 0x2EC) = func_00283248(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        if (*(u8 *)(vars + 0x302) & 2) {
            func_PAL_L09_003FBDF0(self, func_001163B0() & 1, 0, func_002A7820(10, 20));
            func_L09_003F73E8(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
            *(s16 *)(vars + 0x300) = 1;
            func_002A7750(self, *(u8 *)(self + 0x20), 2);
        }
        if (*(int *)(vars + 0x204) != 1 && *(s16 *)(vars + 0x2E0) == 0) {
            func_L09_003F73E8(self);
            func_PAL_L09_003FBDF0(self, func_001163B0() & 1, 0, func_002A7820(10, 20));
            func_002A7750(self, 5, 6);
        }
        break;
    case 6:
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x2E0) != 0) {
            func_L09_003F73E8(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
            func_PAL_L09_003FBDF0(self, 3, 0, func_002A7820(7, 0xC));
            func_002A7750(self, 5, 5);
        } else if (*(s16 *)(vars + 0x2E8) == 0) {
            func_L09_003F73E8(self);
            func_L09_003F7C50(self, *(int *)(vars + 0x2B8), 0);
            func_PAL_L09_003FBDF0(self, func_001163B0() & 1, 0, func_002A7820(10, 20));
            func_002A7750(self, 4, 4);
        }
        break;
    case 7:
        *(float *)(vars + 0x2EC) = func_00283248(*(float *)(*(char **)(vars + 0x200) + 0x10) - *(float *)(self + 0x10),
                                                 *(float *)(*(char **)(vars + 0x200) + 0x14) - *(float *)(self + 0x14));
        break;
    case 8:
        *(float *)(vars + 0x2EC) = func_00283B98(*(float *)(vars + 0x2EC),
            (func_00283198(func_002ABB18(func_00283CE0(D_L09_001B2388) * 0.02f)) + 2.0f) * 0.027925273f);
        break;
    case 9: {
        int flags;
        *(float *)(vars + 0x2EC) = *(float *)(self + 0xF8);
        flags = func_002B1C20(self, vars + 0x50);
        if (*(float *)(vars + 0x20) <= 0.0f
            && (*(u8 *)(self + 0x42) == 0xF || *(u8 *)(self + 0x43) == 0xF
                || (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))))
            func_002A7750(self, 0xF, -1);
        if (flags & 1) {
            if (*(float *)(vars + 0x20) > 0.0f)
                func_PAL_L09_003FCF28(self);
            func_L09_003F73E8(self);
            func_002A7750(self, 0xF, -1);
        } else if (flags & 2) {
            func_L09_003F73E8(self);
            *(s16 *)(vars + 0x2E0) = ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
            if (*(u8 *)(self + 0x42) == 0xF || *(u8 *)(self + 0x43) == 0xF
                || (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))
                || *(int *)(vars + 0x428) != 0) {
                if (*(int *)(vars + 0x428) != 2) {
                    func_L09_003F7C50(self, *(int *)(vars + 0x2B0), -1);
                    func_002A7750(self, 3, 3);
                } else {
                    func_002A7750(self, 0x10, 3);
                }
                func_PAL_L09_003FBDF0(self, 0xE, 0, func_002A7820(7, 0xC));
            } else {
                if (*(int *)(vars + 0x2DC) != -1)
                    func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
                else
                    func_PAL_L09_003FBDF0(self, 0, 0, func_002A7820(7, 0xC));
                if (*(u8 *)(vars + 0x30F) != 0)
                    func_002A7750(self, 0xD, 8);
                else
                    func_002A7750(self, 6, 5);
            }
        }
        break;
    }
    }

    switch (*(u8 *)(self + 0x20)) {
    case 0:
        break;
    case 1:
        if (*(u8 *)(self + 0x60) & 2)
            func_PAL_L09_003FBDF0(self, 0xE, 0, func_002A7820(7, 0xC));
        break;
    case 2:
        if ((*(char **)(vars + 0x2F8) != 0 && (*(u8 *)(*(char **)(vars + 0x2F8) + 0x60) & 2))
            || (*(u8 *)(self + 0x60) & 2)) {
            func_PAL_L09_003FBDF0(self, 0xE, 0, func_002A7820(7, 0xC));
            func_002A7750(self, 3, -1);
        }
        break;
    case 4:
        if (*(int *)(vars + 0x2DC) != -1) {
            char *p = D_L09_001FE6C0[*(int *)(vars + 0x2DC)] + *(s16 *)(vars + 0x1C8) * 0x10;
            func_002B5278(self, func_00283248(*(float *)(p + 0x10) - *(float *)(self + 0x10),
                                              *(float *)(p + 0x14) - *(float *)(self + 0x14)));
        }
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(int *)(vars + 0x2DC) != -1)
                func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
            else
                func_PAL_L09_003FBDF0(self, 0, 0, func_002A7820(7, 0xC));
            func_002A7750(self, 6, -1);
        }
        break;
    case 5:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(self + 0x95) == 5) {
                if (*(int *)(vars + 0x2DC) != -1)
                    func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
                else
                    func_PAL_L09_003FBDF0(self, 0, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 6, -1);
            } else if (*(int *)(vars + 0x2DC) != -1) {
                func_PAL_L09_003FBDF0(self, 0xC, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 6, -1);
            }
        }
        break;
    case 3:
        if (*(u8 *)(self + 0x60) & 2)
            func_PAL_L09_003FBDF0(self, 0xE, 0, func_002A7820(7, 0xC));
        if (func_L09_003F7B28(self, *(int *)(vars + 0x2DC)) != 0) {
            if (*(int *)(vars + 0x428) == 0) {
                *(int *)(vars + 0x138) &= ~4;
                func_L09_003F7C50(self, *(int *)(vars + 0x2BC), -1);
                func_PAL_L09_003FBDF0(self, 0x10, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 7, 5);
            } else {
                func_002A7750(self, 0x10, 5);
            }
        }
        break;
    case 6:
        func_PAL_L09_003FE4C0(self);
        break;
    case 16: {
        int near;
        int close;
        int lt;
        int got;
        int tried;
        float d;
        near = 1;
        d = func_00282E80(self + 0x10, *(char **)(vars + 0x200) + 0x10);
        if (!(d <= *(float *)(vars + 0x4BC)))
            near = 0;
        close = 1;
        lt = **(int **)(vars + 0x304) < *(int *)(vars + 0x2CC);
        if (!(d < D_L09_001B0F2C))
            close = 0;
        got = 0;
        tried = 0;
        if (func_002B3868(self) != 0) {
            *(int *)(vars + 0x428) = 2;
            *(int *)(vars + 0x4B4) = 0;
            *(int *)(vars + 0x138) |= 0x10;
        }
        if (!close && near && lt && func_002A77E0(D_L09_001B0F34 - 1) == 0 && *(s16 *)(vars + 0x2E6) == 0) {
            tried = 1;
            got = func_L09_003F9568(self, 0, *(u8 *)(vars + 0x30C) != 0, 0);
        }
        if ((close || got) && lt) {
            if (func_L09_003F9568(self, 0, *(u8 *)(vars + 0x30C) != 0, 1) != 0)
                *(u8 *)(vars + 0x30D) = 1;
            *(int *)(vars + 0x138) &= ~0x10;
            func_L09_003F7430(self);
            func_PAL_L09_003FBDF0(self, 8, 0, 7);
            func_0026FEB8(D_L09_001B1128);
            func_002A7750(self, 0xA, -1);
        }
        if (tried && !got)
            *(u8 *)(vars + 0x30C) = ~*(u8 *)(vars + 0x30C);
        func_L09_003F9970(self);
        break;
    }
    case 7:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(vars + 0x30E) != 0) {
                func_PAL_L09_003FBDF0(self, 4, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 4, 5);
            } else {
                func_PAL_L09_003FBDF0(self, 0xC, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 8, 5);
            }
        }
        break;
    case 8: {
        float a = func_00283248(*(float *)(vars + 0x1F0) - *(float *)(self + 0x10),
                                *(float *)(vars + 0x1F4) - *(float *)(self + 0x14));
        func_002B5278(self, a);
        if (func_00283C80(a, *(float *)(self + 0xF8)) < 0.17453295f) {
            func_PAL_L09_003FBDF0(self, 5, 0, func_002A7820(7, 0xC));
            *(u8 *)(vars + 0x30C) = 0;
            *(u8 *)(vars + 0x30D) = 0;
            func_002A7750(self, 9, -1);
        }
        break;
    }
    case 9: {
        int near;
        int close;
        int lt;
        float d;
        near = 1;
        d = func_00282E80(self + 0x10, *(char **)(vars + 0x200) + 0x10);
        if (!(d <= *(float *)(vars + 0x4BC)))
            near = 0;
        close = 1;
        lt = **(int **)(vars + 0x304) < *(int *)(vars + 0x2CC);
        if (!(d < D_L09_001B0F2C))
            close = 0;
        if (*(u8 *)(vars + 0x303) == 0) {
            int got = 0;
            int tried = 0;
            if (!close && near && lt && func_002A77E0(D_L09_001B0F34 - 1) == 0 && *(s16 *)(vars + 0x2E6) == 0) {
                tried = 1;
                got = func_L09_003F9568(self, 0, *(u8 *)(vars + 0x30C) != 0, 0);
            }
            if (*(u8 *)(vars + 0x30C) != 0 && got && !close) {
                func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 6, -1);
            } else if (close || got) {
                if (func_L09_003F9568(self, 0, *(u8 *)(vars + 0x30C) != 0, 1) != 0)
                    *(u8 *)(vars + 0x30D) = 1;
                func_L09_003F7430(self);
                func_PAL_L09_003FBDF0(self, 8, 0, 7);
                func_002A7750(self, 0xA, -1);
            } else if (*(u8 *)(self + 0x60) & 2) {
                func_PAL_L09_003FBDF0(self, 6, 0, func_002A7820(7, 0xC));
            }
            if (tried && !got)
                *(u8 *)(vars + 0x30C) = ~*(u8 *)(vars + 0x30C);
        } else {
            if (*(u8 *)(self + 0x60) & 2)
                func_PAL_L09_003FBDF0(self, 6, 0, func_002A7820(7, 0xC));
            if (close || (*(s16 *)(vars + 0x2E6) == 0 && near && lt)) {
                func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
                func_002A7750(self, 6, -1);
            }
        }
        break;
    }
    case 10:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(u8 *)(vars + 0x30D) != 0)
                func_PAL_L09_003FBDF0(self, 0xA, 0, 0xA);
            else
                func_PAL_L09_003FBDF0(self, 0x13, 0, 0xC);
            *(u16 *)(vars + 0x2E4) = ((s32)(D_L09_001B0F40) * 5 + 2) / 6;
            func_002A7750(self, 0xB, -1);
        }
        break;
    case 11:
        if (*(u16 *)(self + 0x96) > ((s32)(D_L09_001B0F3C) * 5 + 2) / 6)
            func_PAL_L09_003FE118(self);
        if ((*(u16 *)(self + 0x96) > ((s32)(D_L09_001B0F38) * 5 + 2) / 6
             && D_L09_001B0F2C < func_00282E80(self + 0x10, *(char **)(vars + 0x200) + 0x10))
            || *(char **)(vars + 0x2F8) == 0) {
            *(s16 *)(vars + 0x2E6) = ((s32)(func_002A7820(D_L09_001B0F44, D_L09_001B0F48)) * 5 + 2) / 6;
            func_L09_003F73E8(self);
            func_PAL_L09_003FBDF0(self, 0xC, 0, func_002A7820(7, 0xC));
            if (*(int *)(vars + 0x428) != 0)
                func_002A7750(self, 0x10, 5);
            else if (*(int *)(vars + 0x2DC) != -1 && *(int *)(vars + 0x2DC) == *(int *)(vars + 0x2B0))
                func_002A7750(self, 3, 5);
            else
                func_002A7750(self, 8, 5);
        }
        break;
    case 12:
        if (*(u8 *)(self + 0x60) & 2) {
            if (*(int *)(vars + 0x2DC) != -1)
                func_PAL_L09_003FBDF0(self, 0xB, 0, func_002A7820(7, 0xC));
            else
                func_PAL_L09_003FBDF0(self, 0, 0, func_002A7820(7, 0xC));
            func_002A7750(self, 6, 5);
        }
        break;
    case 13:
        if (*(u8 *)(self + 0x60) & 2)
            func_PAL_L09_003FBDF0(self, (func_001163B0() & 1) ? 0xA : 0x13, 0, func_002A7820(0x19, 0x2D));
        if (*(u8 *)(self + 0x42) == 0xA || *(u8 *)(self + 0x42) == 0x13)
            func_PAL_L09_003FE118(self);
        break;
    case 14:
        func_L09_003F73E8(self);
        break;
    case 15:
        *(float *)(vars + 0x20) = 0.0f;
        func_002B3380(self, vars + 0x290, vars + 0x20);
        func_L09_003F73E8(self);
        func_L09_003F77D0(self);
        func_002A6C58(self, 0, 3);
        func_PAL_L09_003FBC48(self, 0.4f);
        func_002E5CF8(3, 0, self);
        func_0029F338(self);
        return;
    }
    func_PAL_L09_003FDB18(self);
    func_L09_003F9468(self);
    func_PAL_L09_003FD248(self);
    func_L09_003F74A8(self);
    if (*(int *)(vars + 0x1D8) != -1 && *(u8 *)(self + 0x20) != 0 && *(u8 *)(self + 0x20) < 0xE) {
        func_PAL_L09_003FCF28(self);
        func_L09_003F73E8(self);
        func_002A7750(self, 0xF, 0xA);
    }
}
