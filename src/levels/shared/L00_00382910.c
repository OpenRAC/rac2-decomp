#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282D30(void *,void *,float);
extern void func_0029F338(void *);
extern unsigned char D_001B8C80[];
extern char *func_L00_0033E220(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void func_002A7750(unsigned char *,int,int);
extern void *func_002A9640(void *,unsigned int,int);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void func_L00_00324F18(char *,char *,float,float,float);
extern void func_L00_002EC248(void *,void *,void *,int,int,float,float,float,float,float);
/* Two complete vectors supply the lower and upper component ranges. */
extern Vector4 D_L00_001AEC90[2] __attribute__((sda));
extern float D_L00_001AEC88[2] __attribute__((sda));
extern float D_L00_001AEC80[2] __attribute__((sda));
extern int D_L00_001AECB0 __attribute__((sda));
/* Updates a Lamp: when it breaks it throws out a burst of sparks and then removes itself. */
void func_L00_00382910(unsigned char *object)
{
    Vector4 velocity,zero,acceleration;
    int *work=FIELD(int *,object,0x68);
    velocity.bits=0; velocity.f[2]=-23;
    switch(object[0x20]) {
    case 0:
        FastVecScale(&velocity,&velocity,FIELD(float,object,0x2C));
        SpawnObjectFollowingEffect(&velocity,object,0x32608080,-1,1,-1,0,96,FIELD(float,object,0x2C)*5250000,FIELD(float,object,0x2C)*15);
        SetMobyState(object,1,-1); break;
    case 1:
        if(FindOwnedEffectSlot(object,0x4010000,0) && !work[0])SetMobyState(object,2,-1);
        object[0xA8]=255; break;
    case 2:
        ExplodeObjectIntoPieces(object,D_L00_001AEC90,D_L00_001AEC88,D_L00_001AEC80,65535,0,D_L00_001AECB0,0,65535,255,0);
        zero.bits=0; LocalOffsetToWorld((char *)object,(char *)&zero,velocity.f[0],velocity.f[1],velocity.f[2]);
        acceleration.bits=0; acceleration.f[2]=-0.083333336f;
        SpawnSparkBurst_L00(object,&velocity,&acceleration,40,0,FIELD(float,object,0x2C)+FIELD(float,object,0x2C),0.20000002f,1,5,1);
        MarkMobySpawned(object); break;
    }
}
