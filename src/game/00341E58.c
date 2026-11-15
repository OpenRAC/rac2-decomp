#include "include_asm.h"
#include "names.h"

extern int list_menu_get_selection(char *);
int func_00341E58(char *object) { int index = list_menu_get_selection(object); return *(int *)(object + 0xD8) + index * 20; }
