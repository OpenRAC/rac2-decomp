#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern void func_002A7750(void *,int,int);
extern float func_00283B98(float,float);
extern char *func_002A9640(void *,int,int);
extern float func_002A96A0(void *,void *);
extern void func_002AB800(void *,void *);
extern void func_002AB8C0(void *,void *);
extern void func_002E5CF8(int,int,void *);
extern void func_002A0488(void *,int,int,int);
extern int func_002A8508(int,int);
extern int func_002A7820(int,int);
extern void func_L00_00321878(void *,int,int,int,int,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern void func_0029F338(void *);
extern int D_L08_001B3AA0 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern int D_L08_002B35C0[];
/* A breakable object with a few hit points: flashes when hit, and when destroyed it bursts into effects. */
void func_L08_0042FCE0(char *moby) {
    char *vars=*(char **)(moby+0x68);
    float hit;
    float offset[4] __attribute__((aligned(16)));
    int effectId;
    switch(*(u8 *)(moby+0x20)) {
    case 0:
        *(s16 *)(vars+0x24)=5;
        *(float *)(vars+0x20)=5.0f;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        *(float *)(moby+0xF8)=FastAddRotations(*(float *)(moby+0xF8),*(float *)(vars+0x64)*0.0002908882452175021f);
        hit=UpdateAimTargetStrength(moby,FindOwnedEffectSlot(moby,0x230000,0));
        if(hit>0.0f) {
            *(u8 *)(vars+0x57)=255;
            *(u8 *)(vars+0x58)=128;
            *(u8 *)(vars+0x59)=128;
            StartColorFade(moby,vars+0x50);
            if(gActiveEmitterCount<4) *(float *)(vars+0x20)-=hit;
        }
        if(*(float *)(vars+0x20)<0.0f) {
            PlayMobySound(0,0,moby);
            SetMobyState(moby,2,-1);
        }
        UpdateColorFade(moby,vars+0x50);
        *(u8 *)(moby+0xA8)=255;
        break;
    case 2:
        set_moby_color(moby,*(u8 *)(vars+0x54),*(u8 *)(vars+0x55),*(u8 *)(vars+0x56));
        if(CountMobysInGroupNotInState(*(u8 *)(moby+0x21),-1)==1) {
            effectId=*(int *)((gCurrentMapIndex << 2)+(char *)D_L08_002B35C0)*35-1;
            SpawnBoltPickups_L00(moby,effectId,effectId,3,-1,RandomIntRange(1,3),0.0f);
        }
        *(u128 *)offset=0;
        offset[0]=0.11666667461395264f; offset[1]=0.06666667014360428f;
        matrix_mul_vec3(offset,offset,moby+0xC0);
        if(*(u8 *)(moby+0x31)) SpawnDebrisForMaskedParts(moby,255,offset,3.0f,6.0f,3.0f,6.0f,255);
        else SpawnDebrisForMaskedParts(moby,170,offset,3.0f,6.0f,3.0f,6.0f,255);
        MarkMobySpawned(moby);
        break;
    }
}
