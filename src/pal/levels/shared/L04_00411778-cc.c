/* func_PAL_L04_00411778, the PAL copy of func_L04_0040D148: the same C. */
#include "common.h"

typedef unsigned int B1202Quad __attribute__((mode(TI)));
typedef union {
    B1202Quad bits;
    float f[4];
} RenderVector;
typedef struct {
    RenderVector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long long primitive, texture, mode, flags;
} B1202Packet;

extern int D_L04_001B2008[] __attribute__((sda));
extern float func_00283CE0(int);
extern float func_00283D00(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283C28(float);
extern float func_00283B98(float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_00283410(void *, void *);
extern void func_00282F20(void *, void *, float);
extern unsigned long long func_0027C878(int);
extern void func_002AF000(void *, float, float, float);
extern void func_00280B90(void *, void *, int);
extern void func_L04_0040DCA8(void *, int, unsigned int, int, float, float, float, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void func_L00_003F8280(void *, int, int, float, float, float, float, float);

/* This unit is built with -g: retail's nops before the two latitude divisions
 * are the assembler's div.s floor after a line label, so keep one statement per
 * line. rows and cols must stay variables: as constants the loops' zero-trip
 * tests fold before gcse, which then hoists the vertex addresses into spill
 * slots. t is one local on purpose: its use in the inner loop, where $f12 is
 * already loaded for the next call, keeps it out of $f12 at the blend calls. */
void func_PAL_L04_00411778(unsigned char *m, int alpha)
{
    B1202Packet packet;
    float matrix[4][4] __attribute__((aligned(16)));
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float t, offset, lat0, lat1, lon0, lon1, u0, v0, v1, cos0, cos1;
    unsigned int color, a, c;
    int i, j;
    int rows = 10, cols = 10;

    t = func_00283198(func_00283D00(func_00283CE0(D_L04_001B2008[0]), 150.33334f) * 0.0066518844f * 6.283186f);
    t = (t + 1.0f) * 0.5f;
    if (alpha == -1) {
        color = func_00283D38(0x1fb43264, 0x1f502800, t);
    } else {
        if (alpha < 0) {
            alpha = 0;
        }
        color = func_00283D38(0x1fb43264, ((unsigned int)alpha << 24) | 0x502800, t);
    }
    offset = func_00283D00(func_00283CE0(D_L04_001B2008[0]), 25.333334f) * 0.039473683f;
    func_00283410(matrix, m + 0xf0);
    *(B1202Quad *)(matrix[3]) = *(B1202Quad *)(m + 0x10);
    func_00282F20(matrix[0], matrix[0], 0.4f);
    func_00282F20(matrix[1], matrix[1], 0.35f);
    func_00282F20(matrix[2], matrix[2], 0.35f);
    packet.texture = func_0027C878(21);
    packet.mode = 0xff9000000260ULL;
    packet.flags = 0x8000000048ULL;
    packet.primitive = 0;
    for (i = 0; i < rows; i++) {
        lat0 = func_00283CE0(i) * 3.141593f / func_00283CE0(rows) - 1.5707965f;
        lat1 = func_00283CE0(i + 1) * 3.141593f / func_00283CE0(rows) - 1.5707965f;
        v0 = (func_00283198(lat0) + 1.0f) * 0.5f;
        v1 = (func_00283198(lat1) + 1.0f) * 0.5f;
        for (j = 0; j < cols; j++) {
            lon0 = func_00283C28(func_00283CE0(j) * 6.283186f / func_00283CE0(cols));
            lon1 = func_00283C28(func_00283CE0(j + 1) * 6.283186f / func_00283CE0(cols));
            cos0 = func_00283180(lon0);
            cos1 = func_00283180(lon1);
            u0 = offset + (cos0 + 1.0f) * 0.5f;
            t = offset + (cos1 + 1.0f) * 0.5f;
            packet.uv[1][1] = v0;
            packet.uv[0][1] = v0;
            packet.uv[3][1] = v1;
            packet.uv[2][1] = v1;
            packet.color[3] = color;
            packet.color[2] = color;
            packet.color[1] = color;
            packet.color[0] = color;
            packet.uv[0][0] = u0;
            packet.uv[1][0] = t;
            packet.uv[2][0] = u0;
            packet.uv[3][0] = t;
            func_002AF000(packet.vertex[0].f, 1.0f, lon0, lat0);
            func_002AF000(packet.vertex[1].f, 1.0f, lon1, lat0);
            func_002AF000(packet.vertex[2].f, 1.0f, lon0, lat1);
            func_002AF000(packet.vertex[3].f, 1.0f, lon1, lat1);
            packet.vertex[0].f[3] = 1.0f;
            packet.vertex[1].f[3] = 1.0f;
            packet.vertex[2].f[3] = 1.0f;
            packet.vertex[3].f[3] = 1.0f;
            func_00280B90(&packet, matrix, 0);
        }
    }
    *(float *)(p + 0x4b4) = func_00283B98(*(float *)(p + 0x4b4), 0.01f);
    *(float *)(p + 0x4b8) = func_00283B98(*(float *)(p + 0x4b8), -0.007f);
    *(float *)(p + 0x4bc) = func_00283B98(*(float *)(p + 0x4bc), 0.007f);
    *(float *)(p + 0x4c0) = func_00283B98(*(float *)(p + 0x4c0), *(float *)(p + 0x30c) * 0.1f);
    if (alpha == -1) {
        func_L04_0040DCA8(m + 0x10, *(int *)(p + 0x648), 0x0fc8c8c8, 1, 0.495f, 0.35f, *(float *)(p + 0x4b4), *(float *)(m + 0xf4));
        func_L04_0040DCA8(m + 0x10, *(int *)(p + 0x648), 0x0fc8c8c8, 1, 0.495f, 0.35f, *(float *)(p + 0x4b8), *(float *)(m + 0xf4));
        func_L04_0040DCA8(m + 0x10, 54, 0x28969600, 1, 0.385f, 0.35f, *(float *)(p + 0x4bc), *(float *)(m + 0xf4));
    } else {
        if (alpha < 0) {
            alpha = 0;
        }
        a = (unsigned int)alpha << 24;
        c = a | 0xc8c8c8;
        func_L04_0040DCA8(m + 0x10, *(int *)(p + 0x648), c, 1, 0.495f, 0.35f, *(float *)(p + 0x4b4), *(float *)(m + 0xf4));
        func_L04_0040DCA8(m + 0x10, *(int *)(p + 0x648), c, 1, 0.495f, 0.35f, *(float *)(p + 0x4b8), *(float *)(m + 0xf4));
        func_L04_0040DCA8(m + 0x10, 54, a | 0x969600, 1, 0.385f, 0.35f, *(float *)(p + 0x4bc), *(float *)(m + 0xf4));
    }
    func_L00_003F8280(m + 0x10, *(int *)(p + 0x644), 0, 0.32f, 0.5f, *(float *)(p + 0x4c0), 0.0f, 0.0f);
}
