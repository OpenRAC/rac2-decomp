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
    int icon;
    char pad2[56];
    int tab_selection[3];
    int icon_group;
    int *icons;
    int count;
    char pad3[88];
    float *position;
    char pad4[240];
    int tab;
};

/* Draws the icon of each row of the tab menu list, tinting the selected one (PAL). */
void tab_menu_draw_icons_pal(struct Obj *self)
{
    int i;

    for (i = 0; i < self->count; i++) {
        object_set_first_float4(&self->icon, self->position[0] + g_tab_menu_icon_offset_x,
                self->position[1] + g_tab_menu_icon_offset_y + g_tab_menu_icon_spacing * (float)i, 0.0f, 0.0f);
        if (self->tab == 2) {
            int icon_id = self->icons[i];

            if (icon_id == 5)
                hud_set_widget_value_pair(&self->icon, 60062, 5);
            else
                hud_set_widget_value_pair(&self->icon, icon_id, 0);
        } else if (self->tab == 0) {
            int icon_id = self->icons[i];

            if (icon_id == 6)
                hud_set_widget_value_pair(&self->icon, 60055, 0);
            else
                hud_set_widget_value_pair(&self->icon, self->icon_group, icon_id);
        } else {
            hud_set_widget_value_pair(&self->icon, self->icon_group, self->icons[i]);
        }
        {
            int *color = object_get_fourth_field(&self->icon);
            int diff = self->tab_selection[self->tab] ^ i;
            int alt = 0x70FFFEED;

            *color = diff ? 0x60F0F0B0 : alt;
        }
        hud_draw_colored_quad_widget(&self->icon);
    }
}
