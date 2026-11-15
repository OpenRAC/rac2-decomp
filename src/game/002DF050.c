#include "common.h"
typedef struct {
    short f0;
    short f2;
    char pad4[8];
} Slot;
extern Slot D_0025EBD0[];
extern int D_001AB29C[4] MACRO_ADDR;
extern int D_001A7318 MACRO_ADDR;
extern int func_002B0E90(void);
extern int func_002B0E28(void);

/* Unlock levels for the counts the player has collected. */
void func_002DF050(void)
{
    int reachedFirst = CountNonZeroFlags() >= 15;
    int reachedSecond = CountNonZeroFlags() >= 30;
    int reachedThird = CountEntriesAboveThreshold() >= 10;
    D_0025EBD0[5].f2 = reachedFirst ? 3 : 2;
    D_0025EBD0[6].f2 = reachedSecond ? 3 : 2;
    D_0025EBD0[7].f2 = reachedThird ? 10 : 2;
    D_0025EBD0[8].f2 = reachedThird ? 3 : 2;
    D_001AB29C[0] = reachedFirst ? 0x2E1F : 0x2E25;
    D_001AB29C[1] = reachedSecond ? 0x2E20 : 0x2E26;
    D_001AB29C[2] = reachedThird ? 0x2E23 : 0x2E27;
    D_001AB29C[3] = reachedThird ? 0x2E24 : 0x2E27;
    if (D_001A7318) D_0025EBD0[8].f0 = 0;
}
