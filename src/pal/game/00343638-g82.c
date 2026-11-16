#include "include_asm.h"
#include "names.h"

typedef float f32_Fd368add8;
extern f32_Fd368add8 g_tab_menu_first_x __attribute__((sda));
extern f32_Fd368add8 g_tab_menu_third_x __attribute__((sda));
extern f32_Fd368add8 g_tab_menu_second_x __attribute__((sda));
extern f32_Fd368add8 g_tab_menu_fourth_x __attribute__((sda));
extern f32_Fd368add8 g_tab_menu_fifth_x __attribute__((sda));
extern f32_Fd368add8 g_tab_menu_first_y;
extern f32_Fd368add8 g_tab_menu_third_y;
extern f32_Fd368add8 g_tab_menu_second_y;
extern f32_Fd368add8 g_tab_menu_fourth_y;
extern f32_Fd368add8 g_tab_menu_fifth_y;
extern void object_set_first_float4(void *a0, f32_Fd368add8 a1, f32_Fd368add8 a2, f32_Fd368add8 a3, f32_Fd368add8 a4);
extern void *object_get_fourth_field(void *a0);
extern int math_ping_pong_blend_values_pal(int a0, int a1, int a2, int a3, int a4);
extern void tab_menu_update_list_pal(void *a0, int a1);
extern void tab_menu_update_cursor_pal(void *a0);
extern void ref_L00_003418C0_00(void *a0);

/* Updates the tab menu: places its widgets, updates the cursor and the list, and returns the selected entry (PAL). */
int tab_menu_update_pal(char *self, int input)
{
    f32_Fd368add8 *position;

    position = *(f32_Fd368add8 **)(self + 552);
    object_set_first_float4(self, g_tab_menu_first_x + position[0], g_tab_menu_first_y + position[1], 0.0f, 0.0f);
    position = *(f32_Fd368add8 **)(self + 552);
    object_set_first_float4(self + 152, g_tab_menu_third_x + position[0], g_tab_menu_third_y + position[1], 0.0f, 0.0f);
    position = *(f32_Fd368add8 **)(self + 552);
    object_set_first_float4(self + 76, g_tab_menu_second_x + position[0], g_tab_menu_second_y + position[1], 0.0f, 0.0f);
    position = *(f32_Fd368add8 **)(self + 552);
    object_set_first_float4(self + 228, g_tab_menu_fourth_x + position[0], g_tab_menu_fourth_y + position[1], 0.0f, 0.0f);
    position = *(f32_Fd368add8 **)(self + 552);
    object_set_first_float4(self + 464, g_tab_menu_fifth_x + position[0], g_tab_menu_fifth_y + position[1], 0.0f, 0.0f);

    *(int *)object_get_fourth_field(self + 304) = math_ping_pong_blend_values_pal(0x60442D00, 0x70FFFEED, 20, 0, 0);
    tab_menu_update_list_pal(self, input);
    tab_menu_update_cursor_pal(self);
    ref_L00_003418C0_00(self);
    return *(int *)(self + (*(int *)(self + 796) << 2) + 440);
}
