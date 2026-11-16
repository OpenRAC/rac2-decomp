#include "include_asm.h"
#include "names.h"
extern float g_tab_menu_list_offset_x __attribute__((sda));
extern float g_tab_menu_list_offset_y;
extern float g_tab_menu_list_setting_first __attribute__((sda));
extern float g_tab_menu_list_setting_second __attribute__((sda));
extern void menu_set_position(void *, float, float);
extern void menu_set_settings(void *, int, int);
extern void *UpdateMenuListSelection(void *, int);
extern int menu_get_selected_index(void *);
extern int math_ping_pong_blend_values(int, int, int, int, int);

void tab_menu_update_list_us2(char *self, int arg)
{
    char *indices = self + 0x1B8;
    char *child = self + 0x238;
    int old;
    float *position = *(float **)(self + 0x228);
    menu_set_position(child, position[0] + g_tab_menu_list_offset_x, position[1] + g_tab_menu_list_offset_y);
    menu_set_settings(child, (int)g_tab_menu_list_setting_first, (int)g_tab_menu_list_setting_second);
    UpdateMenuListSelection(child, arg);
    old = *(int *)(indices + (*(int *)(self + 0x31C) << 2));
    *(int *)(indices + (*(int *)(self + 0x31C) << 2)) = menu_get_selected_index(child);
    indices += *(int *)(self + 0x31C) << 2;
    if (old != *(int *)indices)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
}

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
extern void func_00335E38_1(void *a0, f32_Fd368add8 a1, f32_Fd368add8 a2, f32_Fd368add8 a3, f32_Fd368add8 a4);
extern void *func_00335E20_1(void *a0);
extern int math_ping_pong_blend_values(int a0, int a1, int a2, int a3, int a4);
extern void tab_menu_update_list(void *a0, int a1);
extern void tab_menu_position_cursor(void *a0);
extern void ref_L00_003418C0_00(void *a0);

int tab_menu_update_us2(char *self, int arg1)
{
    f32_Fd368add8 *v;

    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38_1(self, g_tab_menu_first_x + v[0], g_tab_menu_first_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38_1(self + 152, g_tab_menu_third_x + v[0], g_tab_menu_third_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38_1(self + 76, g_tab_menu_second_x + v[0], g_tab_menu_second_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38_1(self + 228, g_tab_menu_fourth_x + v[0], g_tab_menu_fourth_y + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38_1(self + 464, g_tab_menu_fifth_x + v[0], g_tab_menu_fifth_y + v[1], 0.0f, 0.0f);

    *(int *)func_00335E20_1(self + 304) = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    tab_menu_update_list(self, arg1);
    tab_menu_position_cursor(self);
    ref_L00_003418C0_00(self);
    return *(int *)(self + (*(int *)(self + 796) << 2) + 440);
}
