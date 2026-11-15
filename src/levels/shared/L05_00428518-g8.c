#include "common.h"
typedef unsigned int QW __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_002FC560(unsigned int, unsigned long);
extern void func_0027DE50(int, int,int, int, unsigned long);
extern void func_00281DE8(void *, int, int,int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern void func_00281EB8(void *, int, unsigned int, int, float, float,float);
typedef struct { char pad[0x150]; short width, height; } Screen;
extern Screen D_001A6480;
extern char D_L05_001B96C0[];
extern char D_0018A0E0[];
extern float D_L05_001B3580[] __attribute__((sda));
extern int D_L05_001B3598[] __attribute__((sda));
extern char D_L05_001AA250[];
extern float D_L05_001B1580 __attribute__((sda));
/* Draws the slot effect, with an optional screen fade and flash quad, then
   expands its billboards while reducing the slot alpha. */
void func_L05_00428518(char *obj)
{
    struct { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; long tail[4]; } p;
    struct { float a[4], b[4], c[4], d[4], e[4], f[4], g[4], matrix[12]; } v __attribute__((aligned(16)));
    char *s=*(char **)(obj+0x68);
    int i;
    if (*(short *)(s+4)) {
        if (*(int *)(s+0x1c)) {
            int intensity=128-FloatToInt((float)*(short *)(s+4));
            int color=(intensity<<24)|(intensity<<16);
            color |= intensity << 8;
            color |= intensity;
            VU1_addGSregister(0x42,0x48);
            DrawColoredRectangle(0,gScreenAdjustOffsets.height,0,gScreenAdjustOffsets.width,color);
        }
        if (*(short *)(s+4) && *(int *)(s+0x38)) {
            float alpha;
            unsigned int color;
            qcopy_nc(v.a,obj+0xe0);
            alpha=IntToFloat(*(short *)(s+4)) * *(float *)(s+0x10);
            InitQuadPacketState(&p,11,4,128);
            color=(FloatToInt(alpha*255.0f)<<24)|0xffffff;
            p.color[0]=p.color[1]=p.color[2]=p.color[3]=color;
            p.uv[0][0]=0; p.uv[0][1]=0; p.uv[1][0]=0; p.uv[1][1]=1;
            p.uv[2][0]=1; p.uv[2][1]=0; p.uv[3][0]=1; p.uv[3][1]=1;
            FastVecSub(v.b,obj+0x10,D_L05_001B96C0);
            vec_scale_to_length(v.c,v.b,0.1f);
            FastVecAdd(v.d,D_L05_001B96C0,v.c);
            FastVecCross(v.e,v.b,v.a); vec_scale_to_length(v.e,v.e,0.075f);
            FastVecCross(v.f,v.e,v.b); vec_scale_to_length(v.f,v.f,0.075f);
            FastVecAdd(v.g,v.d,v.f);
            FastVecAdd(p.vertex[0],v.g,v.e); FastVecSub(p.vertex[1],v.g,v.e);
            FastVecSub(v.g,v.d,v.f);
            FastVecAdd(p.vertex[2],v.g,v.e); FastVecSub(p.vertex[3],v.g,v.e);
            draw_world_quad(&p,0,0);
        }
    }
    {
        float size = *(float *)(s + 0x40) * 4.0f;

        DrawBillboardQuad_00281EB8(obj+0x10,*(int *)(s+0x48),(D_L05_001B3598[*(int *)(s+0x3c)]<<24)|0x804040,1,D_L05_001B3580[*(int *)(s+0x3c)]*size,0.08f,0);
    }
    DrawBillboardQuad_00281EB8(obj+0x10,*(int *)(s+0x48),(D_L05_001B3598[*(int *)(s+0x3c)]<<24)|0xc84064,1,D_L05_001B3580[*(int *)(s+0x3c)]*(*(float *)(s+0x40)*8.0f),0.08f,0);
    InitQuadPacketState(&p,*(int *)(s+0x48),1,128);
    p.color[0]=p.color[1]=p.color[2]=p.color[3]=0x7f0000ff;
    p.uv[0][0]=0; p.uv[0][1]=0; p.uv[1][0]=0; p.uv[1][1]=1;
    p.uv[2][0]=1; p.uv[2][1]=0; p.uv[3][0]=1; p.uv[3][1]=1;
    qcopy(v.d,obj+0x10);
    FastVecSub(v.a,D_L05_001B96C0,v.d); vec_scale_to_length(v.a,v.a,1);
    FastVecCross(v.b,v.a,D_0018A0E0); vec_scale_to_length(v.b,v.b,1);
    FastVecCross(v.c,v.b,v.a);
    *(QW *)v.f = 0;
    v.f[2] = *(float *)(s + 0x44) * 0.017453294f;
    *(QW *)v.e = *(QW *)v.f;
    euler_rotation_basis(v.matrix,v.e); multiply_matrix3x3(v.a,v.a,v.matrix);
    for(i=0;i<4;i++) {
        FastVecScale(p.vertex[i],D_L05_001AA250+i*16,(D_L05_001B1580*D_L05_001B3580[*(int *)(s+0x3c)])**(float *)(s+0x40));
        transform_vector(p.vertex[i],p.vertex[i],v.a);
        p.color[i]=i<=1?0x70804040:0x50204090;
    }
    p.tail[3]=((unsigned long long)D_L05_001B3598[*(int *)(s+0x3c)]<<32)|0x68;
    draw_world_quad(&p,0,0);
    D_L05_001B3580[*(int *)(s+0x3c)]+=0.3f;
    D_L05_001B3598[*(int *)(s+0x3c)]-=4;
    if(D_L05_001B3598[*(int *)(s+0x3c)]<0) D_L05_001B3598[*(int *)(s+0x3c)]=0;
}
