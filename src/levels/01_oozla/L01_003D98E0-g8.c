#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
extern float func_L01_003BAFB0(void);
extern void func_0026FEB8(const char *, ...);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E80(void *, void *);
extern float func_00282C48(float);
extern void func_00282FB8(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_002AA898(float *position, float target, float *velocity, float acceleration, float damping, float limit, int direction);
extern void func_L01_00316C48(void *, void *, void *, void *, void *);
extern int func_002A8600(void *, int, int, int);
extern int func_002A86E8(void *, void *, int, int);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern void func_L01_003D9830(void *);
extern int func_00282948(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern u8 *D_L01_001B255C __attribute__((sda));
typedef struct {
    u8 pad00[0x30];
    Vec position;
    u8 pad40[0x40];
} AnchorRecord;
extern AnchorRecord *D_L01_001B264C;
typedef struct {
    u8 pad00[0x80];
    Vec position;
    u8 pad90[0x33C - 0x90];
    u8 *platform;
    u8 pad340[0x34E - 0x340];
    s16 mode;
} HeroView;
extern u8 D_00189E20[];
extern char D_L01_001B0800[];
extern float D_L01_001B07A8 __attribute__((sda));
extern float D_L01_001B07AC __attribute__((sda));
extern float D_L01_001B07B0 __attribute__((sda));
extern float D_L01_001B07B4 __attribute__((sda));
extern float D_L01_001B07B8 __attribute__((sda));
extern float D_L01_001B07BC __attribute__((sda));
extern float D_L01_001B07C0 __attribute__((sda));
extern float D_L01_001B07C4 __attribute__((sda));
extern float D_L01_001B07C8 __attribute__((sda));
extern float D_L01_001B07CC __attribute__((sda));
extern float D_L01_001B07D0 __attribute__((sda));
extern float D_L01_001B07D4 __attribute__((sda));
extern float D_L01_001B07D8 __attribute__((sda));
extern float D_L01_001B07DC __attribute__((sda));
extern float D_L01_001B07E0 __attribute__((sda));
extern float D_L01_001B07E4 __attribute__((sda));
extern float D_L01_001B07E8 __attribute__((sda));
extern float D_L01_001B07EC __attribute__((sda));
extern float D_L01_001B07F0 __attribute__((sda));
extern float D_L01_001B07F4 __attribute__((sda));
extern float D_L01_001B07F8 __attribute__((sda));

/* Floating platform. It bobs on the water, tilts under the hero and is pushed away from nearby platforms. */
void func_L01_003D98E0(u8 *moby)
{
    Vec oldPos,oldRot,anchor,target,delta,prevRot,prevPos,out;
    u8 *vars=*(u8 **)(moby+0x68);
    u8 *other;
    u8 *cursor;
    float height;
    float *fieldD0,*fieldD4,*fieldD8,*fieldDC;
    qcopy_nc(oldPos,moby+0x10);
    qcopy_nc(oldRot,moby+0xF0);
    height=GetWaterHeight();
    if(moby[0x20]!=0 && *(float *)(vars+0xB8)+5.0f<height) return;
    switch(moby[0x20]) {
    case 0:
        if(0.0f<height) {
            if(*(int *)(vars+0xC0)==-1) {
                STUB_printf(D_L01_001B0800,*(s16 *)(moby+0xAA),*(s16 *)(moby+0xB2));
                *(int *)(vars+0xC8)=0;
                MarkMobySpawned(moby);
                return;
            }
            *(u8 **)(vars+0xC8)=gMobyTable_L01+(*(int *)(vars+0xC0)<<8);
            qcopy(vars+0x90,moby+0xF0);
            qzero(vars+0xA0);
            qcopy(vars+0xB0,moby+0x10);
            SetMobyState(moby,1,-1);
        }
        break;
    case 1: {
        float limit,secondary;
        u8 *otherState,*attached;
        attached=*(u8 **)(vars+0xC8);
        otherState=*(u8 **)(attached+0x68);
        if(attached!=0 && attached[0x95]>=7) {
            *(float *)(moby+0x10)=*(float *)(vars+0xB0);
            *(float *)(moby+0x14)=*(float *)(vars+0xB4);
            if(*(float *)(moby+0x18)<*(float *)(vars+0xB8)) *(float *)(moby+0x18)=*(float *)(vars+0xB8);
            break;
        }
        qcopy(anchor,D_L01_001B264C[*(int *)(otherState+0x2CC)].position);
        anchor[2]=*(float *)(moby+0x18);
        vec_scale_to_length(target,*(u8 **)(vars+0xC8)+0xC0,5.0f);
        FastVecAdd(target,target,*(u8 **)(vars+0xC8)+0x10);
        if(((HeroView *)gHeroState)->mode==0 && ((HeroView *)gHeroState)->platform==moby) {
            float dotX,dotY,y,x,scale;
            FastVecSub(delta,((HeroView *)gHeroState)->position,moby+0x10);
            dotX=FastVecDot(delta,moby+0xC0);
            dotY=FastVecDot(delta,moby+0xD0);
            scale=D_L01_001B07A8;
            y=-scale*dotY;
            x=scale*dotX;
            *(Quad *)prevRot=*(Quad *)(vars+0x90);
            *(Quad *)prevPos=*(Quad *)(moby+0x10);
            ApproachWithVelocity((float *)(vars+0x90),y,(float *)(vars+0xA0),D_L01_001B07AC*4.848137450608192e-06f,D_L01_001B07B0,D_L01_001B07B4*0.0002908882452175021f,0);
            ApproachWithVelocity((float *)(vars+0x94),x,(float *)(vars+0xA4),D_L01_001B07AC*4.848137450608192e-06f,D_L01_001B07B0,D_L01_001B07B4*0.0002908882452175021f,0);
            TransformOffsetByTwoMatrices(((HeroView *)gHeroState)->position,out,moby+0x10,prevRot,vars+0x90);
        } else {
            ApproachWithVelocity((float *)(vars+0x90),0.0f,(float *)(vars+0xA0),D_L01_001B07B8*4.848137450608192e-06f,D_L01_001B07BC,D_L01_001B07C0*0.0002908882452175021f,0);
            ApproachWithVelocity((float *)(vars+0x94),0.0f,(float *)(vars+0xA4),D_L01_001B07B8*4.848137450608192e-06f,D_L01_001B07BC,D_L01_001B07C0*0.0002908882452175021f,0);
            other=*(u8 **)(vars+0xC8);
            if(other!=0 && other[0x20]!=0xFE && other[0x20]!=0xFD && other[0x95]>=2) {
                float dist,dist2;
                FastVecSub(delta,moby+0x10,other+0x10);
                dist=FastVecLength(delta);
                dist2=vec_distance_xy(moby+0x10,target);
                if(dist2<dist) { FastVecSub(delta,moby+0x10,target); dist=dist2; }
                if(dist<D_L01_001B07C4) {
                    float falloff,anchorDistance,d;
                    dist=D_L01_001B07C4-dist;
                    falloff=dist/(D_L01_001B07C4-D_L01_001B07C8);
                    if(falloff>1.0f) falloff=1.0f;
                    else if(falloff<0.0f) falloff=0.0f;
                    vec_scale_to_length(delta,delta,dist*falloff);
                    FastVectorDivideHelper(delta,delta,D_L01_001B07D4*(1.0f/60.0f));
                    anchorDistance=vec_distance_xy(*(u8 **)(vars+0xC8)+0x10,anchor);
                    FastVecSub(prevRot,moby+0x10,anchor);
                    d=FastVecLength(prevRot)-anchorDistance;
                    d=d/FloatAbs(d);
                    d*=1.0f/60.0f;
                    vec_scale_to_length(prevRot,prevRot,(D_L01_001B07D8*d)*falloff);
                    FastVecAdd(moby+0x10,moby+0x10,prevRot);
                    FastVecAdd(moby+0x10,moby+0x10,delta);
                }
            }
        }
        FastVecSub(delta,vars+0xB0,moby+0x10);
        fieldD8=(float *)(vars+0xD8);
        FastVecScale(delta,delta,D_L01_001B07CC);
        fieldDC=(float *)(vars+0xDC); fieldD0=(float *)(vars+0xD0);
        FastVectorDivideHelper(delta,delta,D_L01_001B07D0*(1.0f/60.0f));
        fieldD4=(float *)(vars+0xD4);
        FastVecAdd(moby+0x10,moby+0x10,delta);
        limit=vec_distance_xy(moby+0x10,*(u8 **)(vars+0xC8)+0x10);
        secondary=vec_distance_xy(moby+0x10,target);
        limit=limit<secondary?limit:secondary;
        cursor=0;
        GetFirstMobyInGroup(&cursor,moby[0x21],0,0);
        while(cursor!=0) {
            float dist,dist2,falloff;
            FastVecSub(delta,moby+0x10,cursor+0x10);
            dist=FastVecLength(delta);
            if(dist<D_L01_001B07DC) {
                dist2=vec_distance_xy(cursor+0x10,*(u8 **)(vars+0xC8)+0x10);
                secondary=vec_distance_xy(moby+0x10,target);
                dist2=dist2<secondary?dist2:secondary;
                dist=D_L01_001B07DC-dist;
                falloff=dist/(D_L01_001B07DC-D_L01_001B07E0);
                if(falloff>1.0f) falloff=1.0f;
                else if(falloff<0.0f) falloff=0.0f;
                vec_scale_to_length(delta,delta,dist*falloff);
                FastVectorDivideHelper(delta,delta,D_L01_001B07E4*(1.0f/60.0f));
                if(limit<dist2) {
                    float radius;
                    FastVecSub(cursor+0x10,cursor+0x10,delta);
                    FastVecSub(prevRot,cursor+0x10,anchor);
                    radius=FastVecLength(prevRot);
                    if(radius<D_L01_001B07E8) {
                        vec_scale_to_length(prevRot,prevRot,D_L01_001B07E8);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    } else if(D_L01_001B07EC<radius) {
                        vec_scale_to_length(prevRot,prevRot,D_L01_001B07EC);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    }
                } else FastVecAdd(moby+0x10,moby+0x10,delta);
            }
            GetNextMobyInGroup(&cursor,cursor,0,0);
        }
        {
            float dist;
            FastVecSub(delta,moby+0x10,anchor);
            dist=FastVecLength(delta);
            if(dist<D_L01_001B07E8) {
                vec_scale_to_length(delta,delta,D_L01_001B07E8);
                FastVecAdd(moby+0x10,anchor,delta);
            } else if(D_L01_001B07EC<dist) {
                vec_scale_to_length(delta,delta,D_L01_001B07EC);
                FastVecAdd(moby+0x10,anchor,delta);
            }
        }
        *(float *)(moby+0x18)=height;
        UpdateWrappedAngleOffset(moby,fieldD8,fieldDC,0.08f,0.008726648055016994f,-1.0f);
        ScaleOwnerWordsByAngles(moby,fieldD0,fieldD4,0.04363323748111725f,0.007272206246852875f,0.00901753549f);
        *(float *)(moby+0xF0)=FastAddRotations(*(float *)(vars+0x90),*(float *)(moby+0xF0));
        *(float *)(moby+0xF4)=FastAddRotations(*(float *)(vars+0x94),*(float *)(moby+0xF4));
        SinkPlatformWhenHit(moby);
        break;
    }
    case 2:
        if(height-D_L01_001B07F0<*(float *)(moby+0x18)) *(float *)(moby+0x18)-=D_L01_001B07F4*(1.0f/60.0f);
        if(FastFloatHelperD(vars+0xC4)) SetMobyState(moby,3,-1);
        break;
    case 3:
        if(*(float *)(moby+0x18)<height) {
            *(float *)(moby+0x18)+=D_L01_001B07F8*(1.0f/60.0f);
            if(height<*(float *)(moby+0x18)) {
                *(float *)(moby+0x18)=height;
                SetMobyState(moby,1,-1);
            }
        }
        break;
    case 4:
    case 5:
        break;
    }
    if(*(float *)(moby+0x10)<10.0f) *(float *)(moby+0x10)=10.0f;
    if(*(float *)(moby+0x10)>1013.0f) *(float *)(moby+0x10)=1013.0f;
    if(*(float *)(moby+0x14)<10.0f) *(float *)(moby+0x14)=10.0f;
    if(*(float *)(moby+0x14)>1013.0f) *(float *)(moby+0x14)=1013.0f;
    if(*(float *)(moby+0x18)<10.0f) *(float *)(moby+0x18)=10.0f;
    if(*(float *)(moby+0x18)>1013.0f) *(float *)(moby+0x18)=1013.0f;
    if(moby[0x20]!=2) {
        FastVecSub(anchor,moby+0x10,oldPos);
        CombineTransformsAndStore(vars+0x50,anchor,oldRot,moby+0xF0);
    }
}
