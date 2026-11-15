#include "common.h"
/* Creates object 3790 with copied position/velocity and randomized rotation. */

typedef int Quad __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern int math_random_int_range(int,int);
extern float math_random_angle(void),math_random_float_range(float,float);
extern void euler_rotation_basis(void *,void *),math_build_axis_angle_quat(void *,void *,float),func_002A0F48(void *);
extern int part_alloc_effect_slot(void *,int,float,float,float);
extern int D_L00_001B0FA4 __attribute__((sda)),D_L00_001B0FA8 __attribute__((sda));
extern unsigned short D_L00_001B0FC4 __attribute__((sda));
extern float D_L00_001B0FB4 __attribute__((sda)),D_L00_001B0FB8 __attribute__((sda));
char *tumbling_debris_create(Quad *position,Quad *velocity,int lifetime,int mode)
{
    char *object;
    char *state;
    float rotation;
    int duration;
    object=CreateMoby(3790 /* moby class 3790 */);
    if(object) {
        state=*(char **)(object+0x68);
        *(short *)(object+0x32)=255; *(unsigned char *)(object+0x30)=255; object[0x20]=0;
        *(Quad *)(object+0x10)=*position; *(Quad *)state=*velocity;
        *(short *)(state+0x20)=math_random_int_range(D_L00_001B0FA4,D_L00_001B0FA8);
        *(unsigned short *)(object+0x34)|=0x100;
        *(float *)(object+0xF0)=math_random_angle();
        *(float *)(object+0xF4)=math_random_angle();
        *(float *)(object+0xF8)=math_random_angle();
        euler_rotation_basis(object+0xC0,object+0xF0);
        rotation=math_random_float_range(0.05235988646745682f,0.10471977293491364f);
        math_build_axis_angle_quat(state+0x10,object+0xD0,rotation);
        duration=D_L00_001B0FC4;
        *(int *)(state+0x24)=mode;
        *(short *)(state+0x22)=duration+lifetime;
        if(mode!=0) *(float *)(object+0x2C)*=D_L00_001B0FB8;
        else *(float *)(object+0x2C)*=D_L00_001B0FB4;
        *(int *)(state+0x28)=part_alloc_effect_slot(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}
