#include "include_asm.h"
#include "names.h"

extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, char *);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(void *, int);
extern void text_label_draw(void *);
extern int save_count_filled_slots(void);
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

/* Updates the texts of the grid menu for the selected entry, such as counts and descriptions, and draws the cursor box. */
void grid_menu_update_labels(char *menu)
{
    int sel = 0;
    float zero;

    if (*(int *)(menu + 0x448) == 3)
        sel = *(int *)(menu + 0x43C) + *(int *)(menu + 0x440) * 2;
    menu[0x410] = 0;
    menu[0x420] = 0;
    hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD2));
    switch (sel) {
    case 0:
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD2));
        zero = 0.0f;
        sprintf(menu + 0x400, g_str_string_format, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, g_str_count_format, save_count_filled_slots());
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x328)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x410, g_str_string_format, GetLocalizedString(0x2DBC));
        hud_set_widget_field_a(menu + 0x370, 0);
        text_label_draw(menu + 0x370);
        sprintf(menu + 0x410, g_str_count_format, save_get_baseline_count());
        object_set_first_float4(menu + 0x370, object_get_first_field(menu + 0x370)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x370)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x370, 2);
        text_label_draw(menu + 0x370);
        sprintf(menu + 0x420, g_str_string_format, GetLocalizedString(0x2DBD));
        hud_set_widget_field_a(menu + 0x3B8, 0);
        text_label_draw(menu + 0x3B8);
        sprintf(menu + 0x420, g_str_count_format, save_count_items_above_baseline());
        object_set_first_float4(menu + 0x3B8, object_get_first_field(menu + 0x3B8)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x3B8)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x3B8, 2);
        text_label_draw(menu + 0x3B8);
        break;
    case 1:
        sprintf(menu + 0x400, g_str_string_format, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, g_str_count_format, g_orb_counter);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD1));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD1));
        break;
    case 2:
        sprintf(menu + 0x400, g_str_string_format, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, g_str_count_format, g_mode_setting_value);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD0));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD0));
        break;
    case 3:
        sprintf(menu + 0x400, g_str_string_format, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, g_str_count_format, g_bolt_count);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)g_grid_label_x_shift,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, g_str_grid_label_format, GetLocalizedString(0x2DBB), g_bolt_count);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xACF));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xACF));
        break;
    }
    text_label_draw(menu + 0x2E0);
    if (*(int *)(menu + 0x444) == sel) {
        object_set_flag_value(menu + 0x210, 1);
        object_set_first_float4(menu + 0x210, (*(float **)(menu + 0x430))[0] + -117.0f,
                      (*(float **)(menu + 0x430))[1] + 3.0f, 0.0f, 0.0f);
        text_label_draw(menu + 0x210);
    }
    if (sel == 0) {
        int x = (*(float **)(menu + 0x430))[0];
        int y = (*(float **)(menu + 0x430))[1];
        AppendScreenRectPacket(x + g_grid_label_rect_left, y + g_grid_label_rect_top, x + g_grid_label_rect_right, y + g_grid_label_rect_bottom,
                      0x55F0C070, 0);
    }
}
