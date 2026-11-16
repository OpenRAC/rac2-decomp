#include "include_asm.h"
#include "names.h"
struct vec2 {
    float x;
    float y;
};
struct quad {
    int v[4];
};
struct row224 {
    unsigned char pad[6];
    short id;
    unsigned char rest[0xD8];
};
extern int g_selected_item_material __attribute__((sda));
extern short g_player_state_shorts[4];
extern unsigned char g_item_owned_flags[];
extern unsigned char g_item_slot_to_record[];
extern struct row224 g_weapon_table[];
extern int g_menu_input_flags[];
extern struct quad g_grid_menu_quad_template;
extern struct vec2 g_grid_menu_offsets[];
extern float g_grid_menu_cursor_x_offset __attribute__((sda));
extern float g_grid_menu_cursor_y_offset;
extern float g_grid_menu_icon_x_offset __attribute__((sda));
extern float g_grid_menu_icon_y_offset;
extern float g_grid_menu_title_x_offset __attribute__((sda));
extern float g_grid_menu_title_y_offset;
extern float g_grid_menu_text_x_offset __attribute__((sda));
extern float g_grid_menu_text_y_offset;
extern float g_grid_menu_frame_x_offset __attribute__((sda));
extern float g_grid_menu_frame_y_offset;
extern float g_grid_menu_panel_x_offset __attribute__((sda));
extern float g_grid_menu_panel_y_offset;
extern float g_grid_menu_label_x_offset __attribute__((sda));
extern float g_grid_menu_label_y_offset;
extern int menu_seek_chain_entry(int, int);
extern void grid_menu_handle_input_first_group(char *, unsigned int);
extern void grid_menu_handle_input_single_choice(char *, unsigned int);
extern void grid_menu_handle_input_main_grid(char *, unsigned int);
extern void grid_menu_handle_input_small_group(char *, unsigned int);
extern void object_set_first_float4(char *, float, float, float, float);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern int *object_get_fourth_field(char *);
extern void grid_menu_reposition_widgets(char *);

/* menu update: clears the index at +0x444, dispatches on the mode at +0x448 (0 to 3), stores the id of the
   selected entry in D_001ADB10, then repositions ten widgets from the position pointer at +0x430; returns 0 */
int grid_menu_update_pal(char *self, unsigned int buttons)
{
    *(int *)(self + 0x4B4) = 0;
    g_selected_item_material = -1;
    menu_seek_chain_entry(6, g_player_state_shorts[4]);
    switch (*(int *)(self + 0x4B8)) {
    case 0:
        grid_menu_handle_input_first_group(self, buttons);
        break;
    case 1:
        grid_menu_handle_input_single_choice(self, buttons);
        break;
    case 2:
        grid_menu_handle_input_main_grid(self, buttons);
        break;
    case 3:
        grid_menu_handle_input_small_group(self, buttons);
        break;
    }
    if (*(int *)(self + 0x4B8) == 3) {
        struct quad table = g_grid_menu_quad_template;
        int idx = *(int *)(self + 0x4B4);

        g_selected_item_material = table.v[idx];
    } else {
        int idx = *(int *)(self + 0x4B4);

        if (g_item_owned_flags[idx])
            g_selected_item_material = (g_weapon_table + g_item_slot_to_record[idx])->id;
    }
    {
        float zero = 0.0f;
        struct vec2 offset = g_grid_menu_offsets[0];
        struct vec2 **pos = (struct vec2 **)(self + 0x4A0);

        object_set_first_float4(self, g_grid_menu_cursor_x_offset + (*pos)->x, g_grid_menu_cursor_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x4C, g_grid_menu_frame_x_offset + (*pos)->x, g_grid_menu_frame_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x98, g_grid_menu_icon_x_offset + (*pos)->x, g_grid_menu_icon_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0xE4, g_grid_menu_title_x_offset + (*pos)->x, g_grid_menu_title_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x130, g_grid_menu_text_x_offset + (*pos)->x, g_grid_menu_text_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x1C8, offset.x + (*pos)->x, offset.y + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x2B8, g_grid_menu_panel_x_offset + (*pos)->x, g_grid_menu_panel_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x220, g_grid_menu_label_x_offset + (*pos)->x, g_grid_menu_label_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x130, g_grid_menu_label_x_offset + (*pos)->x, g_grid_menu_label_y_offset + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x17C, g_grid_menu_label_x_offset + (*pos)->x, g_grid_menu_label_y_offset + (*pos)->y, zero, zero);
    }
    if (g_menu_input_flags[0] & 0xF000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    *object_get_fourth_field(self + 0x17C) = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    grid_menu_reposition_widgets(self);
    return 0;
}
