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
extern void func_US2_00344558(void *a0);
extern void func_US2_003444E8(void *a0);
extern int UpdateListSelection(void *a0, int a1);

void func_US2_003446B8(char *self, int arg)
{
    f32_F7036ef03 *v;
    char *sub = self + 712;

    v = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self, g_item_menu_first_offset_x + v[0], g_item_menu_first_offset_y + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 76, g_item_menu_second_offset_x + v[0], g_item_menu_second_offset_y + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 152, g_item_menu_third_offset_x + v[0], g_item_menu_third_offset_y + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    object_set_first_float4(self + 608, g_item_menu_fourth_offset_x + v[0], g_item_menu_fourth_offset_y + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    menu_list_set_position(sub, g_item_menu_list_offset_x + v[0], g_item_menu_list_offset_y + v[1]);
    func_US2_00344558(self);
    func_US2_003444E8(self);
    *(int *)(self + 416) = UpdateListSelection(sub, arg);
}
