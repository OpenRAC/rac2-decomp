#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    u8 pad0[0x90];
    int path;
    u8 pad94[0xe4-0x94];
    float start;
    float distance[3];
    u8 padf4[0x11c-0xf4];
    float speed;
} Motion;
extern u8 D_L07_001B31A0[] __attribute__((sda));
extern int D_L07_001B1E08[] __attribute__((sda));
extern Quad D_L07_00189EA0[2];
typedef struct {
    u8 pad0[0x270];
    int phase;
    u8 pad274[0x2d0-0x274];
    Quad position;
    u8 pad2e0[0x33c-0x2e0];
    u8 *riding;
    int ridingFlag;
} Player;
extern Player D_L07_00189E20;
extern u8 *D_L07_0018A1C0 NOT_SDA;
extern Quad D_L07_001B1710 __attribute__((sda));
extern Quad D_L07_001B1720 MACRO_ADDR;
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern u8 *sibEntities SDATA(D_L07_001B22DC);
extern int *D_L07_001FDEC0[] NOT_SDA;
extern int D_0018C0BC NOT_SDA;
extern float D_L07_001B1D20[] __attribute__((sda));
extern Player D_L07_001B90C0;
extern float D_L07_001B173C[] __attribute__((sda));
extern Quad D_L07_001B1730 __attribute__((sda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern int func_002A8508(int,int);
extern int func_002E5DA0(int,int,void *,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AFDD8(void *,void *,void *,int);
extern void func_L02_0031F858(int,int);
extern void func_L07_003EEBF8(void *,void *,void *,void *);
extern void func_L00_003294F0(void *,int);
extern void func_L07_003EEE08(void *);
extern void func_L07_003F7968(void *,void *,int);
extern int func_L07_003F7BE0(void *);
extern float func_002AAA00(void *,float,void *,int,float,float,float);
extern void func_L07_0040F468(void *);
extern void func_L02_002DCEA0(int,float);
extern void func_L00_00303530(int,int);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_002DF3F8(void *,void *);
extern void func_L00_0042A500(void *);
extern void func_L07_00410700(void *,int);
extern void func_002A0430(int);
extern void func_002A7750(void *,int,int);
#define W(p,o) (*(int *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
/* Runs the 16 scripted events of the Siberius ship sequence. Each event waits for its trigger, then moves from waiting to started to finished. */
void func_L07_0040FC88(u8 *moby)
{
    Vec pos, rot;
    int i,j;
    u8 *vars=P(moby,0x68), *partVars, *target;
    float *cursor;
    int *path;
    float remaining;
    for(i=0;i<16;i++) {
        if(D_L07_001B31A0[i]==2) continue;
        switch(i) {
        case 0:
            if(D_L07_001B31A0[i]==0) {
                if(CountMobysInGroupNotInState(W(P(P(vars,0xf4),0x68),0x94),-1)==0) {
                    PlaySoundFromClassBank(1,0,P(vars,0xf4),0x11d9);
                    D_L07_001B31A0[i]=1;
                } else if((D_L07_001B1E08[0]&7)==(((int)P(vars,0xf4)>>8)&7)) {
                    FastVecSub(&pos,D_L07_00189EA0,P(vars,0xf4)+0x10);
                    TransformVectorByObjectOrGiven(P(vars,0xf4),&pos,&pos,0);
                    if(pos.f[0]<-14.0f) {
                        PlaySoundFromClassBank(1,0,P(vars,0xf4),0x11d9);
                        D_L07_001B31A0[i]=1;
                    }
                }
            } else {
                partVars=P(P(vars,0xf4),0x68);
                ApproachTargetWithDirectionMode(partVars+0x114,0.0f,partVars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(partVars,0x114)<=0) D_L07_001B31A0[i]=2;
            }
            break;
        case 2:
            if(D_L07_001B31A0[i]==0 && D_L07_0018A1C0==P(vars,0xf8)) {
                u8 *riderVars=P(D_L07_0018A1C0,0x68);
                int idx;
                SetGroupObjectsEnabled(W(riderVars,0x94),1);
                idx=W(riderVars,0xb8);
                pos.q=D_L07_001B1710;
                rot.q=D_L07_001B1720;
                AttachMobyToParentAtOffset(gMobyArray_L07[0]+(idx<<8),P(vars,0xf8),&pos,&rot);
                D_L07_001B31A0[i]=2;
            }
            break;
        case 1:
            if(D_L07_001B31A0[i]==0) {
                partVars=P(P(vars,0xf8),0x68);
                if(CountMobysInGroupNotInState(W(partVars,0x94),-1)<3) {
                    SetObjectFlagBit(gMobyArray_L07[0]+(W(partVars,0xb8)<<8),1);
                    D_L07_001B31A0[i]=2;
                }
            }
            break;
        case 3:
            if(D_L07_001B31A0[i]==0) {
                partVars=P(P(vars,0xf8),0x68);
                if(CountMobysInGroupNotInState(W(partVars,0x98),-1)==0 && CountMobysInGroupNotInState(W(partVars,0x9c),-1)==0) {
                    SwitchToState5(gMobyArray_L07[0]+(W(P(P(vars,0xf8),0x68),0xb8)<<8));
                    StartBossMoveTier(gMobyArray_L07[0]+(W(vars,0xc4)<<8),P(vars,0xf8),0);
                    D_L07_001B31A0[i]=2;
                } else if((D_L07_001B1E08[0]&7)==(((int)P(vars,0xf8)>>8)&7)) {
                    FastVecSub(&pos,D_L07_00189EA0,P(vars,0xf8)+0x10);
                    TransformVectorByObjectOrGiven(P(vars,0xf8),&pos,&pos,0);
                    if(pos.f[0]<-12.0f) {
                        SwitchToState5(sibEntities+(W(P(P(vars,0xf8),0x68),0xb8)<<8));
                        StartBossMoveTier(gMobyArray_L07[0]+(W(vars,0xc4)<<8),P(vars,0xf8),0);
                        D_L07_001B31A0[i]=2;
                    }
                }
            }
            break;
        case 4:
            if(D_L07_001B31A0[i]==0) {
                if(GetBossAttackMode(gMobyArray_L07[0]+(W(vars,0xc4)<<8))==1) {
                    D_L07_001B31A0[i]=1;
                    break;
                }
                if(D_L07_001B31A0[3]==2) SteerMobyAimYaw(moby);
            } else {
                Motion *motion=(Motion *)P(P(vars,0xf4),0x68);
                path=D_L07_001FDEC0[motion->path];
                cursor=motion->distance;
                for(j=0;j<3;j++,cursor++) {
                    *cursor-=motion->speed*0.1f;
                    if(*cursor<0) *cursor+=(float)*path;
                }
                remaining=motion->distance[0]-motion->start;
                if(remaining<0) remaining+=(float)*path;
                if(remaining<=32.5f) {
                    D_L07_001B31A0[i]=2;
                    D_L07_001B31A0[5]=1;
                    PlaySoundFromClassBank(1,0,P(vars,0xf8),0x11d9);
                }
            }
            break;
        case 5:
            if(D_L07_001B31A0[i]!=0) {
                partVars=P(P(vars,0xfc),0x68);
                ApproachTargetWithDirectionMode(partVars+0x110,0.0f,partVars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(partVars,0x110)>=0) D_L07_001B31A0[i]=2;
            }
            break;
        case 6:
            if(D_L07_001B31A0[i]==0 && D_L07_00189E20.riding==P(vars,0xfc) && D_L07_00189E20.ridingFlag) {
                SetGroupObjectsEnabled(W(P(P(vars,0xfc),0x68),0x94),1);
                D_L07_001B31A0[i]=2;
            }
            break;
        case 7:
            if(D_L07_001B31A0[i]==0) {
                partVars=P(P(vars,0xfc),0x68);
                if(CountMobysInGroupNotInState(W(partVars,0xa0),-1)==0) {
                    W(partVars,0x16cc)=PlaySoundFromClassBank(2,4,P(vars,0xfc),0x11d9);
                    D_L07_001B31A0[i]=2; F(partVars,0x16c8)=6.0f;
                }
            }
            break;
        case 8:
            if(D_L07_001B31A0[i]==0) {
                partVars=P(P(vars,0xfc),0x68);
                if(CountMobysInGroupNotInState(W(partVars,0x98),-1)==0 && CountMobysInGroupNotInState(W(partVars,0x9c),-1)==0) {
                    D_L07_001B31A0[i]=1;
                    PlaySoundFromClassBank(1,0,P(vars,0xfc),0x11d9);
                } else if((D_L07_001B1E08[0]&7)==(((int)P(vars,0xfc)>>8)&7)) {
                    FastVecSub(&pos,D_L07_00189EA0,P(vars,0xfc)+0x10);
                    TransformVectorByObjectOrGiven(P(vars,0xfc),&pos,&pos,0);
                    if(pos.f[0]<-14.0f) {
                        D_L07_001B31A0[i]=1;
                        PlaySoundFromClassBank(1,0,P(vars,0xfc),0x11d9);
                    }
                }
            } else {
                partVars=P(P(vars,0xfc),0x68);
                ApproachTargetWithDirectionMode(partVars+0x114,0.0f,partVars+0x118,0,0.0017453294713050127f,0.0017453294713050127f,0.10471977f);
                if(F(partVars,0x114)<=0) D_L07_001B31A0[i]=2;
            }
            break;
        case 9:
            if(D_L07_001B31A0[i]==0 && D_L07_00189E20.ridingFlag && D_L07_00189E20.riding==P(vars,0x100)) {
                FastVecSub(&pos,&D_L07_00189E20.position,P(vars,0x100)+0x10);
                TransformVectorByObjectOrGiven(P(vars,0x100),&pos,&pos,0);
                if(pos.f[2]>5.8f) {
                    StartBossMoveTier(sibEntities+(W(vars,0xc4)<<8),P(vars,0x100),1);
                    D_L07_001B31A0[i]=2;
                }
            }
            break;
        case 10:
            if(D_L07_001B31A0[i]==0) {
                target=gMobyArray_L07[0]+(W(vars,0xc4)<<8);
                if(GetBossAttackMode(target)==2 && *(u16 *)(target+0x96)>=121 && D_0018C0BC!=20 && D_0018C0BC!=7) D_L07_001B31A0[i]=1;
                else if(D_L07_001B31A0[9]==2) SteerMobyAimYaw(moby);
            } else if(D_L07_001B31A0[i]==1) {
                StartTimedCountdown(5,10.0f);
                if(D_L07_001B1D20[0]>=1.0f && D_L07_001B90C0.phase==1) {
                    D_L07_001B90C0.phase=60;
                    D_L07_001B31A0[i]=2;
                    LoadSceneChunk(0,0);
                    rot.q=0; rot.f[2]=D_L07_001B173C[0]; pos.q=rot.q;
                    ResetHeroPositionAndDirection(&D_L07_001B1730,&pos,0,1);
                    CaptureCheckpointState(D_L07_00189EA0,&D_L07_00189EA0[1]);
                    ResetCameraEntry(P(vars,0xd8));
                    {
                        u8 *child=P(vars,0x100);
                        int mode=W(vars,0xd0);
                        D_L07_001ADAAC=0;
                        StartShipSecondPhase(child,mode);
                    }
                    MarkTableEntryFlagged(moby[0xb0]);
                    SetMobyState(moby,2,-1);
                }
            }
            break;
        }
    }
}
