#include "common.h"

typedef struct { float u, v; } UV;
typedef struct {
    float vertices[4][4];
    u32 colors[4];
    UV uv[4];
    u64 primitive, texture, tag, blend;
} OverlayPacket;
typedef char PacketExtent[sizeof(OverlayPacket) == 0x90 ? 1 : -1];
extern float D_L09_001B9A00[];
/* This consumer reads four complete rows; the external owner extent stays open. */
extern float D_L09_001B1240_gp[][4] SDATA(D_L09_001B1240);
extern u64 func_0027C878(int);
extern void func_002FC560(unsigned int, u64);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L09_003FD7D0(unsigned char *object)
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
    packet.texture = func_0027C878(11);
    packet.tag = 0xFF9000000260ULL;
    packet.blend = 0x8000000048ULL;
    packet.primitive = 0;
    func_002FC560(0x4A, 0);
    func_002FC560(0x47, 0x51001);
    func_00282CF0(direction, D_L09_001B9A00, position);
    distance = func_00282DF0(direction);
    if (distance > 0.0f) {
        radius = *(float *)(state + 0x438);
        remaining = distance - 2.0f;
        if (remaining < radius) {
            radius = remaining;
            if (radius < 0.0f)
                radius = 0.0f;
        }
        func_00282F20(adjusted, direction, radius);
        func_00282CC0(position, position, adjusted);
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
        func_00282D30(packet.vertices[i], D_L09_001B1240_gp[i], *(float *)(state + 0x434));
        func_00282CC0(packet.vertices[i], packet.vertices[i], position);
    }
    func_00280B90(&packet, 0, 0);
    if (state[0x42B] != 0) {
        packet.texture = func_0027C878(32);
        for (i = 0; i < 4; i++) {
            func_00282D30(packet.vertices[i], D_L09_001B1240_gp[i], 1.0f);
            func_00282CC0(packet.vertices[i], packet.vertices[i], position);
        }
        func_00280B90(&packet, 0, 0);
        state[0x42B] = 0;
    }
}
