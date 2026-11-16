#include "include_asm.h"
#include "names.h"
extern void menu_set_settings(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[];
extern char *g_resident_data_base[] __attribute__((sda));
extern float g_small_list_value_float __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void list_menu_reset_attach_items(void *, void *);
extern int list_menu_set_selection(void *, int);

/* Sets up the small list menu: position, two widgets and the list, then selects the first entry (PAL). */
void small_list_menu_init_pal(char *object, void *parent)
{
    int *allocation;
    char *first, *second, *widget;
    *(void **)(object + 4) = parent;
    if (parent) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)object = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)object = 250.0f;
    (*(float **)object)[1] = 120.0f;
    first = object + 0xEC;
    second = object + 0x138;
    widget = object + 0x10;
    object_init_derived_arrays(first, g_menu_widget_desc_first, parent);
    object_init_derived_arrays(second, g_menu_widget_desc_second, parent);
    *object_get_fourth_field(first) = 0x60442D00;
    *object_get_fourth_field(second) = 0x55F0C070;
    object_set_helper_result(first, g_resident_data_base[0] + 0x8710, 0x73);
    object_set_helper_result(second, g_resident_data_base[0] + 0x8710, 0x74);
    object_set_value_float(first, g_small_list_value_float);
    object_set_value_float(second, g_small_list_value_float);
    list_menu_reset_attach_items(widget, parent);
    menu_set_settings(widget, 11, 60);
    list_menu_set_selection(object, 0);
}

extern void object_set_first_float4(void *, float, float, float, float);
extern int menu_get_entry_count_pal(void *);
extern float g_small_list_row_spacing __attribute__((sda));
extern float g_small_list_text_x_offset __attribute__((sda));
extern int g_menu_input_flags[];
extern int list_menu_get_selection_pal(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void option_list_draw_rows_pal(void *);
extern int math_ping_pong_blend_values_pal(int, int, int, int, int);

/* Draws the rows of the small list menu, highlighting the selected one (PAL). */
void small_list_menu_draw_rows_pal(char *self)
{
    int count = menu_get_entry_count_pal(self + 0x10);
    int i;
    int *slot;

    if (g_menu_input_flags[0] & 0x5000)
        math_ping_pong_blend_values_pal(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        object_set_first_float4(self + 0xEC, (*(float **)self)[0] + g_small_list_text_x_offset,
                      (*(float **)self)[1] + g_small_list_row_spacing * step, 0.0f, 0.0f);
        object_set_first_float4(self + 0x138, (*(float **)self)[0] + g_small_list_text_x_offset,
                      (*(float **)self)[1] + g_small_list_row_spacing * step, 0.0f, 0.0f);
        slot = object_get_fourth_field(self + 0x138);
        *slot = list_menu_get_selection_pal(self) == i ? math_ping_pong_blend_values_pal(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        gfx_draw_screen_element_stored(self + 0xEC);
        gfx_draw_screen_element_stored(self + 0x138);
    }
    option_list_draw_rows_pal(self + 0x10);
}
