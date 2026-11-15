#include "include_asm.h"
#include "names.h"
extern char D_L00_001B8E20[];
extern float D_L00_001B14AC __attribute__((sda)), D_L00_001B14B0 __attribute__((sda));
extern float D_L00_001B14B8 __attribute__((sda)), D_L00_001B14BC __attribute__((sda));
extern float D_L00_001B14C0 __attribute__((sda)), D_L00_001B14C4 __attribute__((sda));
extern float math_step_spring_damper_clamped(void *,float,float,float,float,float);
extern float math_fabs(float);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern float mat_fast_helper_a(float,float);
extern float FastAddRotations(float,float);
extern float fast_subtract_rotations(float,float);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define S(p,n) (*(short *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Updates the camera turn for a vehicle from forward and turn input. It smooths the speed and bends the camera's direction toward the turn. */
void cam_vehicle_update_turn(char *obj,float forward,float turn)
{
    float axis[4];
    char *base=P(obj,112);
    char *state=base+448;
    char *movement=base+352;
    char *camera=D_L00_001B8E20;
    float factor, angle, length, dot, amount;
    F(state,0)=math_step_spring_damper_clamped(state+4,F(state,0),forward,D_L00_001B14AC,D_L00_001B14B0,0.0f);
    F(movement,52)=F(state,20)*F(state,0);
    if(turn<-0.3f) turn=(turn+0.3f)*1.4285714626312256f;
    else if(turn>0.3f) turn=(turn-0.3f)*1.4285714626312256f;
    else turn=0;
    if(turn==0) factor=D_L00_001B14BC;
    else if(math_fabs(turn)<math_fabs(F(state,8))) {
        factor = ((turn>0 && F(state,8)>0) || (turn<0 && F(state,8)<0))
            ? D_L00_001B14BC : D_L00_001B14B8;
    } else factor=D_L00_001B14B8;
    {
        float value=math_step_spring_damper_clamped(state+12,F(state,8),turn,D_L00_001B14AC,D_L00_001B14B0,factor);
        amount=D_L00_001B14C4*value;
        F(state,8)=value;
    }
    if(forward==0) math_apply_axis_rotation_to_quat(movement,movement,camera+32,F(state,32));
    else math_apply_axis_rotation_to_quat(movement,movement,camera+32,F(movement,52));
    dot=FastVecDot(movement,camera+32);
    length=FastVecLength(movement);
    FastVecCross(axis,camera+32,movement);
    vec_scale_to_length(axis,axis,1.0f);
    angle=mat_fast_helper_a(length,dot);
    if(math_fabs(angle)<math_fabs(amount) && factor==D_L00_001B14BC)
        F(state,8)=angle/D_L00_001B14C4;
    if(angle<amount) {
        if(amount<FastAddRotations(angle,D_L00_001B14C0))
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=D_L00_001B14C0;
    } else if(amount<angle && S(P(obj,112),552)>=0) {
        if(FastAddRotations(angle,-D_L00_001B14C0)<amount)
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=-D_L00_001B14C0;
    } else F(movement,56)=0;
    if(amount<0) S(P(obj,112),34)=1;
    math_apply_axis_rotation_to_quat(movement,movement,axis,F(movement,56));
}
