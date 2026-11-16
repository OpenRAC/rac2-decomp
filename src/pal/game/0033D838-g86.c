#include "include_asm.h"
#include "names.h"

extern int info_panel_update_pal(char *, int);
extern char g_circle_menu_icon_data[];
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern void object_init_derived_arrays(void *, void *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_a(void *, int);
extern unsigned int *object_get_fourth_field(void *);
extern void object_init_derived_c(void *, void *, void *);
extern void hud_set_widget_value_pair(void *, int, int);
extern void object_set_helper_result(void *, void *, int);
extern int g_info_panel_prompt_ids[2] __attribute__((sda));
extern char *g_resident_data_base;
extern char g_info_panel_count_desc_header[], g_info_panel_count_desc_first[], g_info_panel_count_desc_second[], g_info_panel_count_desc_third[];

/* Sets up the info panel: prompt bar, labels, location name and the three save counters (PAL). */
void info_panel_init_pal(char *object, void *owner)
{
    int *allocation;
    char *label_1;
    char *label_2;
    char *label_3;
    char *location_label;
    char *location_name;
    char *image;
    char *heading;
    char *cursor;
    char *count_1;
    char *count_2;
    char *count_3;
    char *table;
    unsigned int color;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    (*(float **)(object + 0x2D8))[0] = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 200.0f;
    label_1 = object + 0x318;
    label_2 = object + 0x370;
    label_3 = object + 0x3C8;
    location_label = object + 0x628;
    location_name = object + 0x5D0;
    image = object + 0x420;
    heading = object + 0x578;
    cursor = object + 0x2DC;
    color = 0x80F0F0F0;
    prompt_bar_init_pal(object + 8, owner, g_info_panel_prompt_ids);
    table = g_circle_menu_icon_data;
    hud_init_widget_defaults_pal(label_1, table, owner);
    hud_init_widget_defaults_pal(label_2, table, owner);
    count_1 = object + 0x470;
    count_2 = object + 0x4C8;
    hud_init_widget_defaults_pal(label_3, table, owner);
    count_3 = object + 0x520;
    hud_init_widget_defaults_pal(location_label, table, owner);
    hud_init_widget_defaults_pal(location_name, table, owner);
    object_init_derived_arrays(image, table, owner);
    hud_init_widget_defaults_pal(heading, table, owner);
    hud_set_widget_field_b(location_name, object + 0x680);
    hud_set_widget_field_b(heading, GetLocalizedString(0xAD2));
    object_set_second_float4(heading, 0.9f, 0.9f, 0.0f, 0.0f);
    hud_set_widget_field_b(label_1, GetLocalizedString(0xB60));
    hud_set_widget_field_b(label_2, GetLocalizedString(0x1B61));
    hud_set_widget_field_b(label_3, GetLocalizedString(0xBE2));
    hud_set_widget_field_a(label_1, 0);
    hud_set_widget_field_a(label_2, 0);
    hud_set_widget_field_a(label_3, 0);
    *object_get_fourth_field(label_1) = color;
    *object_get_fourth_field(label_2) = color;
    *object_get_fourth_field(label_3) = color;
    *object_get_fourth_field(location_label) = color;
    *object_get_fourth_field(location_name) = color;
    *object_get_fourth_field(heading) = color;
    *object_get_fourth_field(image) = 0x55F0C070;
    object_init_derived_c(cursor, table, owner);
    hud_set_widget_value_pair(cursor, 0xEAA2, 0);
    object_set_second_float4(cursor, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(cursor) = 0x60F0F0B0;
    object_set_helper_result(image, g_resident_data_base + 0x8710, 0x5D);
    hud_init_widget_defaults_pal(count_1, g_info_panel_count_desc_first, *(void **)object);
    hud_init_widget_defaults_pal(count_2, g_info_panel_count_desc_second, *(void **)object);
    hud_init_widget_defaults_pal(count_3, g_info_panel_count_desc_third, *(void **)object);
    *object_get_fourth_field(count_1) = color;
    *object_get_fourth_field(count_2) = color;
    *object_get_fourth_field(count_3) = color;
    hud_set_widget_field_b(count_1, object + 0x6C0);
    hud_set_widget_field_b(count_2, object + 0x6D8);
    hud_set_widget_field_b(count_3, object + 0x6F0);
    info_panel_update_pal(object, 0);
}

extern void prompt_bar_update_pal(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern void info_panel_place_counters_pal(void *);
extern int DrawMapScreen_pal(int);
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

/* Updates the info panel: positions its parts, refreshes the location name and the counters (PAL). */
int info_panel_update_pal(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x628;
    char *state;
    int text;
    float x, y;

    prompt_bar_update_pal(child);
    menu_set_anchor_pos(child, (*(float **)(object + 0x2D8))[0], (*(float **)(object + 0x2D8))[1]);
    x = g_info_panel_offset_x_first + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_first[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x318, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_second + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_second[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x370, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_third + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_third[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x3C8, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_sixth + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_sixth[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x2DC, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_seventh + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_seventh[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x420, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_fifth + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_fifth[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(label, x, y, 0.0f, 0.0f);
    x = g_info_panel_offset_x_fourth + (*(float **)(object + 0x2D8))[0];
    y = g_info_panel_offset_y_fourth[0] + (*(float **)(object + 0x2D8))[1];
    object_set_first_float4(object + 0x5D0, x, y, 0.0f, 0.0f);
    state = g_map_overlay_state;
    text_format_location_name(object + 0x680, *(int *)(state + 0x230));
    text = g_menu_text_id_table[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        hud_set_widget_field_b(label, GetLocalizedString(text));
    else
        hud_set_widget_field_b(label, g_circle_menu_icon_data);
    info_panel_place_counters_pal(object);
    DrawMapScreen_pal(0);
    return (flags >> 6) & 1;
}
