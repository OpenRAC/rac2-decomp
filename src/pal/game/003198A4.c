#include "include_asm.h"

#include "common.h"

extern int D_001B2758 MACRO_ADDR;
extern int func_00283CF0(float), func_002A7820(int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A7750(void *, int, int), func_PAL_002A7E68(void *, int, int, int);
extern float D_001BAFA8;
extern u8 D_00189E20[];
extern u8 D_00188660[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
extern u8 D_00189E20[];
extern u8 *D_001B1B5C MACRO_ADDR;

typedef int TI128_00318340 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_00318340 q[0x260]; } Hero_00318340;
extern char D_00189EA0[];
extern char D_001AFA80[];
extern void func_0026FEB8(const char *, ...);
extern void func_0027CFD0(void (*)(char *), char *);
extern int func_00282948(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_PAL_002A7650(void *, int, int);
extern int func_002A77E0(int);
extern void func_002A7E08(void *, void *, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern int func_002ACBC8(void *, int);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_PAL_002AF6C0(void *, float);
extern int func_002B3868(void *);
extern int func_002B38B8(void *);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_0031AD58(char *);
extern void func_00319FB8(char *);
extern void func_00319EC0(char *);
extern int func_0031A580(char *);
extern int func_0031A628(char *);
extern int func_0031A708(unsigned char *);
extern int func_0031A848(char *, float);
extern void func_0031AAB0(char *);
extern void *func_PAL_00329890(char *, void *, void *, int, int, float);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AEF28(float, float, char *, char *, float, char *);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern char *D_001F1700[];
extern int func_002B3890(char *);
extern int func_PAL_002B27B8(char *, char *);

/* func_PAL_003198A4, the PAL copy of func_00318340: the same C, with the 50 Hz values and scales. */
void func_PAL_003198A4(char *obj)
{
    f32 v0[4] __attribute__((aligned(16)));
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    char *pv = *(char **)(obj + 0x68);
    char *tgt13, *tgt10, *tgt16;
    f32 *pos;
    s32 *path;
    int id;
    int m0, m2, flags, st;
    float h13, h12, floor12, y12, diff12, h5, diff5, dist10, dot, dist11, dist16, sx, sy, sz;

    if (((Hero_00318340 *)D_00189E20)->b[0x22B4] == 1)
        return;
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        if (*(s32 *)(pv + 0x2E0) != 0 && func_002B38B8(obj) == 0)
            break;
        if (func_002B3890(obj) != 0)
            func_002B60B0(obj, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        m0 = *(s32 *)(pv + 0x34);
        if (m0 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (func_00282948(pv + 0x2D0) != 0) {
                func_002A7750(obj, 9, 3);
                if (*(u8 *)(obj + 0x43) != m0)
                    func_PAL_002A7E68(obj, 1, 0, 3);
            }
        } else if (*(s16 *)(pv + 0x286) != 0) {
            func_002A7750(obj, 8, 2);
            *(s16 *)(pv + 0x286) = 0;
            if (*(s16 *)(pv + 0x280) < 250)
                *(s16 *)(pv + 0x280) = ((s32)(func_002A7820(0x1E0, 0x258)) * 5 + 2) / 6;
        }
        break;
    case 2:
        if (func_002B3890(obj) != 0) {
            func_002B60B0(obj, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        m2 = *(s32 *)(pv + 0x34);
        if (m2 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            func_002A7750(obj, 9, 3);
            if (*(u8 *)(obj + 0x43) != m2)
                func_PAL_002A7E68(obj, 1, 0, 3);
        } else if (*(s16 *)(pv + 0x280) == 0) {
            func_002A7750(obj, 2, 0);
            if (*(u8 *)(obj + 0x43) != 2)
                func_PAL_002A7E68(obj, 2, 0, 8);
        }
        break;
    case 1:
        if (func_002B3890(obj) != 0)
            func_002B60B0(obj, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
        if (*(s32 *)(pv + 0x34) == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (func_00282948(pv + 0x2D0) == 0)
                break;
        } else {
            if (*(s16 *)(pv + 0x286) == 0 || *(s32 *)(pv + 0x2A4) == 0)
                break;
            *(s16 *)(pv + 0x286) = 0;
        }
        func_002A7750(obj, 0xD, 3);
        if (*(u8 *)(obj + 0x43) != 0x19)
            func_PAL_002A7E68(obj, 0x19, 0, 3);
        break;
    case 3:
        if (func_002B3890(obj) != 0) {
            func_002B60B0(obj, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        if (*(s32 *)(pv + 0x34) != 1 && *(u8 *)(obj + 0x20) != 0xD && *(u8 *)(obj + 0x20) != 0xC && *(u8 *)(obj + 0x20) != 0xF) {
            func_002A7750(obj, 8, 2);
            if (*(u8 *)(obj + 0x43) != 6)
                func_PAL_002A7E68(obj, 6, 0, 8);
            *(s16 *)(pv + 0x280) = ((s32)(func_002A7820(0x244, 0x258)) * 5 + 2) / 6;
            if (*(s32 *)(pv + 0x28C) != 0) {
                func_002A7750(obj, 3, 1);
                if (*(u8 *)(obj + 0x43) != 0xB)
                    func_PAL_002A7E68(obj, 0xB, 0, 0x11);
            }
        }
        break;
    case 4:
        if (func_002B3868(obj) != 0)
            *(s16 *)(pv + 0x46) = 0x32;
        flags = func_PAL_002B27B8(obj, pv + 0x80);
        if ((flags & 1) || *(f32 *)(pv + 0x40) <= 0.0f) {
            func_PAL_002AD288(obj, obj + 0x10, -1, 1.0f, 13.0f);
            func_PAL_002A7650(obj, 0, 3);
            func_0029F338(obj);
            return;
        }
        if (flags & 2) {
            if (*(s32 *)(pv + 0x34) == 1) {
                func_002A7750(obj, 7, 3);
                if (*(u8 *)(obj + 0x43) != 7)
                    func_PAL_002A7E68(obj, 7, 0, 5);
            } else {
                func_002A7750(obj, 8, 2);
                if (*(u8 *)(obj + 0x43) != 6)
                    func_PAL_002A7E68(obj, 6, 0, 8);
                *(s16 *)(pv + 0x280) = ((s32)(func_002A7820(0x244, 0x258)) * 5 + 2) / 6;
            }
            if (*(s32 *)(pv + 0x2A4) != 1)
                *(s32 *)(pv + 0x2A4) = 1;
        }
        break;
    }

    switch (*(u8 *)(obj + 0x20)) {
    case 2:
        break;
    case 7:
        if (func_0031A848(obj, 10.0f) != 0) {
            func_0031AAB0(obj);
        } else {
            func_002A7750(obj, 0xA, -1);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                func_PAL_002A7E68(obj, 0x1E, 0, 5);
        }
        break;
    case 3:
        func_002AEF28(0.06981318f, 0.062831864f, obj, pv + 0x2A8, 0.015707966f, pv + 0x2AC);
        break;
    case 13:
        tgt13 = *(char **)(pv + 0x30);
        *(s32 *)(pv + 0x2C0) += 1;
        if (tgt13 != 0) {
            func_002A7E08(obj, tgt13, pv + 0x29C, 0.001f, 0.01f, 0.1f);
            func_002AA3A8(obj + 0xF4, 0.0f, pv + 0x2A0, 0.020000001f, 0.0f, 0.080000006f);
            func_002AA3A8(obj + 0xF0, 0.0f, pv + 0x2A0, 0.020000001f, 0.0f, 0.080000006f);
            h13 = func_002A89A8(obj + 0x10, 0, 0.5f);
            if (*(f32 *)(obj + 0x18) - h13 > 0.05f) {
                *(f32 *)(obj + 0x18) -= h13 * 0.00025f;
            } else {
                func_002A7750(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    func_PAL_002A7E68(obj, 0xE, 0, 2);
            }
            if (*(u8 *)(obj + 0x60) & 2) {
                func_002A7750(obj, 0xC, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    func_PAL_002A7E68(obj, 0x1A, 0, 0xC);
            }
        }
        break;
    case 12:
        *(s32 *)(pv + 0x2C0) += 1;
        func_0031AAB0(obj);
        h12 = func_002A89A8(obj + 0x10, 0, 0.5f);
        y12 = *(f32 *)(obj + 0x18);
        floor12 = *(f32 *)(pv + 0x2DC);
        diff12 = y12 - h12;
        h12 -= 3.0f;
        if (floor12 != -1.0f && y12 <= floor12) {
            if (func_0031A708(obj) == 0) {
                func_002A7750(obj, 0x10, -1);
                if (*(u8 *)(obj + 0x43) != 0x1D)
                    func_PAL_002A7E68(obj, 0x1D, 0, 2);
            } else {
                *(s32 *)(pv + 0x354) = 0;
                func_0031A580(obj);
                func_002A7750(obj, 0xE, -1);
            }
        } else if (diff12 > 0.05f) {
            func_002AA548(obj + 0x18, pv + 0x290, h12, 0.020000001f, 0.19600002f, 0.20000002f);
        } else {
            func_0026FEB8(D_001AFA80, *(s32 *)(pv + 0x2C0));
            func_002A7750(obj, 6, -1);
            if (*(u8 *)(obj + 0x43) != 0xE)
                func_PAL_002A7E68(obj, 0xE, 0, 2);
        }
        break;
    case 14:
        if (func_002B3868(obj) != 0) {
            *(TI128_00318340 *)(pv + 0x360) = *(TI128_00318340 *)(obj + 0x10);
            if (*(s32 *)(pv + 0x350) != 0)
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + func_002A7878(4.0f, 7.0f);
            else
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + func_002A7878(-3.0f, 3.0f);
        }
        if (func_00282E48(obj + 0x10, pv + 0x360) < 0.05f) {
            *(s32 *)(pv + 0x354) = 0;
            func_002A7750(obj, 0x10, -1);
        }
        *(s32 *)(pv + 0x2C0) += 1;
        func_0031AAB0(obj);
        func_002AA548(obj + 0x18, pv + 0x290, *(f32 *)(pv + 0x368), 0.0050000004f, 0.0050000004f, 0.20000002f);
        break;
    case 4:
        if (*(u8 *)(obj + 0x60) & 2) {
            func_002A7750(obj, 5, -1);
            if (*(u8 *)(obj + 0x43) != 0xD)
                func_PAL_002A7E68(obj, 0xD, 0, 0xC);
        }
        break;
    case 5:
        if (*(char **)(pv + 0x30) != 0) {
            func_002AA3A8(obj + 0xF4, 0.0f, pv + 0x2A0, 0.020000001f, 0.0f, 0.080000006f);
            func_002833F0(obj + 0xC0, obj + 0xF0);
            func_002A7E08(obj, *(char **)(pv + 0x30), pv + 0x29C, 0.001f, 0.01f, 0.1f);
            h5 = func_002A89A8(obj + 0x10, 0, 0.5f);
            diff5 = *(f32 *)(obj + 0x18) - h5;
            h5 -= 3.0f;
            if (diff5 > 0.05f) {
                func_002AA548(obj + 0x18, pv + 0x290, h5, 0.030000001f, 0.19600002f, 0.3f);
            } else {
                func_002A7750(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    func_PAL_002A7E68(obj, 0xE, 0, 2);
            }
        }
        break;
    case 6:
        if (*(u8 *)(obj + 0x60) & 2) {
            func_002A7750(obj, 0xA, 3);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                func_PAL_002A7E68(obj, 0x1E, 0, 5);
            *(f32 *)(obj + 0x18) = func_002A89A8(obj + 0x10, 0, 0.5f);
        }
        break;
    case 9:
        if (*(u8 *)(obj + 0x60) & 2) {
            func_002B60B0(obj, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
            func_002A7750(obj, 7, -1);
            if (*(u8 *)(obj + 0x43) != 7)
                func_PAL_002A7E68(obj, 7, 0, 5);
        }
        break;
    case 10:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (func_0031A848(obj, 10.0f) != 0) {
                func_002A7750(obj, 7, -1);
                if (*(u8 *)(obj + 0x43) != 7)
                    func_PAL_002A7E68(obj, 7, 0, 5);
            } else if (((Hero_00318340 *)D_00189E20)->ptr[0x249C / 4] == (u8 *)obj || func_002A77E0(6) == 1) {
                func_002A7750(obj, 0xB, -1);
                if (*(u8 *)(obj + 0x43) != 0x10)
                    func_PAL_002A7E68(obj, 0x10, 0, 6);
            }
        }
        dist10 = func_0029F530(obj);
        if (func_PAL_002AF6C0(obj, 17.0f) != 0) {
            func_0029FCC0(obj, 4, v0);
            tgt10 = *(char **)(pv + 0x30);
            if (tgt10 == (char *)((Hero_00318340 *)D_00189E20)->ptr[0x2290 / 4]) {
                qcopy(v10, &((Hero_00318340 *)D_00189E20)->q[0xD0 / 16]);
                pos = v10;
            } else {
                if (tgt10 == 0)
                    break;
                qcopy(v10, tgt10 + 0x10);
                pos = v10;
                v10[2] += *(f32 *)(tgt10 + 0xC) * 0.0009765625f;
            }
            if (func_0031A848(obj, 10.0f) != 0) {
                func_00282CF0(v40, pos, v0);
                qcopy(v20, D_001A8BD0);
                v20[0] = 1.0f;
                func_00283098(v20, v20, obj + 0xC0);
                func_00282DD8(v30, v20, v40);
                dot = func_00282DB0(v20, v40);
                if (dot > 0.0f)
                    func_002ACEC0(v20, v20, v30, -0.17453294f);
                else
                    func_002ACEC0(v20, v20, v30, 0.17453294f);
            } else {
                func_00282CF0(v20, pos, v0);
            }
            func_00282F20(v20, v20, 0.40000004f);
            func_PAL_00329890(obj, v20, v0, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist10 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            func_0029FCC0(obj, 4, v0);
        }
        break;
    case 11:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (func_00282E80(obj + 0x10, D_00189EA0) > 4.0f) {
                func_002B60B0(obj, 0.0048f, 0.120000005f, 0.0016755164f, 0.12566373f);
                func_002A7750(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    func_PAL_002A7E68(obj, 0x1E, 0, 5);
            } else {
                func_002B60B0(obj, 0.0032000002f, 0.080000006f, 0.0016755164f, 0.12566373f);
                func_002A7750(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    func_PAL_002A7E68(obj, 0x1E, 0, 5);
            }
        }
        dist11 = func_0029F530(obj);
        if (*(u8 *)(obj + 0x42) == 0x10 && (dist11 <= 5.0f || (dist11 >= 12.0f && dist11 <= 15.0f)))
            *(s32 *)(pv + 0x2C8) = 1;
        else
            *(s32 *)(pv + 0x2C8) = 0;
        break;
    case 15:
        if (func_002B3868(obj) != 0) {
            *(f32 *)(pv + 0x374) = 0.0f;
            *(f32 *)(pv + 0x378) = 0.0f;
        }
        if (*(s32 *)(pv + 0x37C) == 0) {
            if (func_002ACBC8(D_00189EA0, *(s32 *)(pv + 0x35C)) != 0)
                *(s32 *)(pv + 0x37C) = 1;
        } else {
            path = (s32 *)D_001F1700[*(s32 *)(pv + 0x370)];
            func_002AA548(pv + 0x374, pv + 0x378, (f32)(*path - 1), 0.020000001f, 0.002f, 0.40000004f);
            func_002C9828(path, 0, obj + 0x10, obj + 0xF0, 0, *(f32 *)(pv + 0x374));
            func_002833F0(obj + 0xC0, obj + 0xF0);
            if ((f32)(*path - 1) <= *(f32 *)(pv + 0x374))
                func_002A7750(obj, 0xA, 3);
        }
        break;
    case 16:
        if ((*(u8 *)(obj + 0x60) & 2) && func_0031A708(obj) != 0) {
            *(s32 *)(pv + 0x354) += 1;
            if (*(s32 *)(pv + 0x350) != 0) {
                if (*(s32 *)(pv + 0x354) >= 3 && func_0031A628(obj) != 0) {
                    func_002A7750(obj, 0xE, -1);
                    if (*(u8 *)(obj + 0x43) != 0x1A)
                        func_PAL_002A7E68(obj, 0x1A, 0, 0xC);
                }
            } else {
                func_002A7750(obj, 0xE, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    func_PAL_002A7E68(obj, 0x1A, 0, 0xC);
            }
        }
        dist16 = func_0029F530(obj);
        if (func_PAL_002AF6C0(obj, 16.0f) != 0) {
            func_0029FCC0(obj, 4, v0);
            tgt16 = *(char **)(pv + 0x30);
            if (tgt16 == (char *)((Hero_00318340 *)D_00189E20)->ptr[0x2290 / 4]) {
                qcopy(v10, &((Hero_00318340 *)D_00189E20)->q[0xD0 / 16]);
                pos = v10;
            } else {
                if (tgt16 == 0)
                    break;
                qcopy(v10, tgt16 + 0x10);
                pos = v10;
                v10[2] += *(f32 *)(tgt16 + 0xC) * 0.0009765625f;
            }
            func_00282CF0(v20, pos, v0);
            func_00282F20(v20, v20, 0.40000004f);
            func_002E5CF8(0xB, 0, obj);
            func_PAL_00329890(obj, v20, v0, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist16 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            func_0029FCC0(obj, 4, v0);
            sx = func_002A7878(1.0f, 1.5f) * 210000.0f;
            sy = func_002A7878(0.2f, 0.4f) * 210000.0f;
            sz = func_002A78D8(0.0f, 0.1f);
            func_002C65A0(v0, D_001A8BD0, 3, 0x808080, 9, 0x4F, 0, 0, sx, sy, sz);
        }
        break;
    }

    st = *(u8 *)(obj + 0x20);
    if (st == 12 || st == 13 || st == 14 || st == 16) {
        u8 *recA;
        recA = *(s32 *)(pv + 0x2C4) * 0x70 + D_00188660;
        if (*(char **)(recA + 0x88) != obj || recA[0x74] == 0)
            *(s32 *)(pv + 0x2C4) = func_002E5CF8(10, 4, obj);
    } else {
        u8 *recB;
        id = *(s32 *)(pv + 0x2C4);
        if (id != -1) {
            recB = id * 0x70 + D_00188660;
            if (*(char **)(recB + 0x88) == obj && recB[0x74] != 0)
                func_002E59F8(id);
        }
        *(s32 *)(pv + 0x2C4) = -1;
    }
    func_PAL_0031AD58(obj);
    func_00319EC0(obj);
    func_0027CFD0(func_00319FB8, obj);
}

/* func_00318340 is in 00318340.c. */
/* func_00319780 is in 00319780-g8.c. */

void func_PAL_0031B110(char *self)
{
    char *d = *(char **)(self + 0x68);
    *(u8 *)(d+0x68) = func_00283CF0(15.0f);
    *(u8 *)(d+0x6A) = func_00283CF0(12.0f);
    *(float *)(self+0x2C) *= 1.1f;
    *(u16 *)(self+0x34) |= 0x8100;
    *(char **)(d+0x18) = d+0x130;
    *(u8 *)(d+0x48)=3;
    *(u8 *)(d+0x90)=17;
    *(int *)(d+0xC8)=4;
    *(int *)(d+0xFC)=*(int *)(d+0x270);
    *(u8 *)(d+0x95)=13;
    *(float *)(d+220)=0.30000001192092896f;
    *(float *)(d+216)=0.05000000074505806f;
    *(float *)(d+160)=0.080000006f;
    *(float *)(d+164)=0.006f;
    *(float *)(d+168)=0.012f;
    *(float *)(d+176)=0.5f;
    *(float *)(d+180)=0.5f;
    *(float *)(d+188)=0.4000000059604645f;
    *(float *)(d+156)=0.120000005f;
    if ((float)*(int *)(d+0x2E8)>0.0f) *(float *)(d+0xC0)=(float)*(int *)(d+0x2E8);
    *(float *)(d+0x15C)=0.0f;
    *(float *)(d+320)=12.56637191772461f;
    *(float *)(d+304)=0.800000011920929f;
    *(float *)(d+308)=0.5f;
    *(float *)(d+0x138)=0.4f;
    *(float *)(d+316)=0.4000000059604645f;
    *(float *)(d+352)=0.523598849773407f;
    *(int *)(d+0x168)|=5;
    func_002B60B0(self,0.0048f,0.120000005f,0.0016755164f,0.12566373f);
    qcopy(d+0x220,self+0x10);
    *(float *)(d+0x230)=1.0f;
    *(float *)(d+0x23C)=3.0f;
    *(float *)(d+0x240)=10.0f;
    *(int *)(d+0x2D8)=func_002A7820(100,583);
    *(float *)(d+0x294)*=0.01745329424738884f;
    *(u8 *)(d+0x250)=176;
    *(u8 *)(d+0x251)=128;
    *(u8 *)(d+0x252)=64;
    *(int *)(d+0x2C4)=1;
    *(float *)(d+0x2BC)=0.0f;
    *(int *)(d+0x2C0)=0;
    qcopy(d+0x340,self+0x10);
    *(float *)(d+0x290)=0.0f;
    *(int *)(d+0x2C8)=0;
    *(int *)(d+0x2CC)=0;
    *(int *)(d+0x37C)=0;
    func_0029FCC0(self,0,d+0x2F0);
    qcopy(d+0x300,d+0x2F0);
    *(float *)(d+0x2F8)+=20.0f;
    if (func_002761F8(d+0x300,d+0x2F0,0,self,0))
        *(float *)(d+0x2F8)=D_001BAFA8;
    *(int *)(d+0x168)|=4;
    *(u16 *)(self+0x34)|=0x100;
    *(float *)(d+0x140)=12.56637191772461f;
    *(int *)(d+0x168)|=1;
    if (*(int *)(d+0x28C)==0) {
        if (*(int *)(d+0x370)!=-1) {
            func_002A7750(self,15,3);
            if (*(u8 *)(self+0x43)!=7) func_PAL_002A7E68(self,7,0,0);
        } else {
            func_002A7750(self,1,0);
            if (*(u8 *)(self+0x43)!=0) func_PAL_002A7E68(self,0,0,0);
        }
    } else {
        func_002A7750(self,3,1);
        if (*(u8 *)(self+0x43)!=11) func_PAL_002A7E68(self,11,0,0);
    }
}

