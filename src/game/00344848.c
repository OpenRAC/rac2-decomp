#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(char *p, float x, float y, float zero, float zero2);

extern float g_grid_menu_first_offset_x __attribute__((sda));

extern float g_grid_menu_second_offset_x __attribute__((sda));

extern float g_grid_menu_third_offset_x __attribute__((sda));

extern float g_grid_menu_fourth_offset_x __attribute__((sda));

extern float g_grid_menu_first_offset_y;

extern float g_grid_menu_second_offset_y;

extern float g_grid_menu_third_offset_y;

extern float g_grid_menu_fourth_offset_y;

struct pos54dfe946 {
    float x;
    float y;
};

/* Moves four parts of the grid menu to their places next to the menu position. */
void grid_menu_reposition_widgets(char *menu)
{
    float zero = 0.0f;

    object_set_first_float4(menu + 808, g_grid_menu_first_offset_x + (*(struct pos54dfe946 **)(menu + 1072))->x,
            g_grid_menu_first_offset_y + (*(struct pos54dfe946 **)(menu + 1072))->y, zero, zero);
    object_set_first_float4(menu + 880, g_grid_menu_second_offset_x + (*(struct pos54dfe946 **)(menu + 1072))->x,
            g_grid_menu_second_offset_y + (*(struct pos54dfe946 **)(menu + 1072))->y, zero, zero);
    object_set_first_float4(menu + 952, g_grid_menu_third_offset_x + (*(struct pos54dfe946 **)(menu + 1072))->x,
            g_grid_menu_third_offset_y + (*(struct pos54dfe946 **)(menu + 1072))->y, zero, zero);
    object_set_first_float4(menu + 736, g_grid_menu_fourth_offset_x + (*(struct pos54dfe946 **)(menu + 1072))->x,
            g_grid_menu_fourth_offset_y + (*(struct pos54dfe946 **)(menu + 1072))->y, zero, zero);
}

/* These four fill func_00337210's 23-word descriptor, defaults first. f[21] defaults to 1
   before it takes the mode test, as in func_003462A8, whose object still holds that default
   store; here the store is dead and goes, and the later f[22] = 1 reuses its register. */
extern void DrawItemGrid(int *);

extern char g_help_pending_entries[];
extern int g_item_grid_third_mode_desc_a __attribute__((sda));
extern int g_item_grid_third_mode_desc_b __attribute__((sda));
extern int g_item_grid_third_mode_desc_c __attribute__((sda));
extern int g_item_grid_third_mode_desc_d __attribute__((sda));
extern int g_item_grid_third_mode_desc_e __attribute__((sda));
extern int g_item_grid_third_mode_desc_f __attribute__((sda));
extern int g_item_grid_third_mode_desc_g __attribute__((sda));

/* Fills in the drawing settings for the item grid in the third mode of the menu and draws it. */
void item_grid_draw_third_mode(char *menu)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(menu + 0x444);
    f[21] = *(int *)(menu + 0x448) == 2;
    f[3] = *(int *)(menu + 0x43C);
    f[4] = *(int *)(menu + 0x440);
    f[9] = (int)&g_item_grid_third_mode_desc_g;
    f[1] = g_item_grid_third_mode_desc_a;
    f[2] = g_item_grid_third_mode_desc_b;
    f[0] = (int)g_help_pending_entries;
    f[17] = (int)(menu + 0x210);
    f[10] = (int)(menu + 0x130);
    f[12] = (int)(menu + 0x17C);
    f[15] = (int)(menu + 0x258);
    f[18] = *(int *)(menu + 0x430);
    f[8] = (int)&g_item_grid_third_mode_desc_f;
    f[7] = (int)&g_item_grid_third_mode_desc_e;
    f[6] = (int)&g_item_grid_third_mode_desc_d;
    f[5] = (int)&g_item_grid_third_mode_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}

extern char g_item_grid_second_mode_desc[];
extern int g_item_grid_second_mode_desc_a __attribute__((sda));
extern int g_item_grid_second_mode_desc_b __attribute__((sda));
extern int g_item_grid_second_mode_desc_c __attribute__((sda));
extern int g_item_grid_second_mode_desc_d __attribute__((sda));
extern int g_item_grid_second_mode_desc_e __attribute__((sda));
extern int g_item_grid_second_mode_desc_f __attribute__((sda));
extern int g_item_grid_second_mode_desc_g __attribute__((sda));

/* Fills in the drawing settings for the item grid in the second mode of the menu and draws it. */
void item_grid_draw_second_mode(char *menu)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(menu + 0x444);
    f[21] = *(int *)(menu + 0x448) == 1;
    f[3] = *(int *)(menu + 0x43C);
    f[4] = *(int *)(menu + 0x440);
    f[9] = (int)&g_item_grid_second_mode_desc_g;
    f[1] = g_item_grid_second_mode_desc_a;
    f[2] = g_item_grid_second_mode_desc_b;
    f[0] = (int)g_item_grid_second_mode_desc;
    f[17] = (int)(menu + 0x210);
    f[10] = (int)(menu + 0x130);
    f[12] = (int)(menu + 0x17C);
    f[15] = (int)(menu + 0x258);
    f[18] = *(int *)(menu + 0x430);
    f[8] = (int)&g_item_grid_second_mode_desc_f;
    f[7] = (int)&g_item_grid_second_mode_desc_e;
    f[6] = (int)&g_item_grid_second_mode_desc_d;
    f[5] = (int)&g_item_grid_second_mode_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}

extern char g_item_grid_fourth_mode_desc[];
extern int g_item_grid_fourth_mode_desc_a __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_b __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_c __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_d __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_e __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_f __attribute__((sda));
extern int g_item_grid_fourth_mode_desc_g __attribute__((sda));

/* Fills in the drawing settings for the item grid in the fourth mode of the menu and draws it. */
void item_grid_draw_fourth_mode(char *menu)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(menu + 0x444);
    f[21] = *(int *)(menu + 0x448) == 3;
    f[3] = *(int *)(menu + 0x43C);
    f[4] = *(int *)(menu + 0x440);
    f[9] = (int)&g_item_grid_fourth_mode_desc_g;
    f[1] = g_item_grid_fourth_mode_desc_a;
    f[2] = g_item_grid_fourth_mode_desc_b;
    f[0] = (int)g_item_grid_fourth_mode_desc;
    f[17] = (int)(menu + 0x210);
    f[10] = (int)(menu + 0x130);
    f[12] = (int)(menu + 0x17C);
    f[15] = (int)(menu + 0x258);
    f[18] = *(int *)(menu + 0x430);
    f[8] = (int)&g_item_grid_fourth_mode_desc_f;
    f[7] = (int)&g_item_grid_fourth_mode_desc_e;
    f[6] = (int)&g_item_grid_fourth_mode_desc_d;
    f[5] = (int)&g_item_grid_fourth_mode_desc_c;
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

/* Fills in the drawing settings for the item grid in the first mode of the menu and draws it. */
void item_grid_draw_first_mode(char *menu)
{
    int f[23];

    f[16] = 0;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    f[20] = 0;

    f[21] = 1;
    f[19] = *(int *)(menu + 0x444);
    f[21] = *(int *)(menu + 0x448) == 0;
    f[3] = *(int *)(menu + 0x43C);
    f[4] = *(int *)(menu + 0x440);
    f[9] = (int)&g_item_grid_first_mode_desc_g;
    f[1] = g_item_grid_first_mode_desc_a;
    f[2] = g_item_grid_first_mode_desc_b;
    f[0] = (int)g_grid_menu_selection_rows;
    f[17] = (int)(menu + 0x210);
    f[10] = (int)(menu + 0x130);
    f[12] = (int)(menu + 0x17C);
    f[15] = (int)(menu + 0x258);
    f[18] = *(int *)(menu + 0x430);
    f[8] = (int)&g_item_grid_first_mode_desc_f;
    f[7] = (int)&g_item_grid_first_mode_desc_e;
    f[6] = (int)&g_item_grid_first_mode_desc_d;
    f[5] = (int)&g_item_grid_first_mode_desc_c;
    f[22] = 1;
    DrawItemGrid(f);
}
