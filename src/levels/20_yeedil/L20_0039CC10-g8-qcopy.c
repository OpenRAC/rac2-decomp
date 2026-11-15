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
extern void func_00281DE8(QuadPacket *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, void *, int);
extern char D_L20_001B9FC0[];

typedef struct {
    u8 pad[0x10];
    EffectVector axis;
    u8 pad20[8];
    float scroll;
} RibbonState;

void func_L20_0039CC10(char *object) {
    EffectPacket packet;
    EffectVector camera_delta;
    EffectVector segment;
    EffectVector midpoint;
    EffectVector normal;
    RibbonState *state = *(RibbonState **)(object + 0x68);
    char *position;
    int i;

    func_00281DE8(&packet.header, 23, 0, 0x80);
    COLORS(packet)[0] = COLORS(packet)[1] = 0x40108080;
    COLORS(packet)[2] = COLORS(packet)[3] = 0x40101080;
    UV(packet)[0] = 0.0f; UV(packet)[1] = 0.0f; UV(packet)[2] = 0.0f; UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f; UV(packet)[5] = 0.0f; UV(packet)[6] = 1.0f; UV(packet)[7] = 1.0f;
    for (i = 0; i < 4; i++) {
        UV(packet)[i * 2] -= state->scroll;
        if (UV(packet)[i * 2] <= 7.0f) UV(packet)[i * 2] += 7.0f;
    }
    state->scroll += 0.1f;
    if (state->scroll >= 4.0f) state->scroll -= 4.0f;
    position = object + 0x10;
    FastVecSub(&camera_delta, position, D_L20_001B9FC0);
    vec_scale_to_length(&segment, &state->axis, -2.0f);
    FastVecAdd(&midpoint, position, &segment);
    FastVecCross(&normal, &camera_delta, &segment);
    vec_scale_to_length(&normal, &normal, 0.1f);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
    COLORS(packet)[0] = COLORS(packet)[2];
    COLORS(packet)[1] = COLORS(packet)[3];
    COLORS(packet)[2] = COLORS(packet)[3] = 0x00801010;
    *(EffectVectorWord *)VERTEX(packet,0) = *(EffectVectorWord *)VERTEX(packet,2);
    *(EffectVectorWord *)VERTEX(packet,1) = *(EffectVectorWord *)VERTEX(packet,3);
    FastVecAdd(VERTEX(packet,2), VERTEX(packet,2), &segment);
    FastVecAdd(VERTEX(packet,3), VERTEX(packet,3), &segment);
    draw_world_quad(&packet, 0, 0);
    func_00281DE8(&packet.header, 14, 1, 0x80);
    COLORS(packet)[0] = COLORS(packet)[1] = 0x40FF0020;
    UV(packet)[0] = 0.0f;
    UV(packet)[1] = 0.0f;
    UV(packet)[2] = 0.0f;
    UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f;
    UV(packet)[5] = 0.0f;
    UV(packet)[6] = 1.0f;
    UV(packet)[7] = 1.0f;
    COLORS(packet)[2] = COLORS(packet)[3] = 0x00FF0020;

    vec_scale_to_length(&normal, &normal, 0.6f);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    FastVecAdd(&midpoint, position, &segment);
    FastVecAdd(&midpoint, &midpoint, &segment);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
}
