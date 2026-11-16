#include "include_asm.h"
#include "names.h"

extern int info_panel_update_us2(char *, int);
extern char g_circle_menu_icon_data[];
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_us2(void *, void *, void *);
extern void hud_init_widget_defaults_us2(void *, void *, void *);
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

/* Builds the info panel: the prompt bar, the labels, the icon and the three count lines, then fills them in. (USA v2.00) */
void info_panel_init_us2(char *object, void *owner)
{
    int *allocation;
    char *text_a;
    char *text_b;
    char *text_c;
    char *text_d;
    char *text_e;
    char *bar;
    char *text_g;
    char *icon;
    char *count_a;
    char *count_b;
    char *count_c;
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
    text_a = object + 0x318;
    text_b = object + 0x370;
    text_c = object + 0x3C8;
    text_d = object + 0x628;
    text_e = object + 0x5D0;
    bar = object + 0x420;
    text_g = object + 0x578;
    icon = object + 0x2DC;
    color = 0x80F0F0F0;
    prompt_bar_init_us2(object + 8, owner, g_info_panel_prompt_ids);
    table = g_circle_menu_icon_data;
    hud_init_widget_defaults_us2(text_a, table, owner);
    hud_init_widget_defaults_us2(text_b, table, owner);
    count_a = object + 0x470;
    count_b = object + 0x4C8;
    hud_init_widget_defaults_us2(text_c, table, owner);
    count_c = object + 0x520;
    hud_init_widget_defaults_us2(text_d, table, owner);
    hud_init_widget_defaults_us2(text_e, table, owner);
    object_init_derived_arrays(bar, table, owner);
    hud_init_widget_defaults_us2(text_g, table, owner);
    hud_set_widget_field_b(text_e, object + 0x680);
    hud_set_widget_field_b(text_g, GetLocalizedString(0x333E));
    object_set_second_float4(text_g, 0.9f, 0.9f, 0.0f, 0.0f);
    hud_set_widget_field_b(text_a, GetLocalizedString(0x2BE5));
    hud_set_widget_field_b(text_b, GetLocalizedString(0x3129));
    hud_set_widget_field_b(text_c, GetLocalizedString(0x2C67));
    hud_set_widget_field_a(text_a, 0);
    hud_set_widget_field_a(text_b, 0);
    hud_set_widget_field_a(text_c, 0);
    *object_get_fourth_field(text_a) = color;
    *object_get_fourth_field(text_b) = color;
    *object_get_fourth_field(text_c) = color;
    *object_get_fourth_field(text_d) = color;
    *object_get_fourth_field(text_e) = color;
    *object_get_fourth_field(text_g) = color;
    *object_get_fourth_field(bar) = 0x55F0C070;
    object_init_derived_c(icon, table, owner);
    hud_set_widget_value_pair(icon, 0xEAA2, 0);
    object_set_second_float4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(icon) = 0x60F0F0B0;
    object_set_helper_result(bar, g_resident_data_base + 0x8710, 0x5D);
    hud_init_widget_defaults_us2(count_a, g_info_panel_count_desc_first, *(void **)object);
    hud_init_widget_defaults_us2(count_b, g_info_panel_count_desc_second, *(void **)object);
    hud_init_widget_defaults_us2(count_c, g_info_panel_count_desc_third, *(void **)object);
    *object_get_fourth_field(count_a) = color;
    *object_get_fourth_field(count_b) = color;
    *object_get_fourth_field(count_c) = color;
    hud_set_widget_field_b(count_a, object + 0x6C0);
    hud_set_widget_field_b(count_b, object + 0x6D8);
    hud_set_widget_field_b(count_c, object + 0x6F0);
    info_panel_update_us2(object, 0);
}

extern void prompt_bar_update_us2(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern void info_panel_place_counters_us2(void *);
extern int DrawMapScreen_us2(int);
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

/* Places the info panel's parts around its anchor and sets the location name and label text. (USA v2.00) */
int info_panel_update_us2(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x628;
    char *state;
    int text;
    float x, y;

    prompt_bar_update_us2(child);
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
    info_panel_place_counters_us2(object);
    DrawMapScreen_us2(0);
    return (flags >> 6) & 1;
}
