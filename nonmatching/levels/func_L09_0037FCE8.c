/* func_L09_0037FCE8: near miss, 2492/2488 bytes, 0 of 2 places (USA v1.01, 1 November 2026).

   Profile: its own unit, `-O2 -G8 -ffunction-sections -g` (-g for the nop pairs before div.s).

   The arena floor draw (Dobbo and Yeedil): the fan of six strips between the stage edges, then
   two layers of a tiled grid around the camera with distance-faded quads. Calls, constants,
   GS register words and the vertex/colour/uv tables follow retail, and the size is 4 bytes
   over.
   What differs: allocation. Retail's frame is 0x1F0 (here 0x180): it keeps the row counter,
   both grid colours, the per-row tile/uv pointers and next row in stack slots 0x130..0x148,
   uses $f27 as well, keeps the z column pointer in the caller-saved $t9 and saves it around
   each call with sq/lq at 0x150 (the 128-bit caller-save), and addresses the camera record
   D_L09_001BDF00 from its base. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));

extern char D_L09_001BDF00[];
extern int D_0018C0B4;
extern int D_L09_001A8A48;
extern int D_001A79F0 MACRO_ADDR;
extern char D_L09_001B9C30[];
extern char D_L09_001B9A00[];
extern float D_L09_001B3120 MACRO_ADDR;
extern float D_L09_001B3110[][2];
extern float D_L09_001AEC38[] __attribute__((sda));
extern char D_L09_001B98C0[];
extern float D_L09_002336A0[][3];
extern int D_L09_002339A0[];
extern float D_L09_00233EA0[][2];
extern float D_L09_00233AA0[][3];
extern int D_L09_00233DA0[];
extern float D_L09_002340A0[][2];
extern unsigned long long func_0027C878(int);
extern void func_00280328(void);
extern void func_00281810(int, void *, void *, void *, int);
extern void func_00282A28(void);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern void func_002FC560(unsigned int, unsigned long long);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))

/* Draws the arena floor: a fan of six strips between the two edges of the stage, coloured from
   the object's two colours, then two layers of a tiled grid around the camera whose quads
   fade with their distance from it. */
void func_L09_0037FCE8(char *self)
{
    Vector a;
    Vector b;
    Vector across;
    Vector up;
    Vector corner[4];
    Vector left;
    Vector right;
    unsigned long long registers[4];
    char *q = *(char **)(self + 0x68);
    float far, near;
    float t, scale;
    int i, k, n, row, next, colour, inner, outer;

    near = F(D_L09_001BDF00, 0x228);
    far = F(D_L09_001BDF00, 0x22C);
    if (D_0018C0B4 != 0x1C && D_L09_001A8A48 == 0) {
        F(D_L09_001BDF00, 0x228) = 255.0f;
        F(D_L09_001BDF00, 0x22C) = 249.9f;
    }
    func_002FC560(0x42, 0x3200000044ULL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260ULL);
    if (I(q, 0x38) != 0) {
        func_002FC560(0x47, 0x5310B);
    } else {
        func_002FC560(0x47, 0x513F1);
    }
    func_002FC560(6, func_0027C878(0x16));
    func_00280328();
    across[0] = 1.0f;
    across[1] = 0.0f;
    across[2] = 0.0f;
    across[3] = 1.0f;
    func_00283098(across, across, D_L09_001B9C30);
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 1.0f;
    func_00283098(up, up, D_L09_001B9C30);
    if (D_001A79F0 != 13) {
        across[2] = 0.0f;
    }
    func_00282F20(across, across, 1.0f);
    if (D_001A79F0 != 13) {
        up[2] = 0.0f;
    }
    func_00282F20(up, up, 1.0f);
    func_00282F20(a, across, -75.0f);
    func_00282F20(b, up, -87.0f);
    func_00282CC0(corner[0], a, b);
    func_00282F20(b, up, 87.0f);
    func_00282CC0(corner[2], a, b);
    func_00282F20(a, across, F(q, 0x28));
    func_00282F20(b, up, -750.0f);
    func_00282CC0(corner[1], a, b);
    func_00282F20(b, up, 750.0f);
    func_00282CC0(corner[3], a, b);
    for (k = 0; k < 4; k++) {
        func_00282CC0(corner[k], corner[k], D_L09_001B9A00);
        corner[k][2] = D_L09_001B3120;
    }
    func_00282CF0(left, corner[1], corner[0]);
    func_00282CF0(right, corner[3], corner[2]);
    for (i = 0; i < 12; i += 2) {
        t = func_00283CE0(i) * 0.1f;
        colour = func_00283D38(I(q, 0x0), I(q, 0x4), func_00283CE0(i) / 10.0f);
        func_00282D30(a, left, t);
        D_L09_002339A0[i] = colour;
        D_L09_00233EA0[i][0] = 0.0f;
        D_L09_00233EA0[i][1] = 0.0f;
        func_00282CC0(a, a, corner[0]);
        D_L09_002336A0[i][0] = a[0];
        D_L09_002336A0[i][1] = a[1];
        D_L09_002336A0[i][2] = a[2];
        func_00282D30(a, right, t);
        D_L09_002339A0[i + 1] = colour;
        D_L09_00233EA0[i + 1][0] = 0.0f;
        D_L09_00233EA0[i + 1][1] = 0.0f;
        func_00282CC0(a, a, corner[2]);
        D_L09_002336A0[i + 1][0] = a[0];
        D_L09_002336A0[i + 1][1] = a[1];
        D_L09_002336A0[i + 1][2] = a[2];
    }
    func_00281810(12, D_L09_002336A0, D_L09_002339A0, D_L09_00233EA0, 1);

    row = 0;
    registers[1] = func_0027C878(0x16);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = 0x8000000044ULL;
    registers[0] = 0;
    func_002FC560(0x42, 0x8000000048ULL);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260ULL);
    func_002FC560(0x47, 0x513F1);
    inner = func_00283D38(0, I(q, 0xC), 1.0f);
    outer = func_00283D38(0, I(q, 0x10), 1.0f);
    do {
        float y;

        next = row + 1;
        func_002FC560(6, func_0027C878(I(q, 0x1C) + row + 0x3F));
        for (y = F(q, 0x18) * -2.0f; y < F(q, 0x18) + F(q, 0x18); y += F(q, 0x18)) {
            float x;

            n = 0;
            for (x = F(q, 0x18) * -2.0f; x < F(q, 0x18) + F(q, 0x18); x += F(q, 0x18)) {
                float tile = D_L09_001AEC38[row];
                float u0 = D_L09_001B3110[row][0];
                float v0 = D_L09_001B3110[row][1];
                float px = x + F(D_L09_001B98C0, 0x140) + 1.0f;
                float py = y + F(D_L09_001B98C0, 0x144) + 1.0f;
                float pz = D_L09_001B3120 + (float)next * 0.05f;
                int end;

                D_L09_002340A0[n][0] = x / (F(q, 0x18) + F(q, 0x18)) * tile + u0;
                D_L09_00233AA0[n][0] = px;
                D_L09_00233AA0[n][1] = py;
                D_L09_00233AA0[n][2] = pz;
                D_L09_002340A0[n][1] = y / (F(q, 0x18) + F(q, 0x18)) * tile + v0;
                D_L09_002340A0[n + 1][0] = x / (F(q, 0x18) + F(q, 0x18)) * tile + u0;
                D_L09_00233AA0[n + 1][0] = px;
                D_L09_002340A0[n + 1][1] = (y + F(q, 0x18)) / (F(q, 0x18) + F(q, 0x18)) * tile + v0;
                D_L09_00233AA0[n + 1][1] = y + F(q, 0x18) + F(D_L09_001B98C0, 0x144) + 1.0f;
                D_L09_00233AA0[n + 1][2] = pz;
                D_L09_002340A0[n + 2][0] = (x + F(q, 0x18)) / (F(q, 0x18) + F(q, 0x18)) * tile + u0;
                D_L09_002340A0[n + 2][1] = y / (F(q, 0x18) + F(q, 0x18)) * tile + v0;
                D_L09_00233AA0[n + 2][0] = x + F(q, 0x18) + F(D_L09_001B98C0, 0x140) + 1.0f;
                D_L09_00233AA0[n + 2][1] = py;
                D_L09_00233AA0[n + 2][2] = pz;
                D_L09_002340A0[n + 3][0] = (x + F(q, 0x18)) / (F(q, 0x18) + F(q, 0x18)) * tile + u0;
                D_L09_002340A0[n + 3][1] = (y + F(q, 0x18)) / (F(q, 0x18) + F(q, 0x18)) * tile + v0;
                D_L09_00233AA0[n + 3][0] = x + F(q, 0x18) + F(D_L09_001B98C0, 0x140) + 1.0f;
                D_L09_00233AA0[n + 3][1] = y + F(q, 0x18) + F(D_L09_001B98C0, 0x144) + 1.0f;
                D_L09_00233AA0[n + 3][2] = pz;
                end = n + 4;
                for (k = n; k < end; k++) {
                    a[0] = D_L09_00233AA0[k][0] - F(D_L09_001B98C0, 0x140);
                    a[1] = D_L09_00233AA0[k][1] - F(D_L09_001B98C0, 0x144);
                    a[2] = D_L09_00233AA0[k][2] - F(D_L09_001B98C0, 0x148);
                    a[3] = 1.0f;
                    scale = func_00282E20(a) / (F(q, 0x18) + F(q, 0x18));
                    if (1.0f < scale) {
                        scale = 1.0f;
                    }
                    D_L09_00233DA0[k] = func_00283D38(inner, outer, scale);
                }
                n = end;
                if (n >= 64) {
                    func_00282A28();
                }
            }
            func_00281810(n, D_L09_00233AA0, D_L09_00233DA0, D_L09_002340A0, 1);
        }
        row = next;
    } while (row < 2);
    F(D_L09_001BDF00, 0x22C) = far;
    F(D_L09_001BDF00, 0x228) = near;
    func_002FC560(0x47, 0x5360B);
}
