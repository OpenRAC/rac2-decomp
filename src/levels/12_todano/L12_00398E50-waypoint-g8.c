#include "common.h"
typedef struct PathWaypoint { u8 transform[0x30]; f32 position[4]; u8 tail[0x40]; } PathWaypoint;
typedef struct PathTarget { u8 prefix[0x10]; f32 position[4]; u8 mid[0x14]; u16 flags; u8 tail[0xCA]; } PathTarget;
typedef struct WaypointPath { s32 points[10]; } WaypointPath;
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
extern void todano_creature_update(void *);
extern void joint_pair_advance_counter(void *);
extern s32 moby_dispatch_action_by_kind(void *,void *);
extern int subtitle_request_voice_line(s32,s32);
extern void moby_set_state(void *,s32,s32);
extern void anim_start_blended(void *,s32,s32,s32);
extern void part_spawn_explosion_with_sparks(void *,void *,s32,f32,f32);
extern void SetDeathBits(void *,s32,s32);
extern void FastVecSub(void *,void *,void *);
extern f32 FastVecLength(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern int ComputeRegionRouteHeading(void *,void *,void *,void *,s32,f32,f32,void *,void *);
extern u8 *squirrel_alert_for_object(s32,void *);
extern s32 math_fast_float_d(void *);
extern f32 FastAddRotations(f32,f32);
extern f32 math_random_signed_float_range(f32,f32);
extern s32 moby_move_to_target_temp_limits(void *,void *,s32,f32,f32,f32);
extern s32 math_random_int_range(s32,s32);
extern s32 IsPointInCuboid(void *,s32);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index(s32,s32);
extern int gate_compute_sight_points(void *,void *,void *);
extern f32 math_random_float_range(f32,f32);
extern s32 math_random_int_below(s32);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 mat_fast_helper_a(f32,f32);
extern f32 vec_length_xy(void *);
extern int moby_step_at_own_position_factor(void *,f32);
extern void vec_scale_to_length(void *,void *,f32);
extern s32 D_L12_001B09F0 __attribute__((sda));
extern s32 D_L12_001B09F4 __attribute__((sda));
extern PathWaypoint *D_L12_001B2F8C MACRO_ADDR;
extern s32 D_L12_001B2E9C MACRO_ADDR;
/* Per-entry flag table; other code indexes it too. An element access keeps the
 * store two words long, so it stays out of the call's delay slot, as in retail. */
extern u8 D_001A7A60[] MACRO_ADDR;
extern s32 D_L12_001A903C;
#define ANIM(o,n,t) { if ((o)[0x43]!=(n)) func_002A7470(o,n,0,t); }
#define REST(o) { I(o,0x98)=0; U(o,0x34)=(U(o,0x34)|0x41)&0xEFFF; }
/* Space Tourist (moby class 3000) update. Waypoint-following state machine for a level 12 object: walks a path of 0x80-byte
 * waypoints, looks at targets, and counts hits in D_L12_001B09F0 (50/100/150/200). */
void space_l12_tourist_update(u8 *creature) {
    u8 *vars=*(u8 **)(creature+0x68);
    f32 step[4] __attribute__((aligned(16)));
    f32 angle,angle2,speed,yaw,pitch;
    PathTarget *target;
    s32 hit;
    todano_creature_update(creature);
    if (creature[0x95]==1) goto states;
    if (creature[0x95]==3) {
        hit=moby_dispatch_action_by_kind(creature,vars+0x60);
        if (hit&1) {
            D_L12_001B09F0++;
            if (D_L12_001B09F0==50) subtitle_request_voice_line(0xA2D,0x84);
            else if (D_L12_001B09F0==100) subtitle_request_voice_line(0xA2E,0x85);
            else if (D_L12_001B09F0==150) subtitle_request_voice_line(0xA2F,0x86);
            else if (D_L12_001B09F0==200) subtitle_request_voice_line(0xA30,0x87);
            moby_set_state(creature,1,0);
            ANIM(creature,4,20);
            D_L12_001B09F4++;
            part_spawn_explosion_with_sparks(creature,creature+0x10,-1,1.0f,0.0f);
            SetDeathBits(creature,0,3);
            H(vars,0x98)=0;
            F(vars,0x20)=H(vars,0x24);
            REST(creature);
        } else if (hit&2) moby_set_state(creature,4,1);
    }
states:
    switch(creature[0x20]) {
    case 2:
        D_L12_001B09F4=0;
        I(vars,0x7B8)=0;
        FastVecSub(step,vars+0x740,creature+0x10);
        speed=0.10000000894069672f;
        if (FastVecLength(step)>speed) { vec_scale_to_length(step,step,speed); goto add; }
        moby_set_state(creature,3,-1);
        ANIM(creature,4,20);
        goto add;
    case 3: {
        WaypointPath *path=(WaypointPath *)(vars+0x518);
        matrix_mul_vec3(step,vars+0x770,&D_L12_001B2F8C[path->points[I(vars,0x794)]]);
        FastVecAdd(step,step,D_L12_001B2F8C[path->points[I(vars,0x794)]].position);
        ComputeRegionRouteHeading(creature+0x10,step,&angle,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)-1) {
            speed=0.05000000447034836f;
            if (!I(vars,0x7B8)) {
                I(vars,0x7B8)=squirrel_alert_for_object(I(vars,0x544),creature);
                if (I(vars,0x7B8)) { moby_set_state(creature,7,2); ANIM(creature,5,10); }
            }
        } else speed=F(vars,0x7AC);
        if (!math_fast_float_d(vars+0x7B0)) angle=FastAddRotations(angle,F(vars,0x7B4));
        if (!I(vars,0x7B0) && I(vars,0x5D0)>60) {
            I(vars,0x7B0)=60;
            F(vars,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (moby_move_to_target_temp_limits(creature,step,1,angle,speed,-1.0f)&0x80) {
            moby_set_state(creature,4,-1);
            ANIM(creature,1,20);
            if (I(vars,0x540) && I(vars,0x540)==I(vars,0x794)) I(vars,0x7A8)=math_random_int_range(80,180);
            else I(vars,0x7A8)=math_random_int_range(10,160);
        }
        if (F(creature,0x18)<50.0f) moby_set_state(creature,1,0);
        if (I(vars,0x5D0)>200) {
            moby_set_state(creature,1,0);
            ANIM(creature,4,20);
            part_spawn_explosion_with_sparks(creature,creature+0x10,-1,1.0f,0.0f);
            SetDeathBits(creature,0,3);
            F(vars,0x20)=H(vars,0x24);
            REST(creature);
        } else if (F(vars,0x7A4)>=0.5f && F(vars,0x61C)<4.0f) F(vars,0x7A4)=0.4f;
        if (I(vars,0x794)!=I(vars,0x798) && I(vars,0x7A8)>20) I(vars,0x7A8)=20;
        break;
    }
    case 5:
        ComputeRegionRouteHeading(creature+0x10,vars+0x740,&angle2,vars+0x110,I(vars,0x790),0.0f,F(vars,0x7A4),vars+0x79C,vars+0x7A0);
        if (!math_fast_float_d(vars+0x7B0)) angle2=FastAddRotations(angle2,F(vars,0x7B4));
        moby_move_to_target_temp_limits(creature,vars+0x740,1,angle2,F(vars,0x7AC),-1.0f);
        if (F(creature,0x18)<50.0f) moby_set_state(creature,1,0);
        if (!I(vars,0x7B0) && I(vars,0x5D0)>60) {
            I(vars,0x7B0)=60;
            F(vars,0x7B4)=math_random_signed_float_range(90.0f,135.0f)*0.01745329424738884f;
        }
        if (IsPointInCuboid(creature+0x10,I(vars,0x54C))) { moby_set_state(creature,6,-1); ANIM(creature,3,20); }
        break;
    case 4: {
        if (I(vars,0x794)!=I(vars,0x798) && math_fast_float_d(vars+0x7A8)) {
            if (I(vars,0x798)>=6) {
                if (!D_L12_001B09F4 && !D_001A7A60[10]) {
                    D_001A7A60[10]=1;
                    snd_play_from_global_bank(1,0,0);
                    value_set_entry_by_index(0x1233,-1);
                    D_L12_001A903C=1;
                }
                gate_compute_sight_points((PathTarget *)(D_L12_001B2E9C+(I(vars,0x514)<<8)),vars+0x740,vars+0x750);
                moby_set_state(creature,5,-1);
                ANIM(creature,4,20);
            } else {
                I(vars,0x794)=I(vars,0x798);
                moby_set_state(creature,3,-1);
                ANIM(creature,4,20);
                F(vars,0x7A4)=math_random_float_range(0.5f,0.7f);
            }
            break;
        }
        if (U(creature,0x96)<2 || math_fast_float_d(vars+0x7BC)) {
            if ((u32)(I(vars,0x794)-1)<4 && (U(creature,0x96)<2 || math_random_int_below(2))) {
                qcopy(vars+0x780,D_L12_001B2F8C[I(vars+((u32)(I(vars,0x794)-1)<<2),0x530)].position);
            } else {
                target=(PathTarget *)((I(vars,0x548)<<8)+D_L12_001B2E9C);
                if ((target->flags^1)&1) { qcopy(vars+0x780,target->position); F(vars,0x788)+=0.5f; }
                else {
                    f32 randomYaw=math_random_angle();
                    F(vars,0x780)=math_fast_sin_or_cos_a(randomYaw);
                    F(vars,0x784)=math_fast_sin_or_cos_b(randomYaw);
                    I(vars,0x788)=0;
                    F(vars,0x788)+=math_random_float_range(F(vars,0x788),0.5f);
                    FastVecAdd(vars+0x780,vars+0x780,creature+0x10);
                }
            }
            I(vars,0x7BC)=math_random_int_range(60,120);
        }
        FastVecSub(step,vars+0x780,creature+0x10);
        yaw=mat_fast_helper_a(step[0],step[1]);
        pitch=-mat_fast_helper_a(vec_length_xy(step),step[2]);
        moby_step_at_own_position_factor(creature,yaw);
        F(vars,0x6A4)=F(vars,0x724)=pitch*0.5f;
        break;
    }
    case 8:
        if (U(creature,0x96)>=5) {
            REST(creature);
            part_spawn_explosion_with_sparks(creature,creature+0x10,-1,1.0f,0.0f);
            moby_set_state(creature,1,0);
        }
    case 6:
        FastVecSub(step,vars+0x750,creature+0x10);
        speed=0.10000000894069672f;
        if (FastVecLength(step)>speed) {
            vec_scale_to_length(step,step,speed);
        } else {
            moby_set_state(creature,1,0);
            ANIM(creature,4,20);
            U(creature,0x7C)=1<<math_random_int_below(6);
            REST(creature);
        }
add:
        FastVecAdd(creature+0x10,creature+0x10,step);
        break;
    case 7:
        if (creature[0x60]&2) { moby_set_state(creature,3,1); ANIM(creature,7,10); }
        break;
    case 1:
        REST(creature);
        break;
    }
    joint_pair_advance_counter(creature);
}
