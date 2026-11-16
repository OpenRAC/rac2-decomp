#include "common.h"
/* Creates object 3790 with copied position/velocity and randomized rotation. */

typedef int Quad __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern int math_random_int_range(int,int);
extern float math_random_angle(void),math_random_float_range(float,float);
extern void euler_rotation_basis(void *,void *),math_build_axis_angle_quat(void *,void *,float),func_002A0F48(void *);
extern int part_alloc_effect_slot(void *,int,float,float,float);
extern int g_tumbling_debris_spin_min __attribute__((sda)),g_tumbling_debris_spin_max __attribute__((sda));
extern unsigned short g_tumbling_debris_duration __attribute__((sda));
extern float g_tumbling_debris_scale_default __attribute__((sda)),g_tumbling_debris_scale_alt __attribute__((sda));
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
        *(short *)(state+0x20)=math_random_int_range(g_tumbling_debris_spin_min,g_tumbling_debris_spin_max);
        *(unsigned short *)(object+0x34)|=0x100;
        *(float *)(object+0xF0)=math_random_angle();
        *(float *)(object+0xF4)=math_random_angle();
        *(float *)(object+0xF8)=math_random_angle();
        euler_rotation_basis(object+0xC0,object+0xF0);
        rotation=math_random_float_range(0.05235988646745682f,0.10471977293491364f);
        math_build_axis_angle_quat(state+0x10,object+0xD0,rotation);
        duration=g_tumbling_debris_duration;
        *(int *)(state+0x24)=mode;
        *(short *)(state+0x22)=duration+lifetime;
        if(mode!=0) *(float *)(object+0x2C)*=g_tumbling_debris_scale_alt;
        else *(float *)(object+0x2C)*=g_tumbling_debris_scale_default;
        *(int *)(state+0x28)=part_alloc_effect_slot(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}
