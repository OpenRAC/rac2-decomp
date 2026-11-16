#include "include_asm.h"

#include "common.h"
extern s32 point_in_path_xy(f32 *point, f32 *vertices, s32 count);
extern u8 g_moby_l11_script_data_2[];
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((section(".sdata")));
extern s32 moby_has_free_child_slot_state2(u8 *);
extern s32 moby_has_any_child_slot_used(u8 *);
extern s32 func_417238(s32);
extern s32 func_417270(s32);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table;
extern void security_robot_deactivate(u8 *);
extern void smasher_robot_deactivate_pal(u8 *);
extern void flamethrower_robot_deactivate_pal(u8 *);
extern void drone_reset_to_idle_pal(u8 *);
extern void fighter_reset_to_idle(u8 *);
extern void enemy_reset_to_idle_pal(u8 *);
extern void chain_creature_clear_sound_flags(u8 *);
extern void drone_kill_with_effects_pal(u8 *);
extern void joba_enemy_reset(u8 *);
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));
extern u8 *g_arena_camera_table __attribute__((sda));
extern s32 g_tribe_group_limit[] __attribute__((sda));
extern s16 moby_get_vars_counter(u8 *);
extern s32 moby_get_busy_flag(u8 *);
extern s32 arena_is_target_outside(u8 *, u8 *, s32);
extern s32 drone_is_state_at_least_four(u8 *);
extern u8 g_hero_state[];
extern u8 g_music_state[];

void arena_run_member_handlers_pal(u8 *obj)
{
    s32 index = *(s32 *)(*(u8 **)(obj + 0x68) + 0xC0);
    u16 *p;
    u8 *list;
    u8 *entry;

    if (index == 0xFF)
        return;
    list = g_group_id_lists[index];
    if (list == 0)
        return;
    p = (u16 *)list;
    do {
        entry = D_L11_001B359C_base[0] + ((*p & 0x7FFF) << 8);
        switch (*(s16 *)(entry + 0xAA)) {
        case 0xD98:
            security_robot_deactivate(entry);
            break;
        case 0xDCF:
            smasher_robot_deactivate_pal(entry);
            break;
        case 0xDF4:
            flamethrower_robot_deactivate_pal(entry);
            break;
        case 0xDF7:
            drone_reset_to_idle_pal(entry);
            break;
        case 0xDF9:
            fighter_reset_to_idle(entry);
            break;
        case 0xD37:
            enemy_reset_to_idle_pal(entry);
            break;
        case 0xD4A:
            chain_creature_clear_sound_flags(entry);
            break;
        case 0xD4B:
            drone_kill_with_effects_pal(entry);
            break;
        case 0xB3A:
            joba_enemy_reset(entry);
            break;
        }
    } while (*(s16 *)p++ >= 0);
}

