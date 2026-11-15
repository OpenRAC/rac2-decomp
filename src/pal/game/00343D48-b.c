#include "include_asm.h"
#include "names.h"
extern int list_menu_get_selection(char *);
extern int menu_get_selected_index(void *);

int func_PAL_00343EF8(char *object) {
    return menu_get_selected_index(object + 0x10);
}
