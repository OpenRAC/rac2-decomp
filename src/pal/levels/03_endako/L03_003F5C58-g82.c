#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *,void *);
extern void math_approach_target_with_braking(void *,float,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int PlayMobySound(int,int,void *);
extern void ApproachValue(void *,float,float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float,float);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern void math_approach_target_with_direction_mode(void *,void *,float,float,float,float,int);
extern u8 D_L03_00188660[] NOT_SDA;
extern float D_0018A138 NOT_SDA;
extern float D_L03_001B1088 __attribute__((sda)), D_L03_001B1074 __attribute__((sda)), D_L03_001B1078 __attribute__((sda));
extern float D_L03_001B107C __attribute__((sda)), D_L03_001B1080 __attribute__((sda)), D_L03_001B1084 __attribute__((sda)), D_L03_001B108C __attribute__((sda));

void func_PAL_L03_003FA3C0(u8 *entity) {
    u8 *state = *(u8 **)(entity+0x68);
    float delta[4];
    int next;
    float distance, target, tilt, blend, rate, speed, remaining, wave, step;
    if (*(u8 **)(state+0x2CC)) {
        next = *(int *)(state+0x2D8);
        if (*(int *)(state+0x2DC) < next) next--;
        else if (next < *(int *)(state+0x2DC)) next++;
        FastVecSub(delta, *(u8 **)(state+0x2CC)+(next*16+16), state+0x290);
        distance = FastVecLength(delta);
        remaining=fast_vec_dist(state+0x290,*(u8 **)(state+0x2CC)+(*(int *)(state+0x2DC)*16+16));
        math_approach_target_with_braking(state+0x2D0,remaining,D_L03_001B1088*0.00040000002f,D_L03_001B1088*0.00040000002f,0.20000002f);
        vec_scale_to_length(delta,delta,*(float *)(state+0x2D0));
        FastVecAdd(state+0x290,state+0x290,delta);
        if (distance <= *(float *)(state+0x2D0)) *(int *)(state+0x2D8)=next;
        {
            u8 *sound=D_L03_00188660+*(int *)(state+0x3CC)*0x70;
            if (*(u8 **)(sound+0x88)!=entity || !sound[0x74]) *(int *)(state+0x3CC)=PlayMobySound(0,4,entity);
        }
    }
    switch(entity[0x95]) {
    case 3:
        distance=D_0018A138-155.0f;
        if(distance>1.5f) distance=1.5f;
        else if(distance<0) distance=0;
        ApproachValue(state+0x300,0.1f,0.010000001f);
        ApproachValue(state+0x304,distance,0.030000001f);
        break;
    case 4:
        ApproachValue(state+0x300,0.3f,0.010000001f);
        ApproachValue(state+0x304,1.5f,0.030000001f);
        break;
    case 1:
        ApproachValue(state+0x300,0.1f,0.010000001f);
        ApproachValue(state+0x304,1.5f,0.030000001f);
        break;
    default:
        ApproachValue(state+0x300,D_L03_001B1074,0.010000001f);
        ApproachValue(state+0x304,D_L03_001B1078,0.030000001f);
    }
    qcopy(entity+0x10,state+0x290);
    wave=math_fast_sin_or_cos_b(*(float *)(state+0x2C0));
    step=D_L03_001B107C*0.0003490659f;
    *(float *)(entity+0x18)+=*(float *)(state+0x300)*wave+*(float *)(state+0x304);
    *(float *)(state+0x2C0)=FastAddRotations(*(float *)(state+0x2C0),step);
    if(entity[0x95]==0 && vec_length_xy(delta)>0.020000001f) {
        tilt=0.17453295f;
        target=mat_fast_helper_a(delta[0],delta[1]);
    } else {
        target=mat_fast_helper_a(*(float *)(state+0x50)-*(float *)(entity+0x10),*(float *)(state+0x54)-*(float *)(entity+0x14));
        tilt=0;
        blend=*(float *)(state+0x2D0)*4.9999995f-0.1f;
        if(blend>1) blend=1;
        else if(blend<0) blend=0;
        if(blend!=0) {
            if(entity[0x95]!=4) {
                if(fast_subtract_rotations(mat_fast_helper_a(delta[0],delta[1]),*(float *)(entity+0xF8))<0)
                    speed=-(D_L03_001B1084*0.017453294f);
                else speed=D_L03_001B1084*0.017453294f;
                target=FastAddRotations(target,speed*blend);
            }
            tilt=D_L03_001B1080*(blend*0.017453294f);
        }
    }
    rate=0.0025132746f;
    if(entity[0x95]==3) rate=0;
    math_approach_target_with_direction_mode(state+0x2A4,state+0x3C8,tilt,rate,0.0025132746f,0.25132746f,0);
    math_approach_target_with_direction_mode(state+0x2A8,state+0x3C4,target,rate,0.0025132746f,0.25132746f,0);
    qcopy(entity+0xF0,state+0x2A0);
}
