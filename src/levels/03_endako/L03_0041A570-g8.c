#include "common.h"
/* Local vector transfers retain all four components. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern int D_L03_001AEBF8;
extern int D_L03_001B1B50 __attribute__((sda));
extern float D_L03_001B1B30[8] SDATA(D_L03_001B1B30) __attribute__((sda)), D_L03_001B1B28[2] SDATA(D_L03_001B1B28) __attribute__((sda)), D_L03_001B1B20[2] SDATA(D_L03_001B1B20) __attribute__((sda));
extern void func_00282D30(void *,void *,float);
extern void *func_L00_0033E220(void *,void *,int,float,int,int,float,int,int,int);
extern void *func_002A9640(void *,u32,int);
extern void func_002A7750(void *,int,int);
extern void func_L00_0032A258(void *,float *,float *,float *,int,int,int,int,int,u8,void *);
extern void *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_L00_00326620(void *,int,int);
extern int func_002B3868(void *);
extern void func_L03_002ECF08(void *,void *,void *,void *,void *,int,int);
extern void func_00282D08(void *,void *,void *,float);
extern int func_00282948(void *);
extern void func_0029F338(void *);

typedef struct { int enabled; void *handle; int timer; } DestructionState;

void func_L03_0041A570(u8 *e) {
    DestructionState *s=*(DestructionState **)(e+0x68);
    Vec pos, a,b,c,d,f,g,h,i,j,k,l,m;
    pos.q=0; pos.f[2]=-8.0f;
    switch(e[0x20]) {
    case 0:
        FastVecScale(&pos,&pos,*(float *)(e+0x2c));
        s->handle=func_L00_0033E220(&pos,e,0x40202080,*(float *)(e+0x2c)*4200000.0f,-1,1,1.5f,-1,0,-1);
        func_002A7750(e,1,-1);
        if (s->enabled) D_L03_001AEBF8--;
        break;
    case 1:
        if(func_002A9640(e,0x4010000,0) && !s->enabled) {
            D_L03_001AEBF8--; func_002A7750(e,2,-1);
        }
        e[0xa8]=255;
        break;
    case 2: {
        int skip = D_L03_001B1B50;
        func_L00_0032A258(e,D_L03_001B1B30,D_L03_001B1B28,D_L03_001B1B20,63,0,skip,0,65535,255,0);
        PlayMobySound(0,0,e);
        SpawnExplosion(e+0x10,0,25,20,20,20,45,1,0.75f,20.0f,1,1,0,0);
        { u16 *flags=(u16 *)(e+0x34);
          *flags |= 0x41;
          s->timer=30; }
        func_L00_00326620(e,0xf40,0);
        func_002A7750(e,3,-1);
        break;
    }
    case 3:
        a.q=0; b.q=0; c.q=0; d.q=0; f.q=0; g.q=0; h.q=0; i.q=0;
        a.f[0]=-1; a.f[1]=-1; a.f[2]=-7;
        b.f[0]=1; b.f[1]=1; b.f[2]=-5;
        c.f[0]=-3; c.f[1]=-1; c.f[2]=-6.5f;
        d.f[0]=-1; d.f[1]=1; d.f[2]=-4.5f;
        f.f[0]=-5; f.f[1]=-5; f.f[2]=-25;
        g.f[0]=5; g.f[1]=5; g.f[2]=-7;
        h.f[0]=-15; h.f[1]=-5; h.f[2]=-10;
        i.f[0]=-7; i.f[1]=5;
        if(func_002B3868(e)) SpawnParticleBurst(e,&a,&b,&f,&g,40,1);
        lerp_vector(&l,&f,&h,1.0f-(float)s->timer*0.033333335f);
        lerp_vector(&m,&g,&i,1.0f-(float)s->timer*0.033333335f);
        lerp_vector(&j,&a,&c,1.0f-(float)s->timer*0.033333335f);
        lerp_vector(&k,&b,&d,1.0f-(float)s->timer*0.033333335f);
        SpawnParticleBurst(e,&j,&k,&l,&m,3,1);
        if(func_00282948(&s->timer)) func_0029F338(e);
        break;
    }
}
