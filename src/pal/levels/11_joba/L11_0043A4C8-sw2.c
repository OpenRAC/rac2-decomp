#include "include_asm.h"

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
extern void func_PAL_L11_0043B8D0(char *),enemy_count_frames_draw_glow(char *),func_PAL_L11_0043BFF8(char *);
extern void enemy_pick_random_home_spot(char *,char *);
extern int func_PAL_L11_0043C288(char *,void *);
extern char *arena_get_center_point(char *);
extern int arena_is_point_in_polygon(char *,void *);
extern void func_PAL_L02_004009A0(char *,int,int);
extern void moby_set_state(void *,int,int),func_PAL_002A7E68(void *,int,int,int);
extern int math_random_int_below(int),flag_set_second_pending(void *),flag_set_first_pending(void *),moby_dispatch_action_by_kind(void *,void *);
extern float vec_get_heading_angle(void *,void *,void *),mat_fast_helper_a(float,float),FastDiffRots(float,float),fast_vec_dist(void *,void *),vec_distance_xy(void *,void *),moby_get_anim_value(void *),math_random_float_range(float,float);
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *),vec_scale_to_length(void *,void *,float),FastVecScale(void *,void *,float),euler_rotation_basis(void *,void *),mat_get_euler_angles(void *,void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float),func_PAL_L01_00323068(void *,void *),func_PAL_L02_00335630(void *,void *),func_PAL_002B5BA8(void *,void *,float),func_PAL_002B5C98(void *,void *,float),func_PAL_002B5E30(void *,float),hero_set_control_motion_and_step(void *,void *),moby_rotate_about_point(void *,void *,float,float,float);
extern int coll_test_point(void *,int,void *,float);
extern void coll_test_hit_at_bone(void *,int,int,int,int,int,float,float,float);
static __inline__ void SetAnimation(char *p, int animation, int mode, int blend)
{
    if (ANIM(p) != animation) func_PAL_002A7E68(p, animation, mode, blend);
}
/* Flies to one point from afar and another up close; case 7 uses one point for both. */
static __inline__ void FlyByDistance(char *p, float *farPoint, float *nearPoint, float distance)
{
    if (distance>3.0f) func_PAL_L02_00335630(p,farPoint);
    else func_PAL_L02_00335630(p,nearPoint);
}

void func_PAL_L11_0043AB80(char *p)
{
    float target[4],delta[4],zero[4],matrix[4][4];
    char *s=P(p,0x68), *node;
    float angle,turn,distance;
    int i,flags,clear;
    float *spin;
    if (B(p,0x20)==1) return;
    if (H(s,0x286) && !D_L11_001A8FF4 && B(p,0x20)!=11 && B(p,0x20)!=10) return;
    func_PAL_L11_0043B8D0(p);
    if (B(p,0x20)==1) return;
    if (H(s,0x286) && !D_L11_001A8FF4) return;
    if (!H(s,0x282)) {
        I(s,0x270)=0;
        if (B(p,0x95)==3) {
            moby_set_state(p,5,2);
            if (math_random_int_below(2)) {
                SetAnimation(p,1,0,8);
            } else SetAnimation(p,4,0,8);
        }
    }
    node=0;
    if (P(p,0xB8)) node=arena_get_center_point(P(p,0xB8));
    if (I(s,0x270)) COPY(target,P(s,0x270)+0x10); else COPY(target,g_hero_position);
    if (H(s,0x286)) {
        FastVecSub(delta,target,p+0x10);
        angle=0;
        turn=vec_get_heading_angle(p,delta,s+0x210);
    } else {
        angle=mat_fast_helper_a(target[0]-F(p,0x10),target[1]-F(p,0x14));
        turn=FastDiffRots(angle,F(p,0xF8));
    }
    distance=fast_vec_dist(p+0x10,target);
    if (B(p,0x95)==2) {
        if (flag_set_second_pending(p)) {
            SetAnimation(p,6,0,8);
            B(p,0xBC)=0;
            moby_set_controller_speed_limits(p,0.0064000003f,0.16000001f,0.010053098f,0.25132746f);
            enemy_pick_random_home_spot(p,node);
            U(p,0x96)=10000;
        }
        if (B(p,0xBC)==1 && U(p,0x96)>=251) {
            switch (math_random_int_below(2)) {
            case 0:
                SetAnimation(p,1,0,8);
                break;
            case 1:
                SetAnimation(p,4,0,8);
                break;
            }
            U(p,0x96)=math_random_int_below(83);
        }
        if (H(s,0x282)) {
            moby_set_state(p,6,3);
            SetAnimation(p,2,0,8);
        }
        {
            char *home=s+0x250;
            if (!B(p,0xBC) && vec_distance_xy(p+0x10,home)<0.5f) B(p,0xBC)=1;
            else if (H(s,0x286)) func_PAL_L02_00335630(p,home);
            else func_PAL_L01_00323068(p,home);
        }
    }
    switch (B(p,0x20)) {
    case 3:
        if (flag_set_first_pending(p)) {
            B(p,0xBC)=0;
            SetAnimation(p,1,0,0);
            U(p,0x96)=0;
        }
        if (!B(p,0xBC) && H(s,0x284)<U(p,0x96)) {
            SetAnimation(p,6,0,8);
            B(p,0xBC)=1;
        } else if (B(p,0xBC)==1) {
            if (arena_is_point_in_polygon(P(p,0xB8),p+0x10)) moby_set_state(p,5,2);
            func_PAL_L01_00323068(p,arena_get_center_point(P(p,0xB8)));
        }
        break;
    case 4:
        if (flag_set_first_pending(p)) {
            SetAnimation(p,6,0,8);
            U(p,0x96)=0;
        }
        vec_scale_to_length(zero,p+0xE0,F(s,0x104)+F(s,0x100));
        FastVecAdd(delta,p+0x10,zero);
        clear=1;
        if (coll_test_point(delta,5,p,F(s,0x100)) && D_L11_001C0D18 && H(D_L11_001C0D18,0xAA)==0xB3A) clear=0;
        if (clear) {
            I(p,0x98)=I(P(p,0x24),0x10);
            moby_set_state(p,5,2);
        }
        F(p,0x18)+=0.16000001f;
        break;
    case 5: break;
    case 6:
        if (B(p,0x60)&2) moby_set_state(p,7,-1);
        break;
    case 7:
        if (flag_set_first_pending(p)) SetAnimation(p,6,0,12);
        if (B(p,0x42)==5 && distance>14.0f) {
            SetAnimation(p,6,0,3);
            moby_set_controller_speed_limits(p,0.0064000003f,0.16000001f,0.010053098f,0.25132746f);
        } else if (B(p,0x42)==6 && distance<9.0f) {
            SetAnimation(p,5,0,3);
            moby_set_controller_speed_limits(p,0.0032000002f,0.080000006f,0.010053098f,0.25132746f);
        }
        if (H(s,0x286)) {
            if (distance<3.0f && turn<0.01745329425f) {
                moby_set_state(p,9,-1);
                SetAnimation(p,3,4,2);
            } else FlyByDistance(p,target,target,distance);
        } else {
            if (distance<3.0f && turn<0.01745329425f) {
                moby_set_state(p,9,-1);
                SetAnimation(p,3,4,2);
            } else if (distance>3.0f) {
                if (!func_PAL_L11_0043C288(p,p+0x10)) func_PAL_002B5BA8(p,target,F(s,0x274));
            } else func_PAL_002B5C98(p,p+0x10,angle);
        }
        break;
    case 8:
        if (flag_set_first_pending(p)) moby_set_controller_speed_limits(p,0.2f,2.0000002f,0.005026549f,0.12566373f);
        if (B(p,0x42)==7) {
            if (moby_get_anim_value(p)<=14.0f) {
                if (H(s,0x286)) func_PAL_L02_00335630(p,target);
                else func_PAL_002B5C98(p,target,angle);
                coll_test_hit_at_bone(p,0,1,0,1,0,0.4f,B(s,0x34),1.0f);
            } else {
                moby_set_controller_speed_limits(p,0.080000006f,0.040000003f,0.005026549f,0.12566373f);
                vec_scale_to_length(delta,p+0xC0,-4.0f);
                FastVecAdd(delta,p+0x10,delta);
                I(s,0x138)|=0x10;
                if (H(s,0x286)) func_PAL_L02_00335630(p,delta); else func_PAL_L01_00323068(p,delta);
                I(s,0x138)&=~0x10;
                coll_test_hit_at_bone(p,0,1,0,1,0,0.4f,B(s,0x34),1.0f);
            }
        }
        if (B(p,0x60)&2) {
            if (g_active_attacker_robot==p) {
                SetAnimation(p,2,0,8);
                moby_set_state(p,6,-1);
            } else moby_set_state(p,7,-1);
        }
        break;
    case 9:
        if (!H(s,0x286)) func_PAL_002B5E30(p,angle);
        if (B(p,0x60)&2) {
            SetAnimation(p,7,4,2);
            moby_set_state(p,8,-1);
        }
        break;
    case 10:
        flags=moby_dispatch_action_by_kind(p,s+0x50);
        if (B(p,0x42)==8) {
            if (!math_random_int_below(30) || (flags&1)) {
                if (moby_get_anim_value(p)<10.0f && H(s,0x286) && !math_random_int_below(2)) moby_set_state(p,11,-1);
                else { func_PAL_L02_004009A0(p,0,-1); func_PAL_L11_0043BFF8(p); }
            }
        } else if (flags&2) {
            SetAnimation(p,2,0,8);
            moby_set_state(p,6,3);
        }
        break;
    case 11:
        if (flag_set_first_pending(p)) {
            FastVecSub(s+0x1A0,arena_get_center_point(P(p,0xB8)),p+0x10);
            F(s,0x1A8)=0;
            vec_scale_to_length(s+0x1A0,s+0x1A0,math_random_float_range(3.0f,5.0f)*0.020000001f);
            H(s,0x286)=0;
            spin=(float *)(s+0x260);
            for (i=0;i<3;i++) {
                spin[i]=math_random_float_range(240.0f,720.0f)*0.0003490659f;
                qcopy(matrix[i],p+0xC0+i*16);
            }
            mat_get_euler_angles(matrix,p+0xF0);
            SetAnimation(p,9,0,25);
            U(p,0x34)&=0xEFFF;
        }
        F(s,0x1A8)-=F(s,0x12C);
        hero_set_control_motion_and_step(p,s+0x1A0);
        FastVecScale(s+0x260,s+0x260,0.98f);
        *(Quad *)zero=0;
        zero[2]=F(s,0x30);
        COPY(delta,zero);
        moby_rotate_about_point(p,delta,F(s,0x260),F(s,0x264),F(s,0x268));
        euler_rotation_basis(p+0xC0,p+0xF0);
        if (F(p,0x18)<F(arena_get_center_point(P(p,0xB8)),8)+5.0f || !math_random_int_below(450) || U(p,0x96)>=301) {
            func_PAL_L02_004009A0(p,0,-1);
            func_PAL_L11_0043BFF8(p);
        }
        break;
    }
    enemy_count_frames_draw_glow(p);
}
