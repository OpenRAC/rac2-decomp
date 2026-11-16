#include "common.h"
/* func_PAL_L00_0040E0B0, the PAL copy of func_L00_00409558: the same C, with the spin range
   scaled by 6/5, the random delay and the duration scaled by 5/6 at 50 Hz, and the duration
   read as a word. Creates object 3790 with copied position/velocity and randomized rotation. */

typedef int Quad __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern int math_random_int_range(int,int);
extern float math_random_angle(void),math_random_float_range(float,float);
extern void euler_rotation_basis(void *,void *),math_build_axis_angle_quat(void *,void *,float),func_002A0F48(void *);
extern int part_alloc_effect_slot(void *,int,float,float,float);
extern int g_tumbling_debris_spin_min __attribute__((sda)),g_tumbling_debris_spin_max __attribute__((sda));
extern int g_tumbling_debris_duration __attribute__((sda));
extern float g_tumbling_debris_scale_default __attribute__((sda)),g_tumbling_debris_scale_alt __attribute__((sda));
char *func_PAL_L00_0040E0B0(Quad *position,Quad *velocity,int lifetime,int mode)
{
    char *object;
    char *state;
    float rotation;
    int duration;
    object=CreateMoby(3790);
    if(object) {
        state=*(char **)(object+0x68);
        *(short *)(object+0x32)=255; *(unsigned char *)(object+0x30)=255; object[0x20]=0;
        *(Quad *)(object+0x10)=*position; *(Quad *)state=*velocity;
        *(short *)(state+0x20)=((s32)(math_random_int_range(g_tumbling_debris_spin_min,g_tumbling_debris_spin_max))*5+2)/6;
        *(unsigned short *)(object+0x34)|=0x100;
        *(float *)(object+0xF0)=math_random_angle();
        *(float *)(object+0xF4)=math_random_angle();
        *(float *)(object+0xF8)=math_random_angle();
        euler_rotation_basis(object+0xC0,object+0xF0);
        rotation=math_random_float_range(0.062831864f,0.12566373f);
        math_build_axis_angle_quat(state+0x10,object+0xD0,rotation);
        duration=((s32)(g_tumbling_debris_duration)*5+2)/6;
        *(int *)(state+0x24)=mode;
        *(short *)(state+0x22)=lifetime+duration;
        if(mode!=0) *(float *)(object+0x2C)*=g_tumbling_debris_scale_alt;
        else *(float *)(object+0x2C)*=g_tumbling_debris_scale_default;
        *(int *)(state+0x28)=part_alloc_effect_slot(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}
