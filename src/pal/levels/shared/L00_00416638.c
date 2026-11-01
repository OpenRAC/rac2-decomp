#include "include_asm.h"

#include "common.h"
extern void func_002AFFD8(char *a0, void *a1, int a2);
extern void func_00282D30(void *a0, void *a1, float f12);
extern void func_PAL_L00_00416DC8(char *a0);
extern char ref_L00_004117B8_00[];

/* func_L00_004115E8 is defined in L00_004096B0-g8.c. */

/* Walks the thirty records of the level's block and, for every record whose +0x18 pointer is
   set, folds it into a sixteen-byte buffer: the record's own transform, then the scale of its
   +0x0C word, then its first three words added to the buffer. The block's address differs
   from level to level, so it takes a per-level name. */
void func_PAL_L00_00416638(char *a0)
{
    char *s0 = ref_L00_004117B8_00;
    char *s2 = a0;
    char *p;
    float buf[4];
    int i;

    for (i = 0x1D; i >= 0; i--) {
        if (*(char **)(s0 + 0x18) != 0) {
            p = *(char **)(s0 + 0x18);
            func_002AFFD8(p + 0x10, buf, 1);
            p = *(char **)(s0 + 0x18);
            func_00282D30(buf, buf, *(float *)(p + 0xC) * 0.0008300250046886504f);
            p = *(char **)(s0 + 0x18);
            buf[0] += *(float *)(p + 0) * 0.0009764999849721789f;
            buf[1] += *(float *)(p + 4) * 0.0009764999849721789f;
            buf[2] += *(float *)(p + 8) * 0.0009764999849721789f;
        }
        s0 = s0 + 0x30;
    }
    func_PAL_L00_00416DC8(s2);
}

