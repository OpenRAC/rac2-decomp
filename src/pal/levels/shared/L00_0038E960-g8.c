#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void func_002AF000(float *,float,float,float);
extern int func_002A7820(int,int);
extern float func_00283248(float,float);
extern float func_00282E20(void *);
extern float func_00283B98(float,float);
extern char *func_L00_00333F90(void *,void *);
extern char *func_002BD8B0(void *,void *,unsigned int,unsigned int,int,int,float);
extern void func_PAL_L00_0038E960(Vector4 *,int);
typedef struct { char pad[0x20]; Vector4 position; } CollisionResult;
extern CollisionResult D_L00_001BF200;
extern Vector4 D_L00_001B8DC0;

void func_PAL_L00_0038EB58(char *owner)
{
    Vector4 velocity,position;
    float tilt,unusedHeading,angle;
    int i;
    func_00282CF0(&velocity,&D_L00_001B8DC0,&D_L00_001BF200.position);
    tilt=-func_00283248(func_00282E20(&velocity),velocity.f[2]);
    unusedHeading=func_00283248(velocity.f[0],velocity.f[1]);
    for(i=19;i>=0;--i) {
        angle=func_00283B98(func_002A78D8(0,3.1415927f),tilt);
        func_002AF000(velocity.f,0.2f,func_00283B98(func_002A78D8(0,3.1415927f),tilt),angle);
        func_00282D30(&position,&velocity,func_002A7878(1,3));
        func_00282CC0(&position,&position,&D_L00_001BF200.position);
        func_L00_00333F90(&position,&velocity);
    }
    for(i=9;i>=0;--i) {
        position.f[0]=D_L00_001BF200.position.f[0]+func_002A78D8(0,0.1f);
        position.f[1]=D_L00_001BF200.position.f[1]+func_002A78D8(0,0.1f);
        position.f[2]=D_L00_001BF200.position.f[2]+func_002A78D8(0,0.1f);
        angle=func_00283B98(func_002A78D8(0,3.1415927f),tilt);
        func_002AF000(velocity.f,0.05f,func_00283B98(func_002A78D8(0,3.1415927f),tilt),angle);
        func_002BD8B0(&position,&velocity,0x4F007FFF,0x1FFFFFFF,func_002A7820(8,17),1,20000);
    }
    if(FIELD(short,FIELD(char *,owner,0x68),0x78)==43) func_PAL_L00_0038E960(&D_L00_001BF200.position,10);
}
