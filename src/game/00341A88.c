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
    char pad3[72];
    float *fp536;
    char pad4[224];
    int mode764;
};

/* Draws the row of icons of the tabbed menu, highlighting the selected one. */
void tab_menu_draw_icons(struct Obj *o)
{
    int i;

    for (i = 0; i < o->count460; i++) {
        object_set_first_float4(&o->h380, o->fp536[0] + g_tab_menu_icon_offset_x,
                o->fp536[1] + g_tab_menu_icon_offset_y + g_tab_menu_icon_spacing * (float)i, 0.0f, 0.0f);
        if (o->mode764 == 2) {
            int v = o->p456[i];

            if (v == 5)
                hud_set_widget_value_pair(&o->h380, 60062, 5);
            else
                hud_set_widget_value_pair(&o->h380, v, 0);
        } else if (o->mode764 == 0) {
            int w = o->p456[i];

            if (w == 6)
                hud_set_widget_value_pair(&o->h380, 60055, 0);
            else
                hud_set_widget_value_pair(&o->h380, o->a452, w);
        } else {
            hud_set_widget_value_pair(&o->h380, o->a452, o->p456[i]);
        }
        {
            int *r = object_get_fourth_field(&o->h380);
            int t = o->tbl440[o->mode764] ^ i;
            int alt = 0x70FFFEED;

            *r = t ? 0x60F0F0B0 : alt;
        }
        hud_draw_colored_quad_widget(&o->h380);
    }
}
