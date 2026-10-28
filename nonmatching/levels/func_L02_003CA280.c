/* Retained reconstruction, USA v1.01, game -O2 -G8 -ffunction-sections
 * -frac2-qcopy -frac2-zero-ti-por. 548/548 bytes, 0/2 local places.
 * The 0x90 sprite packet, 64-byte matrix and two real 16-byte angle buffers
 * account for the stack objects. GP/absolute UV views share one 32-byte table.
 * The angle load hoists before the initial zero, and object/matrix register
 * allocation differs. A zero-store barrier moves the clear below the saves;
 * a pointer advance and declaration initializer do not close the mismatch.
 * Reopen with concrete angle/zero liveness evidence, not forced access ordering.
 * No strict linked match.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { float u, v; } TextureCoordinate;
typedef struct {
    Vector vertices[4];
    u32 colors[4];
    TextureCoordinate uv[4];
    u64 primitive, texture, tag, blend;
} SpritePacket;
typedef char PacketExtent[sizeof(SpritePacket) == 0x90 ? 1 : -1];
extern float D_L02_001BA518 NOT_SDA;
extern float D_L02_001B006C_gp SDATA(D_L02_001B006C);
extern float D_L02_001B0070_gp SDATA(D_L02_001B0070);
extern u32 D_L02_001B0060_gp SDATA(D_L02_001B0060);
extern u32 D_L02_001B0064 NOT_SDA;
extern u32 D_L02_001B0068 NOT_SDA;
/* One UV table has two measured address views; its full four-pair extent
 * is independent of the assembler's small-address metadata. */
extern TextureCoordinate D_L02_001AFFF8[4];
extern TextureCoordinate D_L02_001AFFF8_gp[4] SDATA(D_L02_001AFFF8);
extern Vector D_L02_001B0020_gp[4] SDATA(D_L02_001B0020);
extern int D_L02_001AFFE8_gp SDATA(D_L02_001AFFE8);
extern int D_L02_001AFFEC_gp SDATA(D_L02_001AFFEC);
extern int D_L02_001AFFF0_gp SDATA(D_L02_001AFFF0);
extern void func_00283410(void *, void *);
extern void func_00282D30(void *, void *, float);
extern u32 func_00283D38(u32, u32, float);
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int);

void func_L02_003CA280(unsigned char *object)
{
    SpritePacket packet;
    float transform[4][4];
    Vector angle_argument;
    Vector angles = {0};
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float radial, height, phase;
    u32 color;
    int i;
    angles.f[2] = D_L02_001BA518;
    angle_argument.q = angles.q;
    func_00283410(transform, &angle_argument);
    phase = *(float *)(state + 8);
    height = (1.0f - phase) * D_L02_001B006C_gp;
    height += 1.0f;
    radial = *(float *)(state + 0xC) * D_L02_001B0070_gp;
    phase += radial;
    height += radial;
    func_00282D30(transform[0], transform[0], phase);
    func_00282D30(transform[1], transform[1], phase);
    func_00282D30(transform[2], transform[2], height);
    object += 0x10;
    qcopy(transform[3], object);
    transform[3][2] -= (*(float *)(state + 0xC) * D_L02_001B0070_gp) * 0.5f;
    transform[3][3] = 1.0f;
    if (*(float *)(state + 8) < 1.0f)
        color = func_00283D38(D_L02_001B0060_gp, D_L02_001B0064, *(float *)(state + 8));
    else
        color = func_00283D38(D_L02_001B0064, D_L02_001B0068, *(float *)(state + 0xC));
    for (i = 0; i < 4; i++) {
        float u = D_L02_001AFFF8_gp[i].u;
        float v = D_L02_001AFFF8[i].v;
        packet.colors[i] = color;
        packet.uv[i].u = u;
        packet.uv[i].v = v;
        qcopy(&packet.vertices[i], &D_L02_001B0020_gp[i]);
    }
    packet.texture = func_0027C878(D_L02_001AFFE8_gp);
    packet.tag = 0xFF9000000260ULL;
    packet.primitive = 5;
    packet.blend = ((u64)D_L02_001AFFEC_gp << 2) |
                   ((u64)D_L02_001AFFF0_gp << 6) | 0x8000000000ULL;
    func_00280B90(&packet, transform, 1);
    func_00280B90(&packet, transform, 1);
}
