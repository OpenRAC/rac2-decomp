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
extern float D_L05_002B8330[][4],D_L05_002B8670[][4];
extern char D_L05_002B8550[],D_L05_001B96C0[];
extern int D_L05_001B11D0 __attribute__((sda));
extern int D_L05_001B11D4 __attribute__((sda));
extern int D_L05_001B11D8 __attribute__((sda));
extern int D_L05_001B11DC __attribute__((sda));
extern int D_L05_001B11E0 __attribute__((sda));
extern int D_L05_001B11E4 __attribute__((sda));
extern int D_L05_001B1218 __attribute__((sda));
extern int D_L05_001B1078 __attribute__((sda));
extern float D_L05_001B11E8 __attribute__((sda));
extern float D_L05_001B11F0 __attribute__((sda));
extern float D_L05_001B11F4 __attribute__((sda));
extern float D_L05_001B11FC __attribute__((sda));
extern float D_L05_001B1200 __attribute__((sda));
extern float D_L05_001B1204 __attribute__((sda));
extern float D_L05_001B120C __attribute__((sda));
extern float D_L05_001B1210 __attribute__((sda));
extern float D_L05_001B1214 __attribute__((sda));
extern float D_L05_001B121C __attribute__((sda));
extern float D_L05_001B1220 __attribute__((sda));
extern float D_L05_001B1224 __attribute__((sda));
extern float D_L05_001B1228 __attribute__((sda));
extern float D_L05_001B122C __attribute__((sda));
extern char D_L05_001B1090[] SDATA(D_L05_001B1090);
extern char D_L05_001B1130[] SDATA(D_L05_001B1130);
extern char D_L05_001B11A0[] SDATA(D_L05_001B11A0);
extern float D_L05_001B10F0[][4] SDATA(D_L05_001B10F0);
extern float D_L05_001B1160[][4] SDATA(D_L05_001B1160);
extern int D_L05_001B11F8 __attribute__((sda));
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
        D_L05_001B11D8=0x80000000;
        D_L05_001B11DC=0x20000000;
        D_L05_001B11E0=0x40000000;
        D_L05_001B11D4=0xFFFF0000;
        D_L05_001B11E4=0xFFFF0000;
        effect->size+=D_L05_001B122C;
        {
            float radius=D_L05_001B121C+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x31,0x40801010,1,radius,0.0f,angle);
        }
        {
            float radius=D_L05_001B1220+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x31,0x707F7F7F,1,radius,0.0f,angle);
        }
        {
            float radius=D_L05_001B1224+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,0x2F,0x407F7F7F,1,radius,0.0f,angle);
        }
        {
            float radius=D_L05_001B1228+effect->size;
            float angle=math_random_angle();
            gfx_draw_billboard_quad(object+0x10,D_L05_001B1218,0x407F7F7F,1,radius,0.0f,angle);
        }
        return;
    }
    VU1_addGSregister(6,GetEffectTextureDescriptor(D_L05_001B11D0));
    VU1_addGSregister(0x42,0x8000000048LL);
    VU1_addGSregister(8,0);
    VU1_addGSregister(0x14,0xFF9000000260LL);
    font_queue_vu_state();
    copy_matrix_rotation(basis[0],object+0xC0);
    FastVecScale(&point,basis[0],-D_L05_001B11E8);
    FastVecAdd(basis[3],object+0x10,&point);
    width=D_L05_001B1200;
    height=D_L05_001B1214;
    if (*(short *)(effect->owner+0xAA)==0x97C /* moby class 2428 */) width=height=0.2f;
    {
        int i;
        for(i=0;i<34;i++) {
        point.x=D_L05_002B8330[i][0]*width; point.y=D_L05_002B8330[i][1]*D_L05_001B1204; point.z=D_L05_002B8330[i][2]*D_L05_001B1204; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=D_L05_001B11D4|effect->alpha;
        }
    }
    part_draw_glint_effect(D_L05_001B1078,vertices,colors,D_L05_002B8550,1);
    FastVecSub(view,D_L05_001B96C0,basis[3]);
    FastVecCross(basis[1],basis[0],view);vec_scale_to_length(basis[1],basis[1],1.0f);
    FastVecCross(basis[2],basis[1],basis[0]);
    VU1_addGSregister(6,GetEffectTextureDescriptor(11));
    VU1_addGSregister(0x42,0x7F00000044LL);
    {
        int i;
        for(i=0;i<8;i++) {
        point.x=D_L05_002B8670[i][0]*width; point.y=D_L05_002B8670[i][1]*D_L05_001B1204; point.z=D_L05_002B8670[i][2]; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=D_L05_001B11D8|effect->alpha;
        }
    }
    part_draw_glint_effect(8,vertices,colors,D_L05_001B1090,1);
    VU1_addGSregister(0x42,0x7F00000048LL);
    {
        int i;
        float scale_x=1.1f;
        float scale_y=3.0f;
        for(i=0;i<8;i++) {
        point.x=D_L05_002B8670[i][0]*width*scale_x; point.y=D_L05_002B8670[i][1]*D_L05_001B1204*scale_y; point.z=D_L05_002B8670[i][2]; point.w=1.0f;
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=D_L05_001B11DC|effect->alpha;
        }
    }
    part_draw_glint_effect(8,vertices,colors,D_L05_001B1090,1);
    VU1_addGSregister(0x42,0x7F00000044LL);
    FastVecScale(&point,basis[0],height);FastVecAdd(basis[3],basis[3],&point);
    {
        int i;
        for(i=0;i<4;i++) {
        vec_scale_to_length(&point,D_L05_001B1160[i],D_L05_001B120C);
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=D_L05_001B11E0|effect->alpha;
        }
    }
    part_draw_glint_effect(4,vertices,colors,D_L05_001B11A0,1);
    VU1_addGSregister(0x42,0x7F00000048LL);
    {
        int i;
        for(i=0;i<4;i++) {
        vec_scale_to_length(&point,D_L05_001B1160[i],D_L05_001B1210);
        transform_vector(&point,&point,basis[0]);
        {EffectPosition *out=&vertices[i];out->x=point.x;out->y=point.y;out->z=point.z;}
        colors[i]=D_L05_001B11E4|effect->alpha;
        }
    }
    part_draw_glint_effect(4,vertices,colors,D_L05_001B11A0,1);
    uv.q=0;uv.f[2]=1.0f;uv.f[3]=1.0f;
    VU1_addGSregister(6,GetEffectTextureDescriptor(0x40));
    FastVecSub(basis[0],D_L05_001B96C0,basis[3]);vec_scale_to_length(basis[0],basis[0],1.0f);
    FastVecCross(basis[1],basis[0],uv.f);vec_scale_to_length(basis[1],basis[1],1.0f);FastVecCross(basis[2],basis[1],basis[0]);
    radius=effect->radius;
    math_apply_axis_rotation_to_quat(basis[1],basis[1],basis[0],radius);math_apply_axis_rotation_to_quat(basis[2],basis[2],basis[0],radius);
    effect->radius=FastAddRotations(effect->radius,effect->speed*0.017453294f*D_L05_001B11FC);
    math_build_axis_angle_quat(rotation,basis[0],1.5707965f);
    for(j=0;j<4;j++) {
        {
            int i;
            for(i=0;i<4;i++) {
            {float *row=D_L05_001B10F0[i];point.x=row[0]; point.y=row[1]*D_L05_001B11F0; point.z=row[2]*D_L05_001B11F4; point.w=1.0f;}
            transform_vector(&point,&point,basis[0]);
            (vertices+i)->x=point.x;(vertices+i)->y=point.y;(vertices+i)->z=point.z;
            colors[i]=D_L05_001B11F8|effect->alpha;
            }
        }
        part_draw_glint_effect(4,vertices,colors,D_L05_001B1130,1);
        if(j!=3) {vec_rotate_by_quaternion(basis[1],basis[1],rotation);vec_rotate_by_quaternion(basis[2],basis[2],rotation);}
    }
}
