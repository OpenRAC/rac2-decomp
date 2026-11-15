/*
 * Smolg level object update (USA v1.01, level 17 only): state machine on the object's
 * state byte (0x20) with a second dispatch on its mode byte (0x95).  In its own unit
 * because its symbol declarations differ from those in L17_003C7C70.c.
 */

#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u16 *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int D_L17_001CA140[];
extern int D_L17_001A8F00 MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern char *g_moby_l17_pool[] __attribute__((sda));
extern float D_L17_001B0CAC SDATA(D_L17_001B0CAC);
extern float D_L17_001B0CB0 SDATA(D_L17_001B0CB0);
extern float D_L17_001B0CB4 SDATA(D_L17_001B0CB4);
typedef struct { char pad[0x80]; float x,y; } L17HeroRecord;
extern L17HeroRecord g_hero_state;
extern void grulch_init_state_check_hits(char *);
extern void platform_set_path_index(char *,char *);
extern int ride_platform_can_start(char *);
extern void ride_platform_start(char *);
extern void grulch_activate_group_members(char *);
extern void grulch_turn_and_fall(char *);
extern void grulch_update_animation(char *);
extern int grulch_update_pulled_in(char *);
extern int math_fast_float_d(int *);
extern int FastDecTimer(short *);
extern void moby_set_state(char *,int,int);
extern void anim_start_blended(char *,int,int,int);
extern void anim_start_immediate(char *,int,int);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *,void *);
extern void SetDeathBits(char *,int,int);
extern void part_queue_moby_for_glow(char *,int,int);
extern void moby_mark_spawned(char *);
extern void ApproachValue(float *,float,float);
extern void moby_wander_around_home_point(char *,void *,float,float);
extern float mat_fast_helper_a(float,float);
extern void StepAngleTowardTarget(float *,int,float,float);
extern int flag_set_first_pending(char *);
extern float vec_distance_xy(void *,void *);
extern int math_is_value_within_step(char *,float);
extern void PlayMobySound(int,int,char *);
extern int coll_sweep_from_object(char *,float,void *,int,float,float,int,int,int);
extern void moby_set_controller_speed_limits(char *,float,float,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_move_to_target_temp_limits(char *,void *,int,float,float,float);
extern float math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void add_vectors(void *,void *,void *);
extern float FastAddRotations(float,float);
extern void MobySpringTurn(char *,float,float *,float,float,float);

/* Updates a Grulch (moby class 2952): it wanders, notices the player, walks up, attacks and
   is removed when it dies or falls out of the level. */
void grulch_update(char *object)
{
    float movement[4], position[4];
    char *vars, *other;
    int flags;
    float angle;
    if (D_L17_001CA140[0]) return;
    vars=P(object,0x68);
    if (D_L17_001A8F00==2) {
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
    grulch_init_state_check_hits(object);
    math_fast_float_d((int *)(vars+0x440));
    if (I(vars,0x450)!=-1) {
        other=(char *)((I(vars,0x450)<<8)+(u32)g_moby_l17_pool[0]);
        if (H(other,0xAA)==0x929 /* moby class 2345 */) platform_set_path_index(other,object);
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
                grulch_activate_group_members(object);
                if(I(vars,0x428)!=-1) {
                    if(!ride_platform_can_start(g_moby_l17_pool[0]+(I(vars,0x428)<<8))) break;
                    ride_platform_start(g_moby_l17_pool[0]+(I(vars,0x428)<<8));
                    { char *entityBase = g_moby_l17_pool[0];
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                    if(H((I(vars,0x428)<<8)+(u32)entityBase,0xAA)==0x929) {
                        moby_set_state(object,8,3);
                        anim_start_immediate(object,9,0);
                        F(object,0xF8)=F((char *)((I(vars,0x428)<<8)+(u32)g_moby_l17_pool[0]),0xF8);
                        I(vars,0x428)=-1;
                    } else {
                        I(vars,0x428)=-1;
                        moby_set_state(object,10,2);
                        if(B(object,0x43)!=2) anim_start_blended(object,2,0,14);
                        goto restoreCollision;
                    }
                    }
                } else {
                    moby_set_state(object,10,2);
                    if(B(object,0x43)!=2) anim_start_blended(object,2,0,14);
restoreCollision:
                    U(object,0x34)&=0xFFBE;
                    I(object,0x98)=I(P(object,0x24),0x10);
                }
            } else if(H(vars,0x406)) {
                moby_set_state(object,2,1);
                H(vars,0x406)=0;
                I(vars,0x3FC)=FloatToInt(math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                H(vars,0x400)=0;
            }
        }
        break;
    case 1:
        if(H(vars,0x404)==1 && I(vars,0x440)==0) {
            grulch_activate_group_members(object);
            moby_set_state(object,10,2);
            if(B(object,0x43)!=2) anim_start_blended(object,2,0,14);
        } else if(I(vars,0x3FC)==0) {
            moby_set_state(object,1,0);
            if(B(object,0x43)!=0) anim_start_blended(object,0,0,12);
        }
        break;
    case 2:
        if(H(vars,0x404)!=1 && math_random_int_below(19)==0) {
            moby_set_state(object,2,1);
            I(vars,0x3FC)=FloatToInt(math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
            H(vars,0x400)=0;
        }
        break;
    case 3:
        if(flag_set_second_pending(object) && F(object,0x48)<0.0f) F(object,0x48)=1.0f;
        if(B(object,0x20)!=8) {
            flags=moby_dispatch_action_by_kind(object,vars+0x60);
            if(flags&1) {
                H(vars,0x98)=0;
                SetDeathBits(object,0,3);
                part_queue_moby_for_glow(object,0,0);
                return;
            }
            if(flags&2) {
                if(H(vars,0x404)==1 && I(vars,0x440)==0) {
                    grulch_activate_group_members(object);
                    moby_set_state(object,4,2);
                    if(B(object,0x43)!=9) anim_start_blended(object,9,0,14);
                } else {
                    moby_set_state(object,2,1);
                    I(vars,0x3FC)=FloatToInt(math_random_float_range(F(vars,0x3F8)*0.8f,F(vars,0x3F8)*1.2f)*60.0f);
                    H(vars,0x400)=math_random_int_range(120,700);
                }
            }
        }
        break;
    }
    if(F(object,0x18)-F(vars,0x3D8)>10.0f || F(object,0x18)<10.0f) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits(object,0,3);
        moby_mark_spawned(object);
        return;
    }
    if(F(object,0x18)<75.0f && g_current_map_index==11) {
        H(vars,0x98)=0;
        qzero(object+0xF0);
        SetDeathBits(object,0,3);
        moby_mark_spawned(object);
        return;
    }
    switch(B(object,0x20)) {
    case 1:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)==0 && H(vars,0x400)!=0) {
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,14);
        }
        if(H(vars,0x400)>20) ApproachValue((float *)(vars+0x124),D_L17_001B0CB0*(1.0f/60.0f),0.0019444445f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            F(object,0x48)=0.8f;
            if(H(vars,0x400)==0) {
                if(B(object,0x43)!=math_random_int_below(2)) anim_start_blended(object,math_random_int_below(2),0,12);
            }
            moby_wander_around_home_point(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==0 || B(object,0x43)==1) && (B(object,0x60)&2)) {
            H(vars,0x400)=math_random_int_range(120,500);
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,12);
        }
        break;
    case 2:
        FastDecTimer((short *)(vars+0x400));
        if(B(object,0x43)!=9 && B(object,0x43)!=5 && B(object,0x43)!=4) {
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,14);
        }
        if(H(vars,0x400)>20) ApproachValue((float *)(vars+0x124),D_L17_001B0CB4*(1.0f/60.0f),0.0019444445f);
        else ApproachValue((float *)(vars+0x124),0.0f,0.0019444445f);
        if(B(object,0x43)==9) {
            if(H(vars,0x400)==0) {
                anim_start_blended(object,5,0,12);
                if(math_random_int_below(2)==1 && B(object,0x43)!=4) anim_start_blended(object,4,0,12);
            }
            moby_wander_around_home_point(object,vars+0x110,0.35f,0.25f);
        } else if((B(object,0x43)==4 || B(object,0x43)==5) && (B(object,0x60)&2)) {
            H(vars,0x400)=math_random_int_range(120,200);
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,12);
        }
        goto restoreAnimationSpeed;
    case 10:
        if(B(object,0x60)&2) {
            moby_set_state(object,4,-1);
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,14);
        }
        StepAngleTowardTarget((float *)(object+0xF8),0,mat_fast_helper_a(g_hero_state.x-F(object,0x10),g_hero_state.y-F(object,0x14)),0.10471977f);
        break;
    case 4:
        if(flag_set_first_pending(object)) I(vars,0x418)=math_random_int_range(80,100);
        F(object,0x48)=1.0f;
        if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)<=D_L17_001B0CAC) {
            moby_set_state(object,5,2);
            if(B(object,0x43)!=6) anim_start_blended(object,6,2,6);
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
            I(vars,0x418)=math_random_int_range(150,200);
            moby_set_state(object,5,2);
            if(B(object,0x43)!=6) anim_start_blended(object,6,2,6);
        }
        break;
    case 5:
        if(B(object,0x42)==6) {
            if(math_is_value_within_step(object,8.0f)) PlayMobySound(3,0,object);
            if(B(object,0x42)==6) {
                if(math_is_value_within_step(object,10.0f)) {
                    if(coll_sweep_from_object(object,1.0f,object+0x10,0x4000001,F(vars,0x430),1.0f,0,1,0)>0) I(vars,0x448)=1;
                    else I(vars,0x448)=0;
                } else if(B(object,0x42)==6 && ((B(object,0x60)&2) || math_is_value_within_step(object,11.0f))) {
                    if(vec_distance_xy(object+0x10,P(vars,0x408)+0x10)>D_L17_001B0CAC) {
                        if((vec_distance_xy(object+0x10,P(vars,0x408)+0x10)==0.0f ? 1.0f : 0.0f)>D_L17_001B0CAC) {
                            if(math_random_int_range(0,7)>0) {
                                moby_set_state(object,11,2);
                                if(B(object,0x43)!=7) anim_start_blended(object,7,0,14);
                            }
                        } else {
                            moby_set_state(object,6,2);
                            if(B(object,0x43)!=9) anim_start_blended(object,9,0,14);
                        }
                    }
                }
            }
        }
        break;
    case 11:
        if(B(object,0x60)&2) {
            moby_set_state(object,4,2);
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,0);
        }
        break;
    case 6:
        moby_set_controller_speed_limits(object,0.005f,0.10000001f,0.017453294f,1.0471977f);
        if(flag_set_first_pending(object)) {
            FastVecSub(vars+0x3E0,object+0x10,P(vars,0x408)+0x10);
            F(vars,0x3E8)=0;
            vec_scale_to_length(vars+0x3E0,vars+0x3E0,10.0f);
            FastVecAdd(vars+0x3E0,vars+0x3E0,object+0x10);
            F(object,0x48)=-1.0f;
        }
        moby_move_to_target_temp_limits(object,vars+0x3E0,16,mat_fast_helper_a(F(vars,0x3E0)-F(object,0x10),F(vars,0x3E4)-F(object,0x14)),-1.0f,-1.0f);
        if(B(object,0x42)==2 && (B(object,0x60)&2)) {
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,10);
            F(object,0x48)=1.0f;
        }
        if(B(object,0x42)==9 && (B(object,0x60)&2)) {
            if(I(vars,0x448)==0) {
                moby_set_state(object,4,2);
                if(B(object,0x43)!=9) anim_start_blended(object,9,0,6);
            } else {
                moby_set_state(object,11,2);
                if(B(object,0x43)!=7) anim_start_blended(object,7,0,14);
                I(vars,0x448)=0;
            }
restoreAnimationSpeed:
            F(object,0x48)=1.0f;
        }
        break;
    case 8:
        movement[0]=math_fast_sin_or_cos_a(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[1]=math_fast_sin_or_cos_b(F(object,0xF8))*(1.0f/60.0f)*(F(vars,0x40C)+F(vars,0x40C));
        movement[2]=0;
        add_vectors(position,object+0x10,movement);
        if(vec_distance_xy(object+0x10,vars+0x3D0)>6.0f) moby_set_state(object,4,2);
        break;
    case 3:
        angle=FastAddRotations(mat_fast_helper_a(F(P(vars,0x408),0x10)-F(object,0x10),F(P(vars,0x408),0x14)-F(object,0x14)),F(vars,0x414));
        MobySpringTurn(object,angle,(float *)(vars+0x410),0.05f,0.3f,0.10471977f);
        if(B(object,0x60)&2) {
            moby_set_state(object,4,-1);
            if(B(object,0x43)!=9) anim_start_blended(object,9,0,15);
        }
        break;
    case 9:
        if(grulch_update_pulled_in(object)) {
            SetDeathBits(object,0,3);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if(B(object,0x20)!=8 && B(object,0x20)!=9 && B(object,0x20)!=6) grulch_turn_and_fall(object);
    grulch_update_animation(object);
}
