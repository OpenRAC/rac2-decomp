#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } TrailVector;
typedef struct {
    TrailVector vertices[4];
    unsigned int color[4];
    union { float f[4][2]; unsigned int bits[4][2]; } uv;
    unsigned long long tag[4];
} TrailPacket;
extern unsigned long long func_0027C878(int);
extern void func_00316DA0(void *, int);
extern void func_00316B40(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void func_002830C0(void *,void *,void *);
extern void func_00280B90(void *,int,int);
extern float func_00283CE0(int);
extern TrailVector D_001B5340;
void func_00316E08(int unused, int color, TrailVector *points, int count)
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
    a.tag[1]=func_0027C878(43);
    a.tag[3]=((unsigned long long)(unsigned int)color << 32)|0x68;
    green=-2147418368;
    a.tag[2]=0xFF9000000260ULL;
    a.color[0]=a.color[1]=0x7FFFFFFF;
    a.tag[0]=0;
    b.tag[1]=func_0027C878(43);
    b.tag[2]=0xFF9000000260ULL;
    b.tag[0]=0;
    b.tag[3]=((unsigned long long)(unsigned int)(color/3)<<32)|0x68;
    thin.q=0;
    thick.q=0;
    a.color[1]=green; b.color[0]=green;
    thin.v.z=0.05f; thick.v.z=0.2f; thin.v.w=1; thick.v.w=1;
    func_00316DA0(points,count);
    func_00316B40(&a);
    func_00316B40(&b);
    a.uv.bits[0][0]=0; a.uv.bits[0][1]=0; a.uv.bits[1][0]=0; a.uv.f[1][1]=1;
    a.uv.f[2][0]=1; a.uv.bits[2][1]=0; a.uv.f[3][0]=1; a.uv.f[3][1]=1;
    b.uv.bits[0][0]=0; b.uv.bits[0][1]=0; b.uv.bits[1][0]=0; b.uv.f[1][1]=1;
    b.uv.f[2][0]=0.33f; b.uv.bits[2][1]=0; b.uv.f[3][0]=0.33f; b.uv.f[3][1]=1;
    func_00282CF0(&basis[0],next,points);
    func_00282F20(&basis[0],&basis[0],1);
    func_00282CF0(&basis[1],&D_001B5340,points);
    func_00282DD8(&basis[2],&basis[1],&basis[0]);
    func_00282F20(&basis[2],&basis[2],1);
    func_00282DD8(&basis[1],&basis[0],&basis[2]);
    qcopy(&basis[3],points);
    qcopy(&a.vertices[0],&thin);
    func_00282D30(&a.vertices[1],&a.vertices[0],-1);
    func_002830C0(&a.vertices[0],&a.vertices[0],&basis[0]);
    func_002830C0(&a.vertices[1],&a.vertices[1],&basis[0]);
    qcopy(&b.vertices[0],&thick);
    func_00282D30(&b.vertices[1],&b.vertices[0],-1);
    func_002830C0(&b.vertices[0],&b.vertices[0],&basis[0]);
    func_002830C0(&b.vertices[1],&b.vertices[1],&basis[0]);
    for(i=1;i<count-1;i++) {
        float u,v;
        qcopy(&a.vertices[2],&thin);
        func_00282D30(&a.vertices[3],&a.vertices[2],-1);
        qcopy(&b.vertices[2],&thick);
        func_00282D30(&b.vertices[3],&b.vertices[2],-1);
        func_00282CF0(&basis[0],&points[i+1],&points[i]);
        func_00282F20(&basis[0],&basis[0],1);
        func_00282CF0(&basis[1],&D_001B5340,points+i);
        func_00282DD8(&basis[2],&basis[1],&basis[0]);
        func_00282F20(&basis[2],&basis[2],1);
        func_00282DD8(&basis[1],&basis[0],&basis[2]);
        qcopy(&basis[3],points+i);
        func_002830C0(&a.vertices[2],&a.vertices[2],&basis[0]);
        func_002830C0(&a.vertices[3],&a.vertices[3],&basis[0]);
        func_002830C0(&b.vertices[2],&b.vertices[2],&basis[0]);
        func_002830C0(&b.vertices[3],&b.vertices[3],&basis[0]);
        a.color[2]=a.color[3]=0x7F7F7F7F;
        b.color[2]=b.color[3]=green;
        func_00280B90(&a,0,0);
        func_00280B90(&b,0,0);
        u=func_00283CE0(i)*0.33f;
        v=u+0.33f;
        if(u>=1) {u-=1;v-=1;}
        b.uv.f[0][0]=u;b.uv.f[2][0]=v;b.uv.f[1][0]=u;b.uv.f[3][0]=v;
        qcopy(&a.vertices[0],&a.vertices[2]);
        qcopy(&a.vertices[1],&a.vertices[3]);
        qcopy(&b.vertices[0],&b.vertices[2]);
        qcopy(&b.vertices[1],&b.vertices[3]);
    }
}
