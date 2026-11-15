#include "include_asm.h"
#include "names.h"

extern void func_PAL_L23_0042CD30(int);
extern void boss_part_count_frame(int);

void func_PAL_L23_0042CCF8(int param_1)
{
    func_PAL_L23_0042CD30(param_1);
    boss_part_count_frame(param_1);
}


