#include "common.h"
extern float g_shooter_attack_distance __attribute__((sda));
extern int g_enemy_timer_reset_value __attribute__((sda)), g_shooter_cooldown_reset __attribute__((sda));
extern int g_shooter_cooldown __attribute__((sda));
extern u8 g_shooter_burst_count __attribute__((sda));
extern int g_shooter_burst_delay_min __attribute__((sda)), g_shooter_burst_delay_max __attribute__((sda));
extern u32 g_pad_pressed_flags[];
extern char g_str_debug_stub[];
extern float vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern int moby_step_at_own_position_factor_pal(void *, float);
extern int moby_step_at_own_position_pal(void *);
extern int enemy_aim_at_target(void *);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int FastDecTimer(short *), vec_fast_helper_a(u8 *);
extern void SetDeathBits_pal(void *, int, int), moby_set_state(void *, int, int);
extern void moby_start_or_forward_anim_pal(void *, int, int, float), moby_rebuild_scale_matrix_pal(void *);
extern u8 *shooter_fire_shot_pal(void *, int);
extern int math_random_int_range(int, int), func_001163B0(void);
extern void STUB_printf(const char *, ...);

/* The two member stores of the reload: as members they do not conflict with the fixed scalar D_L18_001B1268,
   so its load is free to move ahead of the first store, as in retail. */
typedef struct { u8 pad[0x392]; u16 cooldown; short phase; short delay; } Timers;

/* func_PAL_L18_0042D3B8, the PAL copy of func_L18_00428738: the same C, with its timers scaled to 50 Hz and
   the burst's phase counted in fifths instead of sixths. */
/* Advance the shared enemy's ranged attack and its two muzzle timers. */
int shooter_update_ranged_attack_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    int changed = 0;
    switch (*(short *)(moby + 0xAA)) {
    case 0xEC0: /* moby class 3776 */
        if (moby[0xBC] != 1) {
            if (vec_distance_xy(moby + 0x10, vars + 0x220) < g_shooter_attack_distance)
                moby_step_at_own_position_pal(moby);
            else moby_l01_turn_toward_target_pal(moby, vars + 0x220);
        } else {
            if (g_pad_pressed_flags[1] & 0x80) *(u16 *)(vars + 0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
            FastDecTimer((short *)(vars + 0x392));
        }
        if (*(float *)(moby + 0x18) < *(float *)(vars + 0x90)) {
            SetDeathBits_pal(moby, 0, 3);
            changed = 1;
            moby_set_state(moby, 12, -1);
        }
        enemy_aim_at_target(moby);
        if (*(short *)(vars + 0x392) == 0) {
            if (moby[0xBC] != 1) {
                moby_rebuild_scale_matrix_pal(moby);
                changed = 1;
                *(u16 *)(vars + 0x396) = (g_shooter_cooldown_reset * 5 + 2) / 6;
                moby_start_or_forward_anim_pal(moby, 2, 0, 10.0f);
                moby_set_state(moby, 4, 6);
            } else changed = 1;
        }
        break;
    case 0xED4: /* moby class 3796 */
    case MOBY_CLASS_RECEIVER_BOT:
        if (moby[0xBC] != 1) {
            u8 *target = *(u8 **)(vars + 0x230);
            moby_step_at_own_position_factor_pal(moby, mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(target + 0x14) - *(float *)(moby + 0x14)));
        }
        switch (moby[0x42]) {
        case 10:
            if (moby[0x60] & 2) {
                moby_start_or_forward_anim_pal(moby, 11, 0, 10.0f);
                *(float *)(moby + 0x48) = 3.0f;
                {
                    u8 bursts = g_shooter_burst_count;
                    *(short *)(vars + 0x394) = 0;
                    vars[0x39D] = bursts;
                }
            }
            break;
        case 11:
            if (*(short *)(moby + 0xAA) == MOBY_CLASS_RECEIVER_BOT) {
                if (*(short *)(vars + 0x394) % 5 == 0) {
                    shooter_fire_shot_pal(moby, 0);
                    vec_fast_helper_a(vars + 0x39D);
                }
                if ((*(short *)(vars + 0x394) + 2) % 5 == 0) shooter_fire_shot_pal(moby, 1);
            } else if (*(short *)(moby + 0xAA) == 0xED4 /* moby class 3796 */ && *(short *)(vars + 0x394) % 5 != 0) {
                shooter_fire_shot_pal(moby, 0);
                vec_fast_helper_a(vars + 0x39D);
            }
            {
                int controlled = moby[0xBC];
                if (controlled == 1) {
                    changed = (g_pad_pressed_flags[0] & 0x80) ? changed : controlled;
                } else if (vars[0x39D] == 0) moby_start_or_forward_anim_pal(moby, 12, 0, 10.0f);
            }
            break;
        case 12:
            if (moby[0x60] & 2) {
                changed = 1;
                ((Timers *)vars)->delay = (math_random_int_range(g_shooter_burst_delay_min, g_shooter_burst_delay_max) * 5 + 2) / 6;
                ((Timers *)vars)->cooldown = (g_shooter_cooldown * 5 + 2) / 6;
                moby_start_or_forward_anim_pal(moby, (func_001163B0() & 1) | 4, 0, 10.0f);
                moby_set_state(moby, 2, 6);
            }
            break;
        }
        break;
    default:
        STUB_printf(g_str_debug_stub);
        break;
    }
    return changed;
}
