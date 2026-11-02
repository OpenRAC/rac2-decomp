/* functional: high. Same texture-scroll update, contact checks and stores as retail; only register allocation and scheduling differ. */
/*
 * GPT-6.1 Sol high tier; retained near miss, 29 October 2026.
 * Current pinned game compiler: -O2 -G8 -ffunction-sections -g in a separate
 * -g8.c unit. Final check.py: compiled 1424 bytes, expected 1428; 0/1 places
 * in USA v1.01. This is a size measurement, not matching-byte credit.
 * No linked build or other-release check was run.
 *
 * Explicit contact/region iterators preserve index rereads across calls.
 * Independent advancing U/V pointers preserve retail's store/reload pattern;
 * snapshotting both scaled components before the stores preserves their loads.
 * Separate rate/divisor/division statements with -g reproduce retail's two
 * padding nops before div.s. Without that padding this spelling is 1416 bytes.
 *
 * Remaining: contact/region block order, pointer induction and saved-register
 * allocation, initialization/store scheduling, history base materialization,
 * and mixed GP/absolute layer/height accesses. Explicit SDATA views of both
 * height scalars fix GP selection but shrink another 24 bytes; they do not
 * close the other differences. Struct/union indexed layer views merge stores
 * unlike retail; changing early returns to nested conditionals does not help.
 * Reopen with independent evidence for the contact/region pointer lifetimes
 * and mixed absolute/GP aliases. All required declarations follow.
 */

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
extern LayerPair D_L01_001B2FD0[2];
typedef struct { float speed[2]; } LayerSpeedPrefix;
extern LayerSpeedPrefix D_L01_001AFDF0 SDATA(D_L01_001AFDF0);
extern LayerPair D_L01_001AFE00[2] SDATA(D_L01_001AFE00);
extern float D_L01_001AFE18 MACRO_ADDR;
extern float D_L01_001AFE1C MACRO_ADDR;

extern int D_L01_001B2088;
extern float *D_L01_001AA174;
extern void func_L01_003BAFB8(void *);
void func_L01_003BB9D0(u8 *object)
{
    u8 *state=*(u8 **)(object+0x68);
    float delta[4] __attribute__((aligned(16))),scaled[4] __attribute__((aligned(16)));
    int i,blocked;
    int *contact, *region;
    float *u, *v;
    float dx,dy,rate,divisor;
    if(object[0x20]==0) {
        object[0x30]=255; object[0x20]=1;
        I32(state,0)=0x80103030; I32(state,4)=0x800c1006;
        I32(state,0xc)=0x50106060; I32(state,0x10)=0x106060;
        F32(state,0x28)=224.0f;
        for(i=0,u=&D_L01_001B2FD0[0].u,v=&D_L01_001B2FD0[0].v;i<2;i++,u+=2,v+=2) { *u=0.0f; *v=0.0f; }
        qcopy(&D_L01_001B2FC0, D_L01_001B94C0);
        D_L01_001AFE1C=F32(state,0x14);
        return;
    }
    blocked=0;
    for(i=0,contact=(int *)(state+0x30);i<2;i++,contact++) {
        if(*contact==-1) continue;
        if(I32(D_00189E20,0x2294)==28 && func_002ACBC8(D_L01_001B94C0,I32(state,0x30+i*4))) {
            S16(D_00189E20,0x1fe)=0;
            blocked=1; break;
        }
        if(func_002ACBC8(D_00189EA0,*contact)) {
            S16(D_00189EA0,0x17e)=0;
            blocked=1; break;
        }
    }
    if(blocked) return;
    D_L01_001AFE1C=F32(state,0x14);
    for(i=0,region=(int *)(state+0x40);i<8;i++,region++) {
        if(*region==-1) continue;
        if((I32(D_00189E20,0x2294)==28 && func_002ACBC8(D_L01_001B94C0,I32(state,0x40+i*4))) || func_002ACBC8(D_00189EA0,*region)) {
            D_L01_001AFE1C=F32(D_L01_001B264C+*region*128,0x38)+0.15f;
            break;
        }
    }
    S16(D_00189E20,0x1fe)=2;
    func_00282CF0(delta,D_L01_001B94C0,&D_L01_001B2FC0);
    qcopy(&D_L01_001B2FC0, D_L01_001B94C0);
    if(!(F32(state,0x20)<F32(D_L01_001B94C0,8))) return;
    for(i=0,u=&D_L01_001B2FD0[0].u,v=&D_L01_001B2FD0[0].v;i<2;i++,u+=2,v+=2) {
        rate=D_L01_001AFDF0.speed[i]+D_L01_001AFDF0.speed[i];
        divisor=F32(state,0x18)*5.0f;
        rate=rate/divisor;
        func_00282D30(scaled,delta,rate);
        if(1.0f<scaled[0] || scaled[0]<1.0f) scaled[0]-=func_00283CE0(func_00283CF0(scaled[0]));
        if(1.0f<scaled[1] || scaled[1]<1.0f) scaled[1]-=func_00283CE0(func_00283CF0(scaled[1]));
        dx=scaled[0];dy=scaled[1];
        *u+=dx;
        *v+=dy;
        if(1.0f<*u) *u-=1.0f;
        if(*u<-1.0f) *u+=1.0f;
        if(1.0f<*v) *v-=1.0f;
        if(*v<-1.0f) *v+=1.0f;
    }
    D_L01_001AFE18=D_L01_001AFE1C+func_00283198(func_00283CE0(D_L01_001B2088%360)*0.017444444820284843f-3.140000104904175f)*0.1f;
    D_L01_001AA174=&D_L01_001AFE18;
    for(i=0,u=&D_L01_001B2FD0[0].u,v=&D_L01_001B2FD0[0].v;i<2;i++,u+=2,v+=2) {
        *u+=D_L01_001AFE00[i].u*D_001A7928;
        if(1.0f<*u) *u-=1.0f;
        if(*u<-1.0f) *u+=1.0f;
        *v+=D_L01_001AFE00[i].v*D_001A7928;
        if(1.0f<*v) *v-=1.0f;
        if(*v<-1.0f) *v+=1.0f;
    }
    func_L00_002E6DB8(func_L01_003BAFB8,object);
}
