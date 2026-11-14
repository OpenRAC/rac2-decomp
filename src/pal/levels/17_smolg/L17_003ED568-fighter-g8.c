/* func_PAL_L17_003ED568 (964 bytes, Smolg): the PAL copy of func_L17_003E8A58
 * (src/levels/17_smolg/L17_003E8A58-fighter-g8.c) with its rates for 50 Hz: the 60-frame count
 * is 50, the per-frame rates are scaled by 6/5 (1/60 -> 0.02, 1/120 -> 0.012) and the
 * per-frame-squared ones by 36/25 (1/240 -> 0.006, 1/720 -> 0.002, 1/90 -> 0.016, 1/3 -> 0.4).
 * A FAKEMATCH unit like its v1.01 copy (owner rulings of 13 November 2026, extended to the PAL
 * and USA v2.00 releases on 14 November 2026; config/fakematch.tsv), built with the same
 * flags (config/cflags.txt). */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
typedef struct FighterState {
    u8 pad0[0x26];
    u16 f26;
    u8 f28;
    u8 f29;
    u8 pad2A[0x6];
    float f30;
    u8 f34;
    u8 pad35[0x13];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4B[0x25];
    u8 f70;
    u8 f71;
    u8 pad72[0x3];
    u8 f75;
    u8 f76;
    u8 f77;
    u8 pad78[0x4];
    float f7C;
    float f80;
    float f84;
    float f88;
    float f8C;
    float f90;
    float f94;
    short f98;
    u8 pad9A[0x2];
    float f9C;
    float fA0;
    u8 padA4[0x4];
    int fA8;
    u8 padAC[0xC];
    float fB8;
    u8 padBC[0x10];
    u8 fCC;
    u8 fCD;
    u8 fCE;
    u8 fCF;
    u8 padD0[0x2];
    u8 fD2;
    u8 fD3;
    u8 padD4[0x1];
    u8 fD5;
    u8 padD6[0x3A];
    float f110;
    u8 pad114[0x4];
    float f118;
    float f11C;
    float f120;
    u8 pad124[0x18];
    float f13C;
    u8 pad140[0x8];
    int f148;
    int f14C;
    u8 pad150[0x100];
    int f250;
    u8 pad254[0x42C];
    int f680;
    int f684;
    u8 pad688[0x16];
    short f69E;
    u8 pad6A0[0x4];
    int f6A4;
    u8 pad6A8[0x10];
    int f6B8;
    u8 pad6BC[0x4];
    Vec f6C0;
    u8 pad6D0[0x18];
    int f6E8;
    int f6EC;
    u8 pad6F0[0x10];
    float f700;
    u8 pad704[0x1C];
    char * f720;
    u8 pad724[0xC];
    int f730;
    u8 pad734[0x10];
    char * f744;
    u8 pad748[0x8];
    int f750;

} FighterState;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern char *D_L17_001B2C1C;
extern float D_L17_001B0E40 __attribute__((sda)),D_L17_001B0F38 __attribute__((sda)),D_L17_001B0E48 __attribute__((sda));
extern char D_L17_001B9BC0[];
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_L02_0032E508(void *,int,void *,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern char *func_002A9640(void *,u32,int);
extern int func_002B0ED8(void *,void *,int);
extern int func_002B3BA8(void *,int,void *,int,float,float);
/* Initializes the fighter's complete parameter groups, then handles proximity and damage. */
void func_PAL_L17_003ED568(char *object)
{
    FighterState *state=(FighterState *)P(object,0x68);
    char *hit;
    int index;
    float vf80;
    float vf84;
    float vf94;
    float vf7C;
    float vf88;
    float vf8C;
    float vf9C;
    float vf700;
    float vfB8;
    float vf90;
    int vf14C;
    float vfA0;
    float vf11C;
    float vf120;
    float vf13C;
    float vf30;
    float vf118;float e48;int v;
    if(!U(object,0x20)) {register float t;float o1, o2, o3, o4, o5, o6; /* FAKEMATCH: `register` keeps t live to the end of its scope (-frac2-register-scope, retail's $f20); no-code copy chain of the 1.0 for state->f30 (tied in local-alloc, deleted by reload); its quantity holds $f2 over the init window like retail */int c1,c7,cE,cD,c8,c9,c3,c20,c12,c4,c6,c60;
        F(object,0x2c)=F(P(object,0x24),0x24)*0.85f;
        index=state->f6B8;
        if((unsigned)(index+1)>=2) F(object,0x18)=F(D_L17_001B2C1C+index*256,0x18)+1.4f;
        state->f6C0.q=*(Q *)(object+0x10);
        state->f110=D_L17_001B0E40;
        state->f6C0.f[3]=F(object,0xf8);state->f6E8=0;state->f6EC=0;
t=15.0f;state->f48=func_00283CF0(t);state->f4A=func_00283CF0(12.8f);
/*BEGIN*/
o1=1.0f; /* FAKEMATCH: see o1..o6 */
c1=1;
c7=7;
cE=14;
state->f70=cE;
c20=20;
cD=13;
state->f71=cD;
c4=4;
c8=8;
c9=9;
c12=12;
state->f76=c8;
state->f29=c1;
state->f75=c7;
state->f77=c9;
o2=o1; /* FAKEMATCH: chain copy */
vf80=D_L17_001B0F38*0.0200000014f;
vf90=D_L17_001B0E40;
vf94=vf90+0.1f;
state->fD3=c12;
state->f80=vf80;
state->f84=0.006f;
state->f94=vf94;
c6=6;
vf700=(float)state->f34;
state->fCC=c7;
state->fCF=c9; /* FAKEMATCH: moved before fCD/fCE (sched1 position for c9 span; sched2 restores retail order with -frac2-sched2-qi-store-offset) */
c3=3;
state->fCD=c20;
state->fCE=c4;
state->fD2=c6;
state->fD5=c1;
o3=o2; /* FAKEMATCH: chain copy */
state->fA8=c3;
o4=o3; /* FAKEMATCH: chain copy */
state->f7C=0.400000036f;
state->f88=0.012f;
c60=50;
state->f8C=0.002f;
state->f9C=0.4f;
vf14C=state->f684;
state->f700=vf700;
state->f26=c60;
state->fB8=0.01f;
state->f90=vf90;
state->f14C=vf14C;
o5=o4; /* FAKEMATCH: chain copy */
state->fA0=40.0f;
e48=D_L17_001B0E48;
state->f11C=e48;
o6=o5; /* FAKEMATCH: chain copy */
state->f120=1.308997035f;
state->f13C=0.016f;
state->f148|=16;
state->f28=c3;
state->f30=o6; /* FAKEMATCH: end of the 1.0 chain */
state->f118=e48;
state->f98=0;
/*END*/
        if(state->f680==-1 || state->f684==-1) {func_0029F338(object);return;}
        
        if((unsigned)(state->f6B8+1)<2) func_002A7750(object,3,0);else func_002A7750(object,1,5);
        state->f730=1;state->f720=state->f744;
        if(state->f744) I(state->f744,0)=-1;
        state->f750=func_L02_0032E508(object,state->f684,(char *)state+0x280,32);
    }
    if(U(object,0x31) && func_00282E48(object+16,D_L17_001B9BC0)<24.0f) {func_002A93B0(object);U(object,0x6f)=22;}
    hit=func_002A9640(object,0x10000,1);
    if(hit && P(hit,0x20) && (H(P(hit,0x20),0xaa)==0x31a || H(P(hit,0x20),0xaa)==0x1256 || H(P(hit,0x20),0xaa)==0x1305)) goto impact;
    if(U(object,0x20)!=1) func_002B0ED8(object,(char *)state+0x60,0);
    goto damage;
impact:
    if(hit) U(object,0xa8)=255;
damage:;
    state->f69E=func_002B3BA8(object,state->f680,0,0,0.0f,0.0f);
    state->f6A4=state->f250;
}
