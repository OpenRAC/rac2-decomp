#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
#define S16(p,o) (*(short *)((p)+(o)))
extern u8 D_00189E20[],D_00189EA0[];
extern float D_001A7928;
extern int func_002ACBC8(void *,int);
extern void func_00282CF0(void *,void *,void *),func_00282D30(void *,void *,float);
extern int func_00283CF0(float);
extern float func_00283CE0(int),func_00283198(float);
extern void func_L00_002E6DB8(void (*)(void *),void *);
extern Quad D_L01_001B2FC0 SDATA(D_L01_001B2FC0);
extern u8 D_L01_001B94C0[];
extern u8 *D_L01_001B264C;
/* Bounded views of the two accessed layers, not whole-global extent claims. */
typedef struct { float u, v; } LayerPair;
extern LayerPair D_L01_001B2FD0[] MACRO_ADDR;
typedef struct { float speed[2]; } LayerSpeedPrefix;
extern LayerSpeedPrefix D_L01_001AFDF0 SDATA(D_L01_001AFDF0);
/* Retail reads the scroll speeds' u through GP and v through an absolute address. */
extern LayerPair D_L01_001AFE00[] MACRO_ADDR;
extern LayerPair D_L01_001AFE00_gp[] SDATA(D_L01_001AFE00);
extern float D_L01_001AFE18 __attribute__((sda));
extern float D_L01_001AFE1C __attribute__((sda));

/* Leading part of the ocean state: two contact moby ids at 0x30. */
typedef struct { char pad0[0x30]; int contacts[2]; } OceanContacts;
typedef struct { char pad0[0x1FE]; short f1FE; char pad200[0x2294-0x200]; int f2294; } ResidentE20;
#define RES ((ResidentE20 *)D_00189E20)
extern int D_L01_001B2088;
extern float *D_L01_001AA174;
extern void func_L01_003BAFB8(void *);
/*
 * Ocean update, the counterpart of RAC1's ocean_pokitaru_update (homing_missile_and_water_sheet.c):
 * returns early when func_002ACBC8 accepts one of the two ids at state+0x30, takes the tide
 * base from the first accepted region id at state+0x40, scrolls the two wave layers with the
 * camera and the time, keeps their offsets in -1..1, sets the tide height and registers the
 * draw callback func_L01_003BAFB8. The `1.0f < x || x < 1.0f` tests are as written in RAC1.
 */
void func_L01_003BB9D0(u8 *object)
{
    u8 *state=*(u8 **)(object+0x68);
    float delta[4] __attribute__((aligned(16))),scaled[4] __attribute__((aligned(16)));
    int i,blocked,id;
    int *regions;
    float rate,divisor;
    if(object[0x20]==0) {
        object[0x20]=1; object[0x30]=255;
        I32(state,0)=0x80103030; I32(state,4)=0x800c1006;
        I32(state,0xc)=0x50106060; I32(state,0x10)=0x106060;
        F32(state,0x28)=224.0f;
        for(i=0;i<2;i++) { D_L01_001B2FD0[i].u=0.0f; D_L01_001B2FD0[i].v=0.0f; }
        qcopy(&D_L01_001B2FC0, D_L01_001B94C0);
        D_L01_001AFE1C=F32(state,0x14);
        return;
    }
    blocked=0;
    for(i=0;i<2;i++) {
        id=((OceanContacts *)state)->contacts[i];
        if(id!=-1) {
            if(RES->f2294==28 && func_002ACBC8(D_L01_001B94C0,id)) {
                RES->f1FE=0;
                blocked=1; break;
            }
            if(func_002ACBC8(D_00189EA0,((OceanContacts *)state)->contacts[i])) {
                S16(D_00189EA0,0x17e)=0;
                blocked=1; break;
            }
        }
    }
    if(blocked) return;
    D_L01_001AFE1C=F32(state,0x14);
    regions=(int *)(state+0x40);
    for(i=0;i<8;i++) {
        if(regions[i]==-1) continue;
        if(RES->f2294==28 && func_002ACBC8(D_L01_001B94C0,regions[i])) {
            D_L01_001AFE1C=F32(D_L01_001B264C+regions[i]*128,0x38)+0.15f;
            break;
        }
        if(func_002ACBC8(D_00189EA0,regions[i])) {
            D_L01_001AFE1C=F32(D_L01_001B264C+regions[i]*128,0x38)+0.15f;
            break;
        }
    }
    RES->f1FE=2;
    func_00282CF0(delta,D_L01_001B94C0,&D_L01_001B2FC0);
    qcopy(&D_L01_001B2FC0, D_L01_001B94C0);
    if(!(F32(state,0x20)<F32(D_L01_001B94C0,8))) return;
    for(i=0;i<2;i++) {
        rate=D_L01_001AFDF0.speed[i]+D_L01_001AFDF0.speed[i];
        divisor=F32(state,0x18)*5.0f;
        rate=rate/divisor;
        func_00282D30(scaled,delta,rate);
        if(1.0f<scaled[0] || scaled[0]<1.0f) scaled[0]-=func_00283CE0(func_00283CF0(scaled[0]));
        if(1.0f<scaled[1] || scaled[1]<1.0f) scaled[1]-=func_00283CE0(func_00283CF0(scaled[1]));
        D_L01_001B2FD0[i].u+=scaled[0];
        D_L01_001B2FD0[i].v+=scaled[1];
        if(1.0f<D_L01_001B2FD0[i].u) D_L01_001B2FD0[i].u-=1.0f;
        if(D_L01_001B2FD0[i].u<-1.0f) D_L01_001B2FD0[i].u+=1.0f;
        if(1.0f<D_L01_001B2FD0[i].v) D_L01_001B2FD0[i].v-=1.0f;
        if(D_L01_001B2FD0[i].v<-1.0f) D_L01_001B2FD0[i].v+=1.0f;
    }
    D_L01_001AFE18=D_L01_001AFE1C+func_00283198(func_00283CE0(D_L01_001B2088%360)*0.017444445f-3.14f)*0.1f;
    D_L01_001AA174=&D_L01_001AFE18;
    for(i=0;i<2;i++) {
        float sum=D_L01_001B2FD0[i].u+D_L01_001AFE00_gp[i].u*D_001A7928;
        D_L01_001B2FD0[i].u=sum;
        if(1.0f<sum) D_L01_001B2FD0[i].u=sum-1.0f;
        if(D_L01_001B2FD0[i].u<-1.0f) D_L01_001B2FD0[i].u=D_L01_001B2FD0[i].u+1.0f;
        sum=D_L01_001B2FD0[i].v+D_L01_001AFE00[i].v*D_001A7928;
        D_L01_001B2FD0[i].v=sum;
        if(1.0f<sum) D_L01_001B2FD0[i].v=sum-1.0f;
        if(D_L01_001B2FD0[i].v<-1.0f) D_L01_001B2FD0[i].v=D_L01_001B2FD0[i].v+1.0f;
    }
    func_L00_002E6DB8(func_L01_003BAFB8,object);
}
