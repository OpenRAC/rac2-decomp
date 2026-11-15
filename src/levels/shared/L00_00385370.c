#include "include_asm.h"
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
extern void func_00283098(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern int func_002A7820(int,int);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern void func_L00_003883B8(char *);
extern void func_L00_0038AA40(char *);
extern void func_L00_00388490(void *,Vector4 *);
extern void func_L00_0038AAD0(void *,Vector4 *);
extern void func_0029FCC0(char *,int,char *);
extern int func_001163B0(void);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282E48(void *,void *);
extern void func_00303210(void *);
extern void func_00303BF8(void *);
extern void func_00303AC8(void *);
extern void func_00302DA0(void *);
extern void func_00304128(void *);
extern void func_00303070(void *);
extern void func_L00_002E6DB8(void (*)(void *),void *);
extern void func_002A7750(unsigned char *,unsigned char,int);
extern int func_002B3868(unsigned char *);
extern float func_002AA548(float *,float *,float,float,float,float);
typedef struct { float x,y,a,b; float pad[4]; } Spark;
extern Spark D_L00_00232AC0[];
/* Runs the five-step cycle that makes the object rise, hold, fall and rest, then redraws it. */
void func_L00_00385370(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        BuildSurfaceControlGrid(object);
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x8C)=FIELD(int,work,0x84);FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            object[0x30]=255;
            for(i=0;i<64;++i) {
                D_L00_00232AC0[i].a=RandomFloatRange(0.5f,2);
                D_L00_00232AC0[i].b=RandomFloatRange(0.002f,0.006f);
            }
        }
        SetMobyState(object,1,-1);return;
    case 1:
        if(SetFirstPendingFlag(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(FastFloatHelperD((int *)(work+0x20)))SetMobyState(object,2,-1);
        StepValueTowardTarget((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(SetFirstPendingFlag(object)){FIELD(int,work,0x20)=FIELD(int,work,12);FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(FastFloatHelperD((int *)(work+0x20)))SetMobyState(object,3,-1);
        break;
    case 3:
        if(SetFirstPendingFlag(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(FastFloatHelperD((int *)(work+0x20)))SetMobyState(object,4,-1);
        StepValueTowardTarget((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(SetFirstPendingFlag(object)){FIELD(int,work,4)=0;FIELD(int,work,0x20)=FIELD(int,work,16);}
        if(FastFloatHelperD((int *)(work+0x20)))SetMobyState(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))UpdateSurfaceWaveTables(object);
    UpdateSurfaceHeights(object);UpdateSurfaceGridMoby(object);SpawnSurfaceEffect(object);
    AddDrawCallbackToList2(DrawSurfaceGrid,object);
}
