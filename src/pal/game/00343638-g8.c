#include "include_asm.h"
#include "names.h"

extern float g_tab_menu_cursor_step_y __attribute__((sda));
extern float g_tab_menu_cursor_base_y;
extern float g_tab_menu_cursor_offset_x __attribute__((sda));
extern void object_set_first_float4(void *, float, float, float, float);

/* Moves the tab menu cursor to the row of the current tab selection (PAL). */
void tab_menu_update_cursor_pal(char *self)
{
    int index = *(int *)(self + 0x31C);
    float *position = *(float **)(self + 0x228);
    int *base = (int *)(self + (index << 2));

    object_set_first_float4(self + 0x130, g_tab_menu_cursor_offset_x + position[0],
            (g_tab_menu_cursor_base_y + g_tab_menu_cursor_step_y * (float)base[0x6E]) + position[1],
            0.0f, 0.0f);
}

extern float g_tab_menu_list_offset_x __attribute__((sda));
extern float g_tab_menu_list_offset_y;
extern float g_tab_menu_list_setting_first __attribute__((sda));
extern float g_tab_menu_list_setting_second __attribute__((sda));
extern void menu_set_position_pal(void *, float, float);
extern void menu_set_settings_pal(void *, int, int);
extern void *UpdateMenuListSelection_pal(void *, int);
extern int menu_get_selected_index_pal(void *);
extern int math_ping_pong_blend_values_pal(int, int, int, int, int);

/* Updates the tab menu list: positions it, handles input and plays a sound when the selection changes (PAL). */
void tab_menu_update_list_pal(char *self, int input)
{
    char *indices = self + 0x1B8;
    char *child = self + 0x238;
    int old;
    float *position = *(float **)(self + 0x228);
    menu_set_position_pal(child, position[0] + g_tab_menu_list_offset_x, position[1] + g_tab_menu_list_offset_y);
    menu_set_settings_pal(child, (int)g_tab_menu_list_setting_first, (int)g_tab_menu_list_setting_second);
    UpdateMenuListSelection_pal(child, input);
    old = *(int *)(indices + (*(int *)(self + 0x31C) << 2));
    *(int *)(indices + (*(int *)(self + 0x31C) << 2)) = menu_get_selected_index_pal(child);
    indices += *(int *)(self + 0x31C) << 2;
    if (old != *(int *)indices)
        math_ping_pong_blend_values_pal(0, 0, 1, 0, 1);
}
