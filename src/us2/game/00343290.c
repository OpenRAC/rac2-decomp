#include "include_asm.h"
#include "names.h"

extern void menu_set_entry_table(unsigned char *owner, float *records);

/* func_00342118 is in 00341C20-g8.c (it reaches small data through $gp). */

void list_menu_set_record_table_us2(unsigned char *owner, float *records)
{
    *(float **)(owner + 0x260) = records;
    menu_set_entry_table(owner + 0x188, records);
}

