#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void func_0029F338(void *);
extern int D_L18_001B1BB0 __attribute__((sda));
extern int D_L18_001B1B88 __attribute__((sda));
extern int D_L18_001B1B80 __attribute__((sda));
extern int D_L18_001B1B90 __attribute__((sda));
extern int func_002A77E0(int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00283098(void *,void *,void *);
extern void *func_L06_00463D40(void *,void *,void *,int,float,float);
/* Updates a breakable object (moby class 4486): when it is hit, it spawns a handful of debris pieces and disappears. */
void func_L18_0043CAF8(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *hit;
    int n, i;
    float pointA[4] __attribute__((aligned(16))), pointB[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(moby[0x20]) {
    case 0: SetMobyState(moby,1,-1); break;
    case 1:
        hit=FindOwnedEffectSlot(moby,0x4010000,0);
        if(hit && !*(int *)vars) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=0.75f;
            FastVecScale(pointA,hit+0x10,RandomFloatRange(6.0f,8.0f));
            qcopy(pointB,pointA);
            FastVecSub(pointA,pointA,spread);
            FastVecAdd(pointB,pointB,spread);
            ExplodeObjectIntoPieces(moby,pointA,&D_L18_001B1B88,&D_L18_001B1B80,65535,-1,D_L18_001B1BB0,9,2,255,0);
            SetMobyState(moby,2,-1);
        }
        moby[0xA8]=255;
        break;
    case 2:
        ExplodeObjectIntoPieces(moby,&D_L18_001B1B90,&D_L18_001B1B88,&D_L18_001B1B80,65535,0,D_L18_001B1BB0,6,61,255,0);
        n=RandomIntBelow(5);
        ComputeMobyLocalPoint(moby,pointA,0.35f,0.0f,1.8f);
        for(i=0;i<n;i++) {
            float x,y;
            pointB[0]=RandomFloatRange(8.0f,12.0f)*(1.0f/60.0f);
            pointB[1]=(2*i-n+1)*(1.0f/15.0f);
            pointB[2]=RandomFloatRange(0.0f,2.0f)*(1.0f/60.0f);
            matrix_mul_vec3(pointB,pointB,moby+0xC0);
            x=RandomFloatRange(0.75f,1.25f);
            y=RandomFloatRange(0.75f,1.25f);
            SpawnSparkParticleMoby(moby,pointA,pointB,1,x,y);
        }
        MarkMobySpawned(moby);
        break;
    }
}
