#include "include_asm.h"

#include "common.h"

extern void moby_set_state(u8 *arg0, s32 arg1, s32 arg2);

extern s32 math_random_int_below(s32 arg0);

extern s32 arena_get_fighter_count(s32 arg0);

extern s32 g_joba_max_fighter_count __attribute__((sda));

extern s32 g_joba_attack_random_range __attribute__((sda));

extern f32 g_l11_unused_float;

extern void joba_beams_update(u8 *arg0);

extern void gfx_add_draw_callback_third(void *arg0, u8 *arg1);

extern void joba_beams_draw(u8 *arg0);

extern void UpdateJobaFourFramePoses(u8 *arg0);

extern void gfx_update_color_fade(u8 *arg0, void *arg1);

extern void set_moby_color(u8 *arg0, u32 arg1, u32 arg2, u32 arg3);

extern void value_set_and_smooth(u8 *arg0, void *arg1, f32 arg2, s32 arg3, s32 arg4);

extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);

extern f32 moby_update_aim_target_strength(u8 *arg0, u8 *arg1);

extern void gfx_start_color_fade(u8 *arg0, u8 *arg1);

/* The prototype returns a value: that keeps $v0 busy after the call, as the retail has it. */
extern s32 part_spawn_damage_debris(u8 *arg0, u8 *arg1, u8 *arg2);

extern s32 weapon_select_aim_target(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);

extern void joba_enemy_reset(u8 *arg0);

/* The 7.0 the timed effect is compared against, reached through $gp. */
extern f32 g_joba_damage_threshold __attribute__((sda));

extern s32 g_enemy_damage_accum[];

/* Runs the object's timer down, keeps the shared step counter in step with it, and retires
   the object when the timed effect is over. */
/* Applies damage to the enemy, adds to a score counter, and removes the enemy when it runs
   out of health. */
void joba_enemy_apply_damage(u8 *moby_arg) {
    u8 *moby = moby_arg;
    u8 *vars;
    u8 *attacker;
    u8 *hit_info;
    u32 table_offset;
    f32 damage;

    if (*(u8 *)(moby + 0x20) == 0) {
        return;
    }
    vars = *(u8 **)(moby + 0x68);
    attacker = part_find_owned_effect_slot(moby, 0x10000, 0);
    damage = moby_update_aim_target_strength(moby, attacker);
    if (attacker != 0) {
        if (*(u8 *)(moby + 0x20) >= 3) {
            *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - damage;
            /* The index is a byte offset into the table: keeping it in a variable leaves
               the constant out of the symbol's address, as the retail has it. */
            table_offset = *(u8 *)(vars + 0x37) * 4 + 0xE0;
            *(s32 *)((u8 *)g_enemy_damage_accum + table_offset) += (s32)(damage * 32.0f);
            if (*(f32 *)(attacker + 0x2C) != 0.0f) {
                hit_info = vars + 0x70;
                gfx_start_color_fade(moby, hit_info);
                if (*(f32 *)(attacker + 0x2C) >= g_joba_damage_threshold || *(f32 *)(vars + 0x20) <= 0.0f) {
                    gfx_start_color_fade(moby, hit_info);
                    moby_set_state(moby, 8, -1);
                }
            }
        }
    }
    *(u8 *)(moby + 0xA8) = 0xFF;
    part_spawn_damage_debris(moby, vars + 0x50, vars + 0x20);
    if (*(u8 *)(moby + 0x20) >= 2 && *(u8 *)(vars + 0x2E) == 2) {
        *(s32 *)(vars + 0x20) = 0;
        joba_enemy_reset(moby);
    }
    *(s32 *)(vars + 0x258) = weapon_select_aim_target(moby, *(s32 *)(vars + 0x25C), 0, 0, 200.0f, 200.0f);
}

/* Arms the object's two state records through two callbacks and the class setup, then, when
   the twin record is clear, starts the 0x2A0 animation. */

/* Retires the object and copies two measured state bytes into its state block. */
/* Once the enemy has no pending counters, picks its next state (6 or 7) with a random
   roll. */
void joba_enemy_choose_attack_state(u8 *moby_arg) {
    u8 *moby = moby_arg;
    s32 vars = *(s32 *)(moby + 0x68);
    if (*(u16 *)(vars + 0x278) >= 2)
        return;
    if (*(u16 *)(vars + 0x27A) >= 2)
        return;
    if (math_random_int_below(g_joba_attack_random_range) != 0
        && arena_get_fighter_count(*(s32 *)(moby + 0xB8)) < g_joba_max_fighter_count) {
        moby_set_state(moby, 7, -1);
    } else {
        moby_set_state(moby, 6, -1);
    }
}

extern void matrix_mul_vec3(void *out, void *in, void *matrix);

extern void FastVecAdd(void *out, void *in, void *matrix);

extern f32 mat_fast_helper_a(f32 a0, f32 a1);

extern void euler_rotation_basis(void *a0, void *a1);

extern s32 FloatToInt(f32 a0);

extern void enemy_init_state(u8 *a0, s32 a1, s32 a2);

extern void security_robot_init(u8 *a0, s32 a1, s32 a2);

extern void smasher_robot_init(u8 *a0, s32 a1, s32 a2);

extern void flamethrower_robot_init(u8 *a0, s32 a1, s32 a2);

extern void drone_init_state(u8 *a0, s32 a1, s32 a2);

extern void path_mover_reset(u8 *a0, s32 a1);

extern u32 g_joba_child_offset_step __attribute__((sda));

extern u8 g_hero_state[];

/* Places the measured point on the state's three vertices, then walks them: each one gets
   its angle to the shared origin and the class call its identifier names. */
/* Puts three child objects in place and turns each one toward the player. */
void joba_place_child_mobys(u8 *moby_arg) {
    u8 *moby = moby_arg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *part;
    u8 *hero;
    f32 local_point[4];
    s32 offset_total;
    s32 i;

    local_point[0] = 0.0f;
    local_point[1] = -9.0f;
    local_point[2] = -3.0f;
    local_point[3] = 0.0f;
    matrix_mul_vec3(local_point, local_point, moby + 0xC0);
    FastVecAdd(local_point, local_point, moby + 0x10);

    if (*(u8 **)(vars + 0x10) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x10) = local_point[0] - 2.0f;
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x14) = local_point[1];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x18) = local_point[2];
        *(f32 *)(*(u8 **)(vars + 0x10) + 0x1C) = local_point[3];
    }
    if (*(u8 **)(vars + 0x14) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x10) = local_point[0];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x14) = local_point[1] + 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x18) = local_point[2];
        *(f32 *)(*(u8 **)(vars + 0x14) + 0x1C) = local_point[3];
    }
    if (*(u8 **)(vars + 0x18) != 0) {
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x10) = local_point[0];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x14) = local_point[1] - 1.0f;
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x18) = local_point[2];
        *(f32 *)(*(u8 **)(vars + 0x18) + 0x1C) = local_point[3];
    }

    hero = g_hero_state;
    part = *(u8 **)(vars + 0x10);
    offset_total = 0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            part = *(u8 **)(vars + 0x14);
        }
        if (i == 2) {
            part = *(u8 **)(vars + 0x18);
        }
        if (part == 0) {
            continue;
        }
        *(s32 *)(part + 0xF0) = 0;
        *(f32 *)(part + 0xF4) = 0.0f;
        *(f32 *)(part + 0xF8) = mat_fast_helper_a(*(f32 *)(hero + 0x80) - *(f32 *)(part + 0x10),
                                          *(f32 *)(hero + 0x84) - *(f32 *)(part + 0x14));
        *(s32 *)(part + 0xFC) = 0;
        euler_rotation_basis(part + 0xC0, part + 0xF0);
        switch (*(s16 *)(part + 0xAA)) {
        case 0xD98: /* moby class 3480 */
            security_robot_init(part, offset_total, 0);
            break;
        case 0xDCF: /* moby class 3535 */
            smasher_robot_init(part, offset_total, 0);
            break;
        case 0xDF4: /* moby class 3572 */
            flamethrower_robot_init(part, offset_total, 0);
            break;
        case 0xDF7: /* moby class 3575 */
            *(f32 *)(part + 0x18) += 0.5f;
            drone_init_state(part, FloatToInt((f32)offset_total * 0.16666667f), 0);
            break;
        case 0xDF9: /* moby class 3577 */
            path_mover_reset(part, offset_total);
            break;
        case 0xD37: /* moby class 3383 */
            enemy_init_state(part, offset_total, 0);
            break;
        }
        offset_total += g_joba_child_offset_step;
    }

    *(u8 **)(vars + 0x10) = 0;
    *(u8 **)(vars + 0x14) = 0;
    *(u8 **)(vars + 0x18) = 0;
}
