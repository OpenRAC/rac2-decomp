#include "include_asm.h"
#include "names.h"

extern void menu_set_entry_table(unsigned char *owner, float *records);

void list_menu_set_records_us2(unsigned char *owner, float *records)
{
    menu_set_entry_table(owner + 0x10, records);
    *(float **)(owner + 0xE8) = records;
}

