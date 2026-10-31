/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1452 bytes, expected 1496.
 * us2: 17_smolg: 1452 bytes, expected 1496.
 * pal: func_L17_003C7680 is in neither catalogue of pal.
 * Complete two-trigger platform timing, path interpolation, collision fall and landing.
 * Full 16-byte ray vectors and five-argument collision interface retained. Missing44 bytes and
 * allocation differ; original controller-state/lifetime model is the reopening condition.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern int D_L17_001B2748;
extern char *D_L17_001FE880[];
extern char *D_L17_001B2C1C;
extern char D_00189EA0[];
extern float D_L17_001B03A0 __attribute__((sda)),D_L17_001B03A4 __attribute__((sda)),D_L17_001B03A8 __attribute__((sda)),D_L17_001B03AC __attribute__((sda));
extern float D_L17_001C0028;
extern float func_00283198(float);
extern u32 func_00283D38(u32,u32,float);
extern void func_L17_003C7498(void *,void *,void *,float);
extern int func_002ACBC8(void *,int);
extern int func_002E5DA0(int,int,void *,int);
extern int func_002E5CF8(int,int,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
/* Controls the two linked triggers, timed travel, fall, and landing of a platform. */
void func_L17_003C7680(char *object)
{
    Vec old,delta,lower,upper;
    char *state=P(object,0x68),*trigger,*path;
    int index,allow;
    float angle=(float)(D_L17_001B2748%150)*0.006666667f;
    angle=(angle+angle)*3.1415927f;
    if(angle>3.1415927f) angle-=6.2831855f;
    I(object,0x78)=func_00283D38(0x80464646,0x80828282,(func_00283198(angle)+1.0f)*0.5f);
    old.q=*(Q *)(object+16);
    if(U(object,0x20)==0) {
        U(object,0x20)=1;
        index=I(state,0xa4);
        if(index==-1) index=I(state,0xb4);
        if(index!=-1) *(Q *)(object+16)=*(Q *)(D_L17_001FE880[index]+16);
    }
    if(I(state,0xa0)!=-1 && I(state,0xa4)!=-1) {
        trigger=D_L17_001B2C1C+I(state,0xa0)*256;
        path=D_L17_001FE880[I(state,0xa4)];
        switch(I(state,0xac)) {
        case 0:
            if(!trigger || U(trigger,0x20)==254 || U(trigger,0x20)==253 || U(trigger,0x20)==I(state,0x90)) {F(state,0x9c)=0;I(state,0xac)=1;}
            break;
        case 1:
            F(state,0x9c)+=1.0f;
            if(F(state,0x9c)>=D_L17_001B03A0*60.0f) F(state,0x9c)=D_L17_001B03A0*60.0f;
            func_L17_003C7498(object,path,&old,D_L17_001B03A0);
            if(F(state,0x9c)>=D_L17_001B03A0*60.0f) {F(state,0xc8)=0;I(state,0xac)=2;}
            break;
        case 2:
            if(I(state,0xbc)) break;
            F(state,0xc8)+=1.0f;
            if(F(state,0xc8)>=D_L17_001B03A8*60.0f) {I(state,0xac)=3;U(trigger,0xbc)=0;F(state,0x9c)=D_L17_001B03A0*60.0f;}
            break;
        case 3:
            F(state,0x9c)-=1.0f;
            if(F(state,0x9c)<=0.0f) F(state,0x9c)=0;
            func_L17_003C7498(object,path,&old,D_L17_001B03A0);
            if(F(state,0x9c)<=0.0f) I(state,0xac)=0;
            break;
        }
    }
    if(I(state,0xb0)!=-1 && I(state,0xb4)!=-1) {
        trigger=D_L17_001B2C1C+I(state,0xb0)*256;
        path=D_L17_001FE880[I(state,0xb4)];
        switch(I(state,0xbc)) {
        case 0:
            allow=I(state,0xa0)==-1 || I(state,0xac)==2;
            index=I(state,0xc0);
            if(index!=-1 && U(D_L17_001B2C1C+index*256,0x20)!=3) allow=0;
            if(allow && (!trigger || U(trigger,0x20)==254 || U(trigger,0x20)==253 || U(trigger,0x20)==I(state,0x90))) {F(state,0x9c)=0;I(state,0xbc)=1;}
            break;
        case 1:
            F(state,0x9c)+=1.0f;
            if(F(state,0x9c)>=D_L17_001B03A4*60.0f) F(state,0x9c)=D_L17_001B03A4*60.0f;
            func_L17_003C7498(object,path,&old,D_L17_001B03A4);
            if(F(state,0x9c)>=D_L17_001B03A4*60.0f) {F(state,0xc8)=0;I(state,0xbc)=2;}
            break;
        case 2:
            F(state,0xc8)+=1.0f;
            if(F(state,0xc8)>=D_L17_001B03A8*60.0f) {
                if(!func_002ACBC8(D_00189EA0,I(state,0xcc))) {
                    I(state,0xbc)=3;func_002E5DA0(1,0,object,0x93b);U(trigger,0xbc)=0;F(state,0xc4)=0;
                } else F(state,0xc4)-=1.0f;
            }
            break;
        case 3:
            lower.q=*(Q *)(object+16);lower.f[2]-=20.01f;
            upper.q=*(Q *)(object+16);upper.f[2]+=0.5f;
            if(func_002761F8(&upper,&lower,2,object,0)) angle=D_L17_001C0028;else angle=0.0f;
            if(angle< F(object,0x18)) {
                F(state,0xc4)+=D_L17_001B03AC*0.0002777777845f;
                F(object,0x18)-=F(state,0xc4);
            } else {
                F(state,0xc4)=0;F(object,0x18)=angle;I(state,0xbc)=0;func_002E5CF8(0,0,object);
            }
            break;
        }
    }
    func_00282CF0(&delta,object+16,&old);
    func_002AD6F0(state+0x50,&delta,object+0xf0,object+0xf0);
}
