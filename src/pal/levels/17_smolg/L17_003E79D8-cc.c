#include "names.h"
/* func_PAL_L17_003E79D8, the PAL copy of func_L17_003E31E8: the same C with the 50 Hz values. Tick counts
   and timer ranges scaled by (x * 5 + 2) / 6, per-tick rates by 6/5 and 1/60 becomes 0.02; the wander timer
   is scaled in floats, (t * 60 * 5 + 2) / 6. In its own unit because its declarations differ from
   L17_003E7938.c's and for its jump tables. */
#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int g_grulch_disabled_flag[];
extern int g_spark_effect_state MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern char *g_moby_l17_pool[] __attribute__((sda));
extern float g_grulch_near_distance SDATA(D_L17_001B0CAC);
extern float g_grulch_approach_speed_a SDATA(D_L17_001B0CB0);
extern float g_grulch_approach_speed_b SDATA(D_L17_001B0CB4);
typedef struct { char pad[0x80]; float x,y; } L17HeroRecord;
extern L17HeroRecord g_hero_state;
extern void grulch_init_state_check_hits_pal(char *);
extern void platform_set_path_index(char *,char *);
extern int ride_platform_can_start(char *);
extern void ride_platform_start(char *);
extern void grulch_activate_group_members_pal(char *);
extern void grulch_turn_and_fall_pal(char *);
extern void grulch_update_animation(char *);
extern int grulch_update_pulled_in_pal(char *);
extern int math_fast_float_d(int *);
extern int FastDecTimer(short *);
extern void moby_set_state(char *,int,int);
extern void anim_start_blended_pal(char *,int,int,int);
extern void anim_start_immediate(char *,int,int);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *,void *);
extern void SetDeathBits_pal(char *,int,int);
extern void part_queue_moby_for_glow(char *,int,int);
extern void moby_mark_spawned(char *);
extern f32 ApproachValue(float *,float,float);
extern void moby_wander_around_home_point_pal(char *,void *,float,float);
extern float mat_fast_helper_a(float,float);
extern void StepAngleTowardTarget(float *,int,float,float);
extern int flag_set_first_pending(char *);
extern float vec_distance_xy(void *,void *);
extern int math_is_value_within_step_pal(char *,float);
extern int PlayMobySound(int,int,char *);
extern int coll_sweep_from_object(char *,float,void *,int,float,float,int,int,int);
extern void moby_set_controller_speed_limits(char *,float,float,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int moby_move_to_target_temp_limits_pal(char *,void *,int,float,float,float);
extern float math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void add_vectors(void *,void *,void *);
extern float FastAddRotations(float,float);
extern float MobySpringTurn(char *,float,float *,float,float,float);

/* Main update of the Grulch enemy (PAL: 50 Hz timings): reacts to the player, wanders, chases, attacks and handles its states. */
void grulch_update_pal(char *object)
{
    float movement[4], position[4];
    char *vars, *other;
    int flags;
    float angle;
    if (g_grulch_disabled_flag[0]) return;
    vars=P(object,0x68);
    if (g_spark_effect_state==2) {
        if (!B(object,0x31)) return;
        I(vars,0x454)=1;
        I(object,0x98)=0;
        U(object,0x34)=(U(object,0x34)|0x41)&0xEFFF;
        return;
    }
    if (I(vars,0x454)) {
        U(object,0x34)=(U(object,0x34)&0xFFBE)|0x1000;
        I(object,0x98)=I(P(object,0x24),0x10);
        I(vars,0x454)=0;
    }
    grulch_init_state_check_hits_pal(object);
    math_fast_float_d((int *)(vars+0x440));
    if (I(vars,0x450)!=-1) {
        other=(char *)((I(vars,0x450)<<8)+(u32)g_moby_l17_pool[0]);
        if (H(other,0xAA)==0x929) platform_set_path_index(other,object);
    }
    switch(B(object,0x95)) {
    case 0:
        if (I(vars,0x428)==-1 || I(vars,0x42C)==-1 ||
            g_moby_l17_pool[0]+(I(vars,0x42C)<<8)==object ||
            !(g_moby_l17_pool[0]+(I(vars,0x42C)<<8)) ||
            B(g_moby_l17_pool[0]+(I(vars,0x42C)<<8),0x20)==0xFE ||
            B(g_moby_l17_pool[0]+(I(vars,0x42C)<<8),0x20)==0xFD ||
            !ride_platform_can_start(g_moby_l17_pool[0]+(I(vars,0x428)<<8))) {
            math_fast_float_d((int *)(vars+0x41C));
            if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                grulch_activate_group_members_pal(object);
                if(I(vars,0x428)!=-1) {
                    if(!ride_platform_can_start(g_moby_l17_pool[0]+(I(vars,0x428)<<8))) break;
                    ride_platform_start(g_moby_l17_pool[0]+(I(vars,0x428)<<8));
                    { char *entity_base = g_moby_l17_pool[0];
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                    if(H((I(vars,0x428)<<8)+(u32)entity_base,0xAA)==0x929) {
                        moby_set_state(object,8,3);
                        anim_start_immediate(object,9,0);
                        F(object,0xF8)=F((char *)((I(vars,0x428)<<8)+(u32)g_moby_l17_pool[0]),0xF8);
                        I(vars,0x428)=-1;
                    } else {
                        I(vars,0x428)=-1;
                        moby_set_state(object,10,2);
                        if(B(object,0x43)!=2) anim_start_blended_pal(object,2,0,12);
                        goto restore_collision;
                    }
                    }
                } else {
                    moby_set_state(object,10,2);
                    if(B(object,0x43)!=2) anim_start_blended_pal(object,2,0,12);
restore_collision:
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                }
            } else if(H(vars,0x406)) {
                moby_set_state(object,2,1);
                H(vars,0x406)=0;
                I(vars,0x3FC)=FloatToInt((math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*300.0f+2.0f)*0.16666667f);
                H(vars,0x400)=0;
            }
        }
        break;
    case 1:
        if(H(vars,0x404)==1 && I(vars,0x440)==0) {
            grulch_activate_group_members_pal(object);
            moby_set_state(object,10,2);
            if(B(object,0x43)!=2) anim_start_blended_pal(object,2,0,12);
        } else if(I(vars,0x3FC)==0) {
            moby_set_state(object,1,0);
            if(B(object,0x43)!=0) anim_start_blended_pal(object,0,0,10);
        }
        break;
    case 2:
        if(H(vars,0x404)!=1 && math_random_int_below(19)==0) {
            moby_set_state(object,2,1);
            I(vars,0x3FC)=FloatToInt((math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*300.0f+2.0f)*0.16666667f);
            H(vars,0x400)=0;
        }
        break;
    case 3:
        if(flag_set_second_pending(object) && F(object,0x48)<0.0f) F(object,0x48)=1.0f;
        if(B(object,0x20)!=8) {
            flags=moby_dispatch_action_by_kind(object,vars+0x60);
            if(flags&1) {
                H(vars,0x98)=0;
                SetDeathBits_pal(object,0,3);
                part_queue_moby_for_glow(object,0,0);
                return;
            }
            if(flags&2) {
                if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                    grulch_activate_group_members_pal(object);
                    moby_set_state(object,4,2);
                    if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
                } else {
                    moby_set_state(object,2,1);
                    I(vars,0x3FC)=FloatToInt((math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*300.0f+2.0f)*0.16666667f);
                    H(vars,0x400)=math_random_int_range(100,583);
                }
            }
        }
        break;
    }
    if(F(object,0x18)-F(vars,0x3D8)>10.0f || F(object,0x18)<10.0f) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits_pal(object,0,3);
        moby_mark_spawned(object);
        return;
    }
    if(F(object,0x18)<75.0f && g_current_map_index==11) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits_pal(object,0,3);
        moby_mark_spawned(object);
        return;
    }
    switch(B(object,0x20)) {
    case 1:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)==0 && H(vars,0x400)!=0) {
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
        }
        if(H(vars,0x400)>17) ApproachValue((float *)(vars+0x124),g_grulch_approach_speed_a*0.020000001f,0.0028000001f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0028000001f);
        if(B(object,0x43)==9) {
            F(object,0x48)=0.8f;
            if(H(vars,0x400)==0) {
                if(B(object,0x43)!=math_random_int_below(2)) anim_start_blended_pal(object,math_random_int_below(2),0,10);
            }
            moby_wander_around_home_point_pal(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==0 || B(object,0x43)==1) && (B(object,0x60)&2)) {
            H(vars,0x400)=math_random_int_range(100,417);
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,10);
        }
        break;
    case 2:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)!=9 && B(object,0x43)!=5 && B(object,0x43)!=4) {
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
        }
        if(H(vars,0x400)>17) ApproachValue((float *)(vars+0x124),g_grulch_approach_speed_b*0.020000001f,0.0028000001f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0028000001f);
        if(B(object,0x43)==9) {
            if(H(vars,0x400)==0) {
                anim_start_blended_pal(object,5,0,10);
                if(math_random_int_below(2)==1 && B(object,0x43)!=4) anim_start_blended_pal(object,4,0,10);
            }
            moby_wander_around_home_point_pal(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==4 || B(object,0x43)==5) && (B(object,0x60)&2)) {
            H(vars,0x400)=math_random_int_range(100,167);
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,10);
        }
        goto restore_animation_speed;
    case 10:
        if(B(object,0x60)&2) {
            moby_set_state(object,4,-1);
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
        }
        StepAngleTowardTarget((float *)(object+0xF8),0,mat_fast_helper_a(g_hero_state.x-F(object,0x10),g_hero_state.y-F(object,0x14)),0.12566373f);
        break;
    case 4:
        if(flag_set_first_pending(object)) I(vars,0x418)=math_random_int_range(67,83);
        F(object,0x48)=1.0f;
        if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)<=g_grulch_near_distance) {
            moby_set_state(object,5,2);
            if(B(object,0x43)!=6) anim_start_blended_pal(object,6,2,5);
            F(vars,0x414)=0;
        } else if(math_fast_float_d((int *)(vars+0x418))) {
            /* The separate magnitude lets angle avoid crossing the side call, so its store
               schedules after the arguments of the timer call below. */
            {
                float magnitude=math_random_float_range(0.26179942f,0.52359884f);
                int side=math_random_int_below(2);
                angle=magnitude;
                if(side==0) angle=-angle;
                F(vars,0x414)=angle;
            }
            I(vars,0x418)=math_random_int_range(125,167);
            moby_set_state(object,5,2);
            if(B(object,0x43)!=6) anim_start_blended_pal(object,6,2,5);
        }
        break;
    case 5:
        if(B(object,0x42)==6) {
            if(math_is_value_within_step_pal(object,8.0f)) PlayMobySound(3,0,object);
            if(B(object,0x42)==6) {
                if(math_is_value_within_step_pal(object,10.0f)) {
                    if(coll_sweep_from_object(object,1.0f,object+0x10,0x4000001,F(vars,0x430),1.0f,0,1,0)>0) I(vars,0x448)=1;
                    else I(vars,0x448)=0;
                } else if(B(object,0x42)==6 && ((B(object,0x60)&2) || math_is_value_within_step_pal(object,11.0f))) {
                    if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)>g_grulch_near_distance) {
                        if((vec_distance_xy(object+0x10,P(vars,0x408)+0x10)==0.0f ? 1.0f : 0.0f)>g_grulch_near_distance) {
                            if(math_random_int_range(0,7)>0) {
                                moby_set_state(object,11,2);
                                if(B(object,0x43)!=7) anim_start_blended_pal(object,7,0,12);
                            }
                        } else {
                            moby_set_state(object,6,2);
                            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
                        }
                    }
                }
            }
        }
        break;
    case 11:
        if(B(object,0x60)&2) {
            moby_set_state(object,4,2);
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,0);
        }
        break;
    case 6:
        moby_set_controller_speed_limits(object,0.0072000003f,0.120000005f,0.025132746f,1.2566373f);
        if(flag_set_first_pending(object)) {
            FastVecSub(vars+0x3E0,object+0x10,P(vars,0x408)+0x10);
            F(vars,0x3E8)=0;
            vec_scale_to_length(vars+0x3E0,vars+0x3E0,10.0f);
            FastVecAdd(vars+0x3E0,vars+0x3E0,object+0x10);
            F(object,0x48)=-1.0f;
        }
        moby_move_to_target_temp_limits_pal(object,vars+0x3E0,16,mat_fast_helper_a(F(vars,0x3E0)-F(object,0x10),F(vars,0x3E4)-F(object,0x14)),-1.0f,-1.0f);
        if(B(object,0x42)==2 && (B(object,0x60)&2)) {
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,8);
            F(object,0x48)=1.0f;
        }
        if(B(object,0x42)==9 && (B(object,0x60)&2)) {
            if(I(vars,0x448)==0) {
                moby_set_state(object,4,2);
                if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,5);
            } else {
                moby_set_state(object,11,2);
                if(B(object,0x43)!=7) anim_start_blended_pal(object,7,0,12);
                I(vars,0x448)=0;
            }
restore_animation_speed:
            F(object,0x48)=1.0f;
        }
        break;
    case 8:
        movement[0]=math_fast_sin_or_cos_a(F(object,0xF8))*0.020000001f*(F(vars,0x40C)+F(vars,0x40C));
        movement[1]=math_fast_sin_or_cos_b(F(object,0xF8))*0.020000001f*(F(vars,0x40C)+F(vars,0x40C));
        movement[2]=0;
        add_vectors(position,object+0x10,movement);
        if(vec_distance_xy(object+0x10,vars+0x3D0)>6.0f) moby_set_state(object,4,2);
        break;
    case 3:
        angle=FastAddRotations(mat_fast_helper_a(F(P(vars,0x408),0x10)-F(object,0x10),F(P(vars,0x408),0x14)-F(object,0x14)),F(vars,0x414));
        MobySpringTurn(object,angle,(float *)(vars+0x410),0.05f,0.3f,0.12566373f);
        if(B(object,0x60)&2) {
            moby_set_state(object,4,-1);
            if(B(object,0x43)!=9) anim_start_blended_pal(object,9,0,12);
        }
        break;
    case 9:
        if(grulch_update_pulled_in_pal(object)) {
            SetDeathBits_pal(object,0,3);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if(B(object,0x20)!=8 && B(object,0x20)!=9 && B(object,0x20)!=6) grulch_turn_and_fall_pal(object);
    grulch_update_animation(object);
}
