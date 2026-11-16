#include "names.h"
/* The x offsets use small-data loads; incomplete SDA y declarations retain
 * the absolute macro loads without claiming an unmeasured array extent. */
extern void prompt_bar_update(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void info_panel_place_counters(void *);
extern int DrawMapScreen(int);
extern char g_map_overlay_state[], g_circle_menu_icon_data[];
extern int g_menu_text_id_table[];
extern float g_info_panel_offset_x_first __attribute__((sda));
extern float g_info_panel_offset_y_first[] __attribute__((sda));
extern float g_info_panel_offset_x_second __attribute__((sda));
extern float g_info_panel_offset_y_second[] __attribute__((sda));
extern float g_info_panel_offset_x_third __attribute__((sda));
extern float g_info_panel_offset_y_third[] __attribute__((sda));
extern float g_info_panel_offset_x_fourth __attribute__((sda));
extern float g_info_panel_offset_y_fourth[] __attribute__((sda));
extern float g_info_panel_offset_x_fifth __attribute__((sda));
extern float g_info_panel_offset_y_fifth[] __attribute__((sda));
extern float g_info_panel_offset_x_sixth __attribute__((sda));
extern float g_info_panel_offset_y_sixth[] __attribute__((sda));
extern float g_info_panel_offset_x_seventh __attribute__((sda));
extern float g_info_panel_offset_y_seventh[] __attribute__((sda));
/* Updates the info panel: moves every part into place and shows the text for the selected item. */
int info_panel_update(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x578;
    char *state;
    int text;
    float x, y;

    prompt_bar_update(child);
    menu_set_anchor_pos(child, (*(float **)(object + 0x2A8))[0], (*(float **)(object + 0x2A8))[1]);
    x = g_info_panel_offset_x_first + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_first[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x2E8, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_second + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_second[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x330, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_third + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_third[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x378, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_sixth + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_sixth[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x2AC, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_seventh + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_seventh[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x3C0, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_fifth + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_fifth[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(label, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_fourth + (*(float **)(object + 0x2A8))[0];
    y = g_info_panel_offset_y_fourth[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x530, x, y, 0.0f, 0.0f);
    state = g_map_overlay_state;
    text_format_location_name(object + 0x5C0, *(int *)(state + 0x230));
    text = g_menu_text_id_table[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        hud_set_widget_field_b(label, GetLocalizedString(text));
    else
        hud_set_widget_field_b(label, g_circle_menu_icon_data);
    info_panel_place_counters(object);
    DrawMapScreen(0);
    return (flags >> 6) & 1;
}
