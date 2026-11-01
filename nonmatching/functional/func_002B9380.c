/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
#include "include_asm.h"

/* Claude Opus 5.5 xhigh worker, 2026-10-31; retained near miss, not linked.
 * USA v1.01, -O2 -G0 -ffunction-sections: 12/16 bytes, 0/28 places.
 * Retail: lw $v0,0x3C($a0) ; nop ; jr $v0 ; nop. This body emits the same words
 * without the middle nop. The older call form is 32 bytes (frame, jalr, return).
 *
 * The same 12 bytes came from -g, -O1, -fno-delayed-branch, -frac2-hazard-labels and
 * a volatile load (rejected as a wording; measured only). -O0 gives a frame. Assembling
 * lw/j directly with as -mips1 adds no nop either, so this assembler is not the source.
 *
 * Retail scan of the boot and all 27 levels for lw rX ; nop ; jr rX ; nop: only this
 * function and the boot's 0x2E1AA8 (lw $a3,0x3FA0($ra)), which sits in COP2 macro code.
 * The boot has 112 lw rX ; jr rX sites with no nop. This points to handwritten assembly;
 * it is circumstantial, not proof. An asm nop would close it and is forbidden.
 */

void func_002B9380(void *a0)
{
    goto *(void *)(*(unsigned int *)((char *)a0 + 0x3C));
}
