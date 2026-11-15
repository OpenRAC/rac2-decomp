#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);
extern char *ref_L00_003286D0_00;
extern char ref_L00_003286D0_01[];
extern char *D_0018C0B0;

/* Ask the shared helper to place a1's vector at self+0x10; on success, unless the
   level's current object is excluded (its +0xAA id is 0xFB0, or it is the object at
   D_0018C0B0), copy the resident vector there and answer 1. */

int func_003286D0(char *self, void *a1)
{
    char *o;

    if (CollLine(a1, self + 0x10, 0, self, 0) != 0) {
        o = ref_L00_003286D0_00;
        if (o != 0 && (*(short *)(o + 0xAA) == 0xFB0 || o == D_0018C0B0))
            return 0;
        qcopy(self + 0x10, ref_L00_003286D0_01);
        return 1;
    }
    return 0;
}
