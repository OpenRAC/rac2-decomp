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

/* Sets up a small list menu: its position, two widgets and the list. */
void small_list_menu_init_us2(char *object, void *argument)
{
    int *allocation;
    char *first, *second, *widget;
    *(void **)(object + 4) = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
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
    object_init_derived_arrays(first, g_menu_widget_desc_first, argument);
    object_init_derived_arrays(second, g_menu_widget_desc_second, argument);
    *object_get_fourth_field(first) = 0x60442D00;
    *object_get_fourth_field(second) = 0x55F0C070;
    object_set_helper_result(first, g_resident_data_base[0] + 0x8710, 0x73);
    object_set_helper_result(second, g_resident_data_base[0] + 0x8710, 0x74);
    object_set_value_float(first, g_small_list_value_float);
    object_set_value_float(second, g_small_list_value_float);
    list_menu_reset_attach_items(widget, argument);
    menu_set_settings(widget, 11, 60);
    list_menu_set_selection(object, 0);
}
