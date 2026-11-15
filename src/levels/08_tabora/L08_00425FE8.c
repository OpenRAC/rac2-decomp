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
/* Moves the object toward its target point, speeding up and then slowing down to stop there.
   Returns 1 while it is braking. */
int moby_move_to_target_braking(char *moby,float accel,float speed,float turn,float blend,float angle) {
    float old[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    char *vars=*(char **)(moby+0x68);
    float distance, velocity, limit, timer;
    int braking=0;
    *(u128 *)old=*(u128 *)(moby+0x10);
    speed *= 0.016666668f;
    accel *= 0.00027777778f;
    FastVecSub(dir,vars+0x180,moby+0x10);
    distance=FastVecLength(dir);
    velocity=FastVecLength(vars+0x190);
    if (distance < velocity*(velocity/accel)) {velocity-=accel; braking=1;}
    else velocity += accel*math_ease_out_quad((speed-velocity)/speed);
    vec_scale_to_length(dir,dir,velocity);
    FastVecScale(vars+0x190,vars+0x190,blend);
    FastVecScale(dir,dir,1.0f-blend);
    FastVecAdd(vars+0x190,vars+0x190,dir);
    FastVecAdd(vars+0x190,vars+0x190,vars+0x1A0);
    *(float *)(moby+0x18)+=2.0f;
    timer=IntToFloat(*(s16 *)(vars+0x1BE));
    { float divisor=IntToFloat(120); timer *= 6.0f; limit=timer/divisor; }
    if(limit>6.0f)limit=6.0f;
    moby_move_and_collide(moby,vars+0x190,0,0.0f,limit,0.0f);
    *(float *)(moby+0x18)-=2.0f;
    FastVecSub(vars+0x190,vars+0x190,vars+0x1A0);
    *(float *)(vars+0x208)=math_turn_angle_toward_target(*(float *)(vars+0x208),turn,0.0005817764904350042f,vars+0x1C0,0.0017453294713050127f,0.03490659222006798f);
    *(float *)(moby+0xF4)=math_turn_angle_toward_target(*(float *)(moby+0xF4),angle,0.0004848137323278934f,vars+0x220,0.0017453294713050127f,0.03490659222006798f);
    FastVecScale(vars+0x1A0,vars+0x1A0,0.95f);
    FastVecSub(dir,moby+0x10,old);
    vec_fast_divide_helper(dir,dir,0.13333334f);
    FastVecAdd(moby+0x10,old,dir);
    return braking;
}
