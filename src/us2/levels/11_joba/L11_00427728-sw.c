#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern char D_00189E20[];
extern u8 *const D_L11_001B359C[] __attribute__((sda));
extern u8 *D_L11_001B368C[] __attribute__((sda));
extern void *D_L11_001FC420[];
extern s32 *D_L11_001FF580[];
extern s32 D_L11_001CAE40[];
extern s32 D_L11_001AED04[] __attribute__((sda));
extern s32 D_L11_001B35B8 __attribute__((sda));
extern s32 D_L11_001B0FEC __attribute__((sda));
extern s32 D_L11_001B0FF8 __attribute__((sda));
extern f32 D_L11_001B0FFC __attribute__((sda));
extern char D_L11_001A8F20[] __attribute__((sda));
extern void func_002A7470(u8 *a0, u32 a1, u32 a2, u32 a3);
extern void func_0029FCC0(u32 a0, s32 a1, f32 *a2);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_US2_L11_0042ADB8(u8 *);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern s32 func_002B38B8(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern f32 func_0029F530(u8 *);
extern f32 func_002A89A8(void *, s32, f32);
extern s32 func_002A77E0(s32);
extern void func_002B60B0(u8 *, f32, f32, f32, f32);
extern s32 func_002A8508(s32, s32);
extern u8 *func_L04_0033D4B0(u8 *);
extern s32 func_002B50E0(u8 *, void *, f32);
extern s32 func_002B6120(u8 *, void *);
extern s32 func_002B6228(u8 *, void *, s32, s32);
extern s32 func_L01_00321178(u8 *, void *);
extern s32 func_002B4FF0(u8 *, void *, f32);
extern f32 func_002AA458(void *, void *, void *, f32, f32, f32);
extern void func_002833F0(void *, void *);
extern f32 func_002AA3A8(void *, void *, f32, f32, f32, f32);
extern f32 func_00282C48(f32);
extern s32 func_US2_002AF9C8(u8 *, f32);
extern void func_L11_004349F8(u8 *, f32 *, f32 *, f32);
extern f32 func_002A7878(f32, f32);
extern void func_002C2210(void *, u32, u32, u32, s32, void *, f32, f32, f32, s32);
extern f32 func_002A7E08(u8 *, void *, void *, f32, f32, f32);
extern void func_L00_003294F0(u8 *, s32);
extern void func_002A8C28(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 func_002B3890(u8 *);
extern void func_0029F338(void *);
extern s32 func_002B1C20(u8 *, void *);
extern void func_US2_002A7AA8(u8 *, s32, s32);
extern void func_L01_003E9CF8(u8 *, s32, void *);
extern void func_002AF1D0(u8 *, void *, s32, s32);
extern void func_002AC728(u8 *, void *, f32, f32, s32);
extern s32 func_L11_00425EC0(u8 *);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(void *);
extern void func_00283898(void *, s32, f32);
extern void func_L11_0042A420(u8 *arg0);
extern int func_L11_0042A158(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283C80(f32, f32);
extern void func_00282F20(void *, void *, f32);
extern int func_002A7EA0(void *, void *, void *, f32, f32, f32, f32, int);

void func_US2_L11_00427728(u8 *arg0) {
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    u8 *data;
    f32 z0;
    f32 lim1_9;
    f32 a1_9;
    s32 i1_9;
    s32 r1_0;
    f32 d1_1;
    s32 i1_1;
    s32 best1_1;
    f32 f1_1;
    s32 i1_2;
    s32 i1_8;
    f32 f1_4;
    s32 r1_4;
    u8 *p1_5;
    u8 *q1_5;
    u8 *p1_6;
    u8 *p1_7;
    u8 *q1_7;
    f32 a1_7;
    f32 f1_7;
    f32 f2_2;
    f32 f2_3;
    s32 r2_5;
    s32 n2_5;
    u8 *p2_5;
    u8 c2_5;
    s32 *path2_12;
    f32 d2_12;
    s32 *path2_18;
    f32 d2_18;
    f32 f2_23;
    u8 c2_23;
    u16 *list2_23;
    u8 *base2_23;
    u8 *o2_23;
    u8 *q2_23;
    f32 d2_23;
    u8 *p2_25;
    u8 *q2_25;
    u8 *p2_32;
    f32 f2_32;
    u8 *p2_33;
    s32 *path2_34;
    s32 *pathb2_34;
    u8 *p2_34;
    f32 f2_19;
    f32 f2_20;
    s32 n2_20;
    f32 f2_22;
    f32 f2_27;
    f32 a2_27;
    s32 n2_27;
    f32 f2_28;
    f32 f2_29, g2_29;
    f32 a2_29;
    s32 n2_29;

    if (D_L11_001CAE40[0] != 0)
        return;
    if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x6F && arg0[0x95] != 4)
        return;
    z0 = *(f32 *)(arg0 + 0x18);
    data = *(u8 **)(arg0 + 0x68);
    if (func_US2_L11_0042ADB8(arg0) != 0) {
        func_0029F338(arg0);
        return;
    }
    switch (arg0[0x95]) {
    case 9:
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 6.0f) {
            lim1_9 = 1.5707965f;
            a1_9 = func_00283BE0(func_00283248(*(f32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x10) - *(f32 *)(arg0 + 0x10),
                                            *(f32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x14) - *(f32 *)(arg0 + 0x14)),
                              *(f32 *)(arg0 + 0xF8));
            if (func_002B38B8(arg0) != 0)
                a1_9 = -a1_9;
            if (a1_9 > lim1_9)
                a1_9 = lim1_9;
            else if (a1_9 < -lim1_9)
                a1_9 = -lim1_9;
            *(f32 *)(data + 0x308) = a1_9;
        }
        if (((Hero *)D_00189E20)->i[0x1248 / 4] != 0x41)
            arg0[0x95] = 0;
        break;
    case 0:
        if (func_002B3890(arg0) != 0)
            func_002B60B0(arg0, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
        if (*(s16 *)(data + 0x264) == 2) {
            if (*(s32 *)(data + 0x284) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x1A, 2);
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x19, 2);
            } else if (*(s32 *)(data + 0x294) == 1) {
                if (arg0[0x43] != 0xA)
                    func_002A7470(arg0, 0xA, func_002A77E0(4), func_002A7820(7, 0x14));
                func_002A7750(arg0, 0x13, 2);
            } else {
                if (*(s32 *)(data + 0x570) != 0) {
                    if (arg0[0x43] != 2)
                        func_002A7470(arg0, 2, 0, 0xA);
                    func_002A7750(arg0, 0x13, 3);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (arg0[0x43] != 2)
                        func_002A7470(arg0, 2, 0, 0x28);
                    func_002A7750(arg0, 0x13, 3);
                }
            }
        } else if (*(s16 *)(data + 0x266) != 0) {
            if (*(s32 *)(data + 0x558) != -1) {
                r1_0 = *(s32 *)(data + 0x560);
                if (r1_0 == 1) {
                    if (arg0[0x43] != 9)
                        func_002A7470(arg0, 9, 0, func_002A7820(5, 0xF));
                    func_002A7750(arg0, 6, -1);
                } else if (r1_0 >= 2) {
                    if (arg0[0x43] != 3)
                        func_002A7470(arg0, 3, 0, func_002A7820(5, 0xF));
                    func_002A7750(arg0, 7, -1);
                    func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
                }
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x19, 2);
            }
            if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
                if (*(s32 *)(data + 0x294) == 1) {
                    if (arg0[0x43] != 0xA)
                        func_002A7470(arg0, 0xA, 0, func_002A7820(0xA, 0x14));
                    func_002A7750(arg0, 0x13, 2);
                } else if (*(s32 *)(data + 0x570) != 0) {
                    if (arg0[0x43] != 2)
                        func_002A7470(arg0, 2, 0, 0x28);
                    func_002A7750(arg0, 0x13, 3);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (arg0[0x43] != 2)
                        func_002A7470(arg0, 2, 0, 0xA);
                    func_002A7750(arg0, 0x13, 3);
                }
            }
            *(s16 *)(data + 0x266) = 0;
        }
        break;
    case 1:
        if (func_002B3890(arg0) != 0) {
            func_002B60B0(arg0, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
            *(f32 *)(data + 0x12C) = 6.0f;
        }
        if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
            if (*(s32 *)(data + 0x284) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                d1_1 = 100.0f;
                func_002A7750(arg0, 0x1A, 2);
                i1_1 = 0;
                best1_1 = 0;
                for (; i1_1 < *D_L11_001FF580[*(s32 *)(data + 0x284)]; ) {
                    f1_1 = func_00282E80(arg0 + 0x10, (u8 *)D_L11_001FF580[*(s32 *)(data + 0x284)] + 0x10 + i1_1 * 0x10);
                    if (f1_1 < d1_1) {
                        d1_1 = f1_1;
                        best1_1 = i1_1;
                    }
                    i1_1++;
                }
                func_002B6228(arg0, D_L11_001FF580[*(s32 *)(data + 0x284)], -1, best1_1);
            }
            if (*(s32 *)(data + 0x548) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x19, 2);
            } else if (*(s32 *)(data + 0x294) == 1) {
                if (arg0[0x43] != 0xA)
                    func_002A7470(arg0, 0xA, func_002A77E0(4), func_002A7820(7, 0x14));
                func_002A7750(arg0, 0x13, 2);
            } else {
                *(s32 *)(data + 0x290) = 1;
                if (arg0[0x43] != 2)
                    func_002A7470(arg0, 2, 0, 0x28);
                func_002A7750(arg0, 0x13, 3);
            }
        }
        break;
    case 2:
        if (func_002B3890(arg0) != 0)
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.003781547f, 0.29670602f);
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2 && arg0[0x20] != 0x19 && func_002A77E0(4) == 1) {
            *(f32 *)(arg0 + 0x48) = 1.0f;
            if (arg0[0x43] != 2)
                func_002A7470(arg0, 2, 0, 0xA);
            func_002A7750(arg0, 0xE, 1);
            *(s32 *)(data + 0x560) = 0;
            *(s16 *)(data + 0x260) = func_002A7820(0x244, 0x258);
        }
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x31 && *(s32 *)(data + 0x558) != -1) {
            if (arg0[0x43] != 3)
                func_002A7470(arg0, 3, 0, func_002A7820(5, 0xF));
            func_002A7750(arg0, 7, 8);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
        }
        break;
    case 8:
        if (((Hero *)D_00189E20)->i[0x2294 / 4] != 0x31) {
            if (*(s32 *)(data + 0x548) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x19, 2);
            } else {
                if (arg0[0x43] != 0xA)
                    func_002A7470(arg0, 0xA, 0, 0xA);
                func_002A7750(arg0, 0x13, 2);
            }
        }
        break;
    case 4:
        if (*(f32 *)(data + 0x20) > 0.0f)
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                           ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        r1_4 = func_002B1C20(arg0, data + 0x60);
        if (r1_4 & 1) {
            func_0029F338(*(u8 **)(data + 0x278));
            D_L11_001AED04[0] = D_L11_001AED04[0] - 1;
            func_US2_002A7AA8(arg0, 0, 3);
            func_L01_003E9CF8(arg0, 0, 0);
            return;
        }
        if (r1_4 & 2) {
            *(s16 *)(data + 0x26) = 0;
            if ((u16)(*(s16 *)(data + 0x264) - 1) < 2) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x17, 2);
                if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 6.5f &&
                    func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                     ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.6108653f) {
                    if (arg0[0x43] != 5)
                        func_002A7470(arg0, 5, 1, 4);
                    func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
                    func_002A7750(arg0, 0x1D, 2);
                }
            } else if (*(s32 *)(data + 0x558) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, func_002A7820(5, 0xF));
                func_002A7750(arg0, 7, 0);
                func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0033936962f, 0.26179942f);
            } else {
                if (arg0[0x43] != 0)
                    func_002A7470(arg0, 0, 0, 0xA);
                func_002A7750(arg0, 0xE, 1);
                *(s16 *)(data + 0x260) = func_002A7820(0x244, 0x258);
            }
        }
        break;
    case 3:
        if (func_002B3890(arg0) != 0)
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(data + 0x294) == 1) {
            if (arg0[0x43] != 3)
                func_002A7470(arg0, 3, 0, 0xA);
            func_002A7750(arg0, 0x17, 2);
            if (*(s32 *)(data + 0x284) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x1A, 2);
            }
        }
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2) {
            if (arg0[0x43] != 0xB)
                func_002A7470(arg0, 0xB, 0, 0x1E);
            func_002A7750(arg0, 0xE, 1);
            *(s16 *)(data + 0x260) = func_002A7820(0x244, 0x258);
            *(s32 *)(data + 0x560) = 0;
        }
        break;
    case 5:
        if (*(u8 **)(data + 0x278) != 0)
            func_002AF1D0(arg0, *(u8 **)(data + 0x278), 1, 0);
        p1_5 = *(u8 **)(data + 0x274);
        qcopy(arg0 + 0x10, p1_5 + 0x10);
        qcopy(arg0 + 0xF0, p1_5 + 0xF0);
        q1_5 = *(u8 **)(data + 0x280);
        qcopy(q1_5 + 0x10, arg0 + 0x10);
        qcopy(q1_5 + 0xF0, arg0 + 0xF0);
        qcopy(q1_5 + 0x10, arg0 + 0x10);
        *(f32 *)(q1_5 + 0x18) = *(f32 *)(q1_5 + 0x18) + 0.65f;
        if (*(s32 *)(data + 0x26C) == 0) {
            func_002AC728(arg0, *(u8 **)(data + 0x278) + 0x10, 0.5f, 3.0f, -1);
            func_0029F338(*(u8 **)(data + 0x278));
            func_0029F338(*(u8 **)(data + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = 0;
            func_002A7750(arg0, 2, 6);
        } else if (func_L11_00425EC0(arg0) != 0) {
            func_002AC728(arg0, *(u8 **)(data + 0x278) + 0x10, 0.5f, 3.0f, -1);
            func_0029F338(*(u8 **)(data + 0x278));
            func_0029F338(*(u8 **)(data + 0x280));
            *(s32 *)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = 0;
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 0);
            func_002A7750(arg0, 3, 6);
        }
        break;
    case 6:
        if (func_002B3890(arg0) != 0) {
            p1_6 = func_0029EFD0(0x9AC);
            *(u8 **)(data + 0x29C) = p1_6;
            if (p1_6 != 0) {
                p1_6[0x30] = arg0[0x30];
                *(u16 *)(*(u8 **)(data + 0x29C) + 0x32) = *(u16 *)(arg0 + 0x32);
                (*(u8 **)(data + 0x29C))[0x31] = 1;
                *(s64 *)(*(u8 **)(data + 0x29C) + 0x38) = *(s64 *)(arg0 + 0x38);
                func_002A0F48(*(u8 **)(data + 0x29C));
                *(s32 *)(*(u8 **)(data + 0x29C) + 0x98) = 0;
                func_002AF1D0(arg0, *(u8 **)(data + 0x29C), 3, 0);
                *(s32 *)(data + 0x290) = 1;
                *(f32 *)(arg0 + 0xF0) = 0.0f;
                *(f32 *)(arg0 + 0xF4) = 0.0f;
                func_002833F0(arg0 + 0xC0, arg0 + 0xF0);
            } else {
                func_0029F338(arg0);
                return;
            }
        }
        break;
    case 7:
        *(s32 *)(data + 0x290) = 0;
        p1_7 = D_L11_001B359C[0] + (*(s32 *)(data + 0x548) << 8);
        q1_7 = *(u8 **)(p1_7 + 0x68);
        if (arg0[0x20] != 0x22) {
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                           ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
            a1_7 = func_00283248(func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0xD0 / 4]),
                                 ((Hero *)D_00189E20)->f[0xD8 / 4] - *(f32 *)(arg0 + 0x18));
            func_00283898(q1_7 + 0x10, 1, -a1_7);
        }
        *(f32 *)(arg0 + 0x10) = *(f32 *)(p1_7 + 0x10);
        *(f32 *)(arg0 + 0x14) = *(f32 *)(p1_7 + 0x14);
        *(f32 *)(arg0 + 0x18) = *(f32 *)(p1_7 + 0x18) + 1.5f;
        func_002833F0(p1_7 + 0xC0, arg0 + 0xF0);
        if ((u16)(*(s16 *)(data + 0x264) - 1) >= 2 && arg0[0x20] != 0x20) {
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 0xA);
            func_002A7470(p1_7, 0, 0, 0xA);
            func_002A7750(arg0, 0x22, -1);
        }
        if (arg0[0x20] == 0x22 && *(s16 *)(data + 0x264) == 2) {
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 0xA);
            func_002A7750(arg0, 0x21, -1);
            func_002A7470(p1_7, 1, 0, 0xA);
        }
        break;
    }

    switch (arg0[0x20]) {
    case 1:
        break;
    case 2:
        if (arg0[0x60] & 2) {
            *(u16 *)(arg0 + 0x34) |= 0x5000;
            *(s32 *)(arg0 + 0x98) = *(s32 *)(*(u8 **)(arg0 + 0x24) + 0x10);
            func_002A7750(arg0, 0xE, 1);
            if (*(s16 *)(data + 0x260) < 0x12C)
                *(s16 *)(data + 0x260) = func_002A7820(0x1E0, 0x258);
            if (arg0[0x43] != 1)
                func_002A7470(arg0, 1, 0, 0xA);
        }
        f2_2 = func_0029F530(arg0);
        if (f2_2 >= 10.0f)
            *(f32 *)(arg0 + 0x18) = func_002A89A8(arg0 + 0x10, 0, 0.5f);
        if (f2_2 >= 1.5f && f2_2 <= 17.0f) {
            v0[0] = func_00283180(*(f32 *)(arg0 + 0xF8) + 3.141593f) * 0.15f;
            v0[1] = func_00283198(*(f32 *)(arg0 + 0xF8) + 3.141593f) * 0.15f;
            v0[2] = 0.0f;
            func_00282CC0(arg0 + 0x10, arg0 + 0x10, v0);
            v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8) + 1.5707965f) * 0.05f;
            v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8) + 1.5707965f) * 0.05f;
            v10[2] = 0.0f;
            func_00282CC0(arg0 + 0x10, arg0 + 0x10, v10);
        }
        break;
    case 3:
        if (arg0[0x60] & 2) {
            *(u16 *)(arg0 + 0x34) |= 0x5000;
            *(s32 *)(arg0 + 0x98) = *(s32 *)(*(u8 **)(arg0 + 0x24) + 0x10);
            func_002A7750(arg0, 0xE, 1);
            if (*(s16 *)(data + 0x260) < 0x12C)
                *(s16 *)(data + 0x260) = func_002A7820(0x1E0, 0x258);
            if (arg0[0x43] != 1)
                func_002A7470(arg0, 1, 0, 0xA);
        }
        f2_3 = func_0029F530(arg0);
        if (f2_3 >= 10.0f)
            *(f32 *)(arg0 + 0x18) = func_002A89A8(arg0 + 0x10, 0, 0.5f);
        if (f2_3 >= 1.5f && f2_3 <= 17.0f) {
            v0[0] = func_00283180(*(f32 *)(arg0 + 0xF8) + 3.141593f) * 0.15f;
            v0[1] = func_00283198(*(f32 *)(arg0 + 0xF8) + 3.141593f) * 0.15f;
            v0[2] = 0.0f;
            v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8) + 1.5707965f) * 0.05f;
            v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8) + 1.5707965f) * 0.05f;
            v10[2] = 0.0f;
            qcopy(v20, arg0 + 0x10);
            func_00282CC0(v20, arg0 + 0x10, v10);
            func_00282CC0(v20, arg0 + 0x10, v0);
            func_002A7EA0(arg0, arg0 + 0x10, v20, 0.5f, 0.55f, 0.5f, 0.523598849773407f, 0);
        }
        break;
    case 5:
        if (*(u8 **)(data + 0x55C) != 0) {
            r2_5 = *(s32 *)(data + 0x540);
            if (r2_5 == 1 && arg0[0x42] == 0xD) {
                n2_5 = func_002A77E0(0xC8);
                if (n2_5 == r2_5) {
                    if (arg0[0x43] != 0xC)
                        func_002A7470(arg0, 0xC, 0, 0x1E);
                    if (func_002A77E0(3) == n2_5 && arg0[0x43] != 0xB)
                        func_002A7470(arg0, 0xB, 0, 0x1E);
                }
            }
            if ((u8)(arg0[0x42] - 0xB) < 2 && (arg0[0x60] & 2)) {
                if (arg0[0x43] != 0xE)
                    func_002A7470(arg0, 0xE, 0, 0x1E);
                p2_5 = *(u8 **)(data + 0x55C);
                if (*(s16 *)(p2_5 + 0xAA) == 0xCF6) {
                    *(s32 *)(*(u8 **)(p2_5 + 0x68) + 0x540) = 1;
                    *(s32 *)(data + 0x540) = 2;
                }
            }
            if (arg0[0x42] == 0xE && (arg0[0x60] & 2)) {
                if (arg0[0x43] != 0xF)
                    func_002A7470(arg0, 0xF, 0, 0x1E);
                if (*(s32 *)(data + 0x540) == 1 && arg0[0x43] != 0xD)
                    func_002A7470(arg0, 0xD, 0, 0x1E);
            }
            if (*(s32 *)(data + 0x540) == 1 && arg0[0x42] == 0xF && arg0[0x43] != 0xE)
                func_002A7470(arg0, 0xE, 0, 0x14);
            if (*(s32 *)(data + 0x540) == 3) {
                c2_5 = (*(u8 **)(data + 0x55C))[0x42];
                if (c2_5 == 0xE && arg0[0x43] != c2_5)
                    func_002A7470(arg0, 0xE, 0, 0x23);
            }
        }
        break;
    case 6:
        *(s32 *)(data + 0x290) = 1;
        if (arg0[0x60] & 2) {
            func_002A7750(arg0, 7, -1);
            if (arg0[0x43] != 4)
                func_002A7470(arg0, 4, 0, 0x1E);
            *(s32 *)(data + 0x290) = 0;
        }
        break;
    case 7:
        if (func_002B6120(arg0, D_L11_001FF580[*(s32 *)(data + 0x558)]) != 0) {
            func_002A7750(arg0, 8, -1);
            if (arg0[0x43] != 9)
                func_002A7470(arg0, 9, 0, 0x14);
        }
        break;
    case 8:
        if (arg0[0x60] & 2) {
            func_002B60B0(arg0, 0.0015277779f, 0.045833334f, 0.001163553f, 0.10471977f);
            if (func_002A8508(arg0[0x21], -1) >= 2) {
                *(u8 **)(data + 0x55C) = func_L04_0033D4B0(arg0);
                func_002A7750(arg0, 0xA, -1);
                if (arg0[0x43] != 0xD)
                    func_002A7470(arg0, 0xD, 0, 0x1E);
                *(s32 *)(data + 0x540) = 1;
                if ((*(u8 **)(data + 0x55C))[0x42] == 0xD) {
                    if (arg0[0x43] != 0xF)
                        func_002A7470(arg0, 0xF, 0, 0x1E);
                    *(s32 *)(data + 0x540) = 2;
                }
            }
        }
        break;
    case 10:
        func_002B50E0(arg0, arg0 + 0x10, func_00283248(*(f32 *)(*(u8 **)(data + 0x55C) + 0x10) - *(f32 *)(arg0 + 0x10),
                                                       *(f32 *)(*(u8 **)(data + 0x55C) + 0x14) - *(f32 *)(arg0 + 0x14)));
        if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(*(u8 **)(data + 0x55C) + 0x10) - *(f32 *)(arg0 + 0x10),
                                                              *(f32 *)(*(u8 **)(data + 0x55C) + 0x14) - *(f32 *)(arg0 + 0x14))) < 0.087266475f)
            func_002A7750(arg0, 5, -1);
        break;
    case 11:
        func_002B60B0(arg0, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (func_002B6120(arg0, D_L11_001FF580[*(s32 *)(data + 0x54C)]) != 0) {
            func_002A7750(arg0, 0xC, -1);
            if (arg0[0x43] != 1)
                func_002A7470(arg0, 1, 0, 0x14);
        }
        break;
    case 12:
        if (arg0[0x60] & 2) {
            path2_12 = D_L11_001FF580[*(s32 *)(data + 0x54C)];
            d2_12 = func_00282E80(arg0 + 0x10, path2_12 + 4);
            if (func_00282E80(arg0 + 0x10, (u8 *)path2_12 + *path2_12 * 0x10) < d2_12)
                func_002B6228(arg0, D_L11_001FF580[*(s32 *)(data + 0x54C)], 0, *path2_12 - 1);
            else
                func_002B6228(arg0, D_L11_001FF580[*(s32 *)(data + 0x54C)], *path2_12 - 1, 0);
            func_002A7750(arg0, 0xB, -1);
            if (arg0[0x43] != 4)
                func_002A7470(arg0, 4, 0, 0x14);
        }
        break;
    case 14:
        if (arg0[0x60] & 2) {
            if (arg0[0x43] != 4)
                func_002A7470(arg0, 4, 0, 0x14);
            func_002A7750(arg0, 0xF, -1);
            if (*(s32 *)(data + 0x56C) != -1)
                func_002A7750(arg0, 0x11, -1);
        }
        break;
    case 15:
        func_L01_00321178(arg0, data + 0x110);
        if (func_00282E80(arg0 + 0x10, data + 0x110) < 2.0f) {
            func_002A7750(arg0, 0x10, -1);
            if (arg0[0x43] != 9)
                func_002A7470(arg0, 9, 0, 0x14);
        }
        break;
    case 17:
        func_002B60B0(arg0, 0.0015277779f, 0.045833334f, 0.003781547f, 0.29670602f);
        if (func_002B6120(arg0, D_L11_001FF580[*(s32 *)(data + 0x56C)]) != 0) {
            func_002A7750(arg0, 0x12, -1);
            if (arg0[0x43] != 9)
                func_002A7470(arg0, 9, 0, 0x14);
        }
        break;
    case 18:
        if (arg0[0x60] & 2) {
            path2_18 = D_L11_001FF580[*(s32 *)(data + 0x56C)];
            d2_18 = func_00282E80(arg0 + 0x10, path2_18 + 4);
            if (func_00282E80(arg0 + 0x10, (u8 *)path2_18 + *path2_18 * 0x10) < d2_18)
                func_002B6228(arg0, D_L11_001FF580[*(s32 *)(data + 0x56C)], 0, *path2_18 - 1);
            else
                func_002B6228(arg0, D_L11_001FF580[*(s32 *)(data + 0x56C)], *path2_18 - 1, 0);
            func_002A7750(arg0, 0x11, -1);
            if (arg0[0x43] != 4)
                func_002A7470(arg0, 4, 0, 0x14);
        }
        break;
    case 23:
        if (*(s32 *)(data + 0x57C) != -1) {
            func_002A7750(arg0, 0x18, -1);
        } else if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f &&
                   func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                    ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 6);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            func_002A7750(arg0, 0x1C, 2);
        } else if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                           ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        } else if (*(s32 *)(data + 0x528) != 0) {
            if (func_L11_0042A158(arg0, &((Hero *)D_00189E20)->f[0x80 / 4], *(f32 *)(arg0 + 0xF8), 7.0f, 0.25f, *(f32 *)(data + 0x298)) != 0) {
                c2_23 = arg0[0x21];
                if (D_L11_001B35B8 >= c2_23 && func_002A8508(c2_23, -1) >= 2) {
                    base2_23 = D_L11_001B359C[0];
                    list2_23 = D_L11_001FC420[arg0[0x21]];
                    do {
                        o2_23 = base2_23 + ((*list2_23 & 0x7FFF) << 8);
                        q2_23 = *(u8 **)(o2_23 + 0x68);
                        if (*(s32 *)(q2_23 + 0x294) == 0) {
                            d2_23 = func_00282E80(o2_23 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]);
                            if (d2_23 < func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) && *(f32 *)(q2_23 + 0x20) > 0.0f) {
                                *(s32 *)(q2_23 + 0x294) = 1;
                                *(s32 *)(data + 0x294) = 0;
                                if (arg0[0x43] != 2)
                                    func_002A7470(arg0, 2, 0, 0xA);
                                func_002A7750(arg0, 0x13, 3);
                            }
                            break;
                        }
                    } while (*(s16 *)list2_23++ >= 0);
                }
            }
        } else {
            func_002B4FF0(arg0, &((Hero *)D_00189E20)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        break;
    case 24:
        *(s32 *)(data + 0x290) = 0;
        func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0033936962f, 0.27925274f);
        *(TI128 *)v0 = *(TI128 *)&D_L11_001B368C[0][(*(s32 *)(data + 0x57C) << 7) + 0x30];
        func_L01_00321178(arg0, v0);
        if (func_00282E80(arg0 + 0x10, v0) < 1.5f) {
            if (arg0[0x43] != 0x12)
                func_002A7470(arg0, 0x12, 0, 0x10);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            func_002A7750(arg0, 0x1B, 2);
        }
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 6);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            func_002A7750(arg0, 0x1D, 2);
        }
        break;
    case 25:
        p2_25 = D_L11_001B359C[0] + (*(s32 *)(data + 0x548) << 8);
        q2_25 = *(u8 **)(p2_25 + 0x68);
        if (p2_25[0x20] != 5) {
            func_002AA458(p2_25 + 0xF0, arg0 + 0xF0, data + 0x550, 0.001163553f, 0.0023271059f, 0.10471977f);
            func_002833F0(p2_25 + 0xC0, p2_25 + 0xF0);
            *(f32 *)(p2_25 + 0x18) = *(f32 *)(p2_25 + 0x18) + ((*(f32 *)(q2_25 + 0x5C) - 1.2f) - *(f32 *)(p2_25 + 0x18)) * 0.11f;
        }
        func_L01_00321178(arg0, p2_25 + 0x10);
        if (func_00282E80(arg0 + 0x10, p2_25 + 0x10) < 1.5f && p2_25[0x20] != 5) {
            p2_25[0x20] = 6;
            *(f32 *)(arg0 + 0x10) = *(f32 *)(p2_25 + 0x10);
            *(f32 *)(arg0 + 0x14) = *(f32 *)(p2_25 + 0x14);
            *(f32 *)(arg0 + 0x18) = *(f32 *)(p2_25 + 0x18) + 1.5f;
            *(f32 *)(data + 0x554) = *(f32 *)(p2_25 + 0x18) + 0.75f;
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 0x19);
            func_002A7750(arg0, 0x20, 7);
            arg0[0xBC] = 1;
        }
        break;
    case 32:
        p2_32 = D_L11_001B359C[0] + (*(s32 *)(data + 0x548) << 8);
        func_002AA3A8(p2_32 + 0x18, data + 0x550, *(f32 *)(data + 0x554), 0.00027777778f, 0.0016666667f, 0.033333335f);
        *(f32 *)(arg0 + 0x18) = *(f32 *)(p2_32 + 0x18) + 1.5f;
        if (func_00282C48(*(f32 *)(p2_32 + 0x18) - *(f32 *)(data + 0x554)) < 0.1f) {
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 5);
            func_002A7750(arg0, 0x21, -1);
            if (p2_32[0x43] != 1)
                func_002A7470(p2_32, 1, 0, 5);
        }
        if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                              ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.26179942f &&
            p2_32[0x43] != 1) {
            func_002A7470(p2_32, 1, 0, 5);
            if (arg0[0x43] != 0)
                func_002A7470(arg0, 0, 0, 5);
        } else if (p2_32[0x42] == 1) {
            if (func_US2_002AF9C8(p2_32, 6.0f) != 0 || func_US2_002AF9C8(p2_32, 12.0f) != 0 || func_US2_002AF9C8(p2_32, 0.0f) != 0) {
                func_0029FCC0((u32)p2_32, 1, v0);
                func_00282CF0(v10, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
                func_00282F20(v10, v10, 0.5f);
                func_L11_004349F8(p2_32, v10, v0, 1.0f);
            } else if (func_US2_002AF9C8(p2_32, 3.0f) != 0 || func_US2_002AF9C8(p2_32, 9.0f) != 0 || func_US2_002AF9C8(p2_32, 15.0f) != 0) {
                func_0029FCC0((u32)p2_32, 0, v0);
                func_00282CF0(v10, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
                func_00282F20(v10, v10, 0.5f);
                func_L11_004349F8(p2_32, v10, v0, 1.0f);
            }
        }
        break;
    case 33:
        p2_33 = D_L11_001B359C[0] + (*(s32 *)(data + 0x548) << 8);
        if (func_US2_002AF9C8(p2_33, 6.0f) != 0 || func_US2_002AF9C8(p2_33, 12.0f) != 0 || func_US2_002AF9C8(p2_33, 0.0f) != 0) {
            func_0029FCC0((u32)p2_33, 1, v0);
            func_00282CF0(v10, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
            func_00282F20(v10, v10, 0.5f);
            func_L11_004349F8(p2_33, v10, v0, 1.0f);
        } else if (func_US2_002AF9C8(p2_33, 3.0f) != 0 || func_US2_002AF9C8(p2_33, 9.0f) != 0 || func_US2_002AF9C8(p2_33, 15.0f) != 0) {
            func_0029FCC0((u32)p2_33, 0, v0);
            func_00282CF0(v10, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
            func_00282F20(v10, v10, 0.5f);
            func_L11_004349F8(p2_33, v10, v0, 1.0f);
        }
        break;
    case 34:
        if (*(s32 *)(data + 0x564) != -1) {
            path2_34 = (s32 *)((u8 *)D_L11_001FF580[*(s32 *)(data + 0x564)] + *(s32 *)(data + 0x568) * 0x10);
            p2_34 = D_L11_001B359C[0] + (*(s32 *)(data + 0x548) << 8);
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(*(f32 *)((u8 *)path2_34 + 0x10) - *(f32 *)(arg0 + 0x10),
                                                           *(f32 *)((u8 *)path2_34 + 0x14) - *(f32 *)(arg0 + 0x14)));
            *(f32 *)(arg0 + 0x10) = *(f32 *)(p2_34 + 0x10);
            *(f32 *)(arg0 + 0x14) = *(f32 *)(p2_34 + 0x14);
            *(f32 *)(arg0 + 0x18) = *(f32 *)(p2_34 + 0x18) + 1.5f;
            func_002833F0(p2_34 + 0xC0, arg0 + 0xF0);
            pathb2_34 = (s32 *)((u8 *)D_L11_001FF580[*(s32 *)(data + 0x564)] + *(s32 *)(data + 0x568) * 0x10);
            if (func_00283248(*(f32 *)((u8 *)pathb2_34 + 0x10) - *(f32 *)(arg0 + 0x10),
                              *(f32 *)((u8 *)pathb2_34 + 0x14) - *(f32 *)(arg0 + 0x14)) <= 0.6108653f) {
                if (++*(s32 *)(data + 0x568) >= 2)
                    *(s32 *)(data + 0x568) = 0;
            }
        }
        break;
    case 19:
        *(s32 *)(data + 0x290) = 0;
        func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                       ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        if (*(s32 *)(data + 0x294) == 0) {
            *(s32 *)(data + 0x290) = 1;
            if (arg0[0x43] != 0x11)
                func_002A7470(arg0, 0x11, 0, 0xA);
            func_002A7750(arg0, 0x14, -1);
        } else {
            if (arg0[0x43] != 3)
                func_002A7470(arg0, 3, 0, 0xA);
            func_002A7750(arg0, 0x17, 2);
            if (*(s32 *)(data + 0x284) != -1) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x1A, 2);
            }
        }
        break;
    case 20:
        func_002A7E08(arg0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], data + 0x27C, 0.001f, 0.01f, 0.1f);
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 0xA);
            func_002A7750(arg0, 0x1C, -1);
        }
        n2_20 = func_002A77E0(3);
        if (n2_20 == 1 && (arg0[0x60] & 2)) {
            if (arg0[0x43] != 0xA)
                func_002A7470(arg0, 0xA, 0, 0xA);
            if (func_002A77E0(3) == n2_20 && arg0[0x43] != 9)
                func_002A7470(arg0, 9, 0, 0xA);
            func_002A7750(arg0, 0x13, 3);
        }
        break;
    case 21:
        if (*(s32 *)(data + 0x528) != 0) {
            if (func_L11_0042A158(arg0, &((Hero *)D_00189E20)->f[0x80 / 4], *(f32 *)(arg0 + 0xF8), 7.0f, 0.25f, *(f32 *)(data + 0x298)) != 0) {
                if (arg0[0x43] != 0x11)
                    func_002A7470(arg0, 0x11, 0, 0xA);
                func_002A7750(arg0, 0x14, -1);
            }
        } else {
            func_002B4FF0(arg0, &((Hero *)D_00189E20)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 8.0f) {
            if (arg0[0x43] != 0x11)
                func_002A7470(arg0, 0x11, 0, 0xA);
            func_002A7750(arg0, 0x14, -1);
        }
        break;
    case 22:
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f &&
            func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                             ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 6);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            func_002A7750(arg0, 0x1C, 2);
        } else if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                           ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        } else if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) > 6.0f) {
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            if (arg0[0x43] != 3)
                func_002A7470(arg0, 3, 0, 0xA);
            func_002A7750(arg0, 0x17, -1);
        } else {
            func_002B60B0(arg0, 0.00055555557f, 0.016666668f, 0.001163553f, 0.10471977f);
            func_002B4FF0(arg0, &((Hero *)D_00189E20)->f[0x80 / 4], *(f32 *)(data + 0x298));
        }
        break;
    case 26:
        *(f32 *)(data + 0x174) = 1.5f;
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 2);
            func_002A7750(arg0, 0x1C, -1);
            *(s32 *)(data + 0x284) = -1;
            *(f32 *)(data + 0x164) = 0.00083333335f;
        } else {
            *(f32 *)(data + 0x164) = 0.004166667f;
            if (func_002B6120(arg0, D_L11_001FF580[*(s32 *)(data + 0x284)]) != 0) {
                if (*(s32 *)(data + 0x294) == 1) {
                    if (arg0[0x43] != 3)
                        func_002A7470(arg0, 3, 0, 0xA);
                    func_002A7750(arg0, 0x17, 2);
                } else {
                    *(s32 *)(data + 0x290) = 1;
                    if (func_002A77E0(3) == 1) {
                        if (arg0[0x43] != 2)
                            func_002A7470(arg0, 2, 0, 0xA);
                        func_002A7750(arg0, 0x13, 3);
                    } else {
                        if (arg0[0x43] != 3)
                            func_002A7470(arg0, 3, 0, 0xA);
                        func_002A7750(arg0, 0x15, 3);
                    }
                }
                *(s32 *)(data + 0x284) = -1;
            }
        }
        break;
    case 27:
        if (arg0[0x60] & 2) {
            if (arg0[0x43] != 0x13)
                func_002A7470(arg0, 0x13, 0, 6);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.001163553f, 0.10471977f);
            func_002A7750(arg0, 0x1C, 2);
        }
        func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                       ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        if (arg0[0x42] == 0x12) {
            a2_27 = func_0029F530(arg0);
            func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
            v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            func_00282CC0(v0, v0, v10);
            v0[2] = v0[2] - 0.05f;
            f2_27 = func_002A7878(0.2f, 0.9f) * (a2_27 / D_L11_001B0FFC);
            n2_27 = func_002A77E0(2);
            if (n2_27 == 0) n2_27 = n2_27 - 1;
            func_002C2210(v0, 2, D_L11_001B0FEC, 0, n2_27, D_L11_001A8F20, f2_27 * 0.3f, f2_27, 0.0f, 0);
            func_002C2210(v0, 2, D_L11_001B0FF8, 1, -n2_27, D_L11_001A8F20, f2_27 * 0.04f, f2_27 * 0.4f, 0.0f, 0);
            *(f32 *)(data + 0x574) = *(f32 *)(data + 0x574) + 1.0f;
        }
        if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
            if (arg0[0x43] != 5)
                func_002A7470(arg0, 5, 0, 6);
            func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
            func_002A7750(arg0, 0x1D, 2);
        }
        break;
    case 28:
        func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                       ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        *(s32 *)(data + 0x290) = 0;
        if (func_US2_002AF9C8(arg0, 1.0f) != 0 || func_US2_002AF9C8(arg0, 7.0f) != 0 || func_US2_002AF9C8(arg0, 14.0f) != 0) {
            if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                  ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.78539824f) {
                func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] = v0[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)v0;
                func_00282CF0(data + 0x5A0, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
                *(s32 *)(data + 0x578) = 0;
                func_L00_003294F0(arg0, 0);
                *(TI128 *)v20 = *(TI128 *)(data + 0x580);
                *(TI128 *)v30 = *(TI128 *)(data + 0x5A0);
                func_L11_004349F8(arg0, v20, v30, *(f32 *)(data + 0x28C));
                func_00282CF0(v20, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
                func_00282F20(v20, v20, 0.8333334f);
            } else {
                func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] = v0[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)v0;
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                func_00282CC0(v10, v10, arg0 + 0x10);
                func_00282CF0(data + 0x5A0, v10, v0);
                *(s32 *)(data + 0x578) = 0;
                func_L00_003294F0(arg0, 0);
                *(TI128 *)v20 = *(TI128 *)(data + 0x580);
                *(TI128 *)v30 = *(TI128 *)(data + 0x5A0);
                func_L11_004349F8(arg0, v20, v30, *(f32 *)(data + 0x28C));
            }
        }
        if (arg0[0x60] & 2) {
            if (arg0[0x43] != 0x14)
                func_002A7470(arg0, 0x14, 0, 0x14);
            if (*(s32 *)(data + 0x5B4) != 0 && arg0[0x43] != 0xA)
                func_002A7470(arg0, 0xA, 0, 0x14);
            func_002A7750(arg0, 0x1E, -1);
            if (arg0[0x95] != 2) {
                func_002A7750(arg0, 0x14, -1);
                if (arg0[0x43] != 0x11)
                    func_002A7470(arg0, 0x11, 0, 0xA);
            }
            *(f32 *)(data + 0x574) = 0.0f;
        }
        break;
    case 29:
        func_002B50E0(arg0, arg0 + 0x10, func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                       ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14)));
        *(s32 *)(data + 0x290) = 0;
        if (arg0[0x42] == 5 && func_0029F530(arg0) < 11.0f) {
            a2_29 = func_0029F530(arg0);
            func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
            v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            func_00282CC0(v0, v0, v10);
            v0[2] = v0[2] - 0.05f;
            f2_29 = func_002A7878(0.2f, 0.9f) * (a2_29 / D_L11_001B0FFC);
            n2_29 = func_002A77E0(2);
            if (n2_29 == 0) n2_29 = n2_29 - 1;
            func_002C2210(v0, 2, D_L11_001B0FEC, 0, n2_29, D_L11_001A8F20, f2_29 * 0.3f, f2_29, 0.0f, 0);
            func_002C2210(v0, 2, D_L11_001B0FF8, 1, -n2_29, D_L11_001A8F20, f2_29 * 0.04f, f2_29 * 0.4f, 0.0f, 0);
            *(f32 *)(data + 0x574) = *(f32 *)(data + 0x574) + 1.0f;
        }
        if (func_US2_002AF9C8(arg0, 11.0f) != 0) {
            if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(arg0 + 0x10),
                                                                  ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(arg0 + 0x14))) < 0.78539824f) {
                func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] = v0[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)v0;
                func_00282CF0(data + 0x5A0, &((Hero *)D_00189E20)->f[0xD0 / 4], v0);
                *(s32 *)(data + 0x578) = 0;
                func_L00_003294F0(arg0, 0);
                *(TI128 *)v20 = *(TI128 *)(data + 0x580);
                *(TI128 *)v30 = *(TI128 *)(data + 0x5A0);
                func_L11_004349F8(arg0, v20, v30, *(f32 *)(data + 0x28C));
            } else {
                func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] = v0[2] - 0.05f;
                *(TI128 *)(data + 0x580) = *(TI128 *)v0;
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                func_00282CC0(v10, v10, arg0 + 0x10);
                func_00282CF0(data + 0x5A0, v10, v0);
                *(s32 *)(data + 0x578) = 0;
                func_L00_003294F0(arg0, 0);
                *(TI128 *)v20 = *(TI128 *)(data + 0x580);
                *(TI128 *)v30 = *(TI128 *)(data + 0x5A0);
                func_L11_004349F8(arg0, v20, v30, *(f32 *)(data + 0x28C));
            }
        }
        g2_29 = func_0029F530(arg0);
        if (arg0[0x42] == 5 && g2_29 >= 10.0f && g2_29 <= 15.0f) {
            func_0029FCC0(*(u32 *)(data + 0x278), 0, v0);
            func_002A8C28(arg0, v0, 1, 0.4f, *(f32 *)(data + 0x28C), 1.0f, 0, 1, 0);
        }
        if (arg0[0x60] & 2) {
            if (arg0[0x43] != 0x11)
                func_002A7470(arg0, 0x11, 0, 0x14);
            func_002A77E0(3);
            func_002A7750(arg0, 0x1E, -1);
            if (arg0[0x95] != 2) {
                func_002A7750(arg0, 0x14, -1);
                if (arg0[0x43] != 0x11)
                    func_002A7470(arg0, 0x11, 0, 0xA);
            }
            *(f32 *)(data + 0x574) = 0.0f;
        }
        break;
    case 30:
        if (arg0[0x60] & 2) {
            *(s32 *)(data + 0x5B0) = 0;
            if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x17, -1);
            } else {
                if (arg0[0x43] != 3)
                    func_002A7470(arg0, 3, 0, 0xA);
                func_002A7750(arg0, 0x17, -1);
            }
            *(TI128 *)v0 = *(TI128 *)&D_L11_001B368C[0][(*(s32 *)(data + 0x57C) << 7) + 0x30];
            func_L01_00321178(arg0, v0);
            if (func_00282E80(arg0 + 0x10, v0) < 1.5f) {
                if (*(s32 *)(data + 0x5B4) != 0) {
                    if (arg0[0x43] != 0x12)
                        func_002A7470(arg0, 0x12, 0, 0x14);
                } else if (arg0[0x43] != 0x12) {
                    func_002A7470(arg0, 0x12, 0, 6);
                }
                func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                func_002A7750(arg0, 0x1B, 2);
            }
            if (func_00282E80(arg0 + 0x10, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.5f) {
                if (arg0[0x43] != 5)
                    func_002A7470(arg0, 5, 0, 6);
                func_002B60B0(arg0, 0.003888889f, 0.116666675f, 0.0035876217f, 0.27925274f);
                func_002A7750(arg0, 0x1D, 2);
            }
        }
        break;
    }
    func_L11_0042A420(arg0);
    if (func_00282C48(*(f32 *)(arg0 + 0x18) - z0) < 0.005f)
        *(f32 *)(arg0 + 0x18) = z0;
}
