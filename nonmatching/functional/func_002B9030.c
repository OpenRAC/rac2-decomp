/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
#include "include_asm.h"

/* Retail is an 8-byte tail wrapper: j func_002B9038 with addi $a1,$zero,0
   in the jump delay slot. The likely C interface is one argument here and
   two at the target. Current-master replay of the direct forwarding body in
   src/game/002B7E28.c: 28 bytes and 0/28 USA v1.01 placements. It builds a
   0x10-byte frame, uses jal, and restores $ra. The arg setup for $a1 is in
   the jal delay slot, but the callee target is called and returned from rather
   than tail-jumped to. It cannot express the required form with this compiler
   profile. */
extern char *func_002B9038(int, int);

char *func_002B9030(int a0)
{
    return func_002B9038(a0, 0);
}
