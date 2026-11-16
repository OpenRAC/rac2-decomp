#include "include_asm.h"
#include "names.h"

extern void text_panel_update_mode(char *p);

/* Updates the text panel embedded in the object (PAL copy). */
void sub_object_get_value_first_pal(char *p)
{
    text_panel_update_mode(p + 0x1D8C);
}

extern void text_panel_draw_scaled(char *p);

/* Draws the scaled text panel embedded in the object (PAL copy). */
void sub_object_get_value_second_pal(char *p)
{
    text_panel_draw_scaled(p + 0x1D8C);
}

