#include "common.h"

/* Advances a trail object's phase and draws its four-vertex strips. The template, state and packet
 * layouts are measured from this function; the four selected rows stay in separate locals because
 * retail spills each one on its own, and the hero's moby is read through the cast on every use. */
extern int g_frame_l00_counter;
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float);
typedef int TrailQuad __attribute__((mode(TI)));
typedef union { TrailQuad q; float f[4]; } TrailVector;
typedef struct {
    short selected[4];
    int colors[4][4];
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
    int colors[4];
    float uv[4][2];
    u64 count, texture, tag, primitive;
} TrailPacket;
typedef struct { char pad[0x2290]; u8 *moby; } TrailHero;

extern TrailHero g_hero_state;
extern TrailTemplate g_trail_template_table[];
extern int g_last_frame_stamp;
extern float g_shape_uv_scale __attribute__((sda));
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);

/* Advance and draw the four-vertex strips for the current weapon trail. */
void UpdateTrailStrips(char *object)
{
    TrailPacket packet;
    int selected0, selected1, selected2, selected3;
    int baseColor;
    TrailState *state = *(TrailState **)(object + 0x68);
    TrailTemplate *shape;
    float alpha, scale, phase, advanced;
    int texture, primitive, kind, shapeIndex, elapsed, frame, segment, vertex;

    if (state == 0 || state->phase == 0.0f)
        return;
    if (state->phase == 1.0f) {
        if (g_hero_state.moby[0x42] != g_hero_state.moby[0x43] || g_hero_state.moby[0x42] == 255) {
            state->phase = 0.0f;
            return;
        }
    }
    scale = 1.0f;
    texture = 20;
    primitive = 1;
    baseColor = 0x00808080;
    alpha = 1.0f;
    kind = g_hero_state.moby[0x42];
    if ((unsigned)(kind - 23) >= 3 && kind != 43)
        kind = state->kind;
    else
        kind = g_hero_state.moby[0x42];
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
        alpha = 0.7f;
        scale = 1.25f;
        texture = 12;
        baseColor = 0x00408080;
        primitive = 2;
    }
    phase = state->phase;
    shape = &g_trail_template_table[shapeIndex];
    selected0 = shape->selected[0];
    selected1 = shape->selected[1];
    selected2 = shape->selected[2];
    selected3 = shape->selected[3];
    if (phase == 1.0f) {
        u8 *moby = g_hero_state.moby;
        qcopy(&state->basis[0], moby + 0xC0);
        qcopy(&state->basis[1], moby + 0xD0);
        qcopy(&state->basis[2], moby + 0xE0);
        g_last_frame_stamp = g_frame_l00_counter;
    }
    frame = g_frame_l00_counter;
    elapsed = frame - g_last_frame_stamp;
    if (elapsed <= 0)
        elapsed = 1;
    advanced = phase + (float)elapsed * shape->rate;
    state->phase = advanced;
    g_last_frame_stamp = frame;
    if ((float)(shape->count * 2) <= advanced) {
        int current = g_hero_state.moby[0x42];
        if ((unsigned)(current - 23) >= 3 && current != 43)
            state->phase = 0.0f;
        return;
    }
    packet.texture = GetEffectTextureDescriptor(texture);
    packet.tag = 0xFF9000000260ULL;
    packet.count = 5;
    packet.primitive = ((u64)primitive << 2) | 0x8000000040ULL;
    qcopy(&state->position, g_hero_state.moby + 0x10);
    for (segment = 0; segment < shape->count; segment++) {
        for (vertex = 0; vertex < 4; vertex++) {
            int index = shape->indices[segment][vertex * 2];
            int uvIndex;
            float scroll;
            if (segment == selected0)
                packet.colors[vertex] = shape->colors[0][vertex];
            else if (segment == selected1)
                packet.colors[vertex] = shape->colors[1][vertex];
            else if (segment == selected2)
                packet.colors[vertex] = shape->colors[2][vertex];
            else if (segment == selected3)
                packet.colors[vertex] = shape->colors[3][vertex];
            else
                packet.colors[vertex] = 0x50808080;
            packet.colors[vertex] = (FloatToInt((float)(packet.colors[vertex] >> 24) * alpha) << 24) | baseColor;
            FastVecScale(&packet.position[vertex], &shape->vertices[index], scale);
            uvIndex = shape->indices[segment][vertex * 2 + 1];
            scroll = 1.0f - state->phase * shape->scroll;
            packet.uv[vertex][0] = (shape->uv[uvIndex][0] - 0.5f) * g_shape_uv_scale + 0.5f;
            packet.uv[vertex][1] = (shape->uv[uvIndex][1] - 0.5f) * g_shape_uv_scale + 0.5f + scroll;
        }
        draw_world_quad(&packet, state, 0);
    }
}
