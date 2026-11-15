#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
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

extern EffectCameraView ref_L00_00388790_00;
extern void gfx_l00_init_default_block(char *);
extern void part_l00_draw_camera_facing_flash(void *, float *);

/* Construct two camera-facing ribbons with independently sized end caps. */
void gfx_l00_draw_twin_beam_ribbons(char *owner)
{
    EffectPacket narrow, wide;
    EffectVector basis[4];
    EffectVector startPoint, endPoint;
    EffectVector joint;
    EffectVector thinWidth, wideWidth;
    char *state = *(char **)(owner + 0x68);
    moby_transform_joint_to_world(owner, 1, (char *)&joint);
    EFFECT_COPY(&startPoint, &joint);
    vec_scale_to_length(&endPoint, state + 0x30, math_random_float_range(2.0f, 4.0f));
    matrix_mul_vec3(&endPoint, &endPoint, owner + 0xC0);
    FastVecAdd(&endPoint, &endPoint, &joint);
    part_l00_draw_camera_facing_flash(owner, (float *)&startPoint);
    narrow.texture = GetEffectTextureDescriptor(23);
    narrow.mode = 0x0000ff9000000260UL;
    narrow.primitive = 0;
    narrow.registers = 0x0000008000000048UL;
    narrow.color[0] = narrow.color[1] = 0x7f103080;
    narrow.color[2] = narrow.color[3] = 0x00103080;
    wide.texture = GetEffectTextureDescriptor(23);
    wide.mode = 0x0000ff9000000260UL;
    wide.primitive = 0;
    wide.registers = 0x0000008000000048UL;
    wide.color[2] = wide.color[3] = 0x00103080;
    wide.color[0] = wide.color[1] = 0x3f103080;
    *(EffectWord *)&thinWidth = 0;
    *(EffectWord *)&wideWidth = 0;
    thinWidth.w = 1.0f;
    wideWidth.w = 1.0f;
    thinWidth.z = math_random_float_range(0.1f, 0.3f);
    wideWidth.z = thinWidth.z + thinWidth.z;
    gfx_l00_init_default_block((char *)&narrow);
    gfx_l00_init_default_block((char *)&wide);
    if (!(func_001163B0() & 1)) {
        narrow.uv[0][0] = 0;
        narrow.uv[0][1] = 0;
        narrow.uv[1][0] = 0;
        narrow.uv[1][1] = 1.0f;
        narrow.uv[2][0] = 1.0f;
        narrow.uv[2][1] = 0;
        narrow.uv[3][0] = 1.0f;
        narrow.uv[3][1] = 1.0f;
        wide.uv[0][0] = 0;
        wide.uv[0][1] = 0;
        wide.uv[1][0] = 0;
        wide.uv[1][1] = 1.0f;
        wide.uv[2][0] = 1.0f;
        wide.uv[2][1] = 0;
        wide.uv[3][0] = 1.0f;
        wide.uv[3][1] = 1.0f;
    } else {
        narrow.uv[0][0] = 0;
        narrow.uv[0][1] = 1.0f;
        narrow.uv[1][0] = 0;
        narrow.uv[1][1] = 0;
        narrow.uv[2][0] = 1.0f;
        narrow.uv[2][1] = 1.0f;
        narrow.uv[3][0] = 1.0f;
        narrow.uv[3][1] = 0;
        wide.uv[0][0] = 0;
        wide.uv[0][1] = 1.0f;
        wide.uv[1][0] = 0;
        wide.uv[1][1] = 0;
        wide.uv[2][0] = 1.0f;
        wide.uv[2][1] = 1.0f;
        wide.uv[3][0] = 1.0f;
        wide.uv[3][1] = 0;
    }
    FastVecSub(&basis[0], &endPoint, &startPoint);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecSub(&basis[1], &ref_L00_00388790_00.position, &startPoint);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    vec_scale_to_length(&basis[2], &basis[2], 1.0f);
    FastVecCross(&basis[1], &basis[0], &basis[2]);
    EFFECT_COPY(&basis[3], &startPoint);
    EFFECT_COPY(&narrow.position[0], &thinWidth);
    EFFECT_COPY(&wide.position[0], &wideWidth);
    FastVecScale(&narrow.position[1], &narrow.position[0], -1.0f);
    FastVecScale(&wide.position[1], &wide.position[0], -1.0f);
    transform_vector(&narrow.position[0], &narrow.position[0], basis);
    transform_vector(&narrow.position[1], &narrow.position[1], basis);
    transform_vector(&wide.position[0], &wide.position[0], basis);
    transform_vector(&wide.position[1], &wide.position[1], basis);
    EFFECT_COPY(&basis[3], &endPoint);
    thinWidth.z *= 0.15f;
    wideWidth.z = thinWidth.z + thinWidth.z;
    EFFECT_COPY(&narrow.position[2], &thinWidth);
    EFFECT_COPY(&wide.position[2], &wideWidth);
    FastVecScale(&narrow.position[3], &narrow.position[2], -1.0f);
    FastVecScale(&wide.position[3], &wide.position[2], -1.0f);
    transform_vector(&narrow.position[2], &narrow.position[2], basis);
    transform_vector(&narrow.position[3], &narrow.position[3], basis);
    transform_vector(&wide.position[2], &wide.position[2], basis);
    transform_vector(&wide.position[3], &wide.position[3], basis);
    draw_world_quad(&narrow, 0, 0);
    draw_world_quad(&wide, 0, 0);
}
