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

/* Draws the grid menu page for its third mode (USA v2.00 copy). */
void item_grid_draw_third_mode_us2(char *menu)
{
    int desc[23];

    desc[16] = 0;
    desc[14] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[20] = 0;

    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x4B4);
    desc[21] = *(int *)(menu + 0x4B8) == 2;
    desc[3] = *(int *)(menu + 0x4AC);
    desc[4] = *(int *)(menu + 0x4B0);
    desc[9] = (int)&g_item_grid_third_mode_desc_g;
    desc[1] = g_item_grid_third_mode_desc_a;
    desc[2] = g_item_grid_third_mode_desc_b;
    desc[0] = (int)g_help_pending_entries;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x4A0);
    desc[8] = (int)&g_item_grid_third_mode_desc_f;
    desc[7] = (int)&g_item_grid_third_mode_desc_e;
    desc[6] = (int)&g_item_grid_third_mode_desc_d;
    desc[5] = (int)&g_item_grid_third_mode_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
}

extern char g_grid_menu_selection_rows[];
extern int g_item_grid_first_mode_desc_a __attribute__((sda));
extern int g_item_grid_first_mode_desc_b __attribute__((sda));
extern int g_item_grid_first_mode_desc_c __attribute__((sda));
extern int g_item_grid_first_mode_desc_d __attribute__((sda));
extern int g_item_grid_first_mode_desc_e __attribute__((sda));
extern int g_item_grid_first_mode_desc_f __attribute__((sda));
extern int g_item_grid_first_mode_desc_g __attribute__((sda));

/* Draws the grid menu page for its first mode (USA v2.00 copy). */
void item_grid_draw_first_mode_us2(char *menu)
{
    int desc[23];

    desc[16] = 0;
    desc[14] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[20] = 0;

    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x4B4);
    desc[21] = *(int *)(menu + 0x4B8) == 0;
    desc[3] = *(int *)(menu + 0x4AC);
    desc[4] = *(int *)(menu + 0x4B0);
    desc[9] = (int)&g_item_grid_first_mode_desc_g;
    desc[1] = g_item_grid_first_mode_desc_a;
    desc[2] = g_item_grid_first_mode_desc_b;
    desc[0] = (int)g_grid_menu_selection_rows;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x4A0);
    desc[8] = (int)&g_item_grid_first_mode_desc_f;
    desc[7] = (int)&g_item_grid_first_mode_desc_e;
    desc[6] = (int)&g_item_grid_first_mode_desc_d;
    desc[5] = (int)&g_item_grid_first_mode_desc_c;
    desc[22] = 1;
    DrawItemGrid(desc);
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

extern float g_object_offset_x_a_2 __attribute__((sda));
extern float g_object_offset_y_a_2;
extern float g_object_offset_x_b_2 __attribute__((sda));
extern float g_object_offset_y_b_2;
extern float g_object_offset_x_c_2 __attribute__((sda));
extern float g_object_offset_y_c_2;
extern float g_object_offset_x_d_2 __attribute__((sda));
extern float g_object_offset_y_d_2;

void grid_menu_reposition_widgets_us2(char *self)
{
    float zero = 0.0f;

    object_set_first_float4(self + 872, g_object_offset_x_a_2 + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_a_2 + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 960, g_object_offset_x_b_2 + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_b_2 + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 1048, g_object_offset_x_c_2 + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_c_2 + (*(struct pos **)(self + 1184))->y, zero, zero);
    object_set_first_float4(self + 784, g_object_offset_x_d_2 + (*(struct pos **)(self + 1184))->x,
            g_object_offset_y_d_2 + (*(struct pos **)(self + 1184))->y, zero, zero);
}



extern char g_str_object_label_a[];
extern int g_object_desc_a_nine __attribute__((sda));
extern int g_object_desc_a_eight __attribute__((sda));
extern int g_object_desc_a_one __attribute__((sda));
extern int g_object_desc_a_two __attribute__((sda));
extern int g_object_desc_a_seven __attribute__((sda));
extern int g_object_desc_a_six __attribute__((sda));
extern int g_object_desc_a_five __attribute__((sda));

/* Draws the grid menu page for its second mode (USA v2.00 copy). */
void item_grid_draw_second_mode_us2(char *menu)
{
    int desc[23];

    desc[16] = 0;
    desc[14] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[20] = 0;

    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x4B4);
    desc[21] = *(int *)(menu + 0x4B8) == 1;
    desc[3] = *(int *)(menu + 0x4AC);
    desc[4] = *(int *)(menu + 0x4B0);
    desc[9] = (int)&g_object_desc_a_nine;
    desc[1] = g_object_desc_a_one;
    desc[2] = g_object_desc_a_two;
    desc[0] = (int)g_str_object_label_a;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x4A0);
    desc[8] = (int)&g_object_desc_a_eight;
    desc[7] = (int)&g_object_desc_a_seven;
    desc[6] = (int)&g_object_desc_a_six;
    desc[5] = (int)&g_object_desc_a_five;
    desc[22] = 1;
    DrawItemGrid(desc);
}



extern char g_str_object_label_b[];
extern int g_object_desc_b_nine __attribute__((sda));
extern int g_object_desc_b_eight __attribute__((sda));
extern int g_object_desc_b_one __attribute__((sda));
extern int g_object_desc_b_two __attribute__((sda));
extern int g_object_desc_b_seven __attribute__((sda));
extern int g_object_desc_b_six __attribute__((sda));
extern int g_object_desc_b_five __attribute__((sda));

/* Draws the grid menu page for its fourth mode (USA v2.00 copy). */
void item_grid_draw_fourth_mode_us2(char *menu)
{
    int desc[23];

    desc[16] = 0;
    desc[14] = 0;
    desc[11] = 0;
    desc[13] = 0;
    desc[20] = 0;

    desc[21] = 1;
    desc[19] = *(int *)(menu + 0x4B4);
    desc[21] = *(int *)(menu + 0x4B8) == 3;
    desc[3] = *(int *)(menu + 0x4AC);
    desc[4] = *(int *)(menu + 0x4B0);
    desc[9] = (int)&g_object_desc_b_nine;
    desc[1] = g_object_desc_b_one;
    desc[2] = g_object_desc_b_two;
    desc[0] = (int)g_str_object_label_b;
    desc[17] = (int)(menu + 0x220);
    desc[10] = (int)(menu + 0x130);
    desc[12] = (int)(menu + 0x17C);
    desc[15] = (int)(menu + 0x278);
    desc[18] = *(int *)(menu + 0x4A0);
    desc[8] = (int)&g_object_desc_b_eight;
    desc[7] = (int)&g_object_desc_b_seven;
    desc[6] = (int)&g_object_desc_b_six;
    desc[5] = (int)&g_object_desc_b_five;
    desc[22] = 1;
    DrawItemGrid(desc);
}


