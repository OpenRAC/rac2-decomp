#include "common.h"

typedef struct { float u, v; } UV;
typedef struct {
    float vertices[4][4];
    u32 colors[4];
    UV uv[4];
    u64 primitive, texture, tag, blend;
} OverlayPacket;
typedef char PacketExtent[sizeof(OverlayPacket) == 0x90 ? 1 : -1];
extern float g_camera_l09_position[];
/* This consumer reads four complete rows; the external owner extent stays open. */
extern float D_L09_001B1240_gp[][4] SDATA(D_L09_001B1240);
extern u64 GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(unsigned int, u64);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

/* Draws a glowing flat marker on the ground at the object's target spot, plus a flash when it was just hit. */
void target_marker_draw(unsigned char *object)
{
    float position[4];
    OverlayPacket packet;
    float direction[4], adjusted[4];
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float distance, radius, remaining;
    int i;
    qcopy(position, state + 0x330);
    position[2] += 0.01f;
    position[3] = 1.0f;
    packet.texture = GetEffectTextureDescriptor(11);
    packet.tag = 0xFF9000000260ULL;
    packet.blend = 0x8000000048ULL;
    packet.primitive = 0;
    VU1_addGSregister(0x4A, 0);
    VU1_addGSregister(0x47, 0x51001);
    FastVecSub(direction, g_camera_l09_position, position);
    distance = FastVecLength(direction);
    if (distance > 0.0f) {
        radius = *(float *)(state + 0x438);
        remaining = distance - 2.0f;
        if (remaining < radius) {
            radius = remaining;
            if (radius < 0.0f)
                radius = 0.0f;
        }
        vec_scale_to_length(adjusted, direction, radius);
        FastVecAdd(position, position, adjusted);
    }
    packet.uv[0].u = 1.0f;
    packet.uv[0].v = 1.0f;
    packet.uv[1].u = 0.0f;
    packet.uv[1].v = 1.0f;
    packet.uv[2].u = 1.0f;
    packet.uv[2].v = 0.0f;
    packet.uv[3].u = 0.0f;
    packet.uv[3].v = 0.0f;
    if (*(s16 *)(state + 0x422) != 0) {
        packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = 0x7F40407F;
    } else {
        packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = 0x40507F7F;
    }
    for (i = 0; i < 4; i++) {
        FastVecScale(packet.vertices[i], D_L09_001B1240_gp[i], *(float *)(state + 0x434));
        FastVecAdd(packet.vertices[i], packet.vertices[i], position);
    }
    draw_world_quad(&packet, 0, 0);
    if (state[0x42B] != 0) {
        packet.texture = GetEffectTextureDescriptor(32);
        for (i = 0; i < 4; i++) {
            FastVecScale(packet.vertices[i], D_L09_001B1240_gp[i], 1.0f);
            FastVecAdd(packet.vertices[i], packet.vertices[i], position);
        }
        draw_world_quad(&packet, 0, 0);
        state[0x42B] = 0;
    }
}
