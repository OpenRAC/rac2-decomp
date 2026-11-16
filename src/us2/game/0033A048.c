#include "include_asm.h"
#include "names.h"

extern void *object_construct_derived_a(void *p);
extern char *hud_construct_widget_base(void *p);

/* func_00338F58 is matched in 00338F58.c. */

/* Constructs the mission screen parts (v2.00 version of mission_screen_init_parts): eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
void *mission_screen_init_parts_us2(char *panel)
{
    object_construct_derived_a(panel + 8);
    object_construct_derived_a(panel + 84);
    object_construct_derived_a(panel + 160);
    object_construct_derived_a(panel + 236);
    hud_construct_widget_base(panel + 312);
    hud_construct_widget_base(panel + 400);
    hud_construct_widget_base(panel + 488);
    hud_construct_widget_base(panel + 576);
    return panel;
}
