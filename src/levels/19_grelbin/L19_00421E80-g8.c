#include "names.h"
typedef unsigned char u8;
/* The resident position is copied as a complete 16-byte vector elsewhere. */
extern float D_00189EA0[4];
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks,mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
extern void func_002A7750(u8 *,u8,int);
extern int func_002ACBC8(void *,int);
extern int func_002B3868(u8 *);
extern int func_002E5CF8(int,int,char *);
extern int func_00282948(int *);
extern float func_002AA548(float *,float *,float,float,float,float);
extern float func_00282C48(float);
extern void func_L19_00422238(void *);

/* Trigger the rise, wait and fall cycle while maintaining the attached effects. */
/* Waits for the player to come near, rises up, then slams back down and shakes the screen. Dust puffs are made all the time. */
void func_L19_00421E80(u8 *moby)
{
    char *vars=*(char **)(moby+0x68);
    switch(moby[0x20]) {
    case 0:
        *(int *)(vars+0x0C)=0;
        *(int *)(vars+0x24)=0;
        *(int *)(vars+0x54)=0;
        *(float *)(vars+0x10)=0.55f;
        *(float *)(vars+0x14)=0.01f;
        *(float *)(vars+0x18)=0.05f;
        *(int *)(vars+0x1C)=*(int *)(vars+0x5C)+60;
        *(int *)(vars+0x20)=60;
        *(float *)(vars+0x28)=1.0f;
        *(int *)(vars+0x2C)=3;
        *(float *)(vars+0x30)=105000.0f;
        *(unsigned int *)(vars+0x34)=0x80803C14;
        *(unsigned int *)(vars+0x38)=0x60400000;
        *(int *)(vars+0x3C)=10;
        *(int *)(vars+0x40)=55;
        *(int *)(vars+0x44)=1;
        *(float *)(vars+0x48)=210000.0f;
        *(unsigned int *)(vars+0x4C)=0x80808080;
        *(unsigned int *)(vars+0x50)=0x40804040;
        *(int *)(vars+0x58)=40;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        if (IsPointInCuboid(gHeroPosition,*(int *)vars)) SetMobyState(moby,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) PlayMobySound(0,0,(char *)moby);
        if (FastFloatHelperD((int *)(vars+0x1C))) SetMobyState(moby,3,-1);
        *(float *)(vars+0x24)+=(float)(60-*(int *)(vars+0x1C))*0.25f;
        break;
    case 3:
        if (*(float *)(moby+0x18)<*(float *)(vars+8)) SetMobyState(moby,4,-1);
        *(float *)(vars+0x24)+=1.5f;
        StepValueTowardTarget((float *)(moby+0x18),(float *)(vars+0x0C),
            *(float *)(vars+8)-20.0f,*(float *)(vars+0x14),99999.0f,*(float *)(vars+0x10));
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            PlayMobySound(1,0,(char *)moby);
            D_L19_001B9900.strength=1.0f;
            D_L19_001B9900.ticks=20;
            D_L19_001B9900.mode=0;
        }
        if (FloatAbs((*(float *)(moby+0x18)-*(float *)(vars+8))+*(float *)(vars+0x28))<0.03f)
            SetMobyState(moby,5,-1);
        StepValueTowardTarget((float *)(moby+0x18),(float *)(vars+0x0C),
            *(float *)(vars+8)-*(float *)(vars+0x28),99999.0f,*(float *)(vars+0x18),*(float *)(vars+0x10));
        break;
    case 5:
        break;
    }
    SpawnDustPuffs(moby);
}
