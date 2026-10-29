/* Retained reconstruction, USA v1.01, game -O2 -G8 -ffunction-sections.
 * 624/612 bytes, 0/27 local places. This is the doubled radial / quarter
 * vertical-scale sibling of func_L00_003E5978, with the same64-quad mesh.
 * A complete64-byte affine row view and separate48+16-byte views tie.
 * Both retain the same object-pointer precomputation and spill mismatch as
 * that sibling. Its narrower loop-profile control already worsened, so it
 * is not repeated here. Packet0x90, indices1024 bytes; vector helpers audited.
 * No aliases, forced reloads or broad GCSE profile. No strict linked match.
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

void func_L00_003E5710(unsigned char *object)
{
    DrawPacket packet;
    float transform[4][4];
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
    func_00282C88(transform[0]);
    func_00282C88(transform[1]);
    func_00282C88(transform[2]);
    transform[0][0] = *(float *)(state + 0x10) * 2.0f;
    transform[1][1] = *(float *)(state + 0x10) * 2.0f;
    transform[2][2] = *(float *)(state + 0x10) * 0.25f;
    color = D_L00_001B05F8_gp + (*(u32 *)(state + 0x24) << 24);
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    func_002AFFD8(position, transform[3], 1);
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 4; j++) {
            int texture = D_L00_00297020[i][j].texture;
            func_00282D30(packet.vertices[j], D_L00_00296B20[D_L00_00297020[i][j].vertex],
                           D_L00_001B05FC_gp);
            packet.uv[j].u = D_L00_00297420[texture].u;
            packet.uv[j].v = D_L00_00297420[texture].v;
            func_00283098(packet.vertices[j], packet.vertices[j], transform);
            func_00283098(packet.vertices[j], packet.vertices[j], rotation);
            func_00282CC0(packet.vertices[j], packet.vertices[j], position);
            func_00282F20(transform[3], transform[3], 0.5f);
            func_00282CC0(packet.vertices[j], packet.vertices[j], transform[3]);
        }
        func_00280B90(&packet, 0, 0);
    }
}
