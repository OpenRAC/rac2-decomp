#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } TrailVector;
typedef struct {
    TrailVector vertices[4];
    unsigned int color[4];
    union { float f[4][2]; unsigned int bits[4][2]; } uv;
    unsigned long long tag[4];
} TrailPacket;
extern unsigned long long GetEffectTextureDescriptor(int);
extern void gfx_extrapolate_curve_end(void *, int);
extern void gfx_init_draw_packet_defaults(void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern void transform_vector(void *,void *,void *);
extern void draw_world_quad(void *,int,int);
extern float IntToFloat(int);
extern TrailVector g_camera_eye_state;
/* Draws a lightning ribbon along the given points, facing the camera, as a thin bright band over a wider dim one. */
void gfx_draw_lightning_ribbon(int unused, int color, TrailVector *points, int count)
{
    /* Retail leaves b.color[1] untouched. The assembly renderer transfers the
       packet representation, including that indeterminate word; do not invent
       a color store here. This caller never evaluates that word as a C value. */
    TrailPacket a,b;
    TrailVector basis[4];
    union { TrailQuad q; TrailVector v; } thin, thick;
    int green;
    TrailVector *next = points + 1;
    int i;
    a.tag[1]=GetEffectTextureDescriptor(43);
    a.tag[3]=((unsigned long long)(unsigned int)color << 32)|0x68;
    green=-2147418368;
    a.tag[2]=0xFF9000000260ULL;
    a.color[0]=a.color[1]=0x7FFFFFFF;
    a.tag[0]=0;
    b.tag[1]=GetEffectTextureDescriptor(43);
    b.tag[2]=0xFF9000000260ULL;
    b.tag[0]=0;
    b.tag[3]=((unsigned long long)(unsigned int)(color/3)<<32)|0x68;
    thin.q=0;
    thick.q=0;
    a.color[1]=green; b.color[0]=green;
    thin.v.z=0.05f; thick.v.z=0.2f; thin.v.w=1; thick.v.w=1;
    gfx_extrapolate_curve_end(points,count);
    gfx_init_draw_packet_defaults(&a);
    gfx_init_draw_packet_defaults(&b);
    a.uv.bits[0][0]=0; a.uv.bits[0][1]=0; a.uv.bits[1][0]=0; a.uv.f[1][1]=1;
    a.uv.f[2][0]=1; a.uv.bits[2][1]=0; a.uv.f[3][0]=1; a.uv.f[3][1]=1;
    b.uv.bits[0][0]=0; b.uv.bits[0][1]=0; b.uv.bits[1][0]=0; b.uv.f[1][1]=1;
    b.uv.f[2][0]=0.33f; b.uv.bits[2][1]=0; b.uv.f[3][0]=0.33f; b.uv.f[3][1]=1;
    FastVecSub(&basis[0],next,points);
    vec_scale_to_length(&basis[0],&basis[0],1);
    FastVecSub(&basis[1],&g_camera_eye_state,points);
    FastVecCross(&basis[2],&basis[1],&basis[0]);
    vec_scale_to_length(&basis[2],&basis[2],1);
    FastVecCross(&basis[1],&basis[0],&basis[2]);
    qcopy(&basis[3],points);
    qcopy(&a.vertices[0],&thin);
    FastVecScale(&a.vertices[1],&a.vertices[0],-1);
    transform_vector(&a.vertices[0],&a.vertices[0],&basis[0]);
    transform_vector(&a.vertices[1],&a.vertices[1],&basis[0]);
    qcopy(&b.vertices[0],&thick);
    FastVecScale(&b.vertices[1],&b.vertices[0],-1);
    transform_vector(&b.vertices[0],&b.vertices[0],&basis[0]);
    transform_vector(&b.vertices[1],&b.vertices[1],&basis[0]);
    for(i=1;i<count-1;i++) {
        float u,v;
        qcopy(&a.vertices[2],&thin);
        FastVecScale(&a.vertices[3],&a.vertices[2],-1);
        qcopy(&b.vertices[2],&thick);
        FastVecScale(&b.vertices[3],&b.vertices[2],-1);
        FastVecSub(&basis[0],&points[i+1],&points[i]);
        vec_scale_to_length(&basis[0],&basis[0],1);
        FastVecSub(&basis[1],&g_camera_eye_state,points+i);
        FastVecCross(&basis[2],&basis[1],&basis[0]);
        vec_scale_to_length(&basis[2],&basis[2],1);
        FastVecCross(&basis[1],&basis[0],&basis[2]);
        qcopy(&basis[3],points+i);
        transform_vector(&a.vertices[2],&a.vertices[2],&basis[0]);
        transform_vector(&a.vertices[3],&a.vertices[3],&basis[0]);
        transform_vector(&b.vertices[2],&b.vertices[2],&basis[0]);
        transform_vector(&b.vertices[3],&b.vertices[3],&basis[0]);
        a.color[2]=a.color[3]=0x7F7F7F7F;
        b.color[2]=b.color[3]=green;
        draw_world_quad(&a,0,0);
        draw_world_quad(&b,0,0);
        u=IntToFloat(i)*0.33f;
        v=u+0.33f;
        if(u>=1) {u-=1;v-=1;}
        b.uv.f[0][0]=u;b.uv.f[2][0]=v;b.uv.f[1][0]=u;b.uv.f[3][0]=v;
        qcopy(&a.vertices[0],&a.vertices[2]);
        qcopy(&a.vertices[1],&a.vertices[3]);
        qcopy(&b.vertices[0],&b.vertices[2]);
        qcopy(&b.vertices[1],&b.vertices[3]);
    }
}
