#include "common.h"
#define FIELD(p,t,o) (*(t *)((char *)(p)+(o)))
extern int D_L09_001B0C4C __attribute__((sda));
extern float D_L09_001B0C00 __attribute__((sda)), D_L09_001B0C04 __attribute__((sda)), D_L09_001B0C08 __attribute__((sda)), D_L09_001B0C0C __attribute__((sda));
extern float D_L09_001B0C10 __attribute__((sda)), D_L09_001B0C14 __attribute__((sda)), D_L09_001B0C18 __attribute__((sda)), D_L09_001B0C1C __attribute__((sda));
extern char D_L09_001B0C50[];
extern int func_002ACD38(void *);
extern void func_L09_003EAA18(void *);
extern void func_0026FEB8(void *,int,int);
extern int func_002B38B8(void *);
extern void func_002A7750(void *,int,int);
extern void func_002B60B0(void *,float,float,float,float);
extern void func_002A7470(void *,int,int,int);
extern int func_L09_003EA058(void *,int);
extern int func_L09_003EA2D0(void *,int,int);
extern int func_L09_0033E658(int);
extern void func_L09_003EA108(void *,int);
extern int func_002B1C20(void *,void *);
extern void func_L09_003EAF60(void *);
extern void func_L09_003E99E0(void *);
extern void func_L09_003EA360(void *);
extern void func_L09_003E9AA0(void *);
extern void func_L09_003EA9D0(void *);
/* Per-frame update of this enemy: handles its state changes, starts its animations and keeps its position in sync. */
void func_L09_003EAB20(char *moby)
{
    char *state;
    char *position;
    int ready;
    if (D_L09_001B0C4C) return;
    position=moby+0x10;
    if (!IsObjectInSelectedZone(position)) return;
    state=FIELD(moby,char *,0x68);
    StepEnemyAnimation(moby);
    qcopy(position,state+0x330);
    switch (FIELD(moby,unsigned char,0x95)) {
    case 0: STUB_printf(D_L09_001B0C50,FIELD(moby,short,0xB2),FIELD(moby,short,0xAA)); break;
    case 1:
        if (FIELD(state,int,0x154)==1 || IsThirdPendingFlagSet(moby)) {
            FIELD(state,int,0x354)=FIELD(state,int,0x378);
            SetMobyState(moby,2,2);
        }
        break;
    case 3:
        if (FIELD(state,int,0x154)==1) {
            SetControllerSpeedLimits(moby,D_L09_001B0C10*0.00027777778f,D_L09_001B0C14*0.016666668f,D_L09_001B0C18*4.84813745061e-06f,D_L09_001B0C1C*0.000290888245218f);
            SetMobyState(moby,4,4);
        }
        break;
    case 2: case 5: break;
    case 4:
        if (FIELD(state,int,0x154)!=1 && !FIELD(state,unsigned char,0x369)) {
            if (FIELD(moby,unsigned char,0x43)) StartAnimationBlended(moby,0,0,0);
            SetControllerSpeedLimits(moby,D_L09_001B0C00*0.00027777778f,D_L09_001B0C04*0.016666668f,D_L09_001B0C08*4.84813745061e-06f,D_L09_001B0C0C*0.000290888245218f);
            SetMobyState(moby,3,3);
        }
        break;
    }
    switch (FIELD(moby,unsigned char,0x20)) {
    case 0: STUB_printf(D_L09_001B0C50,FIELD(moby,short,0xB2),FIELD(moby,short,0xAA)); break;
    case 1: break;
    case 2:
        ready = 1;
        if (FIELD(state,int,0x36C)!=-1) ready = AdvancePathIndexAndMove(moby,FIELD(state,int,0x36C)) != 0;
        if (ready) {
            SetControllerSpeedLimits(moby,D_L09_001B0C00*0.00027777778f,D_L09_001B0C04*0.016666668f,D_L09_001B0C08*4.84813745061e-06f,D_L09_001B0C0C*0.000290888245218f);
            StartMobyOnPathEntry(moby,FIELD(state,int,0x350),-1);
            FIELD(state,int,0x380)=1;
            SetMobyState(moby,3,3);
        } break;
    case 3:
        ready = 1;
        if (FIELD(state,int,0x350)!=-1) ready = AdvancePathIndexAndMove(moby,FIELD(state,int,0x350)) != 0;
        if (ready) {
            if(FIELD(state,short,0x11A)) FIELD(state,short,0x11A)=0;
            else FIELD(state,short,0x11A)=GetPathTableEntryId(FIELD(state,int,0x350));
        } break;
    case 4:
        if(FIELD(state,int,0x350)!=-1) SteerMobyToNearestPathPoint(moby,FIELD(state,int,0x350));
        break;
    case 5:
        if(DispatchActionByKind(moby,state+0x180)&2) {
            if(FIELD(state,float,0x20)<=0) SetMobyState(moby,6,-1);
            else {
                FIELD(state,int,0x37C)=0;
                if(FIELD(state,int,0x380)) {
                    FIELD(state,unsigned char,0x369)=0;
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    SetMobyState(moby,4,4);
                } else {
                    if(FIELD(moby,unsigned char,0x43)) StartAnimationBlended(moby,0,0,0);
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    SetMobyState(moby,2,2);
                }
            }
        } break;
    case 6: DestroyMobyWithExplosion(moby); break;
    }
    EaseMobyTurnAngles(moby);
    FIELD(moby,int,0xF0)=0;
    FaceHeroAndSwayEnemy(moby);
    SpawnFallingParticles(moby);
    BumpFrameCounterResetTimers(moby);
}
