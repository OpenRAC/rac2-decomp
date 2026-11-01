#include "include_asm.h"







#include "common.h"

/* func_L00_0040DF58 is in L00_0040DF58-g8.c. */

/* func_L00_0040F6A0 is in L00_0040F6A0-g16.c. */

/* func_L00_00410178 is defined in L00_00410178.c. */



/* func_L00_00410690 is defined in L00_00410690-g64.c. */

/* Reads the halfword at +0x1A of the object's node and grades it: 4 at or above 90, 3 above 60,
   2 above 30, else 1. The two lower bounds stay in variables, which is what keeps them in
   registers instead of an immediate compare. */
int func_PAL_L00_00415648(char *object)
{
    int value = *(short *)(*(int *)(object + 0x68) + 0x1A);
    int upper = 0x32;
    int lower = 0x19;
    int result = 1;

    if (value >= 0x4B)
        result = 4;
    else if (upper < value)
        result = 3;
    else if (lower < value)
        result = 2;
    return result;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00415690);
