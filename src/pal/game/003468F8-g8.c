#include "include_asm.h"
#include "names.h"

extern void DrawItemGrid(int *);
extern char g_help_pending_entries[];
extern int g_item_grid_third_mode_desc_a __attribute__((sda));
extern int g_item_grid_third_mode_desc_b __attribute__((sda));
extern int g_item_grid_third_mode_desc_c __attribute__((sda));
extern int g_item_grid_third_mode_desc_d __attribute__((sda));
extern int g_item_grid_third_mode_desc_e __attribute__((sda));
extern int g_item_grid_third_mode_desc_f __attribute__((sda));
extern int g_item_grid_third_mode_desc_g __attribute__((sda));

/* Draws the item grid in its third mode, highlighted while the menu mode is 2. */
void item_grid_draw_third_mode_pal(char *menu)
{
    int params[23];

    params[16] = 0;
    params[14] = 0;
    params[11] = 0;
    params[13] = 0;
    params[20] = 0;

    params[21] = 1;
    params[19] = *(int *)(menu + 0x4B4);
    params[21] = *(int *)(menu + 0x4B8) == 2;
    params[3] = *(int *)(menu + 0x4AC);
    params[4] = *(int *)(menu + 0x4B0);
    params[9] = (int)&g_item_grid_third_mode_desc_g;
    params[1] = g_item_grid_third_mode_desc_a;
    params[2] = g_item_grid_third_mode_desc_b;
    params[0] = (int)g_help_pending_entries;
    params[17] = (int)(menu + 0x220);
    params[10] = (int)(menu + 0x130);
    params[12] = (int)(menu + 0x17C);
    params[15] = (int)(menu + 0x278);
    params[18] = *(int *)(menu + 0x4A0);
    params[8] = (int)&g_item_grid_third_mode_desc_f;
    params[7] = (int)&g_item_grid_third_mode_desc_e;
    params[6] = (int)&g_item_grid_third_mode_desc_d;
    params[5] = (int)&g_item_grid_third_mode_desc_c;
    params[22] = 1;
    DrawItemGrid(params);
}

extern char g_grid_menu_selection_rows[];
extern int g_item_grid_first_mode_desc_a __attribute__((sda));
extern int g_item_grid_first_mode_desc_b __attribute__((sda));
extern int g_item_grid_first_mode_desc_c __attribute__((sda));
extern int g_item_grid_first_mode_desc_d __attribute__((sda));
extern int g_item_grid_first_mode_desc_e __attribute__((sda));
extern int g_item_grid_first_mode_desc_f __attribute__((sda));
extern int g_item_grid_first_mode_desc_g __attribute__((sda));

/* Draws the item grid in its first mode, highlighted while the menu mode is 0. */
void item_grid_draw_first_mode_pal(char *menu)
{
    int params[23];

    params[16] = 0;
    params[14] = 0;
    params[11] = 0;
    params[13] = 0;
    params[20] = 0;

    params[21] = 1;
    params[19] = *(int *)(menu + 0x4B4);
    params[21] = *(int *)(menu + 0x4B8) == 0;
    params[3] = *(int *)(menu + 0x4AC);
    params[4] = *(int *)(menu + 0x4B0);
    params[9] = (int)&g_item_grid_first_mode_desc_g;
    params[1] = g_item_grid_first_mode_desc_a;
    params[2] = g_item_grid_first_mode_desc_b;
    params[0] = (int)g_grid_menu_selection_rows;
    params[17] = (int)(menu + 0x220);
    params[10] = (int)(menu + 0x130);
    params[12] = (int)(menu + 0x17C);
    params[15] = (int)(menu + 0x278);
    params[18] = *(int *)(menu + 0x4A0);
    params[8] = (int)&g_item_grid_first_mode_desc_f;
    params[7] = (int)&g_item_grid_first_mode_desc_e;
    params[6] = (int)&g_item_grid_first_mode_desc_d;
    params[5] = (int)&g_item_grid_first_mode_desc_c;
    params[22] = 1;
    DrawItemGrid(params);
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

extern float g_object_offset_x_a __attribute__((sda));
extern float g_object_offset_y_a;
extern float g_object_offset_x_b __attribute__((sda));
extern float g_object_offset_y_b;
extern float g_object_offset_x_c __attribute__((sda));
extern float g_object_offset_y_c;
extern float g_object_offset_x_d __attribute__((sda));
extern float g_object_offset_y_d;

/* Places four of the grid menu's widgets relative to the menu position. */
void grid_menu_reposition_widgets_pal(char *self)
{
    float zero = 0.0f;

    object_set_first_float4(self + 872, g_object_offset_x_a + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_a + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 960, g_object_offset_x_b + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_b + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 1048, g_object_offset_x_c + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_c + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 784, g_object_offset_x_d + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_d + (*(struct pos **)(self + 1184))->y, zero, zero);
}

extern char g_str_menu_item_a[];
extern int g_menu_field_nine_a __attribute__((sda));
extern int g_menu_field_eight_a __attribute__((sda));
extern int g_menu_field_one_a __attribute__((sda));
extern int g_menu_field_two_a __attribute__((sda));
extern int g_menu_field_seven_a __attribute__((sda));
extern int g_menu_field_six_a __attribute__((sda));
extern int g_menu_field_five_a __attribute__((sda));

/* Draws the item grid in its second mode, highlighted while the menu mode is 1. */
void item_grid_draw_second_mode_pal(char *menu)
{
    int params[23];

    params[16] = 0;
    params[14] = 0;
    params[11] = 0;
    params[13] = 0;
    params[20] = 0;

    params[21] = 1;
    params[19] = *(int *)(menu + 0x4B4);
    params[21] = *(int *)(menu + 0x4B8) == 1;
    params[3] = *(int *)(menu + 0x4AC);
    params[4] = *(int *)(menu + 0x4B0);
    params[9] = (int)&g_menu_field_nine_a;
    params[1] = g_menu_field_one_a;
    params[2] = g_menu_field_two_a;
    params[0] = (int)g_str_menu_item_a;
    params[17] = (int)(menu + 0x220);
    params[10] = (int)(menu + 0x130);
    params[12] = (int)(menu + 0x17C);
    params[15] = (int)(menu + 0x278);
    params[18] = *(int *)(menu + 0x4A0);
    params[8] = (int)&g_menu_field_eight_a;
    params[7] = (int)&g_menu_field_seven_a;
    params[6] = (int)&g_menu_field_six_a;
    params[5] = (int)&g_menu_field_five_a;
    params[22] = 1;
    DrawItemGrid(params);
}

extern char g_str_menu_item_b[];
extern int g_menu_field_nine_b __attribute__((sda));
extern int g_menu_field_eight_b __attribute__((sda));
extern int g_menu_field_one_b __attribute__((sda));
extern int g_menu_field_two_b __attribute__((sda));
extern int g_menu_field_seven_b __attribute__((sda));
extern int g_menu_field_six_b __attribute__((sda));
extern int g_menu_field_five_b __attribute__((sda));

/* Draws the item grid in its fourth mode, highlighted while the menu mode is 3. */
void item_grid_draw_fourth_mode_pal(char *menu)
{
    int params[23];

    params[16] = 0;
    params[14] = 0;
    params[11] = 0;
    params[13] = 0;
    params[20] = 0;

    params[21] = 1;
    params[19] = *(int *)(menu + 0x4B4);
    params[21] = *(int *)(menu + 0x4B8) == 3;
    params[3] = *(int *)(menu + 0x4AC);
    params[4] = *(int *)(menu + 0x4B0);
    params[9] = (int)&g_menu_field_nine_b;
    params[1] = g_menu_field_one_b;
    params[2] = g_menu_field_two_b;
    params[0] = (int)g_str_menu_item_b;
    params[17] = (int)(menu + 0x220);
    params[10] = (int)(menu + 0x130);
    params[12] = (int)(menu + 0x17C);
    params[15] = (int)(menu + 0x278);
    params[18] = *(int *)(menu + 0x4A0);
    params[8] = (int)&g_menu_field_eight_b;
    params[7] = (int)&g_menu_field_seven_b;
    params[6] = (int)&g_menu_field_six_b;
    params[5] = (int)&g_menu_field_five_b;
    params[22] = 1;
    DrawItemGrid(params);
}
