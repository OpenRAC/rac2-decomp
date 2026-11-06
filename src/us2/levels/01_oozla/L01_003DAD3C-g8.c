/* func_US2_L01_003DAD3C, the USA v2.00 copy of func_L01_003D98E0: the same C, where the snap-back to the attached object moves ahead of the switch, also fires when its state field 0x20 is zero, raises the height only below 0xB8 - 0.2, and clears 0xC4 before re-entering mode 1. */
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

void func_US2_L01_003DAD3C(u8 *m)
{
    Vec oldPos,oldRot,anchor,target,delta,prevRot,prevPos,out;
    u8 *s=*(u8 **)(m+0x68);
    u8 *other;
    u8 *cursor;
    float height;
    float *fieldD0,*fieldD4,*fieldD8,*fieldDC;
    qcopy_nc(oldPos,m+0x10);
    qcopy_nc(oldRot,m+0xF0);
    height=func_L01_003BAFB0();
    if(m[0x20]!=0) {
        u8 *attached;
        if(*(float *)(s+0xB8)+5.0f<height) return;
        attached=*(u8 **)(s+0xC8);
        if(attached!=0 && (attached[0x95]>=7 || *(float *)(*(u8 **)(attached+0x68)+0x20)==0.0f)) {
            *(float *)(m+0x10)=*(float *)(s+0xB0);
            *(float *)(m+0x14)=*(float *)(s+0xB4);
            if(*(float *)(m+0x18)<*(float *)(s+0xB8)-0.2f) *(float *)(m+0x18)=*(float *)(s+0xB8);
            *(int *)(s+0xC4)=0;
            func_002A7750(m,1,-1);
            return;
        }
    }
    switch(m[0x20]) {
    case 0:
        if(0.0f<height) {
            if(*(int *)(s+0xC0)==-1) {
                func_0026FEB8(D_L01_001B0800,*(s16 *)(m+0xAA),*(s16 *)(m+0xB2));
                *(int *)(s+0xC8)=0;
                func_0029F338(m);
                return;
            }
            *(u8 **)(s+0xC8)=D_L01_001B255C+(*(int *)(s+0xC0)<<8);
            qcopy(s+0x90,m+0xF0);
            qzero(s+0xA0);
            qcopy(s+0xB0,m+0x10);
            func_002A7750(m,1,-1);
        }
        break;
    case 1: {
        float limit,secondary;
        qcopy(anchor,D_L01_001B264C[*(int *)(*(u8 **)(*(u8 **)(s+0xC8)+0x68)+0x2CC)].position);
        anchor[2]=*(float *)(m+0x18);
        func_00282F20(target,*(u8 **)(s+0xC8)+0xC0,5.0f);
        func_00282CC0(target,target,*(u8 **)(s+0xC8)+0x10);
        if(((HeroView *)D_00189E20)->mode==0 && ((HeroView *)D_00189E20)->platform==m) {
            float dotX,dotY,y,x,scale;
            func_00282CF0(delta,((HeroView *)D_00189E20)->position,m+0x10);
            dotX=func_00282DB0(delta,m+0xC0);
            dotY=func_00282DB0(delta,m+0xD0);
            scale=D_L01_001B07A8;
            y=-scale*dotY;
            x=scale*dotX;
            *(Quad *)prevRot=*(Quad *)(s+0x90);
            *(Quad *)prevPos=*(Quad *)(m+0x10);
            func_002AA898((float *)(s+0x90),y,(float *)(s+0xA0),D_L01_001B07AC*4.848137450608192e-06f,D_L01_001B07B0,D_L01_001B07B4*0.0002908882452175021f,0);
            func_002AA898((float *)(s+0x94),x,(float *)(s+0xA4),D_L01_001B07AC*4.848137450608192e-06f,D_L01_001B07B0,D_L01_001B07B4*0.0002908882452175021f,0);
            func_L01_00316C48(((HeroView *)D_00189E20)->position,out,m+0x10,prevRot,s+0x90);
        } else {
            func_002AA898((float *)(s+0x90),0.0f,(float *)(s+0xA0),D_L01_001B07B8*4.848137450608192e-06f,D_L01_001B07BC,D_L01_001B07C0*0.0002908882452175021f,0);
            func_002AA898((float *)(s+0x94),0.0f,(float *)(s+0xA4),D_L01_001B07B8*4.848137450608192e-06f,D_L01_001B07BC,D_L01_001B07C0*0.0002908882452175021f,0);
            other=*(u8 **)(s+0xC8);
            if(other!=0 && other[0x20]!=0xFE && other[0x20]!=0xFD && other[0x95]>=2) {
                float dist,dist2;
                func_00282CF0(delta,m+0x10,other+0x10);
                dist=func_00282DF0(delta);
                dist2=func_00282E80(m+0x10,target);
                if(dist2<dist) { func_00282CF0(delta,m+0x10,target); dist=dist2; }
                if(dist<D_L01_001B07C4) {
                    float falloff,anchorDistance,d;
                    dist=D_L01_001B07C4-dist;
                    falloff=dist/(D_L01_001B07C4-D_L01_001B07C8);
                    if(falloff>1.0f) falloff=1.0f;
                    else if(falloff<0.0f) falloff=0.0f;
                    func_00282F20(delta,delta,dist*falloff);
                    func_00282FB8(delta,delta,D_L01_001B07D4*(1.0f/60.0f));
                    anchorDistance=func_00282E80(*(u8 **)(s+0xC8)+0x10,anchor);
                    func_00282CF0(prevRot,m+0x10,anchor);
                    d=func_00282DF0(prevRot)-anchorDistance;
                    d=d/func_00282C48(d);
                    d*=1.0f/60.0f;
                    func_00282F20(prevRot,prevRot,(D_L01_001B07D8*d)*falloff);
                    func_00282CC0(m+0x10,m+0x10,prevRot);
                    func_00282CC0(m+0x10,m+0x10,delta);
                }
            }
        }
        func_00282CF0(delta,s+0xB0,m+0x10);
        fieldD8=(float *)(s+0xD8);
        func_00282D30(delta,delta,D_L01_001B07CC);
        fieldDC=(float *)(s+0xDC); fieldD0=(float *)(s+0xD0);
        func_00282FB8(delta,delta,D_L01_001B07D0*(1.0f/60.0f));
        fieldD4=(float *)(s+0xD4);
        func_00282CC0(m+0x10,m+0x10,delta);
        limit=func_00282E80(m+0x10,*(u8 **)(s+0xC8)+0x10);
        secondary=func_00282E80(m+0x10,target);
        limit=limit<secondary?limit:secondary;
        cursor=0;
        func_002A8600(&cursor,m[0x21],0,0);
        while(cursor!=0) {
            float dist,dist2,falloff;
            func_00282CF0(delta,m+0x10,cursor+0x10);
            dist=func_00282DF0(delta);
            if(dist<D_L01_001B07DC) {
                dist2=func_00282E80(cursor+0x10,*(u8 **)(s+0xC8)+0x10);
                secondary=func_00282E80(m+0x10,target);
                dist2=dist2<secondary?dist2:secondary;
                dist=D_L01_001B07DC-dist;
                falloff=dist/(D_L01_001B07DC-D_L01_001B07E0);
                if(falloff>1.0f) falloff=1.0f;
                else if(falloff<0.0f) falloff=0.0f;
                func_00282F20(delta,delta,dist*falloff);
                func_00282FB8(delta,delta,D_L01_001B07E4*(1.0f/60.0f));
                if(limit<dist2) {
                    float radius;
                    func_00282CF0(cursor+0x10,cursor+0x10,delta);
                    func_00282CF0(prevRot,cursor+0x10,anchor);
                    radius=func_00282DF0(prevRot);
                    if(radius<D_L01_001B07E8) {
                        func_00282F20(prevRot,prevRot,D_L01_001B07E8);
                        func_00282CC0(cursor+0x10,anchor,prevRot);
                    } else if(D_L01_001B07EC<radius) {
                        func_00282F20(prevRot,prevRot,D_L01_001B07EC);
                        func_00282CC0(cursor+0x10,anchor,prevRot);
                    }
                } else func_00282CC0(m+0x10,m+0x10,delta);
            }
            func_002A86E8(&cursor,cursor,0,0);
        }
        {
            float dist;
            func_00282CF0(delta,m+0x10,anchor);
            dist=func_00282DF0(delta);
            if(dist<D_L01_001B07E8) {
                func_00282F20(delta,delta,D_L01_001B07E8);
                func_00282CC0(m+0x10,anchor,delta);
            } else if(D_L01_001B07EC<dist) {
                func_00282F20(delta,delta,D_L01_001B07EC);
                func_00282CC0(m+0x10,anchor,delta);
            }
        }
        *(float *)(m+0x18)=height;
        func_002AEE70(m,fieldD8,fieldDC,0.08f,0.008726648055016994f,-1.0f);
        func_002AEF28(m,fieldD0,fieldD4,0.04363323748111725f,0.007272206246852875f,0.00901753549f);
        *(float *)(m+0xF0)=func_00283B98(*(float *)(s+0x90),*(float *)(m+0xF0));
        *(float *)(m+0xF4)=func_00283B98(*(float *)(s+0x94),*(float *)(m+0xF4));
        func_L01_003D9830(m);
        break;
    }
    case 2:
        if(height-D_L01_001B07F0<*(float *)(m+0x18)) *(float *)(m+0x18)-=D_L01_001B07F4*(1.0f/60.0f);
        if(func_00282948(s+0xC4)) func_002A7750(m,3,-1);
        break;
    case 3:
        if(*(float *)(m+0x18)<height) {
            *(float *)(m+0x18)+=D_L01_001B07F8*(1.0f/60.0f);
            if(height<*(float *)(m+0x18)) {
                *(float *)(m+0x18)=height;
                func_002A7750(m,1,-1);
            }
        }
        break;
    case 4:
    case 5:
        break;
    }
    if(*(float *)(m+0x10)<10.0f) *(float *)(m+0x10)=10.0f;
    if(*(float *)(m+0x10)>1013.0f) *(float *)(m+0x10)=1013.0f;
    if(*(float *)(m+0x14)<10.0f) *(float *)(m+0x14)=10.0f;
    if(*(float *)(m+0x14)>1013.0f) *(float *)(m+0x14)=1013.0f;
    if(*(float *)(m+0x18)<10.0f) *(float *)(m+0x18)=10.0f;
    if(*(float *)(m+0x18)>1013.0f) *(float *)(m+0x18)=1013.0f;
    if(m[0x20]!=2) {
        func_00282CF0(anchor,m+0x10,oldPos);
        func_002AD6F0(s+0x50,anchor,oldRot,m+0xF0);
    }
}
