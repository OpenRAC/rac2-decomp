#include "common.h"
typedef unsigned int QW __attribute__((mode(TI)));
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void gfx_draw_colored_rectangle(int, int,int, int, unsigned long);
extern void gfx_init_quad_packet_state(void *, int, int,int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float,float);
typedef struct { char pad[0x150]; short width, height; } Screen;
extern Screen g_screen_adjust_offsets;
extern char g_origin_vec[];
extern char g_hero_state_block[];
extern float g_expanding_effect_scales[] __attribute__((sda));
extern int g_expanding_effect_alphas[] __attribute__((sda));
extern char g_ground_quad_vertices[];
extern float g_pickup_vertex_scale __attribute__((sda));
/* Draws the slot effect, with an optional screen fade and flash quad, then
   expands its billboards while reducing the slot alpha. */
void DrawExpandingBillboardEffect(char *obj)
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
            gfx_draw_colored_rectangle(0,g_screen_adjust_offsets.height,0,g_screen_adjust_offsets.width,color);
        }
        if (*(short *)(s+4) && *(int *)(s+0x38)) {
            float alpha;
            unsigned int color;
            qcopy_nc(v.a,obj+0xe0);
            alpha=IntToFloat(*(short *)(s+4)) * *(float *)(s+0x10);
            gfx_init_quad_packet_state(&p,11,4,128);
            color=(FloatToInt(alpha*255.0f)<<24)|0xffffff;
            p.color[0]=p.color[1]=p.color[2]=p.color[3]=color;
            p.uv[0][0]=0; p.uv[0][1]=0; p.uv[1][0]=0; p.uv[1][1]=1;
            p.uv[2][0]=1; p.uv[2][1]=0; p.uv[3][0]=1; p.uv[3][1]=1;
            FastVecSub(v.b,obj+0x10,g_origin_vec);
            vec_scale_to_length(v.c,v.b,0.1f);
            FastVecAdd(v.d,g_origin_vec,v.c);
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

        gfx_draw_billboard_quad(obj+0x10,*(int *)(s+0x48),(g_expanding_effect_alphas[*(int *)(s+0x3c)]<<24)|0x804040,1,g_expanding_effect_scales[*(int *)(s+0x3c)]*size,0.08f,0);
    }
    gfx_draw_billboard_quad(obj+0x10,*(int *)(s+0x48),(g_expanding_effect_alphas[*(int *)(s+0x3c)]<<24)|0xc84064,1,g_expanding_effect_scales[*(int *)(s+0x3c)]*(*(float *)(s+0x40)*8.0f),0.08f,0);
    gfx_init_quad_packet_state(&p,*(int *)(s+0x48),1,128);
    p.color[0]=p.color[1]=p.color[2]=p.color[3]=0x7f0000ff;
    p.uv[0][0]=0; p.uv[0][1]=0; p.uv[1][0]=0; p.uv[1][1]=1;
    p.uv[2][0]=1; p.uv[2][1]=0; p.uv[3][0]=1; p.uv[3][1]=1;
    qcopy(v.d,obj+0x10);
    FastVecSub(v.a,g_origin_vec,v.d); vec_scale_to_length(v.a,v.a,1);
    FastVecCross(v.b,v.a,g_hero_state_block); vec_scale_to_length(v.b,v.b,1);
    FastVecCross(v.c,v.b,v.a);
    *(QW *)v.f = 0;
    v.f[2] = *(float *)(s + 0x44) * 0.017453294f;
    *(QW *)v.e = *(QW *)v.f;
    euler_rotation_basis(v.matrix,v.e); multiply_matrix3x3(v.a,v.a,v.matrix);
    for(i=0;i<4;i++) {
        FastVecScale(p.vertex[i],g_ground_quad_vertices+i*16,(g_pickup_vertex_scale*g_expanding_effect_scales[*(int *)(s+0x3c)])**(float *)(s+0x40));
        transform_vector(p.vertex[i],p.vertex[i],v.a);
        p.color[i]=i<=1?0x70804040:0x50204090;
    }
    p.tail[3]=((unsigned long long)g_expanding_effect_alphas[*(int *)(s+0x3c)]<<32)|0x68;
    draw_world_quad(&p,0,0);
    g_expanding_effect_scales[*(int *)(s+0x3c)]+=0.3f;
    g_expanding_effect_alphas[*(int *)(s+0x3c)]-=4;
    if(g_expanding_effect_alphas[*(int *)(s+0x3c)]<0) g_expanding_effect_alphas[*(int *)(s+0x3c)]=0;
}
