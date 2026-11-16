#include "include_asm.h"
#include "names.h"

extern int D_L00_001A904C_2 __attribute__((sda));
extern int audio_menu_update(int, int);

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_3_us2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return audio_menu_update(value + 0x3DA78, argument);
    return 0;
}

void level_l00_call_module_handler_4_us2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        audio_menu_draw(value + 0x3DA78);
}

