#include "include_asm.h"

#include "common.h"
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
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
extern void func_PAL_L12_0041F568(void *);
extern int func_002B1C20(void *,void *);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_L12_0041A6D0(void *,int);
extern int func_PAL_002B5E30(void *,float);
extern void func_002B6D28(void);
extern void func_L12_0041A730(int);
extern int func_L12_0041A578(void *,int);
extern int func_PAL_L12_0041F710(void *);
extern float func_00283B98(float,float);
extern int func_00282948(void *);
extern int func_002B3868(void *);
extern void func_PAL_L02_003CDF48(void *);
extern void func_L12_0041A530(void *);

void func_PAL_L12_0041F0F0(char *obj) {
    char *s=P(obj,0x68);
    int r;
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
    func_PAL_L12_0041F568(obj);
    switch(B(obj,0x95)) {
    case 1:
        { int flags=func_002B1C20(obj,s+0x60);
        if(flags&1) {func_0029F338(obj);return;}
        if(flags&2) func_002A7750(obj,4,0); }
        break;
    case 0: break;
    }
    switch(B(obj,0x20)) {
    case 2:
        if((B(obj,0x60)&2) && func_L12_0041A6D0(obj,W(s,0x11C))) {
            func_002A7750(obj,8,-1);
            r=func_002A77E0(4);
            if(r==W(s,0x258)) {if(r!=3) r++; else r=0;}
            goto set_attack_animation;
        }
        break;
    case 8:
        func_PAL_002B5E30(obj,F(s,0x228));
        if(D_L12_001A63A8.f72==3 && D_L12_001A63A8.f6C<6000) {
            func_002B6D28(); func_002A7750(obj,5,-1);
        }
        break;
    case 5:
        if(!D_L12_001A63A8.f68 && D_L12_001A63A8.f24==-1) {
            func_L12_0041A730(W(s,0x114));
            func_002A7750(obj,6,-1);
            if(B(obj,0x43)) func_PAL_002A7E68(obj,0,0,17);
            W(s,0x220)=func_L12_0041A578(obj,W(s,0x224));
        } else if(B(obj,0x60)&2) {
            r=func_002A77E0(4);
            if(r==W(s,0x258)) {if(r!=3)r++;else r=0;}
            if(B(obj,0x43)!=r+1) func_PAL_002A7E68(obj,r+1,0,17);
            W(s,0x258)=r;
        }
        break;
    case 6:
        if(func_PAL_L12_0041F710(obj)) {
            if(W(s,0x220)==W(D_L12_001FEAC0[W(s,0x110)],0)-1) {
                func_002A7750(obj,3,-1);
                if(B(obj,0x43)!=9)func_PAL_002A7E68(obj,9,0,17);
            } else {
                func_002A7750(obj,7,-1);
                if(B(obj,0x43))func_PAL_002A7E68(obj,0,0,17);
                W(s,0x22C)=100;
                F(s,0x228)=func_00283B98(F(obj,0xF8),3.141590118408203f);
            }
        }
        break;
    case 7:
        func_PAL_002B5E30(obj,F(s,0x228));
        if(func_00282948(s+0x22C) && func_L12_0041A6D0(obj,W(s,0x11C))) {
            func_002A7750(obj,8,-1);
            r=func_002A77E0(4);
            if(r==W(s,0x258)){if(r!=3)r++;else r=0;}
set_attack_animation:
            if(B(obj,0x43)!=r+1)func_PAL_002A7E68(obj,r+1,0,17);
            W(s,0x258)=r;
            W(s,0x11C)++;
        }
        break;
    case 3:
        if(B(obj,0x60)&2) {
            W(s,0x220)=0; W(s,0x224)=0; W(s,0x11C)=0;
            func_002A7750(obj,10,-1);
        }
        break;
    case 10:
        if(func_002B3868(obj)) {
            W(s,0x25C)=21; W(obj,0x98)=0;
            U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        }
        if(func_00282948(s+0x25C)) {
            func_002A7750(obj,1,-1);
            qcopy(obj+0x10,s+0x210);
        }
        func_PAL_L02_003CDF48(obj);
        break;
    case 1:
        W(obj,0x98)=0; U(obj,0x34)=(U(obj,0x34)|0x41)&0xEFFF;
        break;
    }
    func_L12_0041A530(obj);
}
