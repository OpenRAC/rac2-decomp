#include "common.h"

/* func_PAL_L12_0041A100, the PAL copy of func_L12_00415128: the same C, with its eleven
   timers and thresholds scaled to 50 Hz (f300 < 5 becomes < 4), the sweep step at 6/5 and
   D_L12_001B1828 read as a word. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct GuardVars GuardVars;

typedef struct {
    char pad00[0x10];
    s32 f10;                /* 0x10 */
} GuardClass;

typedef struct GuardMoby {
    char pad00[0x10];
    f32 x;                  /* 0x10 */
    f32 y;                  /* 0x14 */
    f32 z;                  /* 0x18 */
    f32 w;                  /* 0x1C */
    u8 state;               /* 0x20 */
    char pad21[0x24 - 0x21];
    GuardClass *f24;        /* 0x24 */
    char pad28[0x30 - 0x28];
    u8 f30;                 /* 0x30 */
    u8 f31;                 /* 0x31 */
    char pad32[0x34 - 0x32];
    u16 f34;                /* 0x34 */
    char pad36[0x42 - 0x36];
    u8 f42;                 /* 0x42 */
    u8 f43;                 /* 0x43 */
    char pad44[0x60 - 0x44];
    u8 f60;                 /* 0x60 */
    char pad61[0x68 - 0x61];
    GuardVars *vars;        /* 0x68 */
    char pad6C[0x95 - 0x6C];
    u8 f95;                 /* 0x95 */
    u16 f96;                /* 0x96 */
    s32 f98;                /* 0x98 */
    char pad9C[0xAA - 0x9C];
    s16 fAA;                /* 0xAA */
    char padAC[0xB2 - 0xAC];
    s16 fB2;                /* 0xB2 */
    char padB4[0xF8 - 0xB4];
    f32 fF8;                /* 0xF8 */
} GuardMoby;

struct GuardVars {
    char pad000[0x20];
    f32 f20;                /* 0x020 */
    char pad024[0x2E - 0x24];
    u8 f2E;                 /* 0x02E */
    char pad02F[0x138 - 0x2F];
    s32 f138;               /* 0x138 */
    char pad13C[0x1F0 - 0x13C];
    f32 f1F0;               /* 0x1F0 */
    f32 f1F4;               /* 0x1F4 */
    char pad1F8[0x200 - 0x1F8];
    GuardMoby *f200;        /* 0x200 */
    s32 f204;               /* 0x204 */
    char pad208[0x2B0 - 0x208];
    s32 f2B0;               /* 0x2B0 */
    char pad2B4[0x2B8 - 0x2B4];
    s32 f2B8;               /* 0x2B8 */
    s32 f2BC;               /* 0x2BC */
    s32 f2C0;               /* 0x2C0 */
    char pad2C4[0x2CC - 0x2C4];
    s32 f2CC;               /* 0x2CC */
    char pad2D0[0x2D4 - 0x2D0];
    s32 f2D4;               /* 0x2D4 */
    s32 f2D8;               /* 0x2D8 */
    s32 f2DC;               /* 0x2DC */
    s16 f2E0;               /* 0x2E0 */
    char pad2E2[0x2E4 - 0x2E2];
    u16 f2E4;               /* 0x2E4 */
    s16 f2E6;               /* 0x2E6 */
    s16 f2E8;               /* 0x2E8 */
    char pad2EA[0x2EC - 0x2EA];
    f32 f2EC;               /* 0x2EC */
    GuardMoby *f2F0[2];     /* 0x2F0 */
    GuardMoby *f2F8;        /* 0x2F8 */
    char pad2FC[0x300 - 0x2FC];
    s16 f300;               /* 0x300 */
    u8 f302;                /* 0x302 */
    u8 f303;                /* 0x303 */
    s32 *f304;              /* 0x304 */
    char pad308[0x30C - 0x308];
    u8 f30C;                /* 0x30C */
    u8 f30D;                /* 0x30D */
    u8 f30E;                /* 0x30E */
    u8 f30F;                /* 0x30F */
    char pad310[0x314 - 0x310];
    s32 f314;               /* 0x314 */
    char pad318[0x31C - 0x318];
    s8 f31C;                /* 0x31C */
    u8 f31D;                /* 0x31D */
    u8 f31E;                /* 0x31E */
    u8 f31F;                /* 0x31F */
    char pad320[0x4A0 - 0x320];
    GuardMoby *f4A0;        /* 0x4A0 */
};

/* The level's guard zone: its mode, its kind and the two heights it splits at. */
typedef struct {
    s32 mode;               /* 0x00 */
    char pad04[0xC - 0x4];
    s32 kind;               /* 0x0C */
    char pad10[0x28 - 0x10];
    f32 low;                /* 0x28 */
    char pad2C[0x38 - 0x2C];
    f32 high;               /* 0x38 */
} GuardZone;

extern GuardZone D_L12_001CA380;
extern s32 D_L12_001A8F00 __attribute__((sda));
extern s32 D_L12_001B1878 __attribute__((sda));
extern f32 D_L12_001B1814 __attribute__((sda));
extern f32 D_L12_001B1818 __attribute__((sda));
extern s32 D_L12_001B181C __attribute__((sda));
extern s32 D_L12_001B1820 __attribute__((sda));
extern s32 D_L12_001B1824 __attribute__((sda));
extern s32 D_L12_001B1828 __attribute__((sda));
extern s32 D_L12_001B182C __attribute__((sda));
extern s32 D_L12_001B1830 __attribute__((sda));
extern s32 D_L12_001B183C __attribute__((sda));
extern s32 D_L12_001B1840 __attribute__((sda));
extern s32 D_L12_001B29C8 MACRO_ADDR;
extern s32 D_L12_001B3D98 MACRO_ADDR;
extern s32 D_L12_001B3D9C MACRO_ADDR;
extern s32 D_L12_001B3DA0 MACRO_ADDR;
extern char *D_L12_001FEAC0[];
extern char D_00189EA0[];
extern char D_L12_001B1880[];
extern char D_L12_001B1890[];
extern char D_L12_001B18A8[];

extern void func_0026FEB8(const char *, ...);
extern int func_L02_002EF388(void *, void *, void *, void *, int);
extern float func_00282E80(void *, void *);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00283CE0(int);
extern void func_002A0488(void *, int, int, int);
extern void func_002A04B8(void *, s32 *, s32 *, s32 *);
extern void func_002A6C58(void *, int, int);
extern int func_002A77E0(int);
extern float func_002ABB18(float);
extern void func_002ABBB8(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern s32 func_002B1C20(void *, void *);
extern s32 func_002B3380(void *, void *, void *);
extern int func_002B3890(void *);
extern int func_L00_00329520(void *, int);
extern void func_002B5278(void *, float);
extern int func_001163B0(void);
extern s32 func_00282978(s16 *);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern void func_L09_003F73E8(void *);
extern void func_L09_003F7430(void *);
extern void func_L09_003F77D0(void *);
extern int func_L09_003F7B28(void *, int);
extern void func_L09_003F7C50(void *, int, int);
extern void func_L12_00412DA0(void *);
extern void func_L12_00412DE0(void *);
extern void func_L12_00412E50(void *, int, int, int);
extern void func_L12_00413CE0(void *);
extern void func_L12_00413F68(void *);
extern void func_L12_004141A8(void *);
extern void func_L12_00414670(void *);
extern void func_L12_004149B8(void *);
extern int func_L12_00414AB8(void *, int, int, int);
extern void func_L12_00414C60(void *);
extern void func_L12_00414EB8(void *);

void func_PAL_L12_0041A100(GuardMoby *moby)
{
    GuardVars *vars;
    GuardMoby *list[3];
    s32 sx, sy, sz;
    s32 n;
    s8 alarm;

    if (D_L12_001CA380.kind != 0) {
        f32 z = moby->z;
        if (z < D_L12_001CA380.low && D_L12_001CA380.mode == 1)
            return;
        if (D_L12_001CA380.low < z && D_L12_001CA380.mode == 0)
            return;
        if (D_L12_001CA380.kind == 2) {
            if (D_L12_001CA380.high < z && D_L12_001CA380.mode == 1)
                return;
            if (z < D_L12_001CA380.high && D_L12_001CA380.mode == 2)
                return;
        }
    }

    vars = moby->vars;
    if (vars->f2E == 2) {
        func_L12_00413CE0(moby);
        func_002B3380(moby, (char *)vars + 0x290, (char *)vars + 0x20);
        func_L09_003F73E8(moby);
        func_L09_003F77D0(moby);
        func_002ABBB8(moby, (char *)vars + 0xD0, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        func_0029F338(moby);
        return;
    }
    if (D_L12_001A8F00 == 2)
        return;

    if (vars->f31E != 0 && moby->f30 == 0xFF)
        moby->f30 = vars->f31E;

    if (vars->f314 != -1 && moby->f95 == 0) {
        if (func_L00_00329520(D_00189EA0, vars->f314) == 0) {
            if (vars->f31D == 0)
                vars->f31C = -1;
            else
                vars->f31C = 0;
        } else if (vars->f31C == 0) {
            vars->f31C = 1;
        }
    }

    if (vars->f302 & 1) {
        vars->f31C = -1;
        vars->f31F = 1;
    } else if (vars->f31D != 0) {
        if (vars->f31F == 1) {
            vars->f31F = 0;
            moby->f96 = 0;
            return;
        }
        if (moby->f96 < D_L12_001B1878) {
            moby->f96 = moby->f96 + 1;
            return;
        }
        vars->f31C = 1;
        func_L12_004141A8(moby);
        *(TI128 *)&moby->x = *(TI128 *)(D_L12_001FEAC0[vars->f2C0] + 0x10);
        n = 0;
        if (vars->f2F8 != 0) {
            list[0] = vars->f2F8;
            n = 1;
        }
        if (vars->f2F0[0] != 0)
            list[n++] = vars->f2F0[0];
        if (vars->f2F0[1] != 0)
            list[n++] = vars->f2F0[1];
        func_L02_002EF388(moby, &moby->x, (char *)moby + 0xF0, list, n);
    }

    if (vars->f4A0 != 0) {
        if (vars->f4A0->state == 0xFE)
            goto release;
        if (vars->f4A0->state == 0xFD) {
        release:
            func_002A04B8(moby, &sx, &sy, &sz);
        if (sx != D_L12_001B3D98 || sy != D_L12_001B3D9C || sz != D_L12_001B3DA0)
            func_0026FEB8(D_L12_001B1880);
        func_002A0488(moby, D_L12_001B3D98, D_L12_001B3D9C, D_L12_001B3DA0);
        vars->f4A0 = 0;
        }
    }

    alarm = vars->f31C;
    if (alarm < 0) {
        if (vars->f31D == 0) {
            GuardMoby *head;
            int i;

            moby->f98 = 0;
            moby->f31 = 0;
            moby->f34 = moby->f34 | 1;
            head = vars->f2F8;
            if (head != 0 && head->fAA == 0x114B && head->state != 0xFE && head->state != 0xFD) {
                head->f34 = head->f34 | 1;
                vars->f2F8->f31 = 0;
                vars->f2F8->f98 = 0;
            }
            for (i = 0; i < 2; i++) {
                GuardMoby *h = vars->f2F0[i];
                if (h != 0 && h->fAA == 0xD66 && h->state != 0xFE && h->state != 0xFD) {
                    h->f34 = h->f34 | 1;
                    vars->f2F0[i]->f31 = 0;
                }
            }
        }
        vars->f31C = 0;
        vars->f31D = 1;
        return;
    }
    if (alarm > 0) {
        if (vars->f31D != 0) {
            GuardMoby *head;
            int i;

            func_0026FEB8(D_L12_001B1890, D_L12_001B29C8, moby->fB2, alarm);
            moby->f31 = 1;
            moby->f34 = moby->f34 & 0xFFFE;
            moby->f98 = moby->f24->f10;
            func_002A0488(moby, D_L12_001B3D98, D_L12_001B3D9C, D_L12_001B3DA0);
            head = vars->f2F8;
            if (head != 0 && head->fAA == 0x114B && head->state != 0xFE && head->state != 0xFD) {
                head->f34 = head->f34 & 0xFFFE;
                vars->f2F8->f31 = 1;
                vars->f2F8->f98 = vars->f2F8->f24->f10;
            }
            for (i = 0; i < 2; i++) {
                GuardMoby *h = vars->f2F0[i];
                if (h != 0 && h->fAA == 0xD66 && h->state != 0xFE && h->state != 0xFD) {
                    h->f34 = h->f34 & 0xFFFE;
                    vars->f2F0[i]->f31 = 1;
                }
            }
            vars->f31D = 0;
        }
    } else if (vars->f31D != 0) {
        vars->f31C = 0;
        return;
    }
    vars->f31C = 0;

    func_L12_00412DA0(moby);
    moby->f31 = 1;
    moby->f34 = moby->f34 & 0xFFFE;
    func_L12_004141A8(moby);

    switch (moby->f95) {
    case 0:
        func_0026FEB8(D_L12_001B18A8, moby->fB2, moby->fAA);
        break;
    case 1:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            vars->f2D8 = vars->f2D4;
            if (!(vars->f302 & 1)) {
                vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
                func_002A7750(moby, moby->state, 2);
            } else {
                func_L12_00412E50(moby, 0xC, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 8, 5);
            }
        }
        break;
    case 2:
        if (func_002B3890(moby) != 0 && vars->f300 < 4 && !(vars->f302 & 2))
            vars->f300 = ((s32)func_002A7820(0, 0x78) * 5 + 2) / 6;
        if (func_00282978(&vars->f300) != 0) {
            vars->f2D8 = vars->f2D4;
            if (vars->f2B0 != -1) {
                func_L09_003F7C50(moby, vars->f2B0, -1);
                func_002A7750(moby, 2, 3);
            } else {
                func_L09_003F7C50(moby, vars->f2B8, -1);
                func_L12_00412E50(moby, 2, 0, 0xA);
                func_002A7750(moby, 4, 3);
            }
            if (vars->f302 & 2)
                func_L09_003F7C50(moby, vars->f2C0, -1);
        }
        /* fall through */
    case 3:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1)
            vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
        break;
    case 4:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            func_L09_003F7C50(moby, vars->f2B8, -1);
            vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
            func_L12_00412E50(moby, 2, 0, 0xA);
            func_002A7750(moby, 4, 3);
        }
        break;
    case 5:
        vars->f2EC = func_00283248(vars->f200->x - moby->x, vars->f200->y - moby->y);
        if (vars->f302 & 2) {
            int side = func_001163B0() & 1;
            func_L12_00412E50(moby, side, 0, func_002A7820(0xA, 0x14));
            func_L09_003F73E8(moby);
            vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
            vars->f300 = 1;
            func_002A7750(moby, moby->state, 2);
        }
        if (vars->f204 != 1 && vars->f2E0 == 0) {
            int side;
            func_L09_003F73E8(moby);
            side = func_001163B0() & 1;
            func_L12_00412E50(moby, side, 0, func_002A7820(0xA, 0x14));
            func_002A7750(moby, 5, 6);
        }
        break;
    case 6:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            func_L09_003F73E8(moby);
            vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
            func_L12_00412E50(moby, 3, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 5, 5);
        } else if (vars->f2E8 == 0) {
            int side;
            func_L09_003F73E8(moby);
            func_L09_003F7C50(moby, vars->f2B8, 0);
            side = func_001163B0() & 1;
            func_L12_00412E50(moby, side, 0, func_002A7820(0xA, 0x14));
            func_002A7750(moby, 4, 4);
        }
        break;
    case 7:
        vars->f2EC = func_00283248(vars->f200->x - moby->x, vars->f200->y - moby->y);
        break;
    case 8:
        vars->f2EC = func_00283B98(vars->f2EC,
            (func_00283198(func_002ABB18(func_00283CE0(D_L12_001B29C8) * 0.02f)) + 2.0f) * 0.027925273f);
        break;
    case 9: {
        s32 hit;

        vars->f2EC = moby->fF8;
        hit = func_002B1C20(moby, (char *)vars + 0x50);
        if (vars->f20 <= 0.0f && (moby->f42 == 0xF || moby->f43 == 0xF))
            func_002A7750(moby, 0xF, -1);
        if (hit & 1) {
            if (vars->f20 > 0.0f)
                func_L12_00413CE0(moby);
            func_L09_003F73E8(moby);
            func_002A7750(moby, 0xF, -1);
        } else if (hit & 2) {
            func_L09_003F73E8(moby);
            vars->f2E0 = ((s32)func_002A7820(D_L12_001B183C, D_L12_001B1840) * 5 + 2) / 6;
            if (moby->f42 == 0xF || moby->f43 == 0xF) {
                func_L09_003F7C50(moby, vars->f2B0, -1);
                func_002A7750(moby, 3, 3);
                func_L12_00412E50(moby, 0xE, 0, func_002A7820(7, 0xC));
            } else {
                func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
                if (vars->f30F != 0)
                    func_002A7750(moby, 0xD, 8);
                else
                    func_002A7750(moby, 6, 5);
            }
        }
        break;
    }
    }

    switch (moby->state) {
    case 0:
        break;
    case 1:
        if (moby->f60 & 2)
            func_L12_00412E50(moby, 0xE, 0, func_002A7820(7, 0xC));
        break;
    case 2:
        if (moby->f60 & 2) {
            func_L12_00412E50(moby, 0xE, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 3, -1);
        }
        break;
    case 4:
        if (moby->f60 & 2) {
            func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 6, -1);
        }
        break;
    case 5:
        if (moby->f60 & 2) {
            if (moby->f95 == 5) {
                func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 6, -1);
            } else {
                func_L12_00412E50(moby, 0xC, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 6, -1);
            }
        }
        break;
    case 3:
        if (moby->f60 & 2)
            func_L12_00412E50(moby, 0xE, 0, func_002A7820(7, 0xC));
        if (func_L09_003F7B28(moby, vars->f2DC) != 0) {
            vars->f138 = vars->f138 & ~4;
            func_L09_003F7C50(moby, vars->f2BC, -1);
            func_L12_00412E50(moby, 0x10, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 7, 5);
        }
        break;
    case 6:
        func_L12_00414EB8(moby);
        break;
    case 7:
        if (moby->f60 & 2) {
            if (vars->f30E != 0) {
                func_L12_00412E50(moby, 4, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 4, 5);
            } else {
                func_L12_00412E50(moby, 0xC, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 8, 5);
            }
        }
        break;
    case 8: {
        f32 yaw = func_00283248(vars->f1F0 - moby->x, vars->f1F4 - moby->y);

        func_002B5278(moby, yaw);
        if (func_00283C80(yaw, moby->fF8) < 0.17453295f) {
            func_L12_00412E50(moby, 5, 0, func_002A7820(7, 0xC));
            vars->f30C = 0;
            vars->f30D = 0;
            func_002A7750(moby, 9, -1);
        }
        break;
    }
    case 9: {
        f32 d;
        s32 near, close, ahead, picked, tried;

        near = 1;
        d = func_00282E80(&moby->x, &vars->f200->x);
        if (!(d <= D_L12_001B1818))
            near = 0;
        close = 1;
        ahead = *vars->f304 < vars->f2CC;
        if (!(d < D_L12_001B1814))
            close = 0;
        if (vars->f303 == 0) {
            picked = 0;
            tried = 0;
            if (close == 0 && near != 0 && ahead != 0 && func_002A77E0(D_L12_001B181C - 1) == 0
                && vars->f2E6 == 0) {
                tried = 1;
                picked = func_L12_00414AB8(moby, 0, vars->f30C != 0, 0);
            }
            if (vars->f30C != 0 && picked != 0 && close == 0) {
                func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 6, -1);
            } else if (close != 0 || picked != 0) {
                if (func_L12_00414AB8(moby, 0, (u8)(s8)vars->f30C != 0, 1) != 0)
                    vars->f30D = 1;
                func_L09_003F7430(moby);
                func_L12_00412E50(moby, 8, 0, 7);
                func_002A7750(moby, 0xA, -1);
            } else if (moby->f60 & 2) {
                func_L12_00412E50(moby, 6, 0, func_002A7820(7, 0xC));
            }
            if (tried != 0 && picked == 0)
                vars->f30C = ~vars->f30C;
        } else {
            if (moby->f60 & 2)
                func_L12_00412E50(moby, 6, 0, func_002A7820(7, 0xC));
            if (close != 0 || (vars->f2E6 == 0 && near != 0 && ahead != 0)) {
                func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
                func_002A7750(moby, 6, -1);
            }
        }
        break;
    }
    case 10:
        if (moby->f60 & 2) {
            if (vars->f30D != 0)
                func_L12_00412E50(moby, 0xA, 0, 1);
            else
                func_L12_00412E50(moby, 0x13, 0, 1);
            vars->f2E4 = ((s32)D_L12_001B1828 * 5 + 2) / 6;
            func_002A7750(moby, 0xB, -1);
        }
        break;
    case 11:
        if (moby->f96 > ((s32)D_L12_001B1824 * 5 + 2) / 6)
            func_L12_00414C60(moby);
        if ((moby->f96 > ((s32)D_L12_001B1820 * 5 + 2) / 6 && D_L12_001B1814 < func_00282E80(&moby->x, &vars->f200->x))
            || vars->f2F8 == 0) {
            vars->f2E6 = ((s32)func_002A7820(D_L12_001B182C, D_L12_001B1830) * 5 + 2) / 6;
            func_L09_003F73E8(moby);
            func_L12_00412E50(moby, 0xC, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 8, 5);
        }
        break;
    case 12:
        if (moby->f60 & 2) {
            func_L12_00412E50(moby, 0xB, 0, func_002A7820(7, 0xC));
            func_002A7750(moby, 6, 5);
        }
        break;
    case 13:
        if (moby->f60 & 2) {
            int anim = (func_001163B0() & 1) ? 0xA : 0x13;
            func_L12_00412E50(moby, anim, 0, func_002A7820(0x19, 0x2D));
        }
        if (moby->f42 == 0xA || moby->f42 == 0x13)
            func_L12_00414C60(moby);
        break;
    case 14:
        func_L09_003F73E8(moby);
        break;
    case 15:
        vars->f20 = 0.0f;
        func_002B3380(moby, (char *)vars + 0x290, (char *)vars + 0x20);
        func_L09_003F73E8(moby);
        func_L09_003F77D0(moby);
        func_002A6C58(moby, 0, 3);
        func_002ABBB8(moby, (char *)vars + 0xD0, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        func_0029F338(moby);
        return;
    }
    func_L12_00414670(moby);
    func_L12_004149B8(moby);
    func_L12_00413F68(moby);
    func_L12_00412DE0(moby);
}
