#include "common.h"

typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
typedef struct { V vertex[4]; unsigned color[4]; union { float uv[4][2]; unsigned uvBits[4][2]; } tex; unsigned long long flags,texture,mode,prim; } Packet;
extern char D_L00_001B8C80[];
extern int D_L00_0025A9B8;
extern unsigned long long func_0027C878(int);
extern void ref_L00_00418230_00(void *,int), ref_L00_00418230_01(void *);
extern void func_00282CF0(void *,void *,void *),func_00282DD8(void *,void *,void *),func_002830C0(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float);
extern void func_00280B90(void *,int,int);
extern float func_00283CE0(int);
void func_L00_00418230(char *object,int alpha,V *points,int count)
{
    /* As in the resident trail renderer, retail never initializes b.color[1].
       The assembly consumer transfers that packet word unchanged. The caller
       does not read it as a C value or claim a fully initialized packet. */
    Packet a,b;
    V frame[4], inner,outer;
    unsigned color;
    V *previous;
    int i;
    float u,v;
    if(*(int *)(*(char **)(object+0x68)+4)==0) color=0x800000ff;
    else { int c=D_L00_0025A9B8*10; color=((unsigned)alpha<<24)|((unsigned)c<<16)|(unsigned)(255-c); }
    a.texture=GetEffectTextureDescriptor(43);
    a.mode=0xff9000000260ULL;
    a.prim=((unsigned long long)alpha<<32)|0x68;
    previous=points+1;
    a.color[0]=a.color[1]=0x7fffffff;
    a.flags=0;
    b.texture=GetEffectTextureDescriptor(43);
    b.mode=0xff9000000260ULL;
    b.flags=0;
    b.prim=((unsigned long long)(alpha/3)<<32)|0x68;
    inner.q=0; outer.q=0;
    inner.f[2]=.04f; outer.f[2]=.16f;
    a.color[1]=color; b.color[0]=color;
    inner.f[3]=1; outer.f[3]=1;
    ref_L00_00418230_00(points,count);
    ref_L00_00418230_01(&a);
    ref_L00_00418230_01(&b);
    a.tex.uvBits[0][0]=0; a.tex.uvBits[0][1]=0; a.tex.uvBits[1][0]=0;
    a.tex.uv[1][1]=1; a.tex.uv[2][0]=1; a.tex.uvBits[2][1]=0;
    a.tex.uv[3][0]=1; a.tex.uv[3][1]=1;
    b.tex.uvBits[0][0]=0; b.tex.uvBits[0][1]=0; b.tex.uvBits[1][0]=0;
    b.tex.uv[1][1]=1; b.tex.uv[2][0]=.33f; b.tex.uvBits[2][1]=0;
    b.tex.uv[3][0]=.33f;b.tex.uv[3][1]=1;
    FastVecSub(&frame[0],previous,points);
    vec_scale_to_length(&frame[0],&frame[0],1);
    FastVecSub(&frame[1],D_L00_001B8C80+0x140,points);
    FastVecCross(&frame[2],&frame[1],&frame[0]);
    vec_scale_to_length(&frame[2],&frame[2],1);
    FastVecCross(&frame[1],&frame[0],&frame[2]);
    qcopy(&frame[3],points);
    qcopy(&a.vertex[0],&inner);
    FastVecScale(&a.vertex[1],&a.vertex[0],-1);
    transform_vector(&a.vertex[0],&a.vertex[0],frame);
    transform_vector(&a.vertex[1],&a.vertex[1],frame);
    qcopy(&b.vertex[0],&outer);
    FastVecScale(&b.vertex[1],&b.vertex[0],-1);
    transform_vector(&b.vertex[0],&b.vertex[0],frame);
    transform_vector(&b.vertex[1],&b.vertex[1],frame);
    for(i=1;i<count-1;i++) {
        qcopy(&a.vertex[2],&inner);
        FastVecScale(&a.vertex[3],&a.vertex[2],-1);
        qcopy(&b.vertex[2],&outer);
        FastVecScale(&b.vertex[3],&b.vertex[2],-1);
        FastVecSub(&frame[0],&points[i+1],&points[i]);
        vec_scale_to_length(&frame[0],&frame[0],1);
        FastVecSub(&frame[1],D_L00_001B8C80+0x140,&points[i]);
        FastVecCross(&frame[2],&frame[1],&frame[0]);
        vec_scale_to_length(&frame[2],&frame[2],1);
        FastVecCross(&frame[1],&frame[0],&frame[2]);
        qcopy(&frame[3],&points[i]);
        transform_vector(&a.vertex[2],&a.vertex[2],frame);
        transform_vector(&a.vertex[3],&a.vertex[3],frame);
        transform_vector(&b.vertex[2],&b.vertex[2],frame);
        transform_vector(&b.vertex[3],&b.vertex[3],frame);
        a.color[2]=a.color[3]=0x7f7f7f7f;
        b.color[2]=b.color[3]=color;
        draw_world_quad(&a,0,0);draw_world_quad(&b,0,0);
        u=IntToFloat(i)*.33f;v=u+.33f;
        if(u>=1){u-=1;v-=1;}
        b.tex.uv[1][0]=b.tex.uv[0][0]=u;
        b.tex.uv[3][0]=b.tex.uv[2][0]=v;
        qcopy(&a.vertex[0],&a.vertex[2]);qcopy(&a.vertex[1],&a.vertex[3]);
        qcopy(&b.vertex[0],&b.vertex[2]);qcopy(&b.vertex[1],&b.vertex[3]);
    }
}
