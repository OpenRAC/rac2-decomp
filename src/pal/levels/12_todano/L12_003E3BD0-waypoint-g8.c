/* func_PAL_L12_003E3BD0, the PAL copy of func_L12_003DF9A0: the same C, where frame counts and
 * timers shrink by 5/6 (the random ones at run time) and speeds grow by 6/5. */
#include "common.h"
typedef struct PathWaypoint { u8 transform[0x30]; f32 position[4]; u8 tail[0x40]; } PathWaypoint;
typedef struct PathTarget { u8 prefix[0x10]; f32 position[4]; u8 mid[0x14]; u16 flags; u8 tail[0xCA]; } PathTarget;
typedef struct WaypointPath { s32 points[10]; } WaypointPath;
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
extern void todano_creature_update_pal(void *);
extern void joint_pair_advance_counter_pal(void *);
extern s32 moby_dispatch_action_by_kind(void *,void *);
extern int subtitle_request_voice_line_pal(s32,s32);
extern void moby_set_state(void *,s32,s32);
extern void anim_start_blended_pal(void *,s32,s32,s32);
extern void part_spawn_explosion_with_sparks_pal(void *,void *,s32,f32,f32);
extern void SetDeathBits_pal(void *,s32,s32);
extern void FastVecSub(void *,void *,void *);
extern f32 FastVecLength(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern int ComputeRegionRouteHeading(void *,void *,void *,void *,s32,f32,f32,void *,void *);
extern u8 *squirrel_alert_for_object_pal(s32,void *);
extern s32 math_fast_float_d(void *);
extern f32 FastAddRotations(f32,f32);
extern f32 math_random_signed_float_range(f32,f32);
extern s32 moby_move_to_target_temp_limits_pal(void *,void *,s32,f32,f32,f32);
extern s32 math_random_int_range(s32,s32);
extern s32 IsPointInCuboid(void *,s32);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_pal(s32,s32);
extern int gate_compute_sight_points(void *,void *,void *);
extern f32 math_random_float_range(f32,f32);
extern s32 math_random_int_below(s32);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 mat_fast_helper_a(f32,f32);
extern f32 vec_length_xy(void *);
extern int moby_step_at_own_position_factor_pal(void *,f32);
extern void vec_scale_to_length(void *,void *,f32);
extern s32 g_tourist_hit_count __attribute__((sda));
extern s32 g_tourist_wait_counter __attribute__((sda));
extern PathWaypoint *g_path_waypoint_table MACRO_ADDR;
extern s32 g_moby_list_start MACRO_ADDR;
/* Per-entry flag table; other code indexes it too. An element access keeps the
 * store two words long, so it stays out of the call's delay slot, as in retail. */
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern s32 g_tourist_active_flag;
#define ANIM(o,n,t) { if ((o)[0x43]!=(n)) func_PAL_002A7E68(o,n,0,t); }
#define REST(o) { I(o,0x98)=0; U(o,0x34)=(U(o,0x34)|0x41)&0xEFFF; }
/* Waypoint-following state machine for a level 12 object: walks a path of 0x80-byte
 * waypoints, looks at targets, and counts hits in D_L12_001B09F0 (50/100/150/200). */
void space_l12_tourist_update_pal(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    f32 vec[4] __attribute__((aligned(16)));
    f32 angle,angle2,speed,yaw,pitch;
    PathTarget *target;
    s32 hit;
    todano_creature_update_pal(moby);
    if (moby[0x95]==1) goto states;
    if (moby[0x95]==3) {
        hit=moby_dispatch_action_by_kind(moby,vars+0x60);
        if (hit&1) {
            g_tourist_hit_count++;
            if (g_tourist_hit_count==50) subtitle_request_voice_line_pal(0xA2D,0x84);
            else if (g_tourist_hit_count==100) subtitle_request_voice_line_pal(0xA2E,0x85);
            else if (g_tourist_hit_count==150) subtitle_request_voice_line_pal(0xA2F,0x86);
            else if (g_tourist_hit_count==200) subtitle_request_voice_line_pal(0xA30,0x87);
            moby_set_state(moby,1,0);
            ANIM(moby,4,17);
            g_tourist_wait_counter++;
            part_spawn_explosion_with_sparks_pal(moby,moby+0x10,-1,1.0f,0.0f);
            SetDeathBits_pal(moby,0,3);
            H(vars,0x98)=0;
            F(vars,0x20)=H(vars,0x24);
            REST(moby);
        } else if (hit&2) moby_set_state(moby,4,1);
    }
states:
    switch(moby[0x20]) {
    case 2:
        g_tourist_wait_counter=0;
        I(vars,0x7B8)=0;
        FastVecSub(vec,vars+0x740,moby+0x10);
        speed=0.120000005f;
        if (FastVecLength(vec)>speed) { vec_scale_to_length(vec,vec,speed); goto add; }
        moby_set_state(moby,3,-1);
        ANIM(moby,4,17);
        goto add;
    case 3: {
        WaypointPath *path=(WaypointPath *)(vars+0x518);
        matrix_mul_vec3(vec,vars+0x770,&g_path_waypoint_table[path->points[I(vars,0x794)]]);
        FastVecAdd(vec,vec,g_path_waypoint_table[path->points[I(vars,0x794)]].position);
        ComputeRegionRouteHeading(moby+0x10,vec,&angle,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)-1) {
            speed=0.060000002f;
            if (!I(vars,0x7B8)) {
                I(vars,0x7B8)=squirrel_alert_for_object_pal(I(vars,0x544),moby);
                if (I(vars,0x7B8)) { moby_set_state(moby,7,2); ANIM(moby,5,8); }
            }
        } else speed=F(vars,0x7AC);
        if (!math_fast_float_d(vars+0x7B0)) angle=FastAddRotations(angle,F(vars,0x7B4));
        if (!I(vars,0x7B0) && I(vars,0x5D0)>50) {
            I(vars,0x7B0)=50;
            F(vars,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (moby_move_to_target_temp_limits_pal(moby,vec,1,angle,speed,-1.0f)&0x80) {
            moby_set_state(moby,4,-1);
            ANIM(moby,1,17);
            if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)) I(vars,0x7A8)=((s32)(math_random_int_range(80,180)) * 5 + 2) / 6;
            else I(vars,0x7A8)=((s32)(math_random_int_range(10,160)) * 5 + 2) / 6;
        }
        if (F(moby,0x18)<50.0f) moby_set_state(moby,1,0);
        if (I(vars,0x5D0)>167) {
            moby_set_state(moby,1,0);
            ANIM(moby,4,17);
            part_spawn_explosion_with_sparks_pal(moby,moby+0x10,-1,1.0f,0.0f);
            SetDeathBits_pal(moby,0,3);
            F(vars,0x20)=H(vars,0x24);
            REST(moby);
        } else if (F(vars,0x7A4)>=0.5f && F(vars,0x61C)<4.0f) F(vars,0x7A4)=0.4f;
        if (I(vars,0x794)!=I(vars,0x798) && I(vars,0x7A8)>17) I(vars,0x7A8)=17;
        break;
    }
    case 5:
        ComputeRegionRouteHeading(moby+0x10,vars+0x740,&angle2,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (!math_fast_float_d(vars+0x7B0)) angle2=FastAddRotations(angle2,F(vars,0x7B4));
        moby_move_to_target_temp_limits_pal(moby,vars+0x740,1,angle2,F(vars,0x7AC),-1.0f);
        if (F(moby,0x18)<50.0f) moby_set_state(moby,1,0);
        if (!I(vars,0x7B0) && I(vars,0x5D0)>50) {
            I(vars,0x7B0)=50;
            F(vars,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (IsPointInCuboid(moby+0x10,I(vars,0x54C))) { moby_set_state(moby,6,-1); ANIM(moby,3,17); }
        break;
    case 4: {
        if (I(vars,0x794)!=I(vars,0x798) && math_fast_float_d(vars+0x7A8)) {
            if (I(vars,0x798)>=6) {
                if (!g_tourist_wait_counter && !g_item_enabled_flags[10]) {
                    g_item_enabled_flags[10]=1;
                    snd_play_from_global_bank(1,0,0);
                    value_set_entry_by_index_pal(0x1233,-1);
                    g_tourist_active_flag=1;
                }
                gate_compute_sight_points((PathTarget *)(g_moby_list_start+(I(vars,0x514)<<8)),vars+0x740,vars+0x750);
                moby_set_state(moby,5,-1);
                ANIM(moby,4,17);
            } else {
                I(vars,0x794)=I(vars,0x798);
                moby_set_state(moby,3,-1);
                ANIM(moby,4,17);
                F(vars,0x7A4)=math_random_float_range(0.5f,0.7f);
            }
            break;
        }
        if (U(moby,0x96)<2 || math_fast_float_d(vars+0x7BC)) {
            if ((u32)(I(vars,0x794)-1)<4 && (U(moby,0x96)<2 || math_random_int_below(2))) {
                qcopy(vars+0x780,g_path_waypoint_table[I(vars+((u32)(I(vars,0x794)-1)<<2),0x530)].position);
            } else {
                target=(PathTarget *)((I(vars,0x548)<<8)+g_moby_list_start);
                if ((target->flags^1)&1) { qcopy(vars+0x780,target->position); F(vars,0x788)+=0.5f; }
                else {
                    f32 random_yaw=math_random_angle();
                    F(vars,0x780)=math_fast_sin_or_cos_a(random_yaw);
                    F(vars,0x784)=math_fast_sin_or_cos_b(random_yaw);
                    I(vars,0x788)=0;
                    F(vars,0x788)+=math_random_float_range(F(vars,0x788),0.5f);
                    FastVecAdd(vars+0x780,vars+0x780,moby+0x10);
                }
            }
            I(vars,0x7BC)=((s32)(math_random_int_range(60,120)) * 5 + 2) / 6;
        }
        FastVecSub(vec,vars+0x780,moby+0x10);
        yaw=mat_fast_helper_a(vec[0],vec[1]);
        pitch=-mat_fast_helper_a(vec_length_xy(vec),vec[2]);
        moby_step_at_own_position_factor_pal(moby,yaw);
        F(vars,0x6A4)=F(vars,0x724)=pitch*0.5f;
        break;
    }
    case 8:
        if (U(moby,0x96)>=5) {
            REST(moby);
            part_spawn_explosion_with_sparks_pal(moby,moby+0x10,-1,1.0f,0.0f);
            moby_set_state(moby,1,0);
        }
    case 6:
        FastVecSub(vec,vars+0x750,moby+0x10);
        speed=0.120000005f;
        if (FastVecLength(vec)>speed) {
            vec_scale_to_length(vec,vec,speed);
        } else {
            moby_set_state(moby,1,0);
            ANIM(moby,4,17);
            U(moby,0x7C)=1<<math_random_int_below(6);
            REST(moby);
        }
add:
        FastVecAdd(moby+0x10,moby+0x10,vec);
        break;
    case 7:
        if (moby[0x60]&2) { moby_set_state(moby,3,1); ANIM(moby,7,8); }
        break;
    case 1:
        REST(moby);
        break;
    }
    joint_pair_advance_counter_pal(moby);
}
