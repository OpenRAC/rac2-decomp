#include "include_asm.h"
#include "names.h"

extern int ref_L25_00438E98_00;

extern int ref_L05_00447F10_00;

/* Returns a value that is stored in another level's data. */
int level_get_linked_value_a(void)
{
    return ref_L25_00438E98_00;
}

/* Returns a second value kept in the same level data. */
int level_get_linked_value_b(void)
{
    return ref_L05_00447F10_00;
}


