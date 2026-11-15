#include "names.h"
/* func_US2_L20_00441AD8, the USA v2.00 copy of func_L20_00440598: the same C, where the two text ids
   0x325E and 0x3210 become 0x30F4 and 0x30A6, and state 5's spawn is guarded by a test of the saved
   object pointer against the word after D_L20_001B2F9C (the object table's base). */
#include "common.h"
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern f32 FastDiffRots(f32, f32);
extern void menu_set_size_limits(int, int);
extern void settings_store_four(int, int, int, int);
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);
extern int GetLocalizedString(int);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(char *);
extern void func_US2_002A7AA8(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float coll_probe_ground_height_below(void *, int, float);
extern int coll_sweep_from_object(void *, void *, s32, s32, s32, s32, f32, f32, f32);
extern float ApproachValue(float *, float, float);
extern void StepAngleTowardTarget(float *, int, f32, f32);
extern void vec_add_random_offset(float *, float);
extern int IsPointInCuboid(void *, int);
extern s32 func_US2_002AF9C8(u8 *, f32);
extern int flag_set_first_pending(u8 *);
extern int request_begin_slot(int, int, int, int, int);
extern void part_spawn_growing_puff(char *, char *, int, int, int, float);
extern void level_capture_checkpoint_state(void *, void *);
extern void snd_stop_voice(s32);
extern int PlayMobySound(int, int, char *);
extern void hero_record_play_counters(void);
extern void gfx_add_draw_callback_third(void *, void *);
extern void level_clear_first_table_entry(void);
extern int moby_start_effect_from_entry(void *, float);
extern void cutscene_start_scene(void);
extern void trooper_destroy_parts(char *arg0);
extern void electric_orb_set_position_mode(char *arg0, char *arg1, int arg2);
extern void moby_set_motion_limits(char *arg0);
extern void yeedil_boss_start_jump(char *actor);
extern void moby_set_motion_limits_range(char *arg0, float f);
extern void moby_chase_target_update(char *arg0, char *arg1, float f);
extern void enemy_choose_next_state(char *arg0);
extern void moby_run_type_update(char *arg0);
extern int enemy_is_valid_target(char *arg0, char *arg1);
extern char * yeedil_boss_spawn_lobbed_object(char *arg0, int arg1, char *arg2);
extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);
extern void yeedil_boss_launch_damage_shot(char *arg0);
extern void enemy_compute_aim_turn_angle(char *arg0, float *arg1);
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; } Hero;
extern u8 g_hero_state[];

extern void yeedil_boss_init_damage(char *);
extern int yeedil_boss_update_grab(char *);
extern int UpdateBouncingMoby(char *);
extern void yeedil_boss_spawn_minion_at_point(char *);
extern void yeedil_boss_choose_attack(char *);
extern void yeedil_boss_frame_upkeep(char *);
extern void yeedil_boss_compute_side_step(char *, char *);
extern u8 *group_activate_member_along_aim(char *);
extern char *enemy_fire_projectile_along_aim(char *);
extern char *yeedil_boss_fire_lobbed_projectile(char *);
extern int yeedil_boss_launch_group_shot(char *);
extern void yeedil_boss_explode_death(char *);
extern int group_count_active_members(int);
extern char *electric_orb_spawn(char *, char *);
extern char *yeedil_enemy_spawn_shot(char *, char *, int, float, int, int);
extern void gfx_start_screen_effect(void);
extern s32 D_L20_001A8F00[] __attribute__((sda));
/* The same word, read through $gp in some places and absolutely in others. */
extern s32 D_L20_001A8F00_gp SDATA(D_L20_001A8F00);
extern s32 D_L20_001A8F08 __attribute__((sda));
extern f32 D_L20_001B2030 __attribute__((sda));
extern f32 D_L20_001B2038 __attribute__((sda));
extern f32 D_L20_001B2040[] SDATA(D_L20_001B2040);
extern f32 D_L20_001B2054 __attribute__((sda));
extern f32 D_L20_001B2060[] SDATA(D_L20_001B2060);
extern s32 D_L20_001B2070 __attribute__((sda));
extern s32 D_L20_001B2074 __attribute__((sda));
extern f32 D_L20_001B209C __attribute__((sda));
extern f32 D_L20_001B20A0 __attribute__((sda));
extern f32 D_L20_001B20B0[] SDATA(D_L20_001B20B0);
extern s32 D_L20_001B20C4 __attribute__((sda));
extern s32 D_L20_001B20C8 __attribute__((sda));
extern f32 D_L20_001B2100[] SDATA(D_L20_001B2100);
extern u8 g_sound_state[];
extern s32 D_L20_001B29C0[] MACRO_ADDR;
extern s32 D_L20_001B29E0[] MACRO_ADDR;
extern s32 D_L20_001B2AC8[] __attribute__((sda));
extern s32 D_L20_001B2AD4[] MACRO_ADDR;
extern f32 D_L20_001B2BE8[] MACRO_ADDR;
extern char *D_L20_001B2FA0 __attribute__((sda));
extern char * D_L20_001B2FA8[] __attribute__((sda));
extern char * D_L20_001B308C[] __attribute__((sda));
typedef union { u8 b[0x200]; s32 i[0x80]; f32 f[0x80]; } Blk200;
extern u8 D_L20_001B9E80[];
extern s16 D_L20_001C0184[];
extern u8 D_L20_001C01C0[];
extern s32 D_L20_001CA540[];
extern s32 D_L20_0021FC18[];
extern s8 D_L20_001A8F20[] __attribute__((sda));
/* Lane 3 of the D_L20_001B2100 vector, read absolutely. */
extern f32 D_L20_001B210C[] MACRO_ADDR;
extern char * g_hero_moby[];
extern s32 D_0018C0B4[];
#define AT(T, p, o) (*(T *)((char *)(p) + (o)))

void func_US2_L20_00441AD8(char *self) {
    float sp[16] __attribute__((aligned(16)));
    char *st;
    int ctr = D_L20_001CA540[0];
    int v1, v2, v3, v5, v6;
    int fl;
    char *s0_1, *s0_2, *s0_3, *s0_4, *s0_5, *s0_6, *s0_7, *tb_1, *tb_2, *tb_3;

    if (ctr == 2) {
        st = AT(char *, self, 0x68);
        yeedil_boss_init_damage(self);
        if (AT(u8, self, 0x95) == 6) {
            if (AT(u8, self, 0x20) == 0x18 || AT(u8, self, 0x20) == 0x19) {
                if (IsPointInCuboid(g_hero_state + 0x80, AT(s32, st, 0x230)) != 0) {
                    qcopy(sp, D_L20_001B2100);
                    qzero_nc(&sp[4]);
                    sp[6] = D_L20_001B210C[0];
                    level_capture_checkpoint_state(sp, &sp[4]);
                    D_L20_001B20A0 = D_L20_001B20A0 + 1.0f;
                    moby_set_state(self, 1, 0);
                    fl = D_L20_001A8F00[0];
                } else {
                    fl = D_L20_001A8F00_gp;
                }
                /* ctr is 2 here; retail compares against its saved copy. */
                if (fl == ctr) {
                    AT(s32, self, 0x98) = 0;
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
                } else {
                    AT(u16, self, 0x34) = (AT(u16, self, 0x34) & 0xFFBE) | 0x1000;
                    AT(s32, self, 0x98) = AT(s32, AT(char *, self, 0x24), 0x10);
                }
            }
            if (D_L20_001CA540[0] == 2) {
                D_L20_001B2BE8[0] = AT(f32, self, 0x18) - 2.0f;
            }
        }
        switch (AT(u8, self, 0x20)) {
        case 1:
            if (flag_set_first_pending(self) != 0 && AT(u8, self, 0x43) != 0x13) {
                anim_start_blended(self, 0x13, 0, 0x14);
            }
            s0_1 = g_hero_moby[0];
            moby_start_effect_from_entry(self, mat_fast_helper_a(AT(f32, s0_1, 0x10) - AT(f32, self, 0x10), AT(f32, s0_1, 0x14) - AT(f32, self, 0x14)));
            if (AT(u8, self, 0x60) & 2) {
                enemy_choose_next_state(self);
            }
            break;
        case 2:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 6) {
                    anim_start_blended(self, 6, 0, 0x14);
                }
                moby_set_motion_limits(self);
                AT(s32, self, 0x9C) = 1;
            }
            tb_1 = (char *)g_sound_state + AT(s32, st, 0x1854) * 0x70;
            if (AT(s32, tb_1, 0x88) != (s32)self || AT(u8, tb_1, 0x74) == 0) {
                AT(s32, st, 0x1854) = PlayMobySound(1, 4, self);
            }
            if (AT(char *, st, 0x1850) != 0) {
                matrix_mul_vec3(sp, D_L20_001B20B0, self + 0xC0);
                FastVecAdd(sp, sp, self + 0x10);
                electric_orb_set_position_mode(AT(char *, st, 0x1850), (char *)sp, 1);
            }
            if (yeedil_boss_update_grab(self) != 0) {
                moby_set_state(self, 3, -1);
                v1 = AT(s32, st, 0x1854);
                if (v1 != -1 && (tb_2 = (char *)g_sound_state + v1 * 0x70, AT(s32, tb_2, 0x88) == (s32)self)) {
                    if (AT(u8, tb_2, 0x74) != 0) {
                        snd_stop_voice(v1);
                    }
                }
                AT(s32, st, 0x1854) = -1;
            }
            break;
        case 3:
            if (flag_set_first_pending(self) != 0) {
                yeedil_boss_start_jump(self);
                if (AT(u8, self, 0x43) != 6) {
                    anim_start_blended(self, 6, 0, 0x14);
                }
                AT(s32, self, 0x9C) = 1;
                if (AT(char *, st, 0x1850) == 0) {
                    if (AT(s32, st, 0x17F8) != 0) {
                        AT(char *, st, 0x1850) = electric_orb_spawn(self, self + 0x10);
                    }
                }
            }
            if (AT(char *, st, 0x1850) != 0) {
                matrix_mul_vec3(sp, D_L20_001B20B0, self + 0xC0);
                FastVecAdd(sp, sp, self + 0x10);
                electric_orb_set_position_mode(AT(char *, st, 0x1850), (char *)sp, 0);
            }
            StepAngleTowardTarget((float *)(st + 0x1804), 0, 0.0f, 0.10471977f);
            if (UpdateBouncingMoby(self) != 0) {
                if (D_0018C0B4[0] != 0x8C && (math_fast_float_d(st + 0x17F8) == 1 || D_L20_001B20C8 != 0)) {
                    if (AT(s32, st, 0x1810) > 0) {
                        AT(s32, st, 0x1810) = -1;
                        yeedil_boss_spawn_minion_at_point(self);
                    }
                    enemy_choose_next_state(self);
                    AT(s32, self, 0x9C) = 2;
                } else {
                    moby_set_state(self, 2, 1);
                }
            }
            break;
        case 4:
            if (flag_set_first_pending(self) != 0) {
                moby_set_motion_limits_range(self, D_L20_001B2038);
                if (AT(u8, self, 0x43) != 2) {
                    anim_start_blended(self, 2, 0, 0x14);
                }
            }
            { char *p = AT(char *, st, 0x17FC);
            moby_chase_target_update(self, p + 0x10, mat_fast_helper_a(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
            if (enemy_is_valid_target(self, AT(char *, st, 0x17FC)) == 0) {
                moby_set_state(self, 1, -1);
            } else {
                if (AT(f32, st, 0x11C) <= D_L20_001B2038 || AT(u16, self, 0x96) >= 0x12DU) {
                    moby_set_state(self, 5, -1);
                }
            }
            break;
        case 5:
            if (flag_set_first_pending(self) != 0 && AT(u8, self, 0x43) != 0xB) {
                anim_start_blended(self, 0xB, 0, 0xF);
            }
            if (moby_get_anim_value(self) < 31.0f) {
                { char *p = AT(char *, st, 0x17FC);
                moby_start_effect_from_entry(self, mat_fast_helper_a(AT(f32, p, 0x10) - AT(f32, self, 0x10), AT(f32, p, 0x14) - AT(f32, self, 0x14))); }
                if (enemy_is_valid_target(self, AT(char *, st, 0x17FC)) == 0) {
                    moby_set_state(self, 1, -1);
                }
            } else if (func_US2_002AF9C8((u8 *)self, 32.0f) != 0) {
                s0_2 = AT(char *, st, 0x17FC);
                if (s0_2 < D_L20_001B2FA0) {
                    FastVecScale(sp, D_L20_001B2040, D_L20_001B2030);
                    matrix_mul_vec3(sp, sp, self + 0xC0);
                    FastVecAdd(sp, sp, self + 0x10);
                    AT(char *, st, 0x17FC) = yeedil_boss_spawn_lobbed_object(s0_2, AT(s16, s0_2, 0xAA), (char *)sp);
                    AT(s32, st, 0x183C) = AT(s16, s0_2, 0xAA);
                    moby_run_type_update(s0_2);
                    AT(f32, self, 0x48) = D_L20_001B2054;
                }
            } else if (func_US2_002AF9C8((u8 *)self, 50.0f) != 0) {
                AT(f32, self, 0x48) = 1.0f;
            }
            if (moby_get_anim_value(self) >= 60.0f) {
                yeedil_boss_choose_attack(self);
                moby_set_state(self, 6, 3);
            }
            break;
        case 6:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    anim_start_blended(self, 2, 0, 0x14);
                }
                moby_set_motion_limits_range(self, AT(f32, st, 0x1838) * 0.5f);
            }
            s0_3 = (char *)(&((Hero *)g_hero_state)->b[0x80]);
            moby_chase_target_update(self, s0_3, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < AT(f32, st, 0x1838) && FastDiffRots(AT(f32, self, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                moby_set_state(self, AT(s32, st, 0x1834), -1);
            }
            break;
        case 7: {
            int n;
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    anim_start_blended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x180C) = 0;
            }
            moby_start_effect_from_entry(self, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14)));
            AT(s32, st, 0x1808) = D_L20_001B2AC8[0];
            matrix_mul_vec3(sp, D_L20_001B2060, self + 0xC0);
            FastVecAdd(sp, sp, self + 0x10);
            for (n = 1; n >= 0; n -= 1) {
                qcopy(&sp[4], sp);
                vec_add_random_offset(&sp[4], 1.5f);
                sp[2] -= 0.5f;
                part_spawn_growing_puff((char *)&sp[4], D_L20_001A8F20, 0x60309030, 0x107090, 0x2D, math_random_float_range(2.0f, 3.0f) * 210000.0f);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && math_fast_float_d(st + 0x180C) != 0) {
                AT(s32, st, 0x180C) = D_L20_001B2070;
                yeedil_boss_compute_shot_launch(self, (char *)&sp[4], (char *)&sp[8], &sp[12]);
                sp[6] += 1.5f;
                yeedil_enemy_spawn_shot(self, (char *)&sp[4], 0x78, (f32)AT(u8, st, 0x35), math_random_int_below(2), (int)(st + 0x1808));
            }
            if (D_L20_001B2074 < (s32)AT(u16, self, 0x96)) {
                moby_set_state(self, 1, -1);
            }
            break;
        }
        case 11:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    anim_start_blended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = math_random_int_range(0xA, 0xF);
            }
            enemy_compute_aim_turn_angle(self, (float *)(&((Hero *)g_hero_state)->b[0x80]));
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (AT(u16, self, 0x96) % 60U) == 0x1E) {
                yeedil_boss_launch_damage_shot(self);
                math_fast_float_d(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 10:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    anim_start_blended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = math_random_int_range(0x1E, 0x32);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                enemy_fire_projectile_along_aim(self);
                math_fast_float_d(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 8:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    anim_start_blended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = math_random_int_range(0xA, 0x14);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                yeedil_boss_fire_lobbed_projectile(self);
                math_fast_float_d(st + 0x1840);
            }
            if (AT(s32, st, 0x1840) == 0) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 9:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x11) {
                    anim_start_blended(self, 0x11, 0, 0x14);
                }
                AT(s32, st, 0x1840) = math_random_int_range(4, 5);
            }
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43) && (D_L20_001B2AC8[0] & 0x1F) == (((s32)self >> 8) & 0x1F)) {
                if (yeedil_boss_launch_group_shot(self) != 0) {
                    math_fast_float_d(st + 0x1840);
                } else {
                    AT(s32, st, 0x1840) = 0;
                }
            }
            if (AT(s32, st, 0x1840) == 0) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 12:
            if (flag_set_first_pending(self) != 0 && AT(u8, self, 0x43) != 0x11) {
                anim_start_blended(self, 0x11, 0, 0x14);
            }
            if ((D_L20_001B2AC8[0] & 7) == (((s32)self >> 8) & 7)) {
                if (D_L20_001B20C4 != 0) {
                    moby_set_state(self, 0xD, -1);
                } else if (group_activate_member_along_aim(self) == 0 || group_count_active_members(AT(s32, st, 0x21C)) >= 0x15) {
                    moby_set_state(self, 0xD, -1);
                }
            }
            break;
        case 13:
            v2 = flag_set_first_pending(self);
            s0_4 = st + 0x17D0;
            if (v2 != 0) {
                if (AT(u8, self, 0x43) != 2) {
                    anim_start_blended(self, 2, 0, 0x14);
                }
                yeedil_boss_compute_side_step(self, s0_4);
                moby_set_motion_limits_range(self, 1.0f);
            }
            moby_chase_target_update(self, s0_4, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) < 1.0f && FastDiffRots(AT(f32, self, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                moby_set_state(self, 0xE, -1);
            } else if (group_count_active_members(AT(s32, st, 0x21C)) < 3) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 14:
            if (flag_set_first_pending(self) != 0 && AT(u8, self, 0x43) != 1) {
                anim_start_blended(self, 1, 0, 0x14);
            }
            enemy_compute_aim_turn_angle(self, (float *)(&((Hero *)g_hero_state)->b[0x80]));
            if (vec_distance_xy(self + 0x10, g_hero_state + 0x80) < D_L20_001B209C) {
                moby_set_state(self, 0xD, -1);
            }
            if (group_count_active_members(AT(s32, st, 0x21C)) < 3) {
                moby_set_state(self, 1, -1);
            }
            break;
        case 15:
            if (flag_set_first_pending(self) != 0 && AT(u8, self, 0x43) != 0x15) {
                anim_start_blended(self, 0x15, 0, 0xA);
            }
            { float t = coll_probe_ground_height_below(self + 0x10, 0, 0.5f); ApproachValue((f32 *)(self + 0x18), t, 0.16666667f); }
            if (AT(u8, self, 0x60) & 2) {
                if (AT(u8, self, 0xBC) != 0) {
                    moby_set_state(self, 1, 0);
                } else {
                    moby_set_state(self, 0x10, -1);
                }
                AT(u8, self, 0xBC) = 0;
            }
            break;
        case 16: {
            f32 dist;
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 7) {
                    anim_start_blended(self, 7, 0, 0x14);
                }
                moby_set_motion_limits_range(self, 1.0f);
                AT(s32, st, 0x1830) = 0;
            }
            if (AT(u8, self, 0x60) & 2) {
                switch (AT(u8, self, 0x42)) {
                case 7:
                    if (AT(u8, self, 0x43) != 8) {
                        anim_start_blended(self, 8, 0, 1);
                    }
                    break;
                case 8:
                    if (AT(u8, self, 0x43) != 9) {
                        anim_start_blended(self, 9, 0, 1);
                    }
                    break;
                case 9:
                    AT(s32, st, 0x1830) = AT(s32, st, 0x1830) + 1;
                    break;
                }
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8C) {
                ((Hero *)g_hero_state)->h[0x1E0 / 2] = 0xF;
            }
            dist = moby_get_anim_value(self);
            if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                if ((AT(u8, self, 0x42) == 8 && dist < 9.0f) || (AT(u8, self, 0x42) == 9 && dist > 12.0f && dist < 30.0f)) {
                    s0_5 = (char *)(&((Hero *)g_hero_state)->b[0x80]);
                    moby_chase_target_update(self, s0_5, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14)));
                    if (AT(u8, self, 0x42) == AT(u8, self, 0x43)) {
                        if ((AT(u8, self, 0x42) == 8 && dist < 9.0f && dist > 7.0f) || (AT(u8, self, 0x43) == 9 && dist > 25.0f && dist < 30.0f)) {
                            qcopy(sp, self + 0x10);
                            sp[2] += 1.0f;
                            coll_sweep_from_object(self, sp, 0x10008, 0, 1, 0, 5.5f, (f32)AT(u8, st, 0x34), 2.0f);
                        }
                    }
                }
            }
            if (AT(u8, self, 0x42) == 8 && func_US2_002AF9C8((u8 *)self, 6.0f) != 0) {
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = 0.05f;
            }
            if (AT(u8, self, 0x42) == 9 && func_US2_002AF9C8((u8 *)self, 30.0f) != 0) {
                if (AT(s32, st, 0x1830) >= 2 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8C) {
                    yeedil_boss_explode_death(self);
                    moby_set_state(self, 3, -1);
                }
                ((Blk200 *)D_L20_001B9E80)->f[0x180 / 4] = (f32)(AT(s32, st, 0x1830) + 1) * 0.05f;
                ((Blk200 *)D_L20_001B9E80)->i[0x16C / 4] = 0;
                ((Blk200 *)D_L20_001B9E80)->i[0x188 / 4] = 0x2D;
            }
            break;
        }
        case 17:
            if (flag_set_first_pending(self) != 0) {
                if (AT(u8, self, 0x43) != 0x15) {
                    anim_start_blended(self, 0x15, 0, 0xA);
                }
                s0_6 = D_L20_001B2FA8[0];
                v3 = D_L20_001A8F00_gp;
                if (s0_6 != 0) {
                    /* Retail keeps these four in saved registers; with literals cc1 folds the two state
                       tests into one range check. */
                    int class_removed = 0xCBC, state_dead = 0xFE, state_dying = 0xFD;
                    int class_reset = 0xD0F;
                    int id;
                    do {
                        id = AT(s16, s0_6, 0xAA);
                        if (id == class_removed && s0_6 != 0) {
                            u8 k = AT(u8, s0_6, 0x20);
                            if (k != state_dead && k != state_dying) {
                                moby_mark_spawned(s0_6);
                            }
                            id = AT(s16, s0_6, 0xAA);
                        }
                        if (id == class_reset && s0_6 != 0) {
                            u8 k = AT(u8, s0_6, 0x20);
                            if (k != state_dead && k != state_dying && AT(u8, s0_6, 0x21) == AT(s32, st, 0x21C)) {
                                func_US2_002A7AA8(s0_6, 0, 3);
                                trooper_destroy_parts(s0_6);
                            }
                        }
                        s0_6 = AT(char *, s0_6, 0x28);
                    } while (s0_6 != 0);
                    v3 = D_L20_001A8F00[0];
                }
            } else {
                v3 = D_L20_001A8F00[0];
            }
            if (v3 == 2) {
                AT(s32, self, 0x98) = 0;
                AT(u16, self, 0x34) = (AT(u16, self, 0x34) | 0x41) & 0xEFFF;
            }
            if (AT(u8, self, 0x60) & 2) {
                AT(s32, self, 0x48) = 0;
            }
            break;
        case 18:
            if (flag_set_first_pending(self) != 0) {
                D_L20_001B29C0[0] = 0;
                request_begin_slot(9, 1, 0, 0, 0);
            }
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && req_push_queue(D_L20_001C01C0, 0x1E) != 0) {
                req_launch_queued(D_L20_001C01C0);
                moby_set_state(self, 0x13, -1);
            }
            break;
        case 19:
            if (D_L20_001A8F00[0] == 0) {
                if (D_L20_001A8F08 <= 0) {
                    D_L20_001B2AD4[0] = 1;
                    request_begin_slot(9, 1, 0, 0, 0);
                    moby_set_state(self, 0x14, -1);
                }
                if (D_L20_001A8F00[0] == 0) {
                    gfx_add_draw_callback_third(gfx_start_screen_effect, self);
                }
            }
            break;
        case 20:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0 && req_push_queue(D_L20_001C01C0, 0x1F) != 0) {
                req_launch_queued(D_L20_001C01C0);
                moby_set_state(self, 0x15, -1);
            }
            break;
        case 21:
            if (D_L20_001A8F00[0] == 0 && D_L20_001A8F08 <= 0) {
                int a, b;
                moby_set_state(self, 0x16, -1);
                a = GetLocalizedString(0x30F4);
                b = GetLocalizedString(0x30A6);
                settings_store_four(a, b, GetLocalizedString(0xA1F), 1);
                menu_set_size_limits(0x40, 0x20);
                request_begin_slot(4, 1, 9, 0, 0);
            }
            break;
        case 22:
            D_L20_001B29E0[0] = 0;
            if (D_L20_001C0184[0] == 1) {
                cutscene_start_scene();
                moby_set_state(self, 0x17, -1);
            } else {
                char *t;
                level_clear_first_table_entry();
                t = D_L20_001B308C[0] + (AT(s32, st, 0x248) << 7);
                level_capture_checkpoint_state(t + 0x30, t + 0x70);
                D_L20_0021FC18[0] = 0;
                hero_record_play_counters();
            }
            break;
        case 24:
            v5 = flag_set_first_pending(self);
            s0_7 = st + 0x17D0;
            if (v5 != 0) {
                f32 mag = math_random_float_range(5.0f, 15.0f);
                f32 ang = math_random_angle();
                char *target;
                f32 y;
                AT(f32, st, 0x17D0) = math_fast_sin_or_cos_a(ang) * mag;
                y = math_fast_sin_or_cos_b(ang) * mag;
                target = D_L20_001B308C[0] + (AT(s32, st, 0x230) << 7);
                AT(s32, st, 0x17D8) = 0;
                AT(f32, st, 0x17D4) = y;
                FastVecAdd(s0_7, s0_7, target + 0x30);
                if (AT(u8, self, 0x43) != 2) {
                    anim_start_blended(self, 2, 0, 0x14);
                }
                moby_set_motion_limits_range(self, 1.5f);
            }
            moby_chase_target_update(self, s0_7, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14)));
            if (AT(f32, st, 0x11C) <= 1.5f && FastDiffRots(AT(f32, self, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, self, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, self, 0x14))) < 0.087266475f) {
                moby_set_state(self, 0x19, -1);
            }
            break;
        case 25: {
            int anim;
            if (flag_set_first_pending(self) != 0) {
                anim = (math_random_int_below(3) != 0) ? 0x13 : 0x14;
                if (AT(u8, self, 0x43) != anim) {
                    anim_start_blended(self, anim, 0, 0x14);
                }
            }
            if (AT(u8, self, 0x60) & 2) {
                moby_set_state(self, 0x18, -1);
            }
            break;
        }
        }
        yeedil_boss_frame_upkeep(self);
        if (AT(u8, self, 0x20) != 2) {
            v6 = AT(s32, st, 0x1854);
            if (v6 != -1) {
                tb_3 = (char *)g_sound_state + v6 * 0x70;
                if (AT(s32, tb_3, 0x88) == (s32)self && AT(u8, tb_3, 0x74) != 0) {
                    snd_stop_voice(v6);
                }
            }
            AT(s32, st, 0x1854) = -1;
        }
    }
}
