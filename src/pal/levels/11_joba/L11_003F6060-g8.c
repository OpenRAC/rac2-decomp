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
void joba_enemy_apply_damage_pal(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u32 off;
    f32 f2;

    if (*(u8 *)(s0 + 0x20) == 0) {
        return;
    }
    s1 = *(u8 **)(s0 + 0x68);
    s2 = part_find_owned_effect_slot(s0, 0x10000, 0);
    f2 = moby_update_aim_target_strength(s0, s2);
    if (s2 != 0) {
        if (*(u8 *)(s0 + 0x20) >= 3) {
            *(f32 *)(s1 + 0x20) = *(f32 *)(s1 + 0x20) - f2;
            /* The index is a byte offset into the table: keeping it in a variable leaves
               the constant out of the symbol's address, as the retail has it. */
            off = *(u8 *)(s1 + 0x37) * 4 + 0xE0;
            *(s32 *)((u8 *)g_enemy_damage_accum + off) += (s32)(f2 * 32.0f);
            if (*(f32 *)(s2 + 0x2C) != 0.0f) {
                s3 = s1 + 0x70;
                gfx_start_color_fade(s0, s3);
                if (*(f32 *)(s2 + 0x2C) >= g_joba_damage_threshold || *(f32 *)(s1 + 0x20) <= 0.0f) {
                    gfx_start_color_fade(s0, s3);
                    moby_set_state(s0, 8, -1);
                }
            }
        }
    }
    *(u8 *)(s0 + 0xA8) = 0xFF;
    part_spawn_damage_debris(s0, s1 + 0x50, s1 + 0x20);
    if (*(u8 *)(s0 + 0x20) >= 2 && *(u8 *)(s1 + 0x2E) == 2) {
        *(s32 *)(s1 + 0x20) = 0;
        joba_enemy_reset(s0);
    }
    *(s32 *)(s1 + 0x258) = weapon_select_aim_target(s0, *(s32 *)(s1 + 0x25C), 0, 0, 200.0f, 200.0f);
}
