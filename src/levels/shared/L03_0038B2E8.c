/* Resets the quad at a0 from D_001A8F20, then, when a1 is set and a2 is not zero, passes
   each of the a2 quads after a1 to func_00282CC0 and scales by 1/a2 with func_00282D30. */
#include "include_asm.h"
#include "common.h"
extern char D_001A8F20[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
void func_L03_0038B2E8(unsigned char *result, unsigned char *points, int count) {
    int i;
    qcopy(result, D_001A8F20);
    if (points == 0) return;
    if (!count) return;
    for (i = 0; i < count; i++) FastVecAdd(result, result, points + 0x10 + i * 0x10);
    FastVecScale(result, result, 1.0f / (float)count);
}
