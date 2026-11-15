#include "include_asm.h"
#include "names.h"

extern void text_panel_update_mode(char *p);

void func_US2_L00_00445228(char *p)
{
    text_panel_update_mode(p + 0x1D8C);
}

extern void text_panel_draw_scaled(char *p);

void func_US2_L00_00445248(char *p)
{
    text_panel_draw_scaled(p + 0x1D8C);
}

