#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283C80(float,float);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(float *,float,float,float);
extern char *func_002C2210(void *,int,unsigned int,int,int,void *,int,float,float,float);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *,void *);
extern void func_002A7398(signed char *,int,int);
extern void func_002AEC18(void *,int);
extern void func_002833F0(void *,void *);
extern void func_002FE8D8(void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00283198(float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern void func_00282C88(void *);
extern int func_002FEC78(unsigned char *,unsigned int);
extern int func_002FED90(void *,void *,float,float,float);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern int func_002A7820(int,int);
extern float func_00283248(float,float);
extern float func_00282E20(void *);
extern float func_00282E80(void *,void *);
extern float func_00283B98(float,float);
extern char *func_L00_00333F90(void *,void *);
extern char *func_002BD8B0(void *,void *,unsigned int,unsigned int,int,int,float);
extern void func_L00_0038B888(Vector4 *,int);
extern unsigned long func_0027C878(int);
extern void func_00283410(void *,void *);
extern void func_00280B90(void *,void *,int);
extern unsigned char D_001B8C80[];
extern void func_L00_003883B8(char *);
extern void func_L00_0038AA40(char *);
typedef struct { char pad[0x20]; Vector4 position; } CollisionResult;
extern CollisionResult D_L00_001BF200;
extern Vector4 D_L00_001B8DC0;
/* Throws a burst of sparks and puffs from the spot where the weapon hit something. */
void func_L00_0038BA80(char *owner)
{
    Vector4 velocity,position;
    float tilt,unusedHeading,angle;
    int i;
    FastVecSub(&velocity,&gCameraPosition_L00,&gCollisionResult.position);
    tilt=-FastMatrixHelperA(vec_length_xy(&velocity),velocity.f[2]);
    unusedHeading=FastMatrixHelperA(velocity.f[0],velocity.f[1]);
    for(i=19;i>=0;--i) {
        angle=FastAddRotations(RandomSignedFloatRange(0,3.1415927f),tilt);
        BuildSphericalOffset(velocity.f,0.2f,FastAddRotations(RandomSignedFloatRange(0,3.1415927f),tilt),angle);
        FastVecScale(&position,&velocity,RandomFloatRange(1,3));
        FastVecAdd(&position,&position,&gCollisionResult.position);
        SpawnStreakEffect_L00(&position,&velocity);
    }
    for(i=9;i>=0;--i) {
        position.f[0]=gCollisionResult.position.f[0]+RandomSignedFloatRange(0,0.1f);
        position.f[1]=gCollisionResult.position.f[1]+RandomSignedFloatRange(0,0.1f);
        position.f[2]=gCollisionResult.position.f[2]+RandomSignedFloatRange(0,0.1f);
        angle=FastAddRotations(RandomSignedFloatRange(0,3.1415927f),tilt);
        BuildSphericalOffset(velocity.f,0.05f,FastAddRotations(RandomSignedFloatRange(0,3.1415927f),tilt),angle);
        SpawnTrailingSparkParticle(&position,&velocity,0x4F007FFF,0x1FFFFFFF,RandomIntRange(10,20),1,20000);
    }
    if(FIELD(short,FIELD(char *,owner,0x68),0x78)==43) SpawnSparkBurst_L00_2(&gCollisionResult.position,10);
}
