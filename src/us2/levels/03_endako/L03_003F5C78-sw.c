#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define Q(p,o) (*(Quad *)((u8 *)(p)+(o)))
extern u8 D_L03_00189EA0[], D_L03_001BFB80[], D_L03_001B9980[];
typedef struct {u8 pad[0x80]; float position[4];} HeroState;
extern HeroState D_L03_00189E20;
extern u8 D_001395C2[2] NOT_SDA;
extern u8 *D_L03_001FE700[], *D_L03_001B2A1C;
extern u8 D_L03_00188660[];
extern int D_L03_001B104C __attribute__((sda)), D_L03_001B106C __attribute__((sda)), D_L03_001A8F00 __attribute__((sda));
extern float D_L03_001B1054 __attribute__((sda)), D_L03_001B103C __attribute__((sda)), D_L03_001B1068 __attribute__((sda));
extern int D_L03_001B1044 __attribute__((sda)), D_L03_001B1040 __attribute__((sda));
extern float D_L03_001B1030[3] SDATA(D_L03_001B1030);
extern float D_L03_001B105C __attribute__((sda));
extern int D_L03_001B2548;
extern void func_L03_003F5590(void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern float func_00283248(float,float);
extern int func_00288AA0(void *,int);
extern void func_00288BE8(void *);
extern void func_L00_003294F0(void *,int);
extern void func_L01_00323310(int,int);
extern int func_002B3868(void *);
extern void func_002A7470(void *,int,int,int);
extern void func_L03_003F6458(void *,int);
extern int func_00282948(void *);
extern void func_L03_003F62C8(void *);
extern float func_00282C48(float);
extern void func_002AA2E8(void *,float,float);
extern float func_002A78D8(float,float);
extern void func_0029FC20(void *,int,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002E5CF8(int,int,void *);
extern int func_L03_003D9820(void *,void *,void *,int);
extern void func_L03_003F68E8(void *,int);
extern int func_002A7820(int,int);
extern int func_US2_002AF9C8(void *,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_L03_003E18D8(void *,void *,void *,void *,int,float,float,int,int,float);
extern void func_00283098(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_L03_003D09D0(void *,int,void *,void *,void *,int,int,int);
extern float func_002A7878(float,float);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern float func_002AA800(void *,int,float,float);
extern void func_0032DA58(void *,void *,void *,float);
extern float func_00283B98(float,float);
extern float func_00283CE0(int);
extern void func_US2_002A7AA8(void *,int,int);
extern void func_L00_002D7140(int);
extern void func_0029F338(void *);
extern void func_002A0430(int);
extern void func_002E59F8(int);
extern void func_L03_003F6080(void *);
typedef struct {
    u8 pad[0x80];
    int paths[3], activation[2], trigger, ready[2];
    u8 padA0[0x2A0-0xA0];
    float angles[4];
    u8 pad2B0[0x2E8-0x2B0];
    float blend[4], target[2];
} AttackState;

void func_US2_L03_003F5C78(u8 *e) {
    u8 *s=*(u8 **)(e+0x68);
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[16] __attribute__((aligned(16)));
    int i;
    func_L03_003F5590(e);
    switch(e[0x20]) {
    case 1:
        if (func_002ACBC8(D_L03_00189EA0,((AttackState *)s)->activation[I(s,0x2D4)])) {
            u8 *p;
            func_002A7750(e,2,-1);
            H(e,0x34)=(H(e,0x34)&0xFFBE)|0x1000;
            I(e,0x98)=I(*(u8 **)(e+0x24),0x10);
            p=D_L03_001FE700[((AttackState *)s)->paths[I(s,0x2D4)]];
            I(s,0x2D8)=0; *(u8 **)(s+0x2CC)=p; I(s,0x2DC)=0;
            qcopy(s+0x290,p+0x10);
            F(s,0x298)-=7.0f;
            qcopy(e+0x10,s+0x290); qzero(s+0x2A0);
            F(s,0x2A8)=func_00283248(D_L03_00189E20.position[0]-F(e,0x10),D_L03_00189E20.position[1]-F(e,0x14));
            F(s,0x2D0)=0.16666667f;
        }
        if(func_002ACBC8(D_L03_00189EA0,I(s,0x94))) func_002A7750(e,4,-1);
        break;
    case 2:
        if(func_002ACBC8(D_L03_00189EA0,((AttackState *)s)->ready[I(s,0x2D4)])) {
            D_001395C2[0]=1; func_002A7750(e,3,-1);
            I(s,0x2DC)=I(*(u8 **)(s+0x2CC),0)-1;
        }
        break;
    case 3:
        if(I(s,0x2D8)==I(s,0x2DC)) {
            if(I(s,0x2D4)==0) {
                I(e,0x98)=0; H(e,0x34)=(H(e,0x34)|0x41)&0xEFFF;
                func_002A7750(e,1,-1); I(s,0x2D4)++;
            } else {
                I(e,0x98)=0; H(e,0x34)=(H(e,0x34)|0x41)&0xEFFF;
                func_002A7750(e,4,-1);
            }
        }
        break;
    case 4:
        if(D_L03_001B104C && func_002ACBC8(D_L03_00189EA0,I(s,0x94))) {
            if(D_L03_001B106C) func_002A7750(e,5,-1);
            else if(func_00288AA0(D_L03_001BFB80,0x36)) {
                D_L03_001B106C=1;func_00288BE8(D_L03_001BFB80);func_002A7750(e,5,-1);
            }
        }
        break;
    case 5:
        if(H(e,0x96)>=21 && D_L03_001A8F00!=2) {
            u8 *p;
            func_002A7750(e,6,2);
            H(e,0x34)=(H(e,0x34)&0xFFBE)|0x1000;
            I(e,0x98)=I(*(u8 **)(e+0x24),0x10);
            p=D_L03_001FE700[I(s,0x88)];
            I(s,0x2DC)=I(s,0x320); *(u8 **)(s+0x2CC)=p; I(s,0x2D8)=I(s,0x320);
            qcopy(s+0x290,p+I(s,0x320)*16+0x10); qcopy(e+0x10,s+0x290);
            F(s,0x2A8)=func_00283248(D_L03_00189E20.position[0]-F(e,0x10),D_L03_00189E20.position[1]-F(e,0x14));
            F(e,0xF8)=F(s,0x2A8);
            {u8 *linked=D_L03_001B2A1C+(I(s,0xA8)<<8);
            F(s,0x2D0)=0.16666667f; I(s,0x2E0)=60; F(s,0x298)-=7.0f;
            func_L00_003294F0(linked,0);}
            func_L01_00323310(I(s,0xB0),-1);
        }
        break;
    case 6:
        if(func_002B3868(e)) {
            if(e[0x43]!=0) func_002A7470(e,0,0,5);
            if(e[0x94]!=4) func_L03_003F6458(e,e[0x94]!=8);
        }
        if(I(s,0x2D8)==I(s,0x2DC) && func_00282948(s+0x2E0)) func_L03_003F62C8(e);
        break;
    case 7: {
        int done=1;
        F(s,0x178)=F(s,0x2F8); F(s,0x1F8)=F(s,0x2FC);
        if(func_00282C48(F(s,0x158)-F(s,0x2F8))>0.01f) done=0;
        else if(func_00282C48(F(s,0x1D8)-F(s,0x2FC))>0.01f) done=0;
        if(done) {
            if(F(s,0x2F8)!=0 && F(s,0x2FC)!=0) {if(e[0x43]!=3) func_002A7470(e,3,0,5);}
            else if(F(s,0x2F8)!=0) {if(e[0x43]!=1) func_002A7470(e,1,0,5);}
            else {if(e[0x43]!=2) func_002A7470(e,2,0,5);}
            func_002A7750(e,8,-1);
            {float first=((AttackState *)s)->target[0],second=((AttackState *)s)->target[1];
            ((AttackState *)s)->blend[2]=(((AttackState *)s)->blend[0]=first,((AttackState *)s)->blend[1]=second,((AttackState *)s)->blend[3]=0.0f);}
        }
        break;
    }
    case 8: {
        int done=1,n;
        for(i=0;i<2;i++) {
            if(((AttackState *)s)->target[i]!=0) {
                func_002AA2E8(&((AttackState *)s)->blend[i],-((AttackState *)s)->target[i],D_L03_001B1054*0.0002908882452175021f);
                F(s,0x178+i*0x80)=((AttackState *)s)->blend[i];
                if(func_00282C48(((AttackState *)s)->blend[i]+((AttackState *)s)->target[i])>0.01f) done=0;
                if(((D_L03_001B2548+i*4)&7)==0) {
                    Q(b,0)=0; b[1]=func_002A78D8(0,0.1f);b[2]=func_002A78D8(0,0.1f);b[3]=1;
                    Q(a,0)=Q(b,0);func_0029FC20(e,i+2,c);func_002830C0(a,a,c);
                    func_00282F20(b,c,D_L03_001B103C*0.016666668f);
                    func_002E5CF8(3,0,e);n=func_L03_003D9820(e,a,b,s[0x34]);func_L03_003F68E8(e,n);
                }
            }
        }
        if(done) {F(s,0x2F8)=F(s,0x2FC)=0;func_002A7750(e,6,2);}
        break;
    }
    case 9: break;
    case 10:
        if(func_002B3868(e)) {
            switch(S(s,0x3C2)) {
            case 3: I(s,0x33C)=func_002A7820(4,6); break;
            case 2: I(s,0x33C)=func_002A7820(3,5); break;
            case 1: default: I(s,0x33C)=func_002A7820(2,3); break;
            }
            if(e[0x43]!=4) func_002A7470(e,4,0,5);
        }
        if(e[0x60]&2) func_002A7750(e,11,-1);
        break;
    case 11: {
        int n;
        if(func_002B3868(e) && e[0x43]!=6) func_002A7470(e,6,0,5);
        if(func_US2_002AF9C8(e,2.0f)) {
            func_0029FCC0(e,4,a);qcopy(b,e+0xC0);b[2]=0;
            func_00282F20(b,b,D_L03_001B1068*0.016666668f);
            n=s[0x36];func_002E5CF8(4,0,e);
            func_L03_003E18D8(e,a,b,b,30,(float)n,(float)n,80,1,1.0f);
        }
        if((e[0x60]&2) && func_00282948(s+0x33C)) func_002A7750(e,6,2);
        break;
    }
    case 12: {
        int n;
        if(func_00282948(s+0x2E4)) {func_002A7750(e,6,2);break;}
        if(H(e,0x96) && H(e,0x96)%D_L03_001B1044==0) {
            func_0029FCC0(e,I(s,0x330)>0?6:5,a);
            {float limit=D_L03_001B105C, height, side, lateral;
            n=D_L03_001B1040; I(s,0x330)=-I(s,0x330);
            height=limit-a[2];
            Q(c,0)=0; c[0]=0.016666668f;
            side=(float)I(s,0x330)*0.016666668f;
            lateral=D_L03_001B1030[S(s,0x3C2)-1]*side;
            c[2]=2*height/(float)n; c[1]=lateral;}
            Q(b,0)=Q(c,0);func_00283098(b,b,e+0xC0);
            func_00282D30(c,b,(float)(n>>1));func_00282CC0(c,c,a);func_00282CF0(c,s+0x50,c);c[2]=0;
            func_00282F20(c,c,D_L03_001B1030[S(s,0x3C2)-1]*0.016666668f);
            func_L03_003D09D0(e,0,a,b,c,n,300,s[0x35]);
        }
        break;
    }
    case 13:
        if(func_002B3868(e) && e[0x43]!=8) func_002A7470(e,8,0,5);
        if(e[0x60]&2) {func_002A7750(e,10,4);func_L03_003F6458(e,1);I(s,0x2D0)=0;}
        break;
    case 14:
        if(func_002B3868(e)) {if(e[0x43]!=8)func_002A7470(e,8,0,5);}
        else if(e[0x43]!=0)func_002A7470(e,0,0,5);
        if(H(e,0x96)%45==0) {
            Q(b,0)=0;b[0]=func_002A7878(-2,2);b[1]=func_002A7878(-4,4);b[2]=func_002A7878(-1,3);
            Q(a,0)=Q(b,0);func_00283098(a,a,e+0xC0);func_00282CC0(a,a,e+0x10);func_002E5CF8(2,0,e);
            func_0032C700(a,0,25,20,20,20,45,1,0,0,0,0,1,20);
        }
        func_002AA800(s+0x2A0,0,0.26179942f,0.0014544413425028324f);
        ((AttackState *)s)->angles[1]=((AttackState *)s)->angles[0];I(s,0x2DC)=I(s,0x2D8);
        if(H(e,0x96)>=180) {
            func_00282CF0(a,D_L03_001B9980,e+0x10);func_00282F20(a,a,1);func_0032DA58(e,e+0x10,a,0);
            func_002A7750(e,15,-1);I(s,0x2CC)=0;F(s,0x2D0)=-0.083333336f;
        } else F(s,0x2C0)=func_00283B98(F(s,0x2C0),(float)H(e,0x96)*0.0024240687489509583f);
        break;
    case 15: {
        int n;
        float x;
        if(H(e,0x96)%15==0) {
            Q(b,0)=0;b[0]=func_002A7878(-2,2);b[1]=func_002A7878(-2,2);b[2]=func_002A7878(0,3);
            Q(a,0)=Q(b,0);func_00283098(a,a,e+0xC0);func_00282CC0(a,a,e+0x10);func_002E5CF8(2,0,e);
            func_0032C700(a,0,25,20,20,20,45,0,0,0,0,0,1,20);
        }
        func_002AA800(s+0x2A0,0,0.78539824f,0.02617994323372841f);func_002AA800(s+0x2A4,0,1.5707965f,0.02617994323372841f);
        x=func_00283CE0(H(e,0x96));F(s,0x2D0)-=x*9.259259968530387e-05f;F(s,0x298)+=F(s,0x2D0);
        if(!S(s,0x3C0) && F(s,0x298)<F(s,0x2B8)-1) {S(s,0x3C0)=1;func_US2_002A7AA8(e,0,3);}
        if(F(s,0x298)<F(s,0x2B8)-12) {
            func_L00_002D7140(I(s,0x2C8));func_L00_003294F0(D_L03_001B2A1C+(I(s,0xA4)<<8),0);func_L01_00323310(I(s,0xB4),I(s,0xB8));
            if(I(s,0x2C4))func_0029F338(*(void **)(s+0x2C4));
            D_001395C2[1]=1;func_002A0430(e[0xB0]);n=I(s,0x3CC);
            if(n!=-1) {u8 *sound=D_L03_00188660+n*0x70;if(*(u8 **)(sound+0x88)==e && sound[0x74])func_002E59F8(n);}
            I(s,0x3CC)=-1;func_0029F338(e);return;
        }
        break;
    }
    }
    func_L03_003F6080(e);
}
