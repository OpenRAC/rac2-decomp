#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void hud_update_subobject_primary(void *);

/* Runs the level object update routine, if a level object is loaded. */
void level_run_update_pal(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subobject_primary(g_resident_data_base[0] + 0x36F28);
}

extern int D_L00_001A904C_6 __attribute__((sda));
extern void text_draw_framed_box(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void level_forward_draw_args_pal(int arg_0, int arg_1, int arg_2, int arg_3, int arg_4, int arg_5, int arg_6, int arg_7, int arg_8, int arg_9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        text_draw_framed_box((int *)(value + 0x36F28), arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8, arg_9);
}

extern void hud_update_subobject_alt_pal(int);

/* Draws the first on-screen menu panel, if the menu system exists. */
void menu_draw_top_panel_pal(void)
{
    char *value = g_resident_data_base[0];

    if (value != 0)
        hud_update_subobject_alt_pal((int)(value + 0x36F28));
}
