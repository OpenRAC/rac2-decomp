/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Claude Opus 5.5 (xhigh), v1688, 2026-10-31: 980/972 bytes, 0/1 places in USA v1.01, v2.00 and PAL.
 * Profile: -O2 -G0 -ffunction-sections. Not linked. Declarations it needs are included below.
 * Blocker: retail's 192-byte copy is not reachable from C with this compiler. Retail has
 * lq a1,0(v0); lq a2,0x10(v0); sq a1,0(v1); sq a2,0x10(v1); addiu v0; bne v0,a0; addiu v1 with no
 * alignment pad before its label. That is the shape of a block move: src v0, dst v1, end a0 are what
 * this compiler allocates for a struct copy, and a1/a2 are its reload scratch registers. A struct
 * copy here emits only ld/sd (four scratches per 32 bytes), also with aligned(16) or TI members.
 * The explicit pair loop below differs three ways: local-alloc gives its temps v0/v1 before global
 * allocates the pointers, its LOOP_BEG note adds .p2align 3 (the extra nop), and the second sq moves
 * past the addiu. func_00288870 and func_002DE990 hold the same loop; no matched C reproduces it.
 * Fixed here: state loads in the flip branch's delay slot, the packet setup order, and the
 * mul.s/add.s form of the first edge (first += piece * width). 53 instructions differ after
 * alignment, 63 in the previous draft.
 * Still different outside the copy: mode/primitive swap a0/a1 and band follows into a1; phase takes
 * stack slot 0x160 where retail has 0x168 (retail order: stride 0x160, next band 0x164, phase 0x168,
 * so phase behaves like a pseudo numbered above the loop pass's next band); the band head schedules
 * 0x24 and stride differently; retail builds both table addresses in a1/a2 before the add.s.
 * Reopen when the compiler's block move can emit lq/sq for 16-byte-aligned copies, then recheck the
 * allocation from a plain struct assignment of StripGeometry.
 */
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
extern int D_L02_001B0A00[];
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, void *, int);

void func_L02_003E7B58(char *actor) {
    StripGeometry geometry;
    Quad *dst = (Quad *)&geometry;
    Quad *src = (Quad *)&D_L02_002A52F0;
    StripPacket packet;
    float sample[4] __attribute__((aligned(16)));
    char *state;
    float *phase;
    float flip;
    int band, piece;
    do {
        Quad first = src[0], second = src[1];
        dst[0] = first;
        dst[1] = second;
        src += 2;
        dst += 2;
    } while (src != (Quad *)(&D_L02_002A52F0 + 1));
    flip = 0.0f;
    state = *(char **)(actor + 0x68);
    if (*(unsigned short *)(actor + 0x34) & 0x8000) flip = 1.0f;
    packet.mode = 0xFF9000000260ULL;
    packet.tex0[0] = flip;
    packet.tex0[1] = 0.0f;
    packet.tex0[2] = 1.0f - flip;
    packet.tex0[3] = 0.0f;
    packet.tex1[0] = flip;
    packet.tex1[1] = 1.0f;
    packet.tex1[2] = 1.0f - flip;
    packet.tex1[3] = 1.0f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = 0x7F7F7F7F;
    phase = (float *)(state + 0x60);
    packet.primitive = 5;
    packet.flags = 0x8000000000ULL;
    for (band = 0; band < 3; band++) {
        float scroll = phase[band] + 0.15f;
        for (piece = 0; piece < 3; piece++) {
            float first = ((float)func_00283CF0(scroll) - scroll) * 0.43094158f;
            int tile;
            float last;
            float texFirst;
            float texLast;
            first += (float)piece * 0.43094158f;
            tile = func_00283CF0((scroll + (float)piece - 1.0f) + 9.0f) % 9;
            last = first + 0.43094158f;
            packet.texture = func_0027C878(D_L02_001B0A00[D_L02_002A53B0[band][tile]]);
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
