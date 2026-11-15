#include "include_asm.h"
#include "names.h"

extern void text_panel_update_mode(char *p);

void func_PAL_L00_00449870(char *p)
{
    text_panel_update_mode(p + 0x1D8C);
}

extern void text_panel_draw_scaled(char *p);

void func_PAL_L00_00449890(char *p)
{
    text_panel_draw_scaled(p + 0x1D8C);
}

