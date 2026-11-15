#include "names.h"


extern int ref_L00_002F43E0_00;

extern int ref_L00_002F43E8_00;

extern int ref_L00_002F43F8_00;

/* Turns a flag off. */
void level_clear_flag_b(void)
{
    ref_L00_002F43E0_00 = 0;
}

/* Turns a flag on. */
void level_set_flag_b_true(void)
{
    ref_L00_002F43E8_00 = 1;
}

/* Gets the stored flag value. */
int level_get_flag_b(void)
{
    return ref_L00_002F43F8_00;
}
