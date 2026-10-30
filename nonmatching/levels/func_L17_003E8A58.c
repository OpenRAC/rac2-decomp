/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 936 bytes, expected 964.
 * us2: 17_smolg: 936 bytes, expected 964.
 * pal: func_L17_003E8A58 is in neither catalogue of pal.
 * Complete fighter initialization groups, proximity, impact filtering and damage update.
 * Actual entry consumes object pointer a0; an existing caller in L17_003E7068-g8.c still
 * declares this helper void(void), a separate native-interface issue not changed
 * here.936/964 bytes; frame0x20 instead of0x30 and initialization allocation differ.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
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
void func_L17_003E8A58(char *object)
{
    char *state=P(object,0x68),*hit;
    int index;
    if(!U(object,0x20)) {
        F(object,0x2c)=F(P(object,0x24),0x24)*0.85f;
        index=I(state,0x6b8);
        if((unsigned)(index+1)>=2) F(object,0x18)=F(D_L17_001B2C1C+index*256,0x18)+1.4f;
        *(Q *)(state+0x6c0)=*(Q *)(object+0x10);
        F(state,0x110)=D_L17_001B0E40;
        I(state,0x6e8)=0;I(state,0x6ec)=0;F(state,0x6cc)=F(object,0xf8);
        U(state,0x48)=func_00283CF0(15.0f);U(state,0x4a)=func_00283CF0(12.8f);
        U(state,0x70)=14;U(state,0x71)=13;U(state,0x76)=8;U(state,0x29)=1;U(state,0x75)=7;U(state,0x77)=9;
        U(state,0xd3)=12;F(state,0x80)=D_L17_001B0F38*0.016666668f;F(state,0x84)=0.00416666688f;
        F(state,0x94)=D_L17_001B0E40+0.1f;
        U(state,0xcc)=7;U(state,0xcd)=20;U(state,0xce)=4;U(state,0xcf)=9;U(state,0xd2)=6;U(state,0xd5)=1;
        I(state,0xa8)=3;F(state,0x7c)=0.333333343f;F(state,0x88)=0.00833333377f;F(state,0x8c)=0.00138888892f;
        F(state,0x9c)=0.4f;F(state,0x700)=(float)U(state,0x34);*(u16 *)(state+0x26)=60;
        F(state,0xb8)=0.01f;F(state,0x90)=D_L17_001B0E40;I(state,0x14c)=I(state,0x684);F(state,0xa0)=40.0f;
        F(state,0x11c)=D_L17_001B0E48;F(state,0x120)=1.308997035f;F(state,0x13c)=0.01111111138f;
        I(state,0x148)|=16;U(state,0x28)=3;F(state,0x30)=1.0f;F(state,0x118)=D_L17_001B0E48;H(state,0x98)=0;
        if(I(state,0x680)==-1 || I(state,0x684)==-1) {func_0029F338(object);return;}
        if((unsigned)(I(state,0x6b8)+1)<2) func_002A7750(object,3,0);else func_002A7750(object,1,5);
        I(state,0x730)=1;P(state,0x720)=P(state,0x744);
        if(P(state,0x744)) I(P(state,0x744),0)=-1;
        I(state,0x750)=func_L02_0032E508(object,I(state,0x684),state+0x280,32);
    }
    if(U(object,0x31) && func_00282E48(object+16,D_L17_001B9BC0)<24.0f) {func_002A93B0(object);U(object,0x6f)=22;}
    hit=func_002A9640(object,0x10000,1);
    if(hit && P(hit,0x20) && (H(P(hit,0x20),0xaa)==0x31a || H(P(hit,0x20),0xaa)==0x1256 || H(P(hit,0x20),0xaa)==0x1305)) U(object,0xa8)=255;
    else if(U(object,0x20)!=1) func_002B0ED8(object,state+0x60,0);
    H(state,0x69e)=func_002B3BA8(object,I(state,0x680),0,0,0.0f,0.0f);
    I(state,0x6a4)=I(state,0x250);
}
