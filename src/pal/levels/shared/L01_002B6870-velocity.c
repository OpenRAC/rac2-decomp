#include "include_asm.h"

#include "common.h"
typedef int VelocityQuad __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[240];
    float xf0;
    float xf4;
    float xf8;
    unsigned char padfc[120];
    float x174;
    float x178;
    unsigned char pad17c[36];
    float x1a0;
    unsigned char pad1a4[12];
    float x1b0;
    float x1b4;
    unsigned char pad1b8[207];
    unsigned char x287;
    unsigned char pad288[194];
    short x34a;
    unsigned char pad34c[472];
    short x524;
    unsigned char pad526[3886];
    short x1454;
    unsigned char pad1456[3646];
    int x2294;
    unsigned char pad2298[4];
    int x229c;
    unsigned char pad22a0[35];
    unsigned char x22c3;
} PlayerVelocityState;
extern PlayerVelocityState D_00189E20;
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E20(void *);
extern float func_L00_002D3A58(void *);
extern float func_00282DB0(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F70(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern void func_L00_002D3B58(void *,void *,float);
extern void func_L00_002D3BD8(void *,void *,float);
extern float func_L00_002B5590(void *);

/* Approach the requested velocity, increasing acceleration when reversing direction. */
void func_PAL_L01_002B6870(float rate) {
    float v[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    float u[4] __attribute__((aligned(16)));
    float angle,speed,dot,l1,l2;
    switch(D_00189E20.x22c3) {
    case 0:
        angle=D_00189E20.x1a0;speed=D_00189E20.x1b0;
        if(D_00189E20.x229c==4 && D_00189E20.x524 && D_00189E20.x287) speed=0.10000001f;
        if(D_00189E20.x34a && D_00189E20.x2294==14 && speed>0.020000001f) speed=0.020000001f;
        v[0]=func_00283180(angle)*speed;
        v[1]=func_00283198(angle)*speed;
        v[2]=D_00189E20.xf8;
        dot=-(D_00189E20.xf0*v[0]+D_00189E20.xf4*v[1]);
        l1=func_00282E20(v);l2=func_00282E20((char *)&D_00189E20+0xf0);
        if(l1==0.0f || l2==0.0f) dot=0.0f;
        else {
            dot/=l1;
            dot/=l2;
        }
        dot+=1.0f;
        dot*=1.5f;
        if(dot>3.0f) dot=3.0f;
        if(dot<1.0f) dot=1.0f;
        rate*=dot;
        func_00282CF0(v,v,(char *)&D_00189E20+0xf0);
        if(func_00282E20(v)>rate) func_00282F70(v,v,rate);
        func_00282CC0((char *)&D_00189E20+0xf0,(char *)&D_00189E20+0xf0,v);
        *(VelocityQuad *)t=*(VelocityQuad *)((char *)&D_00189E20+0xa60);
        D_00189E20.x1b4=D_00189E20.x178-func_L00_002B5590(t);
        if(D_00189E20.x1454) D_00189E20.x1b4=D_00189E20.x174;
        break;
    case 1:case 2:
        *(VelocityQuad *)t=*(VelocityQuad *)((char *)&D_00189E20+0x190);speed=D_00189E20.x1b0;
        func_L00_002D3B58(v,t,0.0f);
        func_00282F20(v,v,speed);
        func_L00_002D3B58(u,(char *)&D_00189E20+0xf0,0.0f);
        dot=-func_00282DB0(u,v);
        l1=func_L00_002D3A58(v);l2=func_L00_002D3A58((char *)&D_00189E20+0xf0);
        if(l1==0.0f || l2==0.0f) dot=0.0f;
        else {
            dot/=l1;
            dot/=l2;
        }
        dot+=1.0f;
        dot*=1.5f;
        if(dot>3.0f) dot=3.0f;
        if(dot<1.0f) dot=1.0f;
        rate*=dot;
        func_00282CF0(v,v,(char *)&D_00189E20+0xf0);
        func_L00_002D3B58(v,v,0.0f);
        if(func_L00_002D3A58(v)>rate) func_L00_002D3BD8(v,v,rate);
        func_00282CC0((char *)&D_00189E20+0xf0,(char *)&D_00189E20+0xf0,v);
        D_00189E20.x1b4=D_00189E20.x178;
        if(D_00189E20.x1454) D_00189E20.x1b4=D_00189E20.x174;
        break;
    }
}
