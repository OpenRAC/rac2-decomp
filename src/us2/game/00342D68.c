#include "include_asm.h"
#include "names.h"

extern int list_menu_get_selection(char *);

int func_US2_00342D68(char *object) { int index = list_menu_get_selection(object); return *(int *)(object + 0xE8) + index * 20; }

