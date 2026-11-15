#include "common.h"

/* Advances the 0-6 cursor and counts down the pending count once the check call accepts the current pair. */


extern int func_00288E18(int, int);
extern s16 D_L00_001B1B88[] MACRO_ADDR;
extern s16 D_L00_001B1B98[];
extern u8 D_L00_001B1BA6 __attribute__((section(".sdata")));
extern u8 D_L00_001B1BA7 __attribute__((section(".sdata")));

void func_L00_002F59A8(void)
{
    if (D_L00_001B1BA6 == 0)
        return;
    if (RequestSubtitleVoiceLine(D_L00_001B1B88[D_L00_001B1BA7],
                    D_L00_001B1B98[D_L00_001B1BA7]) == 0)
        return;
    D_L00_001B1BA7 = (D_L00_001B1BA7 + 1) % 7;
    D_L00_001B1BA6 = D_L00_001B1BA6 - 1;
}
