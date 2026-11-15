/* Resets the quad at a0 from D_001A8F20, then, when a1 is set and a2 is not zero, passes
   each of the a2 quads after a1 to FastVecAdd and scales by 1/a2 with FastVecScale. */
#include "include_asm.h"
#include "common.h"
extern char D_001A8F20[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
void func_L03_0038B2E8(unsigned char *a0, unsigned char *a1, int a2) {
    int i;
    qcopy(a0, D_001A8F20);
    if (a1 == 0) return;
    if (!a2) return;
    for (i = 0; i < a2; i++) FastVecAdd(a0, a0, a1 + 0x10 + i * 0x10);
    FastVecScale(a0, a0, 1.0f / (float)a2);
}
