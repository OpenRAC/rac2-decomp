/* func_US2_L14_00428BC0, the USA v2.00 copy of func_L14_004275E0: the same C, where rename func_002AEB60 becomes func_US2_002AF9C8. */
#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L14_001B18B0 __attribute__((sda));
extern float D_L14_001B18B4 __attribute__((sda));
/* A float pair (lower, upper), read through two address forms as in func_L12_00426C08. */
extern float D_L14_001B18B8[] __attribute__((sda));
extern float D_L14_001B18B8_gp[] SDATA(D_L14_001B18B8);
extern int D_L14_001B20C8[] __attribute__((sda));
extern char D_0018A0E0[], g_hero_position[];
extern int g_hero_moby[];
extern void guard_update_common(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int math_random_int_below(int);
extern int FastDecTimer(void *);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void moby_l02_explode_and_remove(void *);
extern float FastVecDot(void *,void *);
extern float fast_vec_dist(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern void path_clamp_move_to_area(void *,void *,void *,int,float);
extern int moby_run_entry_hook_by_mode(void *,void *,int);
extern int moby_check_target_point_from_offset(void *,void *);
extern int moby_count_group_side_from_object(void *,int,int);
extern void turret_clamp_aim_yaw_pitch(void *);
extern float mat_fast_helper_a(float,float);
extern void moby_start_effect_from_entry(void *,float);
extern int func_US2_002AF9C8(void *,float);
extern int coll_test_hit_at_bone(void *,int,float,float,int,float,int,int,int);
extern int coll_sweep_from_object(void *,void *,float,float,int,float,int,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_falling_puff(void *);
extern void moby_reset_turn_place(void *);
extern void group_marker_update_pulse(void *);

void func_US2_L14_00428BC0(char *obj) {
    char *s = *(char **)(obj+0x68);
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    guard_update_common(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.005f,0.06666667f,0.006981317885220051f,0.4188791f);
            F(s,0x1D0)=D_L14_001B18B4*0.016666668f;
            F(s,0x124)=0.006666667f;
            F(s,0x134)=0.5f;
            H(s,0x33A)=math_random_int_range(0,30);
        }
        if (H(s,0x314)==1 && FastDecTimer(s+0x33A)) {
            if (math_random_int_below(3)) moby_set_state(obj,9,2);
            else moby_set_state(obj,8,2);
        } else if (H(s,0x316)) {
            if (math_random_int_below(2)) moby_set_state(obj,7,1);
            else moby_set_state(obj,6,1);
            H(s,0x316)=0;
            if (H(s,0x310)<300) H(s,0x310)=math_random_int_range(480,600);
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(s,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(s,0x134)=0.05f;
        }
        if (H(s,0x314)==1) moby_set_state(obj,9,2);
        else if (H(s,0x310)==0) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.005f,0.06666667f,0.017453294f,1.0471977f);
            F(s,0x1D0)=D_L14_001B18B0*0.016666668f;
            F(s,0x124)=0.006666667f;
            F(s,0x134)=0.05f;
            H(s,0x33A)=math_random_int_range(0,30);
        }
        if (H(s,0x314)!=1 && FastDecTimer(s+0x33A)) {
            moby_set_state(obj,3,1);
            H(s,0x310)=math_random_int_range(580,600);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(obj,s+0x50);
        if (flags&1) moby_l02_explode_and_remove(obj);
        else if (flags&2) {
            if (H(s,0x314)==1) moby_set_state(obj,9,2);
            else {
                moby_set_state(obj,3,1);
                H(s,0x310)=math_random_int_range(580,600);
            }
        }
        break;
    }
    switch (B(obj,0x20)) {
    case 1:
        if (!B(obj,0x31)) break;
        if (flag_set_first_pending(obj)) {
            int choice=!math_random_int_below(4);
            if (B(obj,0x43)!=choice) anim_start_blended(obj,choice,0,10);
            H(s,0x312)=math_random_int_range(60,120);
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) anim_start_blended(obj,0,0,20);
        } else if (H(s,0x312)==0) {
            if (!H(s,0x338) || FastVecDot(s+0x300,D_0018A0E0)>0.8f) moby_set_state(obj,2,-1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) anim_start_blended(obj,6,0,20);
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
        moby_run_entry_hook_by_mode(obj,s+0x2F0,0);
        if (U(obj,0x96)>30 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>180)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+4) anim_start_blended(obj,math_random_int_below(2)+4,0,10);
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
            if (B(obj,0x43)!=math_random_int_below(2)+2) anim_start_blended(obj,math_random_int_below(2)+2,0,10);
        }
        moby_check_target_point_from_offset(obj,s+0x1F0);
        if (B(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 7:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=12) anim_start_blended(obj,12,0,10);
        moby_check_target_point_from_offset(obj,s+0x1F0);
        if (B(obj,0x60)&2) moby_set_state(obj,3,-1);
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) anim_start_blended(obj,6,0,10);
            F(s,0x334)=math_random_float_range(D_L14_001B18B8_gp[0],D_L14_001B18B8[1])+0.5f;
        }
        if ((moby_run_entry_hook_by_mode(obj,s+0x2E0,0)&128) || vec_distance_xy(obj+0x10,g_hero_position)>F(s,0x334)) {
            if (math_random_int_below(2)) moby_set_state(obj,6,-1);
            else moby_set_state(obj,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) anim_start_blended(obj,6,0,20);
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
        moby_run_entry_hook_by_mode(obj,s+0x2F0,0);
        if (U(obj,0x96)>30 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>180)) moby_set_state(obj,3,-1);
        break;
    case 8:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+2) anim_start_blended(obj,math_random_int_below(2)+2,0,10);
        }
        if (B(obj,0x60)&2) moby_set_state(obj,9,-1);
        break;
    case 9:
        if (flag_set_first_pending(obj) && B(obj,0x43)!=6) anim_start_blended(obj,6,0,5);
        if (!(U(obj,0x96)&3)) F(s,0x31C)=(float)moby_count_group_side_from_object(obj,g_hero_moby[0],-1)*0.087266475f;
        moby_run_entry_hook_by_mode(obj,s+0x1F0,1);
        turret_clamp_aim_yaw_pitch(obj);
        if (F(s,0x1CC)<=1.25f) moby_set_state(obj,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            F(s,0x320)=mat_fast_helper_a(F(s,0x1F0)-F(obj,0x10),F(s,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) anim_start_blended(obj,8,2,10);
        }
        moby_start_effect_from_entry(obj,F(s,0x320));
        if (func_US2_002AF9C8(obj,13.0f)) {
            char *t=*(char **)(s+0x200);
            int play=1;
            if (t && H(t,0xAA)==0x964 && U(obj,0x96)<=59) play=0;
            if (play) coll_test_hit_at_bone(obj,1,0.75f,1.0f,0x4000001,1.0f,0,1,0);
        }
        if ((B(obj,0x60)&2) && vec_distance_xy(obj+0x10,s+0x1F0)>1.25f) moby_set_state(obj,9,-1);
        break;
    case 14:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=10) anim_start_blended(obj,10,0,5);
            W(s,0x1BC)=D_L14_001B20C8[0];
        }
        vec_scale_to_length(&vec,s+0x1A0,1.0f);
        moby_run_entry_hook_by_mode(obj,&vec,0);
        part_spawn_falling_puff(obj);
        coll_sweep_from_object(obj,obj+0x10,0.6f,1.0f,0x4000000,1.0f,0,1,0);
        if (F(s,0x190)>=F(obj,0x18)) {
            if (H(s,0x314)==1) moby_set_state(obj,8,2);
            else moby_set_state(obj,2,0);
            W(s,0x138)&=~0x11;
        }
        break;
    case 12: moby_l02_explode_and_remove(obj); break;
    }
    moby_reset_turn_place(obj);
    if (B(obj,0x31)) group_marker_update_pulse(obj);
}
