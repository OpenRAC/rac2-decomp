#include "names.h"
/* func_US2_00345890, the USA v2.00 copy of func_00344938: the same C with the text elements moved, new
   string ids, a local row offset in place of 16.0f, and the highlight offsets read from data. */
#include "include_asm.h"

extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, char *);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(void *, int);
extern void text_label_draw_us2(void *);
extern int save_count_filled_slots_us2(void);
extern int save_get_baseline_count(void);
extern int save_count_items_above_baseline(void);
extern float *object_get_first_field(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_flag_value(void *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern char g_str_string_format[], g_str_count_format[], g_str_grid_label_format[];
extern short g_orb_counter;
extern int g_mode_setting_value;
extern int g_bolt_count;
extern int g_grid_label_x_shift __attribute__((sda));
extern int g_grid_label_rect_left __attribute__((sda));
extern int g_grid_label_rect_top;
extern int g_grid_label_rect_right __attribute__((sda));
extern int g_grid_label_rect_bottom;
extern int g_child_offset_x __attribute__((sda));
extern int g_child_offset_y;

void grid_menu_update_labels_us2(char *self)
{
    int sel = 0;
    int yoff;
    float zero;

    if (*(int *)(self + 0x4B8) == 3)
        sel = *(int *)(self + 0x4AC) + *(int *)(self + 0x4B0) * 2;
    self[0x480] = 0;
    self[0x490] = 0;
    yoff = 16;
    hud_set_widget_field_b(self + 0x310, GetLocalizedString(0x333E));
    switch (sel) {
    case 0:
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x333E));
        zero = 0.0f;
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0x2C51));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, save_count_filled_slots_us2());
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1], zero, zero);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x480, g_str_string_format, GetLocalizedString(0x2C52));
        hud_set_widget_field_a(self + 0x3C0, 0);
        text_label_draw_us2(self + 0x3C0);
        sprintf(self + 0x480, g_str_count_format, save_get_baseline_count());
        object_set_first_float4(self + 0x3C0, object_get_first_field(self + 0x3C0)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x3C0)[1], zero, zero);
        hud_set_widget_field_a(self + 0x3C0, 2);
        text_label_draw_us2(self + 0x3C0);
        sprintf(self + 0x490, g_str_string_format, GetLocalizedString(0x2C53));
        hud_set_widget_field_a(self + 0x418, 0);
        text_label_draw_us2(self + 0x418);
        sprintf(self + 0x490, g_str_count_format, save_count_items_above_baseline());
        object_set_first_float4(self + 0x418, object_get_first_field(self + 0x418)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x418)[1], zero, zero);
        hud_set_widget_field_a(self + 0x418, 2);
        text_label_draw_us2(self + 0x418);
        break;
    case 1:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0x2C51));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_orb_counter);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_us2(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0x333C));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x333C));
        break;
    case 2:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0x2C51));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_mode_setting_value);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_us2(self + 0x368);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0x333B));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x333B));
        break;
    case 3:
        sprintf(self + 0x470, g_str_string_format, GetLocalizedString(0x2C51));
        hud_set_widget_field_a(self + 0x368, 0);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x470, g_str_count_format, g_bolt_count);
        object_set_first_float4(self + 0x368, object_get_first_field(self + 0x368)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(self + 0x368)[1] + (float)yoff, 0.0f, 0.0f);
        hud_set_widget_field_a(self + 0x368, 2);
        text_label_draw_us2(self + 0x368);
        sprintf(self + 0x470, g_str_grid_label_format, GetLocalizedString(0x2C51), g_bolt_count);
        hud_set_widget_field_b(self + 0x310, GetLocalizedString(0x333A));
        hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x333A));
        break;
    }
    text_label_draw_us2(self + 0x310);
    if (*(int *)(self + 0x4B4) == sel) {
        object_set_flag_value(self + 0x220, 1);
        object_set_first_float4(self + 0x220, (float)g_child_offset_x + (*(float **)(self + 0x4A0))[0],
                      (float)g_child_offset_y + (*(float **)(self + 0x4A0))[1], 0.0f, 0.0f);
        text_label_draw_us2(self + 0x220);
    }
    if (sel == 0) {
        int x = (*(float **)(self + 0x4A0))[0];
        int y = (*(float **)(self + 0x4A0))[1];
        AppendScreenRectPacket(x + g_grid_label_rect_left, y + g_grid_label_rect_top, x + g_grid_label_rect_right, y + g_grid_label_rect_bottom,
                      0x55F0C070, 0);
    }
}
