#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
struct QuadPacket {
    TI128 vertices[4];
    int colors[4];
    f32 uv[4][2];
    long state70, state78, state80, state88;
};
extern void func_00281DE8(struct QuadPacket *, int, int, int);
void func_L02_002EF968(struct QuadPacket *packet, int texture, int color, f32 (*uv)[2], TI128 *vertices, int flags) {
    int i;
    InitQuadPacketState(packet, texture, flags, 128);
    for (i = 0; i < 4; i++) {
        packet->uv[i][0] = uv[i][0];
        packet->uv[i][1] = uv[i][1];
        packet->colors[i] = color;
        qcopy(&packet->vertices[i], &vertices[i]);
    }
}
