#include "common.h"

extern int func_00283DB8(void *, float);
extern int D_L09_00257110[];
extern float func_00283CE0(int);
extern void func_L09_003FD460(void *);
extern void func_L09_003FD128(void *);
extern void *func_L09_003FE3B0(int index, int *table);
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4_L09;

/* Unit of its own for -fno-gcse: with gcse, PRE keeps the table's high half in a saved
   register across the clear loop (324 bytes).

   Resets the 20-entry screen table to -1, then for each of the sub-object's 0x424 entries
   takes the next candidate from func_L09_003FE3B0, records its 0xB2 id in the table and,
   when its sphere passes the test, runs its draws: func_L09_003FD460 for flag 8 of its
   sub-object's 0x42C word, func_L09_003FD128 for flag 2. */
void func_L09_003FE4D0(unsigned char *moby)
{
    unsigned char *mobyBytes = moby;
    unsigned char *vars = *(unsigned char **)(mobyBytes + 0x68);
    int clearValue = -1;
    int i;
    Vec4_L09 sphere;

    for (i = 19; i >= 0; i--) {
        D_L09_00257110[i] = clearValue;
    }
    i = 0;
    if (*(short *)(vars + 0x424) > 0) {
        int *table = D_L09_00257110;
        int noneId = -1;
        int *tableSlot = table;
        do {
            char *child = (char *)FindFarthestTrackEntry(mobyBytes[0x21], table);
            unsigned char *childVars;
            *tableSlot = *(short *)(child + 0xB2);
            tableSlot++;
            qcopy(&sphere, child + 0x10);
            sphere.f[3] = 4.0f;
            if (FastMathHelperA(&sphere, IntToFloat(*(short *)(child + 0x32))) != noneId) {
                childVars = *(unsigned char **)(child + 0x68);
                if (*(int *)(childVars + 0x42C) & 8)
                    DrawSpinningLayeredQuads(child);
                if (*(int *)(childVars + 0x42C) & 2)
                    DrawLightRing(child);
            }
            i++;
        } while (i < *(short *)(vars + 0x424));
    }
}
