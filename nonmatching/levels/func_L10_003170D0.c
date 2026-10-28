/* func_L10_003170D0 - 496 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L10_003170D0 (496 B, 1 place). Mine is 492 B. Needs a new file
   `L10_003170D0-g64.c` with `-O2 -G64 -Wa,-G64 -ffunction-sections` (the
   4-vector table at 0x1A93E0 is addressed `addiu $s2,$gp,-0x5C10`; a 64-byte
   sda table needs -G64), plus `#include "common.h"`; D_001A79F0 as `extern
   int D_001A79F0[] __attribute__((sda))` read as [0] gives the absolute
   lui/lw.
   Structure matches retail (struct view of D_L10_001BD380 gives `addiu
   $v0,$s5,-0x2C80` form). Remaining diffs:
    - retail has a `nop` before the loop head in the object search loop (after
   `b ; daddu $a2,$a0,$zero`); mine none (-g does not add it)
    - retail computes `sll $s7,$a3,2` (idx*4) right after the `sw
   $v0,0x50($a0)` and keeps `lui $s6,0x1C` (hi of D_L10_001B9680) in a saved
   register; mine computes both later / as $s7 lui
   Tried: lo/hi/idx init after the gate (fixed prologue order), nested ifs
   with a single clear at the end (fixed the three branches to the clear), -g. */

typedef struct {
    u8 pad00[0x30];
    int mode;
    int f34;
    u8 pad38[0x44 - 0x38];
    short count;
    u8 pad46[0x50 - 0x46];
    u8 *target;
    u8 pad54[0x18C - 0x54];
    u8 *objs[1];
} G_L10_001BD380;
extern G_L10_001BD380 D_L10_001BD380;
extern f32 D_L10_001A93E0[16] __attribute__((sda));
extern f32 D_L10_00296EB0[];
extern u8 D_L10_00296E90[];
extern f32 D_L10_001B9680[];
extern int D_001A79F0[] __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);

void func_L10_003170D0(void) {
    f32 tmp[4] __attribute__((aligned(16)));
    int lo;
    int hi;
    int idx;
    int i;
    int j;
    u8 *obj;
    f32 *out;
    f32 *tbl;

    if (D_001A79F0[0] != 10) {
        return;
    }
    lo = -1;
    hi = 0x270F;
    idx = 0;
    if (D_L10_001BD380.mode == 1) {
        lo = 1;
        hi = 0x4D8;
    } else if (D_L10_001BD380.mode == 2) {
        lo = 1;
        hi = 0x190;
        idx = 3;
    }
    if (lo != -1 && D_L10_001BD380.f34 >= lo && D_L10_001BD380.f34 <= hi) {
        D_L10_001BD380.target = D_L10_00296E90;
        obj = 0;
        for (i = 0; i < D_L10_001BD380.count; i++) {
            if (*(short *)(D_L10_001BD380.objs[i] + 0xAA) == 0xD54) {
                obj = D_L10_001BD380.objs[i];
                break;
            }
        }
        if (obj != 0) {
        out = D_L10_00296EB0;
        tbl = D_L10_001A93E0;
        for (j = 3; j >= 0; j--) {
            func_00283098(out, tbl, obj + 0xC0);
            tbl += 4;
            func_00282CC0(out, out, obj + 0x10);
            func_00282CF0(tmp, D_L10_001B9680, out);
            func_00282F20(tmp, tmp, 0.15f);
            func_00282CC0(out, out, tmp);
            out += 4;
        }
            *(u8 **)(D_L10_001BD380.target + 0x68) = D_L10_001BD380.objs[idx];
            return;
        }
    }
    D_L10_001BD380.target = 0;
}
