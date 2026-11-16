#include "common.h"

/* func_PAL_L12_0041A100, the PAL copy of func_L12_00415128: the same C, with its eleven
   timers and thresholds scaled to 50 Hz (f300 < 5 becomes < 4), the sweep step at 6/5 and
   D_L12_001B1828 read as a word. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct GuardVars GuardVars;

typedef struct {
    char pad00[0x10];
    s32 f10;                /* 0x10 */
} GuardClass;

typedef struct GuardMoby {
    char pad00[0x10];
    f32 x;                  /* 0x10 */
    f32 y;                  /* 0x14 */
    f32 z;                  /* 0x18 */
    f32 w;                  /* 0x1C */
    u8 state;               /* 0x20 */
    char pad21[0x24 - 0x21];
    GuardClass *f24;        /* 0x24 */
    char pad28[0x30 - 0x28];
    u8 f30;                 /* 0x30 */
    u8 f31;                 /* 0x31 */
    char pad32[0x34 - 0x32];
    u16 f34;                /* 0x34 */
    char pad36[0x42 - 0x36];
    u8 f42;                 /* 0x42 */
    u8 f43;                 /* 0x43 */
    char pad44[0x60 - 0x44];
    u8 f60;                 /* 0x60 */
    char pad61[0x68 - 0x61];
    GuardVars *vars;        /* 0x68 */
    char pad6C[0x95 - 0x6C];
    u8 f95;                 /* 0x95 */
    u16 f96;                /* 0x96 */
    s32 f98;                /* 0x98 */
    char pad9C[0xAA - 0x9C];
    s16 fAA;                /* 0xAA */
    char padAC[0xB2 - 0xAC];
    s16 fB2;                /* 0xB2 */
    char padB4[0xF8 - 0xB4];
    f32 fF8;                /* 0xF8 */
} GuardMoby;

struct GuardVars {
    char pad000[0x20];
    f32 f20;                /* 0x020 */
    char pad024[0x2E - 0x24];
    u8 f2E;                 /* 0x02E */
    char pad02F[0x138 - 0x2F];
    s32 f138;               /* 0x138 */
    char pad13C[0x1F0 - 0x13C];
    f32 f1F0;               /* 0x1F0 */
    f32 f1F4;               /* 0x1F4 */
    char pad1F8[0x200 - 0x1F8];
    GuardMoby *f200;        /* 0x200 */
    s32 f204;               /* 0x204 */
    char pad208[0x2B0 - 0x208];
    s32 f2B0;               /* 0x2B0 */
    char pad2B4[0x2B8 - 0x2B4];
    s32 f2B8;               /* 0x2B8 */
    s32 f2BC;               /* 0x2BC */
    s32 f2C0;               /* 0x2C0 */
    char pad2C4[0x2CC - 0x2C4];
    s32 f2CC;               /* 0x2CC */
    char pad2D0[0x2D4 - 0x2D0];
    s32 f2D4;               /* 0x2D4 */
    s32 f2D8;               /* 0x2D8 */
    s32 f2DC;               /* 0x2DC */
    s16 f2E0;               /* 0x2E0 */
    char pad2E2[0x2E4 - 0x2E2];
    u16 f2E4;               /* 0x2E4 */
    s16 f2E6;               /* 0x2E6 */
    s16 f2E8;               /* 0x2E8 */
    char pad2EA[0x2EC - 0x2EA];
    f32 f2EC;               /* 0x2EC */
    GuardMoby *f2F0[2];     /* 0x2F0 */
    GuardMoby *f2F8;        /* 0x2F8 */
    char pad2FC[0x300 - 0x2FC];
    s16 f300;               /* 0x300 */
    u8 f302;                /* 0x302 */
    u8 f303;                /* 0x303 */
    s32 *f304;              /* 0x304 */
    char pad308[0x30C - 0x308];
    u8 f30C;                /* 0x30C */
    u8 f30D;                /* 0x30D */
    u8 f30E;                /* 0x30E */
    u8 f30F;                /* 0x30F */
    char pad310[0x314 - 0x310];
    s32 f314;               /* 0x314 */
    char pad318[0x31C - 0x318];
    s8 f31C;                /* 0x31C */
    u8 f31D;                /* 0x31D */
    u8 f31E;                /* 0x31E */
    u8 f31F;                /* 0x31F */
    char pad320[0x4A0 - 0x320];
    GuardMoby *f4A0;        /* 0x4A0 */
};

/* The level's guard zone: its mode, its kind and the two heights it splits at. */
typedef struct {
    s32 mode;               /* 0x00 */
    char pad04[0xC - 0x4];
    s32 kind;               /* 0x0C */
    char pad10[0x28 - 0x10];
    f32 low;                /* 0x28 */
    char pad2C[0x38 - 0x2C];
    f32 high;               /* 0x38 */
} GuardZone;

extern GuardZone g_guard_zone;
extern s32 g_hero_l12_control_mode __attribute__((sda));
extern s32 g_guard_low_timer_threshold __attribute__((sda));
extern f32 g_guard_near_distance __attribute__((sda));
extern f32 g_guard_close_distance __attribute__((sda));
extern s32 g_guard_random_attack_chance __attribute__((sda));
extern s32 g_guard_attack_timer_threshold __attribute__((sda));
extern s32 g_guard_alert_timer_threshold __attribute__((sda));
extern s32 g_guard_attack_sequence_value __attribute__((sda));
extern s32 g_guard_wait_min __attribute__((sda));
extern s32 g_guard_wait_max __attribute__((sda));
extern s32 g_guard_cooldown_min __attribute__((sda));
extern s32 g_guard_cooldown_max __attribute__((sda));
extern s32 g_frame_l12_counter MACRO_ADDR;
extern s32 g_guard_color_red MACRO_ADDR;
extern s32 g_guard_color_green MACRO_ADDR;
extern s32 g_guard_color_blue MACRO_ADDR;
extern char *g_path_zone_table[];
extern char g_hero_position[];
extern char g_str_guard_debug_a[];
extern char g_str_guard_alarm_debug[];
extern char g_str_guard_debug_b[];

extern void STUB_printf(const char *, ...);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern float vec_distance_xy(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(int);
extern void set_moby_color(void *, int, int, int);
extern void get_moby_color(void *, s32 *, s32 *, s32 *);
extern void SetDeathBits(void *, int, int);
extern int math_random_int_below(int);
extern float math_wrap_angle_to_pi(float);
extern void SpawnExplosionEffects(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern s32 moby_dispatch_action_by_kind(void *, void *);
extern s32 part_spawn_damage_debris(void *, void *, void *);
extern int flag_set_second_pending(void *);
extern int coll_point_inside_region(void *, int);
extern int moby_step_at_own_position_factor(void *, float);
extern int func_001163B0(void);
extern s32 FastDecTimer(s16 *);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern void shared_counter_release(void *);
extern void shared_counter_acquire(void *);
extern void moby_destroy_linked(void *);
extern int enemy_walk_to_next_path_point(void *, int);
extern s32 enemy_select_path(void *, int, int);
extern void guard_clear_hit_value(void *);
extern void guard_restore_hit_value(void *);
extern void guard_switch_animation(void *, int, int, int);
extern void path_hand_state_to_nearest(void *);
extern void slot_timers_update(void *);
extern void guard_handle_hit_handover(void *);
extern void guard_aim_partner_hands(void *);
extern void guard_reattach_helpers(void *);
extern int guard_is_line_of_sight_blocked(void *, int, int, int);
extern void guard_aim_hand_helper_at_target(void *);
extern void guard_update_attack_sequence(void *);

/* The guard's per-frame driver: the zone gate, the alarm and release of its
   two bound helpers, then the behaviour switch and the animation switch on its state
   (PAL: 50 Hz timings). */
void todano_guard_update_pal(GuardMoby *moby)
{
    GuardVars *vars;
    GuardMoby *list[3];
    s32 sx, sy, sz;
    s32 helper_count;
    s8 alarm;

    if (g_guard_zone.kind != 0) {
        f32 z = moby->z;
        if (z < g_guard_zone.low && g_guard_zone.mode == 1)
            return;
        if (g_guard_zone.low < z && g_guard_zone.mode == 0)
            return;
        if (g_guard_zone.kind == 2) {
            if (g_guard_zone.high < z && g_guard_zone.mode == 1)
                return;
            if (z < g_guard_zone.high && g_guard_zone.mode == 2)
                return;
        }
    }

    vars = moby->vars;
    if (vars->f2E == 2) {
        path_hand_state_to_nearest(moby);
        part_spawn_damage_debris(moby, (char *)vars + 0x290, (char *)vars + 0x20);
        shared_counter_release(moby);
        moby_destroy_linked(moby);
        SpawnExplosionEffects(moby, (char *)vars + 0xD0, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        moby_mark_spawned(moby);
        return;
    }
    if (g_hero_l12_control_mode == 2)
        return;

    if (vars->f31E != 0 && moby->f30 == 0xFF)
        moby->f30 = vars->f31E;

    if (vars->f314 != -1 && moby->f95 == 0) {
        if (coll_point_inside_region(g_hero_position, vars->f314) == 0) {
            if (vars->f31D == 0)
                vars->f31C = -1;
            else
                vars->f31C = 0;
        } else if (vars->f31C == 0) {
            vars->f31C = 1;
        }
    }

    if (vars->f302 & 1) {
        vars->f31C = -1;
        vars->f31F = 1;
    } else if (vars->f31D != 0) {
        if (vars->f31F == 1) {
            vars->f31F = 0;
            moby->f96 = 0;
            return;
        }
        if (moby->f96 < g_guard_low_timer_threshold) {
            moby->f96 = moby->f96 + 1;
            return;
        }
        vars->f31C = 1;
        guard_handle_hit_handover(moby);
        *(TI128 *)&moby->x = *(TI128 *)(g_path_zone_table[vars->f2C0] + 0x10);
        helper_count = 0;
        if (vars->f2F8 != 0) {
            list[0] = vars->f2F8;
            helper_count = 1;
        }
        if (vars->f2F0[0] != 0)
            list[helper_count++] = vars->f2F0[0];
        if (vars->f2F0[1] != 0)
            list[helper_count++] = vars->f2F0[1];
        moby_fuse_linked_objects(moby, &moby->x, (char *)moby + 0xF0, list, helper_count);
    }

    if (vars->f4A0 != 0) {
        if (vars->f4A0->state == 0xFE)
            goto release;
        if (vars->f4A0->state == 0xFD) {
        release:
            get_moby_color(moby, &sx, &sy, &sz);
        if (sx != g_guard_color_red || sy != g_guard_color_green || sz != g_guard_color_blue)
            STUB_printf(g_str_guard_debug_a);
        set_moby_color(moby, g_guard_color_red, g_guard_color_green, g_guard_color_blue);
        vars->f4A0 = 0;
        }
    }

    alarm = vars->f31C;
    if (alarm < 0) {
        if (vars->f31D == 0) {
            GuardMoby *head;
            int i;

            moby->f98 = 0;
            moby->f31 = 0;
            moby->f34 = moby->f34 | 1;
            head = vars->f2F8;
            if (head != 0 && head->fAA == 0x114B /* moby class 4427 */ && head->state != 0xFE && head->state != 0xFD) {
                head->f34 = head->f34 | 1;
                vars->f2F8->f31 = 0;
                vars->f2F8->f98 = 0;
            }
            for (i = 0; i < 2; i++) {
                GuardMoby *helper = vars->f2F0[i];
                if (helper != 0 && helper->fAA == 0xD66 /* moby class 3430 */ && helper->state != 0xFE && helper->state != 0xFD) {
                    helper->f34 = helper->f34 | 1;
                    vars->f2F0[i]->f31 = 0;
                }
            }
        }
        vars->f31C = 0;
        vars->f31D = 1;
        return;
    }
    if (alarm > 0) {
        if (vars->f31D != 0) {
            GuardMoby *head;
            int i;

            STUB_printf(g_str_guard_alarm_debug, g_frame_l12_counter, moby->fB2, alarm);
            moby->f31 = 1;
            moby->f34 = moby->f34 & 0xFFFE;
            moby->f98 = moby->f24->f10;
            set_moby_color(moby, g_guard_color_red, g_guard_color_green, g_guard_color_blue);
            head = vars->f2F8;
            if (head != 0 && head->fAA == 0x114B /* moby class 4427 */ && head->state != 0xFE && head->state != 0xFD) {
                head->f34 = head->f34 & 0xFFFE;
                vars->f2F8->f31 = 1;
                vars->f2F8->f98 = vars->f2F8->f24->f10;
            }
            for (i = 0; i < 2; i++) {
                GuardMoby *helper = vars->f2F0[i];
                if (helper != 0 && helper->fAA == 0xD66 /* moby class 3430 */ && helper->state != 0xFE && helper->state != 0xFD) {
                    helper->f34 = helper->f34 & 0xFFFE;
                    vars->f2F0[i]->f31 = 1;
                }
            }
            vars->f31D = 0;
        }
    } else if (vars->f31D != 0) {
        vars->f31C = 0;
        return;
    }
    vars->f31C = 0;

    guard_clear_hit_value(moby);
    moby->f31 = 1;
    moby->f34 = moby->f34 & 0xFFFE;
    guard_handle_hit_handover(moby);

    switch (moby->f95) {
    case 0:
        STUB_printf(g_str_guard_debug_b, moby->fB2, moby->fAA);
        break;
    case 1:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            vars->f2D8 = vars->f2D4;
            if (!(vars->f302 & 1)) {
                vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
                moby_set_state(moby, moby->state, 2);
            } else {
                guard_switch_animation(moby, 0xC, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 8, 5);
            }
        }
        break;
    case 2:
        if (flag_set_second_pending(moby) != 0 && vars->f300 < 4 && !(vars->f302 & 2))
            vars->f300 = ((s32)math_random_int_range(0, 0x78) * 5 + 2) / 6;
        if (FastDecTimer(&vars->f300) != 0) {
            vars->f2D8 = vars->f2D4;
            if (vars->f2B0 != -1) {
                enemy_select_path(moby, vars->f2B0, -1);
                moby_set_state(moby, 2, 3);
            } else {
                enemy_select_path(moby, vars->f2B8, -1);
                guard_switch_animation(moby, 2, 0, 0xA);
                moby_set_state(moby, 4, 3);
            }
            if (vars->f302 & 2)
                enemy_select_path(moby, vars->f2C0, -1);
        }
        /* fall through */
    case 3:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1)
            vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
        break;
    case 4:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            enemy_select_path(moby, vars->f2B8, -1);
            vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
            guard_switch_animation(moby, 2, 0, 0xA);
            moby_set_state(moby, 4, 3);
        }
        break;
    case 5:
        vars->f2EC = mat_fast_helper_a(vars->f200->x - moby->x, vars->f200->y - moby->y);
        if (vars->f302 & 2) {
            int side = func_001163B0() & 1;
            guard_switch_animation(moby, side, 0, math_random_int_range(0xA, 0x14));
            shared_counter_release(moby);
            vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
            vars->f300 = 1;
            moby_set_state(moby, moby->state, 2);
        }
        if (vars->f204 != 1 && vars->f2E0 == 0) {
            int side;
            shared_counter_release(moby);
            side = func_001163B0() & 1;
            guard_switch_animation(moby, side, 0, math_random_int_range(0xA, 0x14));
            moby_set_state(moby, 5, 6);
        }
        break;
    case 6:
        vars->f2EC = moby->fF8;
        if (vars->f204 == 1 || vars->f2E0 != 0) {
            shared_counter_release(moby);
            vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
            guard_switch_animation(moby, 3, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 5, 5);
        } else if (vars->f2E8 == 0) {
            int side;
            shared_counter_release(moby);
            enemy_select_path(moby, vars->f2B8, 0);
            side = func_001163B0() & 1;
            guard_switch_animation(moby, side, 0, math_random_int_range(0xA, 0x14));
            moby_set_state(moby, 4, 4);
        }
        break;
    case 7:
        vars->f2EC = mat_fast_helper_a(vars->f200->x - moby->x, vars->f200->y - moby->y);
        break;
    case 8:
        vars->f2EC = FastAddRotations(vars->f2EC,
            (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_frame_l12_counter) * 0.02f)) + 2.0f) * 0.027925273f);
        break;
    case 9: {
        s32 hit;

        vars->f2EC = moby->fF8;
        hit = moby_dispatch_action_by_kind(moby, (char *)vars + 0x50);
        if (vars->f20 <= 0.0f && (moby->f42 == 0xF || moby->f43 == 0xF))
            moby_set_state(moby, 0xF, -1);
        if (hit & 1) {
            if (vars->f20 > 0.0f)
                path_hand_state_to_nearest(moby);
            shared_counter_release(moby);
            moby_set_state(moby, 0xF, -1);
        } else if (hit & 2) {
            shared_counter_release(moby);
            vars->f2E0 = ((s32)math_random_int_range(g_guard_cooldown_min, g_guard_cooldown_max) * 5 + 2) / 6;
            if (moby->f42 == 0xF || moby->f43 == 0xF) {
                enemy_select_path(moby, vars->f2B0, -1);
                moby_set_state(moby, 3, 3);
                guard_switch_animation(moby, 0xE, 0, math_random_int_range(7, 0xC));
            } else {
                guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
                if (vars->f30F != 0)
                    moby_set_state(moby, 0xD, 8);
                else
                    moby_set_state(moby, 6, 5);
            }
        }
        break;
    }
    }

    switch (moby->state) {
    case 0:
        break;
    case 1:
        if (moby->f60 & 2)
            guard_switch_animation(moby, 0xE, 0, math_random_int_range(7, 0xC));
        break;
    case 2:
        if (moby->f60 & 2) {
            guard_switch_animation(moby, 0xE, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 3, -1);
        }
        break;
    case 4:
        if (moby->f60 & 2) {
            guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 6, -1);
        }
        break;
    case 5:
        if (moby->f60 & 2) {
            if (moby->f95 == 5) {
                guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 6, -1);
            } else {
                guard_switch_animation(moby, 0xC, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 6, -1);
            }
        }
        break;
    case 3:
        if (moby->f60 & 2)
            guard_switch_animation(moby, 0xE, 0, math_random_int_range(7, 0xC));
        if (enemy_walk_to_next_path_point(moby, vars->f2DC) != 0) {
            vars->f138 = vars->f138 & ~4;
            enemy_select_path(moby, vars->f2BC, -1);
            guard_switch_animation(moby, 0x10, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 7, 5);
        }
        break;
    case 6:
        guard_update_attack_sequence(moby);
        break;
    case 7:
        if (moby->f60 & 2) {
            if (vars->f30E != 0) {
                guard_switch_animation(moby, 4, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 4, 5);
            } else {
                guard_switch_animation(moby, 0xC, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 8, 5);
            }
        }
        break;
    case 8: {
        f32 yaw = mat_fast_helper_a(vars->f1F0 - moby->x, vars->f1F4 - moby->y);

        moby_step_at_own_position_factor(moby, yaw);
        if (FastDiffRots(yaw, moby->fF8) < 0.17453295f) {
            guard_switch_animation(moby, 5, 0, math_random_int_range(7, 0xC));
            vars->f30C = 0;
            vars->f30D = 0;
            moby_set_state(moby, 9, -1);
        }
        break;
    }
    case 9: {
        f32 distance;
        s32 near, close, ahead, picked, tried;

        near = 1;
        distance = vec_distance_xy(&moby->x, &vars->f200->x);
        if (!(distance <= g_guard_close_distance))
            near = 0;
        close = 1;
        ahead = *vars->f304 < vars->f2CC;
        if (!(distance < g_guard_near_distance))
            close = 0;
        if (vars->f303 == 0) {
            picked = 0;
            tried = 0;
            if (close == 0 && near != 0 && ahead != 0 && math_random_int_below(g_guard_random_attack_chance - 1) == 0
                && vars->f2E6 == 0) {
                tried = 1;
                picked = guard_is_line_of_sight_blocked(moby, 0, vars->f30C != 0, 0);
            }
            if (vars->f30C != 0 && picked != 0 && close == 0) {
                guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 6, -1);
            } else if (close != 0 || picked != 0) {
                if (guard_is_line_of_sight_blocked(moby, 0, (u8)(s8)vars->f30C != 0, 1) != 0)
                    vars->f30D = 1;
                shared_counter_acquire(moby);
                guard_switch_animation(moby, 8, 0, 7);
                moby_set_state(moby, 0xA, -1);
            } else if (moby->f60 & 2) {
                guard_switch_animation(moby, 6, 0, math_random_int_range(7, 0xC));
            }
            if (tried != 0 && picked == 0)
                vars->f30C = ~vars->f30C;
        } else {
            if (moby->f60 & 2)
                guard_switch_animation(moby, 6, 0, math_random_int_range(7, 0xC));
            if (close != 0 || (vars->f2E6 == 0 && near != 0 && ahead != 0)) {
                guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
                moby_set_state(moby, 6, -1);
            }
        }
        break;
    }
    case 10:
        if (moby->f60 & 2) {
            if (vars->f30D != 0)
                guard_switch_animation(moby, 0xA, 0, 1);
            else
                guard_switch_animation(moby, 0x13, 0, 1);
            vars->f2E4 = ((s32)g_guard_attack_sequence_value * 5 + 2) / 6;
            moby_set_state(moby, 0xB, -1);
        }
        break;
    case 11:
        if (moby->f96 > ((s32)g_guard_alert_timer_threshold * 5 + 2) / 6)
            guard_aim_hand_helper_at_target(moby);
        if ((moby->f96 > ((s32)g_guard_attack_timer_threshold * 5 + 2) / 6 && g_guard_near_distance < vec_distance_xy(&moby->x, &vars->f200->x))
            || vars->f2F8 == 0) {
            vars->f2E6 = ((s32)math_random_int_range(g_guard_wait_min, g_guard_wait_max) * 5 + 2) / 6;
            shared_counter_release(moby);
            guard_switch_animation(moby, 0xC, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 8, 5);
        }
        break;
    case 12:
        if (moby->f60 & 2) {
            guard_switch_animation(moby, 0xB, 0, math_random_int_range(7, 0xC));
            moby_set_state(moby, 6, 5);
        }
        break;
    case 13:
        if (moby->f60 & 2) {
            int anim = (func_001163B0() & 1) ? 0xA : 0x13;
            guard_switch_animation(moby, anim, 0, math_random_int_range(0x19, 0x2D));
        }
        if (moby->f42 == 0xA || moby->f42 == 0x13)
            guard_aim_hand_helper_at_target(moby);
        break;
    case 14:
        shared_counter_release(moby);
        break;
    case 15:
        vars->f20 = 0.0f;
        part_spawn_damage_debris(moby, (char *)vars + 0x290, (char *)vars + 0x20);
        shared_counter_release(moby);
        moby_destroy_linked(moby);
        SetDeathBits(moby, 0, 3);
        SpawnExplosionEffects(moby, (char *)vars + 0xD0, 0, 0.0f, 0.0f, 4, 0, 0,
                      2.0f, 1.0f, 9.0f, 1.0f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        moby_mark_spawned(moby);
        return;
    }
    guard_aim_partner_hands(moby);
    guard_reattach_helpers(moby);
    slot_timers_update(moby);
    guard_restore_hit_value(moby);
}
