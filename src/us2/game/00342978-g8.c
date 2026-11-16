#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(void *, int, int);
extern int *object_get_fourth_field(void *);
extern void hud_draw_colored_quad_widget(void *);
extern float g_tab_menu_icon_offset_x __attribute__((sda));
extern float g_tab_menu_icon_offset_y;
extern float g_tab_menu_icon_spacing __attribute__((sda));
struct Obj {
    char pad[380];
    int h380;
    char pad2[56];
    int tbl440[3];
    int a452;
    int *p456;
    int count460;
    char pad3[88];
    float *fp536;
    char pad4[240];
    int mode764;
};

/* Draws the row of icons of a tab menu, tinting the selected one. */
void tab_menu_draw_icons_us2(struct Obj *menu)
{
    int i;

    for (i = 0; i < menu->count460; i++) {
        object_set_first_float4(&menu->h380, menu->fp536[0] + g_tab_menu_icon_offset_x,
                menu->fp536[1] + g_tab_menu_icon_offset_y + g_tab_menu_icon_spacing * (float)i, 0.0f, 0.0f);
        if (menu->mode764 == 2) {
            int icon = menu->p456[i];

            if (icon == 5)
                hud_set_widget_value_pair(&menu->h380, 60062, 5);
            else
                hud_set_widget_value_pair(&menu->h380, icon, 0);
        } else if (menu->mode764 == 0) {
            int icon = menu->p456[i];

            if (icon == 6)
                hud_set_widget_value_pair(&menu->h380, 60055, 0);
            else
                hud_set_widget_value_pair(&menu->h380, menu->a452, icon);
        } else {
            hud_set_widget_value_pair(&menu->h380, menu->a452, menu->p456[i]);
        }
        {
            int *color = object_get_fourth_field(&menu->h380);
            int unselected = menu->tbl440[menu->mode764] ^ i;
            int alt = 0x70FFFEED;

            *color = unselected ? 0x60F0F0B0 : alt;
        }
        hud_draw_colored_quad_widget(&menu->h380);
    }
}
