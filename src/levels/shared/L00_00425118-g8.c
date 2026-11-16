#include "include_asm.h"
#include "names.h"
extern char g_camera_move_state[];
extern float g_cam_vehicle_spring_stiffness __attribute__((sda)), g_cam_vehicle_spring_damping __attribute__((sda));
extern float g_cam_vehicle_turn_factor_idle __attribute__((sda)), g_cam_vehicle_turn_factor_straight __attribute__((sda));
extern float g_cam_vehicle_turn_limit __attribute__((sda)), g_cam_vehicle_turn_divisor __attribute__((sda));
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
    char *camera=g_camera_move_state;
    float factor, angle, length, dot, amount;
    F(state,0)=math_step_spring_damper_clamped(state+4,F(state,0),forward,g_cam_vehicle_spring_stiffness,g_cam_vehicle_spring_damping,0.0f);
    F(movement,52)=F(state,20)*F(state,0);
    if(turn<-0.3f) turn=(turn+0.3f)*1.4285714626312256f;
    else if(turn>0.3f) turn=(turn-0.3f)*1.4285714626312256f;
    else turn=0;
    if(turn==0) factor=g_cam_vehicle_turn_factor_straight;
    else if(math_fabs(turn)<math_fabs(F(state,8))) {
        factor = ((turn>0 && F(state,8)>0) || (turn<0 && F(state,8)<0))
            ? g_cam_vehicle_turn_factor_straight : g_cam_vehicle_turn_factor_idle;
    } else factor=g_cam_vehicle_turn_factor_idle;
    {
        float value=math_step_spring_damper_clamped(state+12,F(state,8),turn,g_cam_vehicle_spring_stiffness,g_cam_vehicle_spring_damping,factor);
        amount=g_cam_vehicle_turn_divisor*value;
        F(state,8)=value;
    }
    if(forward==0) math_apply_axis_rotation_to_quat(movement,movement,camera+32,F(state,32));
    else math_apply_axis_rotation_to_quat(movement,movement,camera+32,F(movement,52));
    dot=FastVecDot(movement,camera+32);
    length=FastVecLength(movement);
    FastVecCross(axis,camera+32,movement);
    vec_scale_to_length(axis,axis,1.0f);
    angle=mat_fast_helper_a(length,dot);
    if(math_fabs(angle)<math_fabs(amount) && factor==g_cam_vehicle_turn_factor_straight)
        F(state,8)=angle/g_cam_vehicle_turn_divisor;
    if(angle<amount) {
        if(amount<FastAddRotations(angle,g_cam_vehicle_turn_limit))
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=g_cam_vehicle_turn_limit;
    } else if(amount<angle && S(P(obj,112),552)>=0) {
        if(FastAddRotations(angle,-g_cam_vehicle_turn_limit)<amount)
            F(movement,56)=fast_subtract_rotations(amount,angle);
        else F(movement,56)=-g_cam_vehicle_turn_limit;
    } else F(movement,56)=0;
    if(amount<0) S(P(obj,112),34)=1;
    math_apply_axis_rotation_to_quat(movement,movement,axis,F(movement,56));
}
