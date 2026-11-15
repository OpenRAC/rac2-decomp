#include "include_asm.h"
#include "names.h"

extern int ref_L00_002F3488_00;

extern int ref_L00_002F3490_00;

extern int ref_L00_002F34A0_00;

/* Gets a stored flag value. */
int level_get_flag_a(void)
{
    return ref_L00_002F3488_00;
}

/* Turns a flag on. */
void level_set_flag_a_true(void)
{
    ref_L00_002F3490_00 = 1;
}

/* Turns a flag off. */
void level_clear_flag_a(void)
{
    ref_L00_002F34A0_00 = 0;
}

extern unsigned char g_item_slot_to_record[];

extern char D_L00_00262620[];

/* One byte of the resident table, scaled by 0xE0 into the level's own table. */
char *level_get_table_entry_address(int index)
{
    return g_item_slot_to_record[index] * 0xE0 + (int)D_L00_00262620;
}
