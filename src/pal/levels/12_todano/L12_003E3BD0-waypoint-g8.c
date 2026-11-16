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
extern void func_PAL_L12_003E4728(void *);
extern void func_PAL_L12_003E4A20(void *);
extern s32 moby_dispatch_action_by_kind(void *,void *);
extern int func_PAL_00289730(s32,s32);
extern void moby_set_state(void *,s32,s32);
extern void func_PAL_002A7E68(void *,s32,s32,s32);
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
void func_PAL_L12_003E3BD0(u8 *o) {
    u8 *s=*(u8 **)(o+0x68);
    f32 v[4] __attribute__((aligned(16)));
    f32 angle,angle2,speed,yaw,pitch;
    PathTarget *target;
    s32 hit;
    func_PAL_L12_003E4728(o);
    if (o[0x95]==1) goto states;
    if (o[0x95]==3) {
        hit=moby_dispatch_action_by_kind(o,s+0x60);
        if (hit&1) {
            g_tourist_hit_count++;
            if (g_tourist_hit_count==50) func_PAL_00289730(0xA2D,0x84);
            else if (g_tourist_hit_count==100) func_PAL_00289730(0xA2E,0x85);
            else if (g_tourist_hit_count==150) func_PAL_00289730(0xA2F,0x86);
            else if (g_tourist_hit_count==200) func_PAL_00289730(0xA30,0x87);
            moby_set_state(o,1,0);
            ANIM(o,4,17);
            g_tourist_wait_counter++;
            part_spawn_explosion_with_sparks_pal(o,o+0x10,-1,1.0f,0.0f);
            SetDeathBits_pal(o,0,3);
            H(s,0x98)=0;
            F(s,0x20)=H(s,0x24);
            REST(o);
        } else if (hit&2) moby_set_state(o,4,1);
    }
states:
    switch(o[0x20]) {
    case 2:
        g_tourist_wait_counter=0;
        I(s,0x7B8)=0;
        FastVecSub(v,s+0x740,o+0x10);
        speed=0.120000005f;
        if (FastVecLength(v)>speed) { vec_scale_to_length(v,v,speed); goto add; }
        moby_set_state(o,3,-1);
        ANIM(o,4,17);
        goto add;
    case 3: {
        WaypointPath *path=(WaypointPath *)(s+0x518);
        matrix_mul_vec3(v,s+0x770,&g_path_waypoint_table[path->points[I(s,0x794)]]);
        FastVecAdd(v,v,g_path_waypoint_table[path->points[I(s,0x794)]].position);
        ComputeRegionRouteHeading(o+0x10,v,&angle,s+0x110,I(s,0x790),0.0f,F(s,0x7A4),s+0x79C,s+0x7A0);
        if (I(s,0x540) && I(s,0x540)==I(s,0x794)-1) {
            speed=0.060000002f;
            if (!I(s,0x7B8)) {
                I(s,0x7B8)=squirrel_alert_for_object_pal(I(s,0x544),o);
                if (I(s,0x7B8)) { moby_set_state(o,7,2); ANIM(o,5,8); }
            }
        } else speed=F(s,0x7AC);
        if (!math_fast_float_d(s+0x7B0)) angle=FastAddRotations(angle,F(s,0x7B4));
        if (!I(s,0x7B0) && I(s,0x5D0)>50) {
            I(s,0x7B0)=50;
            F(s,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (moby_move_to_target_temp_limits_pal(o,v,1,angle,speed,-1.0f)&0x80) {
            moby_set_state(o,4,-1);
            ANIM(o,1,17);
            if (I(s,0x540) && I(s,0x540)==I(s,0x794)) I(s,0x7A8)=((s32)(math_random_int_range(80,180)) * 5 + 2) / 6;
            else I(s,0x7A8)=((s32)(math_random_int_range(10,160)) * 5 + 2) / 6;
        }
        if (F(o,0x18)<50.0f) moby_set_state(o,1,0);
        if (I(s,0x5D0)>167) {
            moby_set_state(o,1,0);
            ANIM(o,4,17);
            part_spawn_explosion_with_sparks_pal(o,o+0x10,-1,1.0f,0.0f);
            SetDeathBits_pal(o,0,3);
            F(s,0x20)=H(s,0x24);
            REST(o);
        } else if (F(s,0x7A4)>=0.5f && F(s,0x61C)<4.0f) F(s,0x7A4)=0.4f;
        if (I(s,0x794)!=I(s,0x798) && I(s,0x7A8)>17) I(s,0x7A8)=17;
        break;
    }
    case 5:
        ComputeRegionRouteHeading(o+0x10,s+0x740,&angle2,s+0x110,I(s,0x790),0.0f,F(s,0x7A4),s+0x79C,s+0x7A0);
        if (!math_fast_float_d(s+0x7B0)) angle2=FastAddRotations(angle2,F(s,0x7B4));
        moby_move_to_target_temp_limits_pal(o,s+0x740,1,angle2,F(s,0x7AC),-1.0f);
        if (F(o,0x18)<50.0f) moby_set_state(o,1,0);
        if (!I(s,0x7B0) && I(s,0x5D0)>50) {
            I(s,0x7B0)=50;
            F(s,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (IsPointInCuboid(o+0x10,I(s,0x54C))) { moby_set_state(o,6,-1); ANIM(o,3,17); }
        break;
    case 4: {
        if (I(s,0x794)!=I(s,0x798) && math_fast_float_d(s+0x7A8)) {
            if (I(s,0x798)>=6) {
                if (!g_tourist_wait_counter && !g_item_enabled_flags[10]) {
                    g_item_enabled_flags[10]=1;
                    snd_play_from_global_bank(1,0,0);
                    value_set_entry_by_index_pal(0x1233,-1);
                    g_tourist_active_flag=1;
                }
                gate_compute_sight_points((PathTarget *)(g_moby_list_start+(I(s,0x514)<<8)),s+0x740,s+0x750);
                moby_set_state(o,5,-1);
                ANIM(o,4,17);
            } else {
                I(s,0x794)=I(s,0x798);
                moby_set_state(o,3,-1);
                ANIM(o,4,17);
                F(s,0x7A4)=math_random_float_range(0.5f,0.7f);
            }
            break;
        }
        if (U(o,0x96)<2 || math_fast_float_d(s+0x7BC)) {
            if ((u32)(I(s,0x794)-1)<4 && (U(o,0x96)<2 || math_random_int_below(2))) {
                qcopy(s+0x780,g_path_waypoint_table[I(s+((u32)(I(s,0x794)-1)<<2),0x530)].position);
            } else {
                target=(PathTarget *)((I(s,0x548)<<8)+g_moby_list_start);
                if ((target->flags^1)&1) { qcopy(s+0x780,target->position); F(s,0x788)+=0.5f; }
                else {
                    f32 randomYaw=math_random_angle();
                    F(s,0x780)=math_fast_sin_or_cos_a(randomYaw);
                    F(s,0x784)=math_fast_sin_or_cos_b(randomYaw);
                    I(s,0x788)=0;
                    F(s,0x788)+=math_random_float_range(F(s,0x788),0.5f);
                    FastVecAdd(s+0x780,s+0x780,o+0x10);
                }
            }
            I(s,0x7BC)=((s32)(math_random_int_range(60,120)) * 5 + 2) / 6;
        }
        FastVecSub(v,s+0x780,o+0x10);
        yaw=mat_fast_helper_a(v[0],v[1]);
        pitch=-mat_fast_helper_a(vec_length_xy(v),v[2]);
        moby_step_at_own_position_factor_pal(o,yaw);
        F(s,0x6A4)=F(s,0x724)=pitch*0.5f;
        break;
    }
    case 8:
        if (U(o,0x96)>=5) {
            REST(o);
            part_spawn_explosion_with_sparks_pal(o,o+0x10,-1,1.0f,0.0f);
            moby_set_state(o,1,0);
        }
    case 6:
        FastVecSub(v,s+0x750,o+0x10);
        speed=0.120000005f;
        if (FastVecLength(v)>speed) {
            vec_scale_to_length(v,v,speed);
        } else {
            moby_set_state(o,1,0);
            ANIM(o,4,17);
            U(o,0x7C)=1<<math_random_int_below(6);
            REST(o);
        }
add:
        FastVecAdd(o+0x10,o+0x10,v);
        break;
    case 7:
        if (o[0x60]&2) { moby_set_state(o,3,1); ANIM(o,7,8); }
        break;
    case 1:
        REST(o);
        break;
    }
    func_PAL_L12_003E4A20(o);
}
