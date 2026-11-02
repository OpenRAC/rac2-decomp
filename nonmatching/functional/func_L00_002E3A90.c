/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* OF2 (2026-10-26): the draft below (own unit, "-O2 -G0 -ffunction-sections
   -mno-split-addresses") is 164/164 bytes with the loop exact; only the head differs.
   Retail shares one `return 0` block for all three tests and places it after the a-test:
   `bnez flag -> R ; (a2 = b) ; bnez a<21 -> L ; R: jr ra ; v0 = 0 ; 3 nops ; L: beqz b<16 -> R`.
   Here the flag test keeps its own block (beqz flag over it). Every other spelling tried
   (one || chain, flag||a then b, three ifs, nested flag ifs, with and without the `c = b`
   copy, address association and 2-D array forms) merges the returns and threads the
   b test, giving 148 or 156 bytes. Only `int c = b;` plus a separate flag test keeps 164. */
/* flags: -O2 -G0 -ffunction-sections -mno-split-addresses (own unit src/levels/shared/L00_002E3A90.c) */
#include "include_asm.h"
extern unsigned char D_L00_001A7A0A;
extern unsigned char D_L00_0025EDE0[];
extern int D_L00_001A24A8[];

int func_L00_002E3A90(int a, int b)
{
    unsigned char *p;
    int sum;
    int n;
    int c = b;

    if (D_L00_001A7A0A != 0)
        return 0;
    if (a >= 0x15 || c >= 0x10)
        return 0;
    p = D_L00_0025EDE0 + c * 0x28 + a * 0x280;
    sum = 0;
    for (n = 9; n >= 0; n--) {
        sum += *(short *)(p + 2) * *(int *)((char *)D_L00_001A24A8 + p[1] * 4 + p[0] * 64);
        p += 4;
    }
    return sum;
}

#if 0
/* Not C in its present form: the accumulate block from +0x54 to +0x94 is R5900/MMI-class.
 * The first ten instructions are ordinary C (a flag load and two bound tests over the
 * arguments), and the tail is an ordinary nine-iteration walk over four-byte records; but the
 * block itself carries three-operand `mult` words (0x00C31818, 0x00852818), `mtlo $zero`
 * (0x00000013), `mflo`, and the word 0x70820000 that rabbitizer prints `.word # INVALID`
 * (opcode 0x1C, MMI-class), so no plain-C spelling reaches the bytes.
 *
 * What would unblock it: ASM_FUNC for the whole row, or a C spelling for the MMI accumulate
 * that no source form of this cc1 emitted so far.
 */

#endif
