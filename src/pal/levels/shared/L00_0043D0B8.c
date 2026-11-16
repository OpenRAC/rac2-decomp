#include "include_asm.h"
#include "names.h"

extern int menu_get_selected_index(char *object);

/* Returns the selected index of the sub-object at +16. */
int sub_object_get_value_near_pal(char *object)
{
    return menu_get_selected_index(object + 16);
}

