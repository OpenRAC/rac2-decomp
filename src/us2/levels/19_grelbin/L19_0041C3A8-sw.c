#include "include_asm.h"

#include "common.h"
extern int D_0018C0B4 NOT_SDA;
extern int g_active_yeti_count __attribute__((sda));
extern int g_max_active_yetis __attribute__((sda));
extern char *g_moby_l19_array __attribute__((sda));
extern void *D_L19_001FB5A0[];
extern int moby_is_in_selected_zone(void *);
extern int yeti_init_stats(void *);
extern void moby_mark_spawned(void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern int math_fast_float_d(void *);
extern int math_random_int_range(int,int);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void func_US2_002A7AA8(void *,int,int);
extern void part_queue_moby_for_glow(void *,int,void *);
extern int math_random_int_below(int);
extern float math_random_float_range(float,float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int moby_l01_turn_toward_target(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int func_US2_002AF9C8(void *,float);
extern float FastDiffRots(float,float);
extern int moby_turn_toward_target_and_step(void *,void *,float);
extern float moby_get_anim_value(void *);
extern int coll_test_hit_at_bone(float,float,float,void *,int,int,int,int,int);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_move_to_target_temp_limits(void *,void *,int,float,float,float);
extern void moby_update_timers_attachment(void *);
#define I(p,n) (*(int *)((p)+(n)))
#define F(p,n) (*(float *)((p)+(n)))
#define B(p,n) (*(u8 *)((p)+(n)))
typedef struct { char pad[0x34]; u16 flags; } GrelbinObjectFlags;
#define H(p) (((GrelbinObjectFlags *)(p))->flags)
#define ANIM(n,a,t) if(B(obj,0x43)!=(n)) func_002A7470(obj,n,a,t)
#define SOLID() H(obj)=(H(obj)&0xFFBE)|0x1000; I(obj,0x98)=I(*(char **)(obj+0x24),0x10)
#define HIDE() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); H(obj)|=0x1000; }
#define PICK_FLEE_TARGET() { \
    qcopy(data+0x290,data+0x210); \
    distance=func_002A7878(6.0f,8.0f); \
    angle=func_002A7940(); \
    func_002AF000(vec,distance,angle,0.0f); \
    func_00282CC0(data+0x290,data+0x290,vec); \
    { int timer=func_002A7820(580,600); int active=D_L19_001B1D20; \
      I(data,0x230)=timer; D_L19_001B1D20=active-1; } }
#define DISABLE_COLLISION() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); SOLID(); }

void func_US2_L19_0041C3A8(char *obj)
{
    char *data;
    char *entity;
    float vec[4] __attribute__((aligned(16)));
    float distance, angle;
    int mode, result;
    if (!moby_is_in_selected_zone(obj+0x10) || D_0018C0B4==111) return;
    data=*(char **)(obj+0x68);
    if (yeti_init_stats(obj)) { moby_mark_spawned(obj); return; }
    if(B(obj,0x20)==1) H(obj)&=0xEFFF;
    mode=B(obj,0x95);
    switch(mode) {
    case 0:
        if(I(data,0x278)==1 && I(data,0x26C)==0 && g_active_yeti_count<g_max_active_yetis) {
            if(I(data,0x264)==-1) {
                if(I(data,0x250)==255 || !D_L19_001FB5A0[I(data,0x250)]) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,10); g_active_yeti_count++;
                } else if(!moby_count_group_not_in_state(I(data,0x250),-1)) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,10); g_active_yeti_count++;
                }
            } else {
                entity=g_moby_l19_array+(I(data,0x264)<<8);
                if(!entity || B(entity,0x20)==254 || B(entity,0x20)==253) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,10); g_active_yeti_count++;
                }
            }
        } else if(I(data,0x240) && math_fast_float_d(data+0x238)) {
            I(data,0x240)=0;
            if(I(data,0x230)<300) I(data,0x230)=math_random_int_range(480,600);
        }
        break;
    case 1:
        if ((I(data,0x278)==1 || I(data,0x27C)==1) && g_active_yeti_count<g_max_active_yetis) {
            ANIM(3,0,10); moby_set_state(obj,14,2); g_active_yeti_count++;
        }
        break;
    case 2:
        if(flag_set_second_pending(obj)) {
            DISABLE_COLLISION();
        }
        if(I(data,0x278)!=1 && I(data,0x27C)!=1 && B(obj,0x20)!=15 && B(obj,0x20)!=16) {
            moby_set_state(obj,7,1); ANIM(7,0,10);
            if(!math_random_int_below(3)) { ANIM(6,0,10); }
            else if(math_random_int_below(2)) {
                ANIM(13,0,10);
            }
            PICK_FLEE_TARGET();
        } else { DISABLE_COLLISION(); }
        break;
    case 3:
        result=moby_dispatch_action_by_kind(obj,data+0x140);
        if(result&1) {
            func_US2_002A7AA8(obj,0,3); part_queue_moby_for_glow(obj,0,0); g_active_yeti_count--;
        } else if(result&2) {
            if(I(data,0x204)==1 && g_active_yeti_count<=g_max_active_yetis) {
                ANIM(3,0,10); moby_set_state(obj,14,2);
            } else {
                moby_set_state(obj,8,1);
                ANIM(2,0,10);
                PICK_FLEE_TARGET();
            }
        }
        break;
    }
    switch(B(obj,0x20)) {
    case 1:
    case 2:
        break;
    case 7:
        if(B(obj,0x60)&2) {moby_set_state(obj,8,-1); ANIM(2,0,13);}
        break;
    case 8:
        if(flag_set_first_pending(obj)) moby_set_controller_speed_limits(obj,0.0016666667f,0.050000004f,0.0069813179f,0.8377582f);
        moby_l01_turn_toward_target(obj,data+0x290);
        if(vec_distance_xy(obj+0x10,data+0x290)<0.5f) {moby_set_state(obj,3,-1); ANIM(1,0,10);}
        break;
    case 3:
        if(B(obj,0x60)&2) {
            ANIM(12,0,10);moby_set_state(obj,1,0);
            B(obj,0x31)=0; I(obj,0x98)=0;H(obj)=(H(obj)|1)&0xEFFF;
        }
        break;
    case 10:
        entity=*(char **)(data+0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(func_US2_002AF9C8(obj,23.0f)) {
            ANIM(7,1,2);
            if(math_random_int_below(2)) {ANIM(6,0,2);}
            moby_set_state(obj,11,-1);
            if(I(data,0x274) || !math_random_int_below(2)) { ANIM(3,0,6);moby_set_state(obj,14,-1); }
        }
        break;
    case 11:
        entity=*(char **)(data+0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(B(obj,0x60)&2) { ANIM(3,0,10);moby_set_state(obj,14,-1); }
        break;
    case 14:
        if(flag_set_first_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0033333334f,0.10000001f,0.0069813179f,0.8377582f); SOLID();
        }
        if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<7.0f && vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)>4.0f &&
            FastDiffRots(F(obj,0xF8),mat_fast_helper_a(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            moby_set_controller_speed_limits(obj,0.02f,0.6f,0.0069813179f,0.8377582f);ANIM(4,0,10);moby_set_state(obj,15,-1);
        } else if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<=3.0f &&
            FastDiffRots(F(obj,0xF8),mat_fast_helper_a(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            ANIM(10,0,10);moby_set_state(obj,16,-1);
        } else moby_turn_toward_target_and_step(obj,data+0x1F0,F(data,0x270));
        break;
    case 15: {
        float attackDistance;
        if(flag_set_first_pending(obj)) { SOLID(); }
        attackDistance=moby_get_anim_value(obj);
        if(attackDistance>4.0f && attackDistance<15.0f) moby_l01_turn_toward_target(obj,data+0x1F0);
        if(func_US2_002AF9C8(obj,30.0f)) {
            ANIM(7,0,10);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,10);} else if(math_random_int_below(2)) {ANIM(13,41,10);}
            if(math_random_int_below(5)) { ANIM(5,0,10);moby_set_state(obj,17,-1); }
        }
        if(attackDistance<19.0f) {
            coll_test_hit_at_bone(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    }
    case 16:
        if(flag_set_first_pending(obj)) {SOLID();}
        if(func_US2_002AF9C8(obj,25.0f)) {
            ANIM(7,0,10);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,10);} else if(math_random_int_below(2)) {ANIM(13,41,10);}
            if(math_random_int_below(3)) {ANIM(5,0,10);moby_set_state(obj,17,-1);}
        }
        if(moby_get_anim_value(obj)<14.0f) {
            coll_test_hit_at_bone(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    case 17: {
        char *target;
        if(flag_set_first_pending(obj)) {
            vec[0]=math_fast_sin_or_cos_a(FastAddRotations(F(obj,0xF8),3.141593f))*18.0f;
            vec[1]=math_fast_sin_or_cos_b(FastAddRotations(F(obj,0xF8),3.141593f))*18.0f;
            vec[2]=0.0f;
            FastVecAdd(data+0x280,vec,obj+0x10);
            moby_set_controller_speed_limits(obj,0.023333333f,0.8000001f,0.0069813179f,0.8377582f);
        }
        { float range=moby_get_anim_value(obj);
        if(range>4.0f && range<14.0f) {
            target=data+0x280;
            { float dx=F(data,0x280)-F(obj,0x10); float dy=F(data,0x284)-F(obj,0x14);
            angle=mat_fast_helper_a(dx,dy); }
            moby_move_to_target_temp_limits(obj,target,16,angle,-1.0f,-1.0f);
        }}
        if(func_US2_002AF9C8(obj,21.0f)) {
            ANIM(7,0,10);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,10);} else if(math_random_int_below(2)) {ANIM(13,41,10);}
        }
        break;
    }
    case 24:
        if(B(obj,0x60)&2) {ANIM(3,0,10);moby_set_state(obj,14,-1);}
        break;
    }
    moby_update_timers_attachment(obj);
}
