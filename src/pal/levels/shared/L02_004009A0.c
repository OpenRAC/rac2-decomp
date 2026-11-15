#include "include_asm.h"

#include "common.h"
extern void SetDeathBits(void *, int, int);

/* Forwards the first argument with a null second and a third of three. */
void func_PAL_L02_004009A0(void *a0) {
    SetDeathBits(a0, 0, 3);
}

