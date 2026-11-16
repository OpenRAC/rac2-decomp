#include "include_asm.h"


#include "common.h"
extern u8 g_hero_prev_position[];
extern u8 g_hero_l12_state_records[];
extern s32 func_315148();
extern s32 func_32D988();
extern s32 FastDecTimer(void *arg0);
extern void gfx_update_color_fade_pal(void *arg0, void *arg1);
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

/* Resets the measured slot state and re-arms the primitive. */
void joint_slots_reset_advance_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 counter;

    gfx_update_color_fade_pal(moby, vars + 0x50);
    FastDecTimer(vars + 0x360);
    FastDecTimer(vars + 0x362);
    counter = *(u16 *)(moby + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(moby + 0x96) = counter + 1;
    moby_update_eased_node(moby, vars + 0x240, 1, 0.0432f, 0.43200004f);
    moby_update_eased_node(moby, vars + 0x2C0, 0, 0.0432f, 0.43200004f);
}

