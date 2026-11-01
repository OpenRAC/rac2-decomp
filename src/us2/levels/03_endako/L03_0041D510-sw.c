#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern float D_L03_001B1BA4 SDATA(D_L03_001B1BA4) __attribute__((sda));
extern float D_L03_001B1BA0 SDATA(D_L03_001B1BA0) __attribute__((sda));
extern float D_L03_001B1B90 SDATA(D_L03_001B1B90) __attribute__((sda));
extern float D_L03_001B1B98 SDATA(D_L03_001B1B98) __attribute__((sda));
extern float D_L03_001B1BB0[4] SDATA(D_L03_001B1BB0) __attribute__((sda));
typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x17A0]; u8 *target;
    u8 pad1834[0xA60]; int state;
} Player;
extern Player D_00189E20;
extern u8 D_L03_001B9980[];
extern u8 D_L03_001A8F20[] NOT_SDA __attribute__((sda));
extern float D_L03_001B1B98_abs[] __asm__("D_L03_001B1B98") __attribute__((sda));
extern int D_L03_001A9044;
extern int D_L03_001A903C[] __attribute__((sda));
extern u8 D_001A7A60[32] __attribute__((sda));
extern u8 *D_L03_001B2B0C[] __attribute__((sda));
extern u8 *D_L03_001B2B0C_gp SDATA(D_L03_001B2B0C) __attribute__((sda));
extern u8 *D_L03_001BFDD8 NOT_SDA;
extern void func_US2_L03_0041E138(void *);
extern int func_002ACBC8(void *,int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern float func_00282E80(void *,void *);
extern int func_002B3890(void *);
extern float func_002A78D8(float,float);
extern int func_002B1C20(void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern int func_002E5E58(int,int,void *);
extern void func_US2_002B1880(int,int);
extern void func_US2_002A7AA8(void *,int,int);
extern void func_0029F338(void *);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float),func_002A7940(void),func_00283180(float),func_00283198(float);
extern void func_L02_0032EF10(void *,void *,void *,int,float);
extern int func_002B3868(void *),func_L01_00321178(void *,void *);
extern float func_00283248(float,float);
extern int func_L01_00322288(void *,float);
extern int func_00282948(void *),func_002B38B8(void *);
extern int func_L03_0032CFD8(void *,void *,int,float,float,float);
extern int func_L02_00331440(void *,void *,int,float,float,float);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern float func_002A89A8(void *,int,float);
extern int func_00277258(void *,int,void *,float);
extern void func_L00_003294F0(void *,int),func_L03_0041D128(void *);
extern int func_L02_002EF388(void *,void *,void *,int,int);
extern void func_002830C0(void *,void *,void *);
extern int func_L03_0041D1D8(void *);
extern void func_L03_0041CEB0(void *);

/* Updates the actor's combat and movement states, including hiding and respawning. */
void func_US2_L03_0041D510(u8 *e) {
    u8 *s=P(e,0x68);
    Vec a,b;
    float speed,scale,angle;
    int hit;
    func_US2_L03_0041E138(e);
    speed=I(s,0x29c) ? D_L03_001B1BA4 : D_L03_001B1BA0;
    scale=I(s,0x29c) ? 1.0f : D_L03_001B1B90;
    switch(e[0x95]) {
    case 0:
        if(I(s,0x2a8)!=-1) {
            hit=func_002ACBC8(D_L03_001B9980,I(s,0x2a8));
            if(!hit) { e[0x31]=0; U(e,0x34)|=1; return; }
            e[0x31]=1; U(e,0x34)&=0xfffe;
        }
        if(I(s,0x204)!=1) {
            if(H(s,0x2d6)) {
                func_002A7750(e,3,1);
                H(s,0x2d6)=0;
                if(H(s,0x2d0)<300) H(s,0x2d0)=func_002A7820(480,600);
            }
            break;
        }
        /* Fall through to the active-state transition. */
    case 1:
        if(I(s,0x204)==1) {
            func_002A7750(e,5,2);
            if(e[0x43]) func_002A7470(e,0,0,10);
        } else if(func_00282E80(e+0x10,D_00189E20.position)>24.0f && H(s,0x2d0)==0) func_002A7750(e,1,0);
        break;
    case 2:
        if(func_002B3890(e)) { float upper=D_L03_001B1B98_abs[1]; F(s,0x2e0)=func_002A78D8(D_L03_001B1B98,upper)*0.017453294f; }
        if(I(s,0x204)!=1) {
            func_002A7750(e,3,1);
            if(e[0x43]) func_002A7470(e,0,0,10);
            H(s,0x2d0)=func_002A7820(580,600);
        }
        break;
    case 3:
        hit=func_002B1C20(e,s+0x140);
        if(hit&1) {
            func_00283098(&a,D_L03_001B1BB0,e+0xc0);
            func_00282CC0(&a,&a,e+0x10);
            func_002E5CF8(2,0,e);
            func_002AC728(e,&a,-1,0.333f,0.0f);
            func_00282CF0(&b,e+0x10,D_00189E20.position);
            b.f[2]=0;
            func_00282F20(&b,&b,0.10000001f);
            func_002B0A68(e,31,D_L03_001A8F20,3.0f,6.0f,3.0f,6.0f,255);
            if(D_00189E20.state==49) {
                D_L03_001A9044=D_L03_001A9044+1;
                if(D_L03_001A9044>=10 && !D_001A7A60[28]) {
                    D_001A7A60[28]=1; func_002E5E58(1,0,0); func_US2_002B1880(0x1233,-1); D_L03_001A903C[0]=1;
                }
            }
            func_US2_002A7AA8(e,0,3);
            if(I(s,0x2a4)) {
                func_002A7750(e,8,4); I(e,0x98)=0; U(e,0x34)=(U(e,0x34)|0x41)&0xefff;
            } else {func_0029F338(e);return;}
        } else if(hit&2) {
            if(I(s,0x204)==1) func_002A7750(e,6,2);
            else {func_002A7750(e,3,1); H(s,0x2d0)=func_002A7820(580,600);}
        }
        break;
    }
    switch(e[0x20]) {
    case 1:
        if(e[0x31] && U(e,0x96)>10 && func_00282E80(e+0x10,D_L03_001B9980)<50.0f) {
            speed=func_002A7878(2.0f,5.0f); angle=func_002A7940();
            F(s,0x2c0)=func_00283180(angle)*speed;
            F(s,0x2c4)=func_00283198(angle)*speed; I(s,0x2c8)=0;
            func_00282CC0(s+0x2c0,s+0x2c0,s+0x2b0);
            a.q=*(Quad *)(s+0x2b0);
            func_L02_0032EF10(&a,s+0x2c0,s+0x2c0,I(s,0x290),1.5f);
            func_002A7750(e,2,-1);
        }
        break;
    case 2:
        if(func_002B3868(e)) I(s,0x88)&=~0x10;
        if((func_L01_00321178(e,s+0x2c0)&0x80)||U(e,0x96)>300) func_002A7750(e,1,-1);
        break;
    case 3:
        {
            float heading;
            if(D_00189E20.state==49) {
                u8 *target=D_00189E20.target;
                heading=func_00283248(F(target,0x10)-F(e,0x10),F(target,0x14)-F(e,0x14));
            } else {
                heading=func_00283248(D_00189E20.position[0]-F(e,0x10),D_00189E20.position[1]-F(e,0x14));
            }
            func_L01_00322288(e,heading);
        }
        if(U(e,0x96)>10) func_002A7750(e,4,-1);
        break;
    case 4:
        if(func_002B3868(e)) {
            I(s,0x88)|=0x10;
            speed=func_002A7878(2.0f,5.0f); angle=func_002A7940();
            F(s,0x2c0)=func_00283180(angle)*speed;
            F(s,0x2c4)=func_00283198(angle)*speed; I(s,0x2c8)=0;
            func_00282CC0(s+0x2c0,s+0x2c0,s+0x2b0);
            a.q=*(Quad *)(s+0x2b0);
            func_L02_0032EF10(&a,s+0x2c0,s+0x2c0,I(s,0x290),1.0f);
        }
        {
            float heading;
            if(D_00189E20.state==49) {
                u8 *target=D_00189E20.target;
                heading=func_00283248(F(target,0x10)-F(e,0x10),F(target,0x14)-F(e,0x14));
            } else {
                heading=func_00283248(D_00189E20.position[0]-F(e,0x10),D_00189E20.position[1]-F(e,0x14));
            }
            func_L01_00322288(e,heading);
        }
        if((func_L01_00321178(e,s+0x2c0)&0x80)||U(e,0x96)>300) func_002A7750(e,3,-1);
        break;
    case 5:
        if(func_002B3868(e)) func_002E5CF8(5,0,e);
        if(func_00282948(s+0x2e4) && I(s,0xd0)>60) {I(s,0x2e4)=60; F(s,0x2e0)=-F(s,0x2e0);}
        angle=func_00283248(F(s,0x1f0)-F(e,0x10),F(s,0x1f4)-F(e,0x14));
        func_L01_00322288(e,angle);
        func_L03_0032CFD8(e,s+0x1f0,16,F(s,0x2e0),-1.0f,-1.0f);
        if(U(e,0x96)>60 && func_00282E80(e+0x10,D_00189E20.position)<scale*speed) {
            func_002A7750(e,6,-1);
            if(e[0x43]!=1) func_002A7470(e,1,0,10);
        }
        break;
    case 6: {
        if(U(e,0x96)>45) {
            func_002A7750(e,5,-1); if(e[0x43]) func_002A7470(e,0,0,10);
        } else if(U(e,0x96)>10) {
            qcopy(&a,e+0x10); a.f[2]+=0.25f;
            func_002A8C28(e,&a,0x4000001,0,1,0,speed*1.25f,(float)s[0x34],1.0f);
        }
        {
            float *target=(float *)(s+0x1f0);
            angle=func_00283248(F(s,0x1f0)-F(e,0x10),F(s,0x1f4)-F(e,0x14)); func_L01_00322288(e,angle);
            {
                float x=target[0];
                angle=func_00283248(x-F(e,0x10),F(s,0x1f4)-F(e,0x14));
                func_L02_00331440(e,target,16,angle,-1.0f,-1.0f);
            }
        }
        break;
    }
    case 8:
        if(func_002B38B8(e) && func_00282948(s+0x2d8)) {
            if(I(s,0x2a0)!=-1) {
                qcopy(&a,D_L03_001B2B0C_gp+I(s,0x2a0)*128+0x30);
                a.f[2]=func_002A89A8(&a,0,0.5f); qcopy(&b,&a);
                b.f[2]+=F(s,0x50)+0.1f;
                func_00277258(&b,0,e,F(s,0x50));
                if(!D_L03_001BFDD8 || H(D_L03_001BFDD8,0xaa)!=0xff3) {
                    func_L00_003294F0(e,0); I(s,0x8c)=-1; func_L03_0041D128(e);func_002A7750(e,9,-1);
                    U(e,0x34)=(U(e,0x34)&0xffbe)|0x1000; I(e,0x98)=I(P(e,0x24),0x10);
                    if(e[0x43])func_002A7470(e,0,0,0);
                    H(s,0x178)=0;
                    func_002A8C28(e,&b,0x10001,0,1,0,F(s,0x50),2.0f,1.0f);
                    func_L02_002EF388(e,&a,D_L03_001B2B0C[0]+I(s,0x2a0)*128+0x70,0,0);
                } else {I(s,0x2d8)=func_002A7820(10,20);}
            } else if(func_00282E80(D_00189E20.position,s+0x2b0)>5.0f) {
                func_L00_003294F0(e,0);func_L03_0041D128(e); H(s,0x178)=0;F(s,0x20)=(float)H(s,0x24);
                func_002A7750(e,9,-1);
                U(e,0x34)=(U(e,0x34)&0xffbe)|0x1000;I(e,0x98)=I(P(e,0x24),0x10);
                if(e[0x43])func_002A7470(e,0,0,0);
                b.q=0;b.f[2]=func_002A7940();a.q=b.q;
                func_L02_002EF388(e,s+0x2b0,&a,0,0);
            }
        }
        break;
    case 9:
        if(!I(s,0x2ac)) {func_002E5CF8(3,0,e);I(s,0x2ac)=1;}
        a.q=0;a.f[0]=6.0f;a.f[3]=1.0f;
        func_002830C0(&a,&a,D_L03_001B2B0C[0]+I(s,0x2a0)*128);
        func_L01_00321178(e,&a);
        if(func_L03_0041D1D8(e)) {I(s,0x8c)=I(s,0x290);func_002A7750(e,5,2);}
        break;
    }
    func_L03_0041CEB0(e);
}
