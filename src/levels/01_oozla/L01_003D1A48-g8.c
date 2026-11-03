/* func_L01_003D1A48: builds GS packet words for a quad strip, then for five
 * passes (a switch over i, which owns the unit's five-entry jump table) sets a
 * base point, colour and v offset, and walks t from step to 1 emitting quads
 * through func_00280B90; each colour's top byte comes from func_00283CF0 of
 * func_002A7798(func_00283198(t*pi)). Profile -O2 -G8 -ffunction-sections -g;
 * the copies use qcopy.
 * The RGB mask is a local constant declared inside the inner loop: its set is
 * then the first movable in the loop and loop.c hoists it on the first pass,
 * ahead of the pointer preparations, which gives retail's preheader order
 * (the 128.0f constant moves to the rerun instead).
 * Written inline (0xFFFFFF) it was rejected on pass one and hoisted on the
 * rerun, after them.
 */
#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { Vec p[4]; int color[4]; float uv[4][2]; long gs[4]; } Quad;
extern long func_0027C878(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern u32 func_002AAE98(float, float, float, float);
extern float func_00283CC8(float *, float);
extern float func_00283198(float);
extern float func_002A7798(float);
extern int func_00283CF0(float);
extern void func_00280B90(void *, int, int);
extern float D_L01_001B04D4 __attribute__((sda));
extern float D_L01_001B04D8 __attribute__((sda));
extern float D_L01_001B04DC __attribute__((sda));
extern int D_L01_001B04E0 __attribute__((sda));
extern int D_L01_001B04E4 __attribute__((sda));
extern int D_L01_001B04E8 __attribute__((sda));
extern int D_L01_001B04EC __attribute__((sda));
extern int D_L01_001B04F0 __attribute__((sda));
extern float D_L01_001B04F4 __attribute__((sda));
extern float D_L01_001B04F8 __attribute__((sda));
extern float D_L01_001B04FC __attribute__((sda));
extern float D_L01_001B0500 __attribute__((sda));
extern float D_L01_001B0504 __attribute__((sda));
extern float D_L01_001B0508 __attribute__((sda));
extern float D_L01_001B050C __attribute__((sda));
extern float D_L01_001B0510 __attribute__((sda));
extern float D_L01_001B0514 __attribute__((sda));
extern float D_L01_001B0518 __attribute__((sda));
extern float D_L01_001B051C __attribute__((sda));
extern float D_L01_001B0520 __attribute__((sda));
extern float D_L01_001B0524 __attribute__((sda));
extern float D_L01_001B0528 __attribute__((sda));
extern float D_L01_001B052C __attribute__((sda));
extern float D_L01_001B0530 __attribute__((sda));
extern float D_L01_001B0534 __attribute__((sda));
extern float D_L01_001B0538 __attribute__((sda));
extern float D_L01_001B053C __attribute__((sda));

void func_L01_003D1A48(u8 *m)
{
    Quad q;
    Vec a,b,c,d,e;
    float phase;
    u8 *s = *(u8 **)(m+0x68);
    float width, step, t, v, angle, halfWidth, scroll;
    long blend;
    int color;
    int i;
    q.gs[1] = func_0027C878(*(int *)(s+0xB4)+0x3F);
    width = D_L01_001B04D4 / D_L01_001B04D8;
    scroll = (D_L01_001B053C * (1.0f/60.0f)) / width;
    halfWidth = -(D_L01_001B04D4*0.5f);
    q.gs[2] = 0xFF9000000260ULL;
    blend = (long)D_L01_001B04E0 | ((long)D_L01_001B04E4 << 2);
    blend |= (long)D_L01_001B04E8 << 4;
    blend |= (long)D_L01_001B04EC << 6;
    blend |= (long)D_L01_001B04F0 << 32;
    q.gs[3] = blend;
    q.gs[0] = 0;
    *(float *)(s+0xB8) -= scroll;
    func_00282F20(a,m+0xC0,halfWidth);
    func_00282CC0(a,a,s+0x60);
    func_00282F20(b,m+0xC0,width);
    func_00282F20(d,m+0xD0,-(D_L01_001B04DC*0.5f));
    func_00282F20(e,m+0xD0,D_L01_001B04DC*((1.0f-D_L01_001B0530)*0.5f));
    step = 1.0f / D_L01_001B04D8;
    for(i=0;i<5;i++) {
        v=0.0f;
        switch(i) {
        case 0:
            a[2]+=D_L01_001B0528;
            qcopy(c,a);
            color=func_002AAE98(D_L01_001B04F8,D_L01_001B04FC,D_L01_001B0500,0.0f);
            q.color[2]=q.color[3]=color;
            v=func_00283CC8(&phase,*(float *)(s+0xB8));
            break;
        case 1:
            qcopy(c,a);
            color=func_002AAE98(D_L01_001B0504,D_L01_001B0508,D_L01_001B050C,0.0f);
            q.color[2]=q.color[3]=color;
            v=func_00283CC8(&phase,*(float *)(s+0xB8)+0.5f);
            break;
        case 2:
            a[2]+=D_L01_001B0528;
            qcopy(c,a);
            color=func_002AAE98(D_L01_001B0510,D_L01_001B0514,D_L01_001B0518,0.0f);
            q.color[2]=q.color[3]=color;
            func_00282F20(d,d,D_L01_001B04DC*(D_L01_001B052C*0.5f));
            width*=D_L01_001B0530;
            step*=D_L01_001B0530;
            func_00282F20(b,m+0xC0,width);
            v=func_00283CC8(&phase,(D_L01_001B0534 * *(float *)(s+0xB8))/D_L01_001B0530);
            break;
        case 3:
            v=func_00283CC8(&phase,(D_L01_001B0538 * *(float *)(s+0xB8))/D_L01_001B0530);
            color=func_002AAE98(D_L01_001B051C,D_L01_001B0520,D_L01_001B0524,0.0f);
            q.color[2]=q.color[3]=color;
            func_00282CC0(c,a,e);
            break;
        case 4:
            func_00282CF0(c,a,e);
            break;
        }
        func_00282CF0(q.p[2],c,d);
        t=step;
        func_00282CC0(q.p[3],c,d);
        func_00282CC0(c,c,b);
        q.uv[2][0]=q.uv[0][0]=0.0f;
        q.uv[3][0]=q.uv[1][0]=1.0f;
        q.uv[1][1]=q.uv[0][1]=v;
        q.uv[3][1]=q.uv[2][1]=v+1.0f;
        while(t<1.0f) {
            int rgb = 0xFFFFFF;
            angle=func_002A7798(func_00283198(t*3.14159274f))*128.0f;
            q.color[0]=q.color[1]=q.color[2];
            color=func_00283CF0((D_L01_001B04F4*angle)* *(float *)(s+0xAC));
            q.color[2]=q.color[3]=(q.color[0]&rgb)|(color<<24);
            qcopy(q.p[0],q.p[2]);
            qcopy(q.p[1],q.p[3]);
            func_00282CF0(q.p[2],c,d);
            t+=step;
            func_00282CC0(q.p[3],c,d);
            func_00282CC0(c,c,b);
            func_00280B90(&q,0,1);
        }
    }
}
