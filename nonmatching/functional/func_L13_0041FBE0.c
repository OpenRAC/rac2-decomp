/* functional: high. From the near-miss draft (pinned-profile near miss; register allocation differs); same reads, writes and calls in retail's order, fade compares in retail's c.le.s / c.lt.s sense. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { Vector vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long long state[4]; } DrawPacket;
extern float D_L13_001B98C0[4] __attribute__((nosda));
extern unsigned int D_L13_001B1A90 __attribute__((sda));
extern unsigned int D_L13_001B1A94 __attribute__((nosda));
extern unsigned int D_L13_001B1A98 __attribute__((nosda));
extern unsigned int D_L13_001B1A9C __attribute__((nosda));
extern int D_L13_001B1A40 __attribute__((sda));
extern int D_L13_001B1A44 __attribute__((nosda));
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
    func_00283658(transform, object + 0xC0);
    qcopy(transform + 12, object + 0x10);
    one = 1.0f;
    transform[15] = one;
    func_00282F20(transform, transform, 4.0f);
    func_00282F20(transform + 4, transform + 4, 10.0f);
    func_00282CF0(&direction, D_L13_001B98C0, object + 0x10);
    func_002AFDD8(object, (char *)&direction, (char *)&direction, 0);
    if (direction.f[0] < 0.0f) func_00282D30(transform, transform, -1.0f);
    amount = func_00283198(*(float *)(private + 0x20)) * 0.5f + 0.5f;
    main_color = func_00283D38(D_L13_001B1A90, D_L13_001B1A94, amount);
    trim_color = func_00283D38(D_L13_001B1A98, D_L13_001B1A9C, amount);
    fade_a = *(float *)(private + 4);
    if (!(0.2f <= fade_a)) fade_a = one - fade_a * 5.0f;
    edge[0] = func_00283D38(D_L13_001B1A9C, D_L13_001B1A9C & 0xFFFFFF, fade_a);
    fade_b = *(float *)(private + 8);
    if (!(0.2f <= fade_b)) fade_b = 1.0f - fade_b * 5.0f;
    edge[1] = func_00283D38(D_L13_001B1A9C, D_L13_001B1A9C & 0xFFFFFF, fade_b);
    if (*(float *)private < 1.0f) {
        main_color = func_00283D38(main_color & 0xFFFFFF, main_color, *(float *)private);
        trim_color = func_00283D38(trim_color & 0xFFFFFF, trim_color, *(float *)private);
        edge[0] = func_00283D38(edge[0] & 0xFFFFFF, edge[0], *(float *)private);
        edge[1] = func_00283D38(edge[1] & 0xFFFFFF, edge[1], *(float *)private);
    }
    func_L02_002EF968(packet, D_L13_001B1A40, main_color, D_L13_001B1A50, D_L13_001B1AB0, 1);
    func_L02_002EF968(packet + 1, D_L13_001B1A44, trim_color, D_L13_001B1A70, D_L13_001B1AF0, 1);
    func_L02_002EF968(packet + 2, D_L13_001B1A44, trim_color, D_L13_001B1A70, D_L13_001B1B30, 1);
    func_L02_002EF968(packet + 3, D_L13_001B1A44, edge[0], D_L13_001B1A70, D_L13_001B1AF0, 1);
    func_L02_002EF968(packet + 4, D_L13_001B1A44, edge[0], D_L13_001B1A70, D_L13_001B1B30, 1);
    func_L02_002EF968(packet + 5, D_L13_001B1A44, edge[1], D_L13_001B1A70, D_L13_001B1AF0, 1);
    func_L02_002EF968(packet + 6, D_L13_001B1A44, edge[1], D_L13_001B1A70, D_L13_001B1B30, 1);
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
    func_00115484(offsets, 0, 32);
    offsets[0].f[2] = *(float *)(private + 4) * D_L13_001B1BB4;
    offsets[1].f[2] = *(float *)(private + 8) * D_L13_001B1BB4;
    subtract_offsets[0].quad = offsets[0].quad;
    subtract_offsets[1].quad = offsets[1].quad;
    func_002833F0(rotation_matrix, &rotation);
    func_L01_002E1510(packet, D_L13_001B1BBC, rotation_matrix, D_L13_001B1BC0, transform);
    for (i = 0; i < 4; i++) {
        func_00282CC0(packet[0].vertex + i, D_L13_001B1AB0 + i, &setup);
        func_00282CC0(packet[1].vertex + i, D_L13_001B1AF0 + i, &setup);
        func_00282CC0(packet[2].vertex + i, D_L13_001B1B30 + i, &setup);
        func_00282CC0(packet[3].vertex + i, D_L13_001B1AF0 + i, &setup);
        func_00282CC0(packet[4].vertex + i, D_L13_001B1B30 + i, &setup);
        func_00282CC0(packet[5].vertex + i, D_L13_001B1AF0 + i, &setup);
        func_00282CC0(packet[6].vertex + i, D_L13_001B1B30 + i, &setup);
        func_00282CF0(packet[3].vertex + i, packet[3].vertex + i, subtract_offsets);
        func_00282CC0(packet[4].vertex + i, packet[4].vertex + i, subtract_offsets);
        func_00282CF0(packet[5].vertex + i, packet[5].vertex + i, subtract_offsets + 1);
        func_00282CC0(packet[6].vertex + i, packet[6].vertex + i, subtract_offsets + 1);
    }
    func_002833F0(rotation_matrix, &rotation);
    func_L01_002E1510(packet, D_L13_001B1BBC, rotation_matrix, D_L13_001B1BC0, transform);
}
