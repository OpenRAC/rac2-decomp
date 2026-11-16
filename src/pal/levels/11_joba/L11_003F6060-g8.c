#include "include_asm.h"
#include "common.h"
extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);
extern s32 math_random_int_below(s32 arg0);
extern s32 arena_get_fighter_count(s32 arg0);
extern s32 g_joba_max_fighter_count __attribute__((sda));
extern s32 g_joba_attack_random_range __attribute__((sda));
extern f32 g_l11_unused_float;
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern f32 moby_update_aim_target_strength(u8 *arg0, u8 *arg1);
extern void gfx_start_color_fade(u8 *arg0, u8 *arg1);
extern s32 part_spawn_damage_debris(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 weapon_select_aim_target(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);
extern void joba_enemy_reset(u8 *arg0);
extern f32 g_joba_damage_threshold __attribute__((sda));
extern s32 g_enemy_damage_accum[];
extern f32 mat_fast_helper_a(f32 a0, f32 a1);
extern s32 FloatToInt(f32 a0);
extern u32 g_joba_child_offset_step __attribute__((sda));
extern u8 g_hero_state[];

/* Runs the object's timer down, keeps the shared step counter in step with it, and retires
   the object when the timed effect is over. */
void joba_enemy_apply_damage_pal(u8 *moby) {
    u8 *enemy = moby;
    u8 *vars;
    u8 *hit_slot;
    u8 *color_ptr;
    u32 table_offset;
    f32 damage;

    if (*(u8 *)(enemy + 0x20) == 0) {
        return;
    }
    vars = *(u8 **)(enemy + 0x68);
    hit_slot = part_find_owned_effect_slot(enemy, 0x10000, 0);
    damage = moby_update_aim_target_strength(enemy, hit_slot);
    if (hit_slot != 0) {
        if (*(u8 *)(enemy + 0x20) >= 3) {
            *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - damage;
            /* The index is a byte offset into the table: keeping it in a variable leaves
               the constant out of the symbol's address, as the retail has it. */
            table_offset = *(u8 *)(vars + 0x37) * 4 + 0xE0;
            *(s32 *)((u8 *)g_enemy_damage_accum + table_offset) += (s32)(damage * 32.0f);
            if (*(f32 *)(hit_slot + 0x2C) != 0.0f) {
                color_ptr = vars + 0x70;
                gfx_start_color_fade(enemy, color_ptr);
                if (*(f32 *)(hit_slot + 0x2C) >= g_joba_damage_threshold || *(f32 *)(vars + 0x20) <= 0.0f) {
                    gfx_start_color_fade(enemy, color_ptr);
                    moby_set_state(enemy, 8, -1);
                }
            }
        }
    }
    *(u8 *)(enemy + 0xA8) = 0xFF;
    part_spawn_damage_debris(enemy, vars + 0x50, vars + 0x20);
    if (*(u8 *)(enemy + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2) {
        *(s32 *)(vars + 0x20) = 0;
        joba_enemy_reset(enemy);
    }
    *(s32 *)(vars + 0x258) = weapon_select_aim_target(enemy, *(s32 *)(vars + 0x25C), 0, 0, 200.0f, 200.0f);
}
