#include "include_asm.h"
#include "names.h"

extern void text_panel_update_mode(char *p);

/* Updates the mode of the text panel sub-object. */
void sub_object_get_value_first_us2(char *p)
{
    text_panel_update_mode(p + 0x1D8C);
}

extern void text_panel_draw_scaled(char *p);

/* Draws the text panel sub-object scaled. */
void sub_object_get_value_second_us2(char *p)
{
    text_panel_draw_scaled(p + 0x1D8C);
}

