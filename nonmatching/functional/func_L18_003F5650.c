/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * GPT-6.1 Sol worker v1617, 2026-10-29: recompiled this retained draft with
 * upstream pinned toolchain, dedicated -O2 -G16 -Wa,-G16 -ffunction-sections
 * unit. USA: 5,716/5,716 bytes, 0/3 places; first mismatch +0xEF0 (case 13
 * a0/a1 setup order). The case 13 loop still hoists the group mask/shift.
 * Independent -g, -frac2-gcse-unsplit-edges and -frac2-keep-block-order probes
 * do not improve the first mismatch (0/3 each). No C body change retained.
 * USA v2.00: 0/3 places, same first mismatch +0xEF0. PAL: neither catalogue.
 * Six checker runs total; no linked build (no match).
 * All required declarations follow below. See older detailed analysis.
 */
/*
 * func_L18_003F5650 (5,716 B; levels 18, 19, 20): Opus near miss, 2026-10-26 (slates big5,
 * big12). Profile: -O2 -G16 -Wa,-G16 -ffunction-sections, as its own unit
 * (src/levels/shared/L18_003F5650-g16.c). check.py: 5,716 of 5,716 bytes, opcodes 1,424 of
 * 1,429 in place; about 27 instructions differ, all in case 13:
 *  - big12 fixed case 6 (the 0x31 arms each end with the whole 0x48 store, so flow's
 *    (use 0) after the arm's call no longer blocks cross-jumping) and case 10 (a `char *h`
 *    copy of D_00189E20 inside the loop, D_00189EA0 read as h + 0x80: global alloc then gives
 *    $fp to &D_00189E20 and rematerialises 0xB69, as retail does).
 *  - case 13, the call to func_L14_00423CD0: retail sets a1 before a0; no float position
 *    in the prototype (0..5 tried) and no declaration order changes it.
 *  - case 13 group loop: retail recomputes (u8)grp and grp << 2 on each pass. Here PRE
 *    (classic, non-edge LCM) inserts both at the end of the preheader (gcse -dG: "PRE/HOIST
 *    end of bb 177"), which also makes loop.c call the loop phony. Retail inserts only the
 *    %hi of D_L18_001FB320 there ($s3). Rereading the group in the increment, as case 12
 *    does (`grp = *(s32 *)(st + 0x27C), g++`), gives retail's loop shape exactly but keeps
 *    the reload lw (+4 bytes) and moves grp/g/lost to a2/a1/t0 (retail a1/a2/a3): the
 *    reload is fully redundant (no store or call in the loop), yet this PRE does not delete
 *    it; retail did, or the source differs. A loop-carried `id = grp` copy stops the shift
 *    hoist but cprop restores the and. Next step: instrument pre_lcm for the 0x27C load.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 *D_0018C2BC[];
extern s32 D_0018C0B4[];
extern s32 D_001A7A00[] __attribute__((section(".sdata")));
extern u8 *D_L18_001BFC18[];
extern u8 *D_L18_001C3C80[];
extern u32 D_L18_001B2348[] __attribute__((section(".sdata")));
/* The 16-byte offset vector (0, 0, 0.5, 0); its size keeps it $gp-relative at -G16. */
extern float D_L18_001B0420[4] __attribute__((sda));
extern u16 *D_L18_001FB320[];
extern s32 D_L18_001B2838[] __attribute__((section(".sdata")));
extern u8 *D_L18_001B281C[] __attribute__((section(".sdata")));
extern s32 *D_L18_001FE480[];

extern int func_00277258(void *, int, void *, float);
extern int func_00277F48(void *, int, void *, int, float);
extern float func_0029F530(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern void func_002A05A8(void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern u8 *func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern void func_002ACB48(void *, float);
extern int func_002ACBC8(void *, int);
extern void func_002B1350(void *, void *, void *, int);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L09_0033E690(void *, int, float);
extern int func_L14_00423CD0(void *, void *, int, s16 *, int, float);
extern void func_L18_0032B768(void *, int, int);
extern void func_L18_003F72D8(void *, void *);
extern int func_L18_003F7320(void *);
extern int func_L18_003F7358(void *, void *);
extern int func_L18_003F73B8(void *, void *);
extern int func_L18_003F7470(void *);
extern void func_L18_003F74B8(void *, int);
extern u8 *func_L18_003F75E8(void *, s32 *);
extern void func_L18_003F76F0(void *, void *, void *);
extern int func_L18_003F8E80(void *);

void func_L18_003F5650(u8 *a0)
{
    float p[4] __attribute__((aligned(16)));
    float q[4] __attribute__((aligned(16)));
    float r[4] __attribute__((aligned(16)));
    s32 n;
    u8 *st;

    st = *(u8 **)(a0 + 0x68);
    switch (a0[0x20]) {
    case 3:
        if (func_002B3868(a0) != 0) {
            *(s16 *)(st + 0x2A6) = 0;
            func_002A7470(a0, 9, 0, 3);
            func_002A05A8(a0);
            a0[0x31] = 1;
            *(float *)(a0 + 0x2C) = 0.001f;
            *(u16 *)(a0 + 0x34) &= 0xFFFE;
            *(s16 *)(st + 0x294) = 0;
            *(s16 *)(st + 0x29E) = func_002A7820(0xB4, 0xB4);
            *(s16 *)(st + 0x2A4) = func_002A7820(2, 4);
        } else {
            if (*(s16 *)(st + 0x2A6) == 0 && *(u16 *)(a0 + 0x96) >= 0x1F) {
                *(s16 *)(st + 0x2A6) = 1;
            }
            if (*(float *)(a0 + 0x2C) < *(float *)(st + 0x268)) {
                *(float *)(a0 + 0x2C) += *(float *)(st + 0x268) * 0.1f;
            }
            if (func_L18_003F7320(a0) != 0) {
                *(float *)(a0 + 0x2C) = *(float *)(st + 0x268);
                func_002A7750(a0, 6, 2);
                func_002A7750(a0, 7, -1);
            }
        }
        *(TI128 *)r = 0;
        r[2] = *(float *)(st + 0x104) + *(float *)(st + 0x100);
        *(TI128 *)q = *(TI128 *)r;
        func_00282CC0(p, a0 + 0x10, q);
        func_002A8C28(a0, p, 0x4000000, 0, 1, 0, *(float *)(st + 0x100) + 0.2f, 10.0f, 1.0f);
        break;
    case 2:
        if (func_002B3868(a0) != 0) {
            *(float *)(st + 0x100) = 0.34f;
            *(float *)(st + 0x108) = 0.1f;
            *(float *)(st + 0x104) = 0.0f;
            if (a0[0x43] != 9) {
                func_002A7470(a0, 9, 0, 0);
            }
            a0[0x31] = 0;
            a0[0xBC] = 0;
            *(u16 *)(a0 + 0x34) |= 1;
            break;
        }
        if (a0[0xBC] == 0) {
            if (func_002ACBC8(D_00189EA0, *(s32 *)(st + 0x270)) != 0) {
                *(u16 *)(a0 + 0x96) = 0;
                a0[0xBC] = 1;
            }
            break;
        }
        if (a0[0xBC] != 1) {
            break;
        }
        *(TI128 *)r = 0;
        r[2] = *(float *)(st + 0x104) + *(float *)(st + 0x100);
        *(TI128 *)q = *(TI128 *)r;
        func_00282CC0(p, a0 + 0x10, q);
        func_002A8C28(a0, p, 0x4000000, 0, 1, 0, *(float *)(st + 0x100) + *(float *)(st + 0x100), 10.0f,
                      1.0f);
        if (*(u16 *)(a0 + 0x96) >= 0xB) {
            func_00282F20(r, a0 + 0xC0, 0.06666667f);
            r[2] = 0.033333335f;
            func_L18_003F76F0(a0, a0 + 0x10, r);
        }
        break;
    case 7:
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 0) {
                func_002A7470(a0, 0, 0, 0xA);
            }
        } else if (a0[0x60] & 2) {
            func_002A7750(a0, a0[0x94], -1);
        }
        break;
    case 16: {
        float f;
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 2) {
                func_002A7470(a0, 2, 0, 0xA);
            }
            func_00282F20(st + 0x1A0, a0 + 0xC0, -0.06666667f);
            break;
        }
        f = func_0029F530(a0);
        if (*(float *)(a0 + 0x48) == 1.0f && 23.0f < f) {
            *(float *)(a0 + 0x48) = -0.65f;
            func_00282F20(st + 0x1A0, a0 + 0xC0, 0.13333334f);
            *(float *)(st + 0x1A8) += 0.1388889f;
        } else if (*(float *)(a0 + 0x48) == -0.65f && f < 3.0f) {
            *(float *)(a0 + 0x48) = 1.0f;
            func_002A7750(a0, a0[0x94], -1);
        }
        break;
    }
    case 6:
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != func_002A77E0(2) + 1) {
                func_002A7470(a0, func_002A77E0(2) + 1, 0, func_002A7820(9, 0xF));
            }
            *(s32 *)(st + 0x250) = func_002A7820(0x1E0, 0x258);
        } else if (*(s32 *)(st + 0x258) != 0) {
            func_002A7750(a0, 0xB, -1);
        } else if (*(s32 *)(st + 0x278) != -1) {
            func_002A7750(a0, 0xD, -1);
        } else if (*(s32 *)(st + 0x248) == 1 && D_0018C0B4[0] != 0x6F) {
            func_002A7750(a0, 0xC, -1);
        }
        if (a0[0x60] & 2) {
            if (func_002A77E0(0x31) == 0) {
                if (a0[0x43] != 0xA) {
                    func_002A7470(a0, 0xA, 0, func_002A7820(9, 0xF));
                }
                *(float *)(a0 + 0x48) = func_002A7878(0.85f, 1.15f);
            } else {
                if (a0[0x43] != func_002A77E0(2) + 1) {
                    func_002A7470(a0, func_002A77E0(2) + 1, 0, func_002A7820(9, 0xF));
                }
                *(float *)(a0 + 0x48) = func_002A7878(0.85f, 1.15f);
            }
        }
        break;
    case 8:
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 0xA) {
                func_002A7470(a0, 0xA, 0, 0xA);
            }
        } else if (a0[0x60] & 2) {
            func_002A7750(a0, a0[0x94], -1);
        }
        break;
    case 9:
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 6) {
                func_002A7470(a0, 6, 0, 0xA);
            }
            a0[0xBC] = 0;
            *(s16 *)(st + 0x298) = 0;
            break;
        }
        if (a0[0xBC] == 0 && (a0[0x60] & 2)) {
            if (a0[0x43] != 7) {
                func_002A7470(a0, 7, 0, 0xA);
            }
            a0[0xBC] = 1;
        } else if (a0[0xBC] == 1) {
            n = 0x32;
            if (*(u16 *)(a0 + 0x96) >= 0x15) {
                u8 *spawn;
                *(u16 *)(a0 + 0x96) = 0;
                spawn = func_L18_003F75E8(*(u8 **)(st + 0x25C), &n);
                if (spawn != 0) {
                    float d;
                    func_00282CC0(p, a0 + 0x10, D_L18_001B0420);
                    func_00282C88(q);
                    q[2] = 0.13333334f;
                    d = func_002A7878(2.0f, 3.0f) * 0.016666668f;
                    q[0] = q[0] + (func_002A77E0(2) != 0 ? d : -d);
                    d = func_002A7878(2.0f, 3.0f) * 0.016666668f;
                    q[1] = q[1] + (func_002A77E0(2) != 0 ? d : -d);
                    func_L18_003F76F0(spawn, p, q);
                    *(s32 *)(spawn + 0xB8) = *(s32 *)(a0 + 0xB8);
                    (*(s16 *)(st + 0x298))++;
                }
            }
            if (*(s16 *)(st + 0x298) >= 3 || n == 0) {
                if (a0[0x43] != 8) {
                    func_002A7470(a0, 8, 0, 0xA);
                }
                a0[0xBC] = 2;
            }
        } else if (a0[0xBC] == 2) {
            if (a0[0x60] & 2) {
                func_002A7750(a0, a0[0x94], -1);
            }
        }
        break;
    case 10: {
        float f;
        s32 count;
        s32 i;
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 5) {
                func_002A7470(a0, 5, 0, 0xA);
            }
            break;
        }
        f = func_0029F530(a0);
        if (a0[0x42] == 5 && f < 10.0f) {
            func_002B60B0(a0, 0.083333336f, 0.33333334f, 0.1939255f, 2.9088826f);
            if (a0[0x94] == 0xB && *(u8 **)(st + 0x258) != 0) {
                func_L18_003F72D8(a0, *(u8 **)(st + 0x258) + 0x10);
            } else {
                func_L18_003F72D8(a0, st + 0x1F0);
            }
        }
        if (a0[0x42] == 5 && 10.0f < f && f < 17.0f) {
            func_0029FCC0(a0, 0, p);
            count = func_00277F48(p, 0, a0, 0, 0.2f);
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    u8 *e = D_L18_001C3C80[i];
                    char *h = D_00189E20;
                    if (e == *(u8 **)(h + 0x2290)) {
                        qcopy(q, h + 0x80);
                    } else {
                        qcopy(q, e + 0x10);
                        if (*(s16 *)(e + 0xAA) == 0xB69) {
                            continue;
                        }
                    }
                    func_00282CF0(r, e + 0x10, a0 + 0x10);
                    r[2] = 0.0f;
                    func_00282F20(r, r, 2.0f);
                    r[3] = 5627.925f;
                    func_002A8F70(e, a0, 0x10001, e + 0x10, r, st[0x34]);
                }
            }
        }
        if (a0[0x60] & 2) {
            func_002B60B0(a0, 0.0044444446f, 0.13333334f, 0.003490659f, 0.20943955f);
            if (D_0018C2BC[0] == a0) {
                u8 next = a0[0x94];
                func_002A7750(a0, 8, -1);
                a0[0x94] = next;
            } else {
                func_002A7750(a0, a0[0x94], -1);
            }
        }
        break;
    }
    case 11: {
        u8 *e;
        if (func_002B3868(a0) != 0) {
            if (a0[0x43] != 4) {
                func_002A7470(a0, 4, 0, 0xA);
            }
            *(float *)(st + 0x24C) = 0.017453294f;
            break;
        }
        qcopy_nc(st + 0x230, *(u8 **)(st + 0x258) + 0x10);
        if (func_L18_003F8E80(*(u8 **)(st + 0x258)) != 0 && func_L18_003F73B8(a0, *(u8 **)(st + 0x258) + 0x10) != 0) {
            func_002A7750(a0, 0xA, -1);
            break;
        }
        if (func_L18_003F7358(a0, *(u8 **)(st + 0x258)) != 0) {
            func_002A7750(a0, 8, -1);
            break;
        }
        e = *(u8 **)(st + 0x258);
        if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD || (*(u16 *)(e + 0x34) & 1)) {
            *(u8 **)(st + 0x258) = 0;
            func_002A7750(a0, 0xC, -1);
            func_002A7750(a0, 8, -1);
        }
        break;
    }
    case 12: {
        u8 phase;
        s32 grp;
        if (func_002B3868(a0) != 0) {
            float f;
            if (a0[0x43] != 4) {
                func_002A7470(a0, 4, 0, 0xA);
            }
            f = func_002A7878(15.0f, 30.0f);
            *(float *)(st + 0x24C) = f * (func_002A77E0(2) != 0 ? -0.017453294f : 0.017453294f);
            a0[0xBC] = 0;
        }
        phase = a0[0xBC];
        if (phase == 0) {
            qcopy(st + 0x230, st + 0x1F0);
            grp = *(s32 *)(st + 0x27C);
            if (grp != -1 && (D_L18_001B2348[0] & 7) == (((s32)a0 >> 8) & 7)) {
                u16 *g;
                float best = 1000.0f;
                s32 lost = 1;
                for (g = D_L18_001FB320[grp];
                     (u8)grp != 0xFF && grp <= D_L18_001B2838[0] && g != 0
                     && ((g != 0 && (s16)g[-1] >= 0) || g == D_L18_001FB320[grp]);
                     grp = *(s32 *)(st + 0x27C), g++) {
                    u8 *e = D_L18_001B281C[0] + ((*g & 0x7FFF) << 8);
                    if (e == 0) {
                        break;
                    }
                    if (e[0x20] != 0xFE) {
                        if (e[0x20] != 0xFD) {
                            float d;
                            lost = 0;
                            d = func_00282E80(a0 + 0x10, e + 0x10);
                            if (d < best) {
                                best = d;
                            }
                        }
                    }
                }
                if (lost) {
                    *(s32 *)(st + 0x278) = -1;
                    *(s32 *)(st + 0x27C) = -1;
                }
            }
            if (func_L18_003F73B8(a0, st + 0x1F0) != 0) {
                *(u16 *)(a0 + 0x96) = 0;
                a0[0xBC] = 1;
                if (a0[0x43] != func_002A77E0(2) + 1) {
                    func_002A7470(a0, func_002A77E0(2) + 1, 0, 0xA);
                }
            }
        } else if (phase == 1) {
            if (func_L18_003F73B8(a0, st + 0x1F0) != 0 && *(s32 *)(st + 0x180) < 2) {
                func_002A7750(a0, 0xA, -1);
            } else if (*(u16 *)(a0 + 0x96) >= 0x3D) {
                func_002A7750(a0, 0xC, -1);
            }
        }
        if (func_L18_003F7470(a0) != 0) {
            func_002A7750(a0, 9, 2);
        }
        if (*(s32 *)(st + 0x248) != 1) {
            func_002A7750(a0, 6, -1);
        }
        break;
    }
    case 13: {
        u16 *g;
        s32 grp;
        s32 lost;
        if (func_002B3868(a0) != 0) {
            float f;
            if (a0[0x43] != 4) {
                func_002A7470(a0, 4, 0, 0xA);
            }
            *(s16 *)(st + 0x29A) = func_L09_0033E690(a0 + 0x10, *(s32 *)(st + 0x278), 0.0f);
            f = func_002A7878(15.0f, 30.0f);
            *(float *)(st + 0x24C) = f * (func_002A77E0(2) != 0 ? -0.017453294f : 0.017453294f);
            func_002B60B0(a0, 0.0016666667f, 0.050000004f, 0.003490659f, 0.10471977f);
            break;
        }
        func_L14_00423CD0(a0, st + 0x230, *(s32 *)(st + 0x278), (s16 *)(st + 0x29A), 0, 3.0f);
        grp = *(s32 *)(st + 0x27C);
        if (grp == -1) {
            break;
        }
        if ((D_L18_001B2348[0] & 0x3F) != (((s32)a0 >> 8) & 0x3F)) {
            break;
        }
        lost = 1;
        for (g = D_L18_001FB320[grp];
             (u8)grp != 0xFF && grp <= D_L18_001B2838[0] && g != 0
             && ((g != 0 && (s16)g[-1] >= 0) || g == D_L18_001FB320[grp]);
             g++) {
            u8 *e = D_L18_001B281C[0] + ((*g & 0x7FFF) << 8);
            if (e == 0) {
                break;
            }
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    lost = 0;
                    break;
                }
            }
        }
        if (lost) {
            *(s32 *)(st + 0x278) = -1;
            *(s32 *)(st + 0x27C) = -1;
            func_002A7750(a0, 0xC, -1);
        }
        break;
    }
    case 14:
        if (func_002B3868(a0) != 0) {
            s32 next;
            s32 *path;
            *(float *)(st + 0xAC) = 1.0f;
            *(float *)(st + 0xA8) = 1.0f;
            *(float *)(st + 0x134) = 0.001f;
            *(s16 *)(st + 0x29A) = func_L09_0033E690(a0 + 0x10, *(s32 *)(st + 0x26C), 0.0f);
            if (*(s16 *)(st + 0x29C) != 0) {
                if (*(s16 *)(st + 0x29A) == 0) {
                    next = *D_L18_001FE480[*(s32 *)(st + 0x26C)] - 1;
                } else {
                    next = *(s16 *)(st + 0x29A) - 1;
                }
            } else {
                next = (*(s16 *)(st + 0x29A) == *D_L18_001FE480[*(s32 *)(st + 0x26C)] - 1) ? 0
                                                                                           : *(s16 *)(st + 0x29A) + 1;
            }
            path = D_L18_001FE480[*(s32 *)(st + 0x26C)];
            func_00282CF0(p, path + (next * 4 + 4), path + (*(s16 *)(st + 0x29A) * 4 + 4));
            func_00282CF0(q, D_L18_001FE480[*(s32 *)(st + 0x26C)] + (*(s16 *)(st + 0x29A) * 4 + 4), a0 + 0x10);
            if (func_00282DB0(q, p) < 0.0f) {
                *(s16 *)(st + 0x29A) = next;
            }
            *(s32 *)(a0 + 0x98) = 0;
            *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
            if (a0[0x43] != func_002A77E0(2) + 1) {
                func_002A7470(a0, func_002A77E0(2) + 1, func_002A77E0(0xA), 0xA);
            }
            a0[0xBC] = 0;
            break;
        }
        if (a0[0xBC] == 0) {
            if (*(s32 *)(st + 0x270) != -1 && func_002ACBC8(D_00189EA0, *(s32 *)(st + 0x270)) != 0) {
                a0[0xBC] = 1;
                *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) & 0xFFBE) | 0x1000;
                *(s32 *)(a0 + 0x98) = *(s32 *)(*(u8 **)(a0 + 0x24) + 0x10);
                func_L18_0032B768(a0, 0, 2);
            }
        } else {
            float d;
            u8 *pos;
            if (func_L14_00423CD0(a0, st + 0x230, *(s32 *)(st + 0x26C), (s16 *)(st + 0x29A),
                                  *(s16 *)(st + 0x29C), 0.2f) == 0) {
                func_002A7750(a0, 0xF, -1);
            }
            pos = a0 + 0x10;
            d = func_00282E48(pos, D_00189EA0);
            if (d < 8.0f) {
                if (a0[0x43] != 1) {
                    func_002A7470(a0, 1, 0, 0xA);
                }
                if (d < 2.0f) {
                    u8 *hit;
                    float reach;
                    qcopy(p, pos);
                    p[2] = p[2] + (*(float *)(st + 0x104) + *(float *)(st + 0x100));
                    reach = *(float *)(st + 0x100) + 0.2f;
                    func_002A8C28(a0, p, 1, 0, 1, 0, reach, func_00283CE0(D_001A7A00[0]) * 0.25f, 1.0f);
                    if (func_00277258(p, 1, a0, *(float *)(st + 0x100) + 0.2f) != 0) {
                        hit = D_L18_001BFC18[0];
                        if (hit != 0 && *(s16 *)(hit + 0xAA) != 0xB69) {
                            *(s32 *)(st + 0x20) = 0;
                            func_00282F20(q, a0 + 0xC0, -1.0f);
                            func_002ACB48(q, 0.3f);
                            func_002B1350(a0, st + 0x50, q, 2);
                            func_002A7750(a0, 0x11, 3);
                        }
                    }
                }
            }
        }
        break;
    case 15:
        if (func_002B3868(a0) != 0) {
            func_002ACB48(st + 0x1A0, 0.050000004f);
            *(float *)(st + 0x1A8) = 0.083333336f;
            if (a0[0x43] != 0xD) {
                func_002A7470(a0, 0xD, 0, 0xA);
            }
        } else if (*(u16 *)(a0 + 0x96) >= 0x12D) {
            func_002A6C58(a0, 0, 1);
            func_L18_003F74B8(a0, 0);
        }
        break;
    case 17: {
        s32 flags;
        float f;
        if (func_002B3868(a0) != 0) {
            if (a0[0x42] == 0xC || a0[0x43] == 0xC) {
                *(u16 *)(a0 + 0x34) &= 0xEFFF;
            }
            if (a0[0x94] == 0xE) {
                func_00282D30(st + 0xD0, st + 0xD0, 3.0f);
            }
        }
        flags = func_002B1C20(a0, st + 0x50);
        if (a0[0x94] == 0xE || a0[0x94] == 0xF) {
            f = func_0029F530(a0);
            if (a0[0x42] == 0xB && 16.0f < f) {
                func_002A7750(a0, 0xF, -1);
            }
        }
        f = func_0029F530(a0);
        if ((flags & 1) || (a0[0x42] == 0xC && 15.0f < f && func_002A77E0(0xF) == 0)) {
            func_002A6C58(a0, 0, 1);
            func_L18_003F74B8(a0, 0);
            break;
        }
        if (flags & 2) {
            u8 mode;
            *(u8 **)(st + 0x258) = 0;
            mode = a0[0x95];
            func_002A7750(a0, 0xC, 2);
            if (mode == 1) {
                func_002A7750(a0, 7, -1);
            }
        }
        break;
    }
    case 18:
        if (func_002B3868(a0) != 0) {
            *(u16 *)(a0 + 0x34) &= 0xEFFF;
            if (a0[0x95] == 2) {
                if (a0[0x43] != 3) {
                    func_002A7470(a0, 3, 0, 0xA);
                }
            }
            *(float *)(a0 + 0x48) = 1.0f;
        }
        if ((a0[0x60] & 2) || *(u16 *)(a0 + 0x96) >= 0x3D) {
            *(s32 *)(st + 0x20) = 0;
            func_002A6C58(a0, 0, 1);
            func_L18_003F74B8(a0, 0);
        }
        break;
    case 0:
    default:
        break;
    }
}
