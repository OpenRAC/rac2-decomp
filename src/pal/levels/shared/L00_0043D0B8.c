#include "include_asm.h"
#include "names.h"

extern int menu_get_selected_index(char *p);

int sub_object_get_value_near_pal(char *p)
{
    return menu_get_selected_index(p + 16);
}

