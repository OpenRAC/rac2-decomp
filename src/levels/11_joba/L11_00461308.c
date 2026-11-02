/* func_L11_00461308: a Joba moby's state machine with a companion moby (class 0xCF6).
   State 0 spawns the companion; 1 sets or clears flag bits 0x41 on both from a level flag
   and waits on its linked moby's state and func_002ACBC8; 2 makes three
   func_L11_003DD068 calls with randomised directions; 3 waits for func_002ACBC8 to clear.
   In states 1-3 it oscillates its height, places the companion at its offset and emits
   three particles.
   Built -O2 -G0 in its own unit. The random bounds are a two-float block: the lower is
   read through $gp, the upper as the block's second word, a two-instruction absolute
   load that stays out of the call's delay slot as in retail.
*/
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_002B37E8(char *, char *);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_0029FCC0(char *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern u8 *func_L11_003DD068(u8 *, u8 *, u8 *, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A05A8(char *);
extern void func_002A0F48(char *);
extern void func_L00_0033C0D0(char *, void *, void *, void *, int);
extern int D_L11_001B089C[] NOT_SDA __attribute__((sda));
typedef struct { int unused; int flags; char pad[56]; } Entry61308;
extern Entry61308 D_L11_002B6D40[];
extern char *D_L11_001B359C[] NOT_SDA __attribute__((sda));
extern char *D_L11_001B368C[] NOT_SDA __attribute__((sda));
extern char D_00189EA0[];
/* The random bounds at 001B2388: lower, upper. Retail reads the lower through $gp and the
   upper as the block's second word, absolutely. */
extern float D_L11_001B2388 SDATA(D_L11_001B2388);
extern float D_L11_001B2388_block[] __asm__("D_L11_001B2388") __attribute__((sda));
extern char D_L11_001B2378[] NOT_SDA __attribute__((sda));
extern char D_L11_001B2368[] NOT_SDA __attribute__((sda));
extern char D_L11_001B2358[] SDATA(D_L11_001B2358);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
void func_L11_00461308(char *p)
{
    float v[4], pos[4], dir[4], tmp[4];
    char *s = P(p,0x68);
    int active=0, i, ready;
    float t, sn, cs;
    switch ((unsigned char)p[0x20]) {
    case 0:
        P(s,0x10)=func_0029EFD0(0xCF6);
        F(s,0x14)=0; F(s,0x18)=0;
        if(P(s,0x10)) {
            func_002B37E8(P(s,0x10),0);
            H(P(s,0x10),0x34)|=6;
            func_002A7470(P(s,0x10),0x10,0,0);
        }
        func_002A7750(p,1,-1);
        break;
    case 1:
        if ((D_L11_002B6D40[D_L11_001B089C[0]].flags&0x10) && !I(s,8)) {
            H(p,0x34)|=0x41;
            H(P(s,0x10),0x34)|=0x41;
            I(p,0x98)=0;
            return;
        }
        active=1;
        H(p,0x34)&=0xFFBE;
        H(P(s,0x10),0x34)&=0xFFBE;
        I(p,0x98)=I(P(p,0x24),0x10);
        ready=1;
        if(I(s,0xC)!=-1) { char *m=D_L11_001B359C[0]+(I(s,0xC)<<8); ready=0; if((unsigned char)m[0x20]!=3) ready=active; }
        if (ready && func_002ACBC8(D_00189EA0,I(s,0)))
            func_002A7750(p,2,-1);
        break;
    case 2:
        active=1;
        t=func_002A7878(0.0f,0.333f);
        for(i=0;i<3;i++) {
            func_0029FCC0(p,i==0?3:i==1?2:4,v);
            *(TI128 *)tmp = 0;
            tmp[0]=func_002A7878(-1.0f,1.0f);
            tmp[3]=1.0f;
            tmp[1]=t+t-1.0f;
            t+=0.333f;
            *(TI128 *)dir=*(TI128 *)tmp;
            func_002830C0(dir,dir,D_L11_001B368C[0]+(I(s,4)<<7));
            {
                float high = D_L11_001B2388_block[1];
                float low = D_L11_001B2388;
                func_L11_003DD068(p,v,dir,func_002A7878(low,high)*0.00027777778f);
            }
        }
        func_002A7750(p,3,-1);
        break;
    case 3:
        active=1;
        if(!func_002ACBC8(D_00189EA0,I(s,0))) func_002A7750(p,1,-1);
        break;
    }
    if(active) {
        F(s,0x14)=func_00283B98(F(s,0x14),0.034906592f);
        sn=func_00283180(F(s,0x14));
        cs=func_00283198(F(s,0x14));
        F(p,0x18)-=F(s,0x18);
        F(s,0x18)=cs*0.1f;
        F(p,0x18)+=F(s,0x18);
        F(p,0xF4)+=cs*0.0015f;
        F(p,0xF0)+=sn*0.0015f;
        *(TI128 *)(P(s,0x10)+0xF0)=*(TI128 *)(p+0xF0);
        func_00282D30(v,p+0xE0,1.46f);
        func_00282CC0(P(s,0x10)+0x10,p+0x10,v);
        func_002A05A8(P(s,0x10));
        func_002A0F48(P(s,0x10));
        func_00282D30(v,p+0xE0,0.59f);
        func_00282CC0(pos,p+0x10,v);
        v[0]=v[1]=0.0f;
        v[2]=-(func_002A7878(2.25f,3.5f)*(1.0f/60.0f));
        func_L00_0033C0D0(p,pos,v,D_L11_001B2378,1);
        v[2]=-(func_002A7878(3.0f,5.0f)*(1.0f/60.0f));
        func_L00_0033C0D0(p,pos,v,D_L11_001B2368,1);
        v[2]=-(func_002A7878(4.0f,8.0f)*(1.0f/60.0f));
        func_L00_0033C0D0(p,pos,v,D_L11_001B2358,1);
    }
}
