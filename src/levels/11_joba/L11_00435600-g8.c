#include "common.h"
struct AnimationView { char pad[0x43]; unsigned char animation; };
#define ANIM(p) (((struct AnimationView *)(p))->animation)
typedef int Quad __attribute__((mode(TI)));
#define COPY(d,s) (*(Quad *)(d)=*(Quad *)(s))
#define B(p,n) (*(unsigned char *)((char *)(p)+(n)))
#define H(p,n) (*(short *)((char *)(p)+(n)))
#define U(p,n) (*(unsigned short *)((char *)(p)+(n)))
#define I(p,n) (*(int *)((char *)(p)+(n)))
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
extern int D_L11_001A8FF4 __attribute__((sda));
extern char g_hero_position[];
extern char *D_L11_001C0D18 NOT_SDA;
extern char *g_active_attacker_robot NOT_SDA;
extern void flying_enemy_hit_and_init(char *),enemy_count_frames_draw_glow(char *),enemy_reset_to_idle(char *);
extern void enemy_pick_random_home_spot(char *,char *);
extern int enemy_aim_at_group_entity_in_cone_short(char *,void *);
extern char *arena_get_center_point(char *);
extern int arena_is_point_in_polygon(char *,void *);
extern void moby_set_anim_type_three(char *,int,int);
extern void moby_set_state(void *,int,int),anim_start_blended(void *,int,int,int);
extern int math_random_int_below(int),flag_set_second_pending(void *),flag_set_first_pending(void *),moby_dispatch_action_by_kind(void *,void *);
extern float vec_get_heading_angle(void *,void *,void *),mat_fast_helper_a(float,float),FastDiffRots(float,float),fast_vec_dist(void *,void *),vec_distance_xy(void *,void *),moby_get_anim_value(void *),math_random_float_range(float,float);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float),euler_rotation_basis(void *,void *),mat_get_euler_angles(void *,void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float),moby_l01_turn_toward_target(void *,void *),moby_aim_at_target_offset(void *,void *),moby_turn_toward_target_and_step(void *,void *,float),moby_step_controller(void *,void *,float),moby_step_at_own_position_factor(void *,float),hero_set_control_motion_and_step(void *,void *),moby_rotate_about_point(void *,void *,float,float,float);
extern int coll_test_point(void *,int,void *,float);
extern void coll_test_hit_at_bone(void *,int,int,int,int,int,float,float,float);
static __inline__ void SetAnimation(char *moby, int animation, int mode, int blend)
{
    if (ANIM(moby) != animation) anim_start_blended(moby, animation, mode, blend);
}
/* Flies to one point from afar and another up close; case 7 uses one point for both. */
static __inline__ void FlyByDistance(char *moby, float *farPoint, float *nearPoint, float distance)
{
    if (distance>3.0f) moby_aim_at_target_offset(moby,farPoint);
    else moby_aim_at_target_offset(moby,nearPoint);
}
/* Runs the flying enemy: it hovers, chases and attacks the hero, and plays the matching animations in each state. */
void flying_l11_enemy_update(char *moby)
{
    float target[4],delta[4],zero[4],matrix[4][4];
    char *vars=P(moby,0x68), *node;
    float angle,turn,distance;
    int i,flags,clear;
    float *spin;
    if (B(moby,0x20)==1) return;
    if (H(vars,0x286) && !D_L11_001A8FF4 && B(moby,0x20)!=11 && B(moby,0x20)!=10) return;
    flying_enemy_hit_and_init(moby);
    if (B(moby,0x20)==1) return;
    if (H(vars,0x286) && !D_L11_001A8FF4) return;
    if (!H(vars,0x282)) {
        I(vars,0x270)=0;
        if (B(moby,0x95)==3) {
            moby_set_state(moby,5,2);
            if (math_random_int_below(2)) {
                SetAnimation(moby,1,0,10);
            } else SetAnimation(moby,4,0,10);
        }
    }
    node=0;
    if (P(moby,0xB8)) node=arena_get_center_point(P(moby,0xB8));
    if (I(vars,0x270)) COPY(target,P(vars,0x270)+0x10); else COPY(target,g_hero_position);
    if (H(vars,0x286)) {
        FastVecSub(delta,target,moby+0x10);
        angle=0;
        turn=vec_get_heading_angle(moby,delta,vars+0x210);
    } else {
        angle=mat_fast_helper_a(target[0]-F(moby,0x10),target[1]-F(moby,0x14));
        turn=FastDiffRots(angle,F(moby,0xF8));
    }
    distance=fast_vec_dist(moby+0x10,target);
    if (B(moby,0x95)==2) {
        if (flag_set_second_pending(moby)) {
            SetAnimation(moby,6,0,10);
            B(moby,0xBC)=0;
            moby_set_controller_speed_limits(moby,0.00444444455f,0.1333333403f,0.006981317885f,0.2094395459f);
            enemy_pick_random_home_spot(moby,node);
            U(moby,0x96)=10000;
        }
        if (B(moby,0xBC)==1 && U(moby,0x96)>=301) {
            switch (math_random_int_below(2)) {
            case 0:
                SetAnimation(moby,1,0,10);
                break;
            case 1:
                SetAnimation(moby,4,0,10);
                break;
            }
            U(moby,0x96)=math_random_int_below(100);
        }
        if (H(vars,0x282)) {
            moby_set_state(moby,6,3);
            SetAnimation(moby,2,0,10);
        }
        {
            char *home=vars+0x250;
            if (!B(moby,0xBC) && vec_distance_xy(moby+0x10,home)<0.5f) B(moby,0xBC)=1;
            else if (H(vars,0x286)) moby_aim_at_target_offset(moby,home);
            else moby_l01_turn_toward_target(moby,home);
        }
    }
    switch (B(moby,0x20)) {
    case 3:
        if (flag_set_first_pending(moby)) {
            B(moby,0xBC)=0;
            SetAnimation(moby,1,0,0);
            U(moby,0x96)=0;
        }
        if (!B(moby,0xBC) && H(vars,0x284)<U(moby,0x96)) {
            SetAnimation(moby,6,0,10);
            B(moby,0xBC)=1;
        } else if (B(moby,0xBC)==1) {
            if (arena_is_point_in_polygon(P(moby,0xB8),moby+0x10)) moby_set_state(moby,5,2);
            moby_l01_turn_toward_target(moby,arena_get_center_point(P(moby,0xB8)));
        }
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            SetAnimation(moby,6,0,10);
            U(moby,0x96)=0;
        }
        vec_scale_to_length(zero,moby+0xE0,F(vars,0x104)+F(vars,0x100));
        FastVecAdd(delta,moby+0x10,zero);
        clear=1;
        if (coll_test_point(delta,5,moby,F(vars,0x100)) && D_L11_001C0D18 && H(D_L11_001C0D18,0xAA)==MOBY_CLASS_ARACHNOID) clear=0;
        if (clear) {
            I(moby,0x98)=I(P(moby,0x24),0x10);
            moby_set_state(moby,5,2);
        }
        F(moby,0x18)+=0.1333333403f;
        break;
    case 5: break;
    case 6:
        if (B(moby,0x60)&2) moby_set_state(moby,7,-1);
        break;
    case 7:
        if (flag_set_first_pending(moby)) SetAnimation(moby,6,0,15);
        if (B(moby,0x42)==5 && distance>14.0f) {
            SetAnimation(moby,6,0,4);
            moby_set_controller_speed_limits(moby,0.00444444455f,0.1333333403f,0.006981317885f,0.2094395459f);
        } else if (B(moby,0x42)==6 && distance<9.0f) {
            SetAnimation(moby,5,0,4);
            moby_set_controller_speed_limits(moby,0.002222222276f,0.06666667014f,0.006981317885f,0.2094395459f);
        }
        if (H(vars,0x286)) {
            if (distance<3.0f && turn<0.01745329425f) {
                moby_set_state(moby,9,-1);
                SetAnimation(moby,3,4,3);
            } else FlyByDistance(moby,target,target,distance);
        } else {
            if (distance<3.0f && turn<0.01745329425f) {
                moby_set_state(moby,9,-1);
                SetAnimation(moby,3,4,3);
            } else if (distance>3.0f) {
                if (!enemy_aim_at_group_entity_in_cone_short(moby,moby+0x10)) moby_turn_toward_target_and_step(moby,target,F(vars,0x274));
            } else moby_step_controller(moby,moby+0x10,angle);
        }
        break;
    case 8:
        if (flag_set_first_pending(moby)) moby_set_controller_speed_limits(moby,0.1388888955f,1.666666746f,0.00349065894f,0.1047197729f);
        if (B(moby,0x42)==7) {
            if (moby_get_anim_value(moby)<=14.0f) {
                if (H(vars,0x286)) moby_aim_at_target_offset(moby,target);
                else moby_step_controller(moby,target,angle);
                coll_test_hit_at_bone(moby,0,1,0,1,0,0.4f,B(vars,0x34),1.0f);
            } else {
                moby_set_controller_speed_limits(moby,0.05555555597f,0.03333333507f,0.00349065894f,0.1047197729f);
                vec_scale_to_length(delta,moby+0xC0,-4.0f);
                FastVecAdd(delta,moby+0x10,delta);
                I(vars,0x138)|=0x10;
                if (H(vars,0x286)) moby_aim_at_target_offset(moby,delta); else moby_l01_turn_toward_target(moby,delta);
                I(vars,0x138)&=~0x10;
                coll_test_hit_at_bone(moby,0,1,0,1,0,0.4f,B(vars,0x34),1.0f);
            }
        }
        if (B(moby,0x60)&2) {
            if (g_active_attacker_robot==moby) {
                SetAnimation(moby,2,0,10);
                moby_set_state(moby,6,-1);
            } else moby_set_state(moby,7,-1);
        }
        break;
    case 9:
        if (!H(vars,0x286)) moby_step_at_own_position_factor(moby,angle);
        if (B(moby,0x60)&2) {
            SetAnimation(moby,7,4,3);
            moby_set_state(moby,8,-1);
        }
        break;
    case 10:
        flags=moby_dispatch_action_by_kind(moby,vars+0x50);
        if (B(moby,0x42)==8) {
            if (!math_random_int_below(30) || (flags&1)) {
                if (moby_get_anim_value(moby)<10.0f && H(vars,0x286) && !math_random_int_below(2)) moby_set_state(moby,11,-1);
                else { moby_set_anim_type_three(moby,0,-1); enemy_reset_to_idle(moby); }
            }
        } else if (flags&2) {
            SetAnimation(moby,2,0,10);
            moby_set_state(moby,6,3);
        }
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            FastVecSub(vars+0x1A0,arena_get_center_point(P(moby,0xB8)),moby+0x10);
            F(vars,0x1A8)=0;
            vec_scale_to_length(vars+0x1A0,vars+0x1A0,math_random_float_range(3.0f,5.0f)*0.0166666675f);
            H(vars,0x286)=0;
            spin=(float *)(vars+0x260);
            for (i=0;i<3;i++) {
                spin[i]=math_random_float_range(240.0f,720.0f)*0.0002908882452175021f;
                qcopy(matrix[i],moby+0xC0+i*16);
            }
            mat_get_euler_angles(matrix,moby+0xF0);
            SetAnimation(moby,9,0,30);
            U(moby,0x34)&=0xEFFF;
        }
        F(vars,0x1A8)-=F(vars,0x12C);
        hero_set_control_motion_and_step(moby,vars+0x1A0);
        FastVecScale(vars+0x260,vars+0x260,0.98f);
        *(Quad *)zero=0;
        zero[2]=F(vars,0x30);
        COPY(delta,zero);
        moby_rotate_about_point(moby,delta,F(vars,0x260),F(vars,0x264),F(vars,0x268));
        euler_rotation_basis(moby+0xC0,moby+0xF0);
        if (F(moby,0x18)<F(arena_get_center_point(P(moby,0xB8)),8)+5.0f || !math_random_int_below(450) || U(moby,0x96)>=301) {
            moby_set_anim_type_three(moby,0,-1);
            enemy_reset_to_idle(moby);
        }
        break;
    }
    enemy_count_frames_draw_glow(moby);
}
