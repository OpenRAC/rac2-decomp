#include "include_asm.h"

#include "common.h"
extern int func_0028B950(void *);

int func_PAL_L00_002F8BE8(char *self) {
    *(short *)(self + 0x48) = 0;
    *(short *)(self + 0x4A) = 0;
    *(int *)(self + 0x58) = 0x20;
    *(int *)(self + 0x7C) = 0x26;
    *(int *)(self + 0x5C) = 0x20;
    return func_0028B950(self);
}


extern int r1_func_0011CC38();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int func_PAL_L00_002F8C60(void) {
    return r1_func_0011CC38();
}

