#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } DrawPacket;
extern int D_L26_001B0664[5] __attribute__((sda));
extern int D_L26_001B0678 __attribute__((sda));
extern unsigned int D_L26_001B0680[2] __attribute__((sda));
extern float D_L26_001B0688[4][2] __attribute__((sda));
extern float D_L26_001B068C[] MACRO_ADDR;
extern int D_L26_001B06A8 __attribute__((sda));
extern int D_L26_001B06AC[5];
extern Vector D_L26_0029ABD0[];
extern short D_L26_0029B3D0[][12];
extern unsigned long long GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern void draw_world_quad(void *, void *, int);

/* Builds a four-vertex draw packet with fixed GS state words and submits each of the 64 faces of
   the vertex/face tables twice, with UVs scrolled and colours blended from the object's private
   phase values (+0x0/+0x4 for the blend, +0x8/+0xC for the scroll). The state words are cleared and
   then accumulated field by field; `face` is scoped to the loop block. */
void DrawDoubleLayerQuadMesh(char *object) {
    DrawPacket packet;
    float *private = *(float **)(object + 0x68);
    float blend;
    int j;
    packet.state[1] = GetEffectTextureDescriptor(D_L26_001B0678);
    packet.state[2] = 0;
    packet.state[2] |= 0xFF9000000260ULL;
    packet.state[0] = 0;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06A8;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06AC[0] << 2;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06AC[1] << 4;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06AC[2] << 14;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06AC[3] << 24;
    packet.state[0] |= (unsigned long long)(long long)D_L26_001B06AC[4] << 34;
    packet.state[3] = 0;
    packet.state[3] |= (unsigned long long)(long long)D_L26_001B0664[0];
    packet.state[3] |= (unsigned long long)(long long)D_L26_001B0664[1] << 2;
    packet.state[3] |= (unsigned long long)(long long)D_L26_001B0664[2] << 4;
    packet.state[3] |= (unsigned long long)(long long)D_L26_001B0664[3] << 6;
    packet.state[3] |= (unsigned long long)(long long)D_L26_001B0664[4] << 32;
    {
        int face;

        for (face = 0; face < 64; face++) {
            for (j = 0; j < 4; j++) {
                qcopy(&packet.vertex[j], &D_L26_0029ABD0[D_L26_0029B3D0[face][j * 3]]);
                packet.uv[j][1] = D_L26_001B068C[j * 2];
            }
            for (j = 0; j < 4; j++) {
                int index;
                unsigned int *entry;
                index = FloatToInt(packet.uv[j][1] + 0.2f);
                packet.uv[j][0] = D_L26_001B0688[j][0] + private[2];
                blend = math_fast_sin_or_cos_b(private[0] * 3.1415927f);
                entry = &D_L26_001B0680[index];
                packet.color[j] = FastTweenColor(*entry & 0xFFFFFF, *entry, blend);
            }
            draw_world_quad(&packet, 0, 0);
            for (j = 0; j < 4; j++) {
                int index;
                unsigned int *entry;
                index = FloatToInt(packet.uv[j][1] + 0.2f);
                packet.uv[j][0] = D_L26_001B0688[j][0] + private[3];
                blend = math_fast_sin_or_cos_b(private[1] * 3.1415927f);
                entry = &D_L26_001B0680[index];
                packet.color[j] = FastTweenColor(*entry & 0xFFFFFF, *entry, blend);
            }
            draw_world_quad(&packet, 0, 0);
        }
    }
}
