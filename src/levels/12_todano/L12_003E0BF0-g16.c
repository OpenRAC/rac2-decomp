#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern u8 D_0019B2E8[];
extern float D_L12_001B0A20 __attribute__((sda));
extern float D_L12_001B0A24 __attribute__((sda));
extern float D_L12_001B0A30[4] __attribute__((sda));
typedef struct TodanoPlayerView { u8 pad[0x80]; float position[4]; } TodanoPlayerView;
extern TodanoPlayerView g_hero_state;
extern u8 *g_hero_moby NOT_SDA;
extern void guard_creature_update(u8 *);
extern void joint_slots_reset_advance(u8 *);
extern int flag_set_second_pending(u8 *);
extern void moby_set_state(u8 *,int,int);
extern void anim_start_blended(u8 *,int,int,int);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int moby_dispatch_action_by_kind(u8 *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_queue_impact_effect(u8 *,u8 *,int,void *,void *,float);
extern void SetDeathBits(u8 *,int,int);
extern void part_queue_moby_for_glow(u8 *,int,int);
extern void moby_mark_spawned(u8 *);
extern float math_random_angle(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int moby_l01_turn_toward_target(u8 *,void *);
extern int math_random_int_below(int);
extern float mat_fast_helper_a(float,float);
extern void moby_step_controller(u8 *,void *,float);
extern void squirrel_alert_group(u8 *);
extern void StepAngleTowardTarget(void *,int,float,float);
extern float moby_get_anim_value(u8 *);
extern void coll_test_hit_at_bone(u8 *,int,int,int,int,int,float,float,float);
extern void moby_step_at_own_position(u8 *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void sub_object_start_move(void *,void *,void *,int);
/* Updates a Mutant Test-Squirrel. It idles and wanders, walks to an object, picks it up and
   throws it. */
void mutant_squirrel_update(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    float temp[4] __attribute__((aligned(16)));
    float angle, speed;
    guard_creature_update(moby);
    switch(moby[0x95]) {
    case 5: {

        if(flag_set_second_pending(moby)) {
            *(u16 *)(moby+0x34)|=1;
            *(int *)(moby+0x98)=0;
            moby[0x31]=0;

        }
        if(D_0019B2E8[moby[0xB0]+(g_current_map_index<<4)]&0x80) {
            if(*(int *)(vars+0x13C)==-1) {
                moby_set_state(moby,1,0);
                if(moby[0x43]) anim_start_blended(moby,0,0,0);
            } else {
                moby_set_state(moby,9,4);
                if(moby[0x43]!=14) anim_start_blended(moby,14,0,0);
                *(float *)(moby+0x18)+=4.0f;
                *(int *)(moby+0x98)=0;
                *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;
            }
            *(int *)(moby+0x98)=*(int *)(*(u8 **)(moby+0x24)+0x10);
            moby[0x31]=1;
            *(u16 *)(moby+0x34)&=0xFFFE;
        }
        break; }
    case 0:
        if(flag_set_second_pending(moby)) moby_set_controller_speed_limits(moby,0.001111111138f,D_L12_001B0A20*0.0166666675359f,0.0008726647356525064f,0.104719772935f);
        if(*(short *)(vars+0x364)==1) {
            moby_set_state(moby,5,2);
            if(moby[0x43]!=2) anim_start_blended(moby,2,0,10);
        } else if(*(short *)(vars+0x366)) {
            moby_set_state(moby,3,1);
            if(moby[0x43]!=3) anim_start_blended(moby,3,0,20);
            *(short *)(vars+0x366)=0;
            if(*(short *)(vars+0x360)<300) *(short *)(vars+0x360)=math_random_int_range(480,600);
        }
        break;
    case 1:
        if(flag_set_second_pending(moby)) moby_set_controller_speed_limits(moby,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(vars+0x364)==1) {
            moby_set_state(moby,6,2);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,10);
        } else if(!*(short *)(vars+0x360)) {
            moby_set_state(moby,1,0);
            if(moby[0x43]) anim_start_blended(moby,0,0,20);
        }
        break;
    case 2:
        if(flag_set_second_pending(moby)) moby_set_controller_speed_limits(moby,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(vars+0x364)!=1) {
            moby_set_state(moby,3,1);
            if(moby[0x43]!=3) anim_start_blended(moby,3,0,20);
            *(short *)(vars+0x360)=math_random_int_range(580,600);
        }
        break;
    case 3: {
        int hit; u8 *target;
        hit=moby_dispatch_action_by_kind(moby,vars+0x60);
        target=*(u8 **)(vars+0x38);
        if(target && *(short *)(target+0xAA)==0xFAB /* moby class 4011 */) {
            FastVecSub(temp,moby+0x10,target+0x10);
            vec_scale_to_length(temp,temp,1.0f);
            part_queue_impact_effect(moby,g_hero_moby,0x10000,*(u8 **)(vars+0x38)+0x10,temp,50.0f);
        }
        if(hit&1) {
            SetDeathBits(moby,0,3);
            qcopy(temp,moby+0x10);
            temp[2]+=0.25f;
            part_queue_moby_for_glow(moby,0,0);
            moby_mark_spawned(moby);
            return;
        }
        if(hit&2) {
            if(*(short *)(vars+0x364)==1) {
                moby_set_state(moby,6,2);
                if(moby[0x43]!=7) anim_start_blended(moby,7,0,20);
            } else {
                moby_set_state(moby,3,1);
                if(moby[0x43]!=3) anim_start_blended(moby,3,0,20);
                *(short *)(vars+0x360)=math_random_int_range(580,600);
            }
        }
        break; }
    case 4:
        if(flag_set_second_pending(moby)) moby_set_controller_speed_limits(moby,0.004444444552f,D_L12_001B0A24*0.0166666675359f,0.0034906589426100254f,0.20943954587f);
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if(!*(short *)(vars+0x362)) {
            moby_set_state(moby,2,-1);
            angle=math_random_angle();
            speed=math_random_float_range(3.0f,5.0f);
            *(float *)(vars+0x350)=math_fast_sin_or_cos_a(angle)*speed;
            *(float *)(vars+0x354)=math_fast_sin_or_cos_b(angle)*speed;
            *(int *)(vars+0x358)=0;
            FastVecAdd(vars+0x350,vars+0x350,vars+0x340);
            if(moby[0x43]!=15) anim_start_blended(moby,15,0,10);
        }
        moby_step_at_own_position(moby);
        break;
    case 2: {
        int hit;
        hit=moby_l01_turn_toward_target(moby,vars+0x350);
        if((*(u16 *)(moby+0x96)>=31 && (hit&0x80)) || *(u16 *)(moby+0x96)>=601) {
            moby_set_state(moby,1,-1);
            *(short *)(vars+0x362)=math_random_int_range(300,500);
            if(moby[0x43]!=math_random_int_below(2)) anim_start_blended(moby,math_random_int_below(2),0,20);
        }
        break; }
    case 3: moby_step_at_own_position(moby); break;
    case 5: {
        u8 *position=moby+0x10;
        u8 *target=*(u8 **)(vars+0x368);
        int anim_flags;
        angle=mat_fast_helper_a(g_hero_state.position[0]-*(float *)(target+0x10),g_hero_state.position[1]-*(float *)(target+0x14));
        moby_step_controller(moby,position,angle);
        anim_flags=moby[0x60];
        anim_flags&=2;
        if(anim_flags) {
            moby_set_state(moby,6,-1);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,20);
        } else {
            anim_flags=*(u16 *)(moby+0x96);
            if(anim_flags==20) squirrel_alert_group(moby);
        }
        break; }
    case 6:
        if(moby_l01_turn_toward_target(moby,*(u8 **)(vars+0x368)+0x10)&0x80) {
            moby_set_state(moby,7,-1);
            if(moby[0x43]!=8) anim_start_blended(moby,8,0,20);
        }
        break;
    case 7:
        if(moby[0x60]&2) {
            moby_set_state(moby,6,-1);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,10);
        } else {
            float anim_time;
            u8 *yaw_field=moby+0xF8;
            u8 *target=*(u8 **)(vars+0x368);
            angle=mat_fast_helper_a(*(float *)(target+0x10)-*(float *)(moby+0x10),*(float *)(target+0x14)-*(float *)(moby+0x14));
            StepAngleTowardTarget(yaw_field,0,angle,0.058177649974823f);
            anim_time=moby_get_anim_value(moby);
            if(12.0f<=anim_time && anim_time<=14.0f) coll_test_hit_at_bone(moby,2,1,0,1,0,0.25f,vars[0x34],1.0f);
            moby_step_at_own_position(moby);
        }
        break;
    case 10: {
        u8 *position=moby+0x10;
        u8 *target=*(u8 **)(vars+0x374);
        angle=mat_fast_helper_a(*(float *)(target+0x10)-*(float *)(moby+0x10),*(float *)(target+0x14)-*(float *)(moby+0x14));
        moby_step_controller(moby,position,angle);
        if(moby[0x43]==5 && *(float *)(moby+0x18)<*(float *)(vars+0x348)+*(float *)(vars+0x1F8)*10.0f) anim_start_blended(moby,6,0,10);
        if(moby[0x43]==6 && (moby[0x60]&2)) {
            moby_set_state(moby,11,-1);
            if(moby[0x43]!=7) anim_start_blended(moby,7,0,20);
        }
        break; }
    case 11:
        moby_l01_turn_toward_target(moby,*(u8 **)(vars+0x374)+0x10);
        if(*(float *)(vars+0x21C)<2.0f) {
            moby_set_state(moby,12,-1);
            if(moby[0x43]!=8) anim_start_blended(moby,8,0,20);
        }
        break;
    case 12: {
        float anim_time;
        if(*(u8 **)(vars+0x374)) {
            moby_l01_turn_toward_target(moby,*(u8 **)(vars+0x374)+0x10);
            anim_time=moby_get_anim_value(moby);
            if(11.0f<=anim_time) {
                int release=1;
                matrix_mul_vec3(temp,D_L12_001B0A30,moby+0xC0);
                FastVecAdd(temp,temp,moby+0x10);
                if(!(14.0f<=anim_time)) release=0;
                sub_object_start_move(*(u8 **)(vars+0x374),temp,moby+0xF0,release);
                if(release) *(int *)(vars+0x374)=0;
            }
        }
        if(moby[0x60]&2) {
            moby_set_state(moby,13,-1);
            if(moby[0x43]!=9) anim_start_blended(moby,9,0,10);
        }
        break; }
    case 13:
        if(moby[0x60]&2) {
            moby_set_state(moby,1,0);
            if(moby[0x43]) anim_start_blended(moby,0,0,10);
        }
        break;
    }
    joint_slots_reset_advance(moby);
}
