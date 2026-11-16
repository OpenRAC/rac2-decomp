#include "names.h"
/* func_PAL_003469E8, the PAL copy of func_00344938: the same C with the PAL field offsets and string ids, where
 * the language byte D_PAL_001A7C3C picks string 0xAD3 for language 2, func_00336A78 is PAL's own func_PAL_00338770,
 * and cases 1 to 3 lose the 16.0f and pass an int local holding 0 instead of 0.0f. */
#include "include_asm.h"

extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, char *);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(void *, int);
extern void text_label_draw_pal(void *);
extern int save_count_filled_slots(void);
extern int save_get_baseline_count(void);
extern int save_count_items_above_baseline(void);
extern float *object_get_first_field(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_flag_value(void *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern char g_str_string_format[], g_str_count_format[], g_str_grid_label_format[];
extern unsigned char g_pal_region_mode;
extern short g_orb_counter;
extern int g_mode_setting_value;
extern int g_bolt_count;
extern int g_grid_label_x_shift __attribute__((sda));
extern int g_grid_label_rect_left __attribute__((sda));
extern int g_grid_label_rect_top;
extern int g_grid_label_rect_right __attribute__((sda));
extern int g_grid_label_rect_bottom;

void grid_menu_update_labels_pal(char *self)
{
    int sel = 0;
    float zero;
    int off;

    if (*(int *)(self + 0x4B8) == 3)
        sel = *(int *)(self + 0x4AC) + *(int *)(self + 0x4B0) * 2;
    self[0x480] = 0;
    self[0x490] = 0;
    if (g_pal_region_mode == 2)
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD3));
    else
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD2));
    off = 0;
    switch (sel) {
    case 0:
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD2));
        zero = 0.0f;
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, save_count_filled_slots());
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1], zero, zero);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x480, g_str_string_format, GetLocalizedString(0xBCD));
        hud_set_widget_field_a(self + 0x3C0, 0);
        text_label_draw_pal(self + 0x3C0);
        sprintf(self + 0x480, g_str_count_format, save_get_baseline_count());
        object_set_first_float4(self + 0x3C0, object_get_first_field(self + 0x3C0)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x3C0)[1], zero, zero);
        hud_set_widget_field_a(self + 0x3C0, 2);
        text_label_draw_pal(self + 0x3C0);
        sprintf(self + 0x490, g_str_string_format, GetLocalizedString(0xBCE));
        hud_set_widget_field_a(self + 0x418, 0);
        text_label_draw_pal(self + 0x418);
        sprintf(self + 0x490, g_str_count_format, save_count_items_above_baseline());
        object_set_first_float4(self + 0x418, object_get_first_field(self + 0x418)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x418)[1], zero, zero);
        hud_set_widget_field_a(self + 0x418, 2);
        text_label_draw_pal(self + 0x418);
        break;
    case 1:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_orb_counter);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_pal(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD1));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD1));
        break;
    case 2:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_mode_setting_value);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_pal(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xAD0));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xAD0));
        break;
    case 3:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0xBCC));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_bolt_count);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1], off, off);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_pal(self + 0x368);
        sprintf(self + 0x470, g_str_grid_label_format, GetLocalizedString(0xBCC), g_bolt_count);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xACF));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0xACF));
        break;
    }
    text_label_draw_pal(self + 0x310);
    if (*(int *)(self + 0x4B4) == sel) {
        object_set_flag_value(self + 0x220, 1);
        object_set_first_float4(self + 0x220, (*(float **)(self + 0x4A0))[0] + -117.0f,
                      (*(float **)(self + 0x4A0))[1] + 3.0f, 0.0f, 0.0f);
        text_label_draw_pal(self + 0x220);
    }
    if (sel == 0) {
        int x = (*(float **)(self + 0x4A0))[0];
        int y = (*(float **)(self + 0x4A0))[1];
        AppendScreenRectPacket(x + g_grid_label_rect_left, y + g_grid_label_rect_top, x + g_grid_label_rect_right, y + g_grid_label_rect_bottom,
                      0x55F0C070, 0);
    }
}
