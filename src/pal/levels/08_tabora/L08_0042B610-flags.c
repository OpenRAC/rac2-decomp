#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern void vec_fast_divide_helper(void *,void *,float);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern float math_ease_out_quad(float);
extern float math_turn_angle_toward_target(float,float,float,void *,float,float);
extern int moby_move_and_collide(void *,void *,int,float,float,float);

int func_PAL_L08_0042B6D0(char *a,float accel,float speed,float turn,float blend,float angle) {
    float old[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    char *q=*(char **)(a+0x68);
    float distance, velocity, limit, timer;
    int braking=0;
    *(u128 *)old=*(u128 *)(a+0x10);
    speed *= 0.020000001f;
    accel *= 0.00040000002f;
    FastVecSub(dir,q+0x180,a+0x10);
    distance=FastVecLength(dir);
    velocity=FastVecLength(q+0x190);
    if (distance < velocity*(velocity/accel)) {velocity-=accel; braking=1;}
    else velocity += accel*math_ease_out_quad((speed-velocity)/speed);
    vec_scale_to_length(dir,dir,velocity);
    FastVecScale(q+0x190,q+0x190,blend);
    FastVecScale(dir,dir,1.0f-blend);
    FastVecAdd(q+0x190,q+0x190,dir);
    FastVecAdd(q+0x190,q+0x190,q+0x1A0);
    *(float *)(a+0x18)+=2.0f;
    timer=IntToFloat(*(s16 *)(q+0x1BE));
    { float divisor=IntToFloat(100); timer *= 6.0f; limit=timer/divisor; }
    if(limit>6.0f)limit=6.0f;
    moby_move_and_collide(a,q+0x190,0,0.0f,limit,0.0f);
    *(float *)(a+0x18)-=2.0f;
    FastVecSub(q+0x190,q+0x190,q+0x1A0);
    *(float *)(q+0x208)=math_turn_angle_toward_target(*(float *)(q+0x208),turn,0.0008377582f,q+0x1C0,0.0025132746f,0.04188791f);
    *(float *)(a+0xF4)=math_turn_angle_toward_target(*(float *)(a+0xF4),angle,0.0006981318f,q+0x220,0.0025132746f,0.04188791f);
    FastVecScale(q+0x1A0,q+0x1A0,0.95f);
    FastVecSub(dir,a+0x10,old);
    vec_fast_divide_helper(dir,dir,0.16000001f);
    FastVecAdd(a+0x10,old,dir);
    return braking;
}
