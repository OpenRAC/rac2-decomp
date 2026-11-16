#include "include_asm.h"
#include "names.h"
extern int g_tab_menu_tab_values __attribute__((sda));
extern char g_tab_menu_records[];
extern void menu_set_selected_index(void *, int);
extern void menu_set_entry_table(unsigned char *, float *);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, unsigned int);
extern void object_set_value_float(void *, float);

void tab_menu_switch_tab_us2(char *self, int idx)
{
    float *records;
    float f;
    unsigned char *child;
    if ((unsigned int)idx > 2) return;
    *(int *)(self + 0x1C4) = ((int *)&g_tab_menu_tab_values)[idx];
    *(int *)(self + 0x1C8) = (int)(g_tab_menu_records + idx * 0x20);
    *(int *)(self + 0x1CC) = (idx == 0) ? 7 : ((idx == 1) ? 8 : 6);
    if (idx != 0) {
        if (idx == 2) f = 2.0f;
        else f = 1.0f;
    } else {
        f = 0.0f;
    }
    child = (unsigned char *)self + 0x238;
    {
        int *p = (int *)(self + idx * 4);
        menu_set_selected_index(child, p[0x6E]);
    }
    records = (idx == 0) ? *(float **)(self + 0x310) : ((idx == 1) ? *(float **)(self + 0x314) : *(float **)(self + 0x318));
    menu_set_entry_table(child, records);
    hud_set_widget_field_b(self + 0x1D0, GetLocalizedString((idx == 0) ? 0x2BEB : ((idx == 1) ? 0x2BEC : 0x3094)));
    object_set_value_float(self, f);
    object_set_value_float(self + 0x4C, f);
    object_set_value_float(self + 0xE4, f);
    *(int *)(self + 0x31C) = idx;
}

extern float g_tab_menu_cursor_step_y __attribute__((sda));
extern float g_tab_menu_cursor_base_y;
extern float g_tab_menu_cursor_offset_x __attribute__((sda));
extern void object_set_first_float4(void *, float, float, float, float);

void tab_menu_position_cursor_us2(char *self)
{
    int index = *(int *)(self + 0x31C);
    float *v = *(float **)(self + 0x228);
    int *base = (int *)(self + (index << 2));

    object_set_first_float4(self + 0x130, g_tab_menu_cursor_offset_x + v[0],
            (g_tab_menu_cursor_base_y + g_tab_menu_cursor_step_y * (float)base[0x6E]) + v[1],
            0.0f, 0.0f);
}
