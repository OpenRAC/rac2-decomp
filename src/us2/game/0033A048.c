#include "include_asm.h"

extern void func_003361A8(void *p);
extern void func_00336968(void *p);

/* func_00338F58 is matched in 00338F58.c. */

/* Initialises eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
void *func_US2_0033A048(char *a0)
{
    func_003361A8(a0 + 8);
    func_003361A8(a0 + 84);
    func_003361A8(a0 + 160);
    func_003361A8(a0 + 236);
    func_00336968(a0 + 312);
    func_00336968(a0 + 400);
    func_00336968(a0 + 488);
    func_00336968(a0 + 576);
    return a0;
}


INCLUDE_ASM("asm/us2/game", func_US2_0033A0B8);
