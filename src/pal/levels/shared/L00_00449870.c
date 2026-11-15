#include "include_asm.h"
#include "names.h"

extern int text_panel_update_mode(char *p);

int func_PAL_L00_00449870(char *p)
{
    return text_panel_update_mode(p + 0x1D8C);
}

extern int text_panel_draw_scaled(char *p);

int func_PAL_L00_00449890(char *p)
{
    return text_panel_draw_scaled(p + 0x1D8C);
}

