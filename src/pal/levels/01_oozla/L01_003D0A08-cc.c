#include "names.h"
/* func_PAL_L01_003D0A08, the PAL copy of func_L01_003CC930: the same C with 50 Hz values.
 * Timers 240, 180, 120, 40, 20 become 200, 150, 100, 33, 17; per-frame rates are scaled by 6/5
 * (0.05f and 0.050000004f both become 0.060000002f, so retail keeps it in a saved register);
 * 1/60 becomes 0.020000001f. The three random values passed to func_002E45B8 are floats, so
 * PAL's (x * 5 + 2) / 6 is written out with a multiply by the constant 1/6.
 * -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-hazard-labels, as the template's unit.
 */
#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; } Hero;

extern char g_hero_state[];
extern s32 g_oozla_intro_stage;
extern u8 *g_moby_l01_table;
extern u8 *g_swamp_patrol_positions;
extern s32 g_hero_l01_control_mode;
extern s32 g_current_map_index;
extern f32 g_swamp_arm_hero_offset_scale __attribute__((sda));
extern s32 g_swamp_arm_particle_type_a __attribute__((sda));
extern s32 g_swamp_arm_particle_type_b __attribute__((sda));
extern f32 g_swamp_arm_random_min_a __attribute__((sda));
extern f32 g_swamp_arm_random_max_a __attribute__((sda));
extern f32 g_swamp_arm_random_min_b __attribute__((sda));
extern f32 g_swamp_arm_random_max_b __attribute__((sda));
extern f32 g_swamp_arm_random_min_c __attribute__((sda));
extern f32 g_swamp_arm_random_max_c __attribute__((sda));
extern f32 g_swamp_arm_vec_e_w __attribute__((sda));
extern f32 g_swamp_arm_vec_h_w __attribute__((sda));
extern f32 g_swamp_arm_rise_speed __attribute__((sda));
extern f32 g_swamp_arm_spin_x_speed __attribute__((sda));
extern f32 g_swamp_arm_spin_y_speed __attribute__((sda));
extern s32 g_swamp_arm_particle_count __attribute__((sda));
extern s32 g_swamp_arm_anim_frame_limit __attribute__((sda));
extern s32 g_swamp_arm_frame_limit_table[4] __attribute__((sda));
extern u8 *g_path_l01_table[];
typedef struct { u8 pad[0x160]; f32 f160; s32 pad164; s32 i168; s32 i16C; } L01Fx;
extern L01Fx g_drive_settings;
extern u8 g_moby_group_flags[];

extern s32 func_001163B0(void);
extern s32 func_002D77E8(void);
extern s32 func_002D9308(u8);
extern void func_002E3470(void *, void *, void *);
extern void func_002E34A0(void *, void *, void *);
extern void func_002E34E0(void *, void *, f32);
extern f32 func_002E35A0(void *);
extern f32 func_002E3650(void *, void *);
extern void func_002E3738(void *, void *, f32);
extern void func_002E37D0(void *, void *, f32);
extern f32 func_002E3B10(f32, f32);
extern f32 func_002E4460(f32, f32);
extern f32 func_002E44A8(f32, f32);
extern f32 func_002E4548(f32, f32);
extern s32 func_002E45B8(f32);
extern void func_00306250(u8 *);
extern f32 func_00306448(u8 *);
extern void func_00307390(u8 *, s32, void *);
extern void func_00307E70(u8);
extern void SetDeathBits_pal(u8 *, s32, s32);
extern void anim_start_blended_pal(u8 *, s32, s32, s32);
extern void func_00310418(u8 *, s32, s32);
extern s32 func_003104E8(s32);
extern s32 func_00310528(s32, s32);
extern f32 func_00310580(f32, f32);
extern void func_00310D28(u8 *, void *, f32, f32, f32, f32);
extern f32 func_00311A00(void *, s32, f32);
extern s32 func_00311B48(void *, void *, s32);
extern s32 func_00312B68(u8 *, s32, s32);
extern void func_00316348(void *, f32);
extern u8 *func_00327360(void *, void *, void *, s32, s32, s32, s32, s32, s32);
extern s32 func_00337A60(void *, void *, void *, s32);
extern void func_0034ECD0(void *, void *);
extern s32 func_00355780(s32, s32, u8 *);
extern s32 func_00355828(s32, s32, u8 *, s32);
extern void swamp_monster_spawn_splash_pal(u8 *, s32, s32, s32);
extern void swamp_monster_release_attack_slot(u8 *);
extern void swamp_monster_arm_init_pal(u8 *);
extern void swamp_monster_release_arm_timers(u8 *);
extern void UpdateOozlaLinkedGroupDamage_pal(u8 *);
extern void swamp_monster_test_attack_segment_hits_hero(u8 *, void *, void *, u8, void *);

/* Updates a swamp monster arm each frame: it rises, follows the hero, swings to hit him, throws up mud and sinks again (PAL: 50 Hz timings). */
void swamp_monster_arm_update_pal(u8 *moby)
{
    f32 vec_a[4];
    f32 vec_b[4];
    f32 vec_c[4];
    f32 vec_d[4];
    f32 vec_e[4];
    f32 vec_f[4];
    f32 vec_g[4];
    f32 vec_h[4];
    u8 *vars = 0;
    u8 *linked_moby_1 = 0;
    u8 *linked_moby_2 = 0;
    u8 *patrol_point = 0;
    u8 *target_pos = 0;
    u8 *unused_target = 0;
    u8 *path_a = 0;
    u8 *path_b = 0;
    u8 *moby_pos = 0;
    u8 *moby_pos_b = 0;
    u8 *moby_pos_c = 0;
    u8 *particle = 0;
    s32 start_attack = 0;
    s32 seg_a = 0;
    s32 seg_b = 0;
    s32 j = 0;
    s32 frames_a = 0;
    s32 frames_b = 0;
    s32 frames_c = 0;
    f32 arm_dist = 0.0f;
    f32 face_angle = 0.0f;
    f32 face_angle_b = 0.0f;
    f32 ground_z = 0.0f;
    f32 drag_speed = 0.0f;
    f32 turn_dir_a = 0.0f;
    f32 turn_dir_b = 0.0f;
    f32 turn_dir_c = 0.0f;
    f32 turn_dir_d = 0.0f;
    u8 *linked_moby_0 = 0;
    u8 *linked_moby_3 = 0;
    u8 *hero_target_a = 0;
    u8 *hero_target_b = 0;
    s32 level = 0;
    f32 blend = 0.0f;
    f32 rand_a = 0.0f;
    f32 rand_b = 0.0f;
    f32 rand_c = 0.0f;
    s32 ground_kind = 0;
    s32 on_path = 0;
    s32 splash_wait_a = 0;
    s32 splash_wait_b = 0;
    s32 splash_wait_c = 0;
    f32 anim_speed_a = 0.0f;
    f32 new_yaw_a = 0.0f;
    f32 new_yaw_b = 0.0f;
    f32 new_yaw_c = 0.0f;
    f32 new_yaw_d = 0.0f;
    f32 spin_x = 0.0f;
    f32 spin_y = 0.0f;
    f32 rise = 0.0f;
    f32 anim_speed_b = 0.0f;
    f32 anim_speed_c = 0.0f;
    s32 splash_wait_d = 0;

    vars = *(u8 **)(moby + 0x68);
    UpdateOozlaLinkedGroupDamage_pal(moby);
    switch (moby[0x95]) {
    case 0:
        if (g_oozla_intro_stage < 2)
            return;
        swamp_monster_arm_init_pal(moby);
        break;
    case 1:
        linked_moby_1 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
        if (*(s32 *)(vars + 0xC8) != 0)
            func_00307390(moby, 7, linked_moby_1 + 0x10);
        else
            func_00307390(moby, 8, linked_moby_1 + 0x10);
        qcopy(linked_moby_1 + 0xF0, moby + 0xF0);
        switch (moby[0x20]) {
        case 0:
            start_attack = 0;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE0);
            if (*(s32 *)(vars + 0x74) == 1) {
                if (*(s32 *)(vars + 0x7C) == 1)
                    start_attack = 1;
            }
            if (*(s32 *)(vars + 0xC0) > 0)
                start_attack = 1;
            linked_moby_0 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (func_00312B68(linked_moby_0, 0x10001, 0) != 0)
                start_attack = 1;
            if (start_attack) {
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                *(s32 *)(vars + 0xBC) = 0;
                func_00310418(moby, 1, -1);
            }
            break;
        case 1:
            if (*(s32 *)(vars + 0xBC) != 0)
                break;
            linked_moby_2 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (*(s32 *)(vars + 0xC8) != 0) {
                if (moby[0x43] != 10)
                    anim_start_blended_pal(moby, 10, 0, 7);
                anim_start_blended_pal(linked_moby_2, 8, 0, 7);
            } else {
                if (moby[0x43] != 6)
                    anim_start_blended_pal(moby, 6, 0, 7);
            }
            func_00355828(0, 0, linked_moby_2, 0xB1A);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 2, 1);
            break;
        case 2:
            splash_wait_a = func_003104E8(4);
            if (splash_wait_a == 0)
                swamp_monster_spawn_splash_pal(moby, 3, 10, 1);
            if (!(moby[0x60] & 2))
                break;
            linked_moby_3 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            linked_moby_3[0x95] = 1;
            if (*(s32 *)(vars + 0xEC) == -1)
                goto done;
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            *(s32 *)(vars + 0xBC) = 33;
            if (moby[0x43] != 0)
                anim_start_blended_pal(moby, 0, 0, 1);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
            func_00310418(moby, 0, 4);
            break;
        }
        break;
    case 2:
        splash_wait_b = func_003104E8(5);
        if (splash_wait_b == 0)
            swamp_monster_spawn_splash_pal(moby, 3, 10, 1);
        if ((moby[0x42] == 6 || moby[0x42] == 10) && (moby[0x60] & 2)) {
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            if (moby[0x43] != 0)
                anim_start_blended_pal(moby, 0, 0, 0);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 4);
        }
        break;
    case 3:
        splash_wait_c = func_003104E8(5);
        if (splash_wait_c == 0)
            swamp_monster_spawn_splash_pal(moby, 3, 10, 1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 200;
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, func_00310528(10, 15));
            anim_speed_a = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = anim_speed_a;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xEC);
            func_00310418(moby, 0, 5);
        }
        break;
    case 4:
        *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
        if (*(s32 *)(vars + 0x74) == 1 && *(s32 *)(vars + 0x7C) == 1) {
            if (*(s32 *)(vars + 0xBC) == 0)
                *(s32 *)(vars + 0xBC) = 100;
            if (*(s32 *)(vars + 0xBC) == 1) {
                if (*(f32 *)(vars + 0xD4) > 0.0f)
                    *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
                *(f32 *)(moby + 0x48) = 1.0f;
                if (moby[0x43] != 0)
                    anim_start_blended_pal(moby, 0, 0, func_00310528(10, 15));
                func_00310418(moby, 0, 3);
            }
        }
        break;
    case 5:
        if (*(s32 *)(vars + 0x74) == 1) {
            func_00337A60(vars + 0x90, vars + 0x60, g_path_l01_table[*(s32 *)(vars + 0xB8)] + 0x10, *(s32 *)g_path_l01_table[*(s32 *)(vars + 0xB8)]);
            *(s32 *)(vars + 0xC0) = 200;
            target_pos = vars + 0x90;
        } else {
            qcopy(vars + 0x90, vars + 0x80);
            target_pos = vars + 0x90;
        }
        hero_target_a = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if (*(u8 **)(vars + 0x70) == hero_target_a) {
            func_002E34E0(vec_a, &((Hero *)g_hero_state)->b[0x110], g_swamp_arm_hero_offset_scale);
            func_002E3470(vec_a, vec_a, *(u8 **)(vars + 0x70) + 0x10);
        } else {
            qcopy(vec_a, *(u8 **)(vars + 0x70) + 0x10);
        }
        moby_pos = moby + 0x10;
        func_002E34A0(vec_b, target_pos, moby_pos);
        func_002E34E0(vec_b, vec_b, 0.060000002f);
        func_002E37D0(vec_b, vec_b, 0.060000002f);
        vec_b[2] = 0.0f;
        func_002E3470(moby_pos, moby_pos, vec_b);
        turn_dir_a = 0.09599312f;
        if (vars[0xDD] != 0)
            turn_dir_a = -0.09599312f;
        new_yaw_a = func_002E4460(*(f32 *)(moby + 0xF8), turn_dir_a);
        *(f32 *)(moby + 0xF8) = new_yaw_a;
        face_angle = func_002E3B10(vec_a[0] - *(f32 *)(moby + 0x10), vec_a[1] - *(f32 *)(moby + 0x14));
        func_00310D28(moby, vars + 0xCC, face_angle, 0.0033510327f, 0.1f, 0.16755164f);
        if (moby[0x60] & 2)
            *(f32 *)(moby + 0x48) = func_00310580(0.8f, 1.2f);
        if (g_hero_l01_control_mode != 2 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F && *(s32 *)(vars + 0xC4) == 0 &&
            (moby[0x21] == 0xFF || **(s32 **)(vars + 0xD8) <= 0) && func_002E3650(moby_pos, vars + 0x60) < 35.0f &&
            (face_angle = func_002E3B10(vec_a[0] - *(f32 *)(moby + 0x10), vec_a[1] - *(f32 *)(moby + 0x14)),
             func_002E4548(*(f32 *)(moby + 0xF8), face_angle) < 0.034906588f)) {
            vars[0xDC] = 1;
            if (moby[0x21] != 0xFF)
                **(s32 **)(vars + 0xD8) += 1;
            if (moby[0x43] != 2)
                anim_start_blended_pal(moby, 2, 0, func_00310528(7, 12));
            func_00310418(moby, 0, 6);
            vars[0xDE] = 0;
        } else if (*(s32 *)(vars + 0xC0) == 0) {
            if (moby[0x43] != 6)
                anim_start_blended_pal(moby, 6, 0, 0x14);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 2);
        }
        turn_dir_b = 0.09599312f;
        if (vars[0xDD] != 0)
            turn_dir_b = -0.09599312f;
        new_yaw_b = func_002E44A8(*(f32 *)(moby + 0xF8), turn_dir_b);
        *(f32 *)(moby + 0xF8) = new_yaw_b;
        break;
    case 6:
        moby_pos_b = moby + 0x10;
        arm_dist = func_00306448(moby);
        func_002E34A0(vec_a, vars + 0x90, moby_pos_b);
        func_002E34E0(vec_a, vec_a, 0.060000002f);
        func_002E37D0(vec_a, vec_a, 0.060000002f);
        vec_a[2] = 0.0f;
        func_002E3470(moby_pos_b, moby_pos_b, vec_a);
        if (arm_dist > 46.0f && arm_dist < 56.0f) {
            for (seg_a = 1; seg_a < 8; seg_a++) {
                func_00307390(moby, seg_a, vec_b);
                func_00307390(moby, seg_a + 1, vec_d);
                func_002E3738(vec_f, moby + 0xD0, 0.3f);
                func_002E3738(vec_g, moby + 0xD0, 0.3f);
                func_002E3470(vec_c, vec_b, vec_f);
                func_002E3470(vec_e, vec_d, vec_g);
                func_002E34A0(vec_b, vec_b, vec_f);
                func_002E34A0(vec_d, vec_d, vec_g);
                swamp_monster_test_attack_segment_hits_hero(moby, vec_b, vec_d, vars[0x34], vars + 0xDE);
                swamp_monster_test_attack_segment_hits_hero(moby, vec_c, vec_e, vars[0x34], vars + 0xDE);
            }
            func_00307390(moby, 6, vec_b);
            qcopy(vec_c, vec_b);
            vec_b[2] += 0.5f;
            vec_d[2] += 2.0f;
            vec_c[2] += 2.0f;
            vec_e[2] += 0.5f;
            swamp_monster_test_attack_segment_hits_hero(moby, vec_b, vec_d, vars[0x34], vars + 0xDE);
            swamp_monster_test_attack_segment_hits_hero(moby, vec_c, vec_e, vars[0x34], vars + 0xDE);
        }
        if (arm_dist >= 56.0f && vars[0xDE] == 0) {
            func_00355780(2, 0, moby);
            vars[0xDE] = 1;
        }
        level = func_002D9308(moby[0xB0]);
        g_swamp_arm_anim_frame_limit = g_swamp_arm_frame_limit_table[level - 1];
        if (arm_dist < (f32)g_swamp_arm_anim_frame_limit &&
            (arm_dist < 20.0f || (((Hero *)g_hero_state)->i[0x340 / 4] != 0 && ((Hero *)g_hero_state)->h[0x34E / 2] == 0 &&
                           ((Hero *)g_hero_state)->i[0x229C / 4] != 4))) {
            turn_dir_c = 0.09599312f;
            if (vars[0xDD] != 0)
                turn_dir_c = -0.09599312f;
            new_yaw_c = func_002E4460(*(f32 *)(moby + 0xF8), turn_dir_c);
            *(f32 *)(moby + 0xF8) = new_yaw_c;
            hero_target_b = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
            if (*(u8 **)(vars + 0x70) == hero_target_b) {
                func_002E34E0(vec_b, &((Hero *)g_hero_state)->b[0x110], 55.0f - arm_dist);
                func_002E3470(vec_b, vec_b, *(u8 **)(vars + 0x70) + 0x10);
            } else {
                qcopy(vec_b, *(u8 **)(vars + 0x70) + 0x10);
            }
            face_angle_b = func_002E3B10(vec_b[0] - *(f32 *)(moby + 0x10), vec_b[1] - *(f32 *)(moby + 0x14));
            func_00310D28(moby, vars + 0xCC, face_angle_b, 0.0033510327f, 0.1f, 0.16755164f);
            turn_dir_d = 0.09599312f;
            if (vars[0xDD] != 0)
                turn_dir_d = -0.09599312f;
            new_yaw_d = func_002E44A8(*(f32 *)(moby + 0xF8), turn_dir_d);
            *(f32 *)(moby + 0xF8) = new_yaw_d;
        }
        if (arm_dist > 55.0f && arm_dist < 58.0f) {
            if (arm_dist <= 56.0f) {
                g_drive_settings.f160 = 0.2f;
                g_drive_settings.i168 = 17;
                g_drive_settings.i16C = 0;
            }
            ground_z = *(f32 *)(moby + 0x18);
            for (seg_b = 1; seg_b < 8; seg_b++) {
                func_00307390(moby, seg_b, vec_b);
                ground_z = func_00311A00(vec_b, 2, 0.5f);
                ground_kind = func_002D77E8();
                if (ground_kind != 3)
                    break;
            }
            vec_b[2] = ground_z;
            func_00307390(moby, 8, vec_c);
            vec_c[2] = ground_z;
            func_002E34A0(vec_c, vec_c, vec_b);
            qzero(vec_h);
            vec_h[3] = g_swamp_arm_vec_h_w;
            for (j = 0; j < g_swamp_arm_particle_count; j++) {
                blend = func_00310580(0.0f, 1.0f);
                func_002E34E0(vec_d, vec_c, blend);
                func_00316348(vec_d, 0.1f);
                func_002E3470(vec_d, vec_d, vec_b);
                spin_x = func_00310580(-(g_swamp_arm_spin_x_speed * 0.020000001f), g_swamp_arm_spin_x_speed * 0.020000001f);
                func_002E3738(vec_f, moby + 0xD0, spin_x);
                spin_y = func_00310580(-(g_swamp_arm_spin_y_speed * 0.020000001f), g_swamp_arm_spin_y_speed * 0.020000001f);
                func_002E3738(vec_g, moby + 0xC0, spin_y);
                func_002E3470(vec_e, vec_f, vec_g);
                rise = func_00310580(0.0f, g_swamp_arm_rise_speed * 0.020000001f);
                vec_e[2] = rise;
                vec_e[3] = g_swamp_arm_vec_e_w;
                rand_a = func_00310580(g_swamp_arm_random_min_a, g_swamp_arm_random_max_a);
                frames_a = func_002E45B8((rand_a * 5.0f + 2.0f) * 0.16666667f);
                rand_b = func_00310580(g_swamp_arm_random_min_b, g_swamp_arm_random_max_b);
                frames_b = func_002E45B8((rand_b * 5.0f + 2.0f) * 0.16666667f);
                rand_c = func_00310580(g_swamp_arm_random_min_c, g_swamp_arm_random_max_c);
                frames_c = func_002E45B8((rand_c * 5.0f + 2.0f) * 0.16666667f);
                particle = func_00327360(vec_d, vec_e, vec_h, g_swamp_arm_particle_type_a, g_swamp_arm_particle_type_b, frames_a, frames_b, frames_c, -1);
                if (particle != 0 && (func_001163B0() & 1))
                    particle[3] = 0x48;
            }
        }
        if (moby[0x60] & 2) {
            swamp_monster_release_attack_slot(moby);
            *(s32 *)(vars + 0xC4) = 150;
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, func_00310528(10, 15));
            anim_speed_b = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = anim_speed_b;
            func_00310418(moby, 0, 5);
        }
        break;
    case 7:
        moby[0xA8] = 0xFF;
        moby_pos_c = moby + 0x10;
        func_002E3470(vec_a, moby_pos_c, vars + 0xA0);
        path_a = g_path_l01_table[*(s32 *)(vars + 0xB8)];
        on_path = func_00311B48(vec_a, path_a + 0x10, *(s32 *)path_a);
        if (on_path != 0) {
            qcopy(moby_pos_c, vec_a);
        } else {
            path_b = g_path_l01_table[*(s32 *)(vars + 0xB8)];
            func_00337A60(moby_pos_c, vec_a, path_b + 0x10, *(s32 *)path_b);
            func_002E34A0(vec_b, vars + 0x80, moby_pos_c);
            func_002E3738(vec_b, vec_b, 0.040000003f);
            func_002E3470(moby_pos_c, moby_pos_c, vec_b);
        }
        drag_speed = func_002E35A0((vars + 0xA0)) - 0.0044f;
        if (drag_speed < 0.0f) {
            drag_speed = 0.0f;
        }
        func_002E3738((vars + 0xA0), (vars + 0xA0), drag_speed);
        if (!(moby[0x60] & 2))
            break;
        qzero_nc((vars + 0xA0));
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            if (moby[0x42] == 3) {
                if (moby[0x43] != 4)
                    anim_start_blended_pal(moby, 4, 0, 10);
            } else {
                func_00310418(moby, 0, 9);
            }
        } else {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 200;
            *(s32 *)(vars + 0xC4) = 0;
            if (moby[0x43] != 1)
                anim_start_blended_pal(moby, 1, 0, func_00310528(10, 15));
            anim_speed_c = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = anim_speed_c;
            func_00310418(moby, 0, 5);
        }
        break;
    case 8:
        splash_wait_d = func_003104E8(4);
        if (splash_wait_d == 0)
            swamp_monster_spawn_splash_pal(moby, 3, 10, 1);
        if (!(moby[0x60] & 2))
            break;
    case 9:
        SetDeathBits_pal(moby, 0x200, 3);
        if (*(s32 *)(vars + 0xE4) != -1 && !(g_moby_group_flags[moby[0xB0] + (g_current_map_index << 4)] & 0x80)) {
            func_00307E70(moby[0xB0]);
            patrol_point = g_swamp_patrol_positions + (*(s32 *)(vars + 0xE4) << 7);
            func_0034ECD0(patrol_point + 0x30, patrol_point + 0x70);
        }
    done:
        func_00306250(moby);
        return;
    }
    swamp_monster_release_arm_timers(moby);
}
