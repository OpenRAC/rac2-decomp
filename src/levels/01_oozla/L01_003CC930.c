#include "names.h"
/* func_L01_003CC930 (4,624 bytes, 1 place). -O2 -G16 -Wa,-G16 -ffunction-sections
 * -frac2-hazard-labels.
 * - Plain (not sda) scalars for D_L01_001B255C / 001B2088 / 001A8F40 / 001B264C /
 *   001A79F0 (lui/lw in flow, $gp in delay slots); sda scalars for the 0x13A0..0x13DC
 *   $gp block; D_L01_001B03D8 is a 16-byte sda table (D_L01_001B03E8 follows it), which
 *   needs -G16.
 * - func_00355828, func_00337A60 and func_00355780 return values: v0 stays taken after
 *   the calls, so the constants stored after them are built in v1, as retail.
 * - One local per case and per loop; the mode-7 clamp as an if; qzero_nc for the
 *   pv+0xA0 clear (cse forgets its 0.0f there, so the later <= 0 test builds its own).
 * - Every local is initialised where it is declared and call results are named
 *   locals. The dead initialisers are deleted by flow but counted by gcse: 1,173
 *   insns give a 587-bucket expression table and retail's spill-slot order for the PRE
 *   addresses &v30/&v40/&v50/&v80/pv+0xDE (bucket of (plus (reg 1) N) is
 *   (14030 + N) % buckets). 1,172-1,175 insns all match.
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
extern void func_0030F920(u8 *, s32, s32);
extern void func_00310138(u8 *, s32, s32, s32);
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
extern void swamp_monster_spawn_splash(u8 *, s32, s32, s32);
extern void swamp_monster_release_attack_slot(u8 *);
extern void swamp_monster_arm_init(u8 *);
extern void swamp_monster_release_arm_timers(u8 *);
extern void UpdateOozlaLinkedGroupDamage(u8 *);
extern void swamp_monster_test_attack_segment_hits_hero(u8 *, void *, void *, u8, void *);

/* Updates the swamp monster arm. It reaches for the hero, swings and sparks on a hit, then goes back to rest. */
void swamp_monster_arm_update(u8 *moby)
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
    u8 *e1 = 0;
    u8 *e2 = 0;
    u8 *e9 = 0;
    u8 *tgt5 = 0;
    u8 *tgt7 = 0;
    u8 *tbl7a = 0;
    u8 *tbl7b = 0;
    u8 *pos5 = 0;
    u8 *pos6 = 0;
    u8 *pos7 = 0;
    u8 *particle = 0;
    s32 flag = 0;
    s32 i1 = 0;
    s32 i2 = 0;
    s32 j = 0;
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    f32 anim_frame = 0.0f;
    f32 f5 = 0.0f;
    f32 f6a = 0.0f;
    f32 f6 = 0.0f;
    f32 f7 = 0.0f;
    f32 dir5a = 0.0f;
    f32 dir5b = 0.0f;
    f32 dir6a = 0.0f;
    f32 dir6b = 0.0f;
    u8 *e0 = 0;
    u8 *e3 = 0;
    u8 *hero_target = 0;
    u8 *hero_target6 = 0;
    s32 level = 0;
    f32 rnd = 0.0f;
    f32 ra = 0.0f;
    f32 rb = 0.0f;
    f32 rc = 0.0f;
    s32 mode6 = 0;
    s32 hit7 = 0;
    s32 busy1 = 0;
    s32 busy2 = 0;
    s32 busy3 = 0;
    f32 scale3 = 0.0f;
    f32 yaw5a = 0.0f;
    f32 yaw5b = 0.0f;
    f32 yaw6a = 0.0f;
    f32 yaw6b = 0.0f;
    f32 spinx = 0.0f;
    f32 spiny = 0.0f;
    f32 rise = 0.0f;
    f32 scale6 = 0.0f;
    f32 scale7 = 0.0f;
    s32 busy8 = 0;

    vars = *(u8 **)(moby + 0x68);
    UpdateOozlaLinkedGroupDamage(moby);
    switch (moby[0x95]) {
    case 0:
        if (g_oozla_intro_stage < 2)
            return;
        swamp_monster_arm_init(moby);
        break;
    case 1:
        e1 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
        if (*(s32 *)(vars + 0xC8) != 0)
            func_00307390(moby, 7, e1 + 0x10);
        else
            func_00307390(moby, 8, e1 + 0x10);
        qcopy(e1 + 0xF0, moby + 0xF0);
        switch (moby[0x20]) {
        case 0:
            flag = 0;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE0);
            if (*(s32 *)(vars + 0x74) == 1) {
                if (*(s32 *)(vars + 0x7C) == 1)
                    flag = 1;
            }
            if (*(s32 *)(vars + 0xC0) > 0)
                flag = 1;
            e0 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (func_00312B68(e0, 0x10001, 0) != 0)
                flag = 1;
            if (flag) {
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                *(s32 *)(vars + 0xBC) = 0;
                func_00310418(moby, 1, -1);
            }
            break;
        case 1:
            if (*(s32 *)(vars + 0xBC) != 0)
                break;
            e2 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            if (*(s32 *)(vars + 0xC8) != 0) {
                if (moby[0x43] != 10)
                    func_00310138(moby, 10, 0, 7);
                func_00310138(e2, 8, 0, 7);
            } else {
                if (moby[0x43] != 6)
                    func_00310138(moby, 6, 0, 7);
            }
            func_00355828(0, 0, e2, 0xB1A);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 2, 1);
            break;
        case 2:
            busy1 = func_003104E8(4);
            if (busy1 == 0)
                swamp_monster_spawn_splash(moby, 3, 10, 1);
            if (!(moby[0x60] & 2))
                break;
            e3 = g_moby_l01_table + (*(s32 *)(vars + 0xB4) << 8);
            e3[0x95] = 1;
            if (*(s32 *)(vars + 0xEC) == -1)
                goto done;
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            *(s32 *)(vars + 0xBC) = 0x28;
            if (moby[0x43] != 0)
                func_00310138(moby, 0, 0, 1);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
            func_00310418(moby, 0, 4);
            break;
        }
        break;
    case 2:
        busy2 = func_003104E8(5);
        if (busy2 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if ((moby[0x42] == 6 || moby[0x42] == 10) && (moby[0x60] & 2)) {
            if (*(f32 *)(vars + 0xD4) > 0.0f)
                *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
            if (moby[0x43] != 0)
                func_00310138(moby, 0, 0, 0);
            *(f32 *)(moby + 0x48) = 0.0f;
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 4);
        }
        break;
    case 3:
        busy3 = func_003104E8(5);
        if (busy3 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 0xF0;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale3 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale3;
            *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xEC);
            func_00310418(moby, 0, 5);
        }
        break;
    case 4:
        *(s32 *)(vars + 0xF0) = *(s32 *)(vars + 0xE8);
        if (*(s32 *)(vars + 0x74) == 1 && *(s32 *)(vars + 0x7C) == 1) {
            if (*(s32 *)(vars + 0xBC) == 0)
                *(s32 *)(vars + 0xBC) = 0x78;
            if (*(s32 *)(vars + 0xBC) == 1) {
                if (*(f32 *)(vars + 0xD4) > 0.0f)
                    *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0xD4);
                *(f32 *)(moby + 0x48) = 1.0f;
                if (moby[0x43] != 0)
                    func_00310138(moby, 0, 0, func_00310528(10, 15));
                func_00310418(moby, 0, 3);
            }
        }
        break;
    case 5:
        if (*(s32 *)(vars + 0x74) == 1) {
            func_00337A60(vars + 0x90, vars + 0x60, g_path_l01_table[*(s32 *)(vars + 0xB8)] + 0x10, *(s32 *)g_path_l01_table[*(s32 *)(vars + 0xB8)]);
            *(s32 *)(vars + 0xC0) = 0xF0;
            tgt5 = vars + 0x90;
        } else {
            qcopy(vars + 0x90, vars + 0x80);
            tgt5 = vars + 0x90;
        }
        hero_target = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
        if (*(u8 **)(vars + 0x70) == hero_target) {
            func_002E34E0(vec_a, &((Hero *)g_hero_state)->b[0x110], g_swamp_arm_hero_offset_scale);
            func_002E3470(vec_a, vec_a, *(u8 **)(vars + 0x70) + 0x10);
        } else {
            qcopy(vec_a, *(u8 **)(vars + 0x70) + 0x10);
        }
        pos5 = moby + 0x10;
        func_002E34A0(vec_b, tgt5, pos5);
        func_002E34E0(vec_b, vec_b, 0.05f);
        func_002E37D0(vec_b, vec_b, 0.050000004f);
        vec_b[2] = 0.0f;
        func_002E3470(pos5, pos5, vec_b);
        dir5a = 0.09599312f;
        if (vars[0xDD] != 0)
            dir5a = -0.09599312f;
        yaw5a = func_002E4460(*(f32 *)(moby + 0xF8), dir5a);
        *(f32 *)(moby + 0xF8) = yaw5a;
        f5 = func_002E3B10(vec_a[0] - *(f32 *)(moby + 0x10), vec_a[1] - *(f32 *)(moby + 0x14));
        func_00310D28(moby, vars + 0xCC, f5, 0.002327106f, 0.1f, 0.13962637f);
        if (moby[0x60] & 2)
            *(f32 *)(moby + 0x48) = func_00310580(0.8f, 1.2f);
        if (g_hero_l01_control_mode != 2 && ((Hero *)g_hero_state)->i[0x2294 / 4] != 0x6F && *(s32 *)(vars + 0xC4) == 0 &&
            (moby[0x21] == 0xFF || **(s32 **)(vars + 0xD8) <= 0) && func_002E3650(pos5, vars + 0x60) < 35.0f &&
            (f5 = func_002E3B10(vec_a[0] - *(f32 *)(moby + 0x10), vec_a[1] - *(f32 *)(moby + 0x14)),
             func_002E4548(*(f32 *)(moby + 0xF8), f5) < 0.034906588f)) {
            vars[0xDC] = 1;
            if (moby[0x21] != 0xFF)
                **(s32 **)(vars + 0xD8) += 1;
            if (moby[0x43] != 2)
                func_00310138(moby, 2, 0, func_00310528(7, 12));
            func_00310418(moby, 0, 6);
            vars[0xDE] = 0;
        } else if (*(s32 *)(vars + 0xC0) == 0) {
            if (moby[0x43] != 6)
                func_00310138(moby, 6, 0, 0x14);
            *(u16 *)(moby + 0x34) &= 0xEFFF;
            func_00310418(moby, 0, 2);
        }
        dir5b = 0.09599312f;
        if (vars[0xDD] != 0)
            dir5b = -0.09599312f;
        yaw5b = func_002E44A8(*(f32 *)(moby + 0xF8), dir5b);
        *(f32 *)(moby + 0xF8) = yaw5b;
        break;
    case 6:
        pos6 = moby + 0x10;
        anim_frame = func_00306448(moby);
        func_002E34A0(vec_a, vars + 0x90, pos6);
        func_002E34E0(vec_a, vec_a, 0.05f);
        func_002E37D0(vec_a, vec_a, 0.050000004f);
        vec_a[2] = 0.0f;
        func_002E3470(pos6, pos6, vec_a);
        if (anim_frame > 46.0f && anim_frame < 56.0f) {
            for (i1 = 1; i1 < 8; i1++) {
                func_00307390(moby, i1, vec_b);
                func_00307390(moby, i1 + 1, vec_d);
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
        if (anim_frame >= 56.0f && vars[0xDE] == 0) {
            func_00355780(2, 0, moby);
            vars[0xDE] = 1;
        }
        level = func_002D9308(moby[0xB0]);
        g_swamp_arm_anim_frame_limit = g_swamp_arm_frame_limit_table[level - 1];
        if (anim_frame < (f32)g_swamp_arm_anim_frame_limit &&
            (anim_frame < 20.0f || (((Hero *)g_hero_state)->i[0x340 / 4] != 0 && ((Hero *)g_hero_state)->h[0x34E / 2] == 0 &&
                           ((Hero *)g_hero_state)->i[0x229C / 4] != 4))) {
            dir6a = 0.09599312f;
            if (vars[0xDD] != 0)
                dir6a = -0.09599312f;
            yaw6a = func_002E4460(*(f32 *)(moby + 0xF8), dir6a);
            *(f32 *)(moby + 0xF8) = yaw6a;
            hero_target6 = ((Hero *)g_hero_state)->ptr[0x2290 / 4];
            if (*(u8 **)(vars + 0x70) == hero_target6) {
                func_002E34E0(vec_b, &((Hero *)g_hero_state)->b[0x110], 55.0f - anim_frame);
                func_002E3470(vec_b, vec_b, *(u8 **)(vars + 0x70) + 0x10);
            } else {
                qcopy(vec_b, *(u8 **)(vars + 0x70) + 0x10);
            }
            f6a = func_002E3B10(vec_b[0] - *(f32 *)(moby + 0x10), vec_b[1] - *(f32 *)(moby + 0x14));
            func_00310D28(moby, vars + 0xCC, f6a, 0.002327106f, 0.1f, 0.13962637f);
            dir6b = 0.09599312f;
            if (vars[0xDD] != 0)
                dir6b = -0.09599312f;
            yaw6b = func_002E44A8(*(f32 *)(moby + 0xF8), dir6b);
            *(f32 *)(moby + 0xF8) = yaw6b;
        }
        if (anim_frame > 55.0f && anim_frame < 58.0f) {
            if (anim_frame <= 56.0f) {
                g_drive_settings.f160 = 0.2f;
                g_drive_settings.i168 = 0x14;
                g_drive_settings.i16C = 0;
            }
            f6 = *(f32 *)(moby + 0x18);
            for (i2 = 1; i2 < 8; i2++) {
                func_00307390(moby, i2, vec_b);
                f6 = func_00311A00(vec_b, 2, 0.5f);
                mode6 = func_002D77E8();
                if (mode6 != 3)
                    break;
            }
            vec_b[2] = f6;
            func_00307390(moby, 8, vec_c);
            vec_c[2] = f6;
            func_002E34A0(vec_c, vec_c, vec_b);
            qzero(vec_h);
            vec_h[3] = g_swamp_arm_vec_h_w;
            for (j = 0; j < g_swamp_arm_particle_count; j++) {
                rnd = func_00310580(0.0f, 1.0f);
                func_002E34E0(vec_d, vec_c, rnd);
                func_00316348(vec_d, 0.1f);
                func_002E3470(vec_d, vec_d, vec_b);
                spinx = func_00310580(-(g_swamp_arm_spin_x_speed * 0.016666668f), g_swamp_arm_spin_x_speed * 0.016666668f);
                func_002E3738(vec_f, moby + 0xD0, spinx);
                spiny = func_00310580(-(g_swamp_arm_spin_y_speed * 0.016666668f), g_swamp_arm_spin_y_speed * 0.016666668f);
                func_002E3738(vec_g, moby + 0xC0, spiny);
                func_002E3470(vec_e, vec_f, vec_g);
                rise = func_00310580(0.0f, g_swamp_arm_rise_speed * 0.016666668f);
                vec_e[2] = rise;
                vec_e[3] = g_swamp_arm_vec_e_w;
                ra = func_00310580(g_swamp_arm_random_min_a, g_swamp_arm_random_max_a);
                a = func_002E45B8(ra);
                rb = func_00310580(g_swamp_arm_random_min_b, g_swamp_arm_random_max_b);
                b = func_002E45B8(rb);
                rc = func_00310580(g_swamp_arm_random_min_c, g_swamp_arm_random_max_c);
                c = func_002E45B8(rc);
                particle = func_00327360(vec_d, vec_e, vec_h, g_swamp_arm_particle_type_a, g_swamp_arm_particle_type_b, a, b, c, -1);
                if (particle != 0 && (func_001163B0() & 1))
                    particle[3] = 0x48;
            }
        }
        if (moby[0x60] & 2) {
            swamp_monster_release_attack_slot(moby);
            *(s32 *)(vars + 0xC4) = 0xB4;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale6 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale6;
            func_00310418(moby, 0, 5);
        }
        break;
    case 7:
        moby[0xA8] = 0xFF;
        pos7 = moby + 0x10;
        func_002E3470(vec_a, pos7, vars + 0xA0);
        tbl7a = g_path_l01_table[*(s32 *)(vars + 0xB8)];
        hit7 = func_00311B48(vec_a, tbl7a + 0x10, *(s32 *)tbl7a);
        if (hit7 != 0) {
            qcopy(pos7, vec_a);
        } else {
            tbl7b = g_path_l01_table[*(s32 *)(vars + 0xB8)];
            func_00337A60(pos7, vec_a, tbl7b + 0x10, *(s32 *)tbl7b);
            func_002E34A0(vec_b, vars + 0x80, pos7);
            func_002E3738(vec_b, vec_b, 0.033333335f);
            func_002E3470(pos7, pos7, vec_b);
        }
        f7 = func_002E35A0((vars + 0xA0)) - 0.0030555557f;
        if (f7 < 0.0f) {
            f7 = 0.0f;
        }
        func_002E3738((vars + 0xA0), (vars + 0xA0), f7);
        if (!(moby[0x60] & 2))
            break;
        qzero_nc((vars + 0xA0));
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            if (moby[0x42] == 3) {
                if (moby[0x43] != 4)
                    func_00310138(moby, 4, 0, 10);
            } else {
                func_00310418(moby, 0, 9);
            }
        } else {
            *(u16 *)(moby + 0x34) |= 0x1000;
            *(s32 *)(vars + 0xC0) = 0xF0;
            *(s32 *)(vars + 0xC4) = 0;
            if (moby[0x43] != 1)
                func_00310138(moby, 1, 0, func_00310528(10, 15));
            scale7 = func_00310580(0.8f, 1.2f);
            *(f32 *)(moby + 0x48) = scale7;
            func_00310418(moby, 0, 5);
        }
        break;
    case 8:
        busy8 = func_003104E8(4);
        if (busy8 == 0)
            swamp_monster_spawn_splash(moby, 3, 10, 1);
        if (!(moby[0x60] & 2))
            break;
    case 9:
        func_0030F920(moby, 0x200, 3);
        if (*(s32 *)(vars + 0xE4) != -1 && !(g_moby_group_flags[moby[0xB0] + (g_current_map_index << 4)] & 0x80)) {
            func_00307E70(moby[0xB0]);
            e9 = g_swamp_patrol_positions + (*(s32 *)(vars + 0xE4) << 7);
            func_0034ECD0(e9 + 0x30, e9 + 0x70);
        }
    done:
        func_00306250(moby);
        return;
    }
    swamp_monster_release_arm_timers(moby);
}
