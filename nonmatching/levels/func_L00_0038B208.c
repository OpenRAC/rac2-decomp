/* 2 November 2026:
 * Complete reconstruction of the weapon-trail renderer from the current retail body, replacing
 * an inspection-only note. Default game -O2 -G8 -ffunction-sections: 1252/1260 bytes, 0/27 US
 * placements; the retail 0x140 frame is recovered. Template stride is 0x60 and the draw packet
 * is 0x90 bytes. The selected-index palette, signed vertex/UV indices and signed alpha byte,
 * phase/clock/expiry tests, four-row state and both UV equations were independently checked.
 * Pointer bases initialized before the strip loop recover its spilled output pointers; indexed
 * and inner-scoped forms emitted 1264 and 1228 bytes. Remaining: hero-base rematerialization,
 * shape-selection branches and register/store scheduling. No full linked or native runtime
 * check; this remains nonmatching.
 */
#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
typedef union { TrailQuad q; float f[4]; } TrailVector;
typedef struct {
    short selected[4];
    u32 colors[4][4];
    float rate;
    TrailVector *vertices;
    short (*indices)[8];
    float (*uv)[2];
    short count;
    short unknown5a;
    float scroll;
} TrailTemplate;
typedef struct {
    TrailVector basis[3];
    TrailVector position;
    char unknown40[0x30];
    float phase;
    int unknown74;
    short kind;
} TrailState;
typedef struct {
    TrailVector position[4];
    u32 colors[4];
    float uv[4][2];
    u64 count, texture, tag, primitive;
} TrailPacket;

extern char D_00189E20[];
extern TrailTemplate D_L00_00290C78[];
extern int D_L00_001B19C8[] __attribute__((sda));
extern int D_L00_001B2740[] __attribute__((sda));
extern float D_L00_001AEFD8 __attribute__((sda));
extern u64 func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* Advance and draw the four-vertex strips for the current weapon trail. */
void func_L00_0038B208(char *object)
{
    TrailPacket packet;
    int selected[4];
    u32 baseColor;
    TrailState *state = *(TrailState **)(object + 0x68);
    TrailTemplate *shape;
    char *weapon;
    float alpha, scale;
    u32 *colorStart;
    float *uStart, *vStart;
    int texture, primitive, kind, shapeIndex, elapsed, frame, segment, vertex, remaining;

    if (state == 0 || state->phase == 0.0f)
        return;
    if (state->phase == 1.0f) {
        weapon = *(char **)(D_00189E20 + 0x2290);
        if ((u8)weapon[0x42] != (u8)weapon[0x43] || (u8)weapon[0x42] == 255) {
            state->phase = 0.0f;
            return;
        }
    }
    alpha = 1.0f;
    scale = 1.0f;
    texture = 20;
    primitive = 1;
    baseColor = 0x00808080;
    weapon = *(char **)(D_00189E20 + 0x2290);
    kind = (u8)weapon[0x42];
    if ((unsigned)(kind - 23) < 3 || kind == 43)
        kind = (u8)(*(char **)(D_00189E20 + 0x2290))[0x42];
    else
        kind = state->kind;
    if (kind == 23) {
        state->kind = 23;
        shapeIndex = 0;
    } else if (kind == 24) {
        state->kind = 24;
        shapeIndex = 1;
    } else if (kind == 25) {
        state->kind = 25;
        shapeIndex = 2;
    } else {
        state->kind = 43;
        shapeIndex = 3;
        baseColor = 0x00408080;
        alpha = 0.7f;
        scale = 1.25f;
        texture = 12;
        primitive = 2;
    }
    shape = &D_L00_00290C78[shapeIndex];
    selected[0] = shape->selected[0];
    selected[1] = shape->selected[1];
    selected[2] = shape->selected[2];
    selected[3] = shape->selected[3];
    if (state->phase == 1.0f) {
        weapon = *(char **)(D_00189E20 + 0x2290);
        qcopy(&state->basis[0], weapon + 0xC0);
        qcopy(&state->basis[1], weapon + 0xD0);
        qcopy(&state->basis[2], weapon + 0xE0);
        D_L00_001B2740[0] = D_L00_001B19C8[0];
    }
    frame = D_L00_001B19C8[0];
    elapsed = frame - D_L00_001B2740[0];
    if (elapsed <= 0)
        elapsed = 1;
    state->phase += (float)elapsed * shape->rate;
    D_L00_001B2740[0] = frame;
    if ((float)(shape->count * 2) <= state->phase) {
        kind = (u8)(*(char **)(D_00189E20 + 0x2290))[0x42];
        if ((unsigned)(kind - 23) >= 3 && kind != 43)
            state->phase = 0.0f;
        return;
    }
    packet.texture = func_0027C878(texture);
    packet.count = 5;
    packet.tag = 0xFF9000000260ULL;
    packet.primitive = ((u64)primitive << 2) | 0x8000000040ULL;
    qcopy(&state->position, *(char **)(D_00189E20 + 0x2290) + 0x10);
    colorStart = packet.colors;
    uStart = &packet.uv[0][0];
    vStart = &packet.uv[0][1];
    for (segment = 0; segment < shape->count; segment++) {
        TrailVector *point = packet.position;
        u32 *color = colorStart;
        float *u = uStart;
        float *v = vStart;
        for (vertex = 0, remaining = 3; remaining >= 0; vertex++, remaining--, point++, color++, u += 2, v += 2) {
            int index = shape->indices[segment][vertex * 2];
            float *uv;
            float phase;
            if (segment == selected[0])
                *color = shape->colors[0][vertex];
            else if (segment == selected[1])
                *color = shape->colors[1][vertex];
            else if (segment == selected[2])
                *color = shape->colors[2][vertex];
            else if (segment == selected[3])
                *color = shape->colors[3][vertex];
            else
                *color = 0x50808080;
            *color = ((u32)func_00283CF0((float)((s8 *)color)[3] * alpha) << 24) | baseColor;
            func_00282D30(point, &shape->vertices[index], scale);
            uv = shape->uv[shape->indices[segment][vertex * 2 + 1]];
            phase = 1.0f - state->phase * shape->scroll;
            *u = (uv[0] - 0.5f) * D_L00_001AEFD8 + 0.5f;
            *v = (uv[1] - 0.5f) * D_L00_001AEFD8 + 0.5f + phase;
        }
        func_00280B90(&packet, state, 0);
    }
}
