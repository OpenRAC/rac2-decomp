/* func_PAL_L04_003C7600, the PAL copy of func_L04_003C4050: the same C, where wrap D_L04_0023D540[i] (({e}) * 8.0f); lit 8.0f becomes 9.6f. */
#include "common.h"

/* DrawEmitterParticles, the render callback that func_L04_003C3BA0
 * (L04-particle-emitter-g8.c) registers. It builds a basis facing the camera and its
 * mirror, then draws each particle of the emitter's range: two faces of the
 * D_L04_002AB860 box for particles flagged in D_L04_0023D158, a fading sprite
 * otherwise. Last it draws the emitter's own six-face box. Its $gp tables need -G8,
 * so it has a unit of its own instead of its place in L04_002CC748.c. */
typedef unsigned int EQ __attribute__((mode(TI)));
typedef union { EQ q; float f[4]; } EVec;
typedef struct { float x,y,z,w; } RPoint __attribute__((aligned(16)));
#define EB(p,o) (*(u8 *)((char *)(p)+(o)))
#define EH(p,o) (*(s16 *)((char *)(p)+(o)))
#define EI(p,o) (*(s32 *)((char *)(p)+(o)))
#define EF(p,o) (*(float *)((char *)(p)+(o)))
extern char *g_linked_record_table;
extern char g_tether_zero_vec[];
extern EVec g_particle_positions[];
extern float g_particle_speeds[],g_particle_sizes[];
extern u8 g_particle_mirror_flags[],g_particle_sprite_flags[];
extern float g_particle_uv_offsets[],g_particle_life_rates[];
extern s16 g_particle_fade_in_timers[],g_particle_fade_out_timers[],g_particle_delay_timers[];
extern float g_particle_l04_opacity_scale_2,g_particle_fade_scale;
extern u16 g_particle_delay_reload __attribute__((sda));
extern int g_particle_base_opacity __attribute__((sda));
extern float g_particle_l04_opacity_scale __attribute__((sda));
extern EVec g_particle_quad_vertices[] SDATA(D_L04_001AF340);
extern u8 g_particle_color_weights[] SDATA(D_L04_001AF380);
extern float g_particle_l04_uv_u_table[] SDATA(D_L04_001AF388);
extern float g_particle_l04_uv_v_table[] MACRO_ADDR;
extern u8 g_particle_color_mask_table[] SDATA(D_L04_001AF3A8);
extern RPoint g_particle_vertex_offsets_a[],g_particle_vertex_offsets_b[];
extern int g_particle_quad_indices[][4];
extern float g_particle_l04_uv_v_table_2[],g_particle_l04_uv_u_table_2[],g_particle_uv_scroll_table[];
extern float ref_L04_003C4050_00;
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,int,int);
extern u32 FastDecTimer(s16 *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void transform_vector(void *,void *,void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void VU1_addGSregister(int,u64);
extern void part_init_from_ranges(void *,int);

static inline void TransformVertex(RPoint *v, EVec *m)
{
    transform_vector(v, v, m);
}
void func_PAL_L04_003C7600(char *self) {
    EVec position,up,basis[4],other[4];
    struct {
        RPoint vertices[4];
        u32 colors[4]; struct { float u,v; } uv[4]; u64 giftag[4];
    } packet;
    char *state=*(char **)(self+0x68);
    char *matrix=g_linked_record_table+EI(state,4)*128;
    u32 alpha=(u32)EB(state,0x5C)<<24;
    u32 rgb=(EB(state,0x5F)<<16)|(EB(state,0x5E)<<8)|EB(state,0x5D);
    int end=EH(state,0)+EH(state,2)+EH(state,0x40);
    int i,j,k,index,opacity;
    RPoint *vertex;
    float speed,size,age;
    qcopy(&position,self+0x10);
    up.q=0;
    position.f[3]=1.0f; up.f[2]=1.0f;
    FastVecSub(&basis[0],g_tether_zero_vec,&position);
    vec_scale_to_length(&basis[0],&basis[0],1.0f);
    FastVecCross(&basis[1],&basis[0],&up);
    vec_scale_to_length(&basis[1],&basis[1],1.0f);
    FastVecCross(&basis[2],&basis[1],&basis[0]);
    qcopy(&basis[3],&position);
    /* The mirrored basis, for particles flagged in D_L04_0023D090. */
    do {
        FastVecScale(&other[0],&basis[0],-1.0f);
        FastVecCross(&other[1],&other[0],&up);
        vec_scale_to_length(&other[1],&other[1],1.0f);
        FastVecCross(&other[2],&other[1],&other[0]);
        qcopy(&other[3],&basis[3]);
    } while (0);
    packet.giftag[1]=GetEffectTextureDescriptor(EI(state,0x54)+0x3F);
    packet.giftag[2]=0xFF9000000260ULL; packet.giftag[3]=0x8000000048ULL;
    packet.giftag[0]=0;
    VU1_addGSregister(0x4A,0); VU1_addGSregister(0x47,0x51001);
    for(i=EH(state,0);i<end;i++) {
        EVec *transform,*chosen;
        age=g_particle_uv_offsets[i]-((g_particle_life_rates[i]) * 1.2f);
        chosen=g_particle_mirror_flags[i] ? other : basis;
        transform=chosen;
        g_particle_uv_offsets[i]=age;
        if(age<=-8.0f) g_particle_uv_offsets[i]=age+8.0f;
        transform_vector(&transform[3],&g_particle_positions[i],matrix);
        speed=g_particle_speeds[i]; size=g_particle_sizes[i];
        if(g_particle_sprite_flags[i]) {
            packet.giftag[3]=0x8000000044ULL;
            for(j=2;j<4;j++) {
                for(k=0;k<4;k++) {
                    vertex=&packet.vertices[k];
                    index=g_particle_quad_indices[j][k];
                    vertex->x=g_particle_vertex_offsets_b[index].x;
                    vertex->y=g_particle_vertex_offsets_b[index].y*speed;
                    vertex->z=g_particle_vertex_offsets_b[index].z*size;
                    vertex->w=1.0f;
                    TransformVertex(vertex,transform);
                    packet.uv[k].u=(g_particle_uv_scroll_table+1)[index*2]+g_particle_uv_offsets[i]; /* u: the second float of each pair */
                    packet.uv[k].v=g_particle_uv_scroll_table[index*2];
                    packet.colors[k]=alpha*g_particle_color_mask_table[index]|rgb;
                }
                draw_world_quad(&packet,0,0);
            }
        } else {
            if(g_particle_fade_in_timers[i]) {
                FastDecTimer(&g_particle_fade_in_timers[i]);
                opacity=FloatToInt((1.0f-IntToFloat(g_particle_fade_in_timers[i])*g_particle_l04_opacity_scale_2)*g_particle_l04_opacity_scale);
            } else if(g_particle_fade_out_timers[i]) {
                if(FastDecTimer(&g_particle_fade_out_timers[i])) {
                    part_init_from_ranges(self,i); opacity=0;
                    g_particle_mirror_flags[i]=math_random_int_below(2);
                } else opacity=FloatToInt(IntToFloat(g_particle_fade_out_timers[i])*g_particle_fade_scale*g_particle_l04_opacity_scale);
            } else {
                if(FastDecTimer(&g_particle_delay_timers[i])) g_particle_fade_out_timers[i]=g_particle_delay_reload;
                opacity=g_particle_base_opacity;
            }
            packet.giftag[3]=0x8000000048ULL;
            opacity=(u32)opacity<<24;
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                vertex->x=g_particle_quad_vertices[k].f[0];
                vertex->y=g_particle_quad_vertices[k].f[1]*speed;
                vertex->z=g_particle_quad_vertices[k].f[2]*size;
                vertex->w=1.0f;
                packet.uv[k].u=g_particle_l04_uv_u_table[k*2]-g_particle_uv_offsets[i];
                packet.uv[k].v=g_particle_l04_uv_v_table[k*2];
                packet.colors[k]=(u32)opacity*g_particle_color_weights[k]|EI(state,0x38);
                TransformVertex(vertex,transform);
            }
            draw_world_quad(&packet,0,0);
        }
    }
    packet.giftag[1]=GetEffectTextureDescriptor(EI(state,0x58)+0x3F);
    packet.giftag[3]=0x8000000044ULL;
    qcopy(&basis[3],matrix+0x30);
    basis[3].f[2]-=EF(state,0x50);
    if(!EH(state,0x42)) {
        for(j=0;j<6;j++) {
            for(k=0;k<4;k++) {
                vertex=&packet.vertices[k];
                index=g_particle_quad_indices[j][k];
                vertex->x=g_particle_vertex_offsets_a[index].x;
                vertex->y=g_particle_vertex_offsets_a[index].y*EF(state,0x48);
                vertex->z=g_particle_vertex_offsets_a[index].z*EF(state,0x4C);
                vertex->w=1.0f;
                TransformVertex(vertex,basis);
                packet.uv[k].u=g_particle_l04_uv_u_table_2[index*2]+ref_L04_003C4050_00;
                packet.uv[k].v=g_particle_l04_uv_v_table_2[index*2];
                packet.colors[k]=g_particle_color_mask_table[index]*0xFF000000|rgb;
            }
            draw_world_quad(&packet,0,0);
        }
    }
}
