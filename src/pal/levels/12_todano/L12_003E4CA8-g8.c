#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_list_start __attribute__((sda));
extern u16 *g_moby_l12_group_lists[];
extern s32 g_tourist_wait_counter __attribute__((sda));
extern void func_PAL_002A7E68(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void moby_set_state(void *arg0, s32 arg1, s32 arg2);
extern void FastVecSub(f32 *buf, u8 *arg1, u8 *arg2);
extern void vec_clamp_length(f32 *buf, f32 x);
extern void FastVecAdd(u8 *arg0, u8 *arg1, f32 *buf);
extern void StepAngleTowardTarget(u8 *arg0, s32 arg1, f32 x, f32 y);
extern void part_spawn_explosion_with_sparks_pal(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);
extern s32 g_slot_timer_threshold __attribute__((sda));
extern s32 g_guard_cooldown_min __attribute__((sda));
extern s32 g_guard_cooldown_max __attribute__((sda));
extern u16 g_slot_timer_reset_value __attribute__((sda));
extern f32 g_slot_timer_effect_param __attribute__((sda));
extern s32 func_2F15C8(void *arg0);
extern s32 func_31E2E0(s32 arg0, s32 arg1);
extern u8 *g_tracked_object_ptr __attribute__((sda));
extern u8 *g_second_tracked_object __attribute__((sda));
extern u8 g_hero_prev_position[];
extern u8 *g_hero_moby NOT_SDA;
extern u8 *g_path_zone_table[];
extern u8 g_hero_position[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern int g_game_mode NOT_SDA;

/* Arms the measured sub-object on the first entry. */
void sub_object_start_move_pal(u8 *object, u8 *arg1, u8 *arg2, s32 arg3) {
    f32 buffer[4];
    u16 flags;

    if (*(u8 *)(object + 0x43) != 0xA)
        func_PAL_002A7E68(object, 0xA, 0, 5);
    if (*(u8 *)(object + 0xBC) != 8)
        moby_set_state(object, 8, 1);
    FastVecSub(buffer, arg1, object + 0x10);
    vec_clamp_length(buffer, 0.20000002f);
    FastVecAdd(object + 0x10, object + 0x10, buffer);
    StepAngleTowardTarget(object + 0xF8, 0, *(f32 *)(arg2 + 8), 0.25132746f);
    if (arg3 != 0) {
        flags = *(u16 *)(object + 0x34);
        g_tourist_wait_counter = g_tourist_wait_counter + 1;
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (flags | 0x41) & 0xEFFF;
        part_spawn_explosion_with_sparks_pal(object, object + 0x10, -1, 1.0f, 0.0f);
        moby_set_state(object, 1, 0);
    }
}
