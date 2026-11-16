#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_pal(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, int, int, int);
extern void prompt_bar_set_text_offsets_pal(void *, float, float, float, float, float, float);
extern int audio_menu_update_pal(void *, int);
extern int g_audio_menu_prompt_ids[2] __attribute__((sda));
extern char g_circle_menu_icon_data[];
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void func_PAL_003388E8(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, int);
extern void widget_store_field(void *, int);

/* Sets up the audio menu: prompt bar, two volume meters and the first update (PAL). */
void audio_menu_init_pal(char *object, void *argument)
{
    int *allocation;
    char *child, *widget, *second_widget;
    void *table;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x36C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x36C) = 255.0f;
    (*(float **)(object + 0x36C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2DC;
    second_widget = object + 0x324;
    prompt_bar_init_pal(child, argument, g_audio_menu_prompt_ids);
    text = GetLocalizedString(0xBA8);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.67f);
    table = g_circle_menu_icon_data;
    object_init_derived_b(widget, 150, 1, table, argument);
    widget_set_pos_y(widget, 16);
    func_PAL_003388E8(widget, 0x400);
    meter_set_value(widget, 0);
    object_set_first_pair(widget, 0x55F0C070, 0x55F0C070);
    object_set_second_pair(widget, 0x60442D00, 0x60442D00);
    text_set_alignment(widget, 0x20FFFFFF);
    widget_store_field(widget, 0);
    object_init_derived_b(second_widget, 150, 1, table, argument);
    widget_set_pos_y(second_widget, 16);
    func_PAL_003388E8(second_widget, 0x400);
    meter_set_value(second_widget, 0);
    object_set_first_pair(second_widget, 0x55F0C070, 0x55F0C070);
    object_set_second_pair(second_widget, 0x60442D00, 0x60442D00);
    text_set_alignment(second_widget, 0x20FFFFFF);
    widget_store_field(second_widget, 0);
    *(int *)(object + 0x2D8) = 0;
    audio_menu_update_pal(object, 0);
}

extern int list_page_update_pal(void *, int);
extern int g_list_page_prompt_ids[2] __attribute__((sda));
extern void list_menu_reset_attach_items_pal(void *, void *);
extern void menu_set_settings_pal(void *, int, int);
extern void menu_set_field_c8_pal(void *, int);

/* Sets up the list page: prompt bar, the option list and the first update (PAL). */
void list_page_init_pal(char *object, void *argument)
{
    int *allocation;
    char *child, *widget;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x3BC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x3BC) = 255.0f;
    (*(float **)(object + 0x3BC))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2E0;
    prompt_bar_init_pal(child, argument, g_list_page_prompt_ids);
    text = GetLocalizedString(0xBB1);
    second = GetLocalizedString(0xB86);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    list_menu_reset_attach_items_pal(widget, argument);
    menu_set_settings_pal(widget, -83, 32);
    menu_set_field_c8_pal(widget, 1);
    list_page_update_pal(object, 0);
}

extern void prompt_bar_draw_pal(char *);
extern void menu_set_field_bc_pal(char *, int);
extern void option_list_draw_rows_pal(char *);
extern unsigned char g_language;
extern int g_list_page_field_table[2] __attribute__((sda));

/* Draws the list page: the prompt bar and the option list rows (PAL). */
void list_page_draw_pal(char *object)
{
    char *list;
    prompt_bar_draw_pal(object + 8);
    list = object + 0x2E0;
    menu_set_field_bc_pal(list, g_list_page_field_table[g_language]);
    option_list_draw_rows_pal(list);
}

extern int simple_page_update_pal(void *, int);
extern int g_simple_page_prompt_ids[2] __attribute__((sda));

/* Sets up the simple page: prompt bar with its text and the first update (PAL). */
void simple_page_init_pal(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2D8) = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 208.0f;
    child = object + 8;
    prompt_bar_init_pal(child, argument, g_simple_page_prompt_ids);
    text = GetLocalizedString(0xC31);
    prompt_bar_set_texts_pal(child, text, 0, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, -128.0f, -183.0f, 112.0f, 110.0f, 102.0f, 110.0f);
    simple_page_update_pal(object, 0);
}

extern void object_set_first_float4(char *p, float x, float y, float zero, float zero2);
extern float g_info_panel_counter_x0 __attribute__((sda));
extern float g_info_panel_counter_x1 __attribute__((sda));
extern float g_info_panel_counter_x2 __attribute__((sda));
extern float g_info_panel_counter_offset_x __attribute__((sda));
extern float g_info_panel_counter_y0;
extern float g_info_panel_counter_y1;
extern float g_info_panel_counter_y2;
extern float g_info_panel_counter_offset_y;
struct pos {
    float x;
    float y;
};

/* Places the four counter text objects relative to the info panel position (PAL). */
void info_panel_place_counters_pal(char *self)
{
    float zero = 0.0f;

    object_set_first_float4(self + 1400, g_info_panel_counter_offset_x + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_offset_y + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1136, g_info_panel_counter_x0 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y0 + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1224, g_info_panel_counter_x1 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y1 + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1312, g_info_panel_counter_x2 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y2 + (*(struct pos **)(self + 728))->y, zero, zero);
}
