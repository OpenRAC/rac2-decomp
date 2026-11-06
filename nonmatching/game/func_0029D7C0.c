/* 6 November 2026, round 6: marked ASM_FUNC in src/ (original assembly, pending maintainer review); see the src comment for the evidence. */
/* func_0029D7C0 - near miss (worker 3, wave 3).
 *
 * The retail body is a spin wait: it reads a word, tests bit 0x100 and loops
 * while the bit is set.
 *
 *     0x0029d7c0  lw    $a2, 0x0($v1)
 *     0x0029d7c4  nop
 *     0x0029d7c8  andi  $a2, $a2, 0x100
 *     0x0029d7cc  nop
 *     0x0029d7d0  beqz  $a2, 0x29d7e0
 *     0x0029d7d4  nop
 *     0x0029d7d8  j     0x29d7c0
 *     0x0029d7dc  nop
 *     0x0029d7e0  jr    $ra
 *     0x0029d7e4  nop
 *
 * Three things keep plain C from matching it:
 *
 *  1. The pointer arrives in $v1 ($3), not in an argument register.  No C
 *     source can put an argument there, so the load's base register differs
 *     whatever the source says.
 *  2. The loop is top tested (beqz to the exit, then a jump back to the
 *     first instruction).  This compiler rotates the loop to the bottom
 *     (bnez back to the top) and drops the nops of the delay slots.
 *  3. The catalogue gives the function 72 bytes, but the code ends after
 *     0x0029d7e4: the rest is two `teq $zero,$zero,0` traps, four nops and a
 *     second `jr $ra` (0x0029d800) that no C emits.  A C candidate of the
 *     same shape is 44 bytes, so the size alone can never agree.
 *
 * Measured: the candidate below (a while loop over *p & 0x100) compiles to
 * 44 bytes against the retail's 72, and the loop's branch shape and the base
 * register of the load differ.
 */

void func_0029D7C0(int *p)
{
    while (*p & 0x100)
        ;
}
