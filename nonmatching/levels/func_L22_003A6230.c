/* func_L22_003A6230 - 576 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs a -G8 -g file (retail: `lw $v0,0x314($gp)` outside a delay slot, nop
   nop before div.s): `-O2 -G8 -ffunction-sections -g`; D_001AF304 scalar
   `__attribute__((sda))`, D_L22_001B1C48 incomplete array (abs). 564 vs 576
   bytes.
   Left: retail keeps `lui $s2,0x19` (hi of D_00189E20) in a saved reg, builds
   G=`addiu $v0,$v0,-0x61E0` and loads 0x1874($v0) (base not folded into the
   load offset); the draft folds the offset into the load reloc. A local `u8
   *g = D_00189E20` puts the full address in $s2 instead (also wrong). Float
   mul operand order also differs (f21 = f1*f3 retail). */

#include "include_asm.h"
#include "common.h"

extern void func_L22_003A64E8(u8 *a0, int a1, int a2);
extern void func_L22_003A6470(u8 *a0, int a1);

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_001A63A8[];
extern int D_001AF304 __attribute__((sda));
extern int D_L22_001B1C48[];
extern f32 func_00282EB0(void *a0, void *a1);
extern int func_00282948(void *a0);
extern int func_002A77E0(int a0);
extern void func_002B6D28(void);

void func_L22_003A6230(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    f32 f21 = (f32)*(int *)(D_00189E20 + 0x1874) * 0.00083333335f;
    f32 f20 = *(f32 *)(state + 0x20) / (f32)*(short *)(state + 0x24);

    if (D_001AF304 != 0)
        return;
    if (D_L22_001B1C48[0] != 0) {
        if (!(*(unsigned int *)(state + 0x4E0) & 0x01000000)) {
            *(unsigned int *)(state + 0x4E0) |= 0x01000000;
            func_L22_003A64E8(a0, 0, 2);
        }
    }
    if (*(int *)(state + 0x344) != 0 && !(*(unsigned int *)(state + 0x4E0) & 0x00800000))
        func_L22_003A6470(a0, 0x17);
    if (*(int *)(D_00189E20 + 0x1874) == 0)
        func_L22_003A64E8(a0, 0x14, 0x16);
    if (f20 < 0.25f && !(*(unsigned int *)(state + 0x4E0) & 0x80))
        func_L22_003A6470(a0, 7);
    if (0.02f < f20 && 0.04f < f21) {
        if (func_00282948(state + 0x4E4) != 0 && a0[0x31] != 0 &&
            func_00282EB0(a0 + 0x10, D_00189EA0) < 1600.0f)
            func_L22_003A64E8(a0, 3, 6);
        if (*(int *)(D_00189E20 + 0x229C) == 7 && *(int *)(D_00189E20 + 0x1B8) == 0 &&
            func_002A77E0(2) == 0)
            func_L22_003A64E8(a0, 8, 0xC);
    }
    if (*(short *)(D_001A63A8 + 0x72) == 3 && *(short *)(D_001A63A8 + 0x6C) < 0x1770)
        func_002B6D28();
}
