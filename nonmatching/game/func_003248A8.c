/* Closer C4, 1 November 2026: 2120/2124, 58 rows, nearly all two registers. Found: `changed = 0; if (...) changed = 1;` gives the
 * s5 constant, the search has no base local (PRE's reaching copy makes t0, so read D_001B1B5C inline), and a failed check goes
 * straight to advance. Left: sched1 moves that copy up into a free slot, so peer ties to the a0 of the load; retail has it at the
 * branch, peer in a2 and the class in v1, and a nop more. No flag moves it.
 */
/* GPT-6.1 Sol (high effort), task v1342, 29 October 2026.
 * USA v1.01, default game -O2 -G0 -ffunction-sections; use a separate unit.
 * Best and final check.py: 2112 bytes / retail 2124; 0 of 7 places match.
 * Functional reconstruction only: neither relocations nor linking qualified,
 * because check.py rejects the section size before deriving symbol values.
 *
 * Initialization assignment order and the child-copy path are improved over
 * v0994 (2068 bytes). Both searches now preserve a separate initial primary
 * class check and two entries into the remaining scan. Retail reuses 1 in s5
 * for changed and the first notification; this compiler uses sltiu and merges
 * that notification store with the final store. Peer data/base/class register
 * choices and the nonzero-notification backedges also differ.
 *
 * Eighteen check.py invocations, including one syntax error, no linked build.
 * Natural while/alternate-class forms measured 2032, 2108 and 2100 bytes;
 * a goto-to-body form was 2012. Directly sending the shared nonzero flag test
 * to advance shrinks this draft to 2088, merging its initial flag check too.
 * Equivalent assignment/OR and explicit changed-boolean spellings tie there.
 * Distinct primary/secondary record types leave the old loop shape at 2068.
 * Reopen with a justified flag/base lifetime that preserves the first store
 * and the direct-to-advance backedges without merging the initial flag test.
 *
 * All declarations are below. One truthful MACRO_ADDR declaration per group
 * global supplies the observed absolute/GP mix at -G0; no GP alias is needed.
 * func_002B3BA8's bank-preserving argument interleaving fixes the first call's
 * delay slot (object, index, point, force remain A0-A3; range/height F12-F13).
 */
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
int func_003248A8(char *self)
{
    char *d=P(self,0x68);
    int changed, result;
    float pos[4];
    unsigned short *list;
    char *peer, *pd;
    int peerClass;
    if (B(self,0x20)==0) {
        F(self,0x2C)*=1.1f;
        B(self,0x7E)|=1;
        B(d,0x48)=func_00283CF0(20.0f);
        B(d,0x4A)=func_00283CF0(16.0f);
        if(func_002A77E0(2)==1) H(self,0x34)|=0x8000;
        F(d,0x284)*=0.017453294f;
        P(d,0x18)=d+0x110;
        I(d,0x2AC)=0; I(d,0x2BC)=0; I(d,0x2C0)=-1;
        qcopy(d+0x520,self+0x10);
        F(d,0x2E8)=8.0f; B(d,0x70)=15; I(d,0xA8)=5; F(d,0x9C)=0.4f;
        I(d,0x2C4)=0; I(d,0x2C8)=0;
        F(d,0x90)=0.5f; F(d,0x94)=0.9f;
        if(I(d,0x2EC)) F(d,0x90)=0.07f;
        F(d,0x110)=0.8f; F(d,0x114)=0.5f;
        F(d,0x118)=0.9f; F(d,0x11C)=0.9f;
        F(d,0x120)=1.5533432f; F(d,0x140)=0.52359885f;
        P(d,0x158)=d+0x530; P(d,0x15C)=d+0x5B0;
        F(d,0x13C)=0.0055555557f;
        func_002B60B0(self,0.0033333334f,0.10000001f,0.001163553f,0.10471977f);
        qcopy(d+0x200,self+0x10);
        F(d,0x210)=1.0f; F(d,0x21C)=3.0f; F(d,0x220)=10.0f;
        I(d,0x2D8)=func_002A7820(120,700);
        B(d,0x2E)=1; B(d,0x28)=3;
        I(d,0x280)=0; I(d,0x2E4)=0; F(d,0x2CC)=B(d,0x34);
        func_0029FCC0(self,3,d+0x300);
        F(d,0x308)+=20.0f;
        func_0029FCC0(self,3,d+0x310);
        if(func_002761F8(d+0x310,d+0x300,0,self,0)) F(d,0x308)=D_001BAFA8;
        if(!I(d,0x27C) && I(d,0x288)==-1) {
            F(self,0x18)=func_002A89A8(self+0x10,0,0.5f);
            func_002A7750(self,1,0);
            if(B(self,0x43)!=0) func_002A7470(self,0,0,0);
            if(I(d,0x2DC)) {
                func_002A7750(self,2,0);
                if(B(self,0x43)!=4) func_002A7470(self,4,0,10);
            }
        } else {
            func_002A7750(self,3,2);
            if(B(self,0x43)!=12) func_002A7470(self,12,0,0);
            I(self,0x98)=0; F(d,0x30)=2.5f;
            P(d,0x2E0)=func_0029EFD0(0xAB7);
            if(!P(d,0x2E0)) return 1;
            B(P(d,0x2E0),0x30)=B(self,0x30);
            H(P(d,0x2E0),0x32)=H(self,0x32);
            B(P(d,0x2E0),0x31)=1;
            *(long long *)(P(d,0x2E0)+0x38)=*(long long *)(self+0x38);
            H(P(d,0x2E0),0x34)|=0x41;
            qcopy_nc(P(d,0x2E0)+0x10,self+0x10);
            func_002A0F48(P(d,0x2E0));
        }
        if(I(d,0x288)!=-1) {
            func_002A7750(self,2,0);
            qcopy(d+0x300,D_001B1C4C+I(d,0x288)*128+0x30);
            B(self,0x30)=128;
        }
        func_00325B70(self,d+0x2A0,0,2);
    }
    if(B(self,0x31) && func_00282E48(self+0x10,D_001B5340)<24.0f) {
        func_002A93B0(self); B(self,0x6F)=22;
    }
    changed=0; if(B(d,0x2E)==2) changed=1;
    func_0029FCC0(self,3,d+0x310);
    result=func_002B0ED8(self,d+0x60,0);
    if(result || changed) {
        F(d,0x30)=0.5f;
        if(result==5) { I(d,0xF0)=0; F(d,0xF4)=0.8377582f; }
        func_00325320(self);
        if((result==4 || result==5 || changed) && B(self,0x21)<=D_001B1B78 && func_002A8508(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            peer=D_001B1B5C+((*list&0x7FFF)<<8);
            peerClass=*(short *)(peer+0xAA);
            if (peerClass==0xB0A) {
                char *firstData=P(peer,0x68);
                if (!I(firstData,0x294)) { I(firstData,0x294)=1; goto done1; }
                goto advance1;
            }
            for (;;) {
                if (peerClass==0xB0B) goto check_peer1;
advance1:
                if ((short)*list++<0) goto done1;
                peer=D_001B1B5C+((*list&0x7FFF)<<8);
                peerClass=*(short *)(peer+0xAA);
                if (peerClass!=0xB0A) continue;
check_peer1:
                pd=P(peer,0x68);
                if (I(pd,0x294)) goto advance1;
                break;
            }
            I(pd,0x294)=1;
done1:;
        }
    }
    qcopy(pos,self+0x10);
    if(F(self,0x18)-func_002A89A8(pos,0,0.5f)>20.0f && B(self,0x21)<=D_001B1B78 && !I(d,0x2C8)) {
        I(d,0x2C8)=1;
        if(func_002A8508(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            peer=D_001B1B5C+((*list&0x7FFF)<<8);
            peerClass=*(short *)(peer+0xAA);
            if (peerClass==0xB0A) {
                char *firstData=P(peer,0x68);
                if (!I(firstData,0x294)) { I(firstData,0x294)=1; goto done2; }
                goto advance2;
            }
            for (;;) {
                if (peerClass==0xB0B) goto check_peer2;
advance2:
                if ((short)*list++<0) goto done2;
                peer=D_001B1B5C+((*list&0x7FFF)<<8);
                peerClass=*(short *)(peer+0xAA);
                if (peerClass!=0xB0A) continue;
check_peer2:
                pd=P(peer,0x68);
                if (I(pd,0x294)) goto advance2;
                break;
            }
            I(pd,0x294)=1;
done2:;
        }
    }
    if(I(d,0x2EC) && F(self,0x10)<170.7f && B(self,0x95)!=6) func_002A7750(self,16,6);
    I(d,0x258)=func_002B3BA8(self,I(d,0x250),0,F(d,0x268),10.0f,0);
    I(d,0x25C)=func_002B3BA8(self,I(d,0x254),0,F(d,0x26C),10.0f,0);
    if(F(self,0x18)<90.0f) {
        func_00325D30(self,d+0x2A0);
        func_002AC728(self,self+0x10,-1,0.5f,13.0f);
        func_002A6C58(self,0,3);
        return 1;
    }
    if(changed) {func_003250F8(self); return 1;}
    return 0;
}
