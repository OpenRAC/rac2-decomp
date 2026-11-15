#include "include_asm.h"
#include "names.h"
extern int D_L00_001A8F00;
extern int D_L00_001A9350 __attribute__((sda));
extern int D_L00_001A9090 __attribute__((sda));
extern int math_fast_float_d(void *);
extern void level_clear_table_entry(int);

int func_US2_00290EA0(void)
{
    if (D_L00_001A8F00 == 0 && math_fast_float_d(&D_L00_001A9350) != 0)
        level_clear_table_entry(1);
    return D_L00_001A9090;
}
