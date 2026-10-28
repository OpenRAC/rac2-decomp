/* func_L01_003D25B8 - 260 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs new file L01_003D25B8-g8.c, flags `-O2 -G8 -ffunction-sections`
   (scalar f32 sda D_L01_001B0540 = gp+0x1550; gp=0x1AEFF0). 11 masked diff
   lines in draft.c:
   - retail: lwc1 $f1,0x1550($gp) BEFORE lw $v0,0x24($s0) (mine after, or
   f0/f1 swapped with D*x)
   - retail: sll/addiu -1/addu $t0,$t0,$v0 (q reg updated in place), lw
   0x10($t0) before sh 0x7E; mine addu $v0,$v0,$t0, sh before lw
   - stores of 0x74 before 0x7E change p/q to t0/t1 (worse). Tried: local
   scale, D*x, moving float stmt, q/p decl order. */

#include "common.h"

extern u8 *func_305EE8(u32 a0);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_308938(void *a0);
extern void func_314D00(void *a0);
extern f32 D_L01_001B0540 __attribute__((sda));

/* Spawns the object a3 names and starts it with the vectors a1 and a2. */
u8 *func_L01_003D25B8(u8 *a0, void *a1, void *a2, u32 a3, s32 idx)
{
    u8 *s0 = func_305EE8(a3);
    u8 *p;
    u8 *q;

    if (s0 != 0) {
        q = *(u8 **)(a0 + 0x68);
        p = *(u8 **)(s0 + 0x68);
        s0[0x31] = 1;
        s0[0x30] = 0xFF;
        *(u16 *)(s0 + 0x32) = 0xFF;
        s0[0x20] = 0;
        s0[0xBC] = 0;
        *(u8 **)(p + 0x70) = a0;
        *(u16 *)(p + 0x7C) = idx;
        *(f32 *)(s0 + 0x2C) = *(f32 *)(*(u8 **)(s0 + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(s0 + 0x10, a1);
        qcopy(s0 + 0xF0, a2);
        qcopy(p + 0x60, a1);
        *(s32 *)(p + 0x74) = *(s32 *)(q + idx * 4 + 0x10);
        *(s16 *)(p + 0x7E) = -1;
        *(s32 *)(p + 0x78) = 0;
        func_355780(2, 0, s0);
        func_308938(s0);
        func_314D00(s0);
    }
    return s0;
}
