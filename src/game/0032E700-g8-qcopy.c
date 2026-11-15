#include "include_asm.h"
#include "common.h"
typedef int EffectVectorWord __attribute__((mode(TI)));
typedef union { float v[4]; EffectVectorWord word; } EffectVector;
typedef struct {
    u8 pad[0x70];
    long f70;
    long f78;
    long f80;
    long f88;
} QuadPacket;
typedef union {
    QuadPacket header;
    struct {
        EffectVector vertex[4];
        u32 color[4];
        float uv[8];
        long control[4];
    } fields;
} EffectPacket;
#define VERTEX(p, i) (&(p).fields.vertex[i])
#define COLORS(p) ((p).fields.color)
#define UV(p) ((p).fields.uv)
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283198(float);
extern void func_00281DE8(QuadPacket *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, void *, int);
extern char D_L00_001B8DC0[];

typedef struct {
    int timer;
    float rate;
    float scroll;
    int pad0C;
    float width0;
    float width1;
    float width2;
    float width3;
    u32 color0;
    u32 color1;
    u32 color2;
    u32 color3;
    float end[3];
    u32 color4;
} RibbonState;

/* Draw three bands of the emitter's camera-facing ribbon. */

void func_0032E700(char *object) {
    EffectVector endpoint;
    EffectVector origin;
    EffectPacket packet;
    EffectVector camera_delta;
    EffectVector segment;
    EffectVector midpoint;
    EffectVector normal;
    RibbonState *state = *(RibbonState **)(object + 0x68);
    char *position;
    float life;
    float alpha;
    int i;
    u32 color;
    float *end;

    end = state->end;
    endpoint.v[0] = end[0];
    endpoint.v[1] = end[1];
    endpoint.v[2] = end[2];
    endpoint.v[3] = 0.0f;
    origin.word = *(EffectVectorWord *)(object + 0x10);
    life = IntToFloat(state->timer) * state->rate;
    life = FastSinOrCosB(life * 3.1415927f);
    InitQuadPacketState(&packet.header, 23, 0, 0x80);
    alpha = life * 128.0f;
    COLORS(packet)[0] = COLORS(packet)[1] = COLORS(packet)[2] = COLORS(packet)[3] =
        state->color0 | ((u32)FloatToInt(alpha) << 24);
    COLORS(packet)[2] = COLORS(packet)[3] =
        state->color1 | ((u32)FloatToInt(alpha) << 24);
    UV(packet)[0] = 0.0f; UV(packet)[1] = 0.0f; UV(packet)[2] = 0.0f; UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f; UV(packet)[5] = 0.0f; UV(packet)[6] = 1.0f; UV(packet)[7] = 1.0f;
    for (i = 0; i < 4; i++) {
        UV(packet)[i * 2] -= state->scroll;
        if (UV(packet)[i * 2] <= 7.0f) UV(packet)[i * 2] += 7.0f;
    }
    state->scroll -= 0.1f;
    if (state->scroll <= 4.0f) state->scroll += 4.0f;
    position = (char *)&origin;
    FastVecSub(&camera_delta, position, gCameraPosition_L00);
    FastVecSub(&segment, &endpoint, position);
    FastVecScale(&segment, &segment, 0.5f);
    FastVecAdd(&midpoint, position, &segment);
    FastVecCross(&normal, &camera_delta, &segment);
    vec_scale_to_length(&normal, &normal, state->width0);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    vec_scale_to_length(&normal, &normal, state->width1);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
    COLORS(packet)[0] = COLORS(packet)[2];
    COLORS(packet)[1] = COLORS(packet)[3];
    COLORS(packet)[2] = COLORS(packet)[3] = state->color2;
    *(EffectVectorWord *)VERTEX(packet,0) = *(EffectVectorWord *)VERTEX(packet,2);
    *(EffectVectorWord *)VERTEX(packet,1) = *(EffectVectorWord *)VERTEX(packet,3);
    FastVecAdd(VERTEX(packet,2), VERTEX(packet,2), &segment);
    FastVecAdd(VERTEX(packet,3), VERTEX(packet,3), &segment);
    draw_world_quad(&packet, 0, 0);
    InitQuadPacketState(&packet.header, 14, 1, 0x80);
    color = state->color3 | ((u32)FloatToInt(life * 64.0f) << 24);
    COLORS(packet)[0] = COLORS(packet)[1] = COLORS(packet)[2] = COLORS(packet)[3] = color;
    UV(packet)[0] = 0.0f;
    UV(packet)[1] = 0.0f;
    UV(packet)[2] = 0.0f;
    UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f;
    UV(packet)[5] = 0.0f;
    UV(packet)[6] = 1.0f;
    UV(packet)[7] = 1.0f;
    COLORS(packet)[2] = COLORS(packet)[3] = state->color4;

    vec_scale_to_length(&normal, &normal, state->width2);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    FastVecAdd(&midpoint, position, &segment);
    FastVecAdd(&midpoint, &midpoint, &segment);
    vec_scale_to_length(&normal, &normal, state->width3);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
}
