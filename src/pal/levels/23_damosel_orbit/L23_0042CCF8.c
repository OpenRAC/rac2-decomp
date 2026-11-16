#include "include_asm.h"
#include "names.h"

extern void boss_part_init_health_pal(int);
extern void boss_part_count_frame(int);

void func_PAL_L23_0042CCF8(int param_1)
{
    boss_part_init_health_pal(param_1);
    boss_part_count_frame(param_1);
}


