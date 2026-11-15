#include "include_asm.h"
#include "names.h"
extern void list_menu_get_selection(char *);
extern void menu_get_selected_index(void *);

void func_PAL_00343EF8(char *object) {
    menu_get_selected_index(object + 0x10);
}
