#include "common.h"

typedef int VectorBits __attribute__((mode(TI)));
typedef union { VectorBits bits; float f[4]; } __attribute__((aligned(16))) BeamVector;
typedef float Vector[4] __attribute__((aligned(16)));

/* One GS quad: four corners, vertex colors, texture coordinates and the GIF registers. */
typedef struct {
    float vertices[4][4];
    unsigned int colors[4];
    float uv[4][2];
    u64 registers[4];
} __attribute__((aligned(16))) BeamQuad;

typedef struct { float x, y, z, w; } Vec16_Fc936841d;

extern u64 func_0027C878(int);
extern void func_0031F1A8(Vec16_Fc936841d *, int);
extern void func_0031E750(char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern float func_00283CE0(int);
extern void func_00282DD8(char *, char *, char *);
extern float D_001B5340[4];
extern float func_002A7878(float, float);

/* Draw a two-layer (outer and textured inner) ribbon along sampled beam points. */
void func_0031F210(void *owner, unsigned int opacity, float points[][4], int count)
{
    BeamQuad outer, inner __attribute__((aligned(16)));
    Vector frame[4];
    BeamVector outerWidth, innerWidth;
    float *initial = points[1];
    int index;
    unsigned int innerColor = 0x80FF0000;

    outer.registers[1] = GetEffectTextureDescriptor(43);
    outer.registers[3] = ((u64)opacity << 32) | 0x68;
    outer.registers[2] = 0xFF9000000260ULL;
    outer.registers[0] = 0;
    outer.colors[1] = 0x7FAFAFAF;
    outer.colors[0] = 0x7FAFAFAF;

    inner.registers[1] = GetEffectTextureDescriptor(43);
    inner.registers[2] = 0xFF9000000260ULL;
    inner.registers[0] = 0;
    inner.registers[3] = ((u64)((int)opacity / 3) << 32) | 0x68;

    outerWidth.bits = 0;
    innerWidth.bits = 0;
    inner.colors[1] = innerColor;
    inner.colors[0] = innerColor;
    outerWidth.f[3] = 1.0f;
    innerWidth.f[3] = 1.0f;
    outerWidth.f[2] = RandomFloatRange(0.02f, 0.1f);
    innerWidth.f[2] = RandomFloatRange(0.15f, 0.3f);

    ExtrapolateRibbonPoint((Vec16_Fc936841d *)points, count);
    InitSmallQuadPacket((char *)&outer);
    InitSmallQuadPacket((char *)&inner);

    outer.uv[0][0] = 0.0f;
    outer.uv[0][1] = 0.0f;
    outer.uv[1][0] = 0.0f;
    outer.uv[1][1] = 1.0f;
    outer.uv[2][0] = 1.0f;
    outer.uv[2][1] = 0.0f;
    outer.uv[3][0] = 1.0f;
    outer.uv[3][1] = 1.0f;

    inner.uv[0][0] = 0.0f;
    inner.uv[0][1] = 0.0f;
    inner.uv[1][0] = 0.0f;
    inner.uv[1][1] = 1.0f;
    inner.uv[2][0] = 0.33f;
    inner.uv[2][1] = 0.0f;
    inner.uv[3][0] = 0.33f;
    inner.uv[3][1] = 1.0f;

    FastVecSub(frame[0], initial, points[0]);
    vec_scale_to_length(frame[0], frame[0], 1.0f);
    FastVecSub(frame[1], gCameraState_001B5340, points[0]);
    FastVecCross((char *)frame[2], (char *)frame[1], (char *)frame[0]);
    vec_scale_to_length(frame[2], frame[2], 1.0f);
    FastVecCross((char *)frame[1], (char *)frame[0], (char *)frame[2]);
    qcopy(frame[3], points[0]);

    qcopy(outer.vertices[0], &outerWidth);
    FastVecScale(outer.vertices[1], outer.vertices[0], -1.0f);
    transform_vector(outer.vertices[0], outer.vertices[0], frame);
    transform_vector(outer.vertices[1], outer.vertices[1], frame);

    qcopy(inner.vertices[0], &innerWidth);
    FastVecScale(inner.vertices[1], inner.vertices[0], -1.0f);
    transform_vector(inner.vertices[0], inner.vertices[0], frame);
    transform_vector(inner.vertices[1], inner.vertices[1], frame);

    for (index = 1; index < count - 1; index++) {

        qcopy(outer.vertices[2], &outerWidth);
        FastVecScale(outer.vertices[3], outer.vertices[2], -1.0f);
        qcopy(inner.vertices[2], &innerWidth);
        FastVecScale(inner.vertices[3], inner.vertices[2], -1.0f);

        FastVecSub(frame[0], points[index + 1], points[index]);
        vec_scale_to_length(frame[0], frame[0], 1.0f);
        FastVecSub(frame[1], gCameraState_001B5340, points[index]);
        FastVecCross((char *)frame[2], (char *)frame[1], (char *)frame[0]);
        vec_scale_to_length(frame[2], frame[2], 1.0f);
        FastVecCross((char *)frame[1], (char *)frame[0], (char *)frame[2]);
        qcopy(frame[3], points[index]);

        transform_vector(outer.vertices[2], outer.vertices[2], frame);
        transform_vector(outer.vertices[3], outer.vertices[3], frame);
        transform_vector(inner.vertices[2], inner.vertices[2], frame);
        transform_vector(inner.vertices[3], inner.vertices[3], frame);

        outer.colors[2] = outer.colors[3] = 0x7FAFAFAF;
        inner.colors[2] = inner.colors[3] = innerColor;

        draw_world_quad(&outer, 0, 0);
        draw_world_quad(&inner, 0, 0);

        {
            float startU = IntToFloat(index) * 0.33f;
            float endU = startU + 0.33f;
            if (startU >= 1.0f) {
                startU -= 1.0f;
                endU -= 1.0f;
            }
            inner.uv[0][0] = startU;
            inner.uv[2][0] = endU;
            inner.uv[1][0] = startU;
            inner.uv[3][0] = endU;
        }

        qcopy(outer.vertices[0], outer.vertices[2]);
        qcopy(outer.vertices[1], outer.vertices[3]);
        qcopy(inner.vertices[0], inner.vertices[2]);
        qcopy(inner.vertices[1], inner.vertices[3]);
    }
}
