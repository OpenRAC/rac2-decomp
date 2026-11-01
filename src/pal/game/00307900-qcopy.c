#include "common.h"
typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct {
    float horizontalLow, horizontalHigh, verticalLow, verticalHigh;
    float rotation, sizeLow, sizeHigh;
} ParticleBurstSettings;
extern ParticleVector ref_PAL_00307900_00 __attribute__((nosda));
extern float ref_PAL_00307900_01 __attribute__((sda)); /* horizontalLow */
extern float ref_PAL_00307900_02 __attribute__((sda)); /* horizontalHigh */
extern float ref_PAL_00307900_03 __attribute__((sda)); /* verticalLow */
extern float ref_PAL_00307900_04 __attribute__((sda)); /* verticalHigh */
extern float ref_PAL_00307900_05 __attribute__((sda)); /* rotation */
extern float ref_PAL_00307900_06 __attribute__((sda)); /* sizeLow */
extern float ref_PAL_00307900_07 __attribute__((sda)); /* sizeHigh */
extern void func_00282CF0(void *, void *, void *);
extern void func_002FE8D8(void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C2210(void *, int, float, float, u32, int, int, void *, float, int);
extern int func_00283CF0(float);

/* Scatter paired impact particles in the plane around the supplied point. */
void func_PAL_00307900(void *origin, int count)
{
    ParticleVector velocity, position, side, axis, projection, pull;
    char *particle;
    float size, speed, angle, projectionLength;
    int random, spin, i;
    func_00282CF0(&side,&ref_PAL_00307900_00,origin);
    func_002FE8D8(origin,&axis);
    projectionLength=func_00282DB0(&axis,&side);
    func_00282D30(&projection,&axis,projectionLength);
    func_00282CF0(&side,&side,&projection);
    for (i = 0; i < count; i++) {
        size=func_002A7878(ref_PAL_00307900_06,ref_PAL_00307900_07);
        spin=func_002A77E0(2);
        if (spin) ; else spin--;
        angle=func_002A7878(-1.0471977f,1.0471977f);
        func_002ACEC0(&velocity,&side,&axis,angle);
        speed=func_002A7878(ref_PAL_00307900_01,ref_PAL_00307900_02)*0.020000001f;
        func_00282F20(&velocity,&velocity,speed);
        velocity.f[2]=func_002A7878(ref_PAL_00307900_03,ref_PAL_00307900_04)*0.020000001f;
        position.word=*(ParticleWord *)origin;
        position.f[0]+=func_002A78D8(0.0f,0.15f);
        position.f[1]+=func_002A78D8(0.0f,0.15f);
        position.f[2]+=func_002A78D8(0.0f,0.15f);
        if (!(func_001163B0()&1)) {
            func_00282D30(&velocity,&velocity,1.5f);
            particle=func_002C2210(&position,50,size*0.35f,size,0x7f000080,0,spin,&velocity,ref_PAL_00307900_05*1.44f,1);
            if (particle) particle[9]=(char)func_00283CF0(4.0f)+0x70;
            particle=func_002C2210(&position,50,size*0.245f,size*0.7f,0x7f7f7f7f,1,-spin,&velocity,ref_PAL_00307900_05*1.44f,1);
        } else {
            func_00282CF0(&pull,&ref_PAL_00307900_00,&position);
            func_00282F20(&pull,&pull,speed);
            func_00282CC0(&velocity,&velocity,&pull);
            particle=func_002C2210(&position,33,size*2.05f,size,0x7f000080,0,spin,&velocity,ref_PAL_00307900_05*1.44f,1);
            if (particle) particle[9]=(char)func_00283CF0(4.0f)+0x70;
            particle=func_002C2210(&position,33,size*1.4350001f,size*0.7f,0x7f7f7f7f,1,-spin,&velocity,ref_PAL_00307900_05*1.44f,1);
        }
        if (particle) particle[9]=(char)func_00283CF0(4.0f)+0x70;
    }
}
