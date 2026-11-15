#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) StripVector;
typedef struct {
    StripVector vertices[4];
    unsigned int colors[4];
    union {
        float uv[8];
        unsigned int uv_bits[8];
    } tex;
    long long zero, texture, state, flags;
} StripPacket;
typedef struct { unsigned char pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef union { unsigned int value; unsigned char bytes[4]; } StripColor;
extern char *level_get_slot_body(int, int);
extern void gfx_init_quad_packet_state(QuadPacket *, int, int, int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FastTweenColor(int, int, float);
extern void draw_world_quad(void *, void *, int);
extern StripColor D_L00_001B0958;
extern unsigned int D_L00_001B0958_word SDATA(D_L00_001B0958);
extern StripColor D_L00_001B095C;
extern unsigned int D_L00_001B095C_word SDATA(D_L00_001B095C);
extern StripColor D_L00_001B0960;
extern unsigned int D_L00_001B0960_word SDATA(D_L00_001B0960);
extern StripColor D_L00_001B0964;
extern unsigned int D_L00_001B0964_word SDATA(D_L00_001B0964);
extern float D_L00_001B0968 __attribute__((sda));
extern float D_L00_001B096C __attribute__((sda));
extern int D_L00_001B0974 __attribute__((sda));
extern int D_L00_001B0978 __attribute__((sda));
extern int D_0018C0B4 __attribute__((nosda));
extern StripVector g_camera_l00_position __attribute__((nosda));

/* Draws inner and outer strips along the effect's 0x30-byte point records.
   Each point uses the view direction to face the strip towards the camera;
   its stored width scales the inner strip, then the shared factor widens the
   outer strip. Endpoint colors fade with the state and interpolate along it. */
void RenderTwoLayerEffectStrip(char *object)
{
    char *state = *(char **)(object + 0x68);
    StripPacket inner, outer;
    StripVector normal, offset, view, direction;
    char *base, *point;
    int i;
    unsigned int innerA, innerB, outerA, outerB;
    float fade, step, stripRatio, zero, scroll;
    if (*(short *)(state + 0x20) <= 1 || *(short *)(state + 0x22) == 0)
        return;
    base = *(char **)(level_get_slot_body(0xC04 /* Vaporizer */, *(short *)(state + 0x1A)) + *(short *)(state + 0x18) * 4);
    gfx_init_quad_packet_state((QuadPacket *)&inner, D_L00_001B0974, 1, 0x80);
    scroll = D_L00_001B096C;
    inner.tex.uv[0] = 0.0f;
    inner.tex.uv_bits[1] = 0;
    inner.tex.uv[3] = 1.0f;
    /* Reuse the initial zero for the outer strip's V coordinates. */
    zero = inner.tex.uv[0];
    inner.tex.uv[2] = scroll;
    inner.tex.uv[0] = scroll;
    inner.tex.uv[4] = inner.tex.uv[6] = D_L00_001B096C + 1.0f;
    /* The packet also exposes coordinates as raw words for zero initialization. */
    inner.tex.uv_bits[5] = 0;
    inner.tex.uv[7] = 1.0f;
    gfx_init_quad_packet_state((QuadPacket *)&outer, D_L00_001B0978, 1, 0x80);
    outer.tex.uv[3] = 1.0f;
    outer.tex.uv[7] = 1.0f;
    outer.tex.uv[1] = zero;
    outer.tex.uv[0] = outer.tex.uv[2] = D_L00_001B096C;
    outer.tex.uv[5] = zero;
    outer.tex.uv[4] = outer.tex.uv[6] = D_L00_001B096C + 1.0f;
    fade = (float)*(short *)(state + 0x22) * *(float *)(state + 0x24);
    if (D_0018C0B4 == 0x1D)
        fade *= 0.5f;
    innerA = (unsigned int)FloatToInt(IntToFloat(D_L00_001B0958.bytes[3]) * fade) << 24 | (D_L00_001B0958_word & 0xFFFFFF);
    innerB = (unsigned int)FloatToInt(IntToFloat(D_L00_001B0960.bytes[3]) * fade) << 24 | (D_L00_001B0960_word & 0xFFFFFF);
    outerA = (unsigned int)FloatToInt(IntToFloat(D_L00_001B095C.bytes[3]) * fade) << 24 | (D_L00_001B095C_word & 0xFFFFFF);
    outerB = (unsigned int)FloatToInt(IntToFloat(D_L00_001B0964.bytes[3]) * fade) << 24 | (D_L00_001B0964_word & 0xFFFFFF);
    inner.colors[0] = inner.colors[1] = innerA;
    outer.colors[0] = outer.colors[1] = outerA;
    FastVecSub(&view, base, &g_camera_l00_position);
    FastVecSub(&direction, base + 0x30, base);
    FastVecCross(&normal, &direction, &view);
    vec_scale_to_length(&offset, &normal, *(float *)(base + 0xC));
    FastVecAdd(&inner.vertices[0], base, &offset);
    FastVecSub(&inner.vertices[1], base, &offset);
    FastVecScale(&offset, &offset, D_L00_001B0968);
    FastVecAdd(&outer.vertices[0], base, &offset);
    FastVecSub(&outer.vertices[1], base, &offset);
    step = 1.0f / IntToFloat(*(short *)(state + 0x20));
    for (i = 1; i < *(short *)(state + 0x20); i++) {
        point = base + i * 0x30;
        FastVecSub(&view, point, &g_camera_l00_position);
        FastVecSub(&direction, point, base + (i * 0x30 - 0x30));
        FastVecCross(&normal, &direction, &view);
        vec_scale_to_length(&offset, &normal, *(float *)(point + 0xC));
        FastVecAdd(&inner.vertices[2], point, &offset);
        FastVecSub(&inner.vertices[3], point, &offset);
        FastVecScale(&offset, &offset, D_L00_001B0968);
        FastVecAdd(&outer.vertices[2], point, &offset);
        FastVecSub(&outer.vertices[3], point, &offset);
        stripRatio = IntToFloat(i) * step;
        inner.colors[2] = inner.colors[3] = FastTweenColor(innerA, innerB, stripRatio);
        outer.colors[2] = outer.colors[3] = FastTweenColor(outerA, outerB, stripRatio);
        draw_world_quad(&inner, 0, 0);
        draw_world_quad(&outer, 0, 0);
        qcopy(&inner.vertices[0], &inner.vertices[2]);
        qcopy(&inner.vertices[1], &inner.vertices[3]);
        qcopy(&outer.vertices[0], &outer.vertices[2]);
        qcopy(&outer.vertices[1], &outer.vertices[3]);
        inner.colors[0] = inner.colors[1] = inner.colors[2];
        outer.colors[0] = outer.colors[1] = outer.colors[2];
    }
}
