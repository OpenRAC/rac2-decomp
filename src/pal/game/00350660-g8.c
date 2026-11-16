#include "include_asm.h"
#include "names.h"
extern char g_hud_float_params[];
extern int g_input_block_flag;
extern char *g_bolt_counter_base;
extern int g_radial_menu_layout_x __attribute__((sda));
extern int g_radial_menu_layout_y __attribute__((sda));
extern void UpdateViewContext(void);
extern unsigned int menu_get_label_color_alpha(void *);
extern void radial_menu_layout_items(void *, int, int, int);
extern void menu_noop_hook(void *);
extern void DrawBoltCounterPanel(void *);
extern void text_panel_draw_scaled(void *);
extern void func_0029CB80(void);

/* Draws the item and bolt HUD once, using a temporary setting that is put back afterwards (PAL layout). */
void hud_item_bolt_draw_pal(char *hud)
{
    float saved_scale;
    char *view;
    char *state = g_hud_float_params;
    saved_scale = *(float *)(state + 0xB0);
    *(float *)(state + 0xB0) = 0.62f;
    UpdateViewContext();
    if (g_input_block_flag == 0)
        radial_menu_layout_items(hud, g_radial_menu_layout_x, g_radial_menu_layout_y, menu_get_label_color_alpha(hud + 0x7A0) >> 24);
    menu_noop_hook(hud);
    DrawBoltCounterPanel(hud + 0x7A0);
    view = g_bolt_counter_base + 0x38000;
    *(int *)(view + 0x7A8C) = 0;
    *(int *)(view + 0x7A90) = 0;
    text_panel_draw_scaled(hud + 0x1FDC);
    func_0029CB80();
    *(float *)(state + 0xB0) = saved_scale;
    UpdateViewContext();
}
