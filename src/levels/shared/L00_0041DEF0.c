#include "common.h"
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void mat_build_rotation_toward_vector(void *,void *,void *,int,float);
extern float IntToFloat(int);
extern void FastVecCross(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern float math_fast_angle_helper(float);
extern float math_fabs(float);
extern void vec_scale_to_length(void *,void *,float);
extern float math_step_spring_damper_stored(char *,float,float,float,float,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *,void *,float);
extern void vec_rotate_by_quaternion(void *,void *,void *);
/* Turns a missile toward a target, limited by how fast it can turn. Returns how sharply it is turning, from 0 to 1. */
float missile_steer_toward_target(char *object,void *target,void *up)
{
    float difference[4],axis[4],fallback[4];
    char *state=*(char **)(object+0x68);
    float distance,ratio,dot,length,angle,step,fraction=0.0f;
    FastVecSub(difference,target,object+0x10);
    distance=FastVecLength(difference);
    if(distance==0.0f) goto done;
    if(distance<1.5f) { mat_build_rotation_toward_vector(state,state,difference,0,0.5f); goto done; }
    *(short *)(state+0x12)=*(unsigned short *)(state+0x12)+1;
    if(*(short *)(state+0x12)>30) *(short *)(state+0x12)=30;
    ratio=IntToFloat(*(short *)(state+0x12))/IntToFloat(30);
    FastVecCross(axis,difference,state);
    dot=FastVecDot(state,difference);
    length=FastVecLength(state)*FastVecLength(difference);
    if(length==0.0f) goto done;
    angle=1.57079637f-math_fast_angle_helper(dot/length);
    if(math_fabs(angle)>2.879793644f) {
        FastVecCross(fallback,state,up); FastVecCross(axis,fallback,state);
    }
    vec_scale_to_length(axis,axis,1.0f);
    step=math_step_spring_damper_stored(state+0x20,0.0f,angle*0.5f,ratio*0.025f,0.3f,0.0f);
    fraction=*(float *)(state+0x20)*57.29577255f;
    if(fraction>1.0f) fraction=1.0f;
    FastVecScale(axis,axis,math_fast_sin_or_cos_b(step)); axis[3]=math_fast_sin_or_cos_a(step);
    vec_rotate_by_quaternion(state,state,axis);
done:
    return fraction;
}
