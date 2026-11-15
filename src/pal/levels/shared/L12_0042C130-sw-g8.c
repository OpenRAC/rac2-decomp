/* func_PAL_L12_0042C130, the PAL copy of func_L12_00426C08: the same C, with the rates and speeds
 * rescaled for 50 Hz and the random timers written with the 5/6 scale. */
#include "common.h"
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(s16 *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern float D_L12_001B21C0 __attribute__((sda));
extern float D_L12_001B21C4 __attribute__((sda));
/* A float pair (lower, upper) read through two address forms. The sda incomplete array has no
 * .extern, so the assembler builds the upper bound with $at, and read as symbol+offset that load
 * stays ahead of the call while the lower bound takes the delay slot. The SDATA view gives the
 * $gp lower bound. */
extern float D_L12_001B21C8[] __attribute__((sda));
extern float D_L12_001B21C8_gp[] SDATA(D_L12_001B21C8);
extern int D_L12_001B29C8[] __attribute__((sda));
extern char D_0018A0E0[], g_hero_position[];
extern int g_hero_moby[];
extern void func_PAL_L12_0042CD98(void *);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int math_random_int_below(int);
extern int FastDecTimer(void *);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void func_PAL_L12_0042D378(void *);
extern int coll_point_inside_region(void *,int);
extern void vec_clear_128(void *);
extern float FastVecDot(void *,void *);
extern float fast_vec_dist(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern void path_clamp_move_to_area(void *,void *,void *,int,float);
extern int func_PAL_L12_0042D200(void *,void *,int);
extern int moby_check_target_point_from_offset(void *,void *);
extern int moby_count_group_side_from_object(void *,int,int);
extern void moby_turn_toward_target_limited(void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int func_PAL_002AF6C0(void *,float);
extern int coll_test_hit_at_bone(void *,int,int,int,int,int,float,float,float);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void func_PAL_L07_003FB6B0(void *);
extern void func_PAL_L12_0042D258(void *);
extern void func_PAL_L12_0042D5E8(void *);

void func_PAL_L12_0042C130(char *obj) {
    char *s = *(char **)(obj+0x68);
    /* The aligned local preserves the old position or a temporary vector. */
    typedef int Quad __attribute__((mode(TI)));
    Quad vec;
    int flags;
    float angle, speed;
    func_PAL_L12_0042CD98(obj);
    switch (B(obj,0x95)) {
    case 0:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.010053098f,0.5026549f);
            F(s,0x1D0)=D_L12_001B21C4*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.5f;
            H(s,0x35A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x334)==1 && FastDecTimer(s+0x35A)) {
            if (math_random_int_below(3)) moby_set_state(obj,9,2);
            else moby_set_state(obj,8,2);
        } else if (H(s,0x336)) {
            if (math_random_int_below(2)) moby_set_state(obj,7,1);
            else moby_set_state(obj,6,1);
            H(s,0x336)=0;
            if (H(s,0x330)<250) H(s,0x330)=((s32)(math_random_int_range(480,600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=D_L12_001B21C0*0.020000001f;
            F(s,0x134)=0.05f;
        }
        if (H(s,0x334)==1) moby_set_state(obj,9,2);
        else if (H(s,0x330)==0) moby_set_state(obj,1,0);
        break;
    case 2:
        if (flag_set_second_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0072000003f,0.080000006f,0.025132746f,1.2566373f);
            F(s,0x1D0)=D_L12_001B21C0*0.020000001f;
            F(s,0x124)=0.0096f;
            F(s,0x134)=0.05f;
            H(s,0x35A)=((s32)(math_random_int_range(0,30)) * 5 + 2) / 6;
        }
        if (H(s,0x334)!=1 && FastDecTimer(s+0x35A)) {
            moby_set_state(obj,3,1);
            H(s,0x330)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        vec=*(Quad *)(obj+0x10);
        flags=moby_dispatch_action_by_kind(obj,s+0x50);
        if (flags&1) func_PAL_L12_0042D378(obj);
        else if (!coll_point_inside_region(obj+0x10,W(s,0x230))) {
            qcopy(obj+0x10,&vec);
            vec_clear_128(s+0xD0);
        } else if (flags&2) {
            if (H(s,0x334)==1) moby_set_state(obj,9,2);
            else {
                moby_set_state(obj,3,1);
                H(s,0x330)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
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
            H(s,0x332)=((s32)(math_random_int_range(60,120)) * 5 + 2) / 6;
        }
        if (B(obj,0x43)==1) {
            if (B(obj,0x60)&2) func_PAL_002A7E68(obj,0,0,17);
        } else if (H(s,0x332)==0) {
            if (!H(s,0x358) || FastVecDot(s+0x320,D_0018A0E0)>0.8f) moby_set_state(obj,2,-1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(s,0x310)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x314)=math_fast_sin_or_cos_b(angle)*speed;
            W(s,0x318)=0;
            FastVecAdd(s+0x310,s+0x310,s+0x300);
            if (W(s,0x238)!=-1) {
                vec=*(Quad *)(s+0x300);
                path_clamp_move_to_area(&vec,s+0x310,s+0x310,W(s,0x238),1.5f);
            }
        }
        func_PAL_L12_0042D200(obj,s+0x310,0);
        if (U(obj,0x96)>25 && (F(s,0x1CC)<=0.5f || U(obj,0x96)>150)) moby_set_state(obj,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=math_random_int_below(2)+4) func_PAL_002A7E68(obj,math_random_int_below(2)+4,0,8);
        }
        if (fast_vec_dist(obj+0x10,g_hero_position)<D_L12_001B21C8_gp[0]) moby_set_state(obj,4,-1);
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
            F(s,0x354)=math_random_float_range(D_L12_001B21C8_gp[0],D_L12_001B21C8[1])+0.5f;
        }
        if ((func_PAL_L12_0042D200(obj,s+0x300,0)&128) || vec_distance_xy(obj+0x10,g_hero_position)>F(s,0x354)) {
            if (math_random_int_below(2)) moby_set_state(obj,6,-1);
            else moby_set_state(obj,7,-1);
        }
        break;
    case 5:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=6) func_PAL_002A7E68(obj,6,0,17);
            angle=math_random_angle(); speed=math_random_float_range(2,5);
            F(s,0x310)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x314)=math_fast_sin_or_cos_b(angle)*speed;
            W(s,0x318)=0;
            FastVecAdd(s+0x310,s+0x310,s+0x300);
            if (W(s,0x238)!=-1) {
                vec=*(Quad *)(s+0x300);
                path_clamp_move_to_area(&vec,s+0x310,s+0x310,W(s,0x238),1.5f);
            }
        }
        func_PAL_L12_0042D200(obj,s+0x310,0);
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
        if (!(U(obj,0x96)&3)) F(s,0x33C)=(float)moby_count_group_side_from_object(obj,g_hero_moby[0],-1)*0.087266475f;
        func_PAL_L12_0042D200(obj,s+0x1F0,1);
        moby_turn_toward_target_limited(obj);
        if (F(s,0x1CC)<=1.25f) moby_set_state(obj,10,-1);
        break;
    case 10:
        if (flag_set_first_pending(obj)) {
            F(s,0x340)=mat_fast_helper_a(F(s,0x1F0)-F(obj,0x10),F(s,0x1F4)-F(obj,0x14));
            if (B(obj,0x43)!=8) func_PAL_002A7E68(obj,8,2,8);
        }
        moby_start_effect_from_entry(obj,F(s,0x340));
        if (func_PAL_002AF6C0(obj,13.0f)) coll_test_hit_at_bone(obj,1,0x4000001,0,1,0,0.75f,(float)B(s,0x34),1.0f);
        if (B(obj,0x60)&2) moby_set_state(obj,9,-1);
        break;
    case 14:
        if (flag_set_first_pending(obj)) {
            if (B(obj,0x43)!=10) func_PAL_002A7E68(obj,10,0,5);
            W(s,0x1BC)=D_L12_001B29C8[0];
        }
        vec_scale_to_length(&vec,s+0x1A0,1.0f);
        func_PAL_L12_0042D200(obj,&vec,0);
        func_PAL_L07_003FB6B0(obj);
        coll_sweep_from_object(obj,obj+0x10,0x4000000,0,1,0,0.6f,(float)B(s,0x34),1.0f);
        if (F(s,0x190)>=F(obj,0x18)) {
            if (H(s,0x334)==1) moby_set_state(obj,8,2);
            else moby_set_state(obj,2,0);
            W(s,0x138)&=~0x11;
        }
        break;
    case 12: func_PAL_L12_0042D378(obj); break;
    }
    func_PAL_L12_0042D258(obj);
    if (B(obj,0x31)) func_PAL_L12_0042D5E8(obj);
}
