/* func_L11_00453358 (4,524 B, 1 place), 5 November 2026: retained near miss, not linked.
 * USA v1.01 tools/check.py: 4524/4524 bytes, 1131/1131 instructions, 0/1 places. Every
 * instruction and register equals retail except the four spilled pointers' stack slots
 * (pos 0x8C, pv+0x1B0 0x84, self+0xC0 0x88, self+0xF0 0x90; retail 0x84, 0x90, 0x88, 0x8C).
 * Profile: own unit src/levels/11_joba/L11_00453358-state-g8.c, -O2 -G8 -ffunction-sections.
 * This file is that complete unit: the declarations follow the callees' existing contracts
 * in the Joba and Maktar units. Removing the draft's ten dead initializers (d, lim, t, rot,
 * path, p, s, n, dist) leaves every instruction unchanged.
 *
 * Case 9: `height = 0.0f;` (height = case 8's ground height) is the construct the matched twin
 * func_L02_0040BE08 uses in its case 9. Without it, jump2's find_cross_jump merges case 9's
 * func_002A7750(self, 11, -1) tail into case 13's identical (14, -1) tail (-8 bytes); retail
 * keeps both. find_cross_jump stops when the current jump's side reaches a CODE_LABEL, so
 * retail kept a label between that call and the break. It is a dead store: whether it is
 * acceptable needs a ruling (the same one as the twin's), and a natural construct leaving that
 * label would be better.
 *
 * The slots: all four are gcse PRE reaching registers, numbered in expression-hash bucket
 * order, bucket = (14029 + regno + offset) % S, S = (max_cuid / 2) | 1 (self is pseudo 84,
 * pv 85). Retail's order pos < +0xC0 < +0xF0 < pv+0x1B0 is the unwrapped order and needs
 * S in {539, 541, 543} (or 561..565); this source gives S 551. Measured: whole-file
 * -fno-force-mem gives S 541 and exactly retail's four slots, but breaks case 3 (retail's
 * `andi v1,a0,0xFF` needs the forced QI compare) and three FP compares, so it is not
 * retail's profile. Scratch compiler variants (not kept) that skip force_not_mem in
 * extendhisi2 only, or for HImode compares only, move max_cuid by 2 and 4: not the cause.
 * Bucket sweep (scratch cc1 overriding expr_hash_table_size from RAC_S, not kept): this exact
 * unit gives tools/check.py `1 of 1 places match` at S 539, 541, 543, 561, 563 and 565 and at
 * no other odd S in 531..571. Everything but gcse's bucket count is retail's.
 * Second pass, 5 November 2026 (count measured exactly as real insns in the -dF dump; this
 * source has 1095, S 551). Count-neutral, code unchanged: case 11's loop as do-while, case
 * 14's loop as do-while, rot set before the loop, the byte-offset matrix qcopy (all 1095).
 * All ten dead initializers together reach only S 555, so neither window is reachable that
 * way. A `pos = self + 0x10` local (set once, or in each head arm as in func_L11_0044AFC8)
 * lands in the window (1078, S 543) and gives retail's compute-then-copy head, but pos then
 * takes $fp/$s7 instead of retail's slot 0x84; mixing pos and direct `self + 0x10` is worse.
 * So retail's pos is a gcse reaching register. These change code, so they are out: qcopy for
 * the head's or case 14's TI copies, and the `flag` spellings in case 8 (if/else, per arm).
 * Next: find source wording with 13 to 27 fewer insns at gcse (or 17 to 31 more), with
 * unchanged code; candidates are wordings whose redundancy gcse/flow removes later.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 q; } Vec;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

extern char D_00189E20[];
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 D_L11_001B1D40 __attribute__((sda));
extern f32 D_L11_001B1D44;
extern f32 D_L11_001B1D48;
extern u8 *D_L11_001FF580[];

extern int func_002761F8(void *, void *, int, void *, void *);
extern s32 func_00277258(void *, s32, void *, float);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283248(float, float);
extern void func_002833F0(void *, void *);
extern float func_00283B98(float, float);
extern void func_002A677C(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_002A7A00(void *, float, float);
extern void func_002A8C28(void *, void *, int, float, float, float, int, int, int);
extern void func_002A8D70(void *, int, int, float, float, float, int, int, int);
extern float func_002AA150(float, float, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_002AB6D8(void *, void *);
extern int func_002B3868(u8 *);
extern int func_002B3890(u8 *);
extern void func_002B4090(void *, void *, float, float, float);
extern int func_002B4FF0(void *, void *, float);
extern void func_002B60B0(u8 *, float, float, float, float);
extern char *func_002C2210(void *, float, float, int, unsigned int, int, int, void *, float, int);
extern int func_L01_00321178(void *, void *);
extern void func_L02_00333438(void *, void *);
extern void func_L07_00321D68(void *, void *);
extern u8 *func_L11_004417E8(u8 *);
extern int func_L11_00441808(u8 *, void *);
extern void func_L11_00441A38(u8 *, int, int);
extern void func_L11_00454508(u8 *);
extern void func_L11_00454AE0(u8 *);
extern void func_L11_00454DD8(u8 *);

void func_L11_00453358(u8 *self)
{
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
    f32 m[4][4];
    u8 *pv;
    u8 *target;
    f32 dist;
    f32 height;

    pv = *(u8 **)(self + 0x68);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(pv + 0x1FC) != 0 && D_L11_001A8FF4 == 0 && self[0x20] != 0xE && self[0x20] != 0xD)
        return;
    func_L11_00454508(self);
    if (*(u8 **)(pv + 0x1C4) != 0) {
        *(TI128 *)v00 = *(TI128 *)(*(u8 **)(pv + 0x1C4) + 0x10);
        func_00283248(*(f32 *)(*(u8 **)(pv + 0x1C4) + 0x10) - *(f32 *)(self + 0x10),
                      *(f32 *)(*(u8 **)(pv + 0x1C4) + 0x14) - *(f32 *)(self + 0x14));
    } else {
        *(Vec *)v00 = *(Vec *)(D_00189E20 + 0x80);
        func_00283248(((Hero *)D_00189E20)->f[0x80 / 4] - *(f32 *)(self + 0x10),
                      ((Hero *)D_00189E20)->f[0x84 / 4] - *(f32 *)(self + 0x14));
    }
    dist = func_00282E48((self + 0x10), v00);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(pv + 0x1FC) != 0 && D_L11_001A8FF4 == 0)
        return;
    target = 0;
    if (*(s32 *)(self + 0xB8) != 0)
        target = func_L11_004417E8(*(u8 **)(self + 0xB8));

    switch (self[0x20]) {
    case 3: {
        if (func_002B3868(self) != 0) {
            func_002B60B0(self, 0.027777778f, 1.6666667f, 0.001163553f, 0.10471977f);
            self[0xBC] = 0;
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(pv + 0x1EE)) {
            self[0xBC] = 1;
            break;
        }
        if (self[0xBC] == 1) {
            if (func_L11_00441808(*(u8 **)(self + 0xB8), (self + 0x10)) != 0)
                func_002A7750(self, 7, 3);
            func_L01_00321178(self, func_L11_004417E8(*(u8 **)(self + 0xB8)));
        }
        break;
    }
    case 4:
        if (func_002B3868(self) != 0)
            *(u16 *)(self + 0x96) = 0;
        if (*(u16 *)(self + 0x96) < 0x1A)
            break;
        if (self[0x43] != 0)
            func_002A7470(self, 0, 0, 5);
        func_002A7750(self, 8, 3);
        break;
    case 7: {
        u8 *path;
        u8 *p;
        s32 i;
        s32 best;
        f32 d;
        f32 lim;

        if (*(s16 *)(pv + 0x1FC) != 0)
            path = D_L11_001FF580[*(s32 *)(pv + 0x1E0)];
        else
            path = D_L11_001FF580[*(s32 *)(pv + 0x1C0)];
        if (func_002B3868(self) != 0) {
            p = path + 0x10;
            best = 0;
            func_002B60B0(self, 0.027777778f, 3.3333335f, 0.001163553f, 0.10471977f);
            *(f32 *)(pv + 0x1C8) = func_002A7878(1.0f, 3.0f);
            d = func_00282E48((self + 0x10), p);
            for (i = 0; i < *(s32 *)path - 1; i++, p += 0x10) {
                f32 e = func_00282E48((self + 0x10), p);
                if (e < d) {
                    d = e;
                    best = i;
                }
            }
            *(s32 *)(pv + 0x1D4) = best;
            *(s16 *)(pv + 0x1E8) = func_002A77E0(2);
        } else {
            qcopy(v10, path + 0x10 + (*(s32 *)(pv + 0x1D4) << 4));
            if (*(s16 *)(pv + 0x1FC) != 0) {
                func_00282CF0(v30, v10, target);
                v30[2] = 0.0f;
                func_00282F20(v30, v30, 15.0f - *(f32 *)(pv + 0x1C8));
                v10[0] = *(f32 *)(target + 0) + v30[0];
                v10[1] = *(f32 *)(target + 4) + v30[1];
            } else {
                v10[2] = *(f32 *)(pv + 0x1C8) + *(f32 *)(target + 8);
            }
            func_00282CF0(v20, v10, (self + 0x10));
            lim = 2.0f;
            func_00282F20(v20, v20, *(f32 *)(pv + 0x1D8));
            func_00282CC0((self + 0x10), (self + 0x10), v20);
            if (*(s16 *)(pv + 0x1FC) != 0)
                lim = 4.0f;
            if (*(s16 *)(pv + 0x1E8) != 0) {
                if (func_00282E48((self + 0x10), v10) < lim)
                    *(s32 *)(pv + 0x1D4) -= 1;
                if (*(s32 *)(pv + 0x1D4) < 0)
                    *(s32 *)(pv + 0x1D4) = *(s32 *)path - 1;
            } else {
                if (func_00282E48((self + 0x10), v10) < lim)
                    *(s32 *)(pv + 0x1D4) += 1;
                if (*(s32 *)(pv + 0x1D4) >= *(s32 *)path)
                    *(s32 *)(pv + 0x1D4) = 0;
            }
            if (*(s32 *)(pv + 0x1D4) >= *(s32 *)path - 6 && *(f32 *)(pv + 0x1D8) >= 0.10000001f)
                *(f32 *)(pv + 0x1D8) = *(f32 *)(pv + 0x1D8) - 0.0025f;
            func_002A677C(self);
            if (*(s16 *)(pv + 0x1FC) != 0) {
                func_L02_00333438(self, v10);
            } else {
                func_002B4FF0(self, v10, *(f32 *)(pv + 0x1D0));
                func_002AA548(self + 0x18, pv + 0x108, *(f32 *)(pv + 0x1C8), 0.00055555557f, 0.00055555557f,
                              0.16666667f);
            }
        }
        if (*(s16 *)(pv + 0x1EC) != 0)
            func_002A7750(self, 8, 3);
        break;
    }
    case 8: {
        s32 flag;
        if (func_002B3868(self) != 0)
            func_002B60B0(self, 0.011111111f, 1.3333334f, 0.001163553f, 0.10471977f);
        flag = 0;
        if (*(s16 *)(pv + 0x1FC) != 0) {
            if (4.0f < dist) {
                func_00282CF0(v10, v00, (self + 0x10));
                func_00282F20(v10, v10, 10.0f);
                func_00282CC0(v10, v10, (self + 0x10));
                func_L02_00333438(self, v10);
            } else {
                func_L02_00333438(self, v00);
            }
            flag = dist < 4.0f;
        } else {
            height = *(f32 *)(target + 8) + 0.5f;
            func_002AA548(self + 0x18, pv + 0x108, height, 0.0055555557f, 0.027777778f, 0.16666667f);
            func_002B4FF0(self, v00, *(f32 *)(pv + 0x1D0));
            if (func_00282C48(*(f32 *)(self + 0x18) - height) < 0.1f &&
                func_00282E80((self + 0x10), &((Hero *)D_00189E20)->q[0x80 / 16]) < 2.0f)
                flag = 1;
        }
        if (flag) {
            *(u16 *)(self + 0x96) = 0;
            func_002A7750(self, 10, -1);
        }
        func_002A8C28(self, (self + 0x10), 1, 0.3f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        break;
    }
    case 9:
        if (func_002B3868(self) != 0 && self[0x43] != 2)
            func_002A7470(self, 2, 0, 3);
        if (self[0x60] & 2) {
            if (self[0x43] != 3)
                func_002A7470(self, 3, 0, 5);
            func_002A7750(self, 11, -1);
        }
        height = 0.0f;
        break;
    case 11: {
        s32 k;
        f32 lim;
        if (func_002B3890(self) != 0) {
            func_002B60B0(self, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            *(u16 *)(self + 0x96) = 0;
        }
        *(f32 *)(self + 0x48) = 1.75f;
        for (k = 0; k < 4; k++)
            func_002A8D70(self, k, 1, 0.5f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        lim = 1.8f;
        if (lim <= func_00282E48((self + 0x10), &((Hero *)D_00189E20)->q[0x80 / 16])) {
            qcopy(v10, v00);
        } else if (func_00282E48((self + 0x10), &((Hero *)D_00189E20)->q[0x80 / 16]) < lim) {
            func_00282CF0(v10, (self + 0x10), v00);
            func_00282F20(v10, v10, 2.0f);
            func_00282CC0(v10, v10, (self + 0x10));
        } else {
            qcopy(v10, (self + 0x10));
        }
        if (*(s16 *)(pv + 0x1FC) != 0) {
            func_L02_00333438(self, v10);
        } else {
            func_002AA548(self + 0x18, pv + 0x108, *(f32 *)(target + 8) + 0.5f, 0.0055555557f, 0.027777778f,
                          0.16666667f);
            func_L01_00321178(self, v10);
        }
        if (((Hero *)D_00189E20)->ptr[0x249C / 4] == self) {
            func_002A7750(self, 12, -1);
            if (self[0x43] != 4)
                func_002A7470(self, 4, 0, 5);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        if (func_00282E48((self + 0x10), &((Hero *)D_00189E20)->q[0x80 / 16]) > 4.0f && *(u16 *)(self + 0x96) >= 0x79) {
            if (self[0x43] != 5)
                func_002A7470(self, 5, 0, 15);
            func_002A7750(self, 4, -1);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        break;
    }
    case 12:
        if (!(self[0x60] & 2))
            break;
        if (self[0x43] != 0)
            func_002A7470(self, 0, 0, 15);
        func_002A7750(self, 8, -1);
        break;
    case 10:
        if (*(u16 *)(self + 0x96) >= 0xF) {
            func_002A7750(self, 9, -1);
            if (self[0x43] != 2)
                func_002A7470(self, 2, 0, 2);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        qcopy(v10, (self + 0x10));
        if (dist < 1.0f)
            func_002A8C28(self, v10, 1, 0.3f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        break;
    case 13:
        qcopy_nc(v10, (self + 0x10));
        *(f32 *)(pv + 0x108) = *(f32 *)(pv + 0x108) - *(f32 *)(pv + 0x8C);
        func_00282CC0((self + 0x10), (self + 0x10), pv + 0x100);
        if (func_002761F8(v10, (self + 0x10), 0, self, 0) == 0 && func_00277258((self + 0x10), 4, self, 0.3f) == 0 &&
            func_002A77E0(0x1E) != 0)
            break;
        func_002A8C28(self, (self + 0x10), 0x10000, 0.5f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        if (*(f32 *)(pv + 0x20) > 0.0f) {
            func_002A7750(self, 8, 3);
            if (self[0x43] != 0)
                func_002A7470(self, 0, 0, 5);
        } else if (*(s16 *)(pv + 0x1FC) != 0 && func_002A77E0(2) == 0) {
            func_002A7750(self, 14, -1);
        } else {
            func_L11_00441A38(self, 0, 1);
            func_L11_00454DD8(self);
        }
        break;
    case 14: {
        s32 j;
        u8 *t;
        f32 *rot;
        if (func_002B3868(self) != 0) {
            t = func_L11_004417E8(*(u8 **)(self + 0xB8));
            func_00282CF0(pv + 0x100, t, (self + 0x10));
            *(f32 *)(pv + 0x108) = 0.0f;
            func_00282F20(pv + 0x100, pv + 0x100, func_002A7878(3.0f, 5.0f) * 0.016666668f);
            *(s16 *)(pv + 0x1FC) = 0;
            for (j = 0; j < 3; j++) {
                rot = (f32 *)(pv + 0x1B0);
                rot[j] = func_002A7878(240.0f, 720.0f) * 0.00029088825f;
                qcopy(m[j], self + 0xC0 + j * 0x10);
            }
            func_002AB6D8(m, self + 0xF0);
            *(u16 *)(self + 0x34) &= 0xEFFF;
        }
        *(f32 *)(pv + 0x108) = *(f32 *)(pv + 0x108) - *(f32 *)(pv + 0x8C);
        func_L07_00321D68(self, pv + 0x100);
        func_00282D30(pv + 0x1B0, pv + 0x1B0, 0.98f);
        *(TI128 *)v20 = 0;
        v20[2] = *(f32 *)(pv + 0x30);
        *(TI128 *)v10 = *(TI128 *)v20;
        func_002B4090(self, v10, *(f32 *)(pv + 0x1B0), *(f32 *)(pv + 0x1B4), *(f32 *)(pv + 0x1B8));
        func_002833F0(self + 0xC0, self + 0xF0);
        t = func_L11_004417E8(*(u8 **)(self + 0xB8));
        if (*(f32 *)(self + 0x18) < *(f32 *)(t + 8) + 5.0f || func_002A77E0(0x1C2) == 0 ||
            *(u16 *)(self + 0x96) >= 0x12D) {
            func_L11_00441A38(self, 0, -1);
            func_L11_00454DD8(self);
        }
        break;
    }
    }

    if (*(s16 *)(pv + 0x1FC) != 0 && self[0x95] != 4) {
        f32 z = *(f32 *)(self + 0x18);
        func_00282CF0(v10, (self + 0x10), target);
        v10[2] = 0.0f;
        func_00282F20(v10, v10, 14.3f);
        func_00282CC0((self + 0x10), v10, target);
        *(f32 *)(self + 0x18) = z;
    }
    if (self[0x20] != 0xE) {
        *(f32 *)(pv + 0x1B0) = func_002AA150(*(f32 *)(pv + 0x1B0), D_L11_001B1D40 * 0.00029088825f, 0.0625f);
        *(f32 *)(pv + 0x1B4) = func_002AA150(*(f32 *)(pv + 0x1B4), D_L11_001B1D44 * 0.00029088825f, 0.0625f);
        *(f32 *)(pv + 0x1B8) = func_002AA150(*(f32 *)(pv + 0x1B8), D_L11_001B1D48 * 0.00029088825f, 0.0625f);
        *(f32 *)(self + 0xF0) = func_00283B98(*(f32 *)(self + 0xF0), *(f32 *)(pv + 0x1B0));
        *(f32 *)(self + 0xF4) = func_00283B98(*(f32 *)(self + 0xF4), *(f32 *)(pv + 0x1B4));
        *(f32 *)(self + 0xF8) = func_00283B98(*(f32 *)(self + 0xF8), *(f32 *)(pv + 0x1B8));
    }
    if (target != 0 && *(s16 *)(pv + 0x1FC) == 0 && *(f32 *)(self + 0x18) <= *(f32 *)(target + 8) + 0.4f) {
        if (self[0x31] == 0) {
            *(f32 *)(pv + 0x108) = 0.016666668f;
            *(f32 *)(self + 0x18) = *(f32 *)(target + 8) + 0.3f;
        } else if (func_00277258((self + 0x10), 6, 0, 0.3f) != 0) {
            f32 s;
            s32 n;
            *(f32 *)(pv + 0x108) = 0.016666668f;
            *(f32 *)(self + 0x18) = *(f32 *)(target + 8) + 0.3f;
            v10[0] = *(f32 *)(self + 0x10) + func_002A7878(-0.01f, 0.01f);
            v10[1] = *(f32 *)(self + 0x14) + func_002A7878(-0.01f, 0.01f);
            v10[2] = *(f32 *)(self + 0x18) - 0.3f;
            s = func_002A7878(0.3f, 0.8f);
            n = func_002A77E0(2);
            if (n == 0)
                n--;
            func_002A7A00(v20, 0.0008333334f, 0.050000004f);
            v20[2] = func_002A7878(1.0f, 5.0f) * 0.016666668f;
            func_002C2210(v10, s * 0.1f, s, 0x3C, 0x7F007F7F, 0, n, v20, 0.002f, 0);
        }
    }
    func_002A8C28(self, (self + 0x10), 0x4000000, 0.8f, 5.0f, 1.0f, 0, 1, 0);
    func_L11_00454AE0(self);
}
