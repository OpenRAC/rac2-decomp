/* func_L01_003D8AD0 - 304 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c: 300 B vs 304 (plus 2 insns). Remaining diffs (check --diff): a0
   copy lands in $a3 and b in $a2 (retail: a2 / a3);
   retail has `andi $a1,$a3,0xFF` before the index (draft gets that with s32 b
   and (u8)b casts) and `beqz ..; nop` before the last
   `lh/lui/addiu/sb` (draft fills the delay slot with lui). Tried:
   u8/u32/int/s32 b, addr calc inside each odd/even branch (needed, matches
   retail order). */

#include "common.h"
/* needs: src/levels/01_oozla/L01_003CAFE0.c includes common.h (its own u8..f32 typedefs removed) */
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 D_L01_001B23A0[];
typedef struct { u8 pad[0x464]; u8 slot[1]; } L01_SlotTable;
extern L01_SlotTable D_L01_0021D840;
extern L01_SlotTable D_L01_0021E4B0;

/* Counts the visit of the entity in the saved per-slot byte (a saturating 3-bit counter in the
   low or high nibble, by the odd bit of +0xB2), then records its kind in the slot tables. */
void func_L01_003D8AD0(u8 *a0)
{
    u8 *e;
    s32 b;

    if (a0[0xB0] != 0xFF && (*(short *)(a0 + 0xB2) >= 0) && !(a0[0xB1] & 0x80)) {
        if (*(u16 *)(a0 + 0xB2) & 1) {
            e = &D_0019B4A8[(*(short *)(a0 + 0xB2) >> 1) + D_001A79F0 * 0x400];
            if (((*e >> 4) & 7) != 7)
                *e += 0x10;
        } else {
            e = &D_0019B4A8[(*(short *)(a0 + 0xB2) >> 1) + D_001A79F0 * 0x400];
            if ((*e & 7) != 7)
                *e += 1;
        }
        D_L01_0021D840.slot[*(short *)(a0 + 0xB2)] = a0[0xB0] + 2;
        b = a0[0xB0];
        if (b != 0xFF && !(D_L01_001B23A0[(u8)b] & 0x80) && (D_0019B2E8[(u8)b + D_001A79F0 * 16] & 0x80))
            D_L01_0021E4B0.slot[*(short *)(a0 + 0xB2)] = b + 2;
    }
}
