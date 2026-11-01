#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector direction; u8 *source; u32 mask; u8 kind,enabled; u16 type; float strength; int mode; } ImpactInfo;
typedef struct { Vector previous,normal,start; ImpactInfo impact; } BeamQuery;
typedef struct { u8 reserved[0x18]; u8 *other; u32 reserved1c; Vector position; } HitView;
extern HitView D_L11_001C0D00 __attribute__((nosda));
extern float D_L11_001B1FF4 __attribute__((sda)),D_L11_001B1FF8 __attribute__((sda));
extern float D_L11_001B1FF0 __attribute__((sda));
extern u32 D_L11_001B2000 __attribute__((sda)),D_L11_001B2004 __attribute__((sda));
extern void func_002AFFD8(void *,void *,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern void func_L11_00459640(void *,int,int);
extern void func_002A8BD0(char *,int,int,float);
extern int func_00277F48(void *,int,void *,void *,float);
extern int func_00282948(int *);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_001163B0(void);
extern u8 *func_002C2210(void *,int,u32,float,float,int,int,void *,int,float);
extern void func_0029F338(void *);
extern void func_L11_00459D48(u8 *);

/* Move and test the beam endpoint, then emit its fading or impact particles.
 * The interleaved particle arguments preserve the EE integer/FP register banks. */
void func_L11_004590F0(u8 *object)
{
    BeamQuery query;
    ImpactInfo impact;
    u8 *state=*(u8 **)(object+0x68);

    qcopy(&query.previous,object+0x10);
    func_002AFFD8(object+0x10,&query.normal,1);
    qcopy(&query.start,object+0x10);
    if(object[0x20]==0) {
        func_00282CC0(object+0x10,object+0x10,state+0x40);
        query.impact.source=object;
        query.impact.mask=0x10001;
        query.impact.strength=*(float *)(state+0x64);
        query.impact.mode=1;
        qcopy(&query.impact.direction,state+0x40);
        func_00282F20(&query.impact.direction,&query.impact.direction,1.0f);
        query.impact.direction.f[3]=5627.9248046875f;
        query.impact.kind=1;
        query.impact.enabled=1;
        query.impact.type=*(u16 *)(object+0xAA);
        if(func_002761F8(&query.start,object+0x10,0,object,0)) {
            int same=0;
            if(D_L11_001C0D00.other && *(u8 **)(state+0x50))
                if(*(s16 *)(D_L11_001C0D00.other+0xAA)==*(s16 *)(*(u8 **)(state+0x50)+0xAA)) same=1;
            if(!same) {
            if(!D_L11_001C0D00.other) func_L11_00459640(&D_L11_001C0D00.position,1,0);
            else if(*(int *)(D_L11_001C0D00.other+0x98)) func_L11_00459640(&D_L11_001C0D00.position,1,1);
            func_002A8BD0((char *)&impact,(int)object,0x810001,*(float *)(state+0x64));
            impact.kind=2;impact.enabled=1;
            impact.type=*(u16 *)(*(u8 **)(state+0x50)+0xAA);
            func_00277F48(&D_L11_001C0D00.position,16,object,&impact,0.2f);
            func_0029F338(object);
            return;
            }
        }
    }
    if(func_00282948((int *)(state+0x58))) {
        u8 *position=object+0x10;
        float size;
        int sign,left;
        size=func_002A7878(D_L11_001B1FF4,D_L11_001B1FF8);
        sign=func_002A77E0(2);if(sign==0)sign--;
        left=4;
        do {
            query.impact.direction.f[2]=func_002A7878(-1.0f,1.0f);
            query.impact.direction.f[1]=func_002A7878(-1.0f,1.0f);
            query.impact.direction.f[0]=func_002A7878(-1.0f,1.0f);
            func_00282F20(&query.impact.direction,&query.impact.direction,0.025f);
            query.impact.direction.f[2]=func_002A7878(0,0.1f);
            func_002C2210(position,60,D_L11_001B2000,size*0.35f,size,0,sign,&query.impact.direction,0,D_L11_001B1FF0);
            func_002C2210(position,60,D_L11_001B2004,size*0.245f,size*0.7f,1,sign,&query.impact.direction,0,D_L11_001B1FF0);
            sign=-sign;
        } while(--left>=0);
        func_0029F338(object);
        return;
    }
    if(*(int *)(state+0x58)<16) {
        *(float *)(state+0x60)=func_00283CE0(*(int *)(state+0x58))/func_00283CE0(15);
        if(func_001163B0()%3==0) {
            int sign;
            float size;
            sign=func_002A77E0(2);if(sign==0)sign--;
            size=func_002A7878(D_L11_001B1FF4,D_L11_001B1FF8);
            query.impact.direction.f[2]=func_002A7878(-1.0f,1.0f);
            query.impact.direction.f[1]=func_002A7878(-1.0f,1.0f);
            query.impact.direction.f[0]=func_002A7878(-1.0f,1.0f);
            func_00282F20(&query.impact.direction,&query.impact.direction,0.025f);
            func_002C2210(object+0x10,60,D_L11_001B2000,size*0.05f,size,0,sign,&query.impact.direction,0,D_L11_001B1FF0);
            func_002C2210(object+0x10,60,D_L11_001B2004,size*0.0035f,size*0.035f,1,sign,&query.impact.direction,0,D_L11_001B1FF0);
        }
    }
    if(*(float *)(object+0x10)<2.0f || *(float *)(object+0x10)>1021.0f ||
       *(float *)(object+0x14)<2.0f || *(float *)(object+0x14)>1021.0f ||
       *(float *)(object+0x18)<2.0f || *(float *)(object+0x18)>1021.0f) func_0029F338(object);
    else func_L11_00459D48(object);
}
