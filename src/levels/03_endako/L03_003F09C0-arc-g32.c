
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int D_L03_001AEBF8;
extern int D_L03_001B1B10 __attribute__((sda));
extern float D_L03_001B1AF0[8] SDATA(D_L03_001B1AF0) __attribute__((sda)), D_L03_001B1AE8[2] SDATA(D_L03_001B1AE8) __attribute__((sda)), D_L03_001B1AE0[2] SDATA(D_L03_001B1AE0) __attribute__((sda));
extern int func_002A9640(void *,int,int);
extern void func_002A7750(void *,int,int);
extern void func_L00_0032A258(void *,void *,void *,void *,int,int,int,int,int,u8,void *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_002E5CF8(int,int,void *);
extern void func_L03_002ECF08(void *,void *,void *,void *,void *,int,int);
extern void func_0029F338(void *);
extern void func_L00_00324F18(void *,void *,float,float,float);
extern void func_L03_0042B6F8(void *,void *,int,void *,int,int);
extern void func_L01_0031A278(void *,void *,float,float,float);
extern void func_00283098(void *,void *,void *);
extern void func_L00_003263D0(void *,void *,int,int,float,float,float,float,void *,int,int);

void func_L03_0041A090(u8 *e) {
    u8 *s=*(u8 **)(e+0x68);
    Vec p,a,b,c,d,f,g;
    switch(e[0x20]) {
    case 0:
        if(!*(int *)(s+4)) {
            func_L00_00324F18(e,&a,12,-10,20);
            func_L00_00324F18(e,&b,12,-25,20);
            a.f[3]=0.5f; b.f[3]=1.5f;
            func_L03_0042B6F8(&a,&b,0x50285050,e,5,*(int *)(s+8)!=0);
            func_L00_00324F18(e,&a,-12,-10,20);
            func_L00_00324F18(e,&b,-12,-25,20);
            func_L03_0042B6F8(&a,&b,0x50285050,e,5,*(int *)(s+8)!=0);
        }
        if(*(int *)s) D_L03_001AEBF8--;
        func_002A7750(e,1,-1);
        break;
    case 1:
        if(func_002A9640(e,0x4010000,0) && !*(int *)s) {
            D_L03_001AEBF8--; func_002A7750(e,2,-1);
        }
        e[0xa8]=255;
        break;
    case 2:
        func_L00_0032A258(e,D_L03_001B1AF0,D_L03_001B1AE8,D_L03_001B1AE0,63,0,D_L03_001B1B10,0,65535,255,0);
        func_L00_00324F18(e,&p,0,0,0);
        func_0032C700(e+0x10,0,25,20,20,20,45,1,0.75f,20,1,1,0,0);
        func_002E5CF8(0,0,e);
        func_L01_0031A278(e,&a,*(float *)(e+0x2c)*12,*(float *)(e+0x2c)*-15,*(float *)(e+0x2c)*20);
        b.f[0]=0; b.f[1]=-0.050000004f; b.f[2]=0;
        func_00283098(&b,&b,e+0xc0);
        func_L00_003263D0(e,&a,2,1,0.15f,2,0.5f,1,&b,0x50404040,0);
        func_L01_0031A278(e,&a,*(float *)(e+0x2c)*-12,*(float *)(e+0x2c)*-15,*(float *)(e+0x2c)*20);
        func_L00_003263D0(e,&a,2,1,0.15f,2,0.5f,1,&b,0x50404040,0);
        c.q=0; d.q=0; f.q=0; g.q=0;
        c.f[0]=12; c.f[1]=-12; c.f[2]=20;
        d.f[0]=12; d.f[1]=-12; d.f[2]=20;
        f.f[0]=-1.5f; f.f[1]=-5; f.f[2]=-1.5f;
        g.f[0]=1.5f; g.f[1]=-15; g.f[2]=1.5f;
        func_L03_002ECF08(e,&c,&d,&f,&g,15,0); c.f[0]=-12;
        d.f[0]=-12;
        func_L03_002ECF08(e,&c,&d,&f,&g,15,0);
        if(D_L03_001B1B10>=0) {
            *(u16 *)(e+0x7c)=(1<<D_L03_001B1B10)|0x8000;
            func_002A7750(e,3,-1);
        } else func_0029F338(e);
        break;
    }
}
