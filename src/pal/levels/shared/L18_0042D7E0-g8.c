#include "common.h"
extern u8 *g_moby_l18_table MACRO_ADDR;
extern int ref_L18_00428AE8_00 __attribute__((sda));
typedef union { u8 b[0x100]; s16 h[0x80]; int i[0x40]; float f[0x40]; } Obj;
extern int g_enemy_timer_reset_value __attribute__((sda));
extern int g_receiver_wander_timer __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void add_vectors(void *, void *, void *);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern void enemy_update_wander_heading_pal(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern int ref_L18_00428AE8_01(void *, int);
extern int moby_set_anim(void *, int, int);
extern int moby_toggle_anim_helper(void *);
extern void moby_start_or_forward_anim_pal(void *, int, int, float);
extern void moby_set_state(void *, int, int);
extern int enemy_try_notice_player_pal(void *);
extern int func_001163B0(void);
extern void SetDeathBits_pal(void *, int, int);
/* func_PAL_L18_0042D7E0, the PAL copy of func_L18_00428AE8: the same C, with both reloads of the timer
   scaled to 50 Hz. */
/* Moves the receiver bot toward its target or wanders: turns, steps, switches between idle and shooting states, and updates its linked object (PAL: 50 Hz timers). */
void receiver_bot_move_toward_target_pal(u8 *moby) {
    float dir[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    float saved_turn_limit, saved_speed_scale;
    int link_index = *(int *)(vars + 0x3B4);
    if (link_index != -1) {
        u8 *link_moby = (u8 *)((link_index << 8) + ref_L18_00428AE8_00);
        if (((Obj *)link_moby)->h[0xAA/2] == 0x114D && ((Obj *)link_moby)->b[0x20] != 0xFE && ((Obj *)link_moby)->b[0x20] != 0xFD)
            ((Obj *)link_moby)->i[0x98/4] = 0;
    }
    if (moby[0x95] == 13) {
        vec_scale_to_length(dir, g_moby_l18_table + (*(int *)(vars+0x3B4)<<8) + 0xC0, 5.0f);
        add_vectors(point, dir, g_moby_l18_table + (*(int *)(vars+0x3B4)<<8) + 0x10);
        dir[2] = *(float *)(moby+0x18);
        *(float *)(vars+0x128) *= 10.0f;
        *(float *)(vars+0x120) *= 10.0f;
        saved_turn_limit = *(float *)(vars+0x110);
        saved_speed_scale = *(float *)(vars+0x10C);
        *(float *)(vars+0x110) = 3.1415927f;
        *(float *)(vars+0x10C) = 0.5f;
        moby_l01_turn_toward_target_pal(moby,dir);
        *(float *)(vars+0x128) *= 0.1f;
        *(float *)(vars+0x120) *= 0.1f;
        *(float *)(vars+0x110) = saved_turn_limit;
        *(float *)(vars+0x10C) = saved_speed_scale;
        goto restore;
    } else {
        if (*(int *)(vars+0x38C) != -1) {
            if (ref_L18_00428AE8_01(moby, *(int *)(vars+0x38C))) {
                switch (moby[0x95]) {
                case 5:
                    if (vars[0x399] & 2) vars[0x399] = 0;
                    moby_set_anim(moby, *(int *)(vars+0x374), -1);
                    *(u16 *)(vars+0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
                    moby_start_or_forward_anim_pal(moby,2,0,10.0f);
                    moby_set_state(moby,4,6);
                    break;
                case 6:
                    if (moby_toggle_anim_helper(moby)) {
                        *(u16 *)(vars+0x392) = (g_enemy_timer_reset_value * 5 + 2) / 6;
                        moby_start_or_forward_anim_pal(moby,2,0,10.0f);
                        moby_set_state(moby,4,6);
                    }
                    if (*(s16 *)(moby+0xAA) != 0xEC0 /* moby class 3776 */) enemy_try_notice_player_pal(moby);
                    break;
                case 2:
                    moby_toggle_anim_helper(moby);
                    if (moby[0x60] & 2) {
                        moby_start_or_forward_anim_pal(moby,func_001163B0() & 1,0,10.0f);
                        moby_set_state(moby,2,-1);
                    }
                    break;
                }
            }
                if (*(s16 *)(moby+0xAA) == 0xEC0 /* moby class 3776 */ && (unsigned)(moby[0x95]-5) < 2) {
                    if (vec_distance_xy(moby+0x10, *(u8 **)(vars+0x230)+0x10) < *(float *)(vars+0x3A0)) {
                        *(int *)(vars+0x38C) = -1;
                        moby_set_state(moby,4,6);
                    }
                }
                goto restore;

        } else if (moby[0x95] == 6) {
            if (moby[0x20] == moby[0x95]) moby_l01_turn_toward_target_pal(moby,vars+0x220);
            else {
                moby_turn_toward_target_and_step_pal(moby,vars+0x220,0.0f);
                enemy_try_notice_player_pal(moby);
            }
        } else {
wander:
            enemy_update_wander_heading_pal(moby,vars+0x1F0,vars+0x100);
            if (*(s16 *)(vars+0x392) == 0) {
                *(u16 *)(vars+0x392) = (g_receiver_wander_timer * 5 + 2) / 6;
                moby_start_or_forward_anim_pal(moby,func_001163B0() & 1,0,10.0f);
                moby_set_state(moby,2,-1);
            }
        }
        if (*(float *)(moby+0x18) < *(float *)(vars+0x90)) {
            SetDeathBits_pal(moby,0,3);
            moby_set_state(moby,12,10);
        }
restore:
        { int link_index2 = *(int *)(vars+0x3B4);
        if (link_index2 != -1) {
            u8 *link_moby = (u8 *)((link_index2 << 8) + ref_L18_00428AE8_00);
            if (((Obj *)link_moby)->h[0xAA/2] == 0x114D && ((Obj *)link_moby)->b[0x20] != 0xFE && ((Obj *)link_moby)->b[0x20] != 0xFD)
                ((Obj *)link_moby)->i[0x98/4] = *(int *)(((Obj *)link_moby)->i[0x24/4]+0x10);
        } }
    }
}
