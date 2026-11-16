#include "names.h"
/* func_L11_00438880: skips set entries in the 13-byte flag table at state+0x380,
 * then for each pair of points state+0x100+prev*16 / state+0x100+next*16
 * fills a four-corner quad record twice (func_00281DE8 setup, func_00280B90
 * submit) with different widths, colours and UVs, and
 * finally advances the scrolling UV offset at state+0x35C, wrapping to [-1,1].
 * Built -G8 -g -mno-split-addresses in its own unit (SDATA UV base, absolute
 * NOT_SDA load of 001B12B4).
 * The flag scans index through a block-local `j = next-1`: as a separate
 * variable, the C front end cannot fold flags+(next-1) into (flags+next)-1,
 * so loop.c sees a giv (next-1) feeding the address giv; the summed benefit
 * makes it strength-reduce the address into a pointer register. That gives
 * retail's pointer cursor, the pre-loop test through the computed address and
 * the separate copy into the cursor in the second scan.
 * Explicit UV pointer locals give the spills at 0x100/0x104, following at
 * 0x108 and flags at 0x10C. Casting the shifted alpha byte to int avoids an
 * unsigned-to-float fallback absent in retail. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void draw_world_quad(void *, int, int);
extern float math_random_float_range(float, float);
extern char g_hero_l11_position[];
extern float g_chain_creature_ribbon_alpha_min __attribute__((sda));
extern float g_chain_creature_ribbon_length_a __attribute__((sda));
extern float g_chain_creature_ribbon_length_b __attribute__((sda));
extern float g_chain_creature_ribbon_inset __attribute__((sda));
extern float g_chain_creature_ribbon_scroll_speed __attribute__((sda));
extern unsigned int g_chain_creature_ribbon_color __attribute__((sda));
extern unsigned int g_chain_creature_quad_color __attribute__((sda));
extern float g_chain_creature_ribbon_uv_u[] SDATA(D_L11_001B1280);
extern float g_chain_creature_ribbon_uv_v[];
extern float g_chain_creature_ribbon_alpha_max[] NOT_SDA;
/* The alpha range endpoint at 001B12B4 is read as float by retail. */
/* Draws the chain as a glowing ribbon between its points and scrolls its texture. */
void chain_creature_draw_ribbon(char *obj) {
    float end[4], start[4], span[4], a[4], b[4], inset[4];
    struct { Quadword pos[4]; unsigned int color[4]; float uv[4][2]; unsigned long words[4]; } quad;
    Quadword corner;
    float *uv0, *uv1;
    char *vars=*(char **)(obj+0x68);
    int next, prev, following, i;
    unsigned char *flags;
    unsigned int color;
    if (*(unsigned char *)(obj+0x20)<2) return;
    next=1; prev=0; flags=(unsigned char *)(vars+0x380);
    while(next<13) { int j=next-1; if(!flags[j]) break; next++; }
    while (next<12) {
        qcopy(end,vars+0x100+next*16);
        qcopy(start,vars+0x100+prev*16);
        following=next+1;
        FastVecSub(inset,start,end);
        vec_scale_to_length(inset,inset,g_chain_creature_ribbon_inset);
        FastVecAdd(end,end,inset);
        FastVecSub(span,end,start);
        FastVecSub(a,end,g_hero_l11_position);
        FastVecSub(b,start,g_hero_l11_position);
        FastVecCross(a,a,span);
        FastVecCross(b,b,span);
        vec_scale_to_length(a,a,g_chain_creature_ribbon_length_a);
        vec_scale_to_length(b,b,g_chain_creature_ribbon_length_a);
        gfx_init_quad_packet_state(&quad,23,1,128);
        color=(g_chain_creature_ribbon_color & 0xFFFFFF) | ((int)(math_random_float_range(g_chain_creature_ribbon_alpha_min,g_chain_creature_ribbon_alpha_max[0])*(int)(g_chain_creature_ribbon_color>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        uv0=&quad.uv[0][0]; uv1=&quad.uv[0][1];
        for(i=0;i<4;i++) { uv0[i*2]=g_chain_creature_ribbon_uv_u[i*2]+*(float *)(vars+0x35C); uv1[i*2]=g_chain_creature_ribbon_uv_v[i*2]; }
        FastVecSub(&corner,end,a); quad.pos[0]=corner;
        FastVecAdd(&corner,end,a); quad.pos[1]=corner;
        FastVecSub(&corner,start,b); quad.pos[2]=corner;
        FastVecAdd(&corner,start,b); quad.pos[3]=corner;
        draw_world_quad(&quad,0,0);
        vec_scale_to_length(a,a,g_chain_creature_ribbon_length_b);
        vec_scale_to_length(b,b,g_chain_creature_ribbon_length_b);
        FastVecSub(&corner,end,a); quad.pos[0]=corner;
        FastVecAdd(&corner,end,a); quad.pos[1]=corner;
        FastVecSub(&corner,start,b); quad.pos[2]=corner;
        FastVecAdd(&corner,start,b); quad.pos[3]=corner;
        gfx_init_quad_packet_state(&quad,43,1,128);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=g_chain_creature_quad_color;
        draw_world_quad(&quad,0,0);
        prev=next; next=following;
        while(next<13) { int j=next-1; if(!flags[j]) break; next++; }
    }
    *(float *)(vars+0x35C)+=g_chain_creature_ribbon_scroll_speed;
    if (*(float *)(vars+0x35C)>1) *(float *)(vars+0x35C)-=2;
    if (*(float *)(vars+0x35C)<-1) *(float *)(vars+0x35C)+=2;
}
