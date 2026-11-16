#include "include_asm.h"
#include "names.h"

extern int info_panel_update_pal(char *, int);
extern char g_circle_menu_icon_data[];
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
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

void info_panel_init_pal(char *object, void *owner)
{
    int *allocation;
    char *a;
    char *b;
    char *c;
    char *d;
    char *e;
    char *f;
    char *g;
    char *h;
    char *i;
    char *j;
    char *k;
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
    a = object + 0x318;
    b = object + 0x370;
    c = object + 0x3C8;
    d = object + 0x628;
    e = object + 0x5D0;
    f = object + 0x420;
    g = object + 0x578;
    h = object + 0x2DC;
    color = 0x80F0F0F0;
    prompt_bar_init_pal(object + 8, owner, g_info_panel_prompt_ids);
    table = g_circle_menu_icon_data;
    func_PAL_00338688(a, table, owner);
    func_PAL_00338688(b, table, owner);
    i = object + 0x470;
    j = object + 0x4C8;
    func_PAL_00338688(c, table, owner);
    k = object + 0x520;
    func_PAL_00338688(d, table, owner);
    func_PAL_00338688(e, table, owner);
    object_init_derived_arrays(f, table, owner);
    func_PAL_00338688(g, table, owner);
    hud_set_widget_field_b(e, object + 0x680);
    hud_set_widget_field_b(g, GetLocalizedString(0xAD2));
    object_set_second_float4(g, 0.9f, 0.9f, 0.0f, 0.0f);
    hud_set_widget_field_b(a, GetLocalizedString(0xB60));
    hud_set_widget_field_b(b, GetLocalizedString(0x1B61));
    hud_set_widget_field_b(c, GetLocalizedString(0xBE2));
    hud_set_widget_field_a(a, 0);
    hud_set_widget_field_a(b, 0);
    hud_set_widget_field_a(c, 0);
    *object_get_fourth_field(a) = color;
    *object_get_fourth_field(b) = color;
    *object_get_fourth_field(c) = color;
    *object_get_fourth_field(d) = color;
    *object_get_fourth_field(e) = color;
    *object_get_fourth_field(g) = color;
    *object_get_fourth_field(f) = 0x55F0C070;
    object_init_derived_c(h, table, owner);
    hud_set_widget_value_pair(h, 0xEAA2, 0);
    object_set_second_float4(h, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(h) = 0x60F0F0B0;
    object_set_helper_result(f, g_resident_data_base + 0x8710, 0x5D);
    func_PAL_00338688(i, g_info_panel_count_desc_first, *(void **)object);
    func_PAL_00338688(j, g_info_panel_count_desc_second, *(void **)object);
    func_PAL_00338688(k, g_info_panel_count_desc_third, *(void **)object);
    *object_get_fourth_field(i) = color;
    *object_get_fourth_field(j) = color;
    *object_get_fourth_field(k) = color;
    hud_set_widget_field_b(i, object + 0x6C0);
    hud_set_widget_field_b(j, object + 0x6D8);
    hud_set_widget_field_b(k, object + 0x6F0);
    info_panel_update_pal(object, 0);
}

extern void prompt_bar_update_pal(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern void func_PAL_00340C88(void *);
extern int func_PAL_002D7B68(int);
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
    func_PAL_00340C88(object);
    func_PAL_002D7B68(0);
    return (flags >> 6) & 1;
}
