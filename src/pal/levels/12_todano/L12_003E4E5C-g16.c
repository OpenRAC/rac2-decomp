#include "names.h"
/* func_PAL_L12_003E4E5C, the PAL copy of func_L12_003E0BF0: the same C, where every blend time 10
 * becomes 8 and 20 becomes 17, the float pacing values take their 50 Hz forms, and the four timers from
 * func_002A7820 (three at +0x360, one at +0x362) are scaled by ((s32)(x) * 5 + 2) / 6 with their
 * arguments unchanged. */
#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern u8 D_0019B2E8[];
extern float D_L12_001B0A20 __attribute__((sda));
extern float D_L12_001B0A24 __attribute__((sda));
extern float D_L12_001B0A30[4] __attribute__((sda));
typedef struct TodanoPlayerView { u8 pad[0x80]; float position[4]; } TodanoPlayerView;
extern TodanoPlayerView g_hero_state;
extern u8 *g_hero_moby NOT_SDA;
extern void func_PAL_L12_003E58E8(u8 *);
extern void func_PAL_L12_003E5CA0(u8 *);
extern int flag_set_second_pending(u8 *);
extern void moby_set_state(u8 *,int,int);
extern void func_PAL_002A7E68(u8 *,int,int,int);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern int math_random_int_range(int,int);
extern int moby_dispatch_action_by_kind(u8 *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_queue_impact_effect(u8 *,u8 *,int,void *,void *,float);
extern void func_PAL_002A7650(u8 *,int,int);
extern void part_queue_moby_for_glow(u8 *,int,int);
extern void moby_mark_spawned(u8 *);
extern float math_random_angle(void);
extern float math_random_float_range(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int func_PAL_L01_00323068(u8 *,void *);
extern int math_random_int_below(int);
extern float mat_fast_helper_a(float,float);
extern void func_PAL_002B5C98(u8 *,void *,float);
extern void squirrel_alert_group(u8 *);
extern void StepAngleTowardTarget(void *,int,float,float);
extern float moby_get_anim_value(u8 *);
extern void coll_test_hit_at_bone(u8 *,int,int,int,int,int,float,float,float);
extern void func_PAL_002B5E10(u8 *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_PAL_L12_003E4CA8(void *,void *,void *,int);
void func_PAL_L12_003E4E5C(u8 *o) {
    u8 *d=*(u8 **)(o+0x68);
    float temp[4] __attribute__((aligned(16)));
    float angle, speed;
    func_PAL_L12_003E58E8(o);
    switch(o[0x95]) {
    case 5: {

        if(flag_set_second_pending(o)) {
            *(u16 *)(o+0x34)|=1;
            *(int *)(o+0x98)=0;
            o[0x31]=0;

        }
        if(D_0019B2E8[o[0xB0]+(g_current_map_index<<4)]&0x80) {
            if(*(int *)(d+0x13C)==-1) {
                moby_set_state(o,1,0);
                if(o[0x43]) func_PAL_002A7E68(o,0,0,0);
            } else {
                moby_set_state(o,9,4);
                if(o[0x43]!=14) func_PAL_002A7E68(o,14,0,0);
                *(float *)(o+0x18)+=4.0f;
                *(int *)(o+0x98)=0;
                *(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xEFFF;
            }
            *(int *)(o+0x98)=*(int *)(*(u8 **)(o+0x24)+0x10);
            o[0x31]=1;
            *(u16 *)(o+0x34)&=0xFFFE;
        }
        break; }
    case 0:
        if(flag_set_second_pending(o)) moby_set_controller_speed_limits(o,0.0016000001f,D_L12_001B0A20*0.020000001f,0.0012566373f,0.12566373f);
        if(*(short *)(d+0x364)==1) {
            moby_set_state(o,5,2);
            if(o[0x43]!=2) func_PAL_002A7E68(o,2,0,8);
        } else if(*(short *)(d+0x366)) {
            moby_set_state(o,3,1);
            if(o[0x43]!=3) func_PAL_002A7E68(o,3,0,17);
            *(short *)(d+0x366)=0;
            if(*(short *)(d+0x360)<250) *(short *)(d+0x360)=((s32)(math_random_int_range(480,600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if(flag_set_second_pending(o)) moby_set_controller_speed_limits(o,0.0048f,D_L12_001B0A24*0.020000001f,0.0025132746f,0.25132746f);
        if(*(short *)(d+0x364)==1) {
            moby_set_state(o,6,2);
            if(o[0x43]!=7) func_PAL_002A7E68(o,7,0,8);
        } else if(!*(short *)(d+0x360)) {
            moby_set_state(o,1,0);
            if(o[0x43]) func_PAL_002A7E68(o,0,0,17);
        }
        break;
    case 2:
        if(flag_set_second_pending(o)) moby_set_controller_speed_limits(o,0.0048f,D_L12_001B0A24*0.020000001f,0.0025132746f,0.25132746f);
        if(*(short *)(d+0x364)!=1) {
            moby_set_state(o,3,1);
            if(o[0x43]!=3) func_PAL_002A7E68(o,3,0,17);
            *(short *)(d+0x360)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
        }
        break;
    case 3: {
        int hit; u8 *target;
        hit=moby_dispatch_action_by_kind(o,d+0x60);
        target=*(u8 **)(d+0x38);
        if(target && *(short *)(target+0xAA)==0xFAB) {
            FastVecSub(temp,o+0x10,target+0x10);
            vec_scale_to_length(temp,temp,1.0f);
            part_queue_impact_effect(o,g_hero_moby,0x10000,*(u8 **)(d+0x38)+0x10,temp,50.0f);
        }
        if(hit&1) {
            func_PAL_002A7650(o,0,3);
            qcopy(temp,o+0x10);
            temp[2]+=0.25f;
            part_queue_moby_for_glow(o,0,0);
            moby_mark_spawned(o);
            return;
        }
        if(hit&2) {
            if(*(short *)(d+0x364)==1) {
                moby_set_state(o,6,2);
                if(o[0x43]!=7) func_PAL_002A7E68(o,7,0,17);
            } else {
                moby_set_state(o,3,1);
                if(o[0x43]!=3) func_PAL_002A7E68(o,3,0,17);
                *(short *)(d+0x360)=((s32)(math_random_int_range(580,600)) * 5 + 2) / 6;
            }
        }
        break; }
    case 4:
        if(flag_set_second_pending(o)) moby_set_controller_speed_limits(o,0.0064000003f,D_L12_001B0A24*0.020000001f,0.005026549f,0.25132746f);
        break;
    }
    switch(o[0x20]) {
    case 1:
        if(!*(short *)(d+0x362)) {
            moby_set_state(o,2,-1);
            angle=math_random_angle();
            speed=math_random_float_range(3.0f,5.0f);
            *(float *)(d+0x350)=math_fast_sin_or_cos_a(angle)*speed;
            *(float *)(d+0x354)=math_fast_sin_or_cos_b(angle)*speed;
            *(int *)(d+0x358)=0;
            FastVecAdd(d+0x350,d+0x350,d+0x340);
            if(o[0x43]!=15) func_PAL_002A7E68(o,15,0,8);
        }
        func_PAL_002B5E10(o);
        break;
    case 2: {
        int hit;
        hit=func_PAL_L01_00323068(o,d+0x350);
        if((*(u16 *)(o+0x96)>=26 && (hit&0x80)) || *(u16 *)(o+0x96)>=501) {
            moby_set_state(o,1,-1);
            *(short *)(d+0x362)=((s32)(math_random_int_range(300,500)) * 5 + 2) / 6;
            if(o[0x43]!=math_random_int_below(2)) func_PAL_002A7E68(o,math_random_int_below(2),0,17);
        }
        break; }
    case 3: func_PAL_002B5E10(o); break;
    case 5: {
        u8 *position=o+0x10;
        u8 *target=*(u8 **)(d+0x368);
        int v;
        angle=mat_fast_helper_a(g_hero_state.position[0]-*(float *)(target+0x10),g_hero_state.position[1]-*(float *)(target+0x14));
        func_PAL_002B5C98(o,position,angle);
        v=o[0x60];
        v&=2;
        if(v) {
            moby_set_state(o,6,-1);
            if(o[0x43]!=7) func_PAL_002A7E68(o,7,0,17);
        } else {
            v=*(u16 *)(o+0x96);
            if(v==17) squirrel_alert_group(o);
        }
        break; }
    case 6:
        if(func_PAL_L01_00323068(o,*(u8 **)(d+0x368)+0x10)&0x80) {
            moby_set_state(o,7,-1);
            if(o[0x43]!=8) func_PAL_002A7E68(o,8,0,17);
        }
        break;
    case 7:
        if(o[0x60]&2) {
            moby_set_state(o,6,-1);
            if(o[0x43]!=7) func_PAL_002A7E68(o,7,0,8);
        } else {
            float time;
            u8 *yaw=o+0xF8;
            u8 *target=*(u8 **)(d+0x368);
            angle=mat_fast_helper_a(*(float *)(target+0x10)-*(float *)(o+0x10),*(float *)(target+0x14)-*(float *)(o+0x14));
            StepAngleTowardTarget(yaw,0,angle,0.06981318f);
            time=moby_get_anim_value(o);
            if(12.0f<=time && time<=14.0f) coll_test_hit_at_bone(o,2,1,0,1,0,0.25f,d[0x34],1.0f);
            func_PAL_002B5E10(o);
        }
        break;
    case 10: {
        u8 *position=o+0x10;
        u8 *target=*(u8 **)(d+0x374);
        angle=mat_fast_helper_a(*(float *)(target+0x10)-*(float *)(o+0x10),*(float *)(target+0x14)-*(float *)(o+0x14));
        func_PAL_002B5C98(o,position,angle);
        if(o[0x43]==5 && *(float *)(o+0x18)<*(float *)(d+0x348)+*(float *)(d+0x1F8)*8.0f) func_PAL_002A7E68(o,6,0,8);
        if(o[0x43]==6 && (o[0x60]&2)) {
            moby_set_state(o,11,-1);
            if(o[0x43]!=7) func_PAL_002A7E68(o,7,0,17);
        }
        break; }
    case 11:
        func_PAL_L01_00323068(o,*(u8 **)(d+0x374)+0x10);
        if(*(float *)(d+0x21C)<2.0f) {
            moby_set_state(o,12,-1);
            if(o[0x43]!=8) func_PAL_002A7E68(o,8,0,17);
        }
        break;
    case 12: {
        float time;
        if(*(u8 **)(d+0x374)) {
            func_PAL_L01_00323068(o,*(u8 **)(d+0x374)+0x10);
            time=moby_get_anim_value(o);
            if(11.0f<=time) {
                int release=1;
                matrix_mul_vec3(temp,D_L12_001B0A30,o+0xC0);
                FastVecAdd(temp,temp,o+0x10);
                if(!(14.0f<=time)) release=0;
                func_PAL_L12_003E4CA8(*(u8 **)(d+0x374),temp,o+0xF0,release);
                if(release) *(int *)(d+0x374)=0;
            }
        }
        if(o[0x60]&2) {
            moby_set_state(o,13,-1);
            if(o[0x43]!=9) func_PAL_002A7E68(o,9,0,8);
        }
        break; }
    case 13:
        if(o[0x60]&2) {
            moby_set_state(o,1,0);
            if(o[0x43]) func_PAL_002A7E68(o,0,0,8);
        }
        break;
    }
    func_PAL_L12_003E5CA0(o);
}
