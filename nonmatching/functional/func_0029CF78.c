/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_0029CF78: near miss (worker 5, 22 October 2026).
 *
 * The body is a spin loop on the hardware register at 0x1000D400 (in the retail's
 * .vutext segment), waiting for bit 0x100 to clear:
 *
 *   lui   $at,0x1000 ; ori $at,$at,0xD400
 *   loop: lw   $v0,0($at)
 *         nop
 *         nop
 *         nop
 *         andi $v0,$v0,0x100
 *         nop
 *         beqz $v0,exit
 *         nop
 *         j    loop
 *         nop
 *   exit: jr   $ra
 *         nop
 *
 * The three nops after the load come from the volatile read: the matched
 * func_00130DB8 (src/core/00130DB8.c, "while (*(volatile s32 *)0x10002010 < 0) {}")
 * has the same shape, four nops between the load and the branch that reads it.
 * A volatile read is therefore the right spelling, and this attempt uses it.
 *
 * Measured (tools/check.py func_0029CF78 --diff, 28 places): 44 bytes against the
 * retail's 56.  What differs:
 *   - the nops sit after the "andi" here and before it in the retail;
 *   - the compiler ends the loop with "bne $2,$0,loop" and the exit inline, the
 *     retail branches to an exit block that follows the loop and jumps back with
 *     an unconditional "j";
 *   - the address is materialised in $v1 here and in $at in the retail.
 *
 * What was tried: nine spellings - "while (*(volatile u32 *)0x1000D400 & 0x100) {}",
 * the same with a "return 0" inside the loop, a do/while, a "for(;;)" with a
 * "break", a "for(;;)" with a "continue" and a "break", a "do { ... if (...) break; }
 * while (1)" and a volatile pointer variable.  All of them produce the same body:
 * the nops after the mask, a conditional branch back and the exit inline.
 *
 * To unblock: a loop layout in which the mask is scheduled after the load's
 * settling nops and the exit block is placed after the loop with an unconditional
 * jump back.
 *
 * 28 October 2026: one explicit-label form (`if (mask == 0) goto done; goto
 * loop; done: return 0;`) was tried in the original source unit. cc1
 * canonicalized it to a 40-byte conditional-backedge loop, still with the
 * mask before three nops, against 56 retail bytes (0/28 USA placements).
 * The labels did not preserve the forward exit plus unconditional jump.
 */

typedef unsigned int u32;

int func_0029CF78(void)
{
    for (;;) {
        u32 v = *(volatile u32 *)0x1000D400;
        if ((v & 0x100) == 0)
            return 0;
    }
}
