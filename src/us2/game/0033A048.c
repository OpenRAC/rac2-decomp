#include "include_asm.h"
#include "names.h"

extern void *object_construct_derived_a(void *p);
extern char *hud_construct_widget_base(void *p);

/* func_00338F58 is matched in 00338F58.c. */

/* Initialises eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
void *func_US2_0033A048(char *a0)
{
    object_construct_derived_a(a0 + 8);
    object_construct_derived_a(a0 + 84);
    object_construct_derived_a(a0 + 160);
    object_construct_derived_a(a0 + 236);
    hud_construct_widget_base(a0 + 312);
    hud_construct_widget_base(a0 + 400);
    hud_construct_widget_base(a0 + 488);
    hud_construct_widget_base(a0 + 576);
    return a0;
}
