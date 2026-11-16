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

void func_PAL_00347078(char *o)
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

void func_PAL_00347348(char *o)
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

extern float g_object_offset_x_a __attribute__((sda));
extern float g_object_offset_y_a;
extern float g_object_offset_x_b __attribute__((sda));
extern float g_object_offset_y_b;
extern float g_object_offset_x_c __attribute__((sda));
extern float g_object_offset_y_c;
extern float g_object_offset_x_d __attribute__((sda));
extern float g_object_offset_y_d;

void func_PAL_003468F8(char *self)
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

void func_PAL_00347168(char *o)
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
    f[9] = (int)&g_menu_field_nine_a;
    f[1] = g_menu_field_one_a;
    f[2] = g_menu_field_two_a;
    f[0] = (int)g_str_menu_item_a;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_menu_field_eight_a;
    f[7] = (int)&g_menu_field_seven_a;
    f[6] = (int)&g_menu_field_six_a;
    f[5] = (int)&g_menu_field_five_a;
    f[22] = 1;
    DrawItemGrid(f);
}

extern char g_str_menu_item_b[];
extern int g_menu_field_nine_b __attribute__((sda));
extern int g_menu_field_eight_b __attribute__((sda));
extern int g_menu_field_one_b __attribute__((sda));
extern int g_menu_field_two_b __attribute__((sda));
extern int g_menu_field_seven_b __attribute__((sda));
extern int g_menu_field_six_b __attribute__((sda));
extern int g_menu_field_five_b __attribute__((sda));

void func_PAL_00347258(char *o)
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
    f[9] = (int)&g_menu_field_nine_b;
    f[1] = g_menu_field_one_b;
    f[2] = g_menu_field_two_b;
    f[0] = (int)g_str_menu_item_b;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x4A0);
    f[8] = (int)&g_menu_field_eight_b;
    f[7] = (int)&g_menu_field_seven_b;
    f[6] = (int)&g_menu_field_six_b;
    f[5] = (int)&g_menu_field_five_b;
    f[22] = 1;
    DrawItemGrid(f);
}
