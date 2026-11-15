#include "common.h"
typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct {
    float horizontalLow, horizontalHigh, verticalLow, verticalHigh;
    float rotation, sizeLow, sizeHigh;
} ParticleBurstSettings;
extern ParticleVector ref_00306680_00 __attribute__((nosda));
extern float ref_00306680_01 __attribute__((sda)); /* horizontalLow */
extern float ref_00306680_02 __attribute__((sda)); /* horizontalHigh */
extern float ref_00306680_03 __attribute__((sda)); /* verticalLow */
extern float ref_00306680_04 __attribute__((sda)); /* verticalHigh */
extern float ref_00306680_05 __attribute__((sda)); /* rotation */
extern float ref_00306680_06 __attribute__((sda)); /* sizeLow */
extern float ref_00306680_07 __attribute__((sda)); /* sizeHigh */
extern void FastVecSub(void *, void *, void *);
extern void moby_get_facing_direction(void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern int func_001163B0(void);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_ground_effect(void *, int, float, float, u32, int, int, void *, float, int);
extern int FloatToInt(float);

/* Scatter paired impact particles in the plane around the supplied point. */
void part_spawn_impact_burst(void *origin, int count)
{
    ParticleVector velocity, position, side, axis, projection, pull;
    ParticleVector *anchor=&ref_00306680_00;
    char *particle;
    float size, speed, angle, projectionLength;
    int random, spin, i;
    FastVecSub(&side,anchor,origin);
    moby_get_facing_direction(origin,&axis);
    projectionLength=FastVecDot(&axis,&side);
    FastVecScale(&projection,&axis,projectionLength);
    FastVecSub(&side,&side,&projection);
    for (i = 0; i < count; i++) {
        size=math_random_float_range(ref_00306680_06,ref_00306680_07);
        spin=math_random_int_below(2);
        if (spin) ; else spin--;
        angle=math_random_float_range(-1.0471977f,1.0471977f);
        math_apply_axis_rotation_to_quat(&velocity,&side,&axis,angle);
        speed=math_random_float_range(ref_00306680_01,ref_00306680_02)*0.016666668f;
        vec_scale_to_length(&velocity,&velocity,speed);
        velocity.f[2]=math_random_float_range(ref_00306680_03,ref_00306680_04)*0.016666668f;
        position.word=*(ParticleWord *)origin;
        position.f[0]+=math_random_signed_float_range(0.0f,0.15f);
        position.f[1]+=math_random_signed_float_range(0.0f,0.15f);
        position.f[2]+=math_random_signed_float_range(0.0f,0.15f);
        if (!(func_001163B0()&1)) {
            FastVecScale(&velocity,&velocity,1.5f);
            particle=part_spawn_ground_effect(&position,60,size*0.35f,size,0x7f000080,0,spin,&velocity,ref_00306680_05,1);
            if (particle) particle[9]=(char)FloatToInt(4.0f)+0x70;
            particle=part_spawn_ground_effect(&position,60,size*0.245f,size*0.7f,0x7f7f7f7f,1,-spin,&velocity,ref_00306680_05,1);
        } else {
            FastVecSub(&pull,&ref_00306680_00,&position);
            vec_scale_to_length(&pull,&pull,speed);
            FastVecAdd(&velocity,&velocity,&pull);
            particle=part_spawn_ground_effect(&position,40,size*2.05f,size,0x7f000080,0,spin,&velocity,ref_00306680_05,1);
            if (particle) particle[9]=(char)FloatToInt(4.0f)+0x70;
            particle=part_spawn_ground_effect(&position,40,size*1.4350001f,size*0.7f,0x7f7f7f7f,1,-spin,&velocity,ref_00306680_05,1);
        }
        if (particle) particle[9]=(char)FloatToInt(4.0f)+0x70;
    }
}
