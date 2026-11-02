/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* near miss: 9 of 10 instructions (ours 36 bytes, retail 40). Retail loads through $at with hand-placed nops and ends in jr ra + lui ra, 0x7000 (looks like hand asm); plain C gives $v0 and fewer nops.
 *
 * Measured again in wave 12 (worker s2), the plain C attempt is
 *
 *   void func_L00_0036BE28(char *a0)
 *   {
 *       while (*(volatile unsigned int *)(a0 - 0x3000) & 0x100)
 *           ;
 *   }
 *
 * which comes out as
 *
 *   lw $v0, -0x3000($a0) ; andi $v0, $v0, 0x100 ; nop ; nop ; nop ;
 *   bnez $v0, -0x18 ; nop ; jr $ra ; nop
 *
 * (36 bytes) against retail's
 *
 *   lw $at, -0x3000($a0) ; nop ; nop ; nop ; andi $at, $at, 0x100 ; nop ;
 *   bnez $at, -0x1C ; nop ; jr $ra ; lui $ra, 0x7000
 *
 * (40 bytes). The gap is not a spelling problem:
 *  - the retail uses $at as a working register (it holds the status word from
 *    the load to the test), which no C spelling produces - this cc1 always
 *    picks $v0 for it;
 *  - retail has three hand-placed nops after the load and one after the test,
 *    which gcc never emits here;
 *  - retail's return delay slot is `lui $ra, 0x7000`, a hand-written filler
 *    (the jr has already read $ra, so the lui is harmless, but no compiler
 *    writes one).
 *
 * The five siblings func_L00_0036C9AC, func_L00_0036C9D4, func_L00_0036D274,
 * func_L00_0036D29C and func_L00_0036EF40 have the same ten instructions (only
 * the -0x3000 / -0x2C00 offset differs), so the same wall applies to all six.
 */
void func_L00_0036BE28(char *a0)
{
    while (*(volatile unsigned int *)(a0 - 0x3000) & 0x100)
        ;
}
