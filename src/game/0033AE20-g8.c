#include "include_asm.h"
#include "names.h"

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern void hud_set_widget_field_b(void *, int);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_value_pair(void *, int, int);
extern char *GetLocalizedString(int);
extern int map_screen_update_layout(char *, int);
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[], g_menu_widget_desc_third[], g_menu_widget_desc_fourth[];
extern char g_menu_hud_desc_title[], g_menu_hud_desc_body[], g_menu_hud_desc_label[], g_map_screen_derived_desc_left[], g_map_screen_derived_desc_right[];
extern char *g_resident_data_base;

/* Constructor of an on-screen map object: stores the owner, allocates the 16-byte anchor (255, 207)
   at +0x1C8, then names and tints three sprites ("0", "1", "2" at +0x0, +0x4C, +0x98), three more
   named "3" (+0xE4, +0x130, +0x17C), three texts (Title +0x1D8, Exit +0x268, Sel +0x220) and two
   map sprites (MapSpr +0x2B0, MapPlanetSpr +0x2EC), sets their strings and places them with
   func_0033B540. The three sprite loops keep their own counters (i, j, k): sharing one counter
   keeps the loop-invariant high half of the "3" name out of a register. */
void map_screen_init(char *self, char *owner)
{
    int i, j, k;

    *(char **)(self + 0x1CC) = owner;
    if (owner) {
        int *allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x1C8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(self + 0x328) = 1;
    (*(float **)(self + 0x1C8))[0] = 255.0f;
    (*(float **)(self + 0x1C8))[1] = 207.0f;
    object_init_derived_arrays(self, g_menu_widget_desc_first, owner);
    object_init_derived_arrays(self + 0x4C, g_menu_widget_desc_second, owner);
    object_init_derived_arrays(self + 0x98, g_menu_widget_desc_third, owner);
    for (i = 0; i < 3; i++)
        object_init_derived_arrays(self + 0xE4 + i * 0x4C, g_menu_widget_desc_fourth, owner);
    hud_init_widget_defaults(self + 0x1D8, g_menu_hud_desc_title, owner);
    hud_init_widget_defaults(self + 0x268, g_menu_hud_desc_body, owner);
    hud_init_widget_defaults(self + 0x220, g_menu_hud_desc_label, owner);
    hud_set_widget_field_a(self + 0x268, 0);
    hud_set_widget_field_a(self + 0x220, 0);
    object_init_derived_c(self + 0x2B0, g_map_screen_derived_desc_left, owner);
    object_init_derived_c(self + 0x2EC, g_map_screen_derived_desc_right, owner);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(self + 0x4C) = 0x60241700;
    *object_get_fourth_field(self + 0x98) = 0x55F0C070;
    for (j = 0; j < 3; j++)
        *object_get_fourth_field(self + 0xE4 + j * 0x4C) = 0x80FFDE8D;
    *object_get_fourth_field(self + 0x2B0) = 0x70A0C0C0;
    *object_get_fourth_field(self + 0x1D8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x268) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x220) = 0x80F0F0F0;
    object_set_helper_result(self, g_resident_data_base + 0x8710, 0x87);
    object_set_helper_result(self + 0x4C, g_resident_data_base + 0x8710, 0x88);
    object_set_helper_result(self + 0x98, g_resident_data_base + 0x8710, 0x89);
    for (k = 0; k < 3; k++)
        object_set_helper_result(self + 0xE4 + k * 0x4C, g_resident_data_base + 0x8710, 0x8A);
    object_set_second_float4(self + 0x130, 1.0f, -1.0f, 0.0f, 0.0f);
    hud_set_widget_value_pair(self + 0x2B0, 0xE99A, 10);
    object_set_second_float4(self + 0x2B0, 302.0f, 194.0f, 0.0f, 0.0f);
    object_set_second_float4(self + 0x2EC, 32.0f, 32.0f, 0.0f, 0.0f);
    *(int *)(self + 0x1D0) = 0;
    hud_set_widget_field_b(self + 0x1D8, GetLocalizedString(0x2D60));
    hud_set_widget_field_b(self + 0x268, GetLocalizedString(0x2D4F));
    hud_set_widget_field_b(self + 0x220, GetLocalizedString(0x2D75));
    map_screen_update_layout(self, 0);
}

extern void object_set_first_float4(char *, float, float, float, float);
extern float *object_get_first_field(char *);
extern float g_map_screen_offset_x_first __attribute__((sda));
extern float g_map_screen_offset_y_first;
extern float g_map_screen_offset_x_second;
extern float g_map_screen_offset_y_second;
extern float g_map_screen_offset_x_third;
extern float g_map_screen_offset_y_third;
extern float g_map_screen_offset_x_fourth __attribute__((sda));
extern float g_map_screen_offset_y_fourth;
extern float g_map_screen_offset_x_fifth __attribute__((sda));
extern float g_map_screen_offset_y_fifth;
extern float g_map_screen_offset_x_sixth __attribute__((sda));
extern float g_map_screen_offset_y_sixth;
extern float g_map_screen_offset_x_seventh __attribute__((sda));
extern float g_map_screen_offset_y_seventh;
extern char g_map_overlay_state[];

typedef struct { int first, second, third; float scale; } Entry_0033B540;
extern Entry_0033B540 g_map_spot_table[];

/* Places the sprites of the object built by func_0033B170 around the anchor at +0x1C8 and returns
   0. While the word at D_001C4FA0 + 0x230 is below 0x15, the offset of the sprites at +0xE4 and
   +0x130 (horizontal, 5 at most per call) and of the one at +0x17C (vertical, 3 at most) is eased
   toward a cell of the 16-byte table D_00265140. g and g2 are two loads of the same base: the
   second branch rebuilds the address, as retail does. The second argument is not read. */
int map_screen_update_layout(char *self, int unused)
{
    float dx, dy;
    float *anchor;
    char *game;

    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x4C, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x98, anchor[0], anchor[1], 0.0f, 0.0f);
    dx = dy = 0.0f;
    game = g_map_overlay_state;
    if (*(int *)(game + 0x230) < 0x15) {
        float step;

        dx = object_get_first_field(self + 0xE4)[0] - (g_map_screen_offset_x_first + (*(float **)(self + 0x1C8))[0]);
        if (object_get_first_field(self + 0xE4)[0] == 0.0f) {
            dx = 56.0f;
        } else {
            step = (float)g_map_spot_table[*(int *)(game + 0x230)].first + g_map_spot_table[*(int *)(game + 0x230)].scale * 0.5f - dx;
            if (step > 5.0f)
                step = 5.0f;
            else if (step < -5.0f)
                step = -5.0f;
            dx += step;
        }
        dy = object_get_first_field(self + 0x17C)[1] - (g_map_screen_offset_y_third + (*(float **)(self + 0x1C8))[1]);
        if (object_get_first_field(self + 0x17C)[1] == 0.0f) {
            dy = -50.0f;
        } else {
            char *game2 = g_map_overlay_state;
            step = (float)g_map_spot_table[*(int *)(game2 + 0x230)].second + g_map_spot_table[*(int *)(game2 + 0x230)].scale * 0.5f - dy;
            if (step > 3.0f)
                step = 3.0f;
            else if (step < -3.0f)
                step = -3.0f;
            dy += step;
        }
    }
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0xE4, g_map_screen_offset_x_first + anchor[0] + dx, g_map_screen_offset_y_first + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x130, g_map_screen_offset_x_second + anchor[0] + dx, g_map_screen_offset_y_second + anchor[1], 0.0f, 0.0f);
    object_set_first_float4(self + 0x17C, g_map_screen_offset_x_third + (*(float **)(self + 0x1C8))[0], g_map_screen_offset_y_third + (*(float **)(self + 0x1C8))[1] + dy, 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x1D8, g_map_screen_offset_x_fourth + anchor[0], g_map_screen_offset_y_fourth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x220, g_map_screen_offset_x_fifth + anchor[0], g_map_screen_offset_y_fifth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x268, g_map_screen_offset_x_sixth + anchor[0], g_map_screen_offset_y_sixth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x2B0, g_map_screen_offset_x_seventh + anchor[0], g_map_screen_offset_y_seventh + anchor[1], 0.0f, 0.0f);
    return 0;
}
