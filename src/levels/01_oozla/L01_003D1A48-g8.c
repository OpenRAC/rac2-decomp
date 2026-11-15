#include "names.h"
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
extern long GetEffectTextureDescriptor(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern u32 gfx_pack_color_floats(float, float, float, float);
extern float SplitFloatFraction(float *, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_ease_out_quad(float);
extern int FloatToInt(float);
extern void draw_world_quad(void *, int, int);
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

/* Draws a scrolling, fading ribbon of quads along the platform path. */
void gfx_draw_scrolling_ribbon(u8 *moby)
{
    Quad q;
    Vec origin,stepAlong,cursorPos,sideVec,offsetVec;
    float phase;
    u8 *vars = *(u8 **)(moby+0x68);
    float width, step, t, v, angle, halfWidth, scroll;
    long blend;
    int color;
    int i;
    q.gs[1] = GetEffectTextureDescriptor(*(int *)(vars+0xB4)+0x3F);
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
    *(float *)(vars+0xB8) -= scroll;
    vec_scale_to_length(origin,moby+0xC0,halfWidth);
    FastVecAdd(origin,origin,vars+0x60);
    vec_scale_to_length(stepAlong,moby+0xC0,width);
    vec_scale_to_length(sideVec,moby+0xD0,-(D_L01_001B04DC*0.5f));
    vec_scale_to_length(offsetVec,moby+0xD0,D_L01_001B04DC*((1.0f-D_L01_001B0530)*0.5f));
    step = 1.0f / D_L01_001B04D8;
    for(i=0;i<5;i++) {
        v=0.0f;
        switch(i) {
        case 0:
            origin[2]+=D_L01_001B0528;
            qcopy(cursorPos,origin);
            color=gfx_pack_color_floats(D_L01_001B04F8,D_L01_001B04FC,D_L01_001B0500,0.0f);
            q.color[2]=q.color[3]=color;
            v=SplitFloatFraction(&phase,*(float *)(vars+0xB8));
            break;
        case 1:
            qcopy(cursorPos,origin);
            color=gfx_pack_color_floats(D_L01_001B0504,D_L01_001B0508,D_L01_001B050C,0.0f);
            q.color[2]=q.color[3]=color;
            v=SplitFloatFraction(&phase,*(float *)(vars+0xB8)+0.5f);
            break;
        case 2:
            origin[2]+=D_L01_001B0528;
            qcopy(cursorPos,origin);
            color=gfx_pack_color_floats(D_L01_001B0510,D_L01_001B0514,D_L01_001B0518,0.0f);
            q.color[2]=q.color[3]=color;
            vec_scale_to_length(sideVec,sideVec,D_L01_001B04DC*(D_L01_001B052C*0.5f));
            width*=D_L01_001B0530;
            step*=D_L01_001B0530;
            vec_scale_to_length(stepAlong,moby+0xC0,width);
            v=SplitFloatFraction(&phase,(D_L01_001B0534 * *(float *)(vars+0xB8))/D_L01_001B0530);
            break;
        case 3:
            v=SplitFloatFraction(&phase,(D_L01_001B0538 * *(float *)(vars+0xB8))/D_L01_001B0530);
            color=gfx_pack_color_floats(D_L01_001B051C,D_L01_001B0520,D_L01_001B0524,0.0f);
            q.color[2]=q.color[3]=color;
            FastVecAdd(cursorPos,origin,offsetVec);
            break;
        case 4:
            FastVecSub(cursorPos,origin,offsetVec);
            break;
        }
        FastVecSub(q.p[2],cursorPos,sideVec);
        t=step;
        FastVecAdd(q.p[3],cursorPos,sideVec);
        FastVecAdd(cursorPos,cursorPos,stepAlong);
        q.uv[2][0]=q.uv[0][0]=0.0f;
        q.uv[3][0]=q.uv[1][0]=1.0f;
        q.uv[1][1]=q.uv[0][1]=v;
        q.uv[3][1]=q.uv[2][1]=v+1.0f;
        while(t<1.0f) {
            int rgb = 0xFFFFFF;
            angle=math_ease_out_quad(math_fast_sin_or_cos_b(t*3.14159274f))*128.0f;
            q.color[0]=q.color[1]=q.color[2];
            color=FloatToInt((D_L01_001B04F4*angle)* *(float *)(vars+0xAC));
            q.color[2]=q.color[3]=(q.color[0]&rgb)|(color<<24);
            qcopy(q.p[0],q.p[2]);
            qcopy(q.p[1],q.p[3]);
            FastVecSub(q.p[2],cursorPos,sideVec);
            t+=step;
            FastVecAdd(q.p[3],cursorPos,sideVec);
            FastVecAdd(cursorPos,cursorPos,stepAlong);
            draw_world_quad(&q,0,1);
        }
    }
}
