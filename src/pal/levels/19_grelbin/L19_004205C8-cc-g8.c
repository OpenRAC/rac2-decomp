#include "names.h"
/* func_PAL_L19_004205C8, the PAL copy of func_L19_0041B078: the same C, where rename func_L19_0041BFD0 becomes func_PAL_L19_00421568; rename func_002A7470 becomes func_PAL_002A7E68; rename func_002A6C58 becomes func_PAL_002A7650; rename func_L01_00321178 becomes func_PAL_L01_00323068; rename func_002AEB60 becomes func_PAL_002AF6C0; rename func_002B4FF0 becomes func_PAL_002B5BA8; rename func_L02_00331440 becomes func_PAL_L02_00333638; scale timer; scale func_002A7820(480,600). */
#include "common.h"

extern int g_game_mode NOT_SDA;
extern int g_active_yeti_count __attribute__((sda));
extern int g_max_active_yetis __attribute__((sda));
extern char *g_moby_l19_array __attribute__((sda));
extern void *g_group_ptr_table[];
extern int moby_is_in_selected_zone(void *);
extern int yeti_init_stats_pal(void *);
extern void moby_mark_spawned(void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern int math_fast_float_d(void *);
extern int math_random_int_range(int,int);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void SetDeathBits_pal(void *,int,int);
extern void part_queue_moby_for_glow(void *,int,void *);
extern int math_random_int_below(int);
extern float math_random_float_range(float,float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern int moby_l01_turn_toward_target_pal(void *,void *);
extern float vec_distance_xy(void *,void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int math_is_value_within_step_pal(void *,float);
extern float FastDiffRots(float,float);
extern int moby_turn_toward_target_and_step_pal(void *,void *,float);
extern float moby_get_anim_value(void *);
extern int coll_test_hit_at_bone(float,float,float,void *,int,int,int,int,int);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_move_to_target_temp_limits_pal(void *,void *,int,float,float,float);
extern void moby_update_timers_attachment(void *);

#define I(p,n) (*(int *)((p)+(n)))
#define F(p,n) (*(float *)((p)+(n)))
#define B(p,n) (*(u8 *)((p)+(n)))
typedef struct { char pad[0x34]; u16 flags; } GrelbinObjectFlags;
#define H(p) (((GrelbinObjectFlags *)(p))->flags)
#define ANIM(n,a,t) if(B(obj,0x43)!=(n)) func_PAL_002A7E68(obj,n,a,t)
#define SOLID() H(obj)=(H(obj)&0xFFBE)|0x1000; I(obj,0x98)=I(*(char **)(obj+0x24),0x10)
#define HIDE() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); H(obj)|=0x1000; }
/* Written out in both state 2 and state 3: jump2 cross-jumps the two copies, which is what
 * shares the animation 13 and 2 calls while leaving the animation 6 call alone. */
#define PICK_FLEE_TARGET() { \
    qcopy(data+0x290,data+0x210); \
    distance=func_002A7878(6.0f,8.0f); \
    angle=func_002A7940(); \
    func_002AF000(vec,distance,angle,0.0f); \
    func_00282CC0(data+0x290,data+0x290,vec); \
    { int timer=func_002A7820(580,600); int active=D_L19_001B1D20; \
      I(data,0x230)=(((int)(timer) * 5 + 2) / 6); D_L19_001B1D20=active-1; } }
#define DISABLE_COLLISION() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); SOLID(); }

/* Updates a Y.E.T.I. every frame. It waits in hiding, runs toward the player, and attacks up close or with a leap. It runs away to a new spot when it is hurt. (PAL: 50 Hz timings) */
void yeti_update_pal(char *obj)
{
    char *data;
    char *entity;
    float vec[4] __attribute__((aligned(16)));
    float distance, angle;
    int ai_mode, path_result;
    if (!moby_is_in_selected_zone(obj+0x10) || g_game_mode==111) return;
    data=*(char **)(obj+0x68);
    if (yeti_init_stats_pal(obj)) { moby_mark_spawned(obj); return; }
    if(B(obj,0x20)==1) H(obj)&=0xEFFF;
    ai_mode=B(obj,0x95);
    switch(ai_mode) {
    case 0:
        if(I(data,0x278)==1 && I(data,0x26C)==0 && g_active_yeti_count<g_max_active_yetis) {
            if(I(data,0x264)==-1) {
                if(I(data,0x250)==255 || !g_group_ptr_table[I(data,0x250)]) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,8); g_active_yeti_count++;
                } else if(!moby_count_group_not_in_state(I(data,0x250),-1)) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,8); g_active_yeti_count++;
                }
            } else {
                entity=g_moby_l19_array+(I(data,0x264)<<8);
                if(!entity || B(entity,0x20)==254 || B(entity,0x20)==253) {
                    HIDE(); moby_set_state(obj,10,2); ANIM(0,0,8); g_active_yeti_count++;
                }
            }
        } else if(I(data,0x240) && math_fast_float_d(data+0x238)) {
            I(data,0x240)=0;
            if(I(data,0x230)<250) I(data,0x230)=(((int)(math_random_int_range(480,600)) * 5 + 2) / 6);
        }
        break;
    case 1:
        if ((I(data,0x278)==1 || I(data,0x27C)==1) && g_active_yeti_count<g_max_active_yetis) {
            ANIM(3,0,8); moby_set_state(obj,14,2); g_active_yeti_count++;
        }
        break;
    case 2:
        if(flag_set_second_pending(obj)) {
            DISABLE_COLLISION();
        }
        if(I(data,0x278)!=1 && I(data,0x27C)!=1 && B(obj,0x20)!=15 && B(obj,0x20)!=16) {
            moby_set_state(obj,7,1); ANIM(7,0,8);
            if(!math_random_int_below(3)) { ANIM(6,0,8); }
            else if(math_random_int_below(2)) {
                ANIM(13,0,8);
            }
            PICK_FLEE_TARGET();
        } else { DISABLE_COLLISION(); }
        break;
    case 3:
        path_result=moby_dispatch_action_by_kind(obj,data+0x140);
        if(path_result&1) {
            SetDeathBits_pal(obj,0,3); part_queue_moby_for_glow(obj,0,0); g_active_yeti_count--;
        } else if(path_result&2) {
            if(I(data,0x204)==1 && g_active_yeti_count<=g_max_active_yetis) {
                ANIM(3,0,8); moby_set_state(obj,14,2);
            } else {
                moby_set_state(obj,8,1);
                ANIM(2,0,8);
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
        if(B(obj,0x60)&2) {moby_set_state(obj,8,-1); ANIM(2,0,11);}
        break;
    case 8:
        if(flag_set_first_pending(obj)) moby_set_controller_speed_limits(obj,0.0024f,0.060000002f,0.010053098f,1.0053098f);
        moby_l01_turn_toward_target_pal(obj,data+0x290);
        if(vec_distance_xy(obj+0x10,data+0x290)<0.5f) {moby_set_state(obj,3,-1); ANIM(1,0,8);}
        break;
    case 3:
        if(B(obj,0x60)&2) {
            ANIM(12,0,8);moby_set_state(obj,1,0);
            B(obj,0x31)=0; I(obj,0x98)=0;H(obj)=(H(obj)|1)&0xEFFF;
        }
        break;
    case 10:
        entity=*(char **)(data+0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(math_is_value_within_step_pal(obj,23.0f)) {
            ANIM(7,1,2);
            if(math_random_int_below(2)) {ANIM(6,0,2);}
            moby_set_state(obj,11,-1);
            if(I(data,0x274) || !math_random_int_below(2)) { ANIM(3,0,5);moby_set_state(obj,14,-1); }
        }
        break;
    case 11:
        entity=*(char **)(data+0x200);
        moby_start_effect_from_entry(obj,mat_fast_helper_a(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(B(obj,0x60)&2) { ANIM(3,0,8);moby_set_state(obj,14,-1); }
        break;
    case 14:
        if(flag_set_first_pending(obj)) {
            moby_set_controller_speed_limits(obj,0.0048f,0.120000005f,0.010053098f,1.0053098f); SOLID();
        }
        if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<7.0f && vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)>4.0f &&
            FastDiffRots(F(obj,0xF8),mat_fast_helper_a(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            moby_set_controller_speed_limits(obj,0.028800001f,0.72f,0.010053098f,1.0053098f);ANIM(4,0,8);moby_set_state(obj,15,-1);
        } else if(vec_distance_xy(obj+0x10,*(char **)(data+0x200)+0x10)<=3.0f &&
            FastDiffRots(F(obj,0xF8),mat_fast_helper_a(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            ANIM(10,0,8);moby_set_state(obj,16,-1);
        } else moby_turn_toward_target_and_step_pal(obj,data+0x1F0,F(data,0x270));
        break;
    case 15: {
        float attack_distance;
        if(flag_set_first_pending(obj)) { SOLID(); }
        attack_distance=moby_get_anim_value(obj);
        if(attack_distance>4.0f && attack_distance<15.0f) moby_l01_turn_toward_target_pal(obj,data+0x1F0);
        if(math_is_value_within_step_pal(obj,30.0f)) {
            ANIM(7,0,8);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,8);} else if(math_random_int_below(2)) {ANIM(13,41,8);}
            if(math_random_int_below(5)) { ANIM(5,0,8);moby_set_state(obj,17,-1); }
        }
        if(attack_distance<19.0f) {
            coll_test_hit_at_bone(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    }
    case 16:
        if(flag_set_first_pending(obj)) {SOLID();}
        if(math_is_value_within_step_pal(obj,25.0f)) {
            ANIM(7,0,8);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,8);} else if(math_random_int_below(2)) {ANIM(13,41,8);}
            if(math_random_int_below(3)) {ANIM(5,0,8);moby_set_state(obj,17,-1);}
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
            moby_set_controller_speed_limits(obj,0.033600003f,0.96000004f,0.010053098f,1.0053098f);
        }
        { float range=moby_get_anim_value(obj);
        if(range>4.0f && range<14.0f) {
            target=data+0x280;
            { float dx=F(data,0x280)-F(obj,0x10); float dy=F(data,0x284)-F(obj,0x14);
            angle=mat_fast_helper_a(dx,dy); }
            moby_move_to_target_temp_limits_pal(obj,target,16,angle,-1.0f,-1.0f);
        }}
        if(math_is_value_within_step_pal(obj,21.0f)) {
            ANIM(7,0,8);moby_set_state(obj,24,-1);
            if(math_random_int_below(3)) {ANIM(6,0,8);} else if(math_random_int_below(2)) {ANIM(13,41,8);}
        }
        break;
    }
    case 24:
        if(B(obj,0x60)&2) {ANIM(3,0,8);moby_set_state(obj,14,-1);}
        break;
    }
    moby_update_timers_attachment(obj);
}
