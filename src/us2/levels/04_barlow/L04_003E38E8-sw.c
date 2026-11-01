#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;
extern char D_00189E20[];
extern s32 D_L04_001C9C00[];
extern s32 D_L04_001A8F00;
extern s32 *D_L04_001FE340[];
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern char D_L04_001A8F20[] __attribute__((sda));
extern u8 D_L04_001C7800[];
extern TI128 D_L04_001BFAE0;
extern s32 func_L04_003E4C00(u8 *);
extern void func_L04_003E51F0(u8 *);
extern void func_L04_003E5318(u8 *);
extern void func_L04_003E5B10(u8 *, void *);
extern void func_L04_003E2338(u8 *);
extern s32 func_002B3890(u8 *);
extern void func_002B60B0(u8 *, f32, f32, f32, f32);
extern void func_002A7750(u8 *, s32, s32);
extern void func_002A7470(u8 *a0, u32 a1, u32 a2, u32 a3);
extern s32 func_002A7820(s32, s32);
extern s32 func_002A77E0(s32);
extern s32 func_002A8AF0(void *, void *, s32);
extern s32 func_002B1C20(u8 *, void *);
extern void func_US2_002A7AA8(u8 *, s32, s32);
extern void func_L01_003E9CF8(u8 *, s32, void *);
extern void func_0029F338(void *);
extern f32 func_002A7878(f32, f32);
extern s32 func_00282948(void *);
extern s32 func_00282978(void *);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002AE8C0(u8 *, void *, f32, f32);
extern s32 func_002B6120(u8 *, void *);
extern s32 func_002B6228(u8 *, void *, s32, s32);
extern f32 func_002A7E08(u8 *, void *, void *, f32, f32, f32);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern s32 func_L01_00321178(u8 *, void *);
extern void func_0029FCC0(u32 a0, s32 a1, f32 *a2);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern void func_00282D30(void *, void *, f32);
extern void func_002A8C00(void *, void *, s32, f32, void *);
extern void func_002A8C28(void *, void *, s32, f32, f32, f32, s32, s32, s32);
extern s32 func_00277F48(void *, f32, s32, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern s32 func_L02_00331440(u8 *, void *, f32, s32, f32, f32);
extern f32 func_0029F530(u8 *);
extern void func_002C2210(void *, u32, f32, f32, u32, u32, s32, void *, f32, s32);
extern s32 func_002A8D70(void *, f32, f32, s32, s32, f32, s32, s32, s32);
extern s32 func_US2_002AF9C8(u8 *, f32);
extern void func_L00_003294F0(u8 *, s32);
extern s32 func_L00_002FCF18(void *, f32, f32, f32, f32, f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_002B38B8(u8 *);
extern void func_L04_003E5830(void *, s32);
extern void func_L00_002E6EF8(void *, void *);
extern void func_00291450(s32);
extern s32 func_002B50E0(u8 *, void *, f32);
extern void func_L04_003E22B0(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);

void func_US2_L04_003E38E8(u8 *arg0) {
    u8 *data;

    data = *(u8 **)(arg0 + 0x68);
    if (D_L04_001C9C00[0] == 1) {
        if (D_L04_001A8F00 == 2) {
            *(s32 *)(arg0 + 0x98) = 0;
            *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        } else {
            *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) & 0xFFBE) | 0x1000;
            *(s32 *)(arg0 + 0x98) = *(s32 *)(*(u8 **)(arg0 + 0x24) + 0x10);
        }
    }
    if (func_L04_003E4C00(arg0) != 0) {
        func_0029F338(arg0);
        return;
    }

    switch (arg0[0x95]) {
    case 0: {
        s32 s;

        s = *(s32 *)(data + 0x2F0);
        if (s != -1)
            break;
        if (func_002B3890(arg0) != 0) {
            func_002B60B0(arg0, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            if (*(f32 *)(data + 0x2C0) < 0.2f)
                func_L04_003E22B0(arg0, 4, 3, 0, 0xC);
            if (*(s32 *)(data + 0x2CC) != s && *(s32 *)(data + 0x2C4) == s) {
                func_L04_003E22B0(arg0, 5, 4, 0, 0xC);
                func_002A7750(arg0, 2, -1);
            }
        }
        if (*(s32 *)(data + 0x258) == 1 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6F) {
            if (*(s32 *)(data + 0x2C4) != -1) {
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002B60B0(arg0, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
                *(f32 *)(data + 0x164) = 0.0055555557f;
                func_002A7750(arg0, 0xD, 2);
            } else if (*(u8 **)(data + 0x2AC) != 0) {
                func_002A7750(arg0, 0xA, 2);
            } else {
                func_L04_003E22B0(arg0, 0, 2, 0, 0xA);
                func_002A7750(arg0, 0xA, 2);
            }
        } else if (*(s16 *)(data + 0x2A6) != 0) {
            func_002A7750(arg0, 8, 1);
            *(s16 *)(data + 0x2A6) = 0;
            if (*(s16 *)(data + 0x2A0) < 0x12C)
                *(s16 *)(data + 0x2A0) = func_002A7820(0x1E0, 0x258);
            if (*(s32 *)(data + 0x2CC) != -1) {
                func_002A7750(arg0, 8, 1);
                func_L04_003E22B0(arg0, 4, 3, 0, 0xC);
            }
        } else if (*(s32 *)(data + 0x2DC) != -1 &&
                   func_002A8AF0(data + 0x230, (u8 *)D_L04_001FE340[*(s32 *)(data + 0x2DC)] + 0x10,
                                 *D_L04_001FE340[*(s32 *)(data + 0x2DC)]) != 0) {
            func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
            func_002B60B0(arg0, 0.016666668f, 0.5f, 0.001163553f, 0.10471977f);
            *(f32 *)(data + 0x164) = 0.0055555557f;
            func_002A7750(arg0, 0xD, 2);
        }
        break;
    }
    case 1:
        if (func_002B3890(arg0) != 0)
            func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(data + 0x258) == 1 || *(s32 *)(data + 0x25C) == 1) {
            if (*(u8 **)(data + 0x2AC) != 0) {
                func_002A7750(arg0, 0xA, 2);
            } else {
                func_L04_003E22B0(arg0, 0, 2, 0, 0xA);
                func_002A7750(arg0, 0xA, 2);
            }
        } else if (*(s16 *)(data + 0x2A0) == 0 && *(s32 *)(data + 0x30C) == 0) {
            func_002A7750(arg0, 1, 0);
            func_L04_003E22B0(arg0, 5, 4, 0, 0xC);
        }
        break;
    case 2:
        if (func_002B3890(arg0) != 0)
            func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if ((*(s32 *)(data + 0x2DC) == -1 ||
             func_002A8AF0(data + 0x230, (u8 *)D_L04_001FE340[*(s32 *)(data + 0x2DC)] + 0x10,
                           *D_L04_001FE340[*(s32 *)(data + 0x2DC)]) == 0) &&
            *(s32 *)(data + 0x258) != 1 && *(s32 *)(data + 0x25C) != 1) {
            if (arg0[0x20] == 0xD || arg0[0x20] == 0x10 || arg0[0x20] == 0xC) {
            } else if (arg0[0x20] == 0xF) {
                func_L04_003E22B0(arg0, 8, 0, 1, 3);
                func_002A7750(arg0, 0x10, -1);
            } else if (*(s32 *)(data + 0x2CC) != -1 && *(s32 *)(data + 0x2C4) == -1) {
                func_L04_003E22B0(arg0, 5, 4, 0, 0xC);
                func_002A7750(arg0, 2, 1);
            } else {
                *(s32 *)(data + 0x2D0) = 0;
                func_L04_003E22B0(arg0, 3, 1, 0, 0xC);
                func_002A7750(arg0, 8, 1);
                if (*(s32 *)(data + 0x2D4) != -1) {
                    qcopy(data + 0x110, D_L04_001B25CC[0] + (*(s32 *)(data + 0x2D4) << 7) + 0x30);
                    if (*(f32 *)(data + 0x12C) == 0.0f)
                        *(f32 *)(data + 0x12C) = 4.0f;
                }
                *(s16 *)(data + 0x2A0) = func_002A7820(0x4B0, 0x514);
            }
        }
        break;
    case 3: {
        s32 r;
        s32 s;

        r = func_002B1C20(arg0, data + 0x60);
        if (r & 1) {
            func_US2_002A7AA8(arg0, 0, 3);
            func_L01_003E9CF8(arg0, 0, 0);
            return;
        }
        if (r & 2) {
            s = *(s32 *)(data + 0x2F0);
            if (s != -1) {
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002A7750(arg0, 7, 0);
                *(s8 *)(data + 0x307) = 0x78;
            } else if (*(s32 *)(data + 0x258) == 1 || *(s32 *)(data + 0x25C) == 1) {
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002A7750(arg0, 0xB, 2);
            } else {
                func_002A7750(arg0, 8, 1);
                func_L04_003E22B0(arg0, 1, 1, 0, 0xA);
                *(s16 *)(data + 0x2A0) = func_002A7820(0x244, 0x258);
                if (*(s32 *)(data + 0x2CC) != -1) {
                    func_002A7750(arg0, 8, 1);
                    func_L04_003E22B0(arg0, 4, 3, 0, 0xC);
                }
            }
        }
        break;
    }
    }

    switch (arg0[0x20]) {
    case 1:
        if (*(f32 *)(data + 0x2C0) > 0.2f) {
            func_00282948(data + 0x2BC);
            if (*(s32 *)(data + 0x2BC) >= 0x15)
                *(f32 *)(data + 0x124) = 0.06666667f;
            else
                func_002AA2E8((f32 *)(data + 0x124), 0.0f, 0.0011111111f);
            if (arg0[0x43] == 5) {
                if (*(s32 *)(data + 0x2BC) == 0) {
                    func_L04_003E22B0(arg0, 1, 1, 0, 0xC);
                    if (func_002A77E0(2) == 1)
                        func_L04_003E22B0(arg0, 0, 0, 0, 0xC);
                }
                func_002AE8C0(arg0, data + 0x110, 0.35f, 0.25f);
            } else if (arg0[0x43] < 2 && (arg0[0x60] & 2)) {
                *(s32 *)(data + 0x2BC) = func_002A7820(0x78, 0x2BC);
                func_L04_003E22B0(arg0, 5, 4, 0, 0xC);
            }
        } else if (*(u8 **)(data + 0x2AC) != 0 && (*(u8 **)(data + 0x2AC))[0x43] != 3) {
            func_L04_003E22B0(arg0, 4, 3, 0, 0xC);
        }
        break;
    case 2:
        if (func_002B6120(arg0, D_L04_001FE340[*(s32 *)(data + 0x2CC)]) != 0) {
            func_002A7750(arg0, 4, -1);
            func_L04_003E22B0(arg0, 4, 3, 0, 0xA);
            func_002B6228(arg0, D_L04_001FE340[*(s32 *)(data + 0x2CC)], 0, 1);
            *(s32 *)(data + 0x308) = 1;
        }
        break;
    case 3:
        if (func_002B6120(arg0, D_L04_001FE340[*(s32 *)(data + 0x2CC)]) != 0) {
            func_002A7750(arg0, 4, -1);
            func_L04_003E22B0(arg0, 4, 3, 0, 0xA);
            func_002B6228(arg0, D_L04_001FE340[*(s32 *)(data + 0x2CC)], 1, 0);
            *(s32 *)(data + 0x308) = 0;
        }
        break;
    case 4:
        if (arg0[0x60] & 2) {
            func_L04_003E22B0(arg0, 0xF, 0x17, 0, 7);
            func_002A7750(arg0, 0x15, -1);
        }
        break;
    case 5:
        if (func_00282978(data + 0x300) != 0) {
            func_L04_003E22B0(arg0, 5, 4, 0, 0xA);
            func_L04_003E2338(arg0);
            func_002A7750(arg0, 6, 0);
        }
        break;
    case 6: {
        {
        f32 v[4] __attribute__((aligned(16)));

        *(TI128 *)v = *(TI128 *)(data + 0x280);
        func_002B60B0(arg0, 0.00044444445f, 0.02666667f, 0.001163553f, 0.10471977f);
        func_L01_00321178(arg0, v);
        if (func_00282E80(arg0 + 0x10, v) < 1.0f) {
            func_L04_003E22B0(arg0, 1, 1, 0, 0xA);
            *(s16 *)(data + 0x300) = func_002A7820(0x4B0, 0xBB8);
            func_002A7750(arg0, 5, -1);
        }
        }
        break;
    }
    case 7: {
        {
        f32 v[4] __attribute__((aligned(16)));
        f32 m;

        *(TI128 *)v = *(TI128 *)(data + 0x280);
        func_002B60B0(arg0, 0.0006666667f, 0.040000003f, 0.001163553f, 0.10471977f);
        func_L04_003E5B10(arg0, v);
        m = *(f32 *)(data + 0x16C) * 30.0f;
        if (m < *(f32 *)(data + 0x1E8))
            *(f32 *)(data + 0x1E8) = m;
        if (func_00282E80(arg0 + 0x10, v) < 1.0f || *(s32 *)(data + 0x1C0) >= 0x3D) {
            func_L04_003E22B0(arg0, 1, 1, 0, 0xA);
            *(s16 *)(data + 0x300) = func_002A7820(0x4B0, 0xBB8);
            func_002A7750(arg0, 5, -1);
        }
        }
        break;
    }
    case 8:
        func_00282948(data + 0x2BC);
        if (*(s32 *)(data + 0x2BC) >= 0x15)
            func_002AA2E8((f32 *)(data + 0x124), 0.06666667f, 0.0019444445f);
        else
            func_002AA2E8((f32 *)(data + 0x124), 0.0f, 0.0019444445f);
        if (arg0[0x43] == 6) {
            if (*(s32 *)(data + 0x2BC) == 0) {
                func_L04_003E22B0(arg0, 3, 2, 0, 0xC);
                if (func_002A77E0(2) == 1)
                    func_L04_003E22B0(arg0, 4, 3, 0, 0xC);
            }
            func_002AE8C0(arg0, data + 0x110, 0.35f, 0.25f);
        } else if ((u8)(arg0[0x43] - 3) < 2 && (arg0[0x60] & 2)) {
            *(s32 *)(data + 0x2BC) = func_002A7820(0x78, 0x2BC);
            func_L04_003E22B0(arg0, 6, 5, 0, 0xC);
        }
        break;
    case 9:
        if (arg0[0x60] & 2) {
            func_L04_003E22B0(arg0, 5, 4, 0, 0xC);
            func_002A7750(arg0, 2, -1);
        }
        break;
    case 10:
        func_002A7E08(arg0, *(void **)(data + 0x240), data + 0x2B4, 0.001f, 0.01f, 0.1f);
        if (*(u8 **)(data + 0x2AC) != 0) {
            func_002A7750(arg0, 0x14, -1);
            func_L04_003E22B0(arg0, 0x10, 4, 0, 0xA);
        } else if (*(s32 *)(data + 0x2D8) != 0) {
            func_002A7750(arg0, 0xF, -1);
            func_L04_003E22B0(arg0, 7, 5, 0, 0xA);
        } else {
            func_002A7750(arg0, 0xB, -1);
            func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
        }
        break;
    case 11:
        func_L04_003E5B10(arg0, data + 0x230);
        *(s32 *)(data + 0x2B0) = *(s32 *)(data + 0x2B0) + 1;
        if (*(u8 **)(data + 0x2AC) != 0) {
            if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) < 20.0f &&
                func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                                 *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) < 0.17453295f) {
                func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
                func_002A7750(arg0, 0xE, -1);
            }
        } else {
            if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) < 2.7f &&
                func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                                 *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
                func_L04_003E22B0(arg0, 0xC, 0, 0, 5);
                func_002A7750(arg0, 0x11, -1);
            }
            if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) > 2.7f && (arg0[0x42] == 5 || arg0[0x42] == 0x10)) {
                func_L04_003E22B0(arg0, 6, 5, 0, 4);
                func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    case 15: {
        *(f32 *)(data + 0x164) = 0.0069444445f;
        func_002B60B0(arg0, 0.006666667f, 0.20000002f, 0.001163553f, 0.10471977f);
        func_L01_00321178(arg0, data + 0x230);
        func_002A7E08(arg0, *(void **)(data + 0x240), data + 0x2B4, 0.001f, 0.01f, 0.1f);
        *(s32 *)(data + 0x2B0) = *(s32 *)(data + 0x2B0) + 1;
        if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) < 3.5f) {
            func_L04_003E22B0(arg0, 8, 0, 1, 3);
            *(f32 *)(arg0 + 0x48) = 1.0f;
            func_002A7750(arg0, 0x10, -1);
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));
        f32 z;

        func_0029FCC0((u32)arg0, 1, pos);
        dir[0] = func_00283180(*(f32 *)(arg0 + 0xF8));
        dir[1] = func_00283198(*(f32 *)(arg0 + 0xF8));
        dir[2] = 0.0f;
        z = dir[2];
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        func_00282D30(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        func_002A8C00(req, arg0, 1, *(f32 *)(data + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
        req[0x18] = 0;
        func_00277F48(pos, 1.1f, 0, arg0, req);
        func_002A8C28(arg0, pos, 0x10000, 1.1f, *(f32 *)(data + 0x2E8) * 4.0f, z, 0, 1, 0);
        }
        break;
    }
    case 16: {
        u8 *p;

        p = arg0 + 0x10;
        {
        f32 off[4] __attribute__((aligned(16)));
        func_002B60B0(arg0, 0.004166667f, 0.033333335f, 0.001163553f, 0.10471977f);
        off[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 4.0f;
        off[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 4.0f;
        off[2] = 0.0f;
        func_00282CC0(off, p, off);
        func_L01_00321178(arg0, data + 0x230);
        *(s32 *)(data + 0x2B0) = *(s32 *)(data + 0x2B0) + 1;
        if (arg0[0x60] & 2) {
            func_L04_003E22B0(arg0, 2, 2, 0, 0xA);
            func_002A7750(arg0, 0xC, -1);
            if (func_00282E80(p, &((Hero *)D_00189E20)->f[0x80 / 4]) < 3.0f) {
                func_002B60B0(arg0, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                if (arg0[0x43] != 0x11)
                    func_002A7470(arg0, 0x11, 0, 0xA);
                func_002A7750(arg0, 0x17, -1);
            }
        }
        }
        {
        f32 pos[4] __attribute__((aligned(16)));
        f32 scaled[4] __attribute__((aligned(16)));
        f32 dir[4] __attribute__((aligned(16)));
        u8 req[0x30] __attribute__((aligned(16)));

        func_0029FCC0((u32)arg0, 1, pos);
        dir[0] = func_00283180(*(f32 *)(arg0 + 0xF8));
        dir[1] = func_00283198(*(f32 *)(arg0 + 0xF8));
        dir[2] = 2.0f;
        qcopy(scaled, dir);
        func_00282D30(scaled, scaled, 2.5f);
        scaled[3] = 5627.925f;
        func_002A8C00(req, arg0, 0x04000001, *(f32 *)(data + 0x2E8), scaled);
        req[0x19] = 1;
        *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
        req[0x18] = 0;
        func_00277F48(pos, 1.3f, 0, arg0, req);
        }
        break;
    }
    case 23: {
        func_002B60B0(arg0, 0.0011111111f, 0.033333335f, 0.001163553f, 0.10471977f);
        {
        f32 v[4] __attribute__((aligned(16)));

        func_00282F20(v, arg0 + 0xC0, -5.5f);
        func_00282CC0(v, v, arg0 + 0x10);
        func_L02_00331440(arg0, v, func_00283248(v[0] - *(f32 *)(arg0 + 0x10), v[1] - *(f32 *)(arg0 + 0x14)), 0x10, -1.0f, -1.0f);
        }
        if (*(u16 *)(arg0 + 0x96) >= 0x79) {
            *(f32 *)(data + 0x164) = 0.00083333335f;
            if (*(u8 **)(data + 0x2AC) != 0) {
                func_002B60B0(arg0, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
                func_002A7750(arg0, 0xE, -1);
            } else {
                func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002A7750(arg0, 0xB, -1);
            }
        }
        break;
    }
    case 12:
        if (arg0[0x60] & 2) {
            *(f32 *)(data + 0x164) = 0.00083333335f;
            if (*(u8 **)(data + 0x2AC) != 0) {
                func_002B60B0(arg0, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
                func_002A7750(arg0, 0xE, -1);
            } else {
                func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002A7750(arg0, 0xB, -1);
            }
        }
        break;
    case 13:
        func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
        if (func_002B6120(arg0, D_L04_001FE340[*(s32 *)(data + 0x2C4)]) != 0) {
            func_002A7750(arg0, 0x14, -1);
            func_L04_003E22B0(arg0, 0x10, 4, 0, 0xA);
            func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(s32 *)(data + 0x2C4) = -1;
            *(f32 *)(data + 0x164) = 0.00083333335f;
            *(s32 *)(data + 0x2DC) = -1;
        }
        break;
    case 14: {
        f32 v0[4] __attribute__((aligned(16)));
        f32 v10[4] __attribute__((aligned(16)));
        f32 f, g;
        s32 n;

        if (*(u8 **)(data + 0x2AC) != 0 && arg0[0x42] == 9) {
            func_0029FCC0(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x2AC) + 0x68) + 0x288), 0, v0);
            v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
            v10[2] = 0.0f;
            func_00282CC0(v0, v0, v10);
            v0[2] -= 0.05f;
            g = func_0029F530(arg0);
            f = func_002A7878(0.2f, 0.9f) * 0.2f * g;
            n = func_002A77E0(2);
            if (n == 0)
                n = n - 1;
            func_002C2210(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
            func_002C2210(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            *(f32 *)(data + 0x2B8) = g;
        }
        if (*(u16 *)(arg0 + 0x96) >= 0x2E) {
            func_L04_003E22B0(arg0, 0xA, 7, 0, 0xA);
            func_002A7750(arg0, 0x12, -1);
        }
        break;
    }
    case 17: {
        f32 f;

        f = func_0029F530(arg0);
        if (arg0[0x42] == 0xC && f >= 10.0f && f <= 15.0f)
            func_002A8D70(arg0, 1.0f, *(f32 *)(data + 0x2E4), 1, 0x04000001, 1.0f, 0, 1, 0);
        if (arg0[0x60] & 2) {
            if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) < 2.7f &&
                func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                                 *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) < 0.3490659f) {
                func_L04_003E22B0(arg0, 0xC, 0, 0, 0xA);
                func_002A7750(arg0, 0x11, -1);
            } else {
                func_002A7750(arg0, 0xB, -1);
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                func_002B60B0(arg0, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            }
        }
        break;
    }
    case 18: {
        f32 t;
        f32 hp;

        if (arg0[0x60] & 2) {
            if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) < 25.0f && *(u8 **)(data + 0x2AC) != 0 &&
                *(s32 *)(data + 0x2D0) < 3) {
                if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                                     *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) > 0.087266475f) {
                    func_002A7750(arg0, 0x14, -1);
                    func_L04_003E22B0(arg0, 0x10, 4, 0, 0xA);
                } else {
                    func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
                    func_002A7750(arg0, 0xE, -1);
                }
            } else if (func_00282E80(arg0 + 0x10, *(u8 **)(data + 0x240) + 0x10) > 10.0f && *(u8 **)(data + 0x2AC) != 0 &&
                       *(s32 *)(data + 0x2D0) >= 3) {
                func_L04_003E22B0(arg0, 3, 2, 0, 0xA);
                func_002A7750(arg0, 0x13, -1);
                *(s32 *)(data + 0x2D0) = 0;
            } else {
                func_002A7750(arg0, 0x14, -1);
                func_L04_003E22B0(arg0, 0x10, 4, 0, 0xA);
            }
            if (*(u8 **)(data + 0x2AC) != 0) {
                *(s32 *)(data + 0x2D0) = *(s32 *)(data + 0x2D0) + 1;
            } else {
                func_002A7750(arg0, 0xB, -1);
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
                break;
            }
        } else if (func_US2_002AF9C8(arg0, 3.0f) != 0 && *(u8 **)(data + 0x2AC) != 0) {
            f32 v0[4] __attribute__((aligned(16)));
            f32 v10[4] __attribute__((aligned(16)));

            if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                                 *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) < 0.78539824f) {
                s32 k;
                u8 *l;

                func_0029FCC0(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(data + 0x260) = *(TI128 *)v0;
                func_00282CF0(data + 0x280, data + 0x230, v0);
                *(f32 *)(data + 0x2C8) = 0.0f;
                func_L00_003294F0(arg0, 0);
                k = func_L00_002FCF18(arg0 + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(data + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, data + 0x260);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else {
                s32 k;
                u8 *l;

                func_0029FCC0(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] -= 0.05f;
                *(TI128 *)(data + 0x260) = *(TI128 *)v0;
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 25.0f;
                v10[2] = 0.0f;
                func_00282CC0(v10, v10, arg0 + 0x10);
                func_00282CF0(data + 0x280, v10, v0);
                *(f32 *)(data + 0x2C8) = 0.0f;
                func_L00_003294F0(arg0, 0);
                k = func_L00_002FCF18(arg0 + 0x10, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                *(s32 *)(data + 0x2E0) = k;
                if (k >= 0) {
                    l = D_L04_001C7800 + (k << 5);
                    qcopy(l + 0x10, data + 0x260);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            }
        }
        t = func_0029F530(arg0);
        if (t < 3.0f || arg0[0x42] != 0xA) {
            if (*(u8 **)(data + 0x2AC) != 0) {
                f32 v0[4] __attribute__((aligned(16)));
                f32 v10[4] __attribute__((aligned(16)));
                f32 f;
                s32 n;

                func_0029FCC0(*(u32 *)(*(u8 **)(*(u8 **)(data + 0x2AC) + 0x68) + 0x288), 0, v0);
                v10[0] = func_00283180(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[1] = func_00283198(*(f32 *)(arg0 + 0xF8)) * 0.1f;
                v10[2] = 0.0f;
                func_00282CC0(v0, v0, v10);
                v0[2] -= 0.05f;
                f = func_002A7878(0.2f, 0.9f) * 0.2f * *(f32 *)(data + 0x2B8);
                n = func_002A77E0(2);
                if (n == 0)
                    n = n - 1;
                func_002C2210(v0, 2, f * 0.3f, f, 0x804020FF, 0, n, D_L04_001A8F20, 0.0f, 0);
                func_002C2210(v0, 2, f * 0.04f, f * 0.4f, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
                *(f32 *)(data + 0x2B8) = *(f32 *)(data + 0x2B8) + 1.0f;
            }
        }
        hp = (f32)data[0x35];
        if (t >= 3.0f) {
            if (t < 9.0f) {
                if (arg0[0x42] == 0xA) {
            u8 req[0x30] __attribute__((aligned(16)));
            f32 v30[4] __attribute__((aligned(16)));
                                    u8 *l;
            f32 f, f3, f04, f4;
            s32 n;

            *(f32 *)(data + 0x2C8) = *(f32 *)(data + 0x2C8) + 1.0f;
            func_00282F20(data + 0x270, data + 0x280, *(f32 *)(data + 0x2C8));
            func_002A8C00(req, arg0, 0x04000001, hp, data + 0x270);
            *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
            func_00282CC0(data + 0x270, data + 0x260, data + 0x270);
            if (func_002761F8(data + 0x260, data + 0x270, 0, arg0, req) != 0) {
                *(TI128 *)(data + 0x270) = D_L04_001BFAE0;
                if (func_002B38B8(arg0) == 0) {
                    func_L04_003E5830(&D_L04_001BFAE0, 0x1E);
                    func_L00_003294F0(arg0, 1);
                }
            }
            f = func_002A7878(1.0f, 6.0f);
            n = func_002A7820(0x19, 0x23);
            if (n == 0)
                n = n - 1;
            qcopy(v30, data + 0x270);
            v30[2] -= 0.1f;
            f3 = f * 0.3f;
            func_002C2210(v30, 0x19, f3, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
            n = -n;
            f04 = f * 0.04f;
            f4 = f * 0.4f;
            func_002C2210(v30, 5, f04, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
            func_002C2210(v30, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
            func_002C2210(data + 0x260, 0xA, f3, f, 0x80CA00CB, 0, n, D_L04_001A8F20, 0.0f, 0);
            func_002C2210(data + 0x260, 0xA, f04, f4, 0x7F6F6FFF, 1, -n, D_L04_001A8F20, 0.0f, 0);
            func_L00_002E6EF8(func_L04_003E5318, arg0);
            if (*(s32 *)(data + 0x2E0) >= 0) {
                l = D_L04_001C7800 + (*(s32 *)(data + 0x2E0) << 5);
                qcopy(l + 0x10, data + 0x270);
                *(f32 *)(l + 0x1C) = 5.0f;
                *(f32 *)(l + 0) = 1.0f;
                *(f32 *)(l + 4) = 0.0f;
                *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                *(f32 *)(l + 8) = 0.0f;
                *(f32 *)(l + 0xC) = 0.0f;
            }
                }
            }
        }
        if (t >= 9.0f && t < 15.0f && arg0[0x42] == 0xA) {
                        
            if (func_00282E80(data + 0x260, data + 0x270) > 0.5f) {
                u8 req[0x30] __attribute__((aligned(16)));
                f32 v30[4] __attribute__((aligned(16)));
                f32 v40[4] __attribute__((aligned(16)));
                u8 *l;
                f32 f, f4;
                s32 n;

                *(f32 *)(data + 0x2C8) = *(f32 *)(data + 0x2C8) + 1.0f;
                func_00282F20(data + 0x270, data + 0x280, *(f32 *)(data + 0x2C8));
                func_002A8C00(req, arg0, 0x04000001, hp, data + 0x270);
                *(u16 *)(req + 0x1A) = *(u16 *)(arg0 + 0xAA);
                func_00282CC0(data + 0x270, data + 0x260, data + 0x270);
                if (func_002761F8(data + 0x260, data + 0x270, 0, arg0, req) != 0) {
                    *(TI128 *)(data + 0x270) = D_L04_001BFAE0;
                    if (func_002B38B8(arg0) == 0) {
                        func_L04_003E5830(&D_L04_001BFAE0, 0x1E);
                        func_L00_003294F0(arg0, 1);
                    }
                }
                func_00282F20(v30, data + 0x280, 1.6666667f);
                func_00282CC0(data + 0x260, data + 0x260, v30);
                f = func_002A7878(1.0f, 6.0f);
                n = func_002A7820(0x19, 0x23);
                if (n == 0)
                    n = n - 1;
                qcopy(v40, data + 0x270);
                v40[2] -= 0.1f;
                func_002C2210(v40, 0x19, f * 0.3f, f, 0xFF000080, 0, n, D_L04_001A8F20, 0.0f, 0);
                n = -n;
                f4 = f * 0.4f;
                func_002C2210(v40, 5, f * 0.04f, f4, 0x7F6F6FFF, 1, n, D_L04_001A8F20, 0.0f, 0);
                func_002C2210(v40, 0x14, f4, f * 0.2f, 0xFF4080FF, 1, n, D_L04_001A8F20, 0.0f, 0);
                func_L00_002E6EF8(func_L04_003E5318, arg0);
                if (*(s32 *)(data + 0x2E0) >= 0) {
                    l = D_L04_001C7800 + (*(s32 *)(data + 0x2E0) << 5);
                    qcopy(l + 0x10, data + 0x270);
                    *(f32 *)(l + 0x1C) = 5.0f;
                    *(f32 *)(l + 0) = 1.0f;
                    *(f32 *)(l + 4) = 0.0f;
                    *(f32 *)(l + 0x18) = *(f32 *)(l + 0x18) + 1.0f;
                    *(f32 *)(l + 8) = 0.0f;
                    *(f32 *)(l + 0xC) = 0.0f;
                }
            } else if (*(s32 *)(data + 0x2E0) >= 0) {
                func_00291450(*(s32 *)(data + 0x2E0));
                *(s32 *)(data + 0x2E0) = -1;
            }
        } else if (t > 15.0f && arg0[0x42] == 0xA) {
            if (*(s32 *)(data + 0x2E0) >= 0) {
                func_00291450(*(s32 *)(data + 0x2E0));
                *(s32 *)(data + 0x2E0) = -1;
            }
        }
        break;
    }
    case 19: {
        u8 *p = arg0 + 0x10;

        if (arg0[0x60] & 2) {
            if (func_00282E80(p, *(u8 **)(data + 0x240) + 0x10) < 25.0f && *(u8 **)(data + 0x2AC) != 0) {
                func_002A7750(arg0, 0x14, -1);
                func_L04_003E22B0(arg0, 5, 4, 0, 0xA);
            } else {
                func_002A7750(arg0, 0xB, -1);
                func_L04_003E22B0(arg0, 6, 5, 0, 0xA);
            }
        } else if (func_00282E80(p, *(u8 **)(data + 0x240) + 0x10) < 6.0f) {
            func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
            func_002A7750(arg0, 0xE, -1);
        }
        break;
    }
    case 20:
        if (func_00283C80(*(f32 *)(arg0 + 0xF8), func_00283248(*(f32 *)(data + 0x230) - *(f32 *)(arg0 + 0x10),
                                                             *(f32 *)(data + 0x234) - *(f32 *)(arg0 + 0x14))) <= 0.087266475f) {
            func_L04_003E22B0(arg0, 9, 6, 0, 0xA);
            func_002A7750(arg0, 0xE, -1);
        } else {
            func_002B50E0(arg0, arg0 + 0x10, func_00283248(*(f32 *)(*(u8 **)(data + 0x240) + 0x10) - *(f32 *)(arg0 + 0x10),
                                                           *(f32 *)(*(u8 **)(data + 0x240) + 0x14) - *(f32 *)(arg0 + 0x14)));
        }
        break;
    case 21:
        if (arg0[0x60] & 2) {
            if (*(s32 *)(data + 0x308) == 0) {
                func_L04_003E22B0(arg0, 5, 4, 0, 0);
                func_002A7750(arg0, 2, -1);
            } else {
                func_L04_003E22B0(arg0, 5, 4, 0, 0);
                func_002A7750(arg0, 3, -1);
            }
        } else if (arg0[0x43] == 0xF) {
            func_002B60B0(arg0, 0.13333334f, 0.06666667f, 0.009696275f, 0.6981318f);
            func_002B6120(arg0, D_L04_001FE340[*(s32 *)(data + 0x2CC)]);
        }
        break;
    }
    func_L04_003E51F0(arg0);
    if (*(f32 *)(arg0 + 0x18) < 40.0f) {
        func_US2_002A7AA8(arg0, 0, 3);
        func_0029F338(arg0);
    }
}
