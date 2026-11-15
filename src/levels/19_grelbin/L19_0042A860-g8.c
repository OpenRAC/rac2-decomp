#include "include_asm.h"
#include "names.h"

extern int func_L08_003289D0(int);

extern int D_L19_001B1FB8 __attribute__((sda));

/* Sum of the three subtitles' lengths, kept for the next frame. */
int func_L19_0042A860(void) {
    int firstLength = CountMobysOfClass(0x11C7);
    int secondLength = CountMobysOfClass(0x1266);
    int thirdLength = CountMobysOfClass(0xF57);
    int total = firstLength + secondLength + thirdLength;

    D_L19_001B1FB8 = total;
    return total;
}
