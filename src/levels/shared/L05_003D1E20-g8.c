/* func_L05_003D1E20 (60 bytes; levels 05, 10, 15, 25): clears a $gp flag and two five-word
   tables. Both tables are built with the absolute la macro (MACRO_ADDR), which keeps each
   lui/addiu pair together. */
#include "common.h"
extern int D_L05_001AFCB8 __attribute__((sda));
extern int D_L05_001B2FA0[] MACRO_ADDR;
extern int D_L05_001B3018[] MACRO_ADDR;

/* Clears the explosion counter and both explosion slot tables. */
void func_L05_003D1E20(void)
{
    int i;

    D_L05_001AFCB8 = 0;
    for (i = 0; i < 5; i++) {
        D_L05_001B3018[i] = 0;
        D_L05_001B2FA0[i] = 0;
    }
}
