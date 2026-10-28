/* func_L17_003C7260 - 564 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L17_003C7260-g8.c (-G8), marker removal in
   L17_0032C070.c needed. 560 vs 564 bytes. Logic decoded; frame 0x80 matches
   (saved[4], a[4], b[12] aligned(16) locals; Quad copy through the array).
   Remaining: retail fills the delay slot of `beq st[0x90],-1` with the gp
   form `lw v0,0x3758($gp)` (macro load of D_001B2748 copied from the join
   target; target label is the insn after it), mine fills it from the fall-
   through (`daddu a0,s4`) and
   keeps `lui;lw D` at the join. Also saved-reg save order (s4 saved before
   s0). Tried: D_001B2748[] sda incomplete array, nesting the 3C70E0 call
   inside the st[0x90] != -1 block (this is right), proto order of
   func_002A89A8. */

#include "common.h"

extern float func_002A89A8(float, void *, int);
extern int func_L17_003C70E0(void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A8C00(void *, u8 *, s32, void *, float);
extern void func_002A8E20(s32, void *);
extern float func_00282E48(void *, void *);
extern s32 func_L03_003268C0(void *, s32, s32, s32, s32, s32, s32, void *);
extern void func_002E5CF8(int, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float D_L17_001B0380 __attribute__((sda));
extern float D_L17_001B0390 __attribute__((sda));
extern s32 D_001B2748[] __attribute__((sda));
extern s32 D_001C0018;
extern s32 D_0018C0B0;
extern u8 D_00189EA0[];
extern u8 D_L17_001A8F20[];

void func_L17_003C7260(u8 *obj) {
    typedef unsigned int Quad __attribute__((mode(TI)));
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *pos = obj + 0x10;
    f32 saved[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16)));
    f32 b[12] __attribute__((aligned(16)));
    f32 f;

    if (*(s32 *)(st + 0xAC) == 1) {
        return;
    }
    *(Quad *)saved = *(Quad *)(obj + 0x10);
    if (obj[0x20] == 0) {
        if (*(s32 *)(st + 0x90) != -1) {
            f = func_002A89A8(0.5f, pos, 0);
            *(s32 *)(st + 0x9C) = D_001C0018;
            if (f < *(f32 *)(obj + 0x18)) {
                *(f32 *)(st + 0x98) = *(f32 *)(st + 0x98) + D_L17_001B0390 * 0.00027777778f;
                *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x18) - *(f32 *)(st + 0x98);
            } else {
                *(s32 *)(st + 0x98) = 0;
                *(f32 *)(obj + 0x18) = f;
            }
            if (func_L17_003C70E0(obj) != 0) {
                func_00283098(a, &D_L17_001B0380, obj + 0xC0);
                func_002A8C00(b, obj, 0x10001, a, 2.0f);
                func_002A8E20(D_0018C0B0, b);
            }
        }
    }
    if (D_001B2748[0] >= 0x1F) {
        if (*(s32 *)(st + 0xA4) == 0 && *(s32 *)(st + 0xA8) >= 0x33 && func_00282E48(pos, D_00189EA0) < 15.0f
            && obj[0x20] == 0) {
            func_L03_003268C0(obj, 0x931, 0, 0x931, 4, 6, 0, D_L17_001A8F20);
            func_002E5CF8(0, 0, obj);
            *(u16 *)(obj + 0x34) |= 0x41;
            obj[0x20] = 1;
            *(s32 *)(obj + 0x98) = 0;
            return;
        }
        if (*(s32 *)(st + 0xA4) == 0) {
            *(s32 *)(st + 0xA8) += 1;
        } else {
            *(s32 *)(st + 0xA4) = 0;
            *(s32 *)(st + 0xA8) = 0;
        }
    }
    func_00282CF0(a, pos, saved);
    func_002AD6F0(st + 0x50, a, obj + 0xF0, obj + 0xF0);
}
