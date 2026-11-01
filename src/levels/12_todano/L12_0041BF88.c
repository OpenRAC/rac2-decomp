#include "common.h"

typedef int BF88Quad __attribute__((mode(TI)));
typedef union { BF88Quad q; float f[4]; } __attribute__((aligned(16))) BF88Vector;
typedef struct {
    BF88Vector point[4];
    u32 color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} __attribute__((aligned(16))) BF88Packet;
extern u8 *D_L12_001B2F8C;
extern float D_L12_001B1D20[8] SDATA(D_L12_001B1D20);
extern float D_L12_001B1D24[];
extern float D_L12_001B1D40 SDATA(D_L12_001B1D40);
extern float D_L12_001B1D44 SDATA(D_L12_001B1D44);
extern float D_L12_001B1D80 SDATA(D_L12_001B1D80);
extern float D_L12_001B1D84 SDATA(D_L12_001B1D84);
extern s32 D_L12_001B1D14 SDATA(D_L12_001B1D14);
extern s32 D_L12_001B1D18 SDATA(D_L12_001B1D18);
extern s32 D_L12_001B1D1C SDATA(D_L12_001B1D1C);
extern s32 D_L12_001B1D4C SDATA(D_L12_001B1D4C);
extern s32 D_L12_001B1D50 SDATA(D_L12_001B1D50);
extern s32 D_L12_001B1D54 SDATA(D_L12_001B1D54);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern u64 func_0027C878(int);
extern u32 func_00283D38(u32, u32, float);

void func_L12_0041BF88(u8 *self)
{
    BF88Packet packet;
    BF88Vector matrix[4], rotation[4], angle, offset;
    u8 *p = *(u8 **)(self + 0x68);
    float width, height, thickness;
    float halfWidth;
    float h, y, phase, nextPhase, step, halfHeight;
    int i, j, k, n;

    angle.q = 0;
    angle.f[1] = 1.5707964897155762f;
    height = *(float *)(p + 0x44);
    width = *(float *)(p + 0x40);
    func_00283410(rotation, &angle);
    ({
        BF88Vector corner;
        corner.q = 0;
        thickness = width * 0.5f;
        corner.f[1] = thickness;
        corner.f[2] = D_L12_001B1D40;
        corner.f[3] = 1.0f;
        offset.q = corner.q;
    });
    func_00283410(matrix, D_L12_001B2F8C + *(int *)p * 128 + 0x70);
    qcopy(&matrix[3], D_L12_001B2F8C + *(int *)p * 128 + 0x30);
    matrix[3].f[2] -= height * 0.5f + 0.5f;
    matrix[3].f[3] = 1.0f;
    {
        u32 color = D_L12_001B1D4C;
        for (n = 0; n < 4; n++) {
            packet.color[n] = color;
            packet.uv[n][0] = D_L12_001B1D20[n * 2];
            packet.uv[n][1] = D_L12_001B1D24[n * 2];
            qcopy(&packet.point[n], &offset);
            if (n < 2) packet.point[n].f[1] = -packet.point[n].f[1];
            if (n & 1) packet.point[n].f[2] = -packet.point[n].f[2];
            packet.point[n].f[2] += 0.25f;
        }
    }
    packet.texture = func_0027C878(D_L12_001B1D14);
    packet.setup = 0xFF9000000260ULL;
    packet.state = ((u64)D_L12_001B1D18 << 2) | ((u64)D_L12_001B1D1C << 6) | 0x8000000000ULL;
    packet.reserved = 0;
    for (h = 0.0f; h <= height - 0.1f; h += 0.5f) {
        for (j = 0; j < 4; j++) {
            if (j >= 2) {
                if (h <= 2.5f) packet.point[j].f[1] = *(float *)(p + 0x34);
                else if (h <= 4.5f) packet.point[j].f[1] = *(float *)(p + 0x38);
                else packet.point[j].f[1] = width;
            }
            packet.point[j].f[2] += 0.5f;
        }
        ({
            BF88Packet rotated;
            rotated = packet;
            for (i = 0; i < 4; i++)
                func_002830C0(&rotated.point[i], &packet.point[i], matrix);
            func_00280B90(&rotated, 0, 1);
        });
    }
    for (k = 0; k < 4; k++) {
        thickness = D_L12_001B1D44;
        packet.point[k].f[2] -= height;
        if (packet.point[k].f[2] <= 0.0f) thickness = -thickness;
        packet.point[k].f[2] = thickness;
    }
    y = *(float *)(p + 0x34);
    phase = *(float *)(p + 4);
    step = 0.5f / width;
    halfWidth = width * 0.5f;
    halfHeight = height * 0.5f;
    for (; y > -halfWidth; y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 0; i < 2; i++) packet.point[i].f[2] = -halfHeight; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 3; i >= 0; i--) packet.point[i].f[0] = D_L12_001B1D80; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = -D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            func_00280B90(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            func_00280B90(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = func_00283D38(D_L12_001B1D50, D_L12_001B1D54, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
    for (y = *(float *)(p + 0x38); y > *(float *)(p + 0x34); y -= 0.5f) {
        nextPhase = phase + step;
        { int j; for (j = 0; j < 4; j++) {
            packet.point[j].f[1] = y;
            if (j & 1) packet.point[j].f[1] = y + 0.5f;
        } }
        { int i; for (i = 1; i >= 0; i--) packet.point[i].f[2] = D_L12_001B1D84; }
        packet.point[2].f[2] = packet.point[3].f[2] = halfHeight + halfHeight;
        { int i; for (i = 3; i >= 0; i--) packet.point[i].f[0] = D_L12_001B1D80; }
        ({
            BF88Packet rotated, side;
            rotated = packet;
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            rotated = packet;
            func_00280B90(&rotated, matrix, 1);
            { int i; for (i = 3; i >= 0; i--) rotated.point[i].f[0] = -D_L12_001B1D80; }
            func_00280B90(&rotated, matrix, 1);
            side = packet;
            qcopy(&side.point[0], &packet.point[0]);
            qcopy(&side.point[1], &rotated.point[0]);
            qcopy(&side.point[2], &packet.point[2]);
            qcopy(&side.point[3], &rotated.point[2]);
            func_00280B90(&side, matrix, 1);
            qcopy(&side.point[0], &packet.point[1]);
            qcopy(&side.point[1], &rotated.point[1]);
            qcopy(&side.point[2], &packet.point[3]);
            qcopy(&side.point[3], &rotated.point[3]);
            func_00280B90(&side, matrix, 1);
        });
        { int i; for (i = 0; i < 4; i++)
            packet.color[i] = func_00283D38(D_L12_001B1D50, D_L12_001B1D54, phase); }
        phase = nextPhase;
        if (nextPhase > 0.0f) phase = nextPhase - 1.0f;
    }
}
