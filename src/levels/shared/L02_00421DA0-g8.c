#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { u8 reserved[0x140]; float position[4]; } FlareTargetView;
extern FlareTargetView g_hero_effect_state __attribute__((nosda));
extern float g_impact_particle_speed_min __attribute__((sda)),g_impact_particle_speed_max __attribute__((sda));
extern float g_impact_particle_rise_min __attribute__((sda)),g_impact_particle_rise_max __attribute__((sda));
extern float g_ground_effect_last_arg __attribute__((sda));
extern float g_impact_size_min __attribute__((sda)),g_impact_size_max __attribute__((sda));
extern u32 g_ground_effect_color_a __attribute__((sda)),g_ground_effect_color_b __attribute__((sda));
extern void FastVecSub(void *,void *,void *);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern float math_random_signed_float_range(float,float);
extern int func_001163B0(void);
extern void FastVecScale(void *,void *,float);
extern u8 *part_spawn_ground_effect(void *,int,u32,float,float,int,int,void *,int,float);
extern int FloatToInt(float);
extern void FastVecAdd(void *,void *,void *);

/* Emit paired particles, choosing an outward or target-directed trajectory. */
void part_spawn_impact_particles(void *origin,int count,int inner)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float toward[4] __attribute__((aligned(16)));
    int i,sign;
    float size,angle,speed;
    u8 *particle;
    FastVecSub(base,g_hero_effect_state.position,origin);
    base[2]=0;
    axis[0]=0;axis[1]=0;axis[2]=1;axis[3]=1;
    for(i=0;i<count;i++) {
        size=math_random_float_range(g_impact_size_min,g_impact_size_max);
        sign=math_random_int_below(2);
        if (!sign) sign--;
        angle=math_random_float_range(-1.0471977f,1.0471977f);
        math_apply_axis_rotation_to_quat(velocity,base,axis,angle);
        speed=math_random_float_range(g_impact_particle_speed_min,g_impact_particle_speed_max)*0.016666668f;
        vec_scale_to_length(velocity,velocity,speed);
        velocity[2]=math_random_float_range(g_impact_particle_rise_min,g_impact_particle_rise_max)*0.016666668f;
        qcopy(position,origin);
        position[0]+=math_random_signed_float_range(0,0.15f);
        position[1]+=math_random_signed_float_range(0,0.15f);
        position[2]+=math_random_signed_float_range(0,0.15f);
        if(!inner) {
            if(!(func_001163B0()&1)) {
                FastVecScale(velocity,velocity,1.5f);
                particle=part_spawn_ground_effect(position,60,g_ground_effect_color_a,size*0.35f,size,0,sign,velocity,0,g_ground_effect_last_arg);
                if(particle) particle[9]=(u8)(FloatToInt(4.0f)+0x70);
                particle=part_spawn_ground_effect(position,60,g_ground_effect_color_b,size*0.245f,size*0.7f,1,-sign,velocity,0,g_ground_effect_last_arg);
            } else {
                FastVecSub(toward,g_hero_effect_state.position,position);
                vec_scale_to_length(toward,toward,speed);
                FastVecAdd(velocity,velocity,toward);
                particle=part_spawn_ground_effect(position,40,g_ground_effect_color_a,size*2.05f,size,0,sign,velocity,0,g_ground_effect_last_arg);
                if(particle) particle[9]=(u8)(FloatToInt(4.0f)+0x70);
                particle=part_spawn_ground_effect(position,40,g_ground_effect_color_b,size*1.4350001f,size*0.7f,1,-sign,velocity,0,g_ground_effect_last_arg);
            }
        } else {
            if(!(func_001163B0()&1)) {
                FastVecScale(velocity,velocity,1.5f);
                particle=part_spawn_ground_effect(position,60,g_ground_effect_color_a,size*0.3f,size,0,sign,velocity,0,g_ground_effect_last_arg);
                if(particle) particle[9]=(u8)(FloatToInt(4.0f)+0x70);
                particle=part_spawn_ground_effect(position,60,g_ground_effect_color_b,size*0.21000001f,size*0.7f,1,-sign,velocity,0,g_ground_effect_last_arg);
            } else {
                FastVecSub(toward,g_hero_effect_state.position,position);
                vec_scale_to_length(toward,toward,speed);
                FastVecAdd(velocity,velocity,toward);
                particle=part_spawn_ground_effect(position,40,g_ground_effect_color_a,size*0.25f,size,0,sign,velocity,0,g_ground_effect_last_arg);
                if(particle) particle[9]=(u8)(FloatToInt(4.0f)+0x70);
                particle=part_spawn_ground_effect(position,40,g_ground_effect_color_b,size*0.175f,size*0.7f,1,-sign,velocity,0,g_ground_effect_last_arg);
            }
        }
        if(particle) particle[9]=(u8)(FloatToInt(4.0f)+0x70);
    }
}
