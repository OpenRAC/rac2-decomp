/* Current retained result, 1 November 2026: 5764/5672 bytes. Restore all five collision arguments and the
 * software float-to-double return. Test the adjacent waypoint sentinels with the observed 64-bit load,
 * reset offset 0x268 (not 0x26C), and model the spent-byte table without a one-element bound. Control-
 * flow/allocation differences remain; the smaller historical draft omitted real work.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections -ffast-math -Wa,-G8.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* Opus handoff (big17, 2026-10-26): func_L12_003E2460, 5672 bytes, 2 places (L12 0x003E2460,
 * L17 0x003E52F8). A path-walking enemy's update: pvars at +0x68 (path table D_L12_001FEAC0
 * indexed by pvars+0x158/0x164, a waypoint cursor at +0x264/0x268/0x26C, a 3-bit kill count
 * in D_0019B4A8 like func_L02_00445200), an 11-entry switch on moby+0x95 (jtbl_002A83D0) and
 * a 22-entry switch on moby+0x20 (jtbl_002A8400, cases 3..24). Step 0: one function. No twin
 * (best opcode ratio 0.08). Callees are the level's engine copies under catalogue names.
 * Profile: its own unit, `-O2 -G8 -ffunction-sections -ffast-math -Wa,-G8`
 * (-ffast-math: the min.s in case 21; -Wa,-G8: the level floats near GP 0x001AEFF0 are $gp in
 * ordinary flow, while D_001A79F0, whose .extern cc1 emits after use, stays absolute except in
 * delay slots, as retail). Measured with check.py: 5744/5672 bytes, 1332/1419 opcodes aligned.
 * What moved it: case bodies in table address order; func_0032C700 has 7 ints, 2 floats,
 * 4 ints; func_002C2210 is (float *, 4 ints, float *, int, 3 floats) with the func_002A77E0
 * result in a local; the first test is `pv278 == 1 || pv278 == 5` (5 handled above);
 * case 16's shoot block is the then-arm of `func_002AEB60(...) == 0` (case 15 jumps in).
 * Still off:
 *  - the kill-count block is written twice; retail shares the even arm and its tail with the
 *    first copy (cross-jumped), and in retail the even arm reloads D_001A79F0 (lui/lw) where
 *    this cc1 computes it once above the odd/even branch (not gcse: -fno-gcse keeps it). The
 *    single goto version is 5668 bytes but aligns worse;
 *  - argument-setup order around func_002761F8 (a3 = 0 placement) and func_00282E48;
 *  - the float load order in the two func_002B60B0 calls;
 *  - case 6/21 path walk: retail loads pvars+0x268 with ld in one place; one sll/addu pair.
 */
#include "common.h"

typedef int TI128_L12_003E2460 __attribute__((mode(TI)));
extern u8 D_L12_0021EDF0[];
extern u8 D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;
extern int D_L12_001A8F00 __attribute__((nosda));
extern char D_L12_001A8F20[];
extern char D_L12_001B0B18[];
extern char D_L12_001B0B38[];
extern char D_L12_001B0B50[];
extern s32 *D_L12_001FEAC0[];
extern f32 D_L12_001B0A50 __attribute__((sda));
extern f32 D_L12_001B0A54 __attribute__((sda));
extern s32 D_L12_001B0A58 __attribute__((sda));
extern f32 D_L12_001B0A80 __attribute__((sda));
extern f32 D_L12_001B0A84 __attribute__((sda));
extern f32 D_L12_001B0A88 __attribute__((sda));
extern s32 D_L12_001B0A8C __attribute__((sda));
extern f32 D_L12_001B0A90[4] __attribute__((sda));
extern f32 D_L12_001B0AA8 __attribute__((sda));
extern f32 D_L12_001B0AAC __attribute__((sda));
extern f32 D_L12_001B0AB0 __attribute__((sda));
extern f32 D_L12_001B0B04 __attribute__((sda));
extern f32 D_L12_001B0B08 __attribute__((sda));
extern f32 D_L12_001B0B14 __attribute__((sda));
extern f32 D_L12_001B0B34 __attribute__((sda));

extern void func_0026FEB8(const char *, ...);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00282978(void *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_0029F338(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_002AA800(void *, int, float, float);
extern int func_002AEB60(void *, float);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_002B3890(void *);
extern void * func_002B60B0(void *, float, float, float, float);
extern void * func_002C2210(float *, int, int, int, int, float *, int, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void * func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern double func_001234F0(float);
extern int func_L01_00321178(void *, void *);
extern void func_L12_003E1CB0(void *);
extern int func_L12_003E1EE8(void *, s32 *);
extern void func_L12_003E20F0(void *);
extern void func_L12_003E2370(void *);
extern void func_L12_003E2418(void *);
extern void func_L12_003E2448(void *);
extern void func_L12_003E3A88(void *);
extern void func_L12_00408050(void *, void *, void *, int, float);

void func_L12_003E2460(u8 *obj)
{
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[16] __attribute__((aligned(16)));
    f32 v70[4] __attribute__((aligned(16)));
    f32 v80[4] __attribute__((aligned(16)));
    u8 *pv = *(u8 **)(obj + 0x68);
    u8 *pos;
    int id, k5, k1, v, flags, n, lo, hi, i, fwd, back, cur, nxt;
    s32 *path;
    u8 *p;
    float dist, yaw, ground, y, ang, r;

    if (*(s32 *)(pv + 0x2A4) != 0) {
        id = *(u16 *)(obj + 0xB2);
        if (D_L12_0021EDF0[0x464 + (s16)id] != 0)
            goto release;
        v = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
        if (id & 1)
            v = (v >> 4) & 7;
        else
            v = v & 7;
        if (v != 0)
            goto release;
    }
    if (D_L12_001A8F00 == 2) {
        *(s32 *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    if (obj[0x95] != 7) {
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) & 0xFFBE) | 0x1000;
        *(s32 *)(obj + 0x98) = *(s32 *)(*(u8 **)(obj + 0x24) + 0x10);
    }
    pos = obj + 0x10;
    func_L12_003E3A88(obj);
    dist = func_00282E80(*(u8 **)(pv + 0x270) + 0x10, pos);
    if (dist < 8.0f && *(s32 *)(pv + 0x278) == 0) {
        *(s32 *)(pv + 0x278) = 3;
        *(s16 *)(pv + 0x274) = 0x32;
    }
    if (*(s32 *)(pv + 0x278) == 5) {
        func_002E5CF8(3, 0, obj);
        func_0032C700(pos, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        if (*(s32 *)(pv + 0x2A4) != 0) {
            k5 = *(u16 *)(obj + 0xB2);
            if (k5 & 1) {
                if (((D_0019B4A8[((s16)k5 >> 1) + (D_001A79F0 << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)k5 >> 1) + (D_001A79F0 << 10)] += 0x10;
            } else {
                if ((D_0019B4A8[((s16)k5 >> 1) + (D_001A79F0 << 10)] & 7) != 7)
                    D_0019B4A8[((s16)k5 >> 1) + (D_001A79F0 << 10)] += 1;
            }
        }
        func_002A6C58(obj, 0, 3);
        func_0029F338(obj);
        return;
    }
    if (*(s32 *)(pv + 0x278) == 1 || *(s32 *)(pv + 0x278) == 5) {
        yaw = *(f32 *)(obj + 0xF8);
        qcopy(v20, pos);
        flags = func_002B1C20(obj, pv + 0x60);
        if (D_L12_001B0B04 * 0.016666668f <= *(f32 *)(pv + 0x218)) {
            func_0026FEB8(D_L12_001B0B38);
            *(f32 *)(pv + 0x218) = 0.0f;
        }
        if (flags & 1) {
            func_002E5CF8(3, 0, obj);
            func_0032C700(pos, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            if (*(s32 *)(pv + 0x2A4) != 0) {
                k1 = *(u16 *)(obj + 0xB2);
                if (k1 & 1) {
                    if (((D_0019B4A8[((s16)k1 >> 1) + (D_001A79F0 << 10)] >> 4) & 7) != 7)
                        D_0019B4A8[((s16)k1 >> 1) + (D_001A79F0 << 10)] += 0x10;
                } else {
                    if ((D_0019B4A8[((s16)k1 >> 1) + (D_001A79F0 << 10)] & 7) != 7)
                        D_0019B4A8[((s16)k1 >> 1) + (D_001A79F0 << 10)] += 1;
                }
            }
            func_002A6C58(obj, 0, 3);
        release:
            func_0029F338(obj);
            return;
        }
        if (flags & 2)
            *(s32 *)(pv + 0x278) = 2;
        qcopy(pos, v20);
        *(f32 *)(obj + 0xF8) = yaw;
    }

    switch (obj[0x95]) {
    case 0:
        if (*(s16 *)(pv + 0x276) == 1 || *(s32 *)(pv + 0x278) == 1 || *(s32 *)(pv + 0x278) == 2) {
            *(s32 *)(pv + 0x26C) = -1;
            *(s32 *)(pv + 0x268) = -1;
            if (*(s32 *)(pv + 0x298) == 0) {
                func_002A7750(obj, 0xF, 5);
            } else {
                func_L12_003E2370(obj);
                if (obj[0x20] != 0xF) {
                    func_002A7750(obj, 4, 0xA);
                    *(s16 *)(pv + 0x29E) = 0x320;
                }
            }
        }
        break;
    case 7:
        n = *(s16 *)(pv + 0x276);
        if (n == 1) {
            func_002A7750(obj, 3, 8);
            obj[0x31] = n;
            *(u16 *)(obj + 0x34) &= 0xFFFE;
        } else {
            obj[0x31] = 0;
            *(u16 *)(obj + 0x34) |= 1;
        }
        break;
    case 9:
        func_002B3890(obj);
        if (obj[0x20] == 0x17 && *(s32 *)(pv + 0x278) != 1) {
            func_002A7750(obj, 4, -1);
            if (obj[0x43] != 3)
                func_002A7470(obj, 3, 0, 0x14);
        }
        if (func_00282978(pv + 0x29E) != 0) {
            func_L12_003E2418(obj);
            func_002A7750(obj, 4, 0xA);
            if (obj[0x43] != 3)
                func_002A7470(obj, 3, 0, 0x14);
        } else if (*(s32 *)(pv + 0x278) == 1 && obj[0x20] == 4) {
            func_002A7750(obj, 0xF, 5);
            *(s16 *)(pv + 0x29C) = 0x96;
        }
        break;
    case 10:
        if (func_002B3890(obj) != 0)
            func_L12_003E1CB0(obj);
        if ((obj[0x60] & 2) && obj[0x42] != 2 && obj[0x43] != 2)
            func_002A7470(obj, 2, 0, 0x14);
        func_L12_003E2370(obj);
        if (*(s32 *)(pv + 0x278) == 1) {
            func_002A7750(obj, 0xF, 5);
            *(s16 *)(pv + 0x29C) = 0x96;
            break;
        }
        if (*(s16 *)(pv + 0x276) == 1 || *(s32 *)(pv + 0x278) != 0)
            *(s16 *)(pv + 0x260) = 0xFA;
        if (*(s16 *)(pv + 0x276) == 0 && *(s32 *)(pv + 0x278) == 0 && func_00282978(pv + 0x260) != 0) {
            if (obj[0x43] != 0)
                func_002A7470(obj, 0, 0, 0x14);
            func_002A7750(obj, 5, 0);
        }
        break;
    case 5:
        if (func_002B3890(obj) != 0) {
            *(f32 *)(pv + 0x198) = D_L12_001B0AB0;
            func_002B60B0(obj, D_L12_001B0AA8 * 0.00027777778f, D_L12_001B0AAC * 0.016666668f, 0.0017453295f, 0.20943955f);
            *(s32 *)(pv + 0x1A8) |= 0x10;
        }
        if (*(s32 *)(pv + 0x278) == 3) {
            if (obj[0x95] != 0xF)
                func_002A7750(obj, obj[0x20], 6);
            func_002B3868(obj);
        }
        if (*(s32 *)(pv + 0x298) != 0 && func_00282978(pv + 0x29C) != 0 && *(s32 *)(pv + 0x278) != 1) {
            func_L12_003E2448(obj);
            break;
        }
        func_0029FC20(obj, 2, v30);
        func_002830C0(v20, D_L12_001B0A90, v30);
        if (obj[0x95] != 0xF && func_002761F8(v20, pv + 0x130, 2, obj, 0) != 0) {
            func_002A7750(obj, obj[0x20], 6);
            func_002B3868(obj);
        }
        if (*(s16 *)(pv + 0x276) == 1 || *(s32 *)(pv + 0x278) != 0)
            *(s16 *)(pv + 0x260) = 0xFA;
        if (*(s16 *)(pv + 0x276) == 0 && *(s32 *)(pv + 0x278) == 0 && func_00282978(pv + 0x260) != 0) {
            if (obj[0x43] != 0)
                func_002A7470(obj, 0, 0, 0x14);
            func_002A7750(obj, 5, 0);
        } else {
            func_002AA800(obj + 0xF8, 0, func_00283248(*(f32 *)(*(u8 **)(pv + 0x270) + 0x10) - *(f32 *)(obj + 0x10), *(f32 *)(*(u8 **)(pv + 0x270) + 0x14) - *(f32 *)(obj + 0x14)), 0.10471977f);
        }
        break;
    case 6:
        if (func_002B3890(obj) != 0) {
            *(s32 *)(pv + 0x26C) = -1;
            path = D_L12_001FEAC0[*(s32 *)(pv + 0x158)];
            func_L12_003E1CB0(obj);
            r = func_00282E48(pos, (u8 *)path + *(s32 *)(pv + 0x264) * 0x10 + 0x10);
            if (r > 0.5f)
                func_0026FEB8(D_L12_001B0B50, func_001234F0(r));
        }
        if (*(s32 *)(pv + 0x16C) != 0) {
            func_L12_003E20F0(obj);
            break;
        }
        path = D_L12_001FEAC0[*(s32 *)(pv + 0x158)];
        /* Retail tests both adjacent waypoint cursors in one 64-bit load. */
        if (*(s64 *)(pv + 0x268) == -1) {
            cur = *(s32 *)(pv + 0x264);
            *(s32 *)(pv + 0x268) = -1;
            lo = cur - 1;
            hi = cur + 1;
            if (lo < 0)
                lo = *path - 1;
            if (hi == *path)
                hi = 0;
            if (lo >= 0 && func_002761F8((u8 *)path + lo * 0x10 + 0x10, pv + 0x130, 2, 0, 0) == 0)
                *(s32 *)(pv + 0x26C) = lo;
            if (*(s32 *)(pv + 0x26C) == -1 && hi < *path) {
                if (func_002761F8((u8 *)path + hi * 0x10 + 0x10, pv + 0x130, 2, 0, 0) == 0)
                    *(s32 *)(pv + 0x26C) = hi;
            }
            if (*(s32 *)(pv + 0x26C) == -1) {
                for (i = lo - 1; i >= 0; i--) {
                    if (func_002761F8((u8 *)path + i * 0x10 + 0x10, pv + 0x130, 2, 0, 0) == 0) {
                        *(s32 *)(pv + 0x26C) = i;
                        break;
                    }
                }
            }
            if (*(s32 *)(pv + 0x26C) == -1) {
                for (i = hi + 1; i < *path; i++) {
                    if (func_002761F8((u8 *)path + i * 0x10 + 0x10, pv + 0x130, 2, 0, 0) == 0) {
                        *(s32 *)(pv + 0x26C) = i;
                        break;
                    }
                }
            }
            if (*(s32 *)(pv + 0x26C) == -1) {
                func_002A7750(obj, obj[0x20], 5);
                func_002B3868(obj);
                break;
            }
            fwd = *(s32 *)(pv + 0x26C) - *(s32 *)(pv + 0x264);
            back = *(s32 *)(pv + 0x264) - *(s32 *)(pv + 0x26C);
            if (fwd < 0)
                fwd = fwd - 1 + *path;
            if (back < 0)
                back = back - 1 + *path;
            if (fwd < back)
                *(s32 *)(pv + 0x268) = *(s32 *)(pv + 0x264) + 1;
            else
                *(s32 *)(pv + 0x268) = *(s32 *)(pv + 0x264) - 1;
            if (*(s32 *)(pv + 0x268) < 0)
                *(s32 *)(pv + 0x268) = *path - 1;
            if (*(s32 *)(pv + 0x268) == *path)
                *(s32 *)(pv + 0x268) = 0;
        }
        func_002AA800(obj + 0xF8, 0, func_00283248(*(f32 *)(*(u8 **)(pv + 0x270) + 0x10) - *(f32 *)(obj + 0x10), *(f32 *)(*(u8 **)(pv + 0x270) + 0x14) - *(f32 *)(obj + 0x14)), 6.0000005f);
        y = *(f32 *)(obj + 0x18);
        *(f32 *)(pv + 0x218) = 0.0f;
        flags = func_L01_00321178(obj, (u8 *)path + *(s32 *)(pv + 0x268) * 0x10 + 0x10);
        ground = func_002A89A8(pos, 0, 0.5f);
        if (flags & 0x20) {
            if (*(s32 *)(pv + 0x248) != 0 && !(D_L12_001B0B14 < *(f32 *)(obj + 0x18) - ground)) {
                if (*(f32 *)(obj + 0x18) < *(f32 *)(pv + 0x2A8))
                    *(f32 *)(obj + 0x18) = *(f32 *)(pv + 0x2A8);
                else
                    func_0026FEB8(D_L12_001B0B18, func_001234F0(*(f32 *)(obj + 0x18) - func_002A89A8(pos, 0, 0.5f)), *(s16 *)(obj + 0xB2));
            } else {
                *(f32 *)(obj + 0x18) = y;
            }
        }
        p = (u8 *)path + *(s32 *)(pv + 0x268) * 0x10;
        if (*(f32 *)(obj + 0x18) < *(f32 *)(p + 0x18) && *(f32 *)(p + 0x18) - *(f32 *)(obj + 0x18) > 0.8f) {
            *(f32 *)(obj + 0x18) += D_L12_001B0A54 * 0.016666668f;
            if (*(f32 *)(obj + 0x18) < ground)
                *(f32 *)(obj + 0x18) = ground;
        }
        p = (u8 *)path + *(s32 *)(pv + 0x268) * 0x10;
        if (*(f32 *)(p + 0x18) < *(f32 *)(obj + 0x18) && *(f32 *)(p + 0x18) - *(f32 *)(obj + 0x18) < -0.8f) {
            *(f32 *)(obj + 0x18) -= D_L12_001B0A54 * 0.016666668f;
            if (*(f32 *)(obj + 0x18) < ground)
                *(f32 *)(obj + 0x18) = ground;
        }
        if (flags & 0x80) {
            nxt = *(s32 *)(pv + 0x268);
            cur = *(s32 *)(pv + 0x26C);
            if (cur == nxt) {
                *(s32 *)(pv + 0x264) = nxt;
                *(s32 *)(pv + 0x268) = -1;
                func_002A7750(obj, obj[0x20], 5);
                func_002B3868(obj);
            } else {
                *(s32 *)(pv + 0x264) = nxt;
                fwd = cur - nxt;
                if (fwd < 0)
                    fwd = fwd - 1 + *path;
                back = nxt - cur;
                if (back < 0)
                    back = back - 1 + *path;
                if (fwd < back)
                    *(s32 *)(pv + 0x268) = nxt + 1;
                else
                    *(s32 *)(pv + 0x268) = nxt - 1;
                if (*(s32 *)(pv + 0x268) < 0)
                    *(s32 *)(pv + 0x268) = *path - 1;
                if (*(s32 *)(pv + 0x268) == *path)
                    *(s32 *)(pv + 0x268) = 0;
            }
        }
        break;
    }

    switch (obj[0x20]) {
    case 5:
        if (func_002B3868(obj) != 0) {
            *(s32 *)(pv + 0x1A8) = (*(s32 *)(pv + 0x1A8) & ~0x10) | 1;
            *(f32 *)(pv + 0x198) = D_L12_001B0AB0 * 0.5f;
            if (obj[0x43] != 0)
                func_002A7470(obj, 0, 0, 0x14);
            *(s16 *)(pv + 0x262) = 0x96;
        }
        if (func_00282978(pv + 0x262) != 0) {
            if (obj[0x43] != 1)
                func_002A7470(obj, 1, 0, 0x14);
            func_002A7750(obj, 0x15, -1);
        }
        break;
    case 3:
        if (func_002B3868(obj) != 0) {
            func_002B60B0(obj, 0.008888889f, 0.53333336f, 0.10471977f, 0.10471977f);
            *(s32 *)(pv + 0x168) = 1;
            *(s32 *)(pv + 0x1A8) = (*(s32 *)(pv + 0x1A8) & ~0x10) | 1;
        }
        if (func_L12_003E1EE8(obj, D_L12_001FEAC0[*(s32 *)(pv + 0x164)]) != 0) {
            func_002A7750(obj, 5, 0);
            if (obj[0x43] != 0)
                func_002A7470(obj, 0, 0, 0);
            *(s32 *)(pv + 0x1A8) |= 0x10;
        }
        break;
    case 21:
        path = D_L12_001FEAC0[*(s32 *)(pv + 0x158)];
        if (func_002B3868(obj) != 0) {
            if (*(s32 *)(pv + 0x264) + 1 != *path)
                *(s32 *)(pv + 0x268) = *(s32 *)(pv + 0x264) + 1;
            else
                *(s32 *)(pv + 0x268) = 0;
            func_L12_003E1CB0(obj);
        }
        if (*(s32 *)(pv + 0x16C) != 0)
            func_L12_003E20F0(obj);
        y = *(f32 *)(obj + 0x18);
        *(f32 *)(pv + 0x218) = 0.0f;
        flags = func_L01_00321178(obj, (u8 *)path + *(s32 *)(pv + 0x268) * 0x10 + 0x10);
        ground = func_002A89A8(pos, 0, 0.5f);
        if (flags & 0x20) {
            if (*(s32 *)(pv + 0x248) != 0 && !(D_L12_001B0B14 < *(f32 *)(obj + 0x18) - ground)) {
                if (*(f32 *)(obj + 0x18) < *(f32 *)(pv + 0x2A8))
                    *(f32 *)(obj + 0x18) = *(f32 *)(pv + 0x2A8);
                else
                    func_0026FEB8(D_L12_001B0B18, func_001234F0(*(f32 *)(obj + 0x18) - func_002A89A8(pos, 0, 0.5f)), *(s16 *)(obj + 0xB2));
            } else {
                *(f32 *)(obj + 0x18) = y;
            }
            r = y < ground ? y : ground;
            if (*(f32 *)(obj + 0x18) < r)
                *(f32 *)(obj + 0x18) = r;
        }
        p = (u8 *)path + *(s32 *)(pv + 0x268) * 0x10;
        if (*(f32 *)(obj + 0x18) < *(f32 *)(p + 0x18) && *(f32 *)(p + 0x18) - *(f32 *)(obj + 0x18) > 0.8f) {
            *(f32 *)(obj + 0x18) += D_L12_001B0A54 * 0.016666668f;
            if (*(f32 *)(obj + 0x18) < ground)
                *(f32 *)(obj + 0x18) = ground;
        }
        p = (u8 *)path + *(s32 *)(pv + 0x268) * 0x10;
        if (*(f32 *)(p + 0x18) < *(f32 *)(obj + 0x18) && *(f32 *)(p + 0x18) - *(f32 *)(obj + 0x18) < -0.8f) {
            *(f32 *)(obj + 0x18) -= D_L12_001B0A54 * 0.016666668f;
            if (*(f32 *)(obj + 0x18) < ground)
                *(f32 *)(obj + 0x18) = ground;
        }
        if (flags & 0x80) {
            *(s16 *)(pv + 0x262) = 0xC8;
            *(s32 *)(pv + 0x264) = *(s32 *)(pv + 0x268);
            if (obj[0x43] != 0)
                func_002A7470(obj, 0, 0, 0x14);
            func_002A7750(obj, 5, -1);
        }
        break;
    case 15:
        if (func_002B3868(obj) != 0) {
            *(s16 *)(pv + 0x262) = 0x28;
            if (obj[0x43] != 8)
                func_002A7470(obj, 8, 0, 0x14);
            func_002B60B0(obj, D_L12_001B0AA8 * 0.000034722223f, D_L12_001B0AAC * 0.0020833334f, 0.10471977f, 0.10471977f);
            *(f32 *)(pv + 0x198) = D_L12_001B0AB0 * 0.25f;
        }
        if (func_00282978(pv + 0x262) != 0 || (dist < 4.0f && *(s16 *)(pv + 0x262) < 0x14)) {
            *(f32 *)(pv + 0x198) = D_L12_001B0AB0;
            func_002B60B0(obj, D_L12_001B0AA8 * 0.00027777778f, D_L12_001B0AAC * 0.016666668f, 0.0017453295f, 0.20943955f);
            if (obj[0x43] != 7)
                func_002A7470(obj, 7, 0, 0x14);
            *(s16 *)(pv + 0x262) = 0x14;
            func_002A7750(obj, 0x10, -1);
            break;
        }
        func_0029FC20(obj, 2, v30);
        func_002830C0(v20, D_L12_001B0A90, v30);
        goto shoot;
    case 16:
        if (func_002B3868(obj) != 0)
            func_002E5CF8(3, 0, obj);
        func_0029FC20(obj, 2, v30);
        func_002830C0(v20, D_L12_001B0A90, v30);
        ang = func_00283248(*(f32 *)(pv + 0x130) - *(f32 *)(obj + 0x10), *(f32 *)(pv + 0x134) - *(f32 *)(obj + 0x14));
        if (func_00282C48(func_00283BE0(*(f32 *)(obj + 0xF8), ang)) > 0.17453294f) {
            func_00282F20(v70, obj + 0xC0, func_00282E80(v20, pos) * 0.016666668f);
            v70[2] = (*(f32 *)(pv + 0x138) - v20[2]) * 0.016666668f;
        }
        if (func_002AEB60(obj, D_L12_001B0A50) == 0) {
        shoot:
            r = func_002A7878(D_L12_001B0A80, D_L12_001B0A84);
            n = func_002A77E0(D_L12_001B0A8C);
            func_002C2210(v20, (int)D_L12_001B0A88, D_L12_001B0A58, 0, n, (float *)D_L12_001A8F20, 0, r * 0.3f, r, 0.0f);
        } else {
            if (func_00282C48(func_00283BE0(*(f32 *)(obj + 0xF8), ang)) > 0.17453294f) {
                func_00282F20(v70, obj + 0xC0, 0.53333336f);
                v70[2] = (*(f32 *)(pv + 0x138) - v20[2] + D_L12_001B0B34) * 0.016666668f;
            } else {
                qcopy(v80, pv + 0x130);
                v80[2] += D_L12_001B0B34;
                func_00282CF0(v70, v80, v20);
                func_00282F20(v70, v70, 0.53333336f);
            }
            r = D_L12_001B0B08 * 0.016666668f;
            if (r < v70[2])
                v70[2] = r;
            else if (v70[2] < -100.0f)
                v70[2] = -100.0f;
            func_L12_00408050(obj, v70, v20, 0, *(s16 *)(pv + 0x34));
            *(s16 *)(pv + 0x262) = 0x32;
            func_002A7750(obj, 0x17, -1);
            break;
        }
        break;
    case 23:
        if (func_00282978(pv + 0x262) != 0)
            func_002A7750(obj, 0xF, -1);
        if (*(s16 *)(pv + 0x262) < 0x1E && obj[0x42] != 3 && obj[0x43] != 3)
            func_002A7470(obj, 3, 0, 0x14);
        if (func_00282E80(pv + 0x130, pos) < 8.0f && *(s16 *)(pv + 0x262) < 0x23) {
            if (obj[0x43] != 7)
                func_002A7470(obj, 7, 0, 0x14);
            func_002A7750(obj, 0x10, -1);
        }
        break;
    case 24:
        if (func_002B3868(obj) != 0 && obj[0x43] != 9)
            func_002A7470(obj, 9, 0, 0x14);
        if (func_002AEB60(obj, 12.5f) != 0)
            *(f32 *)(obj + 0x48) = 0.0f;
        break;
    }
}
