#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define W(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern int D_L12_001A79F0 MACRO_ADDR;
extern int D_L12_001A8F00 MACRO_ADDR;
struct L12GlobalState {
    char pad0[0x24]; int f24;
    char pad28[0x40]; int f68; short f6C;
    char pad6E[4]; short f72;
};
extern struct L12GlobalState D_L12_001A63A8;
extern char *D_L12_001FEAC0[];
extern void func_L12_0041A2B8(void *);
extern int func_002B1C20(void *,void *);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_002A77E0(int);
extern void func_002A7470(void *,int,int,int);
extern int func_L12_0041A6D0(void *,int);
/* The wrapper leaves func_002B50E0's integer status in the return register. */
extern int func_002B5278(void *,float);
extern void func_002B6D28(void);
extern void func_L12_0041A730(int);
extern int func_L12_0041A578(void *,int);
extern int func_L12_0041A460(void *);
extern float func_00283B98(float,float);
extern int func_00282948(void *);
extern int func_002B3868(void *);
extern void func_L02_003CA0A8(void *);
extern void func_L12_0041A530(void *);

/* Updates a path-walking enemy (moby class 4076): it waits, shoots at the hero in bursts, walks its route and comes back to its start spot. */
void func_L12_00419E40(char *obj) {
    char *vars=P(obj,0x68);
    int animIndex;
    if(D_L12_001A79F0==13) {
        if(D_L12_001A8F00!=2) {
            U(obj,0x34)=(U(obj,0x34)&0xFFBE)|0x1000;
            W(obj,0x98)=W(P(obj,0x24),0x10);
        } else {
            W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        return;
    }
    InitAndScalePathEnemy(obj);
    switch(B(obj,0x95)) {
    case 1:
        { int flags=DispatchActionByKind(obj,vars+0x60);
        if(flags&1) {MarkMobySpawned(obj);return;}
        if(flags&2) SetMobyState(obj,4,0); }
        break;
    case 0: break;
    }
    switch(B(obj,0x20)) {
    case 2:
        if((B(obj,0x60)&2) && TryClaimAttackTurn(obj,W(vars,0x11C))) {
            SetMobyState(obj,8,-1);
            animIndex=RandomIntBelow(4);
            if(animIndex==W(vars,0x258)) {if(animIndex!=3) animIndex++; else animIndex=0;}
            goto set_attack_animation;
        }
        break;
    case 8:
        StepMovementAtOwnPositionWithFactor(obj,F(vars,0x228));
        if(D_L12_001A63A8.f72==3 && D_L12_001A63A8.f6C<6000) {
            ResumeMusicStream(); SetMobyState(obj,5,-1);
        }
        break;
    case 5:
        if(!D_L12_001A63A8.f68 && D_L12_001A63A8.f24==-1) {
            IncrementSpaceTouristCounters(W(vars,0x114));
            SetMobyState(obj,6,-1);
            if(B(obj,0x43)) StartAnimationBlended(obj,0,0,20);
            W(vars,0x220)=FindNextStopPathPoint(obj,W(vars,0x224));
        } else if(B(obj,0x60)&2) {
            animIndex=RandomIntBelow(4);
            if(animIndex==W(vars,0x258)) {if(animIndex!=3)animIndex++;else animIndex=0;}
            if(B(obj,0x43)!=animIndex+1) StartAnimationBlended(obj,animIndex+1,0,20);
            W(vars,0x258)=animIndex;
        }
        break;
    case 6:
        if(AimAtPathCursorAndAdvance(obj)) {
            if(W(vars,0x220)==W(D_L12_001FEAC0[W(vars,0x110)],0)-1) {
                SetMobyState(obj,3,-1);
                if(B(obj,0x43)!=9)StartAnimationBlended(obj,9,0,20);
            } else {
                SetMobyState(obj,7,-1);
                if(B(obj,0x43))StartAnimationBlended(obj,0,0,20);
                W(vars,0x22C)=120;
                F(vars,0x228)=FastAddRotations(F(obj,0xF8),3.141590118408203f);
            }
        }
        break;
    case 7:
        StepMovementAtOwnPositionWithFactor(obj,F(vars,0x228));
        if(FastFloatHelperD(vars+0x22C) && TryClaimAttackTurn(obj,W(vars,0x11C))) {
            SetMobyState(obj,8,-1);
            animIndex=RandomIntBelow(4);
            if(animIndex==W(vars,0x258)){if(animIndex!=3)animIndex++;else animIndex=0;}
set_attack_animation:
            if(B(obj,0x43)!=animIndex+1)StartAnimationBlended(obj,animIndex+1,0,20);
            W(vars,0x258)=animIndex;
            W(vars,0x11C)++;
        }
        break;
    case 3:
        if(B(obj,0x60)&2) {
            W(vars,0x220)=0; W(vars,0x224)=0; W(vars,0x11C)=0;
            SetMobyState(obj,10,-1);
        }
        break;
    case 10:
        if(SetFirstPendingFlag(obj)) {
            W(vars,0x25C)=25; W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        if(FastFloatHelperD(vars+0x25C)) {
            SetMobyState(obj,1,-1);
            qcopy(obj+0x10,vars+0x210);
        }
        SpawnEffectParticleRing(obj);
        break;
    case 1:
        W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        break;
    }
    TickEnemyTimersAndAge(obj);
}
