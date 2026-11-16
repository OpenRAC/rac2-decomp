#include "common.h"

/* func_PAL_L06_004046D8, the PAL copy of func_L06_004009B8: the same C, where the
 * 60 Hz divisor D_L06_001AFF20 * 60.0f becomes (ref * 300.0f + 2.0f) / 6, ref being
 * this function's own 0.45f: a different variable from the 0.45f that
 * func_PAL_L06_003E8A88 reads, at a different address in each level. */

/* Draws the scrolling mesh grid as textured quads, fading each column by age.
 * Corresponds to RAC1 render_data_processor_linked_effect; the packet layout,
 * loop lifetimes and matrix copies follow the measured RAC2 body.
 */
#define RI(p,o) (*(s32 *)((char *)(p)+(o)))
#define RF(p,o) (*(float *)((char *)(p)+(o)))
typedef int QuadWord __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) RenderVec;
typedef struct { RenderVec points[4]; u32 colors[4]; float uv[4][2]; u64 r70,texture,flags,blend; } RenderQuad;
extern char *g_moby_l06_table;
extern char g_hero_l06_position[];
extern float g_ripple_uv_init_table[] MACRO_ADDR;
extern s32 g_ripple_blend_a __attribute__((sda));
extern s32 g_ripple_blend_b __attribute__((sda));
extern s32 g_ripple_blend_c __attribute__((sda));
extern s32 g_ripple_blend_d __attribute__((sda));
extern u32 g_ripple_color_start __attribute__((sda));
extern u32 g_ripple_color_end __attribute__((sda));
extern float g_ripple_uv_table[8] __attribute__((sda));
extern RenderVec g_ripple_quad_offsets[4] __attribute__((sda));
extern float g_texture_scroll_step;
extern s32 g_ripple_grid_fade_start;
extern s32 g_ripple_grid_duration;
extern float ref_PAL_L06_004046D8_00 __attribute__((sda));
extern float fast_vec_dist(void *,void *);
extern void set_scale_matrix(void *,float);
extern void euler_to_matrix(void *,void *);
extern void multiply_matrix(void *,void *,void *);
extern float IntToFloat(s32);
extern s32 FloatToInt(float);
extern u64 GetEffectTextureDescriptor(s32);
extern u32 FastTweenColor(u32,u32,float);
extern void FastVecAdd(void *,void *,void *);
extern void draw_world_quad(void *,void *,s32);

/* Draws the scrolling mesh grid of a ripple-grid ribbon moby as textured quads, fading each column by age (PAL). */
void gfx_draw_ripple_grid_pal(char *obj)
{
    RenderQuad quad[2];
    RenderVec rotation[4];
    char *data = *(char **)(obj+0x68);
    char *mesh = *(char **)(g_moby_l06_table + RI(data,0xC)*256+0x68);
    char *matrices = __builtin_alloca((u32)(RI(data,4)<<9)>>3);
    float fade;
    float distance;
    s32 n,uv_index,i,j,k;
    u8 *order;
    s32 group_age;
    char *age_base, *ages;
    s32 group_vertices;
    float *uv0;
    s32 next_group, next_row;
    float *uv1, *v0, *v1;
    s32 matrix_index;
    u64 blend;
    u64 texture;
    float scroll;
    u32 color;
    s32 opacity;

    distance = fast_vec_dist(obj+0x10,g_hero_l06_position);
    if (distance>48.0f) fade=(80.0f-distance)*0.03125f;
    else fade=1.0f;
    set_scale_matrix(rotation,RF(data,0)*0.5f);
    uv0=&quad[0].uv[0][0];
    uv1=&quad[1].uv[0][0];
    v0=uv0+1;
    v1=uv1+1;
    for (matrix_index=0;matrix_index<RI(data,4);matrix_index++) {
        char *matrix=matrices+matrix_index*64;
        euler_to_matrix(matrix,obj+0xF0);
        multiply_matrix(matrix,matrix,rotation);
        *(QuadWord *)(matrix+0x30) = *(QuadWord *)(obj+0x10);
        RF(matrix,0x38)+=IntToFloat(matrix_index+1)*RF(data,8);
    }
    texture=GetEffectTextureDescriptor(14);
    blend=(u64)g_ripple_blend_a | ((u64)g_ripple_blend_b<<2);
    blend |= ((u64)g_ripple_blend_c<<4);
    blend |= ((u64)g_ripple_blend_d<<6);
    blend |= 0x8000000000ULL;
    quad[1].texture=texture;
    quad[0].texture=texture;
    quad[1].flags=0xFF9000000260ULL;
    quad[0].flags=0xFF9000000260ULL;
    quad[0].r70=quad[1].r70=0;
    quad[0].blend=quad[1].blend=blend;
    {
        s32 initial_uv_index;
        for(initial_uv_index=0;initial_uv_index<4;initial_uv_index++) {
            v0[initial_uv_index*2]=v1[initial_uv_index*2]=g_ripple_uv_init_table[initial_uv_index*2];
        }
    }
    i=0;
    do {
        next_group=i+1;
        scroll=0.0f;
        j=0;
        do {
            s32 next;
            scroll+=g_texture_scroll_step;
            if(scroll>1.0f) scroll-=1.0f;
            next_row=j+1;
            for(uv_index=0;uv_index<4;uv_index++) {
                float uv=g_ripple_uv_table[uv_index*2]+scroll+RF(mesh,0x12DE0);
                uv0[uv_index*2]=uv1[uv_index*2]=uv;
            }
            for(n=0;n<RI(data,4);n=next) {
                s32 offset;
                float progress;
                float alpha;
                s32 time;
                order=(u8 *)data+0x10;
                group_age=i*120;
                age_base=mesh+0x10000;
                ages=age_base+0x2C00;
                time=RI(ages,order[n]*4+group_age);
                group_vertices=i*0x2580;
                if(time>g_ripple_grid_fade_start) progress=IntToFloat(time-g_ripple_grid_fade_start)/IntToFloat(g_ripple_grid_duration-g_ripple_grid_fade_start);
                else progress=1.0f-IntToFloat(time)/IntToFloat(g_ripple_grid_fade_start);
                color=FastTweenColor(g_ripple_color_start,g_ripple_color_end,progress);
                alpha=IntToFloat((s32)color>>24);
                opacity=FloatToInt(fade*fade*alpha);
                color=(color&0xFFFFFF)+(opacity<<24);
                if((u8)obj[0x20]==2) {
                    alpha=IntToFloat(opacity)*IntToFloat(RI(data,0x34));
                    color=(color&0xFFFFFF)+(FloatToInt(alpha/((ref_PAL_L06_004046D8_00*300.0f+2.0f)*0.16666667f))<<24);
                }
                k=0;
                offset=n*64;
                next=n+1;
                quad[1].colors[3]=color;
                quad[1].colors[2]=color;
                quad[1].colors[1]=color;
                quad[1].colors[0]=color;
                for(;k<4;k++) {
                    FastVecAdd(&quad[1].points[k],&g_ripple_quad_offsets[k],&((RenderVec (*)[20])(mesh+group_vertices))[j+(k>>1)][order[n]]);
                }
                draw_world_quad(&quad[1],matrices+offset,0);
            }
            j=next_row;
        } while(j<19);
        i=next_group;
    } while(i<4);
}
