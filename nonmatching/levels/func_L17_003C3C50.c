/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: instruction at +0x54 differs.
 * us2: 17_smolg: instruction at +0x54 differs.
 * pal: func_L17_003C3C50 is in neither catalogue of pal.
 * Complete five-state triggered-platform reconstruction, both endpoints and both full16-byte
 * probes. Same1088-byte extent; case0 store/register order first differs at+0x54. Subsequent
 * state/common-tail scheduling needs source-lifetime evidence.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern char *D_L17_001FE880[];
extern char *D_L17_001B2C1C;
extern float D_L17_001B0240 __attribute__((sda)),D_L17_001B0244 __attribute__((sda));
extern char D_00189EA0[];
extern int func_00282948(void *);
extern void func_L17_003C3AF0(void *,void *,void *);
extern int func_L17_003C3A00(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
/* Drives a triggered platform between its two path endpoints. */
void func_L17_003C3C50(char *object)
{
    Vec old,delta,probeA,probeB;
    char *state=P(object,0x68),*trigger;
    int index,active;
    old.q=*(Q *)(object+0x10);
    func_00282948(state+0xbc);
    switch(U(object,0x20)) {
    case 0:
        I(state,0xc0)=0;I(state,0xb8)=0;I(state,0xbc)=0;U(object,0x20)=1;
        *(u16 *)(state+0x3e)|=9;
        index=I(state,0xa0);
        if(index!=-1) *(Q *)(object+16)=*(Q *)(D_L17_001FE880[index]+16);
        else if(I(state,0xa4)!=index) *(Q *)(object+16)=*(Q *)(D_L17_001FE880[I(state,0xa4)]+16);
        break;
    case 1:
        if(I(state,0x90)!=-1 && I(state,0xa0)!=-1) {
            trigger=D_L17_001B2C1C+I(state,0x90)*256;
            if(!trigger || U(trigger,0x20)==254 || U(trigger,0x20)==253 || U(trigger,0x20)==I(state,0x98)) {
                F(state,0xa8)=0;I(state,0xc4)=0;U(object,0x20)=2;break;
            }
        }
        if(I(state,0xa0)==-1 && I(state,0x94)!=-1 && I(state,0xa4)!=-1) {
            trigger=D_L17_001B2C1C+I(state,0x94)*256;
            if(!trigger || U(trigger,0x20)==254 || U(trigger,0x20)==253 || U(trigger,0x20)==I(state,0x98)) {
                F(state,0xa8)=0;I(state,0xc4)=1;U(object,0x20)=2;
            }
        }
        break;
    case 2:
        if(!I(state,0xb8)) F(state,0xa8)+=1.0f;
        if(F(state,0xa8)>=D_L17_001B0240*60.0f) F(state,0xa8)=D_L17_001B0240*60.0f;
        index=I(state,0xc4)?I(state,0xa4):I(state,0xa0);
        func_L17_003C3AF0(object,D_L17_001FE880[index],&old);
        if(F(state,0xa8)>=D_L17_001B0240*60.0f) {
            if(I(state,0xb0) && !I(state,0xc4)) {I(state,0xa0)=-1;U(object,0x20)=1;}
            else if(I(state,0xb4) && I(state,0xc4)==1) {I(state,0xa4)=-1;U(object,0x20)=1;}
            else {U(object,0x20)=4;F(state,0xac)=0;}
        }
        break;
    case 3:
        if(!I(state,0xb8)) F(state,0xa8)-=1.0f;
        if(F(state,0xa8)<=0.0f) F(state,0xa8)=0.0f;
        index=I(state,0xc4)?I(state,0xa4):I(state,0xa0);
        func_L17_003C3AF0(object,D_L17_001FE880[index],&old);
        if(F(state,0xa8)<=0.0f) U(object,0x20)=1;
        break;
    case 4:
        F(state,0xac)+=1.0f;
        if(F(state,0xac)>=D_L17_001B0244*60.0f) {
            U(object,0x20)=3;
            if(!I(state,0xc4)) index=I(state,0x90);else if(I(state,0xc4)==1) index=I(state,0x94);else break;
            U(D_L17_001B2C1C+index*256,0xbc)=0;
        }
        break;
    }
    if(!I(state,0xbc)) {
        if(F(state,0xc0)<0.0f) {
            probeA.q=*(Q *)D_00189EA0;
            if(func_L17_003C3A00(object,&probeA)) {if(!I(state,0xbc)) I(state,0xbc)=30;I(state,0xb8)=1;}
        } else {
            probeB.q=*(Q *)D_00189EA0;
            if(!func_L17_003C3A00(object,&probeB)) I(state,0xb8)=0;
        }
    }
    func_00282CF0(&delta,object+16,&old);
    func_002AD6F0(state+0x50,&delta,object+0xf0,object+0xf0);
}
