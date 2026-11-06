/* func_PAL_L12_00425F20, the PAL copy of func_L12_00420B78: the same C, where wrap data[5] (({e}) * 8.0f); lit 8.0f becomes 9.6f. */
#include "common.h"

extern float D_L12_001B1F44 __attribute__((sda));
extern float D_L12_001B1F48 __attribute__((sda));
extern int D_L12_001B363C;
extern float D_L12_001B3640[4] __attribute__((aligned(16), sda));
extern int D_L12_001B29C8[] __attribute__((sda));
extern u8 D_00189EA0[];

/* 294 vertices, in strips of 21. */
extern float D_L12_002A11B0[][4];
typedef struct {
    short vertex;
    short uv;
    short pad;
} L12Corner;

/* 223 quads. */
extern L12Corner D_L12_002A2410[][4];

/* The 144-byte packet func_00281DE8 starts and func_00280B90 submits. */
extern int func_L00_00329520(void *point, int index);
extern void func_L00_002E6CF0(void (*callback)(u8 *), void *object);
extern void func_L00_002E6EF8(void (*callback)(u8 *), void *object);
extern float func_00283198(float angle);
extern float func_002A7878(float low, float high);
extern float func_00282E80(void *a, void *b);

void func_L12_00420950(u8 *object);

void func_PAL_L12_00425F20(u8 *object)
{
    float *data = *(float **)(object + 0x68);
    int i;
    float angle;
    float a, b, c, d, e, f, g, h;

    switch (object[0x20]) {
    case 0:
        data[0] = 0.0f;
        data[1] = 0.25f;
        data[2] = 0.5f;
        data[3] = 0.75f;
        data[8] = 1.0f;
        data[9] = 1.25f;
        data[10] = 1.5f;
        data[11] = 1.75f;
        object[0x20] = 1;
        object[0x30] = 255;
        if (D_L12_002A11B0[0][0] > 1000.0f) {
            for (i = 0; i < 294; i++) {
                D_L12_002A11B0[i][0] *= 0.01f;
                D_L12_002A11B0[i][1] *= 0.01f;
                D_L12_002A11B0[i][2] *= 0.01f;
            }
        }
        break;
    case 1:
        if (func_L00_00329520(D_00189EA0, *(int *)(data + 6)))
            return;
        func_L00_002E6CF0(func_L12_00420950, object);
        D_L12_001B363C = 1;
        qcopy(D_L12_001B3640, D_00189EA0);
        D_L12_001B3640[3] = 48.0f;
        *(short *)(D_00189EA0 + 0x17e) = 5;
        angle = (float)(D_L12_001B29C8[0] % 360) * 0.017444444820284843f - 3.140000104904175f;
        D_L12_001B3640[2] = func_00283198(angle) * 0.25f + 59.5f;
        data[4] += ((data[5]) * 1.2f);
        if (data[4] >= 8.0f)
            data[4] -= 8.0f;
        a = func_00283198(data[0] * 3.141590118408203f) * 0.001f;
        b = func_00283198(data[1] * 3.141590118408203f) * 0.001f;
        c = func_00283198(data[2] * 3.141590118408203f) * 0.001f;
        d = func_00283198(data[3] * 3.141590118408203f) * 0.001f;
        e = func_00283198(data[0] * 3.141590118408203f) * 0.001f;
        f = func_00283198(data[1] * 3.141590118408203f) * 0.001f;
        g = func_00283198(data[2] * 3.141590118408203f) * 0.001f;
        h = func_00283198(data[3] * 3.141590118408203f) * 0.001f;
        for (i = 0; i < 21; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += a;
        }
        for (i = 21; i < 42; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += b;
        }
        for (i = 42; i < 63; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += c;
        }
        for (i = 63; i < 84; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += d;
        }
        for (i = 84; i < 105; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += e;
        }
        for (i = 105; i < 126; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += f;
        }
        for (i = 126; i < 147; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += g;
        }
        for (i = 147; i < 168; i++) {
            float *p = D_L12_002A11B0[i];

            p[2] += h;
        }
        data[0] += 0.01f;
        data[1] += 0.01f;
        data[2] += 0.01f;
        data[3] += 0.01f;
        data[8] += 0.01f;
        data[9] += 0.01f;
        data[10] += 0.01f;
        data[11] += 0.01f;
        if (data[0] > 2.0f) data[0] = 0;
        if (data[1] > 2.0f) data[1] = 0;
        if (data[2] > 2.0f) data[2] = 0;
        if (data[3] > 2.0f) data[3] = 0;
        data[5] = func_002A7878(D_L12_001B1F44, D_L12_001B1F48);
        break;
    case 2:
        if (func_00282E80(object + 0x10, D_00189EA0) < 64.0f)
            func_L00_002E6EF8(func_L12_00420950, object);
        break;
    }
}
