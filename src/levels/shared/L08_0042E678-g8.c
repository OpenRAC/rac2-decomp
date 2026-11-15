#include "common.h"

/* Four position vectors, colours and UV pairs, followed by GS register words. */
typedef struct {
    float p[4][4];
    u32 color[4];
    float uv[8];
    u64 tag, tex0, tex1, alpha;
} QuadPacket;

typedef struct {
    u8 pad[0x140];
    float position[4];
} DoorCamera;

extern QuadPacket D_L08_00265040[], D_L08_00264F20[], D_L08_00264FB0[];
extern float D_L08_001B1EC4 __attribute__((sda));
extern float D_L08_001B1EAC __attribute__((sda));
extern float D_L08_001B1EB0 __attribute__((sda));
extern float D_L08_001B1EB4 __attribute__((sda));
extern float D_L08_001B1EB8 __attribute__((sda));
extern u8 *D_L08_001B1EC8 __attribute__((sda));
extern int D_L08_001B1ECC __attribute__((sda));
extern int D_L08_001B2508;
extern DoorCamera D_L08_001B99C0;
extern float D_L08_001AC5E0[4][4] MACRO_ADDR;
extern float D_L08_001B9B00[4] NOT_SDA;
extern u8 *D_L08_002B2540[];

extern u64 func_0027C878(int);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern void func_0027C768(void *, float *, float *);
extern void func_00280B90(void *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Draws the tiled door overlay and the collected doors' layered quads.
 * Keep the diameter live before testing the camera side. The first two passes
 * retain their source position pointer between that test and sign selection.
 */
void func_L08_0042E678(u8 *self)
{
    float v[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float radius = *(float *)(self + 0x2C) * 8.0f / *(float *)(*(u8 **)(self + 0x24) + 0x24);
    float diameter = radius + radius;
    float z = *(float *)(self + 0x18) + D_L08_001B1EC4;
    u8 *state = *(u8 **)(self + 0x68);
    float sign;
    int i, j;
    {
        int below = *(float *)(self + 0x18) < D_L08_001B99C0.position[2];
        sign = below ? -1.0f : 1.0f;
    }

    if (state[0x23]) {
        float x, y, y2, f;
        float row = -radius, col;
        D_L08_00265040[0].p[0][2] = D_L08_00265040[0].p[1][2] = D_L08_00265040[0].p[2][2] =
            D_L08_00265040[0].p[3][2] = z + sign * 0.1f;
        D_L08_00265040[0].tex0 = GetEffectTextureDescriptor(-1);
        D_L08_00265040[0].color[0] = D_L08_00265040[0].color[1] = D_L08_00265040[0].color[2] =
            D_L08_00265040[0].color[3] = *(u32 *)(state + 0x20);
        f = IntToFloat(D_L08_001B2508) * D_L08_001B1EAC;
        f = func_002ABB18(f);
        f = func_00283198(f);
        y = *(float *)(self + 0x14) - radius + f * D_L08_001B1EB0;
        D_L08_00265040[0].p[0][1] = y;
        D_L08_00265040[0].p[1][1] = y;
        y2 = y + D_L08_001B1EB8;
        D_L08_00265040[0].p[3][1] = y2;
        D_L08_00265040[0].p[2][1] = y2;
        x = *(float *)(self + 0x10) - radius + f * D_L08_001B1EB4;
        D_L08_00265040[0].p[2][0] = D_L08_00265040[0].p[0][0] = x;
        D_L08_00265040[0].p[1][0] = D_L08_00265040[0].p[3][0] = x + D_L08_001B1EB8;
        func_0027C768(D_L08_00265040[0].p[0], D_L08_00265040[0].uv + 2, D_L08_00265040[0].uv + 3);
        func_0027C768(D_L08_00265040[0].p[2], D_L08_00265040[0].uv + 6, D_L08_00265040[0].uv + 7);
        while (row < radius) {
            col = -radius;
            while (col < radius) {
                D_L08_00265040[0].uv[0] = D_L08_00265040[0].uv[2];
                D_L08_00265040[0].uv[1] = D_L08_00265040[0].uv[3];
                D_L08_00265040[0].uv[4] = D_L08_00265040[0].uv[6];
                D_L08_00265040[0].uv[5] = D_L08_00265040[0].uv[7];
                func_0027C768(D_L08_00265040[0].p[1], D_L08_00265040[0].uv + 2, D_L08_00265040[0].uv + 3);
                func_0027C768(D_L08_00265040[0].p[3], D_L08_00265040[0].uv + 6, D_L08_00265040[0].uv + 7);
                draw_world_quad(D_L08_00265040, 0, 1);
                qcopy(D_L08_00265040[0].p[0], D_L08_00265040[0].p[1]);
                qcopy(D_L08_00265040[0].p[2], D_L08_00265040[0].p[3]);
                D_L08_00265040[0].p[2][0] = D_L08_00265040[0].p[0][0] = D_L08_00265040[0].p[1][0];
                D_L08_00265040[0].p[1][0] = D_L08_00265040[0].p[3][0] = D_L08_00265040[0].p[3][0] +
                    D_L08_001B1EB8;
                col += D_L08_001B1EB8;
            }
            D_L08_00265040[0].p[1][1] = D_L08_00265040[0].p[0][1] = D_L08_00265040[0].p[2][1];
            D_L08_00265040[0].p[2][1] = D_L08_00265040[0].p[3][1] = D_L08_00265040[0].p[3][1] +
                D_L08_001B1EB8;
            D_L08_00265040[0].p[2][0] = D_L08_00265040[0].p[0][0] = D_L08_00265040[0].p[0][0] - diameter;
            D_L08_00265040[0].p[1][0] = D_L08_00265040[0].p[3][0] = D_L08_00265040[0].p[3][0] - diameter;
            func_0027C768(D_L08_00265040[0].p[0], D_L08_00265040[0].uv + 2, D_L08_00265040[0].uv + 3);
            func_0027C768(D_L08_00265040[0].p[2], D_L08_00265040[0].uv + 6, D_L08_00265040[0].uv + 7);
            row += D_L08_001B1EB8;
        }
    }
    if (self != D_L08_001B1EC8)
        return;
    for (i = 0; i < D_L08_001B1ECC; i++) {
        u8 *position;
        self = D_L08_002B2540[i];
        radius = *(float *)(self + 0x2C) * 8.0f / *(float *)(*(u8 **)(self + 0x24) + 0x24);
        z = *(float *)(self + 0x18) + D_L08_001B1EC4;
        state = *(u8 **)(self + 0x68);
        {
            int below = *(float *)(self + 0x18) < D_L08_001B99C0.position[2];
            position = self + 0x10;
            sign = below ? -1.0f : 1.0f;
        }
        qcopy(D_L08_00264F20[0].p[0], position);
        D_L08_00264F20[0].p[0][2] = z + sign * 0.06f;
        qcopy(D_L08_00264F20[0].p[1], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[2], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[3], D_L08_00264F20[0].p[0]);
        D_L08_00264F20[0].color[0] = D_L08_00264F20[0].color[1] = D_L08_00264F20[0].color[2] =
            D_L08_00264F20[0].color[3] = *(u32 *)(state + 0x14);
        D_L08_00264F20[0].p[2][0] = D_L08_00264F20[0].p[0][0] = D_L08_00264F20[0].p[0][0] - radius;
        D_L08_00264F20[0].p[3][0] = D_L08_00264F20[0].p[1][0] = D_L08_00264F20[0].p[1][0] + radius;
        D_L08_00264F20[0].p[1][1] = D_L08_00264F20[0].p[0][1] = D_L08_00264F20[0].p[0][1] - radius;
        D_L08_00264F20[0].p[3][1] = D_L08_00264F20[0].p[2][1] = D_L08_00264F20[0].p[2][1] + radius;
        D_L08_00264F20[0].tex0 = GetEffectTextureDescriptor(*(int *)(state + 0x10) + 0x3F);
        draw_world_quad(D_L08_00264F20, 0, 1);
    }
    for (i = 0; i < D_L08_001B1ECC; i++) {
        u8 *position;
        self = D_L08_002B2540[i];
        radius = *(float *)(self + 0x2C) * 8.0f / *(float *)(*(u8 **)(self + 0x24) + 0x24);
        z = *(float *)(self + 0x18) + D_L08_001B1EC4;
        state = *(u8 **)(self + 0x68);
        {
            int below = *(float *)(self + 0x18) < D_L08_001B99C0.position[2];
            position = self + 0x10;
            sign = below ? -1.0f : 1.0f;
        }
        qcopy(D_L08_00264F20[0].p[0], position);
        D_L08_00264F20[0].p[0][2] = z + sign * 0.04f;
        qcopy(D_L08_00264F20[0].p[1], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[2], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[3], D_L08_00264F20[0].p[0]);
        D_L08_00264F20[0].p[2][0] = D_L08_00264F20[0].p[0][0] = D_L08_00264F20[0].p[0][0] + radius;
        D_L08_00264F20[0].p[3][0] = D_L08_00264F20[0].p[1][0] = D_L08_00264F20[0].p[1][0] - radius;
        D_L08_00264F20[0].p[1][1] = D_L08_00264F20[0].p[0][1] = D_L08_00264F20[0].p[0][1] - radius;
        D_L08_00264F20[0].p[3][1] = D_L08_00264F20[0].p[2][1] = D_L08_00264F20[0].p[2][1] + radius;
        D_L08_00264F20[0].color[0] = D_L08_00264F20[0].color[1] = D_L08_00264F20[0].color[2] =
            D_L08_00264F20[0].color[3] = *(u32 *)(state + 0x14);
        draw_world_quad(D_L08_00264F20, 0, 1);
    }
    for (i = 0; i < D_L08_001B1ECC; i++) {
        self = D_L08_002B2540[i];
        radius = *(float *)(self + 0x2C) * 8.0f / *(float *)(*(u8 **)(self + 0x24) + 0x24);
        z = *(float *)(self + 0x18) + D_L08_001B1EC4;
        state = *(u8 **)(self + 0x68);
        qcopy(D_L08_00264F20[0].p[0], (self + 0x10));
        D_L08_00264F20[0].p[0][2] = z;
        qcopy(D_L08_00264F20[0].p[1], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[2], D_L08_00264F20[0].p[0]);
        qcopy(D_L08_00264F20[0].p[3], D_L08_00264F20[0].p[0]);
        D_L08_00264F20[0].p[2][0] = D_L08_00264F20[0].p[0][0] = D_L08_00264F20[0].p[0][0] + radius;
        D_L08_00264F20[0].p[3][0] = D_L08_00264F20[0].p[1][0] = D_L08_00264F20[0].p[1][0] - radius;
        D_L08_00264F20[0].p[1][1] = D_L08_00264F20[0].p[0][1] = D_L08_00264F20[0].p[0][1] + radius;
        D_L08_00264F20[0].p[3][1] = D_L08_00264F20[0].p[2][1] = D_L08_00264F20[0].p[2][1] - radius;
        D_L08_00264F20[0].color[0] = D_L08_00264F20[0].color[1] = D_L08_00264F20[0].color[2] =
            D_L08_00264F20[0].color[3] = *(u32 *)(state + 0x14);
        draw_world_quad(D_L08_00264F20, 0, 1);
    }
    if (*(int *)(state + 0x18) == -1)
        return;
    for (i = 0; i < D_L08_001B1ECC; i++) {
        self = D_L08_002B2540[i];
        radius = *(float *)(self + 0x2C) * 8.0f / *(float *)(*(u8 **)(self + 0x24) + 0x24);
        z = *(float *)(self + 0x18) + D_L08_001B1EC4;
        qcopy(D_L08_00264FB0[0].p[0], (self + 0x10));
        D_L08_00264FB0[0].p[0][2] = z;
        qcopy(D_L08_00264FB0[0].p[1], D_L08_00264FB0[0].p[0]);
        qcopy(D_L08_00264FB0[0].p[2], D_L08_00264FB0[0].p[0]);
        qcopy(D_L08_00264FB0[0].p[3], D_L08_00264FB0[0].p[0]);
        D_L08_00264FB0[0].p[2][0] = D_L08_00264FB0[0].p[0][0] = D_L08_00264FB0[0].p[0][0] - radius;
        D_L08_00264FB0[0].p[3][0] = D_L08_00264FB0[0].p[1][0] = D_L08_00264FB0[0].p[1][0] + radius;
        D_L08_00264FB0[0].p[1][1] = D_L08_00264FB0[0].p[0][1] = D_L08_00264FB0[0].p[0][1] - radius;
        D_L08_00264FB0[0].p[3][1] = D_L08_00264FB0[0].p[2][1] = D_L08_00264FB0[0].p[2][1] + radius;
        D_L08_00264FB0[0].tex0 = GetEffectTextureDescriptor(*(int *)(state + 0x18) + 0x3F);
        D_L08_00264FB0[0].color[0] = D_L08_00264FB0[0].color[1] = D_L08_00264FB0[0].color[2] =
            D_L08_00264FB0[0].color[3] = *(u32 *)(state + 0x1C);
        for (j = 0; j < 4; j++) {
            FastVecSub(delta, D_L08_00264FB0[0].p[j], D_L08_001B9B00);
            func_00283028(v, delta, D_L08_001AC5E0);
            vec_scale_to_length(v, v, 1.0f);
            D_L08_00264FB0[0].uv[j * 2] = v[0];
            D_L08_00264FB0[0].uv[j * 2 + 1] = v[1];
        }
        draw_world_quad(D_L08_00264FB0, 0, 1);
    }
}
