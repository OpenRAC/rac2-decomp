#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int list_page_update(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_2_us2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_page_update(value + 0x3F3F0, argument);
    return 0;
}

void level_l00_call_module_handler_3_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_page_draw(value + 0x3F3F0);
}

