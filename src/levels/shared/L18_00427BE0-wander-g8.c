#include "common.h"
extern u8 *g_moby_l18_table MACRO_ADDR;
extern int ref_L18_00428AE8_00 __attribute__((sda));
typedef union { u8 b[0x100]; s16 h[0x80]; int i[0x40]; float f[0x40]; } Obj;
extern u16 D_L18_001B1240 __attribute__((sda));
extern u16 D_L18_001B1264 __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void add_vectors(void *, void *, void *);
extern void moby_l01_turn_toward_target(void *, void *);
extern void moby_turn_toward_target_and_step(void *, void *, float);
extern void enemy_update_wander_heading(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern int ref_L18_00428AE8_01(void *, int);
extern int moby_set_anim(void *, int, int);
extern int moby_toggle_anim_helper(void *);
extern void moby_start_or_forward_anim(void *, int, int, float);
extern void moby_set_state(void *, int, int);
extern void enemy_try_notice_player(void *);
extern int func_001163B0(void);
extern void SetDeathBits(void *, int, int);
/* Moves the enemy each frame: it heads for its target or wanders when it has none, and drops into its fall state if it sinks too low. It also holds a linked helper object still while it does this. */
void receiver_bot_move_toward_target(u8 *moby) {
    float scaledVec[4] __attribute__((aligned(16)));
    float aimVec[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    float savedLimit, savedRate;
    int helperIndex = *(int *)(vars + 0x3B4);
    if (helperIndex != -1) {
        u8 *helper = (u8 *)((helperIndex << 8) + ref_L18_00428AE8_00);
        if (((Obj *)helper)->h[0xAA/2] == 0x114D /* moby class 4429 */ && ((Obj *)helper)->b[0x20] != 0xFE && ((Obj *)helper)->b[0x20] != 0xFD)
            ((Obj *)helper)->i[0x98/4] = 0;
    }
    if (moby[0x95] == 13) {
        vec_scale_to_length(scaledVec, g_moby_l18_table + (*(int *)(vars+0x3B4)<<8) + 0xC0, 5.0f);
        add_vectors(aimVec, scaledVec, g_moby_l18_table + (*(int *)(vars+0x3B4)<<8) + 0x10);
        scaledVec[2] = *(float *)(moby+0x18);
        *(float *)(vars+0x128) *= 10.0f;
        *(float *)(vars+0x120) *= 10.0f;
        savedLimit = *(float *)(vars+0x110);
        savedRate = *(float *)(vars+0x10C);
        *(float *)(vars+0x110) = 3.1415927f;
        *(float *)(vars+0x10C) = 0.5f;
        moby_l01_turn_toward_target(moby,scaledVec);
        *(float *)(vars+0x128) *= 0.1f;
        *(float *)(vars+0x120) *= 0.1f;
        *(float *)(vars+0x110) = savedLimit;
        *(float *)(vars+0x10C) = savedRate;
        goto restore;
    } else {
        if (*(int *)(vars+0x38C) != -1) {
            if (ref_L18_00428AE8_01(moby, *(int *)(vars+0x38C))) {
                switch (moby[0x95]) {
                case 5:
                    if (vars[0x399] & 2) vars[0x399] = 0;
                    moby_set_anim(moby, *(int *)(vars+0x374), -1);
                    *(u16 *)(vars+0x392) = D_L18_001B1240;
                    moby_start_or_forward_anim(moby,2,0,10.0f);
                    moby_set_state(moby,4,6);
                    break;
                case 6:
                    if (moby_toggle_anim_helper(moby)) {
                        *(u16 *)(vars+0x392) = D_L18_001B1240;
                        moby_start_or_forward_anim(moby,2,0,10.0f);
                        moby_set_state(moby,4,6);
                    }
                    if (*(s16 *)(moby+0xAA) != 0xEC0 /* moby class 3776 */) enemy_try_notice_player(moby);
                    break;
                case 2:
                    moby_toggle_anim_helper(moby);
                    if (moby[0x60] & 2) {
                        moby_start_or_forward_anim(moby,func_001163B0() & 1,0,10.0f);
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
            if (moby[0x20] == moby[0x95]) moby_l01_turn_toward_target(moby,vars+0x220);
            else {
                moby_turn_toward_target_and_step(moby,vars+0x220,0.0f);
                enemy_try_notice_player(moby);
            }
        } else {
wander:
            enemy_update_wander_heading(moby,vars+0x1F0,vars+0x100);
            if (*(s16 *)(vars+0x392) == 0) {
                *(u16 *)(vars+0x392) = D_L18_001B1264;
                moby_start_or_forward_anim(moby,func_001163B0() & 1,0,10.0f);
                moby_set_state(moby,2,-1);
            }
        }
        if (*(float *)(moby+0x18) < *(float *)(vars+0x90)) {
            SetDeathBits(moby,0,3);
            moby_set_state(moby,12,10);
        }
restore:
        { int helperIndex2 = *(int *)(vars+0x3B4);
        if (helperIndex2 != -1) {
            u8 *helper = (u8 *)((helperIndex2 << 8) + ref_L18_00428AE8_00);
            if (((Obj *)helper)->h[0xAA/2] == 0x114D /* moby class 4429 */ && ((Obj *)helper)->b[0x20] != 0xFE && ((Obj *)helper)->b[0x20] != 0xFD)
                ((Obj *)helper)->i[0x98/4] = *(int *)(((Obj *)helper)->i[0x24/4]+0x10);
        } }
    }
}
