#include "common.h"
extern void FastVecSub(void *, void *, void *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef int TI __attribute__((mode(TI)));
typedef float RingVec[4] __attribute__((aligned(16)));
typedef struct {RingVec v[4]; unsigned c[4]; float uv[4][2]; long g[4];} RingQuad;
extern int g_shrink_ring_bits_a __attribute__((sda));
extern int g_shrink_ring_bits_b __attribute__((sda));
extern int g_shrink_ring_bits_c __attribute__((sda));
extern int g_shrink_ring_bits_d __attribute__((sda));
extern int g_shrink_ring_texture_id __attribute__((sda));
extern int g_shrink_ring_color_table[] SDATA(D_L01_001AF5F0);
extern float g_shrink_ring_u_table[] SDATA(D_L01_001AF5F8);
extern float g_shrink_ring_base_height __attribute__((sda));
extern float g_shrink_ring_height_offset __attribute__((sda));
extern float g_shrink_ring_v_table[] MACRO_ADDR;
extern char g_hero_vector_block[];
extern float g_hero_l01_reach_timer_a;
extern void copy_matrix_rotation(void *,void *);
extern long GetEffectTextureDescriptor(int);
extern void vec_clamp_length(void *,float);
extern unsigned FastTweenColor(unsigned,unsigned,float);
extern void vec_store_helper(void *);
extern void euler_rotation_basis(void *,void *);
extern void gfx_transform_and_draw_entries(void *,int,void *,int,void *);
/* Draws the moby's fading ring: four quads, one per row, repeated 32 times around it by the
 * batched draw, fading and growing as the radius in its vars shrinks. Row 0 takes the first
 * colour and the others the second. Adapted from RAC1 draw_moby_radius_ring (GPL-3.0). */
void DrawShrinkingMobyRings(char *moby)
{
    RingQuad q[4];
    float mat[12];
    float pos[4];
    float transform[12];
    float rot[4];
    char *vars=*(char **)(moby+0x68);
    float alpha,half_height;
    int j,k;
    copy_matrix_rotation(mat,moby+0xc0);
    qcopy(pos,moby+0x10);
    for(j=0;j<4;j++) {
        q[j].g[1]=GetEffectTextureDescriptor(g_shrink_ring_texture_id);
        q[j].g[2]=0xFF9000000260L;
        q[j].g[3]=(long)g_shrink_ring_bits_a|((long)g_shrink_ring_bits_b<<2);
        q[j].g[3]|=(long)g_shrink_ring_bits_c<<4;
        q[j].g[3]|=(long)g_shrink_ring_bits_d<<6;
        q[j].g[3]|=0x8000L<<24;
        q[j].g[0]=0;
    }
    half_height=0.1f;
    alpha=(1.95f-F(vars,0x34))*2.0f;
    if(alpha>1) alpha=1; else if(alpha<0) alpha=0;
    if(F(vars,0x34)<1.15f) {
        float t, shrink;
        char *g;
        FastVecSub(g_hero_vector_block,moby+0x10,g_hero_vector_block-0x80);
        g=g_hero_vector_block-0x100;
        I(g,0x108)=0;
        vec_clamp_length(g_hero_vector_block,0.01666666753590107f);
        shrink=F(vars,0x34);
        t=1.15f-shrink; if(t<0)t=0;
        {float fade=(0.2f-shrink)*5; if(fade<0)fade=0; g_hero_l01_reach_timer_a=fade;}
        half_height=t+0.1f;
        if(B(moby,0x20)!=7 && B(moby,0x20)!=8) {
            if(shrink<0.65f) {
                float v=shrink*1.5384615659713745f;
                *(short *)(g+0x2500)=1;
                F(g,0x2024)=v;F(g,0x2020)=v;F(g,0x2028)=2-v;
            } else *(short *)(g+0x2500)=0;
        }
    }
    {
    float scale=0.8f;
    int i;
    RingQuad *row;
    for(i=0;i<4;i++) {
        for(k=0;k<4;k++) {
            unsigned c;
            q[i].uv[k][0]=g_shrink_ring_u_table[k*2];
            q[i].uv[k][1]=g_shrink_ring_v_table[k*2];
            c=g_shrink_ring_color_table[i!=0];
            q[i].c[k]=c;
            q[i].c[k]=FastTweenColor(c&0xffffff,c,alpha);
            vec_store_helper(q[i].v[k]);
            row=(RingQuad *)q[0].v[k];
            {float radius=F(vars,0x34); if(i)radius+=0.01f; q[i].v[k][0]=radius;}
            if(k&1) {
                switch(i) {
                case 0:row[i].v[0][2]+=g_shrink_ring_base_height+half_height;break;
                case 1:row[i].v[0][2]+=g_shrink_ring_base_height+g_shrink_ring_height_offset;break;
                case 2:row[i].v[0][2]+=(g_shrink_ring_base_height-half_height*scale)+g_shrink_ring_height_offset;break;
                case 3:row[i].v[0][2]+=(g_shrink_ring_base_height+half_height*scale)+g_shrink_ring_height_offset;break;
                }
            } else {
                switch(i) {
                case 0:row[i].v[0][2]+=g_shrink_ring_base_height-half_height;break;
                case 1:row[i].v[0][2]+=g_shrink_ring_base_height-g_shrink_ring_height_offset;break;
                case 2:row[i].v[0][2]+=(g_shrink_ring_base_height-half_height*scale)-g_shrink_ring_height_offset;break;
                case 3:row[i].v[0][2]+=(g_shrink_ring_base_height+half_height*scale)-g_shrink_ring_height_offset;break;
                }
            }
        }
    }
    }
    *(TI *)rot=0;rot[2]=0.19634954631328583f;
    euler_rotation_basis(transform,rot);
    gfx_transform_and_draw_entries(q,4,transform,32,mat);
}
