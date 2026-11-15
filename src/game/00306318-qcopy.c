/* func_00306318 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier). */
#include "common.h"

typedef int EffectWord __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } EffectVector __attribute__((aligned(16)));
typedef struct {
    EffectVector position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectPacket;
typedef struct { u8 prefix[0x140]; EffectVector position; } EffectCameraView;
extern unsigned long GetEffectTextureDescriptor(int);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern void gfx_init_effect_packet(char *);
extern void gfx_init_effect_packet_2(char *);
extern void gfx_draw_facing_glow_small(void *, float *);
extern void gfx_draw_facing_glow(void *, float *);
extern void gfx_draw_facing_glow_2(void *, float *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
#define EFFECT_COPY(destination, source) (*(EffectWord *)(destination) = *(EffectWord *)(source))

extern EffectCameraView ref_00306318_00;

/* Construct two camera-facing ribbons with independently sized end caps. */
void gfx_draw_two_ribbon_beam(char *owner, float *start, float *end)
{
    EffectPacket narrow, wide;
    EffectVector basis[4];
    EffectVector *startPoint = (EffectVector *)start;
    EffectVector *endPoint = (EffectVector *)end;
    EffectVector thinWidth, wideWidth;
    float widthRatio = 5.5f;
    narrow.texture = GetEffectTextureDescriptor(14);
    narrow.mode = 0x0000ff9000000260UL;
    narrow.registers = 0x0000008000000048UL;
    narrow.color[0] = narrow.color[1] = 0x7f7f7f7f;
    narrow.primitive = 0;
    wide.texture = GetEffectTextureDescriptor(14);
    wide.mode = 0x0000ff9000000260UL;
    wide.registers = 0x0000008000000048UL;
    wide.primitive = 0;
    wide.color[1] = 0x7f000080;
    wide.color[0] = 0x7f000080;
    *(EffectWord *)&thinWidth = 0;
    *(EffectWord *)&wideWidth = 0;
    thinWidth.w=1.0f; wideWidth.w=1.0f;
    thinWidth.z=0.015f; wideWidth.z=thinWidth.z*widthRatio;
    gfx_init_effect_packet((char *)&narrow);
    gfx_init_effect_packet((char *)&wide);
    gfx_draw_facing_glow_small(owner,start);
    narrow.uv[0][0]=0; narrow.uv[0][1]=0;
    narrow.uv[1][0]=0; narrow.uv[1][1]=1.0f;
    narrow.uv[2][0]=1.0f; narrow.uv[2][1]=0;
    narrow.uv[3][0]=1.0f; narrow.uv[3][1]=1.0f;
    wide.uv[0][0]=0; wide.uv[0][1]=0;
    wide.uv[1][0]=0; wide.uv[1][1]=1.0f;
    wide.uv[2][0]=1.0f; wide.uv[2][1]=0;
    wide.uv[3][0]=1.0f; wide.uv[3][1]=1.0f;
    FastVecSub(&basis[0],endPoint,startPoint);
    vec_scale_to_length(&basis[0],&basis[0],1.0f);
    FastVecSub(&basis[1],&ref_00306318_00.position,startPoint);
    FastVecCross(&basis[2],&basis[1],&basis[0]);
    vec_scale_to_length(&basis[2],&basis[2],1.0f);
    FastVecCross(&basis[1],&basis[0],&basis[2]);
    EFFECT_COPY(&basis[3],startPoint);
    EFFECT_COPY(&narrow.position[0],&thinWidth);
    EFFECT_COPY(&wide.position[0],&wideWidth);
    FastVecScale(&narrow.position[1],&narrow.position[0],-1.0f);
    FastVecScale(&wide.position[1],&wide.position[0],-1.0f);
    transform_vector(&narrow.position[0],&narrow.position[0],basis);
    transform_vector(&narrow.position[1],&narrow.position[1],basis);
    transform_vector(&wide.position[0],&wide.position[0],basis);
    transform_vector(&wide.position[1],&wide.position[1],basis);
    EFFECT_COPY(&basis[3],endPoint);
    narrow.color[2] = narrow.color[3] = 0x007f7f7f;
    wide.color[2] = wide.color[3] = 0x00000080;
    thinWidth.z *= 0.25f;
    wideWidth.z = thinWidth.z*widthRatio;
    EFFECT_COPY(&narrow.position[2],&thinWidth);
    EFFECT_COPY(&wide.position[2],&wideWidth);
    FastVecScale(&narrow.position[3],&narrow.position[2],-1.0f);
    FastVecScale(&wide.position[3],&wide.position[2],-1.0f);
    transform_vector(&narrow.position[2],&narrow.position[2],basis);
    transform_vector(&narrow.position[3],&narrow.position[3],basis);
    transform_vector(&wide.position[2],&wide.position[2],basis);
    transform_vector(&wide.position[3],&wide.position[3],basis);
    draw_world_quad(&narrow,0,0);
    draw_world_quad(&wide,0,0);
}
