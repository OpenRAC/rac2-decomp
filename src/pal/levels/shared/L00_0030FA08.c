#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int list_menu_set_selection_pal(int, int);

/* func_PAL_L00_0030FA08, the PAL copy of func_L00_0030DBB8: the same C, where the offset becomes 0x3EA78 and the handler func_PAL_00343F50. */
int func_PAL_L00_0030FA08(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_set_selection_pal(value + 0x3EA78, argument);
    return 0;
}
