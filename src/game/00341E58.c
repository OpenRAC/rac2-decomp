#include "include_asm.h"
#include "names.h"

extern int func_00341E90(char *);
int func_00341E58(char *object) { int index = GetListMenuSelection(object); return *(int *)(object + 0xD8) + index * 20; }
