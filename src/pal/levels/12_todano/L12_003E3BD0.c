#include "include_asm.h"


#include "common.h"
extern u8 g_hero_prev_position[];
extern u8 g_hero_l12_state_records[];
extern s32 func_315148();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern void func_PAL_002AC3C0(void *arg0, void *arg1);
extern void moby_update_eased_node(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern f32 func_2F2950(f32 x, f32 y);
extern s32 g_moby_list_start __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *g_moby_l12_group_lists[];
extern s32 g_current_map_index __attribute__((sda));
extern s32 GetFirstMobyInGroup(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_unlocked_item_flags MACRO_ADDR;
extern u32 g_object_state_flags_f, g_pad_held_flags;
extern u8 g_requirement_queue[];
extern u8 *CreateMoby(int);
extern char *GetLocalizedString(int);
extern s32 *g_path_zone_table[];
extern s32 point_in_path_xy(void *, void *, s32);

/* Re-arms the measured two-slot primitive after the counter step. */
void func_PAL_L12_003E4A20(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_PAL_002AC3C0(object, state + 0x50);
    moby_update_eased_node(object, state + 0x6C0, 1, 0.0432f, 0.43200004f);
    moby_update_eased_node(object, state + 0x640, 0, 0.0432f, 0.43200004f);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
}


