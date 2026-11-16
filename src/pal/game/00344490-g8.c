#include "include_asm.h"
#include "names.h"
extern float g_list_menu_input_child_x_offset __attribute__((sda));
extern float g_list_menu_input_child_y_offset;
extern float g_list_menu_child_setting_first __attribute__((sda));
extern float g_list_menu_child_setting_second __attribute__((sda));
extern void menu_set_position(void *, float, float);
extern void menu_set_settings(void *, int, int);
extern void *UpdateMenuListSelection(void *, int);
extern int menu_get_selected_index(void *);

void list_menu_update_from_input_pal(char *self, int arg)
{
    char *child = self + 0x188;
    float *position = *(float **)(self + 0x180);
    menu_set_position(child, position[0] + g_list_menu_input_child_x_offset, position[1] + g_list_menu_input_child_y_offset);
    menu_set_settings(child, (int)g_list_menu_child_setting_first, (int)g_list_menu_child_setting_second);
    UpdateMenuListSelection(child, arg);
    *(int *)(self + 0x16C) = menu_get_selected_index(child);
}

extern void object_set_first_float4(void *, float, float, float, float);
extern float g_list_menu_label_x_offset __attribute__((sda));
extern float g_list_menu_label_y_offset;
extern float g_list_menu_item_x_offset __attribute__((sda));
extern float g_list_menu_item_y_offset;
extern float g_list_menu_scales[2] __attribute__((sda));
extern int menu_get_entry_count(void *);
extern void object_set_value_float(void *, float);
extern void list_menu_noop_hook(void *);

int list_menu_update_pal(char *self, int arg)
{
    char *child = self + 0x4C;
    float *position = *(float **)(self + 0x180);
    float *scale;
    unsigned int index;
    object_set_first_float4(self, g_list_menu_label_x_offset + position[0], g_list_menu_label_y_offset + position[1], 0.0f, 0.0f);
    position = *(float **)(self + 0x180);
    object_set_first_float4(child, g_list_menu_item_x_offset + position[0], g_list_menu_item_y_offset + position[1], 0.0f, 0.0f);
    index = menu_get_entry_count(self + 0x188) - 1;
    scale = (float *)((char *)g_list_menu_scales + (index << 2));
    object_set_value_float(self, *scale);
    object_set_value_float(child, *scale);
    list_menu_update_from_input(self, arg);
    list_menu_position_cursor(self);
    list_menu_noop_hook(self);
    return *(int *)(self + 0x16C);
}
