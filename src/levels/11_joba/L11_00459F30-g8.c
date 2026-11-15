#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    Vector point[4];
    unsigned int color[4];
    float uv[8];
    u64 reserved, texture, setup, state;
} EffectPacket;
extern unsigned int ref_L11_00459F30_0 __attribute__((sda));
extern unsigned int ref_L11_00459F30_1 __attribute__((sda));
extern unsigned int ref_L11_00459F30_2 __attribute__((sda));
extern Vector ref_L11_00459F30_4;
extern u64 GetEffectTextureDescriptor(int);
extern int func_001163B0(void);
extern float math_random_float_range(float,float);
/* The packet initialiser: a different copy of the same body in each level. */
extern void ref_L11_00459F30_3(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void transform_vector(void *,void *,void *);
extern void draw_world_quad(void *,int,int);

/* Build the three textured strips around the effect's two endpoints. */
/* Draws the crackling energy strips between the two ends of a beam effect. */
void gfx_l11_draw_beam_strips(u8 *object)
{
    EffectPacket a,b,c;
    u64 texture;
    Vector frame[4];
    Vector small,wide,tall;
    u8 *effect=*(u8 **)(object+0x68);
    u64 setup=0xFF9000000260ULL;
    u64 state=0x8000000048ULL;
    a.texture=GetEffectTextureDescriptor(16);
    a.setup=setup;
    a.reserved=0;
    a.state=0x8000000040ULL | ((u64)(func_001163B0()%2+1)<<2);
    a.color[1]=ref_L11_00459F30_0; a.color[0]=ref_L11_00459F30_0; a.color[3]=ref_L11_00459F30_0; a.color[2]=ref_L11_00459F30_0;
    b.texture=GetEffectTextureDescriptor(16);
    b.setup=setup; b.state=state; b.reserved=0;
    b.color[1]=ref_L11_00459F30_1; b.color[0]=ref_L11_00459F30_1; b.color[3]=ref_L11_00459F30_1; b.color[2]=ref_L11_00459F30_1;
    texture=GetEffectTextureDescriptor(16);
    c.texture=texture; c.setup=setup; c.state=state;
    c.reserved=0; c.color[1]=ref_L11_00459F30_2; c.color[0]=ref_L11_00459F30_2; c.color[3]=ref_L11_00459F30_2; c.color[2]=ref_L11_00459F30_2;
    small.q=0; wide.q=0; tall.q=0;
    small.f[3]=1.0f; wide.f[3]=1.0f; tall.f[3]=1.0f;
    tall.f[2]=math_random_float_range(0.2f,0.25f);
    small.f[2]=math_random_float_range(0.3f,0.4f);
    wide.f[2]=small.f[2]+small.f[2];
    tall.f[2]*=*(float *)(effect+0x60);
    wide.f[2]*=*(float *)(effect+0x60);
    small.f[2]*=*(float *)(effect+0x60);
    ref_L11_00459F30_3(&a); ref_L11_00459F30_3(&b); ref_L11_00459F30_3(&c);
    a.uv[0]=0; a.uv[1]=0; a.uv[2]=0; a.uv[3]=1; a.uv[4]=1; a.uv[5]=0; a.uv[6]=1; a.uv[7]=1;
    b.uv[0]=0; b.uv[1]=0; b.uv[2]=0; b.uv[3]=1; b.uv[4]=1; b.uv[5]=0; b.uv[6]=1; b.uv[7]=1;
    c.uv[0]=0; c.uv[1]=0; c.uv[2]=0; c.uv[3]=1; c.uv[4]=1; c.uv[5]=0; c.uv[6]=1; c.uv[7]=1;
    FastVecSub(&frame[0],effect+0x20,effect+0x10);
    vec_scale_to_length(&frame[0],&frame[0],1.0f);
    FastVecSub(&frame[1],&ref_L11_00459F30_4,effect+0x10);
    FastVecCross(&frame[2],&frame[1],&frame[0]);
    vec_scale_to_length(&frame[2],&frame[2],1.0f);
    FastVecCross(&frame[1],&frame[0],&frame[2]);
    qcopy(&frame[3], effect+0x10);
    qcopy(&a.point[0], &small); qcopy(&b.point[0], &wide); qcopy(&c.point[0], &tall);
    FastVecScale(&a.point[1],&a.point[0],-1.0f);
    FastVecScale(&b.point[1],&b.point[0],-1.0f);
    FastVecScale(&c.point[1],&c.point[0],-1.0f);
    transform_vector(&a.point[0],&a.point[0],frame);
    transform_vector(&a.point[1],&a.point[1],frame);
    transform_vector(&b.point[0],&b.point[0],frame);
    transform_vector(&b.point[1],&b.point[1],frame);
    transform_vector(&c.point[0],&c.point[0],frame);
    transform_vector(&c.point[1],&c.point[1],frame);
    qcopy(&frame[3], effect+0x20);
    qcopy(&a.point[2], &small); qcopy(&b.point[2], &wide); qcopy(&c.point[2], &tall);
    FastVecScale(&a.point[3],&a.point[2],-1.0f);
    FastVecScale(&b.point[3],&b.point[2],-1.0f);
    FastVecScale(&c.point[3],&c.point[2],-1.0f);
    transform_vector(&a.point[2],&a.point[2],frame);
    transform_vector(&a.point[3],&a.point[3],frame);
    transform_vector(&b.point[2],&b.point[2],frame);
    transform_vector(&b.point[3],&b.point[3],frame);
    transform_vector(&c.point[2],&c.point[2],frame);
    transform_vector(&c.point[3],&c.point[3],frame);
    draw_world_quad(&a,0,0); draw_world_quad(&b,0,0); draw_world_quad(&c,0,0);
}
