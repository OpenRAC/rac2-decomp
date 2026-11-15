#include "common.h"

/* func_L13_0041FBE0 (-G64, split addresses, -g, -fno-cse-skip-blocks).
   The color table D_L13_001B1A90 and texture pair D_L13_001B1A40 are read
   through $gp at element 0 and as absolute sym+offset macro loads after it:
   the _1 views have no declared size, so the assembler keeps them absolute
   and cc1 neither splits their %hi nor puts them in delay slots. */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } DrawPacket;
extern float D_L13_001B98C0[];
extern unsigned int D_L13_001B1A90 __attribute__((sda));
extern unsigned int D_L13_001B1A90_1[] __attribute__((sda));
extern int D_L13_001B1A40 __attribute__((sda));
extern int D_L13_001B1A40_1[] __attribute__((sda));
extern float D_L13_001B1A50[4][2] __attribute__((sda));
extern float D_L13_001B1A70[4][2] __attribute__((sda));
extern Vector D_L13_001B1AB0[4] __attribute__((sda));
extern Vector D_L13_001B1AF0[4] __attribute__((sda));
extern Vector D_L13_001B1B30[4] __attribute__((sda));
extern float D_L13_001B1BB0 __attribute__((sda));
extern float D_L13_001B1BB4 __attribute__((sda));
extern float D_L13_001B1BB8 __attribute__((sda));
extern int D_L13_001B1BBC __attribute__((sda));
extern int D_L13_001B1BC0 __attribute__((sda));
extern void func_00283658(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern void func_00282D30(void *, void *, float);
extern float func_00283198(float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_L02_002EF968(void *, int, unsigned int, void *, void *, int);
extern void *func_00115484(void *, int, unsigned int);
extern void func_002833F0(void *, void *);
extern void func_L01_002E1510(void *, int, void *, int, void *);
extern void func_00282CC0(void *, void *, void *);

/* Draws a pulsing glowing strip made of layered quads whose edges fade out. */
void func_L13_0041FBE0(char *object) {
    float transform[16];
    Vector direction;
    DrawPacket packet[7];
    unsigned int edge[2];
    Vector rotation;
    Vector setup;
    Vector setup_source;
    Vector subtract_offsets[2];
    Vector offsets[2];
    float rotation_matrix[12];
    char *private = *(char **)(object + 0x68);
    unsigned int main_color;
    unsigned int trim_color;
    float one;
    float amount;
    float fade_a;
    float fade_b;
    int i;
    int corner;
    copy_matrix_rotation(transform, object + 0xC0);
    qcopy(transform + 12, object + 0x10);
    one = 1.0f;
    transform[15] = one;
    vec_scale_to_length(transform, transform, 4.0f);
    vec_scale_to_length(transform + 4, transform + 4, 10.0f);
    FastVecSub(&direction, D_L13_001B98C0, object + 0x10);
    TransformVectorByObjectOrGiven(object, (char *)&direction, (char *)&direction, 0);
    if (direction.f[0] < 0.0f) FastVecScale(transform, transform, -1.0f);
    amount = FastSinOrCosB(*(float *)(private + 0x20)) * 0.5f + 0.5f;
    main_color = FastTweenColor(D_L13_001B1A90, D_L13_001B1A90_1[1], amount);
    trim_color = FastTweenColor(D_L13_001B1A90_1[2], D_L13_001B1A90_1[3], amount);
    fade_a = *(float *)(private + 4);
    if (!(0.2f <= fade_a)) fade_a = one - fade_a * 5.0f;
    edge[0] = FastTweenColor(D_L13_001B1A90_1[3], D_L13_001B1A90_1[3] & 0xFFFFFF, fade_a);
    fade_b = *(float *)(private + 8);
    if (!(0.2f <= fade_b)) fade_b = 1.0f - fade_b * 5.0f;
    edge[1] = FastTweenColor(D_L13_001B1A90_1[3], D_L13_001B1A90_1[3] & 0xFFFFFF, fade_b);
    if (*(float *)private < 1.0f) {
        main_color = FastTweenColor(main_color & 0xFFFFFF, main_color, *(float *)private);
        trim_color = FastTweenColor(trim_color & 0xFFFFFF, trim_color, *(float *)private);
        edge[0] = FastTweenColor(edge[0] & 0xFFFFFF, edge[0], *(float *)private);
        edge[1] = FastTweenColor(edge[1] & 0xFFFFFF, edge[1], *(float *)private);
    }
    FillQuadPacket(packet, D_L13_001B1A40, main_color, D_L13_001B1A50, D_L13_001B1AB0, 1);
    FillQuadPacket(packet + 1, D_L13_001B1A40_1[1], trim_color, D_L13_001B1A70, D_L13_001B1AF0, 1);
    FillQuadPacket(packet + 2, D_L13_001B1A40_1[1], trim_color, D_L13_001B1A70, D_L13_001B1B30, 1);
    FillQuadPacket(packet + 3, D_L13_001B1A40_1[1], edge[0], D_L13_001B1A70, D_L13_001B1AF0, 1);
    FillQuadPacket(packet + 4, D_L13_001B1A40_1[1], edge[0], D_L13_001B1A70, D_L13_001B1B30, 1);
    FillQuadPacket(packet + 5, D_L13_001B1A40_1[1], edge[1], D_L13_001B1A70, D_L13_001B1AF0, 1);
    FillQuadPacket(packet + 6, D_L13_001B1A40_1[1], edge[1], D_L13_001B1A70, D_L13_001B1B30, 1);
    for (corner = 0; corner < 4; corner++) {
        packet[1].uv[corner][0] += *(float *)(private + 0xC);
        packet[2].uv[corner][0] -= *(float *)(private + 0xC);
        packet[3].uv[corner][0] += *(float *)(private + 0xC);
        packet[4].uv[corner][0] -= *(float *)(private + 0xC);
        packet[5].uv[corner][0] += *(float *)(private + 0xC);
        packet[6].uv[corner][0] -= *(float *)(private + 0xC);
        packet[3].vertex[corner].f[2] -= *(float *)(private + 4) * D_L13_001B1BB4;
        packet[4].vertex[corner].f[2] += *(float *)(private + 4) * D_L13_001B1BB4;
        packet[5].vertex[corner].f[2] -= *(float *)(private + 8) * D_L13_001B1BB4;
        packet[6].vertex[corner].f[2] += *(float *)(private + 8) * D_L13_001B1BB4;
    }
    setup.quad = 0;
    setup.f[2] = -3.1415927f / D_L13_001B1BB8;
    setup_source.quad = 0;
    setup_source.f[2] = D_L13_001B1BB0;
    rotation.quad = setup.quad;
    setup.quad = setup_source.quad;
    memset(offsets, 0, 32);
    offsets[0].f[2] = *(float *)(private + 4) * D_L13_001B1BB4;
    offsets[1].f[2] = *(float *)(private + 8) * D_L13_001B1BB4;
    subtract_offsets[0].quad = offsets[0].quad;
    subtract_offsets[1].quad = offsets[1].quad;
    euler_rotation_basis(rotation_matrix, &rotation);
    TransformAndDrawEntries(packet, D_L13_001B1BBC, rotation_matrix, D_L13_001B1BC0, transform);
    for (i = 0; i < 4; i++) {
        FastVecAdd(packet[0].vertex + i, D_L13_001B1AB0 + i, &setup);
        FastVecAdd(packet[1].vertex + i, D_L13_001B1AF0 + i, &setup);
        FastVecAdd(packet[2].vertex + i, D_L13_001B1B30 + i, &setup);
        FastVecAdd(packet[3].vertex + i, D_L13_001B1AF0 + i, &setup);
        FastVecAdd(packet[4].vertex + i, D_L13_001B1B30 + i, &setup);
        FastVecAdd(packet[5].vertex + i, D_L13_001B1AF0 + i, &setup);
        FastVecAdd(packet[6].vertex + i, D_L13_001B1B30 + i, &setup);
        FastVecSub(packet[3].vertex + i, packet[3].vertex + i, subtract_offsets);
        FastVecAdd(packet[4].vertex + i, packet[4].vertex + i, subtract_offsets);
        FastVecSub(packet[5].vertex + i, packet[5].vertex + i, subtract_offsets + 1);
        FastVecAdd(packet[6].vertex + i, packet[6].vertex + i, subtract_offsets + 1);
    }
    euler_rotation_basis(rotation_matrix, &rotation);
    TransformAndDrawEntries(packet, D_L13_001B1BBC, rotation_matrix, D_L13_001B1BC0, transform);
}
