/* func_PAL_L14_0042CCA4, the PAL copy of func_L14_004275E0: the same C, with the rates and speeds
 * rescaled for 50 Hz and the random timers written with the 5/6 scale. */
#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float g_guard_frame_scale __attribute__((sda));
extern float g_guard_alt_frame_scale __attribute__((sda));
/* A float pair (lower, upper), read through two address forms as in func_L12_00426C08. */
extern float g_guard_random_range[] __attribute__((sda));
extern float D_L14_001B18B8_gp[] SDATA(D_L14_001B18B8);
extern int g_frame_tick_counter[] __attribute__((sda));
extern char g_hero_state_block[], g_hero_position[];
extern int g_hero_moby[];
extern void guard_update_common_pal(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int math_random_int_below(int);
extern int FastDecTimer(void *);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void moby_l02_explode_and_remove_pal(void *);
extern float FastVecDot(void *,void *);
extern float fast_vec_dist(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern void path_clamp_move_to_area(void *,void *,void *,int,float);
extern int moby_run_entry_hook_by_mode_pal(void *,void *,int);
extern int moby_check_target_point_from_offset(void *,void *);
extern int moby_count_group_side_from_object(void *,int,int);
extern void turret_clamp_aim_yaw_pitch(void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int math_is_value_within_step_pal(void *,float);
extern int coll_test_hit_at_bone(void *,int,float,float,int,float,int,int,int);
extern int coll_sweep_from_object(void *,void *,float,float,int,float,int,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_falling_puff_pal(void *);
extern void moby_reset_turn_place_pal(void *);
extern void group_marker_update_pulse_pal(void *);

/* Guard enemy update (PAL: rates and timers rescaled for 50 Hz): runs the common guard logic, picks idle, wander, chase, aim, shoot and flee behaviours by state, and keeps the group marker pulsing. */
void guard_l14_update_pal(char *moby) {
    char *vars = *(char **)(moby+0x68);
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    guard_update_common_pal(moby);
    switch (B(moby,0x95)) {
    case 0:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby,0.0072000003f,0.080000006f,0.010053098f,0.5026549f);
            F(vars,0x1D0)=g_guard_alt_frame_scale*0.020000001f;
            F(vars,0x124)=0.0096f;
            F(vars,0x134)=0.5f;
            H(vars,0x33A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(vars,0x314)==1 && FastDecTimer(vars+0x33A)) {
            if (math_random_int_below(3)) moby_set_state(moby,9,2);
            else moby_set_state(moby,8,2);
        } else if (H(vars,0x316)) {
            if (math_random_int_below(2)) moby_set_state(moby,7,1);
            else moby_set_state(moby,6,1);
            H(vars,0x316)=0;
            if (H(vars,0x310)<250) H(vars,0x310)=((s32)(math_random_int_range(480,600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(vars,0x1D0)=g_guard_frame_scale*0.020000001f;
            F(vars,0x134)=0.05f;
        }
        if (H(vars,0x314)==1) moby_set_state(moby,9,2);
        else if (H(vars,0x310)==0) moby_set_state(moby,1,0);
        break;
    case 2:
        if (flag_set_second_pending(moby)) {
            moby_set_controller_speed_limits(moby,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(vars,0x1D0)=g_guard_frame_scale*0.020000001f;
            F(vars,0x124)=0.0096f;
            F(vars,0x134)=0.05f;
            H(vars,0x33A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(vars,0x314)!=1 && FastDecTimer(vars+0x33A)) {
            moby_set_state(moby,3,1);
            H(vars,0x310)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(moby,vars+0x50);
        if (flags&1) moby_l02_explode_and_remove_pal(moby);
        else if (flags&2) {
            if (H(vars,0x314)==1) moby_set_state(moby,9,2);
            else {
                moby_set_state(moby,3,1);
                H(vars,0x310)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
            }
        }
        break;
    }
    switch (B(moby,0x20)) {
    case 1:
        if (!B(moby,0x31)) break;
        if (flag_set_first_pending(moby)) {
            int choice=!math_random_int_below(4);
            if (B(moby,0x43)!=choice) anim_start_blended_pal(moby,choice,0,8);
            H(vars,0x312)=((s32)(math_random_int_range(60,120)) * 5 + 2) / 6;
        }
        if (B(moby,0x43)==1) {
            if (B(moby,0x60)&2) anim_start_blended_pal(moby,0,0,17);
        } else if (H(vars,0x312)==0) {
            if (!H(vars,0x338) || FastVecDot(vars+0x300,g_hero_state_block)>0.8f) moby_set_state(moby,2,-1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=6) anim_start_blended_pal(moby,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(vars,0x2F0)=math_fast_sin_or_cos_a(angle)*speed;
            F(vars,0x2F4)=math_fast_sin_or_cos_b(angle)*speed;
            W(vars,0x2F8)=0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
            if (W(vars,0x218)!=-1) {
                vec=*(Quad *)(vars+0x2E0);
                path_clamp_move_to_area(&vec,vars+0x2F0,vars+0x2F0,W(vars,0x218),1.5f);
            }
        }
        moby_run_entry_hook_by_mode_pal(moby,vars+0x2F0,0);
        if (U(moby,0x96)>25 && (F(vars,0x1CC)<=0.5f || U(moby,0x96)>150)) moby_set_state(moby,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=math_random_int_below(2)+4) anim_start_blended_pal(moby,math_random_int_below(2)+4,0,8);
        }
        if (fast_vec_dist(moby+0x10,g_hero_position)<D_L14_001B18B8_gp[0]) moby_set_state(moby,4,-1);
        else if (B(moby,0x60)&2) {
            switch (math_random_int_below(3)) {
            case 0:moby_set_state(moby,6,-1);break;
            case 1:moby_set_state(moby,7,-1);break;
            case 2:moby_set_state(moby,5,-1);break;
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=math_random_int_below(2)+2) anim_start_blended_pal(moby,math_random_int_below(2)+2,0,8);
        }
        moby_check_target_point_from_offset(moby,vars+0x1F0);
        if (B(moby,0x60)&2) moby_set_state(moby,3,-1);
        break;
    case 7:
        if (flag_set_first_pending(moby) && B(moby,0x43)!=12) anim_start_blended_pal(moby,12,0,8);
        moby_check_target_point_from_offset(moby,vars+0x1F0);
        if (B(moby,0x60)&2) moby_set_state(moby,3,-1);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=6) anim_start_blended_pal(moby,6,0,8);
            F(vars,0x334)=math_random_float_range(D_L14_001B18B8_gp[0],g_guard_random_range[1])+0.5f;
        }
        if ((moby_run_entry_hook_by_mode_pal(moby,vars+0x2E0,0)&128) || vec_distance_xy(moby+0x10,g_hero_position)>F(vars,0x334)) {
            if (math_random_int_below(2)) moby_set_state(moby,6,-1);
            else moby_set_state(moby,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=6) anim_start_blended_pal(moby,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(vars,0x2F0)=math_fast_sin_or_cos_a(angle)*speed;
            F(vars,0x2F4)=math_fast_sin_or_cos_b(angle)*speed;
            W(vars,0x2F8)=0;
            FastVecAdd(vars+0x2F0,vars+0x2F0,vars+0x2E0);
            if (W(vars,0x218)!=-1) {
                vec=*(Quad *)(vars+0x2E0);
                path_clamp_move_to_area(&vec,vars+0x2F0,vars+0x2F0,W(vars,0x218),1.5f);
            }
        }
        moby_run_entry_hook_by_mode_pal(moby,vars+0x2F0,0);
        if (U(moby,0x96)>25 && (F(vars,0x1CC)<=0.5f || U(moby,0x96)>150)) moby_set_state(moby,3,-1);
        break;
    case 8:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=math_random_int_below(2)+2) anim_start_blended_pal(moby,math_random_int_below(2)+2,0,8);
        }
        if (B(moby,0x60)&2) moby_set_state(moby,9,-1);
        break;
    case 9:
        if (flag_set_first_pending(moby) && B(moby,0x43)!=6) anim_start_blended_pal(moby,6,0,4);
        if (!(U(moby,0x96)&3)) F(vars,0x31C)=(float)moby_count_group_side_from_object(moby,g_hero_moby[0],-1)*0.087266475f;
        moby_run_entry_hook_by_mode_pal(moby,vars+0x1F0,1);
        turret_clamp_aim_yaw_pitch(moby);
        if (F(vars,0x1CC)<=1.25f) moby_set_state(moby,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            F(vars,0x320)=mat_fast_helper_a(F(vars,0x1F0)-F(moby,0x10),F(vars,0x1F4)-F(moby,0x14));
            if (B(moby,0x43)!=8) anim_start_blended_pal(moby,8,2,8);
        }
        moby_start_effect_from_entry(moby,F(vars,0x320));
        if (math_is_value_within_step_pal(moby,13.0f)) {
            char *t=*(char **)(vars+0x200);
            int play=1;
            if (t && H(t,0xAA)==0x964 && U(moby,0x96)<=49) play=0;
            if (play) coll_test_hit_at_bone(moby,1,0.75f,1.0f,0x4000001,1.0f,0,1,0);
        }
        if ((B(moby,0x60)&2) && vec_distance_xy(moby+0x10,vars+0x1F0)>1.25f) moby_set_state(moby,9,-1);
        break;
    case 14:
        if (flag_set_first_pending(moby)) {
            if (B(moby,0x43)!=10) anim_start_blended_pal(moby,10,0,5);
            W(vars,0x1BC)=g_frame_tick_counter[0];
        }
        vec_scale_to_length(&vec,vars+0x1A0,1.0f);
        moby_run_entry_hook_by_mode_pal(moby,&vec,0);
        part_spawn_falling_puff_pal(moby);
        coll_sweep_from_object(moby,moby+0x10,0.6f,1.0f,0x4000000,1.0f,0,1,0);
        if (F(vars,0x190)>=F(moby,0x18)) {
            if (H(vars,0x314)==1) moby_set_state(moby,8,2);
            else moby_set_state(moby,2,0);
            W(vars,0x138)&=~0x11;
        }
        break;
    case 12: moby_l02_explode_and_remove_pal(moby); break;
    }
    moby_reset_turn_place_pal(moby);
    if (B(moby,0x31)) group_marker_update_pulse_pal(moby);
}
