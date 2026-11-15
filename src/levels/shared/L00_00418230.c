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
/* Draws a glowing trail as two ribbons through a list of points. The second one is wider and fainter. */
void func_L00_00418230(char *object,int alpha,V *points,int count)
{
    /* As in the resident trail renderer, retail never initializes wide.color[1].
       The assembly consumer transfers that packet word unchanged. The caller
       does not read it as narrow C value or claim narrow fully initialized packet. */
    Packet narrow,wide;
    V frame[4], inner,outer;
    unsigned color;
    V *previous;
    int i;
    float uStart,uEnd;
    if(*(int *)(*(char **)(object+0x68)+4)==0) color=0x800000ff;
    else { int shade=D_L00_0025A9B8*10; color=((unsigned)alpha<<24)|((unsigned)shade<<16)|(unsigned)(255-shade); }
    narrow.texture=GetEffectTextureDescriptor(43);
    narrow.mode=0xff9000000260ULL;
    narrow.prim=((unsigned long long)alpha<<32)|0x68;
    previous=points+1;
    narrow.color[0]=narrow.color[1]=0x7fffffff;
    narrow.flags=0;
    wide.texture=GetEffectTextureDescriptor(43);
    wide.mode=0xff9000000260ULL;
    wide.flags=0;
    wide.prim=((unsigned long long)(alpha/3)<<32)|0x68;
    inner.q=0; outer.q=0;
    inner.f[2]=.04f; outer.f[2]=.16f;
    narrow.color[1]=color; wide.color[0]=color;
    inner.f[3]=1; outer.f[3]=1;
    ref_L00_00418230_00(points,count);
    ref_L00_00418230_01(&narrow);
    ref_L00_00418230_01(&wide);
    narrow.tex.uvBits[0][0]=0; narrow.tex.uvBits[0][1]=0; narrow.tex.uvBits[1][0]=0;
    narrow.tex.uv[1][1]=1; narrow.tex.uv[2][0]=1; narrow.tex.uvBits[2][1]=0;
    narrow.tex.uv[3][0]=1; narrow.tex.uv[3][1]=1;
    wide.tex.uvBits[0][0]=0; wide.tex.uvBits[0][1]=0; wide.tex.uvBits[1][0]=0;
    wide.tex.uv[1][1]=1; wide.tex.uv[2][0]=.33f; wide.tex.uvBits[2][1]=0;
    wide.tex.uv[3][0]=.33f;wide.tex.uv[3][1]=1;
    FastVecSub(&frame[0],previous,points);
    vec_scale_to_length(&frame[0],&frame[0],1);
    FastVecSub(&frame[1],D_L00_001B8C80+0x140,points);
    FastVecCross(&frame[2],&frame[1],&frame[0]);
    vec_scale_to_length(&frame[2],&frame[2],1);
    FastVecCross(&frame[1],&frame[0],&frame[2]);
    qcopy(&frame[3],points);
    qcopy(&narrow.vertex[0],&inner);
    FastVecScale(&narrow.vertex[1],&narrow.vertex[0],-1);
    transform_vector(&narrow.vertex[0],&narrow.vertex[0],frame);
    transform_vector(&narrow.vertex[1],&narrow.vertex[1],frame);
    qcopy(&wide.vertex[0],&outer);
    FastVecScale(&wide.vertex[1],&wide.vertex[0],-1);
    transform_vector(&wide.vertex[0],&wide.vertex[0],frame);
    transform_vector(&wide.vertex[1],&wide.vertex[1],frame);
    for(i=1;i<count-1;i++) {
        qcopy(&narrow.vertex[2],&inner);
        FastVecScale(&narrow.vertex[3],&narrow.vertex[2],-1);
        qcopy(&wide.vertex[2],&outer);
        FastVecScale(&wide.vertex[3],&wide.vertex[2],-1);
        FastVecSub(&frame[0],&points[i+1],&points[i]);
        vec_scale_to_length(&frame[0],&frame[0],1);
        FastVecSub(&frame[1],D_L00_001B8C80+0x140,&points[i]);
        FastVecCross(&frame[2],&frame[1],&frame[0]);
        vec_scale_to_length(&frame[2],&frame[2],1);
        FastVecCross(&frame[1],&frame[0],&frame[2]);
        qcopy(&frame[3],&points[i]);
        transform_vector(&narrow.vertex[2],&narrow.vertex[2],frame);
        transform_vector(&narrow.vertex[3],&narrow.vertex[3],frame);
        transform_vector(&wide.vertex[2],&wide.vertex[2],frame);
        transform_vector(&wide.vertex[3],&wide.vertex[3],frame);
        narrow.color[2]=narrow.color[3]=0x7f7f7f7f;
        wide.color[2]=wide.color[3]=color;
        draw_world_quad(&narrow,0,0);draw_world_quad(&wide,0,0);
        uStart=IntToFloat(i)*.33f;uEnd=uStart+.33f;
        if(uStart>=1){uStart-=1;uEnd-=1;}
        wide.tex.uv[1][0]=wide.tex.uv[0][0]=uStart;
        wide.tex.uv[3][0]=wide.tex.uv[2][0]=uEnd;
        qcopy(&narrow.vertex[0],&narrow.vertex[2]);qcopy(&narrow.vertex[1],&narrow.vertex[3]);
        qcopy(&wide.vertex[0],&wide.vertex[2]);qcopy(&wide.vertex[1],&wide.vertex[3]);
    }
}
