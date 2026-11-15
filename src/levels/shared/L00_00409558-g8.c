#include "common.h"
/* Creates object 3790 with copied position/velocity and randomized rotation. */

typedef int Quad __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern int func_002A7820(int,int);
extern float func_002A7940(void),func_002A7878(float,float);
extern void func_002833F0(void *,void *),func_002AB668(void *,void *,float),func_002A0F48(void *);
extern int func_002FED90(void *,int,float,float,float);
extern int D_L00_001B0FA4 __attribute__((sda)),D_L00_001B0FA8 __attribute__((sda));
extern unsigned short D_L00_001B0FC4 __attribute__((sda));
extern float D_L00_001B0FB4 __attribute__((sda)),D_L00_001B0FB8 __attribute__((sda));
char *func_L00_00409558(Quad *position,Quad *velocity,int lifetime,int mode)
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
        *(short *)(state+0x20)=RandomIntRange(D_L00_001B0FA4,D_L00_001B0FA8);
        *(unsigned short *)(object+0x34)|=0x100;
        *(float *)(object+0xF0)=RandomAngle();
        *(float *)(object+0xF4)=RandomAngle();
        *(float *)(object+0xF8)=RandomAngle();
        euler_rotation_basis(object+0xC0,object+0xF0);
        rotation=RandomFloatRange(0.05235988646745682f,0.10471977293491364f);
        BuildAxisAngleQuaternion(state+0x10,object+0xD0,rotation);
        duration=D_L00_001B0FC4;
        *(int *)(state+0x24)=mode;
        *(short *)(state+0x22)=duration+lifetime;
        if(mode!=0) *(float *)(object+0x2C)*=D_L00_001B0FB8;
        else *(float *)(object+0x2C)*=D_L00_001B0FB4;
        *(int *)(state+0x28)=AllocEffectSlot_002FED90(object,0,1.0f,1.0f,1.0f);
        func_002A0F48(object);
    }
    return object;
}
