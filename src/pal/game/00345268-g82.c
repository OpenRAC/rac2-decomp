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
extern void menu_update_title_text_pal(void *a0);
extern void menu_update_empty_label_pal(void *a0);
extern int UpdateListSelection(void *a0, int a1);

/* Updates the item menu: places its four parts and list, refreshes title and empty label, returns the list selection (PAL copy). */
int item_menu_update_pal(char *self, int arg)
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
    menu_update_title_text_pal(self);
    menu_update_empty_label_pal(self);
    return *(int *)(self + 416) = UpdateListSelection(list, arg);
}
