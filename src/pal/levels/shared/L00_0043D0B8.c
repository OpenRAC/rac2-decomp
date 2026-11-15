#include "include_asm.h"
#include "names.h"

extern int menu_get_selected_index(char *p);

int func_PAL_L00_0043D0B8(char *p)
{
    return menu_get_selected_index(p + 16);
}

