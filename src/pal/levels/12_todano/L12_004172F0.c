#include "include_asm.h"

#include "common.h"
extern u8 g_hero_prev_position[];
extern u8 g_hero_l12_state_records[];
extern s32 func_315148();
extern void moby_set_state();
extern s32 flag_is_third_pending_set();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern f32 func_2F2950(f32 x, f32 y);
extern s32 g_moby_list_start __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
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

/* Advances the measured state machine of the given object. */
void rising_object_update_pal(u8 *object) {
    switch (object[0x20]) {
    case 0:
        if (flag_is_third_pending_set(object) != 0)
            moby_set_state(object, 1, -1);
        break;
    case 1:
        if (*(f32 *)(object + 0x18) < 160.0f)
            *(f32 *)(object + 0x18) = *(f32 *)(object + 0x18) + 0.10000001f;
        break;
    }
}

