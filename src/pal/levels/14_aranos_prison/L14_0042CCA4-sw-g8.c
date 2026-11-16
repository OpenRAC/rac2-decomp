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
extern void func_PAL_L14_0042D918(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int math_random_int_below(int);
extern int FastDecTimer(void *);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
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
extern int func_PAL_002AF6C0(void *,float);
extern int coll_test_hit_at_bone(void *,int,float,float,int,float,int,int,int);
extern int coll_sweep_from_object(void *,void *,float,float,int,float,int,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void func_PAL_L07_003FB6B0(void *);
extern void moby_reset_turn_place_pal(void *);
extern void group_marker_update_pulse_pal(void *);

void func_PAL_L14_0042CCA4(char *obj) {
    char *s = *(char **)(obj+0x68);
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    func_PAL_L14_0042D918(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.010053098f,0.5026549f);
            F(s,0x1D0)=g_guard_alt_frame_scale*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.5f;
            H(s,0x33A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x314)==1 && FastDecTimer(s+0x33A)) {
            if (math_random_int_below(3)) moby_set_state(obj,9,2);
            else moby_set_state(obj,8,2);
        } else if (H(s,0x316)) {
            if (math_random_int_below(2)) moby_set_state(obj,7,1);
            else moby_set_state(obj,6,1);
            H(s,0x316)=0;
            if (H(s,0x310)<250) H(s,0x310)=((s32)(math_random_int_range(480,600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=g_guard_frame_scale*0.020000001f;
            F(s,0x134)=0.05f;
        }
        if (H(s,0x314)==1) moby_set_state(obj,9,2);
        else if (H(s,0x310)==0) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=g_guard_frame_scale*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.05f;
            H(s,0x33A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x314)!=1 && FastDecTimer(s+0x33A)) {
            moby_set_state(obj,3,1);
            H(s,0x310)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(obj,s+0x50);
        if (flags&1) moby_l02_explode_and_remove_pal(obj);
        else if (flags&2) {
            if (H(s,0x314)==1) moby_set_state(obj,9,2);
            else {
                moby_set_state(obj,3,1);
                H(s,0x310)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (!B(obj,0x31)) break;
        if (flag_set_first_pending(obj)) {
            int choice=!math_random_int_below(4);
            if (B(obj,0x43)!=choice) func_PAL_002A7E68(obj,choice,0,8);
            H(s,0x312)=((s32)(math_random_int_range(60,120)) * 5 + 2) / 6;
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) func_PAL_002A7E68(obj,0,0,17);
        } else if (H(s,0x312)==0) {
            if (!H(s,0x338) || FastVecDot(s+0x300,g_hero_state_block)>0.8f) moby_set_state(obj,2,-1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(s,0x2F0)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x2F4)=math_fast_sin_or_cos_b(angle)*speed;
            W(s,0x2F8)=0;
            FastVecAdd(s+0x2F0,s+0x2F0,s+0x2E0);
            if (W(s,0x218)!=-1) {
                vec=*(Quad *)(s+0x2E0);
                path_clamp_move_to_area(&vec,s+0x2F0,s+0x2F0,W(s,0x218),1.5f);
            }
        }
        moby_run_entry_hook_by_mode_pal(obj,s+0x2F0,0);
        if (U(obj,0x96)>25 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>150)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+4) func_PAL_002A7E68(obj,math_random_int_below(2)+4,0,8);
        }
        if (fast_vec_dist(obj+0x10,g_hero_position)<D_L14_001B18B8_gp[0]) moby_set_state(obj,4,-1);
        else if (B(obj,0x60)&2) {
            switch (math_random_int_below(3)) {
            case 0:moby_set_state(obj,6,-1);break;
            case 1:moby_set_state(obj,7,-1);break;
            case 2:moby_set_state(obj,5,-1);break;
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+2) func_PAL_002A7E68(obj,math_random_int_below(2)+2,0,8);
        }
        moby_check_target_point_from_offset(obj,s+0x1F0);
        if (B(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=12) func_PAL_002A7E68(obj,12,0,8);
        moby_check_target_point_from_offset(obj,s+0x1F0);
        if (B(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,8);
            F(s,0x334)=math_random_float_range(D_L14_001B18B8_gp[0],g_guard_random_range[1])+0.5f;
        }
        if ((moby_run_entry_hook_by_mode_pal(obj,s+0x2E0,0)&128) || vec_distance_xy(obj+0x10,g_hero_position)>F(s,0x334)) {
            if (math_random_int_below(2)) moby_set_state(obj,6,-1);
            else moby_set_state(obj,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(s,0x2F0)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x2F4)=math_fast_sin_or_cos_b(angle)*speed;
            W(s,0x2F8)=0;
            FastVecAdd(s+0x2F0,s+0x2F0,s+0x2E0);
            if (W(s,0x218)!=-1) {
                vec=*(Quad *)(s+0x2E0);
                path_clamp_move_to_area(&vec,s+0x2F0,s+0x2F0,W(s,0x218),1.5f);
            }
        }
        moby_run_entry_hook_by_mode_pal(obj,s+0x2F0,0);
        if (U(obj,0x96)>25 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>150)) moby_set_state(obj,3,-1);
        break;
    case 8:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+2) func_PAL_002A7E68(obj,math_random_int_below(2)+2,0,8);
        }
        if (B(obj,0x60)&2) moby_set_state(obj,9,-1);
        break;
    case 9:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,4);
        if (!(U(obj,0x96)&3)) F(s,0x31C)=(float)moby_count_group_side_from_object(obj,g_hero_moby[0],-1)*0.087266475f;
        moby_run_entry_hook_by_mode_pal(obj,s+0x1F0,1);
        turret_clamp_aim_yaw_pitch(obj);
        if (F(s,0x1CC)<=1.25f) moby_set_state(obj,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            F(s,0x320)=mat_fast_helper_a(F(s,0x1F0)-F(obj,0x10),F(s,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) func_PAL_002A7E68(obj,8,2,8);
        }
        moby_start_effect_from_entry(obj,F(s,0x320));
        if (func_PAL_002AF6C0(obj,13.0f)) {
            char *t=*(char **)(s+0x200);
            int play=1;
            if (t && H(t,0xAA)==0x964 && U(obj,0x96)<=49) play=0;
            if (play) coll_test_hit_at_bone(obj,1,0.75f,1.0f,0x4000001,1.0f,0,1,0);
        }
        if ((B(obj,0x60)&2) && vec_distance_xy(obj+0x10,s+0x1F0)>1.25f) moby_set_state(obj,9,-1);
        break;
    case 14:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=10) func_PAL_002A7E68(obj,10,0,5);
            W(s,0x1BC)=g_frame_tick_counter[0];
        }
        vec_scale_to_length(&vec,s+0x1A0,1.0f);
        moby_run_entry_hook_by_mode_pal(obj,&vec,0);
        func_PAL_L07_003FB6B0(obj);
        coll_sweep_from_object(obj,obj+0x10,0.6f,1.0f,0x4000000,1.0f,0,1,0);
        if (F(s,0x190)>=F(obj,0x18)) {
            if (H(s,0x314)==1) moby_set_state(obj,8,2);
            else moby_set_state(obj,2,0);
            W(s,0x138)&=~0x11;
        }
        break;
    case 12: moby_l02_explode_and_remove_pal(obj); break;
    }
    moby_reset_turn_place_pal(obj);
    if (B(obj,0x31)) group_marker_update_pulse_pal(obj);
}
