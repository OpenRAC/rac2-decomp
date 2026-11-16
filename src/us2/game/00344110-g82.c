#include "include_asm.h"
#include "names.h"

typedef float f32_F7036ef03;
extern f32_F7036ef03 g_item_menu_first_offset_x __attribute__((sda));
extern f32_F7036ef03 g_item_menu_second_offset_x __attribute__((sda));
extern f32_F7036ef03 g_item_menu_third_offset_x __attribute__((sda));
extern f32_F7036ef03 g_item_menu_fourth_offset_x __attribute__((sda));
extern f32_F7036ef03 g_item_menu_list_offset_x __attribute__((sda));
extern f32_F7036ef03 g_item_menu_first_offset_y;
extern f32_F7036ef03 g_item_menu_second_offset_y;
extern f32_F7036ef03 g_item_menu_third_offset_y;
extern f32_F7036ef03 g_item_menu_fourth_offset_y;
extern f32_F7036ef03 g_item_menu_list_offset_y;
extern void object_set_first_float4(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void menu_list_set_position(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);
extern void menu_update_title_text_us2(void *a0);
extern void menu_update_empty_label_us2(void *a0);
extern int UpdateListSelection(void *a0, int a1);

/* Positions the menu's widgets and list, refreshes the title and empty label, and updates the list selection (USA v2.00 item_menu_update). */
void item_menu_update_us2(char *self, int buttons)
{
    f32_F7036ef03 *position;
    char *list = self + 712;

    position = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self, g_item_menu_first_offset_x + position[0], g_item_menu_first_offset_y + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 76, g_item_menu_second_offset_x + position[0], g_item_menu_second_offset_y + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 152, g_item_menu_third_offset_x + position[0], g_item_menu_third_offset_y + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 608, g_item_menu_fourth_offset_x + position[0], g_item_menu_fourth_offset_y + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 696);
    menu_list_set_position(list, g_item_menu_list_offset_x + position[0], g_item_menu_list_offset_y + position[1]);
    menu_update_title_text_us2(self);
    menu_update_empty_label_us2(self);
    *(int *)(self + 416) = UpdateListSelection(list, buttons);
}
