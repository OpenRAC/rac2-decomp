#include "include_asm.h"
#include "common.h"
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern void func_002B60B0(void *,float,float,float,float);
extern void func_0029FCC0(void *,int,void *);
extern int func_002761F8(void *,void *,int,void *,int);
extern float func_002A89A8(void *,int,float);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_00325B70(void *,void *,int,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *,void *,int);
extern void func_00325320(void *);
extern int func_002A8508(int,int);
extern int func_002B3BA8(void *,int,void *,float,float,int);
extern void func_00325D30(void *,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_002A6C58(void *,int,int);
extern void func_003250F8(void *);
extern float D_001BAFA8 NOT_SDA;
extern int D_001B1B78 MACRO_ADDR;
extern char *D_001B1B5C MACRO_ADDR;
extern char *D_001B1C4C MACRO_ADDR;
extern char D_001B5340[];
extern unsigned short *D_001EE5A0[];
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
/* Sets up the object on its first frame, then every frame handles being hit, alerting group members and falling out of the world. Returns 1 when the object has been removed or finished. */
int func_003248A8(char *self)
{
    char *vars=P(self,0x68);
    int changed, result;
    float pos[4];
    unsigned short *list;
    char *peerObj, *peerVars;
    if (B(self,0x20)==0) {
        F(self,0x2C)*=1.1f;
        B(self,0x7E)|=1;
        B(vars,0x48)=FloatToInt(20.0f);
        B(vars,0x4A)=FloatToInt(16.0f);
        if(RandomIntBelow(2)==1) H(self,0x34)|=0x8000;
        F(vars,0x284)*=0.017453294f;
        P(vars,0x18)=vars+0x110;
        I(vars,0x2AC)=0; I(vars,0x2BC)=0; I(vars,0x2C0)=-1;
        qcopy(vars+0x520,self+0x10);
        F(vars,0x2E8)=8.0f; B(vars,0x70)=15; I(vars,0xA8)=5; F(vars,0x9C)=0.4f;
        I(vars,0x2C4)=0; I(vars,0x2C8)=0;
        F(vars,0x90)=0.5f; F(vars,0x94)=0.9f;
        if(I(vars,0x2EC)) F(vars,0x90)=0.07f;
        F(vars,0x110)=0.8f; F(vars,0x114)=0.5f;
        F(vars,0x118)=0.9f; F(vars,0x11C)=0.9f;
        F(vars,0x120)=1.5533432f; F(vars,0x140)=0.52359885f;
        P(vars,0x158)=vars+0x530; P(vars,0x15C)=vars+0x5B0;
        F(vars,0x13C)=0.0055555557f;
        SetControllerSpeedLimits(self,0.0033333334f,0.10000001f,0.001163553f,0.10471977f);
        qcopy(vars+0x200,self+0x10);
        F(vars,0x210)=1.0f; F(vars,0x21C)=3.0f; F(vars,0x220)=10.0f;
        I(vars,0x2D8)=RandomIntRange(120,700);
        B(vars,0x2E)=1; B(vars,0x28)=3;
        I(vars,0x280)=0; I(vars,0x2E4)=0; F(vars,0x2CC)=B(vars,0x34);
        TransformMobyJointToWorld(self,3,vars+0x300);
        F(vars,0x308)+=20.0f;
        TransformMobyJointToWorld(self,3,vars+0x310);
        if(CollLine(vars+0x310,vars+0x300,0,self,0)) F(vars,0x308)=D_001BAFA8;
        if(!I(vars,0x27C) && I(vars,0x288)==-1) {
            F(self,0x18)=ProbeGroundHeightBelow(self+0x10,0,0.5f);
            SetMobyState(self,1,0);
            if(B(self,0x43)!=0) StartAnimationBlended(self,0,0,0);
            if(I(vars,0x2DC)) {
                SetMobyState(self,2,0);
                if(B(self,0x43)!=4) StartAnimationBlended(self,4,0,10);
            }
        } else {
            SetMobyState(self,3,2);
            if(B(self,0x43)!=12) StartAnimationBlended(self,12,0,0);
            I(self,0x98)=0; F(vars,0x30)=2.5f;
            P(vars,0x2E0)=CreateMoby(0xAB7);
            if(!P(vars,0x2E0)) return 1;
            B(P(vars,0x2E0),0x30)=B(self,0x30);
            H(P(vars,0x2E0),0x32)=H(self,0x32);
            B(P(vars,0x2E0),0x31)=1;
            *(long long *)(P(vars,0x2E0)+0x38)=*(long long *)(self+0x38);
            H(P(vars,0x2E0),0x34)|=0x41;
            qcopy_nc(P(vars,0x2E0)+0x10,self+0x10);
            func_002A0F48(P(vars,0x2E0));
        }
        if(I(vars,0x288)!=-1) {
            SetMobyState(self,2,0);
            qcopy(vars+0x300,D_001B1C4C+(I(vars,0x288)<<7)+0x30);
            B(self,0x30)=128;
        }
        SpawnEnemyChildParts(self,vars+0x2A0,0,2);
    }
    if(B(self,0x31) && fast_vec_dist(self+0x10,gCameraState_001B5340)<24.0f) {
        UpdateMobyGroundCheck(self); B(self,0x6F)=22;
    }
    changed=0; if(B(vars,0x2E)==2) changed=1;
    TransformMobyJointToWorld(self,3,vars+0x310);
    result=ApplyDamageToObject(self,vars+0x60,0);
    if(result || changed) {
        F(vars,0x30)=0.5f;
        if(result==5) { I(vars,0xF0)=0; F(vars,0xF4)=0.8377582f; }
        AlertGroupPeersTypeB(self);
        if((result==4 || result==5 || changed) && B(self,0x21)<=D_001B1B78 && CountMobysInGroupNotInState(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            for (;;) {
                peerObj=D_001B1B5C+((*list&0x7FFF)<<8);
                if (*(short *)(peerObj+0xAA)==0xB0A) {
                    peerVars=P(peerObj,0x68);
                    if (!I(peerVars,0x294)) { I(peerVars,0x294)=1; break; }
                } else if (*(short *)(peerObj+0xAA)==0xB0B) {
                    peerVars=P(peerObj,0x68);
                    if (!I(peerVars,0x294)) { I(peerVars,0x294)=1; goto done1; }
                }
                if ((short)*list++<0) goto done1;
            }
            done1:;
        }
    }
    qcopy(pos,self+0x10);
    if(F(self,0x18)-ProbeGroundHeightBelow(pos,0,0.5f)>20.0f && B(self,0x21)<=D_001B1B78 && !I(vars,0x2C8)) {
        I(vars,0x2C8)=1;
        if(CountMobysInGroupNotInState(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            for (;;) {
                peerObj=D_001B1B5C+((*list&0x7FFF)<<8);
                if (*(short *)(peerObj+0xAA)==0xB0A) {
                    peerVars=P(peerObj,0x68);
                    if (!I(peerVars,0x294)) { I(peerVars,0x294)=1; break; }
                } else if (*(short *)(peerObj+0xAA)==0xB0B) {
                    peerVars=P(peerObj,0x68);
                    if (!I(peerVars,0x294)) { I(peerVars,0x294)=1; goto done2; }
                }
                if ((short)*list++<0) goto done2;
            }
            done2:;
        }
    }
    if(I(vars,0x2EC) && F(self,0x10)<170.7f && B(self,0x95)!=6) SetMobyState(self,16,6);
    I(vars,0x258)=SelectAimTarget_002B3BA8(self,I(vars,0x250),0,F(vars,0x268),10.0f,0);
    I(vars,0x25C)=SelectAimTarget_002B3BA8(self,I(vars,0x254),0,F(vars,0x26C),10.0f,0);
    if(F(self,0x18)<90.0f) {
        DestroyAttachedParts(self,vars+0x2A0);
        SpawnExplosionWithSparks(self,self+0x10,-1,0.5f,13.0f);
        SetDeathBits(self,0,3);
        return 1;
    }
    if(changed) {DestroyEnemyChildAndCleanupB(self); return 1;}
    return 0;
}
