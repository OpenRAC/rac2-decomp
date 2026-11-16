/* func_PAL_L01_003D5C30, the PAL copy of func_L01_003D1A48: the same C, where 1.0f / 60.0f becomes
   0.020000001f. */
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
extern float g_ribbon_length __attribute__((sda));
extern float g_ribbon_l01_segment_count __attribute__((sda));
extern float g_ribbon_width __attribute__((sda));
extern int g_ribbon_l01_blend_a __attribute__((sda));
extern int g_ribbon_l01_blend_b __attribute__((sda));
extern int g_ribbon_l01_blend_c __attribute__((sda));
extern int g_ribbon_l01_blend_d __attribute__((sda));
extern int g_ribbon_blend_fix __attribute__((sda));
extern float g_ribbon_alpha_scale __attribute__((sda));
extern float g_ribbon_color_a_red __attribute__((sda));
extern float g_ribbon_color_a_green __attribute__((sda));
extern float g_ribbon_color_a_blue __attribute__((sda));
extern float g_ribbon_color_b_red __attribute__((sda));
extern float g_ribbon_color_b_green __attribute__((sda));
extern float g_ribbon_color_b_blue __attribute__((sda));
extern float g_ribbon_color_c_red __attribute__((sda));
extern float g_ribbon_color_c_green __attribute__((sda));
extern float g_ribbon_color_c_blue __attribute__((sda));
extern float g_ribbon_color_d_red __attribute__((sda));
extern float g_ribbon_color_d_green __attribute__((sda));
extern float g_ribbon_color_d_blue __attribute__((sda));
extern float g_ribbon_height_offset __attribute__((sda));
extern float g_ribbon_side_width_scale __attribute__((sda));
extern float g_ribbon_texture_repeat __attribute__((sda));
extern float g_ribbon_scroll_speed_a __attribute__((sda));
extern float g_ribbon_scroll_speed_b __attribute__((sda));
extern float g_ribbon_scroll_rate __attribute__((sda));

void func_PAL_L01_003D5C30(u8 *m)
{
    Quad q;
    Vec a,b,c,d,e;
    float phase;
    u8 *s = *(u8 **)(m+0x68);
    float width, step, t, v, angle, halfWidth, scroll;
    long blend;
    int color;
    int i;
    q.gs[1] = GetEffectTextureDescriptor(*(int *)(s+0xB4)+0x3F);
    width = g_ribbon_length / g_ribbon_l01_segment_count;
    scroll = (g_ribbon_scroll_rate * (0.020000001f)) / width;
    halfWidth = -(g_ribbon_length*0.5f);
    q.gs[2] = 0xFF9000000260ULL;
    blend = (long)g_ribbon_l01_blend_a | ((long)g_ribbon_l01_blend_b << 2);
    blend |= (long)g_ribbon_l01_blend_c << 4;
    blend |= (long)g_ribbon_l01_blend_d << 6;
    blend |= (long)g_ribbon_blend_fix << 32;
    q.gs[3] = blend;
    q.gs[0] = 0;
    *(float *)(s+0xB8) -= scroll;
    vec_scale_to_length(a,m+0xC0,halfWidth);
    FastVecAdd(a,a,s+0x60);
    vec_scale_to_length(b,m+0xC0,width);
    vec_scale_to_length(d,m+0xD0,-(g_ribbon_width*0.5f));
    vec_scale_to_length(e,m+0xD0,g_ribbon_width*((1.0f-g_ribbon_texture_repeat)*0.5f));
    step = 1.0f / g_ribbon_l01_segment_count;
    for(i=0;i<5;i++) {
        v=0.0f;
        switch(i) {
        case 0:
            a[2]+=g_ribbon_height_offset;
            qcopy(c,a);
            color=gfx_pack_color_floats(g_ribbon_color_a_red,g_ribbon_color_a_green,g_ribbon_color_a_blue,0.0f);
            q.color[2]=q.color[3]=color;
            v=SplitFloatFraction(&phase,*(float *)(s+0xB8));
            break;
        case 1:
            qcopy(c,a);
            color=gfx_pack_color_floats(g_ribbon_color_b_red,g_ribbon_color_b_green,g_ribbon_color_b_blue,0.0f);
            q.color[2]=q.color[3]=color;
            v=SplitFloatFraction(&phase,*(float *)(s+0xB8)+0.5f);
            break;
        case 2:
            a[2]+=g_ribbon_height_offset;
            qcopy(c,a);
            color=gfx_pack_color_floats(g_ribbon_color_c_red,g_ribbon_color_c_green,g_ribbon_color_c_blue,0.0f);
            q.color[2]=q.color[3]=color;
            vec_scale_to_length(d,d,g_ribbon_width*(g_ribbon_side_width_scale*0.5f));
            width*=g_ribbon_texture_repeat;
            step*=g_ribbon_texture_repeat;
            vec_scale_to_length(b,m+0xC0,width);
            v=SplitFloatFraction(&phase,(g_ribbon_scroll_speed_a * *(float *)(s+0xB8))/g_ribbon_texture_repeat);
            break;
        case 3:
            v=SplitFloatFraction(&phase,(g_ribbon_scroll_speed_b * *(float *)(s+0xB8))/g_ribbon_texture_repeat);
            color=gfx_pack_color_floats(g_ribbon_color_d_red,g_ribbon_color_d_green,g_ribbon_color_d_blue,0.0f);
            q.color[2]=q.color[3]=color;
            FastVecAdd(c,a,e);
            break;
        case 4:
            FastVecSub(c,a,e);
            break;
        }
        FastVecSub(q.p[2],c,d);
        t=step;
        FastVecAdd(q.p[3],c,d);
        FastVecAdd(c,c,b);
        q.uv[2][0]=q.uv[0][0]=0.0f;
        q.uv[3][0]=q.uv[1][0]=1.0f;
        q.uv[1][1]=q.uv[0][1]=v;
        q.uv[3][1]=q.uv[2][1]=v+1.0f;
        while(t<1.0f) {
            int rgb = 0xFFFFFF;
            angle=math_ease_out_quad(math_fast_sin_or_cos_b(t*3.14159274f))*128.0f;
            q.color[0]=q.color[1]=q.color[2];
            color=FloatToInt((g_ribbon_alpha_scale*angle)* *(float *)(s+0xAC));
            q.color[2]=q.color[3]=(q.color[0]&rgb)|(color<<24);
            qcopy(q.p[0],q.p[2]);
            qcopy(q.p[1],q.p[3]);
            FastVecSub(q.p[2],c,d);
            t+=step;
            FastVecAdd(q.p[3],c,d);
            FastVecAdd(c,c,b);
            draw_world_quad(&q,0,1);
        }
    }
}
