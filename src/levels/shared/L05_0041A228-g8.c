#include "include_asm.h"
#include "common.h"
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *,int,int,int,float,float,float);
extern long long GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int,long long);
extern void font_queue_vu_state(void);
extern void copy_matrix_rotation(void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void transform_vector(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_draw_glint_effect(int,void *,void *,void *,int);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern float FastAddRotations(float,float);
extern void math_build_axis_angle_quat(void *,void *,float);
extern void vec_rotate_by_quaternion(void *,void *,void *);
extern float g_energy_blast_points[][4],g_energy_blast_outer_points[][4];
extern char g_energy_blast_glint_params[],g_origin_vec[];
extern int g_energy_blast_texture_id __attribute__((sda));
extern int g_energy_blast_color_a __attribute__((sda));
extern int g_energy_blast_color_b __attribute__((sda));
extern int g_energy_blast_color_c __attribute__((sda));
extern int g_energy_blast_color_d __attribute__((sda));
extern int g_energy_blast_color_e __attribute__((sda));
extern int g_energy_blast_billboard_tex __attribute__((sda));
extern int g_energy_blast_glint_count __attribute__((sda));
extern float g_energy_blast_basis_scale __attribute__((sda));
extern float g_energy_blast_scale_y __attribute__((sda));
extern float g_energy_blast_scale_z __attribute__((sda));
extern float g_energy_blast_spin_scale __attribute__((sda));
extern float g_energy_blast_width __attribute__((sda));
extern float g_energy_blast_ring_scale __attribute__((sda));
extern float g_energy_blast_length_a __attribute__((sda));
extern float g_energy_blast_length_b __attribute__((sda));
extern float g_energy_blast_height __attribute__((sda));
extern float g_energy_blast_radius_base_a __attribute__((sda));
extern float g_energy_blast_radius_base_b __attribute__((sda));
extern float g_energy_blast_radius_base_c __attribute__((sda));
extern float g_energy_blast_radius_base_d __attribute__((sda));
extern float g_energy_blast_size_growth __attribute__((sda));
extern char g_energy_blast_glint_indices_a[] SDATA(D_L05_001B1090);
extern char g_energy_blast_glint_indices_b[] SDATA(D_L05_001B1130);
extern char g_energy_blast_glint_indices_c[] SDATA(D_L05_001B11A0);
extern float g_energy_blast_vertex_table[][4] SDATA(D_L05_001B10F0);
extern float g_energy_blast_direction_table[][4] SDATA(D_L05_001B1160);
extern int g_energy_blast_color_f __attribute__((sda));
typedef struct { float x,y,z,w; } EffectVector;
typedef struct { float x,y,z; } EffectPosition;

typedef struct {
    int mode; char *owner; float radius, speed; char pad10[16];
    int alpha; char pad24[12]; int active; float size;
} EffectState;

/* Draws the glowing energy blast: shaped outlines that grow, then spinning rings. Before it is switched on it just shows a few flat flashes. */
void gfx_draw_energy_blast(char *object)
{
    int colors[34];
    EffectPosition vertices[34];
    EffectVector point;
    float basis[4][4],view[4];
    union { int q __attribute__((mode(TI))); float f[4]; } uv;
    float rotation[4];
    EffectState *effect=*(EffectState **)(object+0x68);
    float width,height,radius;
    int j;
    if (effect->active) {
        g_energy_blast_color_b=0x80000000;
        g_energy_blast_color_c=0x20000000;
        g_energy_blast_color_d=0x40000000;
        g_energy_blast_color_a=0xFFFF0000;
        g_energy_blast_color_e=0xFFFF0000;
        effect->size+=g_energy_blast_size_growth;
        {
            float radius=g_energy_blast_radius_base_a+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x31,0x40801010,1,radius,0.0f,angle);
        }
        {
            float radius=g_energy_blast_radius_base_b+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x31,0x707F7F7F,1,radius,0.0f,angle);
        }
        {
            float radius=g_energy_blast_radius_base_c+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x2F,0x407F7F7F,1,radius,0.0f,angle);
        }
        {
            float radius=g_energy_blast_radius_base_d+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,g_energy_blast_billboard_tex,0x407F7F7F,1,radius,0.0f,angle);
        }
        return;
    }
    VU1_addGSregister(6,GetEffectTextureDescriptor(g_energy_blast_texture_id));
    VU1_addGSregister(0x42,0x8000000048LL);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260LL);
    font_queue_vu_state();
    copy_matrix_rotation(basis[0],object+0xC0);
    FastVecScale(&point,basis[0],-g_energy_blast_basis_scale);
    FastVecAdd(basis[3],object+0x10,&point);
    width=g_energy_blast_width;
    height=g_energy_blast_height;
    if (*(short *)(effect->owner+0xAA)==0x97C /* moby class 2428 */) width=height=0.2f;
    {
        int i;
        for(i=0;i<34;i++) {
        point.x=g_energy_blast_points[i][0]*width; point.y=g_energy_blast_points[i][1]*g_energy_blast_ring_scale; point.z=g_energy_blast_points[i][2]*g_energy_blast_ring_scale; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=g_energy_blast_color_a|effect->alpha;
        }
    }
    part_draw_glint_effect(g_energy_blast_glint_count,vertices,colors,g_energy_blast_glint_params,1);
    FastVecSub(view,g_origin_vec,basis[3]);
    FastVecCross(basis[1],basis[0],view);vec_scale_to_length(basis[1],basis[1],1.0f);
    FastVecCross(basis[2],basis[1],basis[0]);
    VU1_addGSregister(6,GetEffectTextureDescriptor(11));
    VU1_addGSregister(0x42,0x7F00000044LL);
    {
        int i;
        for(i=0;i<8;i++) {
        point.x=g_energy_blast_outer_points[i][0]*width; point.y=g_energy_blast_outer_points[i][1]*g_energy_blast_ring_scale; point.z=g_energy_blast_outer_points[i][2]; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=g_energy_blast_color_b|effect->alpha;
        }
    }
    part_draw_glint_effect(8,vertices,colors,g_energy_blast_glint_indices_a,1);
    VU1_addGSregister(0x42,0x7F00000048LL);
    {
        int i;
        float scale_x=1.1f;
        float scale_y=3.0f;
        for(i=0;i<8;i++) {
        point.x=g_energy_blast_outer_points[i][0]*width*scale_x; point.y=g_energy_blast_outer_points[i][1]*g_energy_blast_ring_scale*scale_y; point.z=g_energy_blast_outer_points[i][2]; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=g_energy_blast_color_c|effect->alpha;
        }
    }
    part_draw_glint_effect(8,vertices,colors,g_energy_blast_glint_indices_a,1);
    VU1_addGSregister(0x42,0x7F00000044LL);
    FastVecScale(&point,basis[0],height);FastVecAdd(basis[3],basis[3],&point);
    {
        int i;
        for(i=0;i<4;i++) {
        vec_scale_to_length(&point,g_energy_blast_direction_table[i],g_energy_blast_length_a);
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=g_energy_blast_color_d|effect->alpha;
        }
    }
    part_draw_glint_effect(4,vertices,colors,g_energy_blast_glint_indices_c,1);
    VU1_addGSregister(0x42,0x7F00000048LL);
    {
        int i;
        for(i=0;i<4;i++) {
        vec_scale_to_length(&point,g_energy_blast_direction_table[i],g_energy_blast_length_b);
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=g_energy_blast_color_e|effect->alpha;
        }
    }
    part_draw_glint_effect(4,vertices,colors,g_energy_blast_glint_indices_c,1);
    uv.q=0;uv.f[2]=1.0f;uv.f[3]=1.0f;
    VU1_addGSregister(6,GetEffectTextureDescriptor(0x40));
    FastVecSub(basis[0],g_origin_vec,basis[3]);vec_scale_to_length(basis[0],basis[0],1.0f);
    FastVecCross(basis[1],basis[0],uv.f);vec_scale_to_length(basis[1],basis[1],1.0f);FastVecCross(basis[2],basis[1],basis[0]);
    radius=effect->radius;
    math_apply_axis_rotation_to_quat(basis[1],basis[1],basis[0],radius);math_apply_axis_rotation_to_quat(basis[2],basis[2],basis[0],radius);
    effect->radius=FastAddRotations(effect->radius,effect->speed*0.017453294f*g_energy_blast_spin_scale);
    math_build_axis_angle_quat(rotation,basis[0],1.5707965f);
    for(j=0;j<4;j++) {
        {
            int i;
            for(i=0;i<4;i++) {
            {float *row=g_energy_blast_vertex_table[i];point.x=row[0]; point.y=row[1]*g_energy_blast_scale_y; point.z=row[2]*g_energy_blast_scale_z; point.w=1.0f;}
            transform_vector(&point,&point,basis[0]);
            (vertices+i)->x=point.x;(vertices+i)->y=point.y;(vertices+i)->z=point.z;
            colors[i]=g_energy_blast_color_f|effect->alpha;
            }
        }
        part_draw_glint_effect(4,vertices,colors,g_energy_blast_glint_indices_b,1);
        if(j!=3) {vec_rotate_by_quaternion(basis[1],basis[1],rotation);vec_rotate_by_quaternion(basis[2],basis[2],rotation);}
    }
}
