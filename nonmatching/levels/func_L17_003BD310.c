/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1524 bytes, expected 1548.
 * us2: 17_smolg: 1524 bytes, expected 1548.
 * pal: func_L17_003BD310 is in neither catalogue of pal.
 * Complete path-linked hazard initialization, sound lifetime, six states and both destruction
 * forms. Separate class-specific runtime reloads and true pointer/float helper contracts
 * retained.1524/1548 bytes, frame0x60 rather than0x50; allocation and source scopes remain
 * unresolved.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern char *D_L17_001FE880[],*D_L17_001B2C1C;
extern char D_00188660[],D_00189EA0[],D_L17_001A8F20[];
extern char D_L17_001AFCF8[],D_L17_001AFD28[];
extern int D_L17_001B2748;
extern float D_L17_001AFCD0 __attribute__((sda)),D_L17_001AFCD4 __attribute__((sda)),D_L17_001AFCD8 __attribute__((sda)),D_L17_001AFCDC __attribute__((sda));
extern float D_L17_001AFCE0 __attribute__((sda)),D_L17_001AFCE4 __attribute__((sda)),D_L17_001AFCE8 __attribute__((sda)),D_L17_001AFCEC __attribute__((sda));
extern int D_L17_001AFCF0 __attribute__((sda));
extern float func_00282E80(void *,void *),func_00282E48(void *,void *),func_00283CE0(int),func_002A7878(float,float);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern void func_0026FEB8(const char *,...);
extern void func_002A7750(void *,int,int);
extern void func_L17_003BCC30(void *),func_L17_003BCEC0(void *);
extern void *func_002A9640(void *,u32,int);
extern int func_002B3868(void *),func_00282948(void *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void func_002B0A68(void *,int,void *,u8,float,float,float,float);
extern char *func_00273730(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_L00_00326110(void *,int,float);
extern void func_0029F338(void *);
/* Updates a path-linked hazard, its movement sound, and its destruction effects. */
void func_L17_003BD310(char *object)
{
    char *state=P(object,0x68),*voice,*path,*linked,*created;
    int index,count;
    float a,b;
    F(state,0x20)=H(object,0xaa)==0x8ad?D_L17_001AFCD4:D_L17_001AFCE4;
    F(state,0x24)=H(object,0xaa)==0x8ad?D_L17_001AFCD0:D_L17_001AFCE0;
    F(state,0x28)=H(object,0xaa)==0x8ad?D_L17_001AFCD8:D_L17_001AFCE8;
    F(state,0x10)=H(object,0xaa)==0x8ad?D_L17_001AFCDC:D_L17_001AFCEC;
    I(object,0x78)=(D_L17_001B2748+H(object,0xb2))%60<15?0x80ffffff:0x80404040;
    if(H(object,0xaa)==0x8d8 || H(object,0xaa)==0x8ad) {
        if(U(object,0x20)==2 && func_00282E80(object+16,D_00189EA0)<80.0f) {
            voice=D_00188660+I(state,0x2c)*0x70;
            if(P(voice,0x88)!=object || !U(voice,0x74)) I(state,0x2c)=func_002E5CF8(0,4,object);
        } else {
            index=I(state,0x2c);
            if(index!=-1) {
                voice=D_00188660+index*0x70;
                if(P(voice,0x88)==object && U(voice,0x74)) func_002E59F8(index);
            }
            I(state,0x2c)=-1;
        }
    }
    switch(U(object,0x20)) {
    case 0:
        I(state,0x2c)=-1;I(state,0x34)=0;
        if(I(state,0)==-1) break;
        path=D_L17_001FE880[I(state,0)];
        if(I(path,0)<2) {func_0026FEB8(D_L17_001AFCF8,H(object,0xaa),H(object,0xb2));func_0026FEB8(D_L17_001AFD28);break;}
        *(u16 *)(object+0x32)=0x180;U(object,0x30)=255;
        if(I(state,4)==-1) F(state,8)=0.0f;
        else {
            index=I(state,4);count=0;
            do {linked=P(D_L17_001B2C1C+index*256,0x68);index=I(linked,4);count++;} while(index!=-1);
            F(state,8)=func_00283CE0(count);
        }
        F(state,0xc)=F(state,8)*4.0f;
        path=D_L17_001FE880[I(state,0)];F(path,0x1c)=func_00282E48(path+16,path+32);
        I(state,0x14)=0;F(state,0x18)=0;
        if(I(state,4)!=-1) {P(P(D_L17_001B2C1C+I(state,4)*256,0x68),0x1c)=object;I(state,0x34)=1;func_002A7750(object,3,-1);}
        else func_002A7750(object,2,-1);
        U(object,0x20)=1;break;
    case 1:
        func_L17_003BCC30(object);U(object,0x20)=D_L17_001AFCF0 && !I(state,0x34)?2:3;break;
    case 2:
    case 3:
        if(U(object,0x20)==2 && D_L17_001AFCF0) func_L17_003BCEC0(object);
        else if(I(state,4)!=-1) {
            linked=D_L17_001B2C1C+I(state,4)*256;
            if(!linked || U(linked,0x20)==254 || U(linked,0x20)==253) func_002A7750(object,4,-1);
        }
        if(func_002A9640(object,0x4010000,1)) func_002A7750(object,5,-1);
        U(object,0xa8)=255;break;
    case 4:
        if(func_002B3868(object)) I(state,0x30)=5;
        if(func_00282948(state+0x30)) func_002A7750(object,5,-1);
        break;
    case 5:
        F(object,0x1c)=1000000.0f;
        if(H(object,0xaa)==0x8ad) {
            func_0032C700(object+16,0,10,10,10,10,20,0,1,0,0,0,10.0f,20.0f);
            func_002B0A68(object,11,D_L17_001A8F20,255,3.0f,6.0f,3.0f,6.0f);
            a=func_002A7878(-10.0f,10.0f);b=func_002A7878(20.0f,30.0f);
            created=func_00273730(object,2,0x8ad,2,object+16,object+0xf0,D_L17_001A8F20,255,a,b);
            if(created) I(P(created,0x68),0x2c)=0;
        } else {
            func_0032C700(object+16,0,10,10,10,10,20,0,1,0,0,0,3.0f,20.0f);
            func_002B0A68(object,31,D_L17_001A8F20,255,3.0f,6.0f,3.0f,6.0f);
        }
        func_L00_00326110(object,1,0.0f);func_0029F338(object);break;
    }
}
