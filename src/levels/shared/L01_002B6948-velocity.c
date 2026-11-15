#include "common.h"

typedef int VelocityQuad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[240];
    float xf0;
    float xf4;
    float xf8;
    unsigned char padfc[120];
    float x174;
    float x178;
    unsigned char pad17c[36];
    float x1a0;
    unsigned char pad1a4[12];
    float x1b0;
    float x1b4;
    unsigned char pad1b8[207];
    unsigned char x287;
    unsigned char pad288[194];
    short x34a;
    unsigned char pad34c[472];
    short x524;
    unsigned char pad526[3886];
    short x1454;
    unsigned char pad1456[3646];
    int x2294;
    unsigned char pad2298[4];
    int x229c;
    unsigned char pad22a0[35];
    unsigned char x22c3;
} PlayerVelocityState;
extern PlayerVelocityState D_00189E20;
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E20(void *);
extern float func_L00_002D3A58(void *);
extern float func_00282DB0(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F70(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern void func_L00_002D3B58(void *,void *,float);
extern void func_L00_002D3BD8(void *,void *,float);
extern float func_L00_002B5590(void *);

/* Approach the requested velocity, increasing acceleration when reversing direction. */
void func_L01_002B6948(float rate) {
    float targetVelocity[4] __attribute__((aligned(16)));
    float sourceVec[4] __attribute__((aligned(16)));
    float currentDir[4] __attribute__((aligned(16)));
    float angle,speed,alignment,targetLength,currentLength;
    switch(gHeroState.x22c3) {
    case 0:
        angle=gHeroState.x1a0;speed=gHeroState.x1b0;
        if(gHeroState.x229c==4 && gHeroState.x524 && gHeroState.x287) speed=0.0833333358f;
        if(gHeroState.x34a && gHeroState.x2294==14 && speed>0.0166666675f) speed=0.0166666675f;
        targetVelocity[0]=FastSinOrCosA(angle)*speed;
        targetVelocity[1]=FastSinOrCosB(angle)*speed;
        targetVelocity[2]=gHeroState.xf8;
        alignment=-(gHeroState.xf0*targetVelocity[0]+gHeroState.xf4*targetVelocity[1]);
        targetLength=vec_length_xy(targetVelocity);currentLength=vec_length_xy((char *)&gHeroState+0xf0);
        if(targetLength==0.0f || currentLength==0.0f) alignment=0.0f;
        else {
            alignment/=targetLength;
            alignment/=currentLength;
        }
        alignment+=1.0f;
        alignment*=1.5f;
        if(alignment>3.0f) alignment=3.0f;
        if(alignment<1.0f) alignment=1.0f;
        rate*=alignment;
        FastVecSub(targetVelocity,targetVelocity,(char *)&gHeroState+0xf0);
        if(vec_length_xy(targetVelocity)>rate) FastVectorNormalizeHelper(targetVelocity,targetVelocity,rate);
        FastVecAdd((char *)&gHeroState+0xf0,(char *)&gHeroState+0xf0,targetVelocity);
        *(VelocityQuad *)sourceVec=*(VelocityQuad *)((char *)&gHeroState+0xa60);
        gHeroState.x1b4=gHeroState.x178-GetSpeedAlongHeroForward(sourceVec);
        if(gHeroState.x1454) gHeroState.x1b4=gHeroState.x174;
        break;
    case 1:case 2:
        *(VelocityQuad *)sourceVec=*(VelocityQuad *)((char *)&gHeroState+0x190);speed=gHeroState.x1b0;
        SetViewSpaceHeight(targetVelocity,sourceVec,0.0f);
        vec_scale_to_length(targetVelocity,targetVelocity,speed);
        SetViewSpaceHeight(currentDir,(char *)&gHeroState+0xf0,0.0f);
        alignment=-FastVecDot(currentDir,targetVelocity);
        targetLength=GetViewSpaceVectorLength(targetVelocity);currentLength=GetViewSpaceVectorLength((char *)&gHeroState+0xf0);
        if(targetLength==0.0f || currentLength==0.0f) alignment=0.0f;
        else {
            alignment/=targetLength;
            alignment/=currentLength;
        }
        alignment+=1.0f;
        alignment*=1.5f;
        if(alignment>3.0f) alignment=3.0f;
        if(alignment<1.0f) alignment=1.0f;
        rate*=alignment;
        FastVecSub(targetVelocity,targetVelocity,(char *)&gHeroState+0xf0);
        SetViewSpaceHeight(targetVelocity,targetVelocity,0.0f);
        if(GetViewSpaceVectorLength(targetVelocity)>rate) SetViewSpaceVectorLength(targetVelocity,targetVelocity,rate);
        FastVecAdd((char *)&gHeroState+0xf0,(char *)&gHeroState+0xf0,targetVelocity);
        gHeroState.x1b4=gHeroState.x178;
        if(gHeroState.x1454) gHeroState.x1b4=gHeroState.x174;
        break;
    }
}
