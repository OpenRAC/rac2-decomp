/* Retained reconstruction, USA v1.01, game -O2 -G8 -ffunction-sections.
 * 616/604 bytes, 0/27 local places. The packet is 0x90 bytes, scale basis
 * 48 bytes, offset vector16 bytes, and the measured index table64*4*4 bytes.
 * VU helper00283098 reads exactly three matrix rows and one full vector.
 * Object position/rotation pointers hoist before the texture call and spill
 * in a different order; output/UV pointer allocation also differs. Mutating
 * the position pointer ties. -fno-rerun-loop-opt worsens to624 bytes.
 * Reopen with actual object-pointer/loop-preheader lifetime evidence.
 * No broad GCSE flag, alias barrier or volatile ordering was introduced.
 * No strict linked match.
 */
#include "common.h"

typedef struct { s16 vertex, texture; } QuadIndex;
typedef struct { float u, v; } UV;
typedef struct {
    float vertices[4][4];
    u32 colors[4];
    UV uv[4];
    u64 primitive, texture, tag, blend;
} DrawPacket;
typedef char PacketExtent[sizeof(DrawPacket) == 0x90 ? 1 : -1];
extern QuadIndex D_L00_00297020[64][4];
extern float D_L00_00296B20[][4];
extern UV D_L00_00297420[];
extern int D_L00_001B05E0_gp SDATA(D_L00_001B05E0);
extern int D_L00_001B05E4_gp SDATA(D_L00_001B05E4);
extern int D_L00_001B05E8_gp SDATA(D_L00_001B05E8);
extern int D_L00_001B05EC_gp SDATA(D_L00_001B05EC);
extern int D_L00_001B05F0_gp SDATA(D_L00_001B05F0);
extern int D_L00_001B05F4_gp SDATA(D_L00_001B05F4);
extern u32 D_L00_001B05F8_gp SDATA(D_L00_001B05F8);
extern float D_L00_001B05FC_gp SDATA(D_L00_001B05FC);
extern u64 func_0027C878(int);
extern void func_00282C88(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L00_003E5978(unsigned char *object)
{
    DrawPacket packet;
    float scale[3][4];
    float offset[4];
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float *rotation = (float *)(object + 0xC0);
    float *position;
    u64 blend;
    u32 color;
    int i, j;
    packet.texture = func_0027C878(D_L00_001B05F4_gp);
    object += 0x10;
    position = (float *)object;
    blend = (u64)D_L00_001B05E0_gp;
    blend |= (u64)D_L00_001B05E4_gp << 2;
    blend |= (u64)D_L00_001B05E8_gp << 4;
    blend |= (u64)D_L00_001B05EC_gp << 6;
    blend |= (u64)D_L00_001B05F0_gp << 32;
    packet.tag = 0xFF9000000260ULL;
    packet.blend = blend;
    packet.primitive = 0;
    func_00282C88(scale[0]);
    func_00282C88(scale[1]);
    func_00282C88(scale[2]);
    scale[0][0] = *(float *)(state + 0x10);
    scale[1][1] = *(float *)(state + 0x10);
    scale[2][2] = *(float *)(state + 0x10) * 0.125f;
    color = D_L00_001B05F8_gp + (*(u32 *)(state + 0x24) << 24);
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    func_002AFFD8(position, offset, 1);
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 4; j++) {
            int texture = D_L00_00297020[i][j].texture;
            func_00282D30(packet.vertices[j], D_L00_00296B20[D_L00_00297020[i][j].vertex],
                           D_L00_001B05FC_gp);
            packet.uv[j].u = D_L00_00297420[texture].u;
            packet.uv[j].v = D_L00_00297420[texture].v;
            func_00283098(packet.vertices[j], packet.vertices[j], scale);
            func_00283098(packet.vertices[j], packet.vertices[j], rotation);
            func_00282CC0(packet.vertices[j], packet.vertices[j], position);
            func_00282F20(offset, offset, 0.5f);
            func_00282CC0(packet.vertices[j], packet.vertices[j], offset);
        }
        func_00280B90(&packet, 0, 0);
    }
}
