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

void func_US2_00345F00(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 2;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&g_item_grid_third_mode_desc_g;
    f[1] = g_item_grid_third_mode_desc_a;
    f[2] = g_item_grid_third_mode_desc_b;
    f[0] = (int)g_help_pending_entries;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_item_grid_third_mode_desc_f;
    f[7] = (int)&g_item_grid_third_mode_desc_e;
    f[6] = (int)&g_item_grid_third_mode_desc_d;
    f[5] = (int)&g_item_grid_third_mode_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}

extern char g_grid_menu_selection_rows[];
extern int g_item_grid_first_mode_desc_a __attribute__((sda));
extern int g_item_grid_first_mode_desc_b __attribute__((sda));
extern int g_item_grid_first_mode_desc_c __attribute__((sda));
extern int g_item_grid_first_mode_desc_d __attribute__((sda));
extern int g_item_grid_first_mode_desc_e __attribute__((sda));
extern int g_item_grid_first_mode_desc_f __attribute__((sda));
extern int g_item_grid_first_mode_desc_g __attribute__((sda));

void func_US2_003461D0(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 0;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&g_item_grid_first_mode_desc_g;
    f[1] = g_item_grid_first_mode_desc_a;
    f[2] = g_item_grid_first_mode_desc_b;
    f[0] = (int)g_grid_menu_selection_rows;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_item_grid_first_mode_desc_f;
    f[7] = (int)&g_item_grid_first_mode_desc_e;
    f[6] = (int)&g_item_grid_first_mode_desc_d;
    f[5] = (int)&g_item_grid_first_mode_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
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

void func_US2_003457A0(char *self)
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

void func_US2_00345FF0(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 1;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&g_object_desc_a_nine;
    f[1] = g_object_desc_a_one;
    f[2] = g_object_desc_a_two;
    f[0] = (int)g_str_object_label_a;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_object_desc_a_eight;
    f[7] = (int)&g_object_desc_a_seven;
    f[6] = (int)&g_object_desc_a_six;
    f[5] = (int)&g_object_desc_a_five;
    f[22] = 1;
    DrawItemGrid(f);
}



extern char g_str_object_label_b[];
extern int g_object_desc_b_nine __attribute__((sda));
extern int g_object_desc_b_eight __attribute__((sda));
extern int g_object_desc_b_one __attribute__((sda));
extern int g_object_desc_b_two __attribute__((sda));
extern int g_object_desc_b_seven __attribute__((sda));
extern int g_object_desc_b_six __attribute__((sda));
extern int g_object_desc_b_five __attribute__((sda));

void func_US2_003460E0(char *o)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(o + 0x4B4);
    f[21] = *(int *)(o + 0x4B8) == 3;
    f[3] = *(int *)(o + 0x4AC);
    f[4] = *(int *)(o + 0x4B0);
    f[9] = (int)&g_object_desc_b_nine;
    f[1] = g_object_desc_b_one;
    f[2] = g_object_desc_b_two;
    f[0] = (int)g_str_object_label_b;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_object_desc_b_eight;
    f[7] = (int)&g_object_desc_b_seven;
    f[6] = (int)&g_object_desc_b_six;
    f[5] = (int)&g_object_desc_b_five;
    f[22] = 1;
    DrawItemGrid(f);
}


