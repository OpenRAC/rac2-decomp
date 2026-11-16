#include "include_asm.h"
#include "names.h"

extern int list_menu_get_selection(char *);

int func_PAL_00343EC0(char *object) { int index = list_menu_get_selection(object); return *(int *)(object + 0xE8) + index * 20; }

extern void menu_set_entry_table(unsigned char *owner, float *records);

void list_menu_set_records_pal(unsigned char *owner, float *records)
{
    menu_set_entry_table(owner + 0x10, records);
    *(float **)(owner + 0xE8) = records;
}

extern void *UpdateMenuListSelection(char *, int);
extern void menu_set_position(char *, float, float);

int list_menu_set_selection_pal(char *object, int arg)
{
    char *child = object + 0x10;
    UpdateMenuListSelection(child, arg);
    menu_set_position(child, (*(float **)object)[0], (*(float **)object)[1]);
    return 0;
}

