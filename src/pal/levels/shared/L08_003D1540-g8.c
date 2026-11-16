#include "names.h"
/* func_PAL_L08_003D1540, the PAL copy of func_L08_003CD708: the same C, where the smoothing
 * rates are scaled by 1.44 and the limits by 1.2 for 50 Hz, and the angle constants change. */
#include "common.h"
typedef struct { unsigned char pad[0x108]; float x,y,z,baseX,baseY,baseZ; unsigned char gap[0x80]; int flags; } SteeringInputs;
extern SteeringInputs g_pad_state;
typedef struct { unsigned char pad[0x1FB4]; float bank; unsigned char gap[0x24B8-0x1FB8]; float tickScale; } SteeringHero;
extern SteeringHero g_hero_state;
extern int g_vehicle_steering_flag __attribute__((sda)),g_vehicle_active_flag __attribute__((sda));
extern float g_vehicle_bank_limit_a __attribute__((sda));
extern float g_vehicle_bank_limit_b __attribute__((sda));
extern float g_vehicle_steer_gain_low __attribute__((sda));
extern float g_vehicle_steer_gain_high __attribute__((sda));
extern float g_vehicle_steer_gain_a __attribute__((sda));
extern float g_vehicle_steer_gain_b __attribute__((sda));
extern float g_vehicle_steer_limit_low __attribute__((sda));
extern float g_vehicle_steer_limit_high __attribute__((sda));
extern float g_vehicle_steer_limit_a __attribute__((sda));
extern float g_vehicle_steer_limit_b __attribute__((sda));
extern float g_vehicle_steer_limit2_low __attribute__((sda));
extern float g_vehicle_steer_limit2_high __attribute__((sda));
extern float g_vehicle_steer_limit_c __attribute__((sda));
extern float g_vehicle_steer_target_scale __attribute__((sda));
extern float g_vehicle_approach_target __attribute__((sda));
extern float g_vehicle_approach_accel __attribute__((sda));
extern float g_vehicle_approach_decel __attribute__((sda));
extern float g_vehicle_steer_divisor_y __attribute__((sda));
extern float g_vehicle_steer_rotation_scale_y __attribute__((sda));
extern float g_vehicle_steer_divisor_x __attribute__((sda));
extern float g_vehicle_steer_multiplier_y __attribute__((sda));
extern float g_vehicle_steer_multiplier_x __attribute__((sda));
extern float g_vehicle_bank_limit_degrees __attribute__((sda));
extern float g_vehicle_turn_step_scale __attribute__((sda));
extern float g_vehicle_tick_turn_scale __attribute__((sda));
extern float g_vehicle_bank_approach_rate __attribute__((sda));
extern float math_spring_float_to_goal(float *,float *,float,float,float,float);
extern float ApproachValue(float *,float,float);
extern float math_approach_with_velocity(float *,float,float *,float,float,float,int);
extern float fast_subtract_rotations(float,float),FastAddRotations(float,float),math_fabs(float);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))

typedef struct { unsigned char pad[0x20]; unsigned char mode; } SteeringObject;

/* Smooth the steering and orientation targets from the combined controls.
 * mode is 64-bit: its (zero_extend:DI (mem:QI)) differs from the (zero_extend:SI) of the first
 * test, so gcse keeps the second read of the field that retail has. */
void func_PAL_L08_003D1540(SteeringObject *object,char *state,float inputScale)
{
    u64 mode;

    float gain=g_vehicle_steer_gain_a;
    float targetX,targetY,bias=0.0f;
    float limit=g_vehicle_steer_limit_a;
    float bound,value,step;
    float magnitude;
    SteeringHero *hero;
    if (object->mode==8) {
        limit=g_vehicle_steer_limit_c;
        if (I(state,0x50)==0) bias=-2.0f;
    }
    targetX=(g_pad_state.x-g_pad_state.baseX+g_pad_state.z)*inputScale;
    targetY=(g_pad_state.y-g_pad_state.baseY+g_pad_state.baseZ+bias)*inputScale;
    if (targetX>inputScale) targetX=inputScale;
    else if (targetX < -inputScale) targetX=-inputScale;
    if (targetY>inputScale) targetY=inputScale;
    else if (targetY < -inputScale) targetY=-inputScale;
    if (g_pad_state.flags&0x200) {
        targetX/=g_vehicle_steer_divisor_x;
        targetY/=g_vehicle_steer_divisor_y;
        targetX*=g_vehicle_steer_multiplier_x;
        targetY*=g_vehicle_steer_multiplier_y;
        gain=g_vehicle_steer_gain_b;
        limit=g_vehicle_steer_limit_b;
    }
    mode=object->mode;
    if (mode==7 || mode<6) goto update_pitch;
    if (g_vehicle_steering_flag) {
        if (mode!=8) {
            math_spring_float_to_goal((float *)(state+0x60),(float *)(state+0x44),targetY,
                          g_vehicle_steer_limit_low*1.44f,g_vehicle_steer_limit_high*1.44f,limit*1.2f);
            if (g_vehicle_active_flag)
                F(state,0x14)=fast_subtract_rotations(F(state,0x14),(F(state,0x60)*0.0003490659f)*g_vehicle_steer_divisor_y);
            bound=g_vehicle_bank_limit_a;
        } else {
            math_spring_float_to_goal((float *)(state+0x60),(float *)(state+0x44),targetY,
                          g_vehicle_steer_limit2_low*1.44f,g_vehicle_steer_limit2_high*1.44f,limit*1.2f);
            if (g_vehicle_active_flag)
                F(state,0x14)=fast_subtract_rotations(F(state,0x14),(F(state,0x60)*0.0003490659f)*g_vehicle_steer_rotation_scale_y);
            bound=g_vehicle_bank_limit_b;
        }
        bound*=0.01745329424738884f;
        if (F(state,0x14)>bound) F(state,0x14)=bound;
        else if (F(state,0x14)<-bound) F(state,0x14)=-bound;
    } else {
        hero=&g_hero_state;
        magnitude=math_fabs(hero->bank);
        if (magnitude<math_fabs(F(state,0x60)))
            ApproachValue((float *)(state+0x60),-hero->bank,g_vehicle_bank_approach_rate*1.44f);
        else F(state,0x60)=-hero->bank;
        step=(F(state,0x60)*0.01745329424738884f)*g_vehicle_turn_step_scale;
        if (math_fabs(F(state,0x60))>0.2f) {
            value=fast_subtract_rotations(step,F(state,0x14));
            bound=g_vehicle_bank_limit_degrees*0.0003490659f;
            if (value>bound) value=bound;
            else if (value<-bound) value=-bound;
            ApproachValue((float *)(state+0x44),value,
                         g_vehicle_tick_turn_scale*(g_hero_state.tickScale*6.981318e-06f));
            F(state,0x14)=FastAddRotations(F(state,0x14),F(state,0x44));
        } else {
            math_approach_with_velocity((float *)(state+0x14),0.0f,(float *)(state+0x44),
                          0.015840001f,0.43200004f,0.01745329424738884f,0);
        }
    }
update_pitch:
    math_spring_float_to_goal((float *)(state+0x5C),(float *)(state+0x48),targetX,
                  g_vehicle_steer_gain_low*1.44f,g_vehicle_steer_gain_high*1.44f,gain*1.2f);
    if (g_vehicle_active_flag)
        math_approach_with_velocity((float *)(state+0x10),F(state,0x5C)*g_vehicle_steer_target_scale,
                      (float *)(state+0x40),g_vehicle_approach_target*1.44f,g_vehicle_approach_accel*1.44f,g_vehicle_approach_decel*1.2f,0);
    if (g_vehicle_active_flag)
        F(state,0x18)=fast_subtract_rotations(F(state,0x18),(F(state,0x5C)*0.0003490659f)*g_vehicle_steer_divisor_x);
}
