/* func_L02_003E7B58: -G8 so D_L02_001B0A00 (a small-data table) is a MACRO_ADDR la; the
 * assembler gives it the lui/addiu pair retail rematerialises in the texture loop. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float point[3][4][4]; } StripGeometry __attribute__((aligned(16)));
typedef struct {
    float corner[4][4];
    unsigned int color[4];
    float tex0[4];
    float tex1[4];
    unsigned long long primitive, texture, mode, flags;
} StripPacket __attribute__((aligned(16)));
extern StripGeometry D_L02_002A52F0;
extern int D_L02_002A53B0[3][9];
extern int D_L02_001B0A00[] MACRO_ADDR;
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, void *, int);

void func_L02_003E7B58(char *actor) {
    StripGeometry geometry;
    StripPacket packet;
    char *state;
    float flip;
    float sample[4] __attribute__((aligned(16)));
    int band, piece;
    geometry = D_L02_002A52F0;
    state = *(char **)(actor + 0x68);
    flip = 0.0f;
    if (*(unsigned short *)(actor + 0x34) & 0x8000) flip = 1.0f;
    packet.tex0[0] = flip;
    packet.tex0[1] = 0.0f;
    packet.tex0[2] = 1.0f - flip;
    packet.tex0[3] = 0.0f;
    packet.tex1[2] = 1.0f - flip;
    packet.tex1[1] = 1.0f;
    packet.tex1[0] = flip;
    packet.tex1[3] = 1.0f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F7F7F7F;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 5;
    packet.flags = 0x8000000000ULL;
    for (band = 0; band < 3; band++) {
        int off = band * 4;
        float *phase = (float *)(state + 0x60);
        float scroll = *(float *)((char *)phase + off) + 0.15f;
        for (piece = 0; piece < 3; piece++) {
            float first = ((float)func_00283CF0(scroll) - scroll) * 0.43094158f;
            int tile;
            float last;
            float texFirst;
            float texLast;
            first += (float)piece * 0.43094158f;
            tile = func_00283CF0((scroll + (float)piece - 1.0f) + 9.0f) % 9;
            last = first + 0.43094158f;
            {
                int idx = D_L02_002A53B0[band][tile];
                packet.texture = func_0027C878(D_L02_001B0A00[idx]);
            }
            texFirst = 0.0f;
            texLast = 1.0f;
            if (last < 0.1f || first > 0.9f) continue;
            if (first < 0.1f) {
                texFirst = (0.1f - first) * 2.3205001f;
                first = 0.1f;
            } else if (last > 0.9f) {
                texLast = (0.9f - last) * 2.3205001f + texLast;
                last = 0.9f;
            }
            packet.tex0[1] = packet.tex0[3] = texFirst;
            packet.tex1[1] = packet.tex1[3] = texLast;
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], first);
            func_L01_0031A278(actor, packet.corner[0], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], first);
            func_L01_0031A278(actor, packet.corner[1], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][0], geometry.point[band][2], last);
            func_L01_0031A278(actor, packet.corner[2], sample[0], sample[1], sample[2]);
            func_00282D08(sample, geometry.point[band][1], geometry.point[band][3], last);
            func_L01_0031A278(actor, packet.corner[3], sample[0], sample[1], sample[2]);
            func_00280B90(&packet, 0, 0);
        }
    }
}
