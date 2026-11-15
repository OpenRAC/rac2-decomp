#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; f32 f[4]; } BurstVec;
extern s32 D_L01_001B19B0 __attribute__((sda));
extern u8 D_L01_001B1990[8] __attribute__((sda));
extern u8 D_L01_001B1988[8] __attribute__((sda));
extern u8 D_L01_001B1980[8] __attribute__((sda));
extern void func_L00_0033E220(void *,void *,s32,s32,s32,s32,s32,s32,f32,f32);
extern void func_002A7750(void *,s32,s32);
extern s32 func_002A9640(void *,s32,s32);
extern void func_L00_0032A258(void *,void *,void *,void *,s32,s32,s32,s32,s32,s32,s32);
extern void func_L00_00326110(void *,s32,f32);
extern void func_L01_0031A278(void *,void *,f32,f32,f32);
extern void func_0032C700(void *,s32,s32,s32,s32,s32,s32,s32,s32,s32,s32,s32,f32,f32);
extern void func_002ABBB8(void *,void *,void *,f32,f32,s32,s32,s32,f32,f32,f32,f32,s32,f32,s32,s32,s32,s32,s32);
extern void func_00283098(void *,void *,void *);
extern void func_L00_003263D0(void *,void *,f32,s32,s32,void *,f32,u32,s32,f32,f32);
extern void func_0029F338(void *);
/* Waits for a hit, then bursts into sparks and sound and removes itself or stays in a final state. */
void func_L01_00412F18(void *mobyArg) {
    BurstVec offset, tmp, up;
    f32 direction[4] __attribute__((aligned(16)));
    u8 *obj=mobyArg;
    u8 *state=*(u8 **)(obj+0x68);
    s32 i;
    tmp.q=0;
    tmp.f[2]=21.5f * *(f32 *)(obj+0x2C);
    offset.q=tmp.q;
    switch(obj[0x20]) {
    case 0:
        SpawnObjectFollowingEffect(&offset,obj,0x28806020,-1,0,-1,0,0x60,409500.0f,0.0f);
        SpawnObjectFollowingEffect(&offset,obj,0x20806020,-1,1,-1,0,0x60,262500.0f,0.75f);
        SetMobyState(obj,1,-1);
        break;
    case 1:
        if(FindOwnedEffectSlot(obj,0x4010000,0) && !*(s32 *)state) SetMobyState(obj,2,-1);
        obj[0xA8]=255;
        break;
    case 2:
        ExplodeObjectIntoPieces(obj,D_L01_001B1990,D_L01_001B1988,D_L01_001B1980,65535,0,D_L01_001B19B0,1,0xC7F,255,0);
        SpawnScaledBolts(obj,3,1.1f);
        up.q=0; up.f[2]=1.0f/6.0f;
        ComputeMobyLocalPoint(obj,&tmp,offset.f[0],offset.f[1],offset.f[2]);
        SpawnExplosion(&tmp,0,2,2,2,2,2,0,1,0,0,0,*(f32 *)(obj+0x2C),20.0f);
        SpawnExplosionEffects(obj,&up,&tmp,0,0,20,1,1,0,0,9.0f,0.75f,-1,0,0,0,-1,0,0x810001);
        for(i=0;i<4;i++) {
            direction[0]=(i/2*2-1)*(1.0f/30.0f);
            direction[1]=(i%2*2-1)*(1.0f/30.0f);
            direction[2]=1.0f/15.0f;
            matrix_mul_vec3(direction,direction,obj+0xC0);
            SpawnTintedEffects(obj,&tmp,0.25f,3,1,direction,5.0f,0x4080FF00,0,0.75f,1.25f);
        }
        if(D_L01_001B19B0>=0) {
            *(u16 *)(obj+0x7C)=(1<<D_L01_001B19B0)|0x8000;
            SetMobyState(obj,3,-1);
        } else MarkMobySpawned(obj);
        break;
    }
}
