#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { u8 b[0x30]; u16 h[0x18]; int i[0xC]; float f[0xC]; void *p[0xC]; } View;
typedef union { u8 b[0x40]; float f[0x10]; int i[0x10]; } State;
extern float D_L18_001B234C MACRO_ADDR;
extern float D_L18_001B2350 MACRO_ADDR;
extern int D_L18_001B2348 __attribute__((sda));
typedef union { u8 b[0x48]; int i[0x12]; float f[0x12]; } Params;
extern Params D_L18_002BDA10;
extern int D_L18_001BFC18 NOT_SDA;
extern u8 D_L18_001A8F20[] MACRO_ADDR;
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
extern void func_00283098(void *,void *,void *);
extern float func_002A7940(void);
extern void func_002ACEC0(void *,void *,void *,float);
extern int func_001163B0(void);
extern void *func_002BD8B0(void *,void *,int,int,float,int,int);
extern int func_002761F8(void *,void *,int,int,void *);
extern int func_00277258(float,void *,int,int);
extern int func_00282948(void *);
extern int func_00277F48(void *,int,int,float,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_0029F338(void *);
/* Drifts a spark shot, spawns its effects, and explodes it on contact or timeout unless the hit is its owner. */
void func_L18_004401E0(u8 *o) {
    float pos[4] __attribute__((aligned(16)));
    State *s = *(State **)(o+0x68);
    int flag;
    func_00282CC0(pos,o+0x10,s);
    flag = 0;
    if (D_L18_001B234C > 0.9f || D_L18_001B2350 > 0.9f) flag = 1;
    if (!flag || !(D_L18_001B2348 & 1)) {
        float len = func_00282DF0(s);
        {
        float v[4], a[4], b[4], c[4];
        *(TI *)b = 0;
        b[0] = func_002A7878(-1.0f,1.0f);
        b[1] = func_002A7878(-1.0f,1.0f);
        b[2] = func_002A7878(-1.0f,1.0f);
        *(TI *)a = *(TI *)b;
        func_00282F20(a,a,func_002A7878(D_L18_002BDA10.f[0],D_L18_002BDA10.f[1]) * (1.0f/60.0f));
        func_00282D30(v,s,func_002A7878(D_L18_002BDA10.f[2],D_L18_002BDA10.f[3]));
        func_00282CC0(a,a,v);
        func_00282F20(v,s,func_002A7878(0.0f,1.0f)*len);
        func_00282CC0(v,v,o+0x10);
        func_002C16C0(o+0x10,a,D_L18_002BDA10.i[4],D_L18_002BDA10.i[5],D_L18_002BDA10.i[6],D_L18_002BDA10.i[7],D_L18_002BDA10.f[8],D_L18_002BDA10.f[9],D_L18_002BDA10.f[10],D_L18_002BDA10.f[11],0.0f);
        *(TI *)c = 0;
        c[2] = D_L18_002BDA10.f[12];
        *(TI *)b = *(TI *)c;
        func_00283098(b,b,o+0xC0);
        func_002ACEC0(b,b,o+0xC0,func_002A7940());
        if (func_001163B0() & 1)
            func_002BD8B0(v,b,D_L18_002BDA10.i[13],D_L18_002BDA10.i[14],(float)D_L18_002BDA10.i[15],D_L18_002BDA10.i[16],D_L18_002BDA10.i[17]);
        }
    }
    {
    View request __attribute__((aligned(16)));
    request.p[4] = o;
    request.i[5] = 0x10001;
    request.f[7] = s->f[8];
    request.i[8] = 1;
    qcopy(&request,s);
    func_00282F20(&request,&request,s->f[9]);
    request.f[3] = 5627.925f;
    request.b[0x18] = s->b[0x28];
    request.b[0x19] = s->b[0x2C];
    request.h[0x1A/2] = *(u16 *)(o+0xAA);
    if (func_002761F8(o+0x10,pos,0,s->i[4],&request) || func_00277258(0.2f,pos,0,s->i[4]) || func_00282948(s->b+0x34)) {
        if (D_L18_001BFC18) {
            if (D_L18_001BFC18 != s->i[4]) {
                func_00277F48(o+0x10,0,s->i[4],0.5f,&request);
                func_002ABBB8(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,10,0.0f,0.0f,9.0f,0.666f,0,0.0f,0,1,-1,0,0x810001);
                func_0029F338(o);
                return;
            }
        } else {
            func_002ABBB8(o,D_L18_001A8F20,0,0.0f,0.0f,0,2,8,0.0f,0.0f,9.0f,0.5f,0,0.0f,0,1,-1,0,0x810001);
            func_0029F338(o);
            return;
        }
    }
    }
    qcopy(o+0x10,pos);
}
