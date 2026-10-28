/* func_L09_003F9708 - 544 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   New file L09_003F9708-g8.c, flags `-O2 -G8 -ffunction-sections` (gp floats
   D_L09_001B0F2C/28, int D_L09_001B0F40; gp = 0x1AEFF0). 524 B vs 544 B, ~100
   diff lines. WARNING: coord/d.sh hides every hex immediate; use check.py's
   own "N of M places match".
   Left: (1) retail loads the 1/60 constant (lui/ori/mtc1) at each of the two
   func_00282F20 calls; draft's gcse hoists it into $f20 (frame 0x60 vs 0x50).
   (2) retail: both `status == 0xFE` and `== 0xFD` branch to one block at the
   end (single `lhu/sh 0x2E4`); the draft duplicates it. `a || b` on the same
   expression folds to a range test ((x+3)&0xFF < 2), the draft avoids that
   with `part->status == 0xFE || (*pp)->status == 0xFD`.
   (3) register numbers: retail state=$s1, odd=$s0, near=$s4, vec copy=$s3.
   (4) `&d->parts[odd]`: retail `addiu v0,s1,0x2F0; addu a0,v0,v1(odd*4)`;
   draft `sll;addiu;addu s0`. */

#include "include_asm.h"
#include "common.h"

extern f32 D_L09_001B0F2C __attribute__((sda));
extern f32 D_L09_001B0F28 __attribute__((sda));
extern s32 D_L09_001B0F40 __attribute__((sda));

extern f32 func_00282E80(void *a0, void *a1);
extern s32 func_00282978(void *a0);
extern s32 func_L09_003F9568(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_0029FCC0(void *a0, s32 a1, void *a2);
extern void func_00282CF0(void *a0, void *a1, void *a2);
extern void func_00282F20(void *a0, void *a1, f32 a2);
extern s32 func_002E5CF8(s32 a0, s32 a1, void *a2);
extern void func_L09_003A06B0(u8 *a0, void *a1, void *a2, f32 f12);

typedef struct L09Obj L09Obj;

typedef struct {
    u8 gap0[0x34];
    u8 f34;
    u8 gap35[0x1BB];
    f32 vec1F0[4];
    u8 *f200;
    u8 gap204[0xE0];
    u16 f2E4;
    u8 gap2E6[0xA];
    L09Obj *parts[2];
    L09Obj *parent;
    u8 gap300[0x11];
    u8 f30D;
} L09Desc;

struct L09Obj {
    u8 gap0[0x10];
    f32 pos[4];
    u8 status;
    u8 gap21[0x75];
    u16 f96;
    u8 gap98[0x12];
    short class_code;
    u8 gapAC[0x4];
    u8 gapB0[0x1];
};

void func_L09_003F9708(u8 *self)
{
    L09Desc *d = *(L09Desc **)(self + 0x68);
    s32 near;
    f32 v0[4];
    f32 v10[4];
    L09Obj **pp;
    L09Obj *part;
    s32 odd;
    s32 bit;
    u8 *vec;

    near = func_00282E80(self + 0x10, d->f200 + 0x10) < D_L09_001B0F2C;
    if (d->parent == 0)
        return;
    if (func_00282978(&d->f2E4) == 0)
        return;
    odd = (*(u16 *)(self + 0x96) / D_L09_001B0F40) & 1;
    bit = odd ? 5 : 4;
    if (!((*(u16 *)((u8 *)d->parent + 0x7C) >> bit) & 1))
        return;
    if (func_L09_003F9568(self, 1, 0, d->f30D != 0) == 0)
        return;
    pp = &d->parts[odd];
    part = *pp;
    if (part == 0)
        return;
    if (part->class_code != 0xD66)
        return;
    if (part->status == 0xFE || (*pp)->status == 0xFD) {
        d->f2E4 = D_L09_001B0F40;
    } else {
        d->f2E4 = D_L09_001B0F40;
        func_0029FCC0(*pp, 0, v0);
        vec = (u8 *)v10;
        func_00282CF0(vec, d->vec1F0, v0);
        func_00282F20(vec, vec, D_L09_001B0F28 * 0.016666668f);
        if (near == 0 && d->f30D == 0) {
            if (v10[2] > 0.033333335f)
                v10[2] = 0.033333335f;
            if (v10[2] < -0.033333335f)
                v10[2] = -0.033333335f;
            func_00282F20(vec, vec, D_L09_001B0F28 * 0.016666668f);
        }
        func_002E5CF8(1, 0, d->parent);
        func_L09_003A06B0(self, vec, v0, (f32)d->f34);
    }
}
