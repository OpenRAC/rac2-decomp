#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282D30(void *,void *,float);
extern void func_0029F338(void *);
extern char *func_L00_0033E220(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void func_002A7750(unsigned char *,int,int);
extern void *func_002A9640(void *,unsigned int,int);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void func_L00_00324F18(char *,char *,float,float,float);
extern void func_PAL_L00_002ED7E8(void *,void *,void *,int,int,float,float,float,float,float);
extern Vector4 D_L00_001AEC90[2] __attribute__((sda));
extern float D_L00_001AEC88[2] __attribute__((sda));
extern float D_L00_001AEC80[2] __attribute__((sda));
extern int D_L00_001AECB0 __attribute__((sda));

void func_PAL_L00_00385710(unsigned char *object)
{
    Vector4 velocity,zero,acceleration;
    int *work=FIELD(int *,object,0x68);
    velocity.bits=0; velocity.f[2]=-23;
    switch(object[0x20]) {
    case 0:
        func_00282D30(&velocity,&velocity,FIELD(float,object,0x2C));
        func_L00_0033E220(&velocity,object,0x32608080,-1,1,-1,0,96,FIELD(float,object,0x2C)*5250000,FIELD(float,object,0x2C)*15);
        func_002A7750(object,1,-1); break;
    case 1:
        if(func_002A9640(object,0x4010000,0) && !work[0])func_002A7750(object,2,-1);
        object[0xA8]=255; break;
    case 2:
        func_PAL_L00_0032C328(object,D_L00_001AEC90,D_L00_001AEC88,D_L00_001AEC80,65535,0,D_L00_001AECB0,0,65535,255,0);
        zero.bits=0; func_L00_00324F18((char *)object,(char *)&zero,velocity.f[0],velocity.f[1],velocity.f[2]);
        acceleration.bits=0; acceleration.f[2]=-0.10000001f;
        func_PAL_L00_002ED7E8(object,&velocity,&acceleration,40,0,FIELD(float,object,0x2C)+FIELD(float,object,0x2C),0.24000001f,1,5,1);
        func_0029F338(object); break;
    }
}
