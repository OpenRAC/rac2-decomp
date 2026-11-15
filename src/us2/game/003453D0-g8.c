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
extern short D_001A7A10[4];
extern unsigned char g_item_owned_flags[];
extern unsigned char g_item_slot_to_record[];
extern struct row224 g_weapon_table[];
extern int D_00138344[];
extern struct quad D_001AE270;
extern struct vec2 D_001AE2A8[];
extern float D_001AE280 __attribute__((sda));
extern float D_001AE284;
extern float D_001AE288 __attribute__((sda));
extern float D_001AE28C;
extern float D_001AE290 __attribute__((sda));
extern float D_001AE294;
extern float D_001AE298 __attribute__((sda));
extern float D_001AE29C;
extern float D_001AE2A0 __attribute__((sda));
extern float D_001AE2A4;
extern float D_001AE2B0 __attribute__((sda));
extern float D_001AE2B4;
extern float D_001AE2B8 __attribute__((sda));
extern float D_001AE2BC;
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
int func_US2_003453D0(char *self, unsigned int buttons)
{
    *(int *)(self + 0x4B4) = 0;
    g_selected_item_material = -1;
    menu_seek_chain_entry(6, D_001A7A10[4]);
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
        struct quad table = D_001AE270;
        int idx = *(int *)(self + 0x4B4);

        g_selected_item_material = table.v[idx];
    } else {
        int idx = *(int *)(self + 0x4B4);

        if (g_item_owned_flags[idx])
            g_selected_item_material = (g_weapon_table + g_item_slot_to_record[idx])->id;
    }
    {
        float zero = 0.0f;
        struct vec2 offset = D_001AE2A8[0];
        struct vec2 **pos = (struct vec2 **)(self + 0x4A0);

        object_set_first_float4(self, D_001AE280 + (*pos)->x, D_001AE284 + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x4C, D_001AE2A0 + (*pos)->x, D_001AE2A4 + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x98, D_001AE288 + (*pos)->x, D_001AE28C + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0xE4, D_001AE290 + (*pos)->x, D_001AE294 + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x130, D_001AE298 + (*pos)->x, D_001AE29C + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x1C8, offset.x + (*pos)->x, offset.y + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x2B8, D_001AE2B0 + (*pos)->x, D_001AE2B4 + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x220, D_001AE2B8 + (*pos)->x, D_001AE2BC + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x130, D_001AE2B8 + (*pos)->x, D_001AE2BC + (*pos)->y, zero, zero);
        object_set_first_float4(self + 0x17C, D_001AE2B8 + (*pos)->x, D_001AE2BC + (*pos)->y, zero, zero);
    }
    if (D_00138344[0] & 0xF000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    *object_get_fourth_field(self + 0x17C) = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    grid_menu_reposition_widgets(self);
    return 0;
}
