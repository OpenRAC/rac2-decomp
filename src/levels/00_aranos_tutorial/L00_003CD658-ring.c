#include "common.h"
typedef unsigned int VecBits __attribute__((mode(TI)));
typedef union { VecBits bits; float f[4]; } LocalVec;
extern void func_00282CC0(void *,void *,void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern void func_002AB668(void *,void *,float);
extern void func_002ACDE8(void *,void *,void *);
extern void func_L00_002EBE88(void *,int,int,int,int,int,float,float,float);

/* Draws two rings of glowing points around the object that scroll slowly. */
void func_L00_003CD658(char *obj) {
    struct { LocalVec initial, axis, offset; VecBits ring[32]; } frame;
    char *ctx=*(char **)(obj+0x68);
    char *point=ctx;
    float angle=0.0f, step;
    int n=8;
    int i;
    frame.initial.bits=0;
    frame.initial.f[3]=1.0f;
    frame.initial.f[2]=3.0f;
    frame.axis.f[0]=FastSinOrCosA(*(float *)(obj+0xF8));
    frame.axis.f[1]=FastSinOrCosB(*(float *)(obj+0xF8));
    frame.axis.f[2]=0.0f;
    frame.axis.f[3]=1.0f;
    step=6.283186f/(IntToFloat(9)-1.0f);
    do {
        BuildAxisAngleQuaternion(&frame.offset,&frame.axis,angle);
        angle+=step;
        RotateVectorByQuaternion(point,&frame.initial,&frame.offset);
        FastVecAdd(point,point,obj+0x10);
        *(float *)(point+12)=0.6f;
        point+=16;
    } while(--n>=0);
    *(float *)(ctx+0x200)+=-0.1f;
    if(*(float *)(ctx+0x200)<=-7.0f) *(float *)(ctx+0x200)+=7.0f;
    DrawTwoLayerPolylineRibbon(ctx,0x2B,0x2B,9,0x10400000,0x10400000,0.3f,0.6f,*(float *)(ctx+0x200));
    i=0;
    point=(char *)frame.ring;
    frame.offset.f[0]=FastSinOrCosA(*(float *)(obj+0xF8)+3.141593f)*0.65f;
    frame.offset.f[1]=FastSinOrCosB(*(float *)(obj+0xF8)+3.141593f)*0.65f;
    frame.offset.f[2]=0;
    { char *input=ctx;
    for(;i<9;i++) {
        qcopy(&frame.ring[i],input);
        FastVecAdd(point,&frame.offset,point);
        ((float *)point)[3]=1.0f;
        point+=16; input+=16;
    }
    }
    DrawTwoLayerPolylineRibbon(frame.ring,0x2B,0x2B,9,0x2200000,0x2200000,0.3f,0.6f,*(float *)(ctx+0x200));
}
