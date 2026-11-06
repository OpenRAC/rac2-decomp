/* func_PAL_L18_0042DC68, the PAL copy of func_L18_00428F08: the same C, with frame counts scaled to
 * 50 Hz, per-frame float rates multiplied by 6/5 or 36/25, and D_L18_001B1260 read as a word.  The
 * callback passed to func_PAL_0029C0F0 is a different function in level 20, hence its ref_ name. */
/* EE argument banks are independent; the interleaved call declaration agrees
 * with the matched motion callers and preserves each bank's argument order. */
#include "common.h"

typedef struct { int q __attribute__((mode(TI))); } Vec4;

extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0013965E[];
extern u8 D_00188660[];
typedef union { u8 b[0x1000]; s16 h[0x800]; u16 uh[0x800]; s32 i[0x400]; u32 ui[0x400]; f32 f[0x400]; u8 *p[0x400]; } View;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *p[0x980]; } Hero;
extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_0018C958[];
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern float D_L18_001B1230 __attribute__((sda));
extern float D_L18_001B1238 __attribute__((sda));
extern s32 D_L18_001B1258 __attribute__((sda));
extern s32 D_L18_001B125C __attribute__((sda));
extern s32 D_L18_001B1260 __attribute__((sda));
extern s32 D_L18_001B1274 __attribute__((sda));
extern s32 D_L18_001B1278 __attribute__((sda));
extern s32 D_L18_001B127C __attribute__((sda));
extern s32 D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B1298 __attribute__((sda));
extern float D_L18_001B129C __attribute__((sda));
extern s32 D_L18_001B2564[] __attribute__((sda));
extern u8 D_L18_001B2660[] MACRO_ADDR;
extern s32 D_L18_001B281C MACRO_ADDR;
extern Vec4 D_L18_001B97C0[];
extern u8 D_L18_0021DB40[][0x464];
extern u8 D_L18_0021E7B0[][0x464];
extern u8 D_L18_002571A0[];

extern s32 func_00282978(void *);
extern void func_00282A60(void *, u32, s32);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283CE0(s32);
extern s32 func_PAL_00289730(s32, s32);
extern void func_PAL_0029C0F0(s32, void *);
extern void func_0029F338(void *);
extern void func_PAL_002A7650(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern float func_002AAA00(void *out, float, void *in, s32, float, float, float);
extern void func_PAL_002AC3C0(void *, void *);
extern float func_002ABB18(float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, s32, s32, s32, float, float,
                          float, float, s32, float, s32, s32, s32, s32, s32);
extern s32 func_002ACD38(void *);
extern void func_002B0C28(s32, s32, s32);
extern s32 func_002B1C20(void *, void *);
extern s32 func_002B3890(void *);
extern s32 func_PAL_002B5E10(void *);
extern void func_PAL_002B5E30(void *, float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002E59F8(s32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_003355A8(s32);
extern s32 func_001163B0(void);
extern s32 func_L00_00329520(void *, s32);
extern s32 func_L02_002EF388(void *, void *, void *, void *, s32);
extern void func_L02_003329C8(void *, void *, float, float);
extern s32 func_PAL_L07_00324F58(void *, float, float, float);
extern void func_PAL_L18_002CFC50(s32, s32, void *);
extern void func_PAL_L18_002CFE30(s32);
extern s32 func_L18_0033B628(void *, s32, s32);
extern float func_L18_0035D5A8(void *, void *, void *, s32, float);
extern void ref_PAL_L18_0042DC68_00(void);
extern void func_L18_00426D98(void *);
extern s32 func_L18_00426E00(void *);
extern s32 func_L18_00426E48(void *, void *);
extern void func_PAL_L18_0042BA90(void *, s32, s32, float);
extern void func_L18_00427010(void *);
extern void func_L18_00427058(void *);
extern s32 func_L18_00427130(void *, s32, s32);
extern void func_PAL_L18_0042BD70(void *);
extern void func_L18_00427B48(void *, s32);
extern void func_PAL_L18_0042C768(void *);
extern void func_PAL_L18_0042CC40(void *);
extern s32 func_L18_004283F0(void *);
extern void func_PAL_L18_0042D3B8(void *);
extern void func_PAL_L18_0042D7E0(void *);

void func_PAL_L18_0042DC68(u8 *a0) {
    float ref[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float ang[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    u8 *v;
    s32 sel;

    if (func_002ACD38(a0 + 0x10) == 0)
        return;
    v = ((View *)a0)->p[0x68 / 4];
    func_PAL_L18_0042C768(a0);
    switch (((View *)a0)->b[0x95]) {
    case 1:
        if (((View *)a0)->b[0x42] == 0xD)
            ((View *)a0)->i[0x48 / 4] = 0;
        break;
    case 2:
        if (!(((View *)v)->b[0x399] & 1) && (((View *)v)->i[0x234 / 4] == 1 || ((View *)v)->h[0x390 / 2] != 0)
            && (func_L18_00426E00(*(void **)(v + 0x230)) == 0
                || func_L18_00426E48(a0, *(void **)(v + 0x230)) != 0)) {
            func_L18_00427B48(a0, ((View *)a0)->b[0x21]);
            ((View *)v)->i[0x37C / 4] = ((View *)v)->i[0x364 / 4];
            ((View *)v)->i[0x13C / 4] = ((View *)v)->i[0x384 / 4];
            ((View *)v)->h[0x392 / 2] = ((View *)v)->b[0x398];
            if (((View *)v)->i[0x368 / 4] != -1
                && (((View *)v)->i[0x3A4 / 4] == -1 || func_L00_00329520(v + 0x220, ((View *)v)->i[0x3A4 / 4]) == 0)) {
                if (**(s32 **)(v + 0x3A8) == 0 && **(s32 **)(v + 0x3AC) < D_L18_001B127C) {
                    **(s32 **)(v + 0x3A8) = ((s32)func_002A7820(D_L18_001B1274, D_L18_001B1278) * 5 + 2) / 6;
                    func_L18_00427058(a0);
                    func_002A7750(a0, 1, 4);
                }
            } else {
                func_L18_00427130(a0, ((View *)v)->i[0x370 / 4], -1);
                func_002A7750(a0, 1, 3);
            }
        }
        break;
    case 3:
        if (((View *)v)->h[0x392 / 2] == 0) {
            func_PAL_L18_0042BA90(a0, 3, 0, 5.0f);
            if (((View *)v)->i[0x370 / 4] != -1) {
                func_002A7750(a0, 3, 5);
            } else {
                func_L18_00427130(a0, ((View *)v)->i[0x374 / 4], -1);
                ((View *)v)->h[0x390 / 2] = ((s32)func_002A7820(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
                func_002A7750(a0, 3, 6);
            }
        }
        break;
    case 4:
        if (((View *)v)->h[0x392 / 2] == 0) {
            ((View *)a0)->b[0x31] = 1;
            ((View *)a0)->uh[0x34 / 2] &= ~1;
            func_L18_0035D5A8(ref, a0 + 0x10, D_00189EA0, ((View *)v)->i[0x368 / 4], 0.0f);
            func_PAL_L18_0042BA90(a0, 6, 0, 5.0f);
            func_L02_003329C8(a0, ref, D_L18_001B1238 * 0.020000001f, D_L18_001B1230 * 0.00040000002f);
            func_002A7750(a0, 5, 10);
        }
        break;
    case 5:
        if (((View *)v)->i[0x234 / 4] == 1 && ((View *)v)->h[0x390 / 2] == 0)
            ((View *)v)->h[0x390 / 2] = ((s32)func_002A7820(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
        break;
    case 6:
        if ((((View *)v)->i[0x234 / 4] != 1 && ((View *)v)->h[0x390 / 2] == 0)
            || (((View *)v)->b[0x3B2] != 0 && ((View *)v)->b[0x3B3] == 0)
            || (((View *)v)->b[0x3B3] != 0 && (((View *)v)->p[0x230 / 4])[0xBC] == 0)) {
            ((View *)v)->h[0x390 / 2] = 0;
            func_PAL_L18_0042BA90(a0, (func_001163B0() & 1) | 4, 0, 10.0f);
            func_002A7750(a0, 2, 2);
        } else if (((View *)v)->b[0x3B0] == 0 && ((View *)v)->i[0x368 / 4] != -1 && ((View *)v)->i[0x3A4 / 4] != -1
                   && func_L00_00329520(v + 0x220, ((View *)v)->i[0x3A4 / 4]) == 0
                   && **(s32 **)(v + 0x3A8) == 0 && **(s32 **)(v + 0x3AC) < D_L18_001B127C) {
            **(s32 **)(v + 0x3A8) = ((s32)func_002A7820(D_L18_001B1274, D_L18_001B1278) * 5 + 2) / 6;
            func_L18_00427058(a0);
            func_002A7750(a0, 0, 4);
        }
        break;
    case 9: {
        s32 r = func_002B1C20(a0, v + 0x50);

        if (r & 1) {
            func_PAL_002A7650(a0, 0, 3);
            func_002A7750(a0, 12, -1);
        } else if (r & 2) {
            ((View *)v)->h[0x390 / 2] = ((s32)func_002A7820(D_L18_001B1258, D_L18_001B125C) * 5 + 2) / 6;
            func_L18_00427B48(a0, ((View *)a0)->b[0x21]);
            if (((View *)a0)->b[0xBC] == 1) {
                func_PAL_L18_0042BA90(a0, 13, 0, 10.0f);
                func_002A7750(a0, 7, 8);
            } else {
                func_PAL_L18_0042BA90(a0, (func_001163B0() & 1) | 4, 0, 10.0f);
                func_002A7750(a0, 4, 6);
            }
        }
        break;
    }
    case 11: {
        s32 idx;
        u8 *m;

        ((View *)v)->f[0x100 / 4] = 0.699999988f;
        idx = ((View *)v)->i[0x3B4 / 4];
        if (idx != -1 && (m = (u8 *)((idx << 8) + D_L18_001B281C), *(s16 *)(m + 0xAA) == 0x114D)
            && m[0x20] != 0xFE && m[0x20] != 0xFD) {
            if (m[0xBC] == 0) {
                ((View *)a0)->b[0x23] = 0x80;
                ((View *)a0)->f[0x2C / 4] = *(float *)(((View *)a0)->p[0x24 / 4] + 0x24);
                ((View *)a0)->b[0x31] = 1;
                ((View *)a0)->uh[0x34 / 2] &= ~1;
                func_002A7750(a0, 0, 12);
            }
        } else {
            ((View *)a0)->b[0x31] = 1;
            ((View *)a0)->uh[0x34 / 2] &= ~1;
            func_L02_002EF388(a0, a0 + 0x10, a0 + 0xF0, 0, 0);
            func_002A7750(a0, 0, 14);
        }
        break;
    }
    case 12: {
        u8 *m;

        *(Vec4 *)(a0 + 0x10) = *(Vec4 *)((u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + D_L18_001B281C) + 0x10);
        m = (u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + D_L18_001B281C);
        if (m[0xBC] == 2) {
            if (((View *)a0)->b[0x43] != 2)
                func_PAL_002A7E68(a0, 2, 0, 10);
            func_002A7750(a0, 4, 13);
        }
        break;
    }
    case 13:
        if (((u8 *)((((View *)v)->i[0x3B4 / 4] << 8) + D_L18_001B281C))[0xBC] == 3) {
            u8 *t = ((View *)a0)->p[0x24 / 4];

            ((View *)a0)->b[0x30] = ((View *)v)->b[0x3E0];
            ((View *)a0)->i[0x98 / 4] = *(s32 *)(t + 0x10);
            ((View *)a0)->uh[0x34 / 2] |= 0x1000;
            ((View *)a0)->f[0x2C / 4] = *(float *)(t + 0x24);
            ((View *)v)->h[0x392 / 2] = 0;
            if (((View *)a0)->h[0xAA / 2] == 0xED4)
                ((View *)v)->f[0x100 / 4] = 1.0f;
            if (((View *)a0)->h[0xAA / 2] == 0xEE1)
                ((View *)v)->f[0x100 / 4] = 1.10000002f;
            func_002A7750(a0, 2, 2);
        }
        break;
    case 14: {
        u8 *t = ((View *)a0)->p[0x24 / 4];

        ((View *)a0)->b[0x23] = 0x80;
        if (*(float *)(t + 0x24) <= ((View *)a0)->f[0x2C / 4]) {
            ((View *)a0)->b[0x30] = ((View *)v)->b[0x3E0];
            ((View *)a0)->i[0x98 / 4] = *(s32 *)(t + 0x10);
            ((View *)a0)->uh[0x34 / 2] |= 0x1000;
            ((View *)a0)->f[0x2C / 4] = *(float *)(t + 0x24);
            if (((View *)a0)->h[0xAA / 2] == 0xED4)
                ((View *)v)->f[0x100 / 4] = 1.0f;
            if (((View *)a0)->h[0xAA / 2] == 0xEE1)
                ((View *)v)->f[0x100 / 4] = 1.10000002f;
            if (((View *)v)->b[0x3E8] != 0) {
                if (((View *)a0)->b[0x43] != 13)
                    func_PAL_002A7E68(a0, 13, 0, 10);
                func_002A7750(a0, 0, 1);
            } else {
                ((View *)v)->h[0x392 / 2] = 0;
                func_002A7750(a0, 2, 2);
            }
        }
        break;
    }
    case 7: {
        s32 h;
        float f;
        float t;

        func_002B0C28(6, 0, 20);
        if (func_002B3890(a0) != 0)
            func_002E5DA0(6, 0, a0, 0xEE1);
        if (((View *)v)->i[0x3F0 / 4] != -1) {
            u8 *e = D_00188660 + ((View *)v)->i[0x3F0 / 4] * 0x70;
            if (*(u8 **)(e + 0x88) == a0 && e[0x74] != 0)
                goto have;
        }
        ((View *)v)->i[0x3F0 / 4] = func_002E5DA0(9, 4, a0, 0xEE1);
    have:
        func_PAL_002AC3C0(a0, v + 0x50);
        func_002AAA00(a0 + 0xF8,
                      func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - ((View *)a0)->f[0x10 / 4],
                                    ((Hero *)D_00189E20)->f[0x84 / 4] - ((View *)a0)->f[0x14 / 4]),
                      v + 0x1B4, 0, ((View *)v)->f[0x114 / 4], ((View *)v)->f[0x118 / 4], ((View *)v)->f[0x11C / 4]);
        D_L18_001B2564[1] = 1;
        qcopy(ref, D_L18_001B97C0);
        ((Hero *)D_00189E20)->h[0x1DC / 2] = 5;
        ((Hero *)D_00189E20)->h[0x1E0 / 2] = 8;
        if (func_00282978(v + 0x396) != 0) {
            func_PAL_0029C0F0(0, ref_PAL_L18_0042DC68_00);
            ((View *)v)->uh[0x3BC / 2] = ((s32)((View *)v)->h[0x3BE / 2] * 5 + 2) / 6;
            f = ((View *)a0)->f[0xF8 / 4];
            if (((Hero *)D_00189E20)->b[0x22B4] == 4) {
                if (D_001A79F0 == 0x14)
                    D_0013965E[0] = 1;
                func_PAL_L18_002CFE30(1);
            }
            func_L18_00426D98(a0);
            ((View *)a0)->b[0xBC] = 1;
            ((View *)v)->i[0x13C / 4] = -1;
            ((View *)v)->h[0x392 / 2] = 25;
            func_00282A60(D_L18_002571A0, 0, 0x50);
            func_PAL_L18_002CFC50(4, 0x8D, a0);
            ((Hero *)D_00189E20)->f[0x98 / 4] = f;
            ((View *)a0)->f[0xF8 / 4] = f;
            D_L18_001B2564[1] = 0;
            if (D_001A79F0 == 0x13) {
                if (((View *)D_0018C958)->uh[0x504 / 2] == 0)
                    func_PAL_00289730(0xA14, 0x6B);
                else
                    ((View *)D_0018C958)->uh[0x504 / 2] = 0xFFFF;
            }
            D_L18_001AFBB0 = 0;
            func_002A7750(a0, 7, 8);
            h = ((View *)v)->i[0x3F0 / 4];
            if (h != -1) {
                u8 *e = D_00188660 + h * 0x70;
                if (*(u8 **)(e + 0x88) == a0 && e[0x74] != 0)
                    func_002E59F8(h);
            }
            ((View *)v)->i[0x3F0 / 4] = -1;
        }
        t = 1.0f - func_00283CE0(((View *)v)->h[0x396 / 2]) / (float)(((s32)D_L18_001B1290 * 5 + 2) / 6);
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        func_00282CF0(c, D_00189EA0, a0 + 0x10);
        *(Vec4 *)b = *(Vec4 *)c;
        b[2] = 0.0f;
        func_00282F20(b, b, D_L18_001B1294);
        func_00282CD8(c, b, a0 + 0x10);
        b[2] += D_L18_001B1298;
        func_00282CF0(c, ref, b);
        *(Vec4 *)a = *(Vec4 *)c;
        func_00282F20(a, a, ((View *)v)->f[0x3B8 / 4] * func_00283CE0(((View *)v)->h[0x396 / 2]));
        func_00282CD8(c, a, b);
        ang[2] = func_00283248(((View *)a0)->f[0x10 / 4] - a[0], ((View *)a0)->f[0x14 / 4] - a[1]);
        ang[1] = -func_00283248(func_00282E80(a, a0 + 0x10), ((View *)a0)->f[0x18 / 4] - a[2]);
        ang[0] = D_L18_001B129C * (func_00283198(func_002ABB18(t * 6.28318548f)) * 0.0174532942f);
        func_00335370(a);
        func_003353C8(ang);
        if (((View *)a0)->b[0x95] == 8)
            func_003355A8(1);
        break;
    }
    case 8:
        func_002B0C28(6, 0, 20);
        if ((((Hero *)D_00189E20)->b[0x22B4] != 4 || ((Hero *)D_00189E20)->p[0x2290 / 4] != a0) && ((View *)v)->h[0x392 / 2] == 0) {
            if (((Hero *)D_00189E20)->b[0x22B4] != 4)
                func_PAL_0029C0F0(0, 0);
            D_L18_001AFBB0 = 0;
            ((View *)v)->i[0x13C / 4] = ((View *)v)->i[0x384 / 4];
            ((View *)v)->i[0x37C / 4] = ((View *)v)->i[0x360 / 4];
            ((View *)v)->i[0x38C / 4] = -1;
            ((View *)a0)->b[0xBC] = 0;
            func_002B60B0(a0, ((View *)v)->f[0x3C4 / 4] * 0.00040000002f, ((View *)v)->f[0x3C0 / 4] * 0.020000001f,
                          ((View *)v)->f[0x3D4 / 4] * 6.981318e-06f, ((View *)v)->f[0x3D0 / 4] * 0.0003490659f);
            ((View *)a0)->uh[0x34 / 2] &= 0xFFBE;
            sel = func_L18_004283F0(a0);
            func_PAL_002AC718(a0, D_L18_001A8F20, 0, 2.0f, (float)((View *)v)->b[0x35], 5, 2, 9, 6.0f, 4.0f, 9.0f, 1.10000002f,
                          sel, 0.0f, 1, 1, -2, 0, 0x850001);
            func_002A7750(a0, 11, -1);
        }
        break;
    }

    switch (((View *)a0)->b[0x20]) {
    case 1:
        func_PAL_002B5E30(a0, func_00283248(((View *)v)->f[0x220 / 4] - ((View *)a0)->f[0x10 / 4],
                                        ((View *)v)->f[0x224 / 4] - ((View *)a0)->f[0x14 / 4]));
        break;
    case 2:
        func_PAL_002B5E10(a0);
        if (((View *)v)->h[0x392 / 2] == 0) {
            ((View *)v)->h[0x392 / 2] = ((s32)D_L18_001B1260 * 5 + 2) / 6;
            func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
            func_002A7750(a0, 4, -1);
        }
        break;
    case 3:
        func_002AAA00(a0 + 0xF8,
                      func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - ((View *)a0)->f[0x10 / 4],
                                    ((Hero *)D_00189E20)->f[0x84 / 4] - ((View *)a0)->f[0x14 / 4]),
                      v + 0x1B4, 0, ((View *)v)->f[0x114 / 4], ((View *)v)->f[0x118 / 4], ((View *)v)->f[0x11C / 4]);
        if (((View *)a0)->b[0x60] & 2) {
            func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
            func_002A7750(a0, 4, -1);
        }
        break;
    case 4:
        func_PAL_L18_0042D7E0(a0);
        break;
    case 5:
        if (func_PAL_L07_00324F58(a0, 7.0f, 32.0f, 37.0f) != 0) {
            if (func_L18_0033B628(a0 + 0x10, ((View *)v)->i[0x380 / 4], 0) != 0) {
                ((View *)v)->h[0x392 / 2] = 0;
                func_002A7750(a0, 0, 4);
            } else {
                s32 n;

                func_PAL_L18_0042BA90(a0, 2, 0, 10.0f);
                n = ((View *)v)->i[0x370 / 4];
                if (n != -1) {
                    func_L18_00427130(a0, n, -1);
                    func_002A7750(a0, 4, 5);
                } else {
                    if (((View *)v)->i[0x374 / 4] != -1)
                        func_L18_00427130(a0, ((View *)v)->i[0x374 / 4], -1);
                    else
                        ((View *)v)->i[0x38C / 4] = -1;
                    func_002A7750(a0, 4, 6);
                }
            }
        }
        break;
    case 6:
        func_PAL_L18_0042D3B8(a0);
        break;
    case 12:
        sel = func_L18_004283F0(a0);
        func_PAL_002AC718(a0, D_L18_001A8F20, 0, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f,
                      sel, 15.0f, 1, 1, -1, 0, 0x810001);
    case 11: {
        u16 b2;
        u8 *p;
        u8 c;

        func_L18_00427010(a0);
        b2 = ((View *)a0)->uh[0xB2 / 2];
        if (b2 & 1) {
            u8 *q = D_0019B4A8 + (((s16)b2 >> 1) + (D_001A79F0 << 10));
            if (((*q >> 4) & 7) != 7)
                *q += 0x10;
        } else {
            u8 *q = D_0019B4A8 + (((s16)b2 >> 1) + (D_001A79F0 << 10));
            if ((*q & 7) != 7)
                *q += 1;
        }
        D_L18_0021DB40[1][((View *)a0)->h[0xB2 / 2]] = ((View *)a0)->b[0xB0] + 2;
        if (((View *)a0)->b[0xB0] == 0xFF || (!(D_L18_001B2660[((View *)a0)->b[0xB0]] & 0x80) && (D_0019B2E8[((View *)a0)->b[0xB0] + (D_001A79F0 << 4)] & 0x80)))
            D_L18_0021E7B0[1][((View *)a0)->h[0xB2 / 2]] = ((View *)a0)->b[0xB0] + 2;
        c = ((View *)v)->b[0x3B1];
        if (c != 0 && c != 0xFE
            && (((View *)a0)->b[0xB0] == 0xFF || !(D_0019B2E8[((View *)a0)->b[0xB0] + (D_001A79F0 << 4)] & 0x80))) {
            func_PAL_L18_0042BD70(a0);
        } else {
            func_0029F338(a0);
            return;
        }
        break;
    }
    }
    func_PAL_L18_0042CC40(a0);
}
